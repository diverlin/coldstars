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

#include "Star.hpp"

#include <common/myStr.hpp>
#include <common/common.hpp>
#include <math/rand.hpp>
#include <common/Logger.hpp>

#include <world/EntityManager.hpp>
#include <world/starsystem.hpp>

#include <resources/textureOb.hpp>

#include <glm/gtx/transform.hpp>

#include "resources/MeshCollector.hpp"
#include "resources/TextureManager.hpp"
   
Star::Star(int id)
:
m_Offset(0.0),
m_DeltaColor(0.0),
m_SparkActive(false),
m_SparkGrows(false),
m_TurnSinceLastSparkCounter(0)
{ 
    SetId(id);
    SetTypeId(TYPE::ENTITY::STAR_ID);

    m_TurnSparkThreshold = getRandInt(STARSPAK_TURN_THRESHOLD_MIN, STARSPAK_TURN_THRESHOLD_MAX);
}
  
/* virtual */  
Star::~Star()
{
    #if CREATEDESTROY_LOG_ENABLED == 1
    Logger::Instance().Log("___::~Star("+int2str(GetId())+")");
    #endif    
}

int Star::GetColorId() const { return GetTextureOb().GetData().color_id; }

float Star::GetBrightThreshold() const { return GetTextureOb().GetData().brightThreshold; }
            
void Star::CalcColor()
{
    SetColor(getColor4fById(GetTextureOb().GetData().color_id));
}
       
void Star::InitiateSpark()
{
    m_SparkActive = true;
    m_SparkGrows = true;
    m_TurnSinceLastSparkCounter = 0;
}

void Star::UpdateInSpaceInStatic()
{
    if (m_TurnSinceLastSparkCounter > m_TurnSparkThreshold)
    {
        if (getRandInt(1, 2) == 1) 
        {
            InitiateSpark(); 
        }
    }
    else
    {
        m_TurnSinceLastSparkCounter++;    
    }
}
               
void Star::UpdateInSpace(int time, bool show_effect)
{

}    

void Star::Update()
{
   m_Offset += getRandFloat(0.0001, 0.0005);
}

/* virtual override final */
void Star::UpdateInfo()
{ 
    GetInfo().clear();
    GetInfo().addTitleStr("STAR");
    GetInfo().addNameStr("id/ss_id:");  GetInfo().addValueStr(int2str(GetId()) + " / " + int2str(GetStarSystem()->GetId()));
    GetInfo().addNameStr("armor:");     GetInfo().addValueStr(int2str(GetDataLife().armor));
    GetInfo().addNameStr("pos:");       GetInfo().addValueStr( str(GetCenter()) );
}

/* virtual override final */
void Star::PostDeathUniqueEvent(bool)
{}

   
void Star::SaveData(boost::property_tree::ptree& save_ptree, const std::string& root) const
{
    #if SAVELOAD_LOG_ENABLED == 1
    Logger::Instance().Log(" Star("+int2str(GetId())+")::SaveData", SAVELOAD_LOG_DIP);
    #endif
    
    save_ptree.put(root+"m_TurnSinceLastSparkCounter", m_TurnSinceLastSparkCounter);
    save_ptree.put(root+"m_TurnSparkThreshold", m_TurnSparkThreshold);
}

void Star::LoadData(const boost::property_tree::ptree& load_ptree)
{
    #if SAVELOAD_LOG_ENABLED == 1
    Logger::Instance().Log(" Star("+int2str(GetId())+")::LoadData", SAVELOAD_LOG_DIP);
    #endif
    
    m_TurnSinceLastSparkCounter = load_ptree.get<int>("m_TurnSinceLastSparkCounter");
    m_TurnSparkThreshold = load_ptree.get<int>("m_TurnSparkThreshold");    
}

void Star::ResolveData()
{
    #if SAVELOAD_LOG_ENABLED == 1
    Logger::Instance().Log(" Star("+int2str(GetId())+")::ResolveData", SAVELOAD_LOG_DIP);
    #endif
    
    ((StarSystem*)EntityManager::Instance().GetEntityById(data_unresolved_BaseSpaceEntity.starsystem_id))->Add(this);     
}

/* virtual override final */
void Star::Save(boost::property_tree::ptree& save_ptree) const
{
    std::string root = "star." + int2str(GetId())+".";

    Base::SaveData(save_ptree, root);
    Orientation::SaveData(save_ptree, root);
    BaseDrawable::SaveData(save_ptree, root);
    BaseSpaceEntity::SaveData(save_ptree, root);
    BasePlanet::SaveData(save_ptree, root);
    Star::SaveData(save_ptree, root);
}

/* virtual override final */
void Star::Load(const boost::property_tree::ptree& load_ptree)
{
    Base::LoadData(load_ptree);
    Orientation::LoadData(load_ptree);
    BaseDrawable::LoadData(load_ptree);
    BaseSpaceEntity::LoadData(load_ptree);
    BasePlanet::LoadData(load_ptree);
    Star::LoadData(load_ptree);
}

/* virtual override final */
void Star::Resolve()
{
    Base::ResolveData();
    Orientation::ResolveData();
    BaseDrawable::ResolveData();
    BaseSpaceEntity::ResolveData();
    BasePlanet::ResolveData();
    Star::ResolveData();
}



Star* GetNewStar()
{
    Star* star = new Star(0);
    Mesh* mesh = MeshCollector::Instance().GetMeshByTypeId(TYPE::MESH::SPHERE_ID);

    LifeData data_life;
    data_life.armor = 1000000;

    PlanetData star_data;
    star_data.orbit_center  = glm::vec3(0, 0, DEFAULT_ENTITY_ZPOS);
    star_data.radius_A      = 0;
    star_data.radius_B      = 0;
    star_data.orbit_phi_inD = 0;
    star_data.speed         = 0;

    TextureOb* texOb = TextureManager::Instance().GetRandomTextureOb(TYPE::TEXTURE::STAR_ID);

    star->SetPlanetData(star_data);
    star->SetLifeData(data_life);
    float scale_comp = getRandInt(100, 200);
    glm::vec3 scale(scale_comp, scale_comp, scale_comp);
    star->SetRenderData(mesh, texOb, scale);

    star->CalcColor();

    return star;
}
