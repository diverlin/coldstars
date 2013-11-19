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

#include <resources/ShaderCollector.hpp>

#include <render/Render.hpp>
#include <glm/gtx/transform.hpp>

   
Star::Star(int id)
:
m_TextureOffset(0.0),
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

int Star::GetColorId() const { return GetTextureOb().color_id; }

float Star::GetBrightThreshold() const { return GetTextureOb().brightThreshold; }
            
void Star::CalcColor()
{
    SetColor(getColor4fById(GetTextureOb().color_id));
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
    m_TextureOffset += 0.0002;

    if (m_SparkActive == true)
    {
        if (show_effect == true)
        {
            if (m_SparkGrows == true)
            {
                m_DeltaColor += 0.02;
                //scale += 0.2;
                if (m_DeltaColor > 1.0)
                {
                    m_DeltaColor = 1.0;
                    GetStarSystem()->StarSparkEvent(getRandInt(600, 1200));
                    m_SparkGrows = false;
                }
            } 
            else
            {        
                m_DeltaColor -= 0.005;    
                //scale -= 0.05;
                if (m_DeltaColor < 0.0)
                {
                    m_DeltaColor = 0;
                    m_SparkActive = false;
                } 
            }
        }
        else
        {
            GetStarSystem()->StarSparkEvent(getRandInt(600, 1200));
            m_SparkActive = false;
        }
    }

    //UpdateRotation(); // not relevant for render NEW
}    
    
void Star::Render_NEW(const Renderer& render)
{
    render.RenderMeshMultiTextured(GetMesh(), GetTextureOb(), GetActualModelMatrix(), m_TextureOffset);
}
        
void Star::Render_OLD(const Renderer& render)
{    
    glBindTexture(GL_TEXTURE_2D, GetTextureOb().texture);              
    render.RenderMeshGeometry(GetMesh(), GetActualModelMatrix());
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

   
void Star::SaveDataUniqueStar(boost::property_tree::ptree& save_ptree, const std::string& root) const
{
    #if SAVELOAD_LOG_ENABLED == 1
    Logger::Instance().Log(" Star("+int2str(GetId())+")::SaveDataUniqueStar", SAVELOAD_LOG_DIP);
    #endif
    
    save_ptree.put(root+"m_TurnSinceLastSparkCounter", m_TurnSinceLastSparkCounter);
    save_ptree.put(root+"m_TurnSparkThreshold", m_TurnSparkThreshold);
}

void Star::LoadDataUniqueStar(const boost::property_tree::ptree& load_ptree)
{
    #if SAVELOAD_LOG_ENABLED == 1
    Logger::Instance().Log(" Star("+int2str(GetId())+")::LoadDataUniqueStar", SAVELOAD_LOG_DIP);
    #endif
    
    m_TurnSinceLastSparkCounter = load_ptree.get<int>("m_TurnSinceLastSparkCounter");
    m_TurnSparkThreshold = load_ptree.get<int>("m_TurnSparkThreshold");    
}

void Star::ResolveDataUniqueStar()
{
    #if SAVELOAD_LOG_ENABLED == 1
    Logger::Instance().Log(" Star("+int2str(GetId())+")::ResolveDataUniqueStar", SAVELOAD_LOG_DIP);
    #endif
    
    ((StarSystem*)EntityManager::Instance().GetEntityById(data_unresolved_BaseSpaceEntity.starsystem_id))->Add(this);     
}

/* virtual override final */
void Star::SaveData(boost::property_tree::ptree& save_ptree) const
{
    std::string root = "star." + int2str(GetId())+".";
    Base::Save(save_ptree, root);
    Orientation::Save(save_ptree, root);
    BaseDrawable::Save(save_ptree, root);
    BaseSpaceEntity::Save(save_ptree, root);
    SaveDataUniqueBasePlanet(save_ptree, root);
    SaveDataUniqueStar(save_ptree, root);
}

/* virtual override final */
void Star::LoadData(const boost::property_tree::ptree& load_ptree)
{
    Base::Load(load_ptree);
    Orientation::Load(load_ptree);
    BaseDrawable::Load(load_ptree);
    BaseSpaceEntity::Load(load_ptree);
    LoadDataUniqueBasePlanet(load_ptree);
    LoadDataUniqueStar(load_ptree);
}

/* virtual override final */
void Star::ResolveData()
{
    Base::Resolve();
    Orientation::Resolve();
    BaseDrawable::Resolve();
    BaseSpaceEntity::Resolve();
    ResolveDataUniqueBasePlanet();
    ResolveDataUniqueStar();
}
