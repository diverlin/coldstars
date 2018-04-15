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

#include <core/builder/spaceobject/ContainerBuilder.hpp>

#include <core/model/spaceobject/Vehicle.hpp> // depr
#include <core/spaceobject/Vehicle.hpp>
#include <core/spaceobject/Container.hpp>
#include <core/pilot/Npc.hpp>

#include "../world/starsystem.hpp"

#include <core/item/equipment/Rocket.hpp>
#include <core/item/equipment/Lazer.hpp>
#include <core/item/equipment/Radar.hpp>
#include <core/item/equipment/Grapple.hpp>

#include <core/model/item/equipment/Rocket.hpp>
#include <core/model/item/equipment/Lazer.hpp>
#include <core/model/item/equipment/Radar.hpp>
#include <core/model/item/equipment/Grapple.hpp>

#include <core/item/other/Bomb.hpp>

#include "../dock/Store.hpp"
#include "../dock/Angar.hpp"

#include <ceti/Logger.hpp>
#include <meti/RandUtils.hpp>

#include <common/Global.hpp>
#include <core/manager/EntityManager.hpp>

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

//} // namespace core

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

//} // namespace core

namespace core {

ItemSlot::ItemSlot(const SlotType& type)
    :
      m_type(type)
{
    m_hitProbability = meti::rand::gen_int(100); // (tmp) move to builder
}

ItemSlot::~ItemSlot()
{}  

///* virtual */
//void putChildrenToGarbage() const
//{
//    assert(false);
////    if (m_item) {
////       manager::EntityManager::get().addToGarbage(m_item);
////    }
//}

bool ItemSlot::__checkItemInsertion(control::Item* item) const
{
    if (type() == SlotType::CARGO) {
        return true;
    }
    if (type() == item->descriptor()->slotType()) {
        return true;
    }
    
    return false;
}

bool ItemSlot::insert(control::Item* item)
{
    if ((type() == SlotType::CARGO) || (type() == item->descriptor()->slotType())) {
        m_item = item;
        if (item->slot()) {
            item->slot()->release();
        }
        item->setSlot(this);
        item->model()->setSlot(offset());

        if (type() == item->descriptor()->slotType()) {
            updateVehiclePropetries();
        }
        return true;
    }

    return false;
}

void ItemSlot::release()
{
    if (!m_item) {
        return;
    }

    if (type() == SlotType::WEAPON) {
        reset();
    }

    // make it oop
    m_item = nullptr;

    if (type() != SlotType::CARGO) {
        updateVehiclePropetries();
    }
}

void ItemSlot::selectEvent()
{
    setSelected(true);

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

    switch(type())
    {
    case SlotType::CARGO: { break; }
    case SlotType::WEAPON: { vehicleOwner()->_updatePropFire(); break; }
    case SlotType::ARTEFACT: { vehicleOwner()->_updateArtefactInfluence(); break; }
    case SlotType::SCANER:     { vehicleOwner()->_updatePropScan(); break; }
    case SlotType::BAK:         {
        vehicleOwner()->_updatePropSpeed();
        vehicleOwner()->_updatePropJump();

        break;
    }

    case SlotType::DRIVE:       {
        vehicleOwner()->_updatePropSpeed();
        vehicleOwner()->_updatePropJump();
        break;
    }

    case SlotType::DROID:     { vehicleOwner()->_updatePropRepair(); break; }
#ifdef USE_EXTRA_EQUIPMENT
    case SlotType::ENERGIZER: { vehicleOwner()->_updatePropEnergy(); break; }
    case SlotType::FREEZER:     { vehicleOwner()->_updatePropFreeze(); break; }
#endif // USE_EXTRA_EQUIPMENT
    case SlotType::GRAPPLE:     { vehicleOwner()->_updatePropGrab(); break; }
    case SlotType::PROTECTOR: { vehicleOwner()->_updatePropProtection(); break; }
    case SlotType::RADAR:     { vehicleOwner()->_updatePropRadar(); break; }

    default:
        assert(false);
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

control::Item*
ItemSlot::takeItem()
{
    control::Item* item = m_item;
    release();
    return item;
}

bool ItemSlot::swapItem(ItemSlot* slot)
{
    assert(slot);
    if (!m_item && slot->item()) {
        if (insert(slot->item())) {
            return true;
        }
    }
    
    if (m_item && !slot->item()) {
        if (slot->insert(item())) {
            return true;
        }
    }

    if (!m_item && slot->item()) {
        control::Item* tmp_item = slot->item();
        if (slot->__checkItemInsertion(m_item) && __checkItemInsertion(tmp_item)) {
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

//void drawRange(const glm::vec2& offset)
//{
//    m_VisualPath.Draw(offset);
//}

///* virtual override final */
//void Save(boost::property_tree::ptree& save_ptree) const
//{
////    const std::string root = "item_slot." + std::to_string(id()) + ".";
////    Base::SaveData(save_ptree, root);
////    BaseSlot::SaveData(save_ptree, root);
////    ItemSlot::SaveData(save_ptree, root);
//}

///* virtual override final */
//void Load(const boost::property_tree::ptree& load_ptree)
//{
////    Base::LoadData(load_ptree);
////    BaseSlot::LoadData(load_ptree);
////    ItemSlot::LoadData(load_ptree);
//}

///* virtual override final */
//void Resolve()
//{
////    Base::ResolveData();
////    BaseSlot::ResolveData();
////    ItemSlot::ResolveData();
//}

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
////        m_target = (SpaceObject*)manager::EntityManager::get().get(m_unresolved_ItemSlot.target_id);
////    }

////    if (m_unresolved_ItemSlot.subtarget_id != NONE) {
////        m_subtarget = (ItemSlot*)manager::EntityManager::get().get(m_unresolved_ItemSlot.subtarget_id);
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

} // namespace core
