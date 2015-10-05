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

ItemSlot::ItemSlot(INTLONGEST id, TYPE::ENTITY subtype_id)
    :
      m_Turrel(nullptr),
      m_Item(nullptr),
      m_Target(nullptr),
      m_Subtarget(nullptr),
      m_HitProbability(0)
{
    setId(id);
    setTypeId(TYPE::ENTITY::ITEM_SLOT_ID);
    setSubTypeId(subtype_id);
    
    m_HitProbability = meti::getRandInt(0, 100); // (tmp) move to builder
}

/* virtual */
ItemSlot::~ItemSlot()
{
    Logger::Instance().Log("___::~ItemSlot("+std::to_string(id())+")");
}  

/* virtual */  
void ItemSlot::putChildrenToGarbage() const
{
    if (m_Item) {
        global::get().entitiesManager().AddToGarbage(m_Item);
    }
}

void ItemSlot::SetTarget(SpaceObject* target, ItemSlot* subtarget)     
{
    m_Target    = target;
    m_Subtarget = subtarget;
}

STATUS ItemSlot::ValidateTarget()
{       
    if (m_Subtarget) {
        if (!CheckSubTarget(m_Subtarget)) {
            m_Subtarget = nullptr; // reseting only subtarget, firemode for target will be used
        }
    }
    
    STATUS status = CheckTarget(m_Target);    
    if (status != STATUS::OK) {
        Logger::Instance().Log(getTargetStatusStr(status), WEAPONSTARGET_LOG_DIP);
    }

    return status;
}

void ItemSlot::ResetTarget()
{ 
    m_Target    = nullptr;
    m_Subtarget = nullptr;
}

bool ItemSlot::CheckAmmo() const
{
    switch(GetItem()->subTypeId())
    {
        case TYPE::ENTITY::LAZER_EQUIPMENT_ID:  { /*if check energy */  return true; break; }
        case TYPE::ENTITY::ROCKET_EQUIPMENT_ID: { if (GetRocketEquipment()->GetAmmo() > 0) return true; break; }
    }
    
    return false;
}

void ItemSlot::FireEvent(float attack_rate, bool show_effect)
{
    switch(GetItem()->subTypeId())
    {
        case TYPE::ENTITY::LAZER_EQUIPMENT_ID:
        {
            GetLazerEquipment()->FireEvent(GetTarget(), GetSubTarget(), attack_rate, show_effect);
            break;
        }

        case TYPE::ENTITY::ROCKET_EQUIPMENT_ID:
        {
            GetRocketEquipment()->FireEvent(attack_rate);
            break;
        }
    }

    if (GetTarget()->isAlive() == false)
    {
        GetOwnerVehicle()->GetOwnerNpc()->AddExpirience(GetTarget()->givenExpirience(), show_effect);
    }
}

bool ItemSlot::CheckItemInsertion(BaseItem* item) const
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

bool ItemSlot::InsertItem(BaseItem* item)
{    
    if (subTypeId() == TYPE::ENTITY::GATE_SLOT_ID)
    {
        m_Item = item;
        DropItemToSpace();
        return true;
    }

    if (subTypeId() == TYPE::ENTITY::CARGO_SLOT_ID)
    {
        m_Item = item;
        if (item->itemSlot() != nullptr)
        {
            item->itemSlot()->RemoveItem();
        }
        item->setItemSlot(this);

        return true;
    }

    if (subTypeId() == item->parentSubTypeId())
    {
        m_Item = item;
        if (item->itemSlot() != nullptr)
        {
            item->itemSlot()->RemoveItem();
        }
        item->setItemSlot(this);
        UpdateVehiclePropetries();

        return true;
    }
    
    return false;
}

void ItemSlot::RemoveItem()
{    
    m_Item = nullptr;
    ResetTarget();

    if (subTypeId() != TYPE::ENTITY::CARGO_SLOT_ID)
    {
        UpdateVehiclePropetries();
    }
}

void ItemSlot::SelectEvent()
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

void ItemSlot::DeselectEvent()
{
    selected = false;
    
    if (owner->typeId() == TYPE::ENTITY::VEHICLE_ID)
    {
        switch(subTypeId())
        {
            case TYPE::ENTITY::WEAPON_SLOT_ID:     {     ResetTarget(); break; }
            case TYPE::ENTITY::DRIVE_SLOT_ID:
            {
                GetOwnerVehicle()->UpdatePropertiesSpeed();
                //GetOwnerVehicle()->UpdatePropertiesJump();
                break;
            }
        }
    }

}

void ItemSlot::UpdateVehiclePropetries() const
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

int ItemSlot::GetItemRadius() const
{       
    switch(m_Item->typeId())
    {
        case TYPE::ENTITY::EQUIPMENT_ID:
        {
            switch (m_Item->subTypeId())
            {
                case TYPE::ENTITY::LAZER_EQUIPMENT_ID:   { return GetLazerEquipment()->GetRadius();  break; };
                case TYPE::ENTITY::ROCKET_EQUIPMENT_ID:  { return GetRocketEquipment()->GetRadius(); break; };

                case TYPE::ENTITY::GRAPPLE_EQUIPMENT_ID: { return GetGrappleEquipment()->GetRadius(); break; };
                case TYPE::ENTITY::RADAR_EQUIPMENT_ID:   { return GetRadarEquipment()->GetRadius();   break; };
            }
            
            break;
        }

        case TYPE::ENTITY::BOMB_ID:
        {
            return GetBomb()->radius();   break;
        }
    }
    
    return 0;
}

int ItemSlot::GetItemDamage() const
{       
    switch(m_Item->typeId())
    {
        case TYPE::ENTITY::EQUIPMENT_ID:
        {
            switch (m_Item->subTypeId())
            {
                case TYPE::ENTITY::LAZER_EQUIPMENT_ID:   { return GetLazerEquipment()->GetDamage();  break; };
                case TYPE::ENTITY::ROCKET_EQUIPMENT_ID:  { return GetRocketEquipment()->GetDamage(); break; };
            }
            
            break;
        }
            
        case TYPE::ENTITY::BOMB_ID:
        {
            return GetBomb()->damage();   break;
        }
    }
    
    return 0;
}

void ItemSlot::DropItemToSpace()
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

bool ItemSlot::SwapItem(ItemSlot* slot)
{
    if ( (m_Item == nullptr) and (slot->GetItem() != nullptr) )
    {
        if (InsertItem(slot->GetItem()) == true)
        {
            return true;
        }
    }
    
    if ( (m_Item != nullptr) and (slot->GetItem() == nullptr) )
    {
        if (slot->InsertItem(GetItem()) == true)
        {
            return true;
        }
    }

    if ( (m_Item != nullptr) and (slot->GetItem() != nullptr) )
    {
        BaseItem* tmp_item = slot->GetItem();
        if ( (slot->CheckItemInsertion(m_Item) == true) and (CheckItemInsertion(tmp_item) == true) )
        {
            slot->InsertItem(m_Item);
            tmp_item->setItemSlot(nullptr);
            InsertItem(tmp_item);

            return true;
        }

        if ( (m_Item->typeId() == TYPE::ENTITY::MODULE_ID) and (slot->GetItem()->typeId() == TYPE::ENTITY::EQUIPMENT_ID) )
        {
            if (((BaseEquipment*)slot->GetItem())->InsertModule((BaseModule*)m_Item) == true)
            {
                return true;
            }
        }
    }
    
    return false;
}

void ItemSlot::UpdateRange(jeti::TextureOb* _texOb)
{
    float radius = this->GetItemRadius();
    int size = 6;
    
    //    m_VisualPath.FillData(_texOb, radius, size);
}

void ItemSlot::DrawRange(const glm::vec2& offset)
{ 
    //m_VisualPath.Draw(offset);
}

bool ItemSlot::CheckSubTarget(ItemSlot* subtarget) const
{
#if WEAPONSTARGET_LOG_ENABLED == 1
    Logger::Instance().Log(" ItemSlot("+std::to_string(id())+")::CheckSubTarget", WEAPONSTARGET_LOG_DIP);
#endif
    
    if (subtarget->GetItem() != nullptr)
    {
        return true;
    }
    
    return false;
}


STATUS ItemSlot::CheckTarget(SpaceObject* target) const
{
#if WEAPONSTARGET_LOG_ENABLED == 1
    Logger::Instance().Log(" ItemSlot("+std::to_string(id())+")::CheckTarget", WEAPONSTARGET_LOG_DIP);
#endif
    
    if (IsTargetAlive(target) == false)
    {
        return STATUS::TARGET_DEAD;
    }

    if (IsTargetInSpace(target) == false)
    {
        return STATUS::TARGET_NOTIN_SPACE;
    }

    if (IsTargetInSameStarSystem(target) == false)
    {
        return STATUS::TARGET_NOTIN_STARSYSTEM;
    }

    if (CheckDistanceToTarget(target) == false)
    {
        return STATUS::TARGET_OUTOF_RANGE;
    }

    return STATUS::TARGET_OK;
}     

STATUS ItemSlot::CheckTargetPure(SpaceObject* target) const
{
    Logger::Instance().Log(" ItemSlot("+std::to_string(id())+")::CheckTarget", WEAPONSTARGET_LOG_DIP);
    if (!IsTargetAlive(target)) {
        return STATUS::TARGET_DEAD;
    }
    if (!IsTargetInSpace(target)) {
        return STATUS::TARGET_NOTIN_SPACE;
    }
    if (!IsTargetInSameStarSystem(target)) {
        return STATUS::TARGET_NOTIN_STARSYSTEM;
    }
    return STATUS::TARGET_OK;
} 

bool ItemSlot::IsTargetAlive(SpaceObject* target) const
{
    return target->isAlive();
}

bool ItemSlot::IsTargetInSpace(SpaceObject* target) const  
{
    return (target->placeTypeId() == TYPE::PLACE::SPACE_ID);
}               

bool ItemSlot::IsTargetInSameStarSystem(SpaceObject* target) const
{
    return (target->starsystem()->id() == GetOwnerVehicle()->starsystem()->id());
}                

bool ItemSlot::CheckDistanceToTarget(SpaceObject* target) const
{
    if (target->typeId() == TYPE::ENTITY::STARSYSTEM_ID)
    {
        return true;
    }
    
    float dist = meti::distance(GetOwnerVehicle()->center(), target->center());
    if (dist < GetItemRadius())
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

    if (m_Target != nullptr)    { save_ptree.put(root+"unresolved_ItemSlot.target_id", m_Target->id()); }
    else                        { save_ptree.put(root+"unresolved_ItemSlot.target_id", NONE_ID); }

    if (m_Subtarget != nullptr) { save_ptree.put(root+"unresolved_ItemSlot.subtarget_id", m_Subtarget->id()); }
    else                        { save_ptree.put(root+"unresolved_ItemSlot.subtarget_id", NONE_ID); }
}

void ItemSlot::LoadData(const boost::property_tree::ptree& load_ptree)
{
    Logger::Instance().Log(" ItemSlot("+std::to_string(id())+")::LoadData", SAVELOAD_LOG_DIP);
    
    unresolved_ItemSlot.target_id    = load_ptree.get<int>("unresolved_ItemSlot.target_id");
    unresolved_ItemSlot.subtarget_id = load_ptree.get<int>("unresolved_ItemSlot.subtarget_id");
}

void ItemSlot::ResolveData()
{
    Logger::Instance().Log(" ItemSlot("+std::to_string(id())+")::ResolveData", SAVELOAD_LOG_DIP);
    
    if (unresolved_ItemSlot.target_id != NONE_ID) {
        m_Target = (SpaceObject*)global::get().entitiesManager().GetEntityById(unresolved_ItemSlot.target_id);
    }

    if (unresolved_ItemSlot.subtarget_id != NONE_ID) {
        m_Subtarget = (ItemSlot*)global::get().entitiesManager().GetEntityById(unresolved_ItemSlot.subtarget_id);
    }

    switch(owner->typeId())
    {
        case TYPE::ENTITY::VEHICLE_ID:     {    ((Vehicle*)owner)->AddItemSlot(this); break; }
        case TYPE::ENTITY::CONTAINER_ID:         {    ((Container*)owner)->BindItemSlot(this); break; }
        case TYPE::ENTITY::STORE_ID:             {     ((Store*)owner)->AddItemSlot(this); break; }
        case TYPE::ENTITY::ANGAR_ID:             {     ((Angar*)owner)->AddItemSlot(this); break; }
            //case TYPE::ENTITY::NATURELAND_ID:      {     ((NatureLand*)owner)->AddItemSlot(this); break; }
    }
}

void ItemSlot::Log(const std::string& func_name) const
{
    std::string str = "ItemSlot(id="+std::to_string(id())+")::"+func_name+" "+dataTypeString();
    
    if (owner != nullptr)       { str += " owner:" + owner->dataTypeString(); }
    if (m_Item != nullptr)      { str += " item:" + m_Item->dataTypeString();  }
    if (m_Target != nullptr)    { str += " target:" + m_Target->dataTypeString();  }
    if (m_Subtarget != nullptr) { str += " subtarget:" + m_Subtarget->dataTypeString(); }
    
    Logger::Instance().Log(str, WEAPONSTARGET_LOG_DIP);
}

