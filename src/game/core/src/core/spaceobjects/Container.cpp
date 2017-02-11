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
#include <managers/EntityManager.hpp>
#include <world/starsystem.hpp>

//#include <jeti/Render.hpp>

//#include <jeti/particlesystem/ExplosionEffect.hpp>

#include <slots/ItemSlot.hpp>
#include <item/BaseItem.hpp>

#include <ceti/serialization/macro.hpp>

namespace model {

Container::Container()
{
    setType(entity::type::CONTAINER_ID);
}

Container::Container(const std::string& data)
{
    MACRO_READ_SERIALIZED_DATA
}

std::string
Container::data() const
{
    MACRO_SAVE_SERIALIZED_DATA
}

} // namespace model


namespace control {

Container::Container(model::Container* model)
    :
      SpaceObject(model)
    , m_model_container(model)
{
//    setId(id);
//    setTypeId(entity::Type::CONTAINER_ID);
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
//   core::global::get().entityManager().addToGarbage(m_itemSlot);
}

bool
Container::insertItem(control::item::Base* item)
{
    return m_itemSlot->insert(item);
}

/* override final */
void Container::hit(int damage) {
    SpaceObject::hit(damage);
    assert(false);
//    if (model()->dataLife().is_dying) {
//        if (m_itemSlot->item()) {
//            if (m_itemSlot->item()->subtype() == entity::Type::BOMB_ID) {
//                // send explosion event
//            }
//        }
//    }
}
            
void Container::bindItemSlot(ItemSlot* item_slot) 
{
    assert(false);
//    m_itemSlot = item_slot;
//    m_itemSlot->setOwner(this);
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
//    if (m_itemSlot->item()->type() == entity::Type::BOMB_ID) {
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
//    setTypeId(entity::Type::CONTAINER_ID);
//}

///* virtual */
//Container::~Container()
//{
//    LOG("___::~Container("+std::to_string(id())+")");
//}

///* virtual override final */
//void Container::putChildrenToGarbage() const
//{
//   core::global::get().entityManager().addToGarbage(m_itemSlot);
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
//            if (m_itemSlot->item()->subtype() == entity::Type::BOMB_ID) {
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
//    if (m_itemSlot->item()->type() == entity::Type::BOMB_ID)
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

//    //((Starsystem*)core::global::get().entityManager().get(data_unresolved_SpaceObject.starsystem_id))->add(this, data_unresolved_Orientation.center);
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