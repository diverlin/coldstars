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

#include "Asteroid.hpp"

#include <common/constants.hpp>
#include <math/rand.hpp>
//#include <ceti/StringUtils.hpp>
#include <common/Logger.hpp>
 
#include <world/starsystem.hpp>
#include <common/Global.hpp>
#include <managers/EntitiesManager.hpp>

#include <builder/spaceobjects/ContainerBuilder.hpp>

//#include <jeti/particlesystem/ExplosionEffect.hpp>

#include <spaceobjects/Container.hpp>

#include <meti/RandUtils.hpp>

Asteroid::Asteroid(int id)
{   
    setId(id);
    setTypeId(TYPE::ENTITY::ASTEROID_ID);
    
    setMass(meti::getRandInt(10, 30));
}
    
/* virtual */
Asteroid::~Asteroid()
{
    #if CREATEDESTROY_LOG_ENABLED == 1
    Logger::Instance().Log("___::~Asteroid("+std::to_string(id())+")");
    #endif
}

void Asteroid::UpdateInSpace(int time, bool show_effect)
{    
    checkDeath(show_effect);
    if (time > 0)
    {    
        UpdatePosition();
    }         
}

void Asteroid::CollisionEvent(bool show_effect)
{
    dataLife().is_alive = false;
    dataLife().dying_time = -1;
}
    
void Asteroid::postDeathUniqueEvent(bool show_effect)
{
    int angleZ = meti::getRandInt(0, 360);
    float impulse_strength = 0.5;
    for (int i=0; i<3; i++)
    {      
        Container* container = ContainerBuilder::Instance().GetNewMineralContainer(4);
        
        glm::vec3 impulse_dir(meti::getXYVec3Unit(angleZ));
        container->addImpulse(impulse_dir, impulse_strength);
        
        starsystem()->AddContainer(container, center());
        
        angleZ += 120;
    }
    
    if (show_effect == true)
    {
//        jeti::ExplosionEffect* explosion = jeti::getNewExplosionEffect(collisionRadius());
//        starsystem()->Add(explosion, center());
    }
                    
}    
  
///* virtual override final */
//void Asteroid::UpdateInfo()
//{
//    GetInfo().clear();

//    GetInfo().addTitleStr("ASTEROID");
//    GetInfo().addNameStr("id/ss_id:");    GetInfo().addValueStr(std::to_string(id()) + " / " + std::to_string(starsystem()->id()));
//    GetInfo().addNameStr("armor:");       GetInfo().addValueStr(std::to_string(dataLife().armor));
//    GetInfo().addNameStr("mass:");        GetInfo().addValueStr(std::to_string(mass()));
//    GetInfo().addNameStr("speed x 100:"); GetInfo().addValueStr(std::to_string(int(GetDataPlanet().speed*100)));
//    GetInfo().addNameStr("pos:");         GetInfo().addValueStr( meti::str(center()) );
//}

void Asteroid::SaveData(boost::property_tree::ptree& save_ptree, const std::string& root) const
{
    #if SAVELOAD_LOG_ENABLED == 1
    Logger::Instance().Log(" Asteroid("+std::to_string(id())+")::SaveData", SAVELOAD_LOG_DIP);
    #endif
}

void Asteroid::LoadData(const boost::property_tree::ptree& ptree)
{
    #if SAVELOAD_LOG_ENABLED == 1
    Logger::Instance().Log(" Asteroid("+std::to_string(id())+")::LoadData", SAVELOAD_LOG_DIP);
    #endif
}

void Asteroid::ResolveData()
{
    #if SAVELOAD_LOG_ENABLED == 1
    Logger::Instance().Log(" Asteroid("+std::to_string(id())+")::ResolveData", SAVELOAD_LOG_DIP);
    #endif
    
    ((StarSystem*)global::get().entitiesManager().GetEntityById(data_unresolved_SpaceObject.starsystem_id))->Add(this, parent(), data_unresolved_Planetoid.orbit_it); 
}

/* virtual override final */    
void Asteroid::Save(boost::property_tree::ptree& save_ptree) const        
{
    std::string root = "asteroid." + std::to_string(id())+".";

    Base::SaveData(save_ptree, root);
    //Orientation::SaveData(save_ptree, root);
//    BaseDrawable::SaveData(save_ptree, root);
    SpaceObject::SaveData(save_ptree, root);
    Planetoid::SaveData(save_ptree, root);
    Asteroid::SaveData(save_ptree, root);
}

/* virtual override final */    
void Asteroid::Load(const boost::property_tree::ptree& load_ptree)
{
    Base::LoadData(load_ptree);
  //  Orientation::LoadData(load_ptree);
//    BaseDrawable::LoadData(load_ptree);
    SpaceObject::LoadData(load_ptree);
    Planetoid::LoadData(load_ptree);
    Asteroid::LoadData(load_ptree);
}

/* virtual override final */    
void Asteroid::Resolve()
{
    Base::ResolveData();
   // Orientation::ResolveData();
//    BaseDrawable::ResolveData();
    SpaceObject::ResolveData();
    Planetoid::ResolveData();
    Asteroid::ResolveData();
}    
        



