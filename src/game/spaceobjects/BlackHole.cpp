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
#include "../resources/MeshCollector.hpp"
#include "../common/constants.hpp"
#include "../common/myStr.hpp"
#include <math/rand.hpp>
#include "../common/Logger.hpp"

#include "../common/IdGenerator.hpp"
#include "../resources/TextureManager.hpp"
#include "../world/starsystem.hpp"

BlackHole::BlackHole(int id)
{        
    SetId(id);
    SetTypeId(TYPE::ENTITY::BLACKHOLE_ID);
    
    SetMass(getRandInt(1000, 4000));
}

/* virtual */
BlackHole::~BlackHole() 
{
    #if CREATEDESTROY_LOG_ENABLED == 1
    Logger::Instance().Log("___::~BlackHole("+int2str(GetId())+")");
    #endif
    
    delete shockwave; 
} 
 
void BlackHole::SetCenter(const glm::vec3& center) { SetCenter(center); shockwave->SetCenter(vec3ToVec2(center)); }
         
void BlackHole::UpdateInSpace(int time, bool show_effect)
{
    CheckDeath(show_effect);

    if (time > 0)
    {
        SetCenter(GetCenter()+getRandXYVec3f(1, 2, 0));
        shockwave->SetCenter(vec3ToVec2(GetCenter()));
    
        GetDataLife().life_time--;
        if (GetDataLife().life_time < 0)
        {
            //scale -= 0.1;
            //if (scale < 1.0)
            {
                GetDataLife().is_alive = false;
            }
        }
    }

    shockwave->Update();
}

void BlackHole::UpdateInfo()
{
    GetInfo().clear();

    GetInfo().addTitleStr("BLACKHOLE");

    GetInfo().addNameStr("id:");         GetInfo().addValueStr(int2str(GetId()));
    GetInfo().addNameStr("mass:");       GetInfo().addValueStr(int2str(GetMass()));
    GetInfo().addNameStr("pos:");        GetInfo().addValueStr( str(GetCenter()) );
}
      
void BlackHole::Render_NEW(const Renderer& render)
{
    //alpitodorender render.DrawMeshLight(GetMesh(), GetTextureOb(), GetActualModelMatrix());
}
    
void BlackHole::Render_OLD(const Renderer& render)
{
    //alpitodorender render.DrawMesh(GetMesh(), GetTextureOb(), GetActualModelMatrix());
}
     
void BlackHole::SaveData(boost::property_tree::ptree& save_ptree, const std::string& root) const
{
    #if SAVELOAD_LOG_ENABLED == 1
    Logger::Instance().Log(" BlackHole("+int2str(GetId())+")::SaveData", SAVELOAD_LOG_DIP);
    #endif
}

void BlackHole::LoadData(const boost::property_tree::ptree& load_ptree)
{
    #if SAVELOAD_LOG_ENABLED == 1
    Logger::Instance().Log(" BlackHole("+int2str(GetId())+")::LoadData", SAVELOAD_LOG_DIP);
    #endif
}

void BlackHole::ResolveData()
{
    #if SAVELOAD_LOG_ENABLED == 1
    Logger::Instance().Log(" BlackHole("+int2str(GetId())+")::ResolveData", SAVELOAD_LOG_DIP);
    #endif
    
    GetStarSystem()->Add(this, data_unresolved_Orientation.center); 
}
 
/*virtual*/
void BlackHole::Save(boost::property_tree::ptree& save_ptree) const
{
    std::string root = "blackhole." + int2str(GetId())+".";

    Base::SaveData(save_ptree, root);
    Orientation::SaveData(save_ptree, root);
//    BaseDrawable::SaveData(save_ptree, root);
    BaseSpaceEntity::SaveData(save_ptree, root);
    BasePlanet::SaveData(save_ptree, root);
    BlackHole::SaveData(save_ptree, root);
}

/*virtual*/        
void BlackHole::Load(const boost::property_tree::ptree& load_ptree)
{
    Base::LoadData(load_ptree);
    Orientation::LoadData(load_ptree);
//    BaseDrawable::LoadData(load_ptree);
    BaseSpaceEntity::LoadData(load_ptree);
    BasePlanet::LoadData(load_ptree);
    BlackHole::LoadData(load_ptree);
}
    
/*virtual*/    
void BlackHole::Resolve()
{
    Base::ResolveData();
    Orientation::ResolveData();
//    BaseDrawable::ResolveData();
    BaseSpaceEntity::ResolveData();
    BasePlanet::ResolveData();
    BlackHole::ResolveData();
}
