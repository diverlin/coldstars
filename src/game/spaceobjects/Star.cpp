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

//#include <ceti/StringUtils.hpp>
#include <common/common.hpp>
#include <math/rand.hpp>
#include <common/Logger.hpp>

#include <world/EntityManager.hpp>
#include <world/starsystem.hpp>

#include <jeti/TextureOb.hpp>

#include <glm/gtx/transform.hpp>

#include <meti/RandUtils.hpp>
   
Star::Star(int id)
:
m_DeltaColor(0.0),
m_SparkActive(false),
m_SparkGrows(false),
m_TurnSinceLastSparkCounter(0)
{ 
    SetId(id);
    SetTypeId(TYPE::ENTITY::STAR_ID);

    m_TurnSparkThreshold = meti::getRandInt(STARSPAK_TURN_THRESHOLD_MIN, STARSPAK_TURN_THRESHOLD_MAX);
}
  
/* virtual */  
Star::~Star()
{
    #if CREATEDESTROY_LOG_ENABLED == 1
    Logger::Instance().Log("___::~Star("+std::to_string(GetId())+")");
    #endif    
}


//alpitodorender
/*
int Star::GetColorId() const { return GetTextureOb().GetData().color_id; }

float Star::GetBrightThreshold() const { return GetTextureOb().GetData().brightThreshold; }
            
void Star::CalcColor()
{
    SetColor(getColor4fById(GetTextureOb().GetData().color_id));
}
*/
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
        if (meti::getRandInt(1, 2) == 1)
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
                    GetStarSystem()->StarSparkEvent(meti::getRandInt(600, 1200));
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
            GetStarSystem()->StarSparkEvent(meti::getRandInt(600, 1200));
            m_SparkActive = false;
        }
    }

    //UpdateRotation(); // not relevant for render NEW
}    
    
///* virtual override final */
//void Star::UpdateInfo()
//{
//    GetInfo().clear();
//    GetInfo().addTitleStr("STAR");
//    GetInfo().addNameStr("id/ss_id:");  GetInfo().addValueStr(std::to_string(GetId()) + " / " + std::to_string(GetStarSystem()->GetId()));
//    GetInfo().addNameStr("armor:");     GetInfo().addValueStr(std::to_string(GetDataLife().armor));
//    GetInfo().addNameStr("pos:");       GetInfo().addValueStr( meti::str(GetCenter()) );
//}

/* virtual override final */
void Star::PostDeathUniqueEvent(bool)
{}

   
void Star::SaveData(boost::property_tree::ptree& save_ptree, const std::string& root) const
{
    #if SAVELOAD_LOG_ENABLED == 1
    Logger::Instance().Log(" Star("+std::to_string(GetId())+")::SaveData", SAVELOAD_LOG_DIP);
    #endif
    
    save_ptree.put(root+"m_TurnSinceLastSparkCounter", m_TurnSinceLastSparkCounter);
    save_ptree.put(root+"m_TurnSparkThreshold", m_TurnSparkThreshold);
}

void Star::LoadData(const boost::property_tree::ptree& load_ptree)
{
    #if SAVELOAD_LOG_ENABLED == 1
    Logger::Instance().Log(" Star("+std::to_string(GetId())+")::LoadData", SAVELOAD_LOG_DIP);
    #endif
    
    m_TurnSinceLastSparkCounter = load_ptree.get<int>("m_TurnSinceLastSparkCounter");
    m_TurnSparkThreshold = load_ptree.get<int>("m_TurnSparkThreshold");    
}

void Star::ResolveData()
{
    #if SAVELOAD_LOG_ENABLED == 1
    Logger::Instance().Log(" Star("+std::to_string(GetId())+")::ResolveData", SAVELOAD_LOG_DIP);
    #endif
    
    ((StarSystem*)EntityManager::Instance().GetEntityById(data_unresolved_BaseSpaceEntity.starsystem_id))->Add(this);     
}

/* virtual override final */
void Star::Save(boost::property_tree::ptree& save_ptree) const
{
    std::string root = "star." + std::to_string(GetId())+".";

    Base::SaveData(save_ptree, root);
    Orientation::SaveData(save_ptree, root);
//    BaseDrawable::SaveData(save_ptree, root);
    BaseSpaceEntity::SaveData(save_ptree, root);
    BasePlanet::SaveData(save_ptree, root);
    Star::SaveData(save_ptree, root);
}

/* virtual override final */
void Star::Load(const boost::property_tree::ptree& load_ptree)
{
    Base::LoadData(load_ptree);
    Orientation::LoadData(load_ptree);
//    BaseDrawable::LoadData(load_ptree);
    BaseSpaceEntity::LoadData(load_ptree);
    BasePlanet::LoadData(load_ptree);
    Star::LoadData(load_ptree);
}

/* virtual override final */
void Star::Resolve()
{
    Base::ResolveData();
    Orientation::ResolveData();
//    BaseDrawable::ResolveData();
    BaseSpaceEntity::ResolveData();
    BasePlanet::ResolveData();
    Star::ResolveData();
}
