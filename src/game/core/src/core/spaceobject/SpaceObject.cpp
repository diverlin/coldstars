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

#include "SpaceObject.hpp"

#include <world/starsystem.hpp>
#include <core/manager/EntityManager.hpp>

#include <ceti/Logger.hpp>
#include <ceti/serialization/macro.hpp>

namespace control {

SpaceObject::SpaceObject(descriptor::SpaceObject* descr, model::SpaceObject* model)
    :
      ceti::control::Orientation(model)
    , Base(descr, model)
    , m_model_spaceobject(model)
    , m_descriptor_spaceobject(descr)
{
    _init();
}

SpaceObject::~SpaceObject()
{}

void SpaceObject::_init()
{
    if (!m_starsystem && model()->starsystem() != NONE) {
        m_starsystem = EntityManager::get().starsystem(model()->starsystem());
    }
    if (!m_parent && model()->parent() != NONE) {
        m_parent = EntityManager::get().spaceObject(model()->parent());
    }
}

void SpaceObject::setStarSystem(StarSystem* starsystem)
{
    assert(starsystem);
    m_starsystem = starsystem;
    model()->setStarSystem(starsystem->id());
}

void SpaceObject::setParent(SpaceObject* parent)
{
    assert(parent);
    m_parent = parent;
    model()->setParent(parent->id());
}

void SpaceObject::resetStarSystem()
{
    m_starsystem = nullptr;
    model()->setStarSystem(NONE);
}

void SpaceObject::resetParent()
{
    m_parent = nullptr;
    model()->setParent(NONE);
}

void SpaceObject::addImpulse(const glm::vec3& force_dir, float strength)
{
    m_impulse += force_dir * strength;
}

void SpaceObject::hit(int damage)
{
    LOG(std::string("SpaceObject::hit id=") << std::to_string(model()->id()) << " damage=" << std::to_string(damage));
    model()->setArmor(model()->armor() - damage);
    if (model()->armor() <= 0) {
        model()->setArmor(0);
        model()->setIsDying(true);
    }
    LOG(std::string("armor=") << std::to_string(model()->armor()) << " is_dying=" << std::to_string(model()->isDying()) << std::endl);
}

void SpaceObject::killSilently()
{
    model()->setIsAlive(false);
    model()->setGarbageReady(true);
}

void SpaceObject::_checkDeath(bool show_effect)
{
    if (model()->isDying()) {
        model()->setDyingTime(model()->dyingTime() - 1);
        if (model()->dyingTime() < 0) {
            model()->setIsAlive(false);
            if (!model()->garbageReady()) {
                _postDeathUniqueEvent(show_effect);
                model()->setGarbageReady(true);
            }
        }
    }
}

///* virtual */
//void SpaceObject::RenderInfoInSpace(const jeti::Renderer&, const glm::vec2& scroll_coords, float scale)
//{
//    UpdateInfo(); // virtual
//    glm::vec2 pos(center().x - scroll_coords.x, center().y - scroll_coords.y);
//    jeti::drawInfoIn2Column(m_Info.title_list, m_Info.value_list, pos/scale);
//}

//void SpaceObject::RenderInfo(const glm::vec2& center)
//{
//    UpdateInfo(); // virtual
//    jeti::drawInfoIn2Column(m_Info.title_list, m_Info.value_list, center);
//}

} // namespace control


















//SpaceObject::SpaceObject()
//    :
//      ceti::control::Orientation(new ceti::model::Orientation)
//{}

///* virtual override */
//SpaceObject::~SpaceObject()
//{
//    LOG("___::~SpaceObject("+std::to_string(id())+")");
//}

//void SpaceObject::addImpulse(const glm::vec3& force_dir, float strength)
//{
//    m_externalForce += force_dir * strength;
//}

///* virtual */
//void SpaceObject::hit(int damage)
//{
//    LOG(std::string("SpaceObject::hit id=") << std::to_string(id()) << " damage=" << std::to_string(damage));
//    m_dataLife.armor -= damage;
//    if (m_dataLife.armor <= 0) {
//        m_dataLife.armor = 0;
//        m_dataLife.is_dying = true;
//    }
//    LOG(std::string("armor=") << std::to_string(m_dataLife.armor) << " is_dying=" << std::to_string(m_dataLife.is_dying) << std::endl);
//}

//void SpaceObject::killSilently()
//{
//    m_dataLife.is_alive      = false;
//    m_dataLife.garbage_ready = true;
//}

//void SpaceObject::_checkDeath(bool show_effect)
//{
//    if (m_dataLife.is_dying) {
//        m_dataLife.dying_time--;
//        if (m_dataLife.dying_time < 0) {
//            m_dataLife.is_alive = false;
//            if (!m_dataLife.garbage_ready) {
//                _postDeathUniqueEvent(show_effect);
//                m_dataLife.garbage_ready = true;
//            }
//        }
//    }
//}

/////* virtual */
////void SpaceObject::RenderInfoInSpace(const jeti::Renderer&, const glm::vec2& scroll_coords, float scale)
////{
////    UpdateInfo(); // virtual
////    glm::vec2 pos(center().x - scroll_coords.x, center().y - scroll_coords.y);
////    jeti::drawInfoIn2Column(m_Info.title_list, m_Info.value_list, pos/scale);
////}

////void SpaceObject::RenderInfo(const glm::vec2& center)
////{
////    UpdateInfo(); // virtual
////    jeti::drawInfoIn2Column(m_Info.title_list, m_Info.value_list, center);
////}

//void SpaceObject::SaveData(boost::property_tree::ptree& save_ptree, const std::string& root) const
//{
//    LOG(" SpaceObject("+std::to_string(id())+")::Save(");
    
//    save_ptree.put(root+"data_life.is_alive",   m_dataLife.is_alive);
//    save_ptree.put(root+"data_life.armor",      m_dataLife.armor);
//    save_ptree.put(root+"data_life.life_time",  m_dataLife.life_time);
//    save_ptree.put(root+"data_life.dying_time", m_dataLife.dying_time);

//    save_ptree.put(root+"mass", m_mass);


//    if (m_parent) save_ptree.put(root+"data_unresolved_SpaceObject.parent_id", m_parent->id());
//    else        save_ptree.put(root+"data_unresolved_SpaceObject.parent_id", NONE);

//    if (m_starsystem)    save_ptree.put(root+"data_unresolved_SpaceObject.starsystem_id", m_starsystem->id());
//    else            save_ptree.put(root+"data_unresolved_SpaceObject.starsystem_id", NONE);

//    save_ptree.put(root+"place_type_id", (int)m_placeTypeId);
//}



//void SpaceObject::LoadData(const boost::property_tree::ptree& load_ptree)
//{
//    LOG(" SpaceObject("+std::to_string(id())+")::LoadData");
    
//    m_dataLife.is_alive   = load_ptree.get<bool>("data_life.is_alive");
//    m_dataLife.armor      = load_ptree.get<int>("data_life.armor");
//    m_dataLife.life_time  = load_ptree.get<int>("data_life.life_time");
//    m_dataLife.dying_time = load_ptree.get<int>("data_life.dying_time");

//    m_mass = load_ptree.get<int>("mass");

//    m_placeTypeId = (type::place)load_ptree.get<int>("place_type_id");
    
//    data_unresolved_SpaceObject.parent_id     = load_ptree.get<int>("data_unresolved_SpaceObject.parent_id");
//    data_unresolved_SpaceObject.starsystem_id = load_ptree.get<int>("data_unresolved_SpaceObject.starsystem_id");
//}

//void SpaceObject::ResolveData()
//{
//    LOG(" SpaceObject("+std::to_string(id())+")::ResolveData");
    
//    if (data_unresolved_SpaceObject.parent_id != NONE) {
//        m_parent = (SpaceObject*)EntityManager::get().getEntity(data_unresolved_SpaceObject.parent_id);
//    }
//    if (data_unresolved_SpaceObject.starsystem_id != NONE) {
//        m_starsystem = (Starsystem*)EntityManager::get().getEntity(data_unresolved_SpaceObject.starsystem_id);
//    }
//}





