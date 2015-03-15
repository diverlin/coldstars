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

#include "BlackHole.hpp"
#include "../common/constants.hpp"
#include <meti/RandUtils.hpp>
#include "../common/Logger.hpp"
#include "../world/starsystem.hpp"

BlackHole::BlackHole(int id)
{        
    setId(id);
    setTypeId(TYPE::ENTITY::BLACKHOLE_ID);
    
    setMass(meti::getRandInt(1000, 4000));
}

/* virtual */
BlackHole::~BlackHole() 
{
    #if CREATEDESTROY_LOG_ENABLED == 1
    Logger::Instance().Log("___::~BlackHole("+std::to_string(id())+")");
    #endif
    
    //delete shockwave;
} 
 
void BlackHole::setCenter(const glm::vec3& center) { setCenter(center); /*shockwave->setCenter(meti::vec2(center));*/ }
         
void BlackHole::UpdateInSpace(int time, bool show_effect)
{
    checkDeath(show_effect);

    if (time > 0)
    {
        setCenter(center()+meti::getRandXYVec3f(1, 2, 0));
//        shockwave->setCenter(meti::vec2(center()));
    
        dataLife().life_time--;
        if (dataLife().life_time < 0)
        {
            //scale -= 0.1;
            //if (scale < 1.0)
            {
                dataLife().is_alive = false;
            }
        }
    }

//    shockwave->Update();
}

//void BlackHole::UpdateInfo()
//{
//    GetInfo().clear();

//    GetInfo().addTitleStr("BLACKHOLE");

//    GetInfo().addNameStr("id:");         GetInfo().addValueStr(std::to_string(id()));
//    GetInfo().addNameStr("mass:");       GetInfo().addValueStr(std::to_string(mass()));
//    GetInfo().addNameStr("pos:");        GetInfo().addValueStr( meti::str(center()) );
//}
          
void BlackHole::SaveData(boost::property_tree::ptree& save_ptree, const std::string& root) const
{
    #if SAVELOAD_LOG_ENABLED == 1
    Logger::Instance().Log(" BlackHole("+std::to_string(id())+")::SaveData", SAVELOAD_LOG_DIP);
    #endif
}

void BlackHole::LoadData(const boost::property_tree::ptree& load_ptree)
{
    #if SAVELOAD_LOG_ENABLED == 1
    Logger::Instance().Log(" BlackHole("+std::to_string(id())+")::LoadData", SAVELOAD_LOG_DIP);
    #endif
}

void BlackHole::ResolveData()
{
    #if SAVELOAD_LOG_ENABLED == 1
    Logger::Instance().Log(" BlackHole("+std::to_string(id())+")::ResolveData", SAVELOAD_LOG_DIP);
    #endif
    
    starsystem()->Add(this, data_unresolved_Orientation.center); 
}
 
/*virtual*/
void BlackHole::Save(boost::property_tree::ptree& save_ptree) const
{
    std::string root = "blackhole." + std::to_string(id())+".";

    Base::SaveData(save_ptree, root);
    //Orientation::SaveData(save_ptree, root);
//    BaseDrawable::SaveData(save_ptree, root);
    SpaceObject::SaveData(save_ptree, root);
    Planetoid::SaveData(save_ptree, root);
    BlackHole::SaveData(save_ptree, root);
}

/*virtual*/        
void BlackHole::Load(const boost::property_tree::ptree& load_ptree)
{
    Base::LoadData(load_ptree);
 //   Orientation::LoadData(load_ptree);
//    BaseDrawable::LoadData(load_ptree);
    SpaceObject::LoadData(load_ptree);
    Planetoid::LoadData(load_ptree);
    BlackHole::LoadData(load_ptree);
}
    
/*virtual*/    
void BlackHole::Resolve()
{
    Base::ResolveData();
   // Orientation::ResolveData();
//    BaseDrawable::ResolveData();
    SpaceObject::ResolveData();
    Planetoid::ResolveData();
    BlackHole::ResolveData();
}
