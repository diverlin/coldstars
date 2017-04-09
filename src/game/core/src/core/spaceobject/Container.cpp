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

#include "Container.hpp"

#include <common/common.hpp>
#include <common/constants.hpp>
//#include <ceti/StringUtils.hpp>
#include <ceti/Logger.hpp>

#include <common/Global.hpp>
#include <core/model/spaceobject/Container.hpp>
#include <core/manager/EntityManager.hpp>
#include <core/manager/Garbage.hpp>

#include <world/starsystem.hpp>

//#include <jeti/Render.hpp>

//#include <jeti/particlesystem/ExplosionEffect.hpp>

#include <core/slot/ItemSlot.hpp>
#include <core/item/Item.hpp>
#include <core/item/equipment/ALL>

#include <core/manager/DescriptorManager.hpp>

namespace control {
namespace {

bool itemInsertHelper(slot::Item* slot, int_t id) {
    control::Base* model_base = manager::EntityManager::get().base(id);
    descriptor::Base* descriptor_base = descriptor::Manager::get().get(model_base->descriptor()->id());
    assert(descriptor_base->obType() == entity::Type::EQUIPMENT);
    switch(descriptor_base->obSubType()) {
    case entity::Type::SCANER_EQUIPMENT: {
        item::Scaner* item = manager::EntityManager::get().scaner(id);
        return slot->insert(item);
    }
    case entity::Type::DRIVE_EQUIPMENT: {
        item::Drive* item = manager::EntityManager::get().drive(id);
        return slot->insert(item);
    }
    case entity::Type::BAK_EQUIPMENT: {
        item::Bak* item = manager::EntityManager::get().bak(id);
        return slot->insert(item);
    }
    case entity::Type::DROID_EQUIPMENT: {
        item::Droid* item = manager::EntityManager::get().droid(id);
        return slot->insert(item);
    }
    case entity::Type::GRAPPLE_EQUIPMENT: {
        item::Grapple* item = manager::EntityManager::get().grapple(id);
        return slot->insert(item);
    }
    case entity::Type::LAZER_EQUIPMENT: {
        item::Lazer* item = manager::EntityManager::get().lazer(id);
        return slot->insert(item);
    }
    case entity::Type::PROTECTOR_EQUIPMENT: {
        item::Protector* item = manager::EntityManager::get().protector(id);
        return slot->insert(item);
    }
    case entity::Type::RADAR_EQUIPMENT: {
        item::Radar* item = manager::EntityManager::get().radar(id);
        return slot->insert(item);
    }
    case entity::Type::ROCKET_EQUIPMENT: {
        item::Rocket* item = manager::EntityManager::get().rocket(id);
        return slot->insert(item);
    }
    }
}
} // namespace

Container::Container(descriptor::Container* descr, model::Container* model)
    :
      SpaceObject(descr, model)
    , m_descriptor_container(descr)
    , m_model_container(model)
{

    slot::Item* slot = new slot::Item(entity::Type::CARGO_SLOT);
    bindItemSlot(slot);

    if (m_model_container->item() != NONE) {
        itemInsertHelper(slot, m_model_container->item());
    }
}

/* virtual */   
Container::~Container()
{
    LOG("___::~Container("+std::to_string(model()->id())+")");
}

Item*
Container::item() const
{
    return m_itemSlot->item();
}

void Container::__putChildrenToGarbage() const
{
    if (auto item = m_itemSlot->item()) {
        manager::Garbage::get().add(item);
    }
}

bool
Container::insert(Item* item)
{
    return m_itemSlot->insert(item);
}

/* override final */
void Container::hit(int damage, SpaceObject* agressor) {
    SpaceObject::hit(damage);
    assert(false);
//    if (model()->dataLife().is_dying) {
//        if (m_itemSlot->item()) {
//            if (m_itemSlot->item()->subtype() == entity::Type::BOMB) {
//                // send explosion event
//            }
//        }
//    }
}
            
void Container::bindItemSlot(slot::Item* item_slot)
{
    m_itemSlot = item_slot;
    m_itemSlot->setOwner(this);
}

///* virtual override final */
//void Container::UpdateInfo()
//{
//    GetInfo().clear();
//    GetInfo().addTitleStr("CONTAINER");
//    GetInfo().addNameStr("id/ss_id:");    GetInfo().addValueStr(std::to_string(id()) + " / " + std::to_string(starsystem()->id()));
//    GetInfo().addNameStr("armor:");       GetInfo().addValueStr(std::to_string(dataLife().armor));
//    GetInfo().addNameStr("pos:");         GetInfo().addValueStr( meti::str(center()) );
//}
 
///* virtual override final */
//void Container::RenderInfoInSpace(const jeti::Renderer& render, const glm::vec2& scroll_coords, float zoom)
//{
//    UpdateInfo();
//    glm::vec2 pos(center().x - scroll_coords.x, center().y - scroll_coords.y);
//    pos /= zoom;
//    jeti::drawInfoIn2Column(GetInfo().title_list, GetInfo().value_list, pos);
    
//    pos.x += 300;
//    m_ItemSlot->item()->RenderInfo(render, pos);
//}
 
/* virtual override final */   
void Container::_postDeathUniqueEvent(bool show_effect)
{
    assert(false);
//    if (m_itemSlot->item()->type() == entity::Type::BOMB) {
//        starsystem()->bombExplosionEvent(this, show_effect);
//    } else {
//        if (show_effect) {
//            jeti::ExplosionEffect* explosion = jeti::getNewExplosionEffect(collisionRadius());
//            starsystem()->Add(explosion, center());
//        }
//    }
}

void Container::updateInSpace(int time, bool show_effect)
{
    _checkDeath(show_effect);         
    if (time > 0) {
        setPosition(position() + _externalForce());
        _externalForce() *= 0.99;
    }
}
               
//void Container::Render(const jeti::Renderer& render)
//{
//    //alpitodorender render.DrawMesh(mesh(), textureOb(), actualModelMatrix());
//}

} // namespace control



//Container::Container(int_t id)
//{
//    setId(id);
//    setTypeId(entity::Type::CONTAINER);
//}

///* virtual */
//Container::~Container()
//{
//    LOG("___::~Container("+std::to_string(id())+")");
//}

///* virtual override final */
//void Container::putChildrenToGarbage() const
//{
//   manager::EntityManager::get().addToGarbage(m_itemSlot);
//}

//bool
//Container::insertItem(item::Base* item)
//{
//    return m_itemSlot->insert(item);
//}

///* override final */
//void Container::hit(int damage) {
//    SpaceObject::hit(damage);
//    if (_dataLife().is_dying) {
//        if (m_itemSlot->item()) {
//            if (m_itemSlot->item()->subtype() == entity::Type::BOMB) {
//                // send explosion event
//            }
//        }
//    }
//}

//void Container::bindItemSlot(slot::ItemSlot* item_slot)
//{
//    m_itemSlot = item_slot;
//    m_itemSlot->setOwner(this);
//}

/////* virtual override final */
////void Container::UpdateInfo()
////{
////    GetInfo().clear();
////    GetInfo().addTitleStr("CONTAINER");
////    GetInfo().addNameStr("id/ss_id:");    GetInfo().addValueStr(std::to_string(id()) + " / " + std::to_string(starsystem()->id()));
////    GetInfo().addNameStr("armor:");       GetInfo().addValueStr(std::to_string(dataLife().armor));
////    GetInfo().addNameStr("pos:");         GetInfo().addValueStr( meti::str(center()) );
////}

/////* virtual override final */
////void Container::RenderInfoInSpace(const jeti::Renderer& render, const glm::vec2& scroll_coords, float zoom)
////{
////    UpdateInfo();
////    glm::vec2 pos(center().x - scroll_coords.x, center().y - scroll_coords.y);
////    pos /= zoom;
////    jeti::drawInfoIn2Column(GetInfo().title_list, GetInfo().value_list, pos);

////    pos.x += 300;
////    m_ItemSlot->item()->RenderInfo(render, pos);
////}

///* virtual override final */
//void Container::_postDeathUniqueEvent(bool show_effect)
//{
//    if (m_itemSlot->item()->type() == entity::Type::BOMB)
//    {
//        starsystem()->bombExplosionEvent(this, show_effect);
//    }
//    else
//    {
//        if (show_effect == true)
//        {
////            jeti::ExplosionEffect* explosion = jeti::getNewExplosionEffect(collisionRadius());
////            starsystem()->Add(explosion, center());
//        }
//    }
//}

//void Container::updateInSpace(int time, bool show_effect)
//{
//    _checkDeath(show_effect);
//    if (time > 0) {
//        setPosition(position() + _externalForce());
//        _externalForce() *= 0.99;
//    }
//}

////void Container::Render(const jeti::Renderer& render)
////{
////    //alpitodorender render.DrawMesh(mesh(), textureOb(), actualModelMatrix());
////}

//void Container::SaveData(boost::property_tree::ptree& save_ptree, const std::string& root) const
//{
//    LOG(" Container("+std::to_string(id())+")::SaveData()");

//    save_ptree.put(root+"target_pos.x", m_targetPos.x);
//    save_ptree.put(root+"target_pos.y", m_targetPos.y);

//    save_ptree.put(root+"velocity", m_velocity);
//}

//void Container::LoadData(const boost::property_tree::ptree& load_ptree)
//{
//    LOG(" Container("+std::to_string(id())+")::LoadData()");

//    m_targetPos.x   = load_ptree.get<float>("target_pos.x");
//    m_targetPos.y   = load_ptree.get<float>("target_pos.y");

//    m_velocity = load_ptree.get<float>("velocity");
//}

//void Container::ResolveData()
//{
//    LOG(" Container("+std::to_string(id())+")::ResolveData()");

//    //((Starsystem*)manager::EntityManager::get().get(data_unresolved_SpaceObject.starsystem_id))->add(this, data_unresolved_Orientation.center);
//}

///* virtual override final */
//void Container::Save(boost::property_tree::ptree& save_ptree) const
//{
//    const std::string root = "container." + std::to_string(id()) + ".";

//    Base::SaveData(save_ptree, root);
//    //Orientation::SaveData(save_ptree, root);
////    BaseDrawable::SaveData(save_ptree, root);
//    SpaceObject::SaveData(save_ptree, root);
//    Container::SaveData(save_ptree, root);
//}

///* virtual override final */
//void Container::Load(const boost::property_tree::ptree& load_ptree)
//{
//    Base::LoadData(load_ptree);
//  //  Orientation::LoadData(load_ptree);
////    BaseDrawable::LoadData(load_ptree);
//    SpaceObject::LoadData(load_ptree);
//    Container::LoadData(load_ptree);
//}

///* virtual override final */
//void Container::Resolve()
//{
//    Base::ResolveData();
//  //  Orientation::ResolveData();
////    BaseDrawable::ResolveData();
//    SpaceObject::ResolveData();
//    Container::ResolveData();
//}
