/*
        Copyright (C) ColdStars, Aleksandr Pivovarov <<coldstars8@gmail.com>>
        
        This program is free software; you can redistribute it and/or
        modify it under the terms of the GNU General Public License
        as published by the Free Software Foundation; either version 2
        of the License, or (at your option) any later version.
        
        This program is distributed in the hope that it will be useful,
        but WITHOUT ANY WARRANTY; without even the implied warranty of
        MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
        GNU General Public License for more details.
        
        You should have received a copy of the GNU General Public License
        along with this program; if not, write to the Free Software
        Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
*/


#include "ItemSlot.hpp"

#include "../builder/spaceobjects/ContainerBuilder.hpp"

#include "../spaceobjects/Vehicle.hpp"
#include "../spaceobjects/Container.hpp"
#include "../pilots/Npc.hpp"

#include "../world/starsystem.hpp"
#include "../parts/Turrel.hpp"

#include "../items/equipment/RocketEquipment.hpp"
#include "../items/equipment/LazerEquipment.hpp"
#include "../items/equipment/RadarEquipment.hpp"
#include "../items/equipment/GrappleEquipment.hpp"

#include "../items/others/Bomb.hpp"

#include "../dock/Store.hpp"
#include "../dock/Angar.hpp"

#include <ceti/Logger.hpp>
#include <meti/RandUtils.hpp>

#include <common/Global.hpp>
#include <managers/EntitiesManager.hpp>

ItemSlot::ItemSlot(unsigned long int TYPE::ENTITY subtype_id)
    :
      m_turrel(nullptr),
      m_item(nullptr),
      m_target(nullptr),
      m_subtarget(nullptr),
      m_hitProbability(0)
{
    setId(id);
    setTypeId(TYPE::ENTITY::ITEM_SLOT_ID);
    setSubTypeId(subtype_id);
    
    m_hitProbability = meti::getRandInt(0, 100); // (tmp) move to builder
}

/* virtual */
ItemSlot::~ItemSlot()
{
    Logger::Instance().Log("___::~ItemSlot("+std::to_string(id())+")");
}  

/* virtual */  
void ItemSlot::putChildrenToGarbage() const
{
    if (m_item) {
        global::get().entitiesManager().addToGarbage(m_item);
    }
}

void ItemSlot::setTarget(SpaceObject* target, ItemSlot* subtarget)
{
    m_target    = target;
    m_subtarget = subtarget;
}

STATUS ItemSlot::validateTarget()
{       
    if (m_subtarget) {
        if (!checkSubTarget(m_subtarget)) {
            m_subtarget = nullptr; // reseting only subtarget, firemode for target will be used
        }
    }
    
    STATUS status = checkTarget(m_target);
    if (status != STATUS::OK) {
        Logger::Instance().Log(getTargetStatusStr(status), WEAPONSTARGET_LOG_DIP);
    }

    return status;
}

void ItemSlot::resetTarget()
{ 
    m_target    = nullptr;
    m_subtarget = nullptr;
}

bool ItemSlot::checkAmmo() const
{
    switch(item()->subTypeId())
    {
        case TYPE::ENTITY::LAZER_EQUIPMENT_ID:  { /*if check energy */  return true; break; }
        case TYPE::ENTITY::ROCKET_EQUIPMENT_ID: { if (rocketEquipment()->GetAmmo() > 0) return true; break; }
    }
    
    return false;
}

void ItemSlot::fireEvent(float attack_rate, bool show_effect)
{
    switch(item()->subTypeId())
    {
        case TYPE::ENTITY::LAZER_EQUIPMENT_ID:
        {
            lazerEquipment()->FireEvent(target(), subtarget(), attack_rate, show_effect);
            break;
        }

        case TYPE::ENTITY::ROCKET_EQUIPMENT_ID:
        {
            rocketEquipment()->FireEvent(attack_rate);
            break;
        }
    }

    if (target()->isAlive() == false)
    {
        GetOwnerVehicle()->GetOwnerNpc()->AddExpirience(target()->givenExpirience(), show_effect);
    }
}

bool ItemSlot::checkItemInsertion(BaseItem* item) const
{
    if (subTypeId() == TYPE::ENTITY::CARGO_SLOT_ID)
    {
        return true;
    }

    if (subTypeId() == item->parentSubTypeId())
    {
        return true;
    }
    
    return false;
}

bool ItemSlot::insertItem(BaseItem* item)
{    
    if (subTypeId() == TYPE::ENTITY::GATE_SLOT_ID)
    {
        m_item = item;
        dropItemToSpace();
        return true;
    }

    if (subTypeId() == TYPE::ENTITY::CARGO_SLOT_ID)
    {
        m_item = item;
        if (item->itemSlot() != nullptr)
        {
            item->itemSlot()->removeItem();
        }
        item->setItemSlot(this);

        return true;
    }

    if (subTypeId() == item->parentSubTypeId())
    {
        m_item = item;
        if (item->itemSlot() != nullptr)
        {
            item->itemSlot()->removeItem();
        }
        item->setItemSlot(this);
        updateVehiclePropetries();

        return true;
    }
    
    return false;
}

void ItemSlot::removeItem()
{    
    m_item = nullptr;
    resetTarget();

    if (subTypeId() != TYPE::ENTITY::CARGO_SLOT_ID)
    {
        updateVehiclePropetries();
    }
}

void ItemSlot::selectEvent()
{
    selected = true;

    if (owner->typeId() == TYPE::ENTITY::VEHICLE_ID)
    {
        switch(subTypeId())
        {
            case TYPE::ENTITY::DRIVE_SLOT_ID: { GetOwnerVehicle()->UpdatePropertiesSpeed(); break; }
        }
    }
}

void ItemSlot::deselectEvent()
{
    selected = false;
    
    if (owner->typeId() == TYPE::ENTITY::VEHICLE_ID)
    {
        switch(subTypeId())
        {
            case TYPE::ENTITY::WEAPON_SLOT_ID:     {     resetTarget(); break; }
            case TYPE::ENTITY::DRIVE_SLOT_ID:
            {
                GetOwnerVehicle()->UpdatePropertiesSpeed();
                //GetOwnerVehicle()->UpdatePropertiesJump();
                break;
            }
        }
    }

}

void ItemSlot::updateVehiclePropetries() const
{
    if (subTypeId() != TYPE::ENTITY::CARGO_SLOT_ID)
    {
        switch(subTypeId())
        {
            case TYPE::ENTITY::WEAPON_SLOT_ID:     { GetOwnerVehicle()->UpdatePropertiesFire(); break; }
            case TYPE::ENTITY::SCANER_SLOT_ID:     { GetOwnerVehicle()->UpdatePropertiesScan(); break; }
            case TYPE::ENTITY::BAK_SLOT_ID:         {
                GetOwnerVehicle()->UpdatePropertiesSpeed();
                GetOwnerVehicle()->UpdatePropertiesJump();

                break;
            }

            case TYPE::ENTITY::DRIVE_SLOT_ID:       {
                GetOwnerVehicle()->UpdatePropertiesSpeed();
                GetOwnerVehicle()->UpdatePropertiesJump();
                break;
            }
                
            case TYPE::ENTITY::DROID_SLOT_ID:     { GetOwnerVehicle()->UpdatePropertiesRepair(); break; }
            case TYPE::ENTITY::ENERGIZER_SLOT_ID: { GetOwnerVehicle()->UpdatePropertiesEnergy(); break; }
            case TYPE::ENTITY::FREEZER_SLOT_ID:     { GetOwnerVehicle()->UpdatePropertiesFreeze(); break; }
            case TYPE::ENTITY::GRAPPLE_SLOT_ID:     { GetOwnerVehicle()->UpdatePropertiesGrab(); break; }
            case TYPE::ENTITY::PROTECTOR_SLOT_ID: { GetOwnerVehicle()->UpdatePropertiesProtection(); break; }
            case TYPE::ENTITY::RADAR_SLOT_ID:     { GetOwnerVehicle()->UpdatePropertiesRadar(); break; }

            case TYPE::ENTITY::ARTEFACT_SLOT_ID: { GetOwnerVehicle()->UpdateArtefactInfluence(); break; }
        }
    }
}

///* virtual */
//void ItemSlot::Render(const jeti::Renderer& render, const ceti::Box2D& box, const glm::vec2& gui_offset, bool draw_text) const
//{
//    render.DrawQuad(*textureOb, box);
//    RenderItem(render, box, gui_offset, draw_text);
//}

//void ItemSlot::RenderItem(const jeti::Renderer& render, const ceti::Box2D& box, const glm::vec2& gui_offset, bool draw_text) const
//{
//    if (m_Item) {
//        m_Item->Render(render, box, gui_offset, draw_text);
//    }
//}

//void ItemSlot::RenderMark(const jeti::Renderer& render, const ceti::Box2D& box, jeti::TextureOb* textureOb_mark) const
//{
//    render.DrawQuad(*textureOb_mark, box);
//}

//void ItemSlot::RenderTargetMark(const jeti::Renderer& render, const ceti::Box2D& box, jeti::TextureOb* textureOb_mask, jeti::TextureOb* textureOb) const
//{
//    render.DrawQuad(*textureOb, box);
//    render.DrawQuad(*textureOb_mask, box);
//}

int ItemSlot::itemRadius() const
{       
    switch(m_item->typeId())
    {
        case TYPE::ENTITY::EQUIPMENT_ID:
        {
            switch (m_item->subTypeId())
            {
                case TYPE::ENTITY::LAZER_EQUIPMENT_ID:   { return lazerEquipment()->GetRadius();  break; };
                case TYPE::ENTITY::ROCKET_EQUIPMENT_ID:  { return rocketEquipment()->GetRadius(); break; };

                case TYPE::ENTITY::GRAPPLE_EQUIPMENT_ID: { return grappleEquipment()->GetRadius(); break; };
                case TYPE::ENTITY::RADAR_EQUIPMENT_ID:   { return radarEquipment()->GetRadius();   break; };
            }
            
            break;
        }

        case TYPE::ENTITY::BOMB_ID:
        {
            return bomb()->radius();   break;
        }
    }
    
    return 0;
}

int ItemSlot::itemDamage() const
{       
    switch(m_item->typeId())
    {
        case TYPE::ENTITY::EQUIPMENT_ID:
        {
            switch (m_item->subTypeId())
            {
                case TYPE::ENTITY::LAZER_EQUIPMENT_ID:   { return lazerEquipment()->GetDamage();  break; };
                case TYPE::ENTITY::ROCKET_EQUIPMENT_ID:  { return rocketEquipment()->GetDamage(); break; };
            }
            
            break;
        }
            
        case TYPE::ENTITY::BOMB_ID:
        {
            return bomb()->damage();   break;
        }
    }
    
    return 0;
}

void ItemSlot::dropItemToSpace()
{
    //    jeti::TextureOb* textureOb_ = nullptr;

    //    switch (m_Item->typeId())
    //    {
    //        case TYPE::ENTITY::BOMB_ID: { textureOb_ = TextureCollector::Instance().getTextureByTypeId(TYPE::TEXTURE::BOMB_ID); break; }
    //        default:                      { textureOb_ = TextureCollector::Instance().getTextureByTypeId(TYPE::TEXTURE::CONTAINER_ID); break; }
    //    }

    //    Container* container = ContainerBuilder::Instance().GetNewContainer(textureOb_, m_Item);
    //    float impulse_strength = 0.5;
    //    glm::vec3 impulse_dir(meti::getRandXYVec3Unit());
    //    container->addImpulse(impulse_dir, impulse_strength);
    //    GetOwnerVehicle()->starsystem()->AddContainer(container, GetOwnerVehicle()->center());
    //    RemoveItem();
}

bool ItemSlot::swapItem(ItemSlot* slot)
{
    if ( (m_item == nullptr) and (slot->item() != nullptr) )
    {
        if (insertItem(slot->item()) == true)
        {
            return true;
        }
    }
    
    if ( (m_item != nullptr) and (slot->item() == nullptr) )
    {
        if (slot->insertItem(item()) == true)
        {
            return true;
        }
    }

    if ( (m_item != nullptr) and (slot->item() != nullptr) )
    {
        BaseItem* tmp_item = slot->item();
        if ( (slot->checkItemInsertion(m_item) == true) and (checkItemInsertion(tmp_item) == true) )
        {
            slot->insertItem(m_item);
            tmp_item->setItemSlot(nullptr);
            insertItem(tmp_item);

            return true;
        }

        if ( (m_item->typeId() == TYPE::ENTITY::MODULE_ID) and (slot->item()->typeId() == TYPE::ENTITY::EQUIPMENT_ID) )
        {
            if (((BaseEquipment*)slot->item())->InsertModule((BaseModule*)m_item) == true)
            {
                return true;
            }
        }
    }
    
    return false;
}

void ItemSlot::updateRange(jeti::TextureOb* _texOb)
{
    float radius = this->itemRadius();
    int size = 6;
    
    //    m_VisualPath.FillData(_texOb, radius, size);
}

void ItemSlot::drawRange(const glm::vec2& offset)
{ 
    //m_VisualPath.Draw(offset);
}

bool ItemSlot::checkSubTarget(ItemSlot* subtarget) const
{
#if WEAPONSTARGET_LOG_ENABLED == 1
    Logger::Instance().Log(" ItemSlot("+std::to_string(id())+")::CheckSubTarget", WEAPONSTARGET_LOG_DIP);
#endif
    
    if (subtarget->item() != nullptr)
    {
        return true;
    }
    
    return false;
}


STATUS ItemSlot::checkTarget(SpaceObject* target) const
{
#if WEAPONSTARGET_LOG_ENABLED == 1
    Logger::Instance().Log(" ItemSlot("+std::to_string(id())+")::CheckTarget", WEAPONSTARGET_LOG_DIP);
#endif
    
    if (isTargetAlive(target) == false)
    {
        return STATUS::TARGET_DEAD;
    }

    if (isTargetInSpace(target) == false)
    {
        return STATUS::TARGET_NOTIN_SPACE;
    }

    if (isTargetInSameStarSystem(target) == false)
    {
        return STATUS::TARGET_NOTIN_STARSYSTEM;
    }

    if (checkDistanceToTarget(target) == false)
    {
        return STATUS::TARGET_OUTOF_RANGE;
    }

    return STATUS::TARGET_OK;
}     

STATUS ItemSlot::checkTargetPure(SpaceObject* target) const
{
    Logger::Instance().Log(" ItemSlot("+std::to_string(id())+")::CheckTarget", WEAPONSTARGET_LOG_DIP);
    if (!isTargetAlive(target)) {
        return STATUS::TARGET_DEAD;
    }
    if (!isTargetInSpace(target)) {
        return STATUS::TARGET_NOTIN_SPACE;
    }
    if (!isTargetInSameStarSystem(target)) {
        return STATUS::TARGET_NOTIN_STARSYSTEM;
    }
    return STATUS::TARGET_OK;
} 

bool ItemSlot::isTargetAlive(SpaceObject* target) const
{
    return target->isAlive();
}

bool ItemSlot::isTargetInSpace(SpaceObject* target) const
{
    return (target->placeTypeId() == TYPE::PLACE::SPACE_ID);
}               

bool ItemSlot::isTargetInSameStarSystem(SpaceObject* target) const
{
    return (target->starsystem()->id() == GetOwnerVehicle()->starsystem()->id());
}                

bool ItemSlot::checkDistanceToTarget(SpaceObject* target) const
{
    if (target->typeId() == TYPE::ENTITY::STARSYSTEM_ID)
    {
        return true;
    }
    
    float dist = meti::distance(GetOwnerVehicle()->center(), target->center());
    if (dist < itemRadius())
    {
        return true;
    }

    return false;
}

/* virtual override final */
void ItemSlot::Save(boost::property_tree::ptree& save_ptree) const
{
    const std::string root = "item_slot." + std::to_string(id()) + ".";
    Base::SaveData(save_ptree, root);
    BaseSlot::SaveData(save_ptree, root);
    ItemSlot::SaveData(save_ptree, root);
}

/* virtual override final */      
void ItemSlot::Load(const boost::property_tree::ptree& load_ptree)
{
    Base::LoadData(load_ptree);
    BaseSlot::LoadData(load_ptree);
    ItemSlot::LoadData(load_ptree);
}

/* virtual override final */ 
void ItemSlot::Resolve()
{
    Base::ResolveData();
    BaseSlot::ResolveData();
    ItemSlot::ResolveData();
}

void ItemSlot::SaveData(boost::property_tree::ptree& save_ptree, const std::string& root) const
{
    Logger::Instance().Log(" ItemSlot("+std::to_string(id())+")::SaveData", SAVELOAD_LOG_DIP);

    if (m_target != nullptr)    { save_ptree.put(root+"unresolved_ItemSlot.target_id", m_target->id()); }
    else                        { save_ptree.put(root+"unresolved_ItemSlot.target_id", NONE_ID); }

    if (m_subtarget != nullptr) { save_ptree.put(root+"unresolved_ItemSlot.subtarget_id", m_subtarget->id()); }
    else                        { save_ptree.put(root+"unresolved_ItemSlot.subtarget_id", NONE_ID); }
}

void ItemSlot::LoadData(const boost::property_tree::ptree& load_ptree)
{
    Logger::Instance().Log(" ItemSlot("+std::to_string(id())+")::LoadData", SAVELOAD_LOG_DIP);
    
    m_unresolved_ItemSlot.target_id    = load_ptree.get<int>("unresolved_ItemSlot.target_id");
    m_unresolved_ItemSlot.subtarget_id = load_ptree.get<int>("unresolved_ItemSlot.subtarget_id");
}

void ItemSlot::ResolveData()
{
    Logger::Instance().Log(" ItemSlot("+std::to_string(id())+")::ResolveData", SAVELOAD_LOG_DIP);
    
    if (m_unresolved_ItemSlot.target_id != NONE_ID) {
        m_target = (SpaceObject*)global::get().entitiesManager().entity(m_unresolved_ItemSlot.target_id);
    }

    if (m_unresolved_ItemSlot.subtarget_id != NONE_ID) {
        m_subtarget = (ItemSlot*)global::get().entitiesManager().entity(m_unresolved_ItemSlot.subtarget_id);
    }

    switch(owner->typeId())
    {
        case TYPE::ENTITY::VEHICLE_ID:     {    ((Vehicle*)owner)->AddItemSlot(this); break; }
        case TYPE::ENTITY::CONTAINER_ID:         {    ((Container*)owner)->bindItemSlot(this); break; }
        case TYPE::ENTITY::STORE_ID:             {     ((Store*)owner)->AddItemSlot(this); break; }
        case TYPE::ENTITY::ANGAR_ID:             {     ((Angar*)owner)->AddItemSlot(this); break; }
            //case TYPE::ENTITY::NATURELAND_ID:      {     ((NatureLand*)owner)->AddItemSlot(this); break; }
    }
}

void ItemSlot::log(const std::string& func_name) const
{
    std::string str = "ItemSlot(id="+std::to_string(id())+")::"+func_name+" "+dataTypeString();
    
    if (owner != nullptr)       { str += " owner:" + owner->dataTypeString(); }
    if (m_item != nullptr)      { str += " item:" + m_item->dataTypeString();  }
    if (m_target != nullptr)    { str += " target:" + m_target->dataTypeString();  }
    if (m_subtarget != nullptr) { str += " subtarget:" + m_subtarget->dataTypeString(); }
    
    Logger::Instance().Log(str, WEAPONSTARGET_LOG_DIP);
}

