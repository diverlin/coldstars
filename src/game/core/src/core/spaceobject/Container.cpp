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
#include <core/manager/DescriptorManager.hpp>
#include <world/starsystem.hpp>

#include <core/builder/slot/ItemSlotBuilder.hpp>

//#include <jeti/Render.hpp>

//#include <jeti/particlesystem/ExplosionEffect.hpp>

#include <core/slot/ItemSlot.hpp>
#include <core/item/Item.hpp>
#include <core/item/equipment/ALL>

namespace {
descriptor::Container* getDescriptor(model::Container* model) {
    return descriptor::Manager::get().container(model->descriptor());
}

} // namespace

namespace control {

namespace {

bool itemInsertHelper(ItemSlot* slot, int_t id) {
    model::Base* model_base = EntityManager::get().get(id);
    descriptor::Base* descriptor_base = descriptor::Manager::get().get(model_base->descriptor());
    assert(descriptor_base->obType() == entity::Type::EQUIPMENT);
    switch(descriptor_base->obSubType()) {
    case entity::Type::SCANER_EQUIPMENT: {
        item::Scaner* item = new item::Scaner(EntityManager::get().scaner(id));
        return slot->insert(item);
    }
    case entity::Type::DRIVE_EQUIPMENT: {
        item::Drive* item = new item::Drive(EntityManager::get().drive(id));
        return slot->insert(item);
    }
    case entity::Type::BAK_EQUIPMENT: {
        item::Bak* item = new item::Bak(EntityManager::get().bak(id));
        return slot->insert(item);
    }
    case entity::Type::DROID_EQUIPMENT: {
        item::Droid* item = new item::Droid(EntityManager::get().droid(id));
        return slot->insert(item);
    }
    case entity::Type::GRAPPLE_EQUIPMENT: {
        item::Grapple* item = new item::Grapple(EntityManager::get().grapple(id));
        return slot->insert(item);
    }
    case entity::Type::LAZER_EQUIPMENT: {
        item::Lazer* item = new item::Lazer(EntityManager::get().lazer(id));
        return slot->insert(item);
    }
    case entity::Type::PROTECTOR_EQUIPMENT: {
        item::Protector* item = new item::Protector(EntityManager::get().protector(id));
        return slot->insert(item);
    }
    case entity::Type::RADAR_EQUIPMENT: {
        item::Radar* item = new item::Radar(EntityManager::get().radar(id));
        return slot->insert(item);
    }
    case entity::Type::ROCKET_EQUIPMENT: {
        item::Rocket* item = new item::Rocket(EntityManager::get().rocket(id));
        return slot->insert(item);
    }
    }
}
} // namespace

Container::Container(model::Container* _model)
    :
      SpaceObject(_model, getDescriptor(_model))
    , m_model_container(_model)
    , m_descriptor_container(getDescriptor(_model))
{

    ItemSlot* slot = genItemSlot(entity::Type::CARGO_SLOT);
    bindItemSlot(slot);

    if (model()->item() != NONE) {
        itemInsertHelper(slot, model()->item());
    }
}

/* virtual */   
Container::~Container()
{
    LOG("___::~Container("+std::to_string(model()->id())+")");
}

/* virtual override final */
void Container::putChildrenToGarbage() const
{
    assert(false);
//   EntityManager::get().addToGarbage(m_itemSlot);
}

bool
Container::insertItem(Item* item)
{
    return m_itemSlot->insert(item);
}

/* override final */
void Container::hit(int damage) {
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
            
void Container::bindItemSlot(ItemSlot* item_slot) 
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
//   EntityManager::get().addToGarbage(m_itemSlot);
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

//void Container::bindItemSlot(ItemSlot* item_slot)
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

//    //((Starsystem*)EntityManager::get().get(data_unresolved_SpaceObject.starsystem_id))->add(this, data_unresolved_Orientation.center);
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
