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
#include <common/rand.hpp>
#include <common/myStr.hpp>
#include <common/Logger.hpp>
 
#include <world/starsystem.hpp>
#include <world/EntityManager.hpp>

#include <builder/spaceobjects/ContainerBuilder.hpp>

#include <effects/particlesystem/ExplosionEffect.hpp>

#include <spaceobjects/Container.hpp>


Asteroid::Asteroid(int id)
{   
    SetId(id);
    SetTypeId(TYPE::ENTITY::ASTEROID_ID);
    
       SetMass(getRandInt(10, 30));
}
    
/* virtual */
Asteroid::~Asteroid()
{
    #if CREATEDESTROY_LOG_ENABLED == 1
    Logger::Instance().Log("___::~Asteroid("+int2str(GetId())+")");
    #endif
}

void Asteroid::UpdateInSpace(int time, bool show_effect)
{    
    CheckDeath(show_effect);
    if (time > 0)
    {    
        UpdatePosition();
    }         
}

void Asteroid::CollisionEvent(bool show_effect)
{
    GetDataLife().is_alive = false;
    GetDataLife().dying_time = -1;
}
    
void Asteroid::PostDeathUniqueEvent(bool show_effect)
{
    int angleZ = getRandInt(0, 360);
    float impulse_strength = 0.5;
    for (int i=0; i<3; i++)
    {      
        Container* container = ContainerBuilder::Instance().GetNewMineralContainer(4);
        
        glm::vec3 impulse_dir(getXYVec3Unit(angleZ));
        container->ApplyImpulse(impulse_dir, impulse_strength);
        
        GetStarSystem()->AddContainer(container, GetCenter());
        
        angleZ += 120;
    }
    
    if (show_effect == true)
    {
        ExplosionEffect* explosion = getNewExplosionEffect(GetCollisionRadius());
        GetStarSystem()->Add(explosion, GetCenter());                
    }
                    
}    
  
/* virtual override final */
void Asteroid::UpdateInfo()
{   
    GetInfo().clear();

    GetInfo().addTitleStr("ASTEROID");
    GetInfo().addNameStr("id/ss_id:");    GetInfo().addValueStr(int2str(GetId()) + " / " + int2str(GetStarSystem()->GetId()));
    GetInfo().addNameStr("armor:");       GetInfo().addValueStr(int2str(GetDataLife().armor));
    GetInfo().addNameStr("mass:");        GetInfo().addValueStr(int2str(GetMass()));
    GetInfo().addNameStr("speed x 100:"); GetInfo().addValueStr(int2str(int(GetDataPlanet().speed*100)));
    GetInfo().addNameStr("pos:");         GetInfo().addValueStr( str(GetCenter()) );
}     

void Asteroid::Render_NEW(const Renderer& render, const glm::vec2& scroll_coords)
{
    render.RenderMeshLightNormalMap(GetMesh(), GetTextureOb(), GetActualModelMatrix(), scroll_coords, GetStarSystem()->GetColor());
}
    
void Asteroid::Render_OLD(const Renderer& render)
{
    render.RenderMeshGeometry(GetMesh(), GetTextureOb(), GetActualModelMatrix());       
}

void Asteroid::SaveDataUniqueAsteroid(boost::property_tree::ptree& save_ptree, const std::string& root) const
{
    #if SAVELOAD_LOG_ENABLED == 1
    Logger::Instance().Log(" Asteroid("+int2str(GetId())+")::SaveDataUniqueAsteroid", SAVELOAD_LOG_DIP);
    #endif
}

void Asteroid::LoadDataUniqueAsteroid(const boost::property_tree::ptree& ptree)
{
    #if SAVELOAD_LOG_ENABLED == 1
    Logger::Instance().Log(" Asteroid("+int2str(GetId())+")::LoadDataUniqueAsteroid", SAVELOAD_LOG_DIP);
    #endif
}

void Asteroid::ResolveDataUniqueAsteroid()
{
    #if SAVELOAD_LOG_ENABLED == 1
    Logger::Instance().Log(" Asteroid("+int2str(GetId())+")::ResolveDataUniqueAsteroid", SAVELOAD_LOG_DIP);
    #endif
    
    ((StarSystem*)EntityManager::Instance().GetEntityById(data_unresolved_BaseSpaceEntity.starsystem_id))->Add(this, GetParent(), data_unresolved_BasePlanet.orbit_it); 
}

/* virtual override final */    
void Asteroid::SaveData(boost::property_tree::ptree& save_ptree) const        
{
    std::string root = "asteroid." + int2str(GetId())+".";
    SaveDataUniqueBase(save_ptree, root);
    SaveDataUniqueOrientation(save_ptree, root);
    SaveDataUniqueBaseDrawable(save_ptree, root);
    SaveDataUniqueBaseSpaceEntity(save_ptree, root);
    SaveDataUniqueBasePlanet(save_ptree, root);
    SaveDataUniqueAsteroid(save_ptree, root);
}

/* virtual override final */    
void Asteroid::LoadData(const boost::property_tree::ptree& load_ptree)
{
    LoadDataUniqueBase(load_ptree);
    LoadDataUniqueOrientation(load_ptree);
    LoadDataUniqueBaseDrawable(load_ptree);
    LoadDataUniqueBaseSpaceEntity(load_ptree);
    LoadDataUniqueBasePlanet(load_ptree);
    LoadDataUniqueAsteroid(load_ptree);
}

/* virtual override final */    
void Asteroid::ResolveData()
{
    ResolveDataUniqueBase();
    ResolveDataUniqueOrientation();
    ResolveDataUniqueBaseDrawable();
    ResolveDataUniqueBaseSpaceEntity();
    ResolveDataUniqueBasePlanet();
    ResolveDataUniqueAsteroid();
}    
        




