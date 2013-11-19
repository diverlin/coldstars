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
    render.RenderMeshLight(GetMesh(), GetTextureOb(), GetActualModelMatrix());
}
    
void BlackHole::Render_OLD(const Renderer& render)
{
    render.RenderMeshGeometry(GetMesh(), GetTextureOb(), GetActualModelMatrix());    
}
     
void BlackHole::SaveDataUniqueBlackHole(boost::property_tree::ptree& save_ptree, const std::string& root) const
{
    #if SAVELOAD_LOG_ENABLED == 1
    Logger::Instance().Log(" BlackHole("+int2str(GetId())+")::SaveDataUniqueBlackHole", SAVELOAD_LOG_DIP);
    #endif
}

void BlackHole::LoadDataUniqueBlackHole(const boost::property_tree::ptree& load_ptree)
{
    #if SAVELOAD_LOG_ENABLED == 1
    Logger::Instance().Log(" BlackHole("+int2str(GetId())+")::LoadDataUniqueBlackHole", SAVELOAD_LOG_DIP);
    #endif
}

void BlackHole::ResolveDataUniqueBlackHole()
{
    #if SAVELOAD_LOG_ENABLED == 1
    Logger::Instance().Log(" BlackHole("+int2str(GetId())+")::ResolveDataUniqueBlackHole", SAVELOAD_LOG_DIP);
    #endif
    
    GetStarSystem()->Add(this, data_unresolved_Orientation.center); 
}
 
/*virtual*/
void BlackHole::SaveData(boost::property_tree::ptree& save_ptree) const
{
    std::string root = "blackhole." + int2str(GetId())+".";
    Base::Save(save_ptree, root);
    Orientation::Save(save_ptree, root);
    BaseDrawable::Save(save_ptree, root);
    SaveDataUniqueBaseSpaceEntity(save_ptree, root);
    SaveDataUniqueBasePlanet(save_ptree, root);
    SaveDataUniqueBlackHole(save_ptree, root);
}

/*virtual*/        
void BlackHole::LoadData(const boost::property_tree::ptree& load_ptree)
{
    Base::Load(load_ptree);
    Orientation::Load(load_ptree);
    BaseDrawable::Load(load_ptree);
    LoadDataUniqueBaseSpaceEntity(load_ptree);
    LoadDataUniqueBasePlanet(load_ptree);
    LoadDataUniqueBlackHole(load_ptree);
}
    
/*virtual*/    
void BlackHole::ResolveData()
{
    Base::Resolve();
    Orientation::Resolve();
    BaseDrawable::Resolve();
    ResolveDataUniqueBaseSpaceEntity();
    ResolveDataUniqueBasePlanet();
    ResolveDataUniqueBlackHole();
}
