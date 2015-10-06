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
#include <items/BaseItem.hpp>


Container::Container(int id)
{
    setId(id);
    setTypeId(TYPE::ENTITY::CONTAINER_ID);
}

/* virtual */   
Container::~Container()
{
    Logger::Instance().Log("___::~Container("+std::to_string(id())+")");
}

/* virtual override final */
void Container::putChildrenToGarbage() const
{
    global::get().entityManager().addToGarbage(m_itemSlot);
}

/* override final */
void Container::hit(int damage) {
    SpaceObject::hit(damage);
    if (dataLife().is_dying) {
        if (m_itemSlot->item()) {
            if (m_itemSlot->item()->subTypeId() == TYPE::ENTITY::BOMB_ID) {
                // send explosion event
            }
        }
    }
}
            
void Container::bindItemSlot(ItemSlot* item_slot) 
{ 
    m_itemSlot = item_slot; 
    m_itemSlot->SetOwner(this); 
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
void Container::postDeathUniqueEvent(bool show_effect)
{
    if (m_itemSlot->item()->typeId() == TYPE::ENTITY::BOMB_ID)
    {
        starsystem()->bombExplosionEvent(this, show_effect);  
    }
    else
    {
        if (show_effect == true)
        {
//            jeti::ExplosionEffect* explosion = jeti::getNewExplosionEffect(collisionRadius());
//            starsystem()->Add(explosion, center());
        }
    }
}

void Container::updateInSpace(int time, bool show_effect)
{
    checkDeath(show_effect);         
    if (time > 0) {
        setCenter(center() + externalForce());
        externalForce() *= 0.99;
    }
}
               
//void Container::Render(const jeti::Renderer& render)
//{
//    //alpitodorender render.DrawMesh(mesh(), textureOb(), actualModelMatrix());
//}

void Container::SaveData(boost::property_tree::ptree& save_ptree, const std::string& root) const    
{
    Logger::Instance().Log(" Container("+std::to_string(id())+")::SaveData()", SAVELOAD_LOG_DIP);
    
    save_ptree.put(root+"target_pos.x", m_targetPos.x);
    save_ptree.put(root+"target_pos.y", m_targetPos.y);

    save_ptree.put(root+"velocity", m_velocity);
}

void Container::LoadData(const boost::property_tree::ptree& load_ptree)
{
    Logger::Instance().Log(" Container("+std::to_string(id())+")::LoadData()", SAVELOAD_LOG_DIP);
    
    m_targetPos.x   = load_ptree.get<float>("target_pos.x");
    m_targetPos.y   = load_ptree.get<float>("target_pos.y");
    
    m_velocity = load_ptree.get<float>("velocity");
}

void Container::ResolveData()
{
    Logger::Instance().Log(" Container("+std::to_string(id())+")::ResolveData()", SAVELOAD_LOG_DIP);
    
    ((StarSystem*)global::get().entityManager().entity(data_unresolved_SpaceObject.starsystem_id))->add(this, data_unresolved_Orientation.center);
}        

/* virtual override final */
void Container::Save(boost::property_tree::ptree& save_ptree) const
{
    const std::string root = "container." + std::to_string(id()) + ".";

    Base::SaveData(save_ptree, root);
    //Orientation::SaveData(save_ptree, root);
//    BaseDrawable::SaveData(save_ptree, root);
    SpaceObject::SaveData(save_ptree, root);
    Container::SaveData(save_ptree, root);
}

/* virtual override final */
void Container::Load(const boost::property_tree::ptree& load_ptree)
{
    Base::LoadData(load_ptree);
  //  Orientation::LoadData(load_ptree);
//    BaseDrawable::LoadData(load_ptree);
    SpaceObject::LoadData(load_ptree);
    Container::LoadData(load_ptree);
}
    
/* virtual override final */    
void Container::Resolve()
{
    Base::ResolveData();
  //  Orientation::ResolveData();
//    BaseDrawable::ResolveData();
    SpaceObject::ResolveData();
    Container::ResolveData();
}
