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

#include <descriptor/item/Item.hpp>

#include "../builder/spaceobjects/ContainerBuilder.hpp"

#include <core/spaceobject/Vehicle.hpp>
#include <core/spaceobject/Container.hpp>
#include "../pilots/Npc.hpp"

#include "../world/starsystem.hpp"
#include "../parts/Turrel.hpp"

#include <core/item/equipment/Rocket.hpp>
#include <core/item/equipment/Lazer.hpp>
#include <core/item/equipment/Radar.hpp>
#include <core/item/equipment/Grapple.hpp>

#include <core/model/item/equipment/Rocket.hpp>
#include <core/model/item/equipment/Lazer.hpp>
#include <core/model/item/equipment/Radar.hpp>
#include <core/model/item/equipment/Grapple.hpp>

#include <item/others/Bomb.hpp>

#include "../dock/Store.hpp"
#include "../dock/Angar.hpp"

#include <ceti/Logger.hpp>
#include <meti/RandUtils.hpp>

#include <common/Global.hpp>
#include <managers/EntityManager.hpp>

//namespace descriptor {


//ItemSlot::ItemSlot(const std::string& data)
//{
//    MACRO_READ_SERIALIZED_DATA
//}

//std::string
//ItemSlot::data() const
//{
//    MACRO_SAVE_SERIALIZED_DATA
//}

//} // namespace descriptor

//namespace model {

//ItemSlot::ItemSlot(const std::string& data)
//{
//    MACRO_READ_SERIALIZED_DATA
//}

//std::string
//ItemSlot::data() const
//{
//    MACRO_SAVE_SERIALIZED_DATA
//}

//} // namespace model


namespace control {

ItemSlot::ItemSlot(entity::Type subtype)
    :
      m_turrel(nullptr),
      m_item(nullptr),
      m_target(nullptr),
      m_subtarget(nullptr),
      m_hitProbability(0)
{
    setType(entity::Type::ITEM_SLOT);
    setSubType(subtype);
    
    m_hitProbability = meti::getRandInt(100); // (tmp) move to builder
}

/* virtual */
ItemSlot::~ItemSlot()
{
//    LOG("___::~ItemSlot("+std::to_string(id())+")");
}  

/* virtual */  
void ItemSlot::putChildrenToGarbage() const
{
    assert(false);
//    if (m_item) {
//       core::global::get().entityManager().addToGarbage(m_item);
//    }
}

void ItemSlot::setTarget(model::SpaceObject* target, ItemSlot* subtarget)
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
    assert(false);
//    switch(item()->subtype()) {
//        case entity::Type::LAZER_EQUIPMENT:  { /*if check energy */  return true; break; }
//        case entity::Type::ROCKET_EQUIPMENT: { if (rocketEquipment()->GetAmmo() > 0) return true; break; }
//    }
    
    return false;
}

void ItemSlot::fireEvent(float attack_rate, bool show_effect)
{
    assert(false);
//    switch(item()->subtype())
//    {
//        case entity::Type::LAZER_EQUIPMENT: {
//            lazerEquipment()->FireEvent(target(), subtarget(), attack_rate, show_effect);
//            break;
//        }

//        case entity::Type::ROCKET_EQUIPMENT: {
//            rocketEquipment()->FireEvent(attack_rate);
//            break;
//        }
//    }

//    if (target()->isAlive() == false) {
//        vehicleOwner()->npc()->addExpirience(target()->givenExpirience(), show_effect);
//    }
}

bool ItemSlot::checkItemInsertion(control::Item* item) const
{
    assert(false);
//    if (subtype() == entity::Type::CARGO_SLOT) {
//        return true;
//    }

//    if (subtype() == item->parentSubtype()) {
//        return true;
//    }
    
    return false;
}

bool ItemSlot::insert(Item* item)
{
//    // make it oop
//    if (subtype() == entity::Type::GATE_SLOT)
//    {
//        // make a gate not be a slot
//        //m_item = item;
//        //dropItemToSpace();
//        return false;
//    }

    if ((subtype() == entity::Type::CARGO_SLOT) || (subtype() == item->descriptor()->slotType())) {
        m_item = item;
        if (item->slot()) {
            item->slot()->removeItem();
        }
        item->setSlot(this);
        item->model()->setSlot(offset());

        if (subtype() == item->descriptor()->slotType()) {
            updateVehiclePropetries();
        }
        return true;
    }

    return false;
}

void ItemSlot::removeItem()
{    
    // make it oop
    m_item = nullptr;
    resetTarget();

    assert(false);
//    if (subtype() != entity::Type::CARGO_SLOT) {
//        updateVehiclePropetries();
//    }
}

void ItemSlot::selectEvent()
{
    // make it oop
    setSelected(true);

    assert(false);
//    if (owner()->type() == entity::Type::VEHICLE) {
//        switch(subtype()) {
//            case entity::Type::DRIVE_SLOT: { vehicleOwner()->_updatePropSpeed(); break; }
//        }
//    }
}

void ItemSlot::deselectEvent()
{
    // make it oop
    setSelected(false);

    assert(false);
//    if (owner()->type() == entity::Type::VEHICLE)
//    {
//        switch(subtype())
//        {
//            case entity::Type::WEAPON_SLOT:     {     resetTarget(); break; }
//            case entity::Type::DRIVE_SLOT:
//            {
//                assert(false);
////                vehicleOwner()->_updatePropSpeed();
//                //GetOwnerVehicle()->UpdatePropertiesJump();
//                break;
//            }
//        }
//    }

}

void ItemSlot::updateVehiclePropetries() const
{
    // TODO: make it oop
    assert(vehicleOwner());

    if (subtype() == entity::Type::CARGO_SLOT) {
        return;
    }

    switch(subtype())
    {
    case entity::Type::WEAPON_SLOT:     { vehicleOwner()->_updatePropFire(); break; }
    case entity::Type::SCANER_SLOT:     { vehicleOwner()->_updatePropScan(); break; }
    case entity::Type::BAK_SLOT:         {
        vehicleOwner()->_updatePropSpeed();
        vehicleOwner()->_updatePropJump();

        break;
    }

    case entity::Type::DRIVE_SLOT:       {
        vehicleOwner()->_updatePropSpeed();
        vehicleOwner()->_updatePropJump();
        break;
    }

    case entity::Type::DROID_SLOT:     { vehicleOwner()->_updatePropRepair(); break; }
#ifdef USE_EXTRA_EQUIPMENT
    case entity::type::ENERGIZER_SLOT: { vehicleOwner()->_updatePropEnergy(); break; }
    case entity::type::FREEZER_SLOT:     { vehicleOwner()->_updatePropFreeze(); break; }
#endif // USE_EXTRA_EQUIPMENT
    case entity::Type::GRAPPLE_SLOT:     { vehicleOwner()->_updatePropGrab(); break; }
    case entity::Type::PROTECTOR_SLOT: { vehicleOwner()->_updatePropProtection(); break; }
    case entity::Type::RADAR_SLOT:     { vehicleOwner()->_updatePropRadar(); break; }

    case entity::Type::ARTEFACT_SLOT: { vehicleOwner()->_updateArtefactInfluence(); break; }
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

//void ItemSlot::RenderMark(const jeti::Renderer& render, const ceti::Box2D& box, jeti::control::TextureOb* textureOb_mark) const
//{
//    render.DrawQuad(*textureOb_mark, box);
//}

//void ItemSlot::RenderTargetMark(const jeti::Renderer& render, const ceti::Box2D& box, jeti::control::TextureOb* textureOb_mask, jeti::control::TextureOb* textureOb) const
//{
//    render.DrawQuad(*textureOb, box);
//    render.DrawQuad(*textureOb_mask, box);
//}

int ItemSlot::itemRadius() const
{       
    switch(m_item->descriptor()->obType())
    {
        case entity::Type::EQUIPMENT:
        {
            switch (m_item->descriptor()->obSubType())
            {
                case entity::Type::LAZER_EQUIPMENT:   { return lazerEquipment()->model()->radius();  break; };
                case entity::Type::ROCKET_EQUIPMENT:  { return rocketEquipment()->model()->radius(); break; };

                case entity::Type::GRAPPLE_EQUIPMENT: { return grappleEquipment()->model()->radius(); break; };
                case entity::Type::RADAR_EQUIPMENT:   { return radarEquipment()->model()->radius();   break; };
            }
            
            break;
        }

        case entity::Type::BOMB:
        {
            assert(false);
            //return bomb()->radius();   break;
        }
    }

    assert(false);
//    if (item()) {
//        return item()->radius();
//    }
    return 0;
}

int ItemSlot::itemDamage() const
{       
    switch(m_item->descriptor()->obType())
    {
        case entity::Type::EQUIPMENT:
        {
            switch (m_item->descriptor()->obSubType())
            {
                case entity::Type::LAZER_EQUIPMENT:   { return lazerEquipment()->model()->damage();  break; };
                case entity::Type::ROCKET_EQUIPMENT:  { return rocketEquipment()->model()->damage(); break; };
            }
            
            break;
        }
            
        case entity::Type::BOMB:
        {
            assert(false);
            //return bomb()->damage();   break;
        }
    }

assert(false);
//    if (item()) {
//        return item()->damage();
//    }
    return 0;
}

Item*
ItemSlot::takeItem()
{
    Item* item = m_item;
    removeItem();
    return item;
}

bool ItemSlot::swapItem(ItemSlot* slot)
{
    assert(slot);
    if ( (m_item == nullptr) && (slot->item() != nullptr) ) {
        if (insert(slot->item()) == true) {
            return true;
        }
    }
    
    if ( (m_item != nullptr) && (slot->item() == nullptr) ) {
        if (slot->insert(item()) == true) {
            return true;
        }
    }

    if ( (m_item != nullptr) && (slot->item() != nullptr) ) {
        Item* tmp_item = slot->item();
        if ( (slot->checkItemInsertion(m_item) == true) && (checkItemInsertion(tmp_item) == true) ) {
            slot->insert(m_item);
            tmp_item->setSlot(nullptr);
            insert(tmp_item);

            return true;
        }

#ifdef USE_MODULES
        if ( (m_item->typeId() == entity::Type::MODULE) && (slot->item()->typeId() == entity::Type::EQUIPMENT) ) {
            if (((Equipment*)slot->item())->InsertModule((BaseModule*)m_item) == true) {
                return true;
            }
        }
#endif
    }
    
    return false;
}

//void ItemSlot::updateRange(jeti::control::Material* _texOb)
//{
//    float radius = this->itemRadius();
//    int size = 6;
    
//    //    m_VisualPath.FillData(_texOb, radius, size);
//}

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


STATUS ItemSlot::checkTarget(model::SpaceObject* target) const
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

STATUS ItemSlot::checkTargetPure(model::SpaceObject* target) const
{
    assert(false);
//    LOG(" ItemSlot("+std::to_string(id())+")::CheckTarget");

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

bool ItemSlot::isTargetAlive(model::SpaceObject* target) const
{
    return target->isAlive();
}

bool ItemSlot::isTargetInSpace(model::SpaceObject* target) const
{
    return (target->place() == place::type::KOSMOS);
}               

bool ItemSlot::isTargetInSameStarSystem(model::SpaceObject* target) const
{
    assert(false);
    //return (target->starsystem()->id() == vehicleOwner()->starsystem()->id());
}                

bool ItemSlot::checkDistanceToTarget(model::SpaceObject* target) const
{
    assert(false);
//    if (target->type() == entity::type::STARSYSTEM) {
//        return true;
//    }
    
//    float dist = meti::distance(vehicleOwner()->position(), target->position());
//    if (dist < itemRadius())
//    {
//        return true;
//    }

    return false;
}

/* virtual override final */
void ItemSlot::Save(boost::property_tree::ptree& save_ptree) const
{
//    const std::string root = "item_slot." + std::to_string(id()) + ".";
//    Base::SaveData(save_ptree, root);
//    BaseSlot::SaveData(save_ptree, root);
//    ItemSlot::SaveData(save_ptree, root);
}

/* virtual override final */      
void ItemSlot::Load(const boost::property_tree::ptree& load_ptree)
{
//    Base::LoadData(load_ptree);
//    BaseSlot::LoadData(load_ptree);
//    ItemSlot::LoadData(load_ptree);
}

/* virtual override final */ 
void ItemSlot::Resolve()
{
//    Base::ResolveData();
//    BaseSlot::ResolveData();
//    ItemSlot::ResolveData();
}

//void ItemSlot::SaveData(boost::property_tree::ptree& save_ptree, const std::string& root) const
//{
////    LOG(" ItemSlot("+std::to_string(id())+")::SaveData");

////    if (m_target != nullptr)    { save_ptree.put(root+"unresolved_ItemSlot.target_id", m_target->id()); }
////    else                        { save_ptree.put(root+"unresolved_ItemSlot.target_id", NONE); }

////    if (m_subtarget != nullptr) { save_ptree.put(root+"unresolved_ItemSlot.subtarget_id", m_subtarget->id()); }
////    else                        { save_ptree.put(root+"unresolved_ItemSlot.subtarget_id", NONE); }
//}

//void ItemSlot::LoadData(const boost::property_tree::ptree& load_ptree)
//{
////    LOG(" ItemSlot("+std::to_string(id())+")::LoadData");
    
////    m_unresolved_ItemSlot.target_id    = load_ptree.get<int>("unresolved_ItemSlot.target_id");
////    m_unresolved_ItemSlot.subtarget_id = load_ptree.get<int>("unresolved_ItemSlot.subtarget_id");
//}

//void ItemSlot::ResolveData()
//{
////    LOG(" ItemSlot("+std::to_string(id())+")::ResolveData");
    
////    if (m_unresolved_ItemSlot.target_id != NONE) {
////        m_target = (SpaceObject*)core::global::get().entityManager().get(m_unresolved_ItemSlot.target_id);
////    }

////    if (m_unresolved_ItemSlot.subtarget_id != NONE) {
////        m_subtarget = (ItemSlot*)core::global::get().entityManager().get(m_unresolved_ItemSlot.subtarget_id);
////    }

////    switch(owner->typeId())
////    {
////        case entity::Type::VEHICLE:     {    ((Vehicle*)owner)->AddItemSlot(this); break; }
////        case entity::Type::CONTAINER:         {    ((Container*)owner)->bindItemSlot(this); break; }
////        case entity::Type::STORE:             {     ((Store*)owner)->AddItemSlot(this); break; }
////        case entity::Type::ANGAR:             {     ((Angar*)owner)->AddItemSlot(this); break; }
////            //case entity::Type::NATURELAND:      {     ((NatureLand*)owner)->AddItemSlot(this); break; }
////    }
//}

void ItemSlot::log(const std::string& func_name) const
{
//    std::string str = "ItemSlot(id="+std::to_string(id())+")::"+func_name+" "+dataTypeStr();
    
//    if (owner() != nullptr)     { str += " owner:" + owner()->dataTypeStr(); }
//    if (m_item != nullptr)      { str += " item:" + m_item->dataTypeStr();  }
//    if (m_target != nullptr)    { str += " target:" + m_target->dataTypeStr();  }
//    if (m_subtarget != nullptr) { str += " subtarget:" + m_subtarget->dataTypeStr(); }
    
//    LOG(str);
}

} // naespace control
