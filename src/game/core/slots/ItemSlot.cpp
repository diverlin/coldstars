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

#include <item/equipment/Rocket.hpp>
#include <item/equipment/Lazer.hpp>
#include <item/equipment/Radar.hpp>
#include <item/equipment/Grapple.hpp>

#include <item/others/Bomb.hpp>

#include "../dock/Store.hpp"
#include "../dock/Angar.hpp"

#include <ceti/Logger.hpp>
#include <meti/RandUtils.hpp>

#include <common/Global.hpp>
#include <managers/EntityManager.hpp>

ItemSlot::ItemSlot(const id_type& id, type::entity subtype_id)
    :
      m_turrel(nullptr),
      m_item(nullptr),
      m_target(nullptr),
      m_subtarget(nullptr),
      m_hitProbability(0)
{
    setId(id);
    setTypeId(type::entity::ITEM_SLOT_ID);
    setSubTypeId(subtype_id);
    
    m_hitProbability = meti::getRandInt(0, 100); // (tmp) move to builder
}

/* virtual */
ItemSlot::~ItemSlot()
{
    LOG("___::~ItemSlot("+std::to_string(id())+")");
}  

/* virtual */  
void ItemSlot::putChildrenToGarbage() const
{
    if (m_item) {
        global::get().entityManager().addToGarbage(m_item);
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
        LOG(getTargetStatusStr(status));
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
    switch(item()->subtype()) {
        case type::entity::LAZER_EQUIPMENT_ID:  { /*if check energy */  return true; break; }
        case type::entity::ROCKET_EQUIPMENT_ID: { if (rocketEquipment()->GetAmmo() > 0) return true; break; }
    }
    
    return false;
}

void ItemSlot::fireEvent(float attack_rate, bool show_effect)
{
    switch(item()->subtype())
    {
        case type::entity::LAZER_EQUIPMENT_ID: {
            lazerEquipment()->FireEvent(target(), subtarget(), attack_rate, show_effect);
            break;
        }

        case type::entity::ROCKET_EQUIPMENT_ID: {
            rocketEquipment()->FireEvent(attack_rate);
            break;
        }
    }

    if (target()->isAlive() == false) {
        vehicleOwner()->npc()->AddExpirience(target()->givenExpirience(), show_effect);
    }
}

bool ItemSlot::checkItemInsertion(item::Base* item) const
{
    if (subtype() == type::entity::CARGO_SLOT_ID) {
        return true;
    }

    if (subtype() == item->parentSubTypeId()) {
        return true;
    }
    
    return false;
}

bool ItemSlot::insertItem(item::Base* item)
{    
    // make it oop
    if (subtype() == type::entity::GATE_SLOT_ID)
    {
        // make a gate not be a slot
        //m_item = item;
        //dropItemToSpace();
        return false;
    }

    if (subtype() == type::entity::CARGO_SLOT_ID)
    {
        m_item = item;
        if (item->itemSlot() != nullptr)
        {
            item->itemSlot()->removeItem();
        }
        item->setItemSlot(this);

        return true;
    }

    if (subtype() == item->parentSubTypeId())
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
    // make it oop
    m_item = nullptr;
    resetTarget();

    if (subtype() != type::entity::CARGO_SLOT_ID) {
        updateVehiclePropetries();
    }
}

void ItemSlot::selectEvent()
{
    // make it oop
    m_selected = true;

    if (owner()->type() == type::entity::VEHICLE_ID) {
        switch(subtype()) {
            case type::entity::DRIVE_SLOT_ID: { vehicleOwner()->_updatePropSpeed(); break; }
        }
    }
}

void ItemSlot::deselectEvent()
{
    // make it oop
    m_selected = false;
    
    if (owner()->type() == type::entity::VEHICLE_ID)
    {
        switch(subtype())
        {
            case type::entity::WEAPON_SLOT_ID:     {     resetTarget(); break; }
            case type::entity::DRIVE_SLOT_ID:
            {
                vehicleOwner()->_updatePropSpeed();
                //GetOwnerVehicle()->UpdatePropertiesJump();
                break;
            }
        }
    }

}

void ItemSlot::updateVehiclePropetries() const
{
    // make it oop
    if (subtype() != type::entity::CARGO_SLOT_ID)
    {
        switch(subtype())
        {
            case type::entity::WEAPON_SLOT_ID:     { vehicleOwner()->_updatePropFire(); break; }
            case type::entity::SCANER_SLOT_ID:     { vehicleOwner()->_updatePropScan(); break; }
            case type::entity::BAK_SLOT_ID:         {
                vehicleOwner()->_updatePropSpeed();
                vehicleOwner()->_updatePropJump();

                break;
            }

            case type::entity::DRIVE_SLOT_ID:       {
                vehicleOwner()->_updatePropSpeed();
                vehicleOwner()->_updatePropJump();
                break;
            }
                
            case type::entity::DROID_SLOT_ID:     { vehicleOwner()->_updatePropRepair(); break; }
            case type::entity::ENERGIZER_SLOT_ID: { vehicleOwner()->_updatePropEnergy(); break; }
            case type::entity::FREEZER_SLOT_ID:     { vehicleOwner()->_updatePropFreeze(); break; }
            case type::entity::GRAPPLE_SLOT_ID:     { vehicleOwner()->_updatePropGrab(); break; }
            case type::entity::PROTECTOR_SLOT_ID: { vehicleOwner()->_updatePropProtection(); break; }
            case type::entity::RADAR_SLOT_ID:     { vehicleOwner()->_updatePropRadar(); break; }

            case type::entity::ARTEFACT_SLOT_ID: { vehicleOwner()->_updateArtefactInfluence(); break; }
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
//    switch(m_item->typeId())
//    {
//        case TYPE::ENTITY::EQUIPMENT_ID:
//        {
//            switch (m_item->subTypeId())
//            {
//                case TYPE::ENTITY::LAZER_EQUIPMENT_ID:   { return lazerEquipment()->radius();  break; };
//                case TYPE::ENTITY::ROCKET_EQUIPMENT_ID:  { return rocketEquipment()->radius(); break; };

//                case TYPE::ENTITY::GRAPPLE_EQUIPMENT_ID: { return grappleEquipment()->radius(); break; };
//                case TYPE::ENTITY::RADAR_EQUIPMENT_ID:   { return radarEquipment()->radius();   break; };
//            }
            
//            break;
//        }

//        case TYPE::ENTITY::BOMB_ID:
//        {
//            return bomb()->radius();   break;
//        }
//    }
    
    if (item()) {
        return item()->radius();
    }
    return 0;
}

int ItemSlot::itemDamage() const
{       
//    switch(m_item->typeId())
//    {
//        case TYPE::ENTITY::EQUIPMENT_ID:
//        {
//            switch (m_item->subTypeId())
//            {
//                case TYPE::ENTITY::LAZER_EQUIPMENT_ID:   { return lazerEquipment()->damage();  break; };
//                case TYPE::ENTITY::ROCKET_EQUIPMENT_ID:  { return rocketEquipment()->damage(); break; };
//            }
            
//            break;
//        }
            
//        case TYPE::ENTITY::BOMB_ID:
//        {
//            return bomb()->damage();   break;
//        }
//    }
    
    if (item()) {
        return item()->damage();
    }
    return 0;
}

item::Base*
ItemSlot::takeItem()
{
    item::Base* item = m_item;
    removeItem();
    return item;
}

bool ItemSlot::swapItem(ItemSlot* slot)
{
    assert(slot);
    if ( (m_item == nullptr) && (slot->item() != nullptr) ) {
        if (insertItem(slot->item()) == true) {
            return true;
        }
    }
    
    if ( (m_item != nullptr) && (slot->item() == nullptr) ) {
        if (slot->insertItem(item()) == true) {
            return true;
        }
    }

    if ( (m_item != nullptr) && (slot->item() != nullptr) ) {
        item::Base* tmp_item = slot->item();
        if ( (slot->checkItemInsertion(m_item) == true) && (checkItemInsertion(tmp_item) == true) ) {
            slot->insertItem(m_item);
            tmp_item->setItemSlot(nullptr);
            insertItem(tmp_item);

            return true;
        }

#ifdef USE_MODULES
        if ( (m_item->typeId() == TYPE::ENTITY::MODULE_ID) && (slot->item()->typeId() == TYPE::ENTITY::EQUIPMENT_ID) ) {
            if (((BaseEquipment*)slot->item())->InsertModule((BaseModule*)m_item) == true) {
                return true;
            }
        }
#endif
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
    LOG(" ItemSlot("+std::to_string(id())+")::CheckSubTarget");
#endif
    
    if (subtarget->item()) {
        return true;
    }
    
    return false;
}


STATUS ItemSlot::checkTarget(SpaceObject* target) const
{
#if WEAPONSTARGET_LOG_ENABLED == 1
    LOG(" ItemSlot("+std::to_string(id())+")::CheckTarget");
#endif
    
    if (isTargetAlive(target) == false) {
        return STATUS::TARGET_DEAD;
    }
    if (isTargetInSpace(target) == false) {
        return STATUS::TARGET_NOTIN_SPACE;
    }
    if (isTargetInSameStarSystem(target) == false) {
        return STATUS::TARGET_NOTIN_STARSYSTEM;
    }
    if (checkDistanceToTarget(target) == false) {
        return STATUS::TARGET_OUTOF_RANGE;
    }
    return STATUS::TARGET_OK;
}     

STATUS ItemSlot::checkTargetPure(SpaceObject* target) const
{
    LOG(" ItemSlot("+std::to_string(id())+")::CheckTarget");
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
    return (target->placeTypeId() == type::place::KOSMOS);
}               

bool ItemSlot::isTargetInSameStarSystem(SpaceObject* target) const
{
    return (target->starsystem()->id() == vehicleOwner()->starsystem()->id());
}                

bool ItemSlot::checkDistanceToTarget(SpaceObject* target) const
{
    if (target->type() == type::entity::STARSYSTEM_ID)
    {
        return true;
    }
    
    float dist = meti::distance(vehicleOwner()->position(), target->position());
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
    LOG(" ItemSlot("+std::to_string(id())+")::SaveData");

    if (m_target != nullptr)    { save_ptree.put(root+"unresolved_ItemSlot.target_id", m_target->id()); }
    else                        { save_ptree.put(root+"unresolved_ItemSlot.target_id", NONE_ID); }

    if (m_subtarget != nullptr) { save_ptree.put(root+"unresolved_ItemSlot.subtarget_id", m_subtarget->id()); }
    else                        { save_ptree.put(root+"unresolved_ItemSlot.subtarget_id", NONE_ID); }
}

void ItemSlot::LoadData(const boost::property_tree::ptree& load_ptree)
{
    LOG(" ItemSlot("+std::to_string(id())+")::LoadData");
    
    m_unresolved_ItemSlot.target_id    = load_ptree.get<int>("unresolved_ItemSlot.target_id");
    m_unresolved_ItemSlot.subtarget_id = load_ptree.get<int>("unresolved_ItemSlot.subtarget_id");
}

void ItemSlot::ResolveData()
{
    LOG(" ItemSlot("+std::to_string(id())+")::ResolveData");
    
//    if (m_unresolved_ItemSlot.target_id != NONE_ID) {
//        m_target = (SpaceObject*)global::get().entityManager().get(m_unresolved_ItemSlot.target_id);
//    }

//    if (m_unresolved_ItemSlot.subtarget_id != NONE_ID) {
//        m_subtarget = (ItemSlot*)global::get().entityManager().get(m_unresolved_ItemSlot.subtarget_id);
//    }

//    switch(owner->typeId())
//    {
//        case TYPE::ENTITY::VEHICLE_ID:     {    ((Vehicle*)owner)->AddItemSlot(this); break; }
//        case TYPE::ENTITY::CONTAINER_ID:         {    ((Container*)owner)->bindItemSlot(this); break; }
//        case TYPE::ENTITY::STORE_ID:             {     ((Store*)owner)->AddItemSlot(this); break; }
//        case TYPE::ENTITY::ANGAR_ID:             {     ((Angar*)owner)->AddItemSlot(this); break; }
//            //case TYPE::ENTITY::NATURELAND_ID:      {     ((NatureLand*)owner)->AddItemSlot(this); break; }
//    }
}

void ItemSlot::log(const std::string& func_name) const
{
    std::string str = "ItemSlot(id="+std::to_string(id())+")::"+func_name+" "+dataTypeStr();
    
    if (owner() != nullptr)     { str += " owner:" + owner()->dataTypeStr(); }
    if (m_item != nullptr)      { str += " item:" + m_item->dataTypeStr();  }
    if (m_target != nullptr)    { str += " target:" + m_target->dataTypeStr();  }
    if (m_subtarget != nullptr) { str += " subtarget:" + m_subtarget->dataTypeStr(); }
    
    LOG(str);
}

