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

#include "SpaceStation.hpp"
#include <math/rand.hpp>
#include <common/myStr.hpp>
#include <common/Logger.hpp>

#include <world/EntityManager.hpp>
#include <world/starsystem.hpp>

#include <garbage/EntityGarbage.hpp>

#include <dock/Kosmoport.hpp>

#include <effects/Shield.hpp>

#include <slots/ItemSlot.hpp>

#include <pilots/Npc.hpp>

#include <render/Render.hpp>


SpaceStation::SpaceStation(int id)
: 
m_Land(nullptr)
{      
    SetId(id);
    SetTypeId(TYPE::ENTITY::VEHICLE_ID);
    SetSubTypeId(TYPE::ENTITY::SPACESTATION_ID);
}

/* virtual */
SpaceStation::~SpaceStation() 
{
    #if CREATEDESTROY_LOG_ENABLED == 1
    Logger::Instance().Log("___::~SpaceStation("+int2str(GetId())+")");
    #endif
}    
 
/* virtual override final */
void SpaceStation::PutChildsToGarbage() const 
{
    EntityGarbage::Instance().Add(m_Land);
    GetOwnerNpc()->SetAlive(false);
    EntityGarbage::Instance().Add(GetOwnerNpc());
    
    for(unsigned int i=0; i<m_SlotTotal_vec.size(); i++)
    {
        EntityGarbage::Instance().Add(m_SlotTotal_vec[i]);    
    }
}

void SpaceStation::BindLand(BaseLand* land)               
{
    m_Land = land;
    m_Land->SetOwner(this);
}
 
/* virtual override final */          
void SpaceStation::UpdateInSpace(int time, bool show_effect)
{
    CheckDeath(show_effect);
    if (time > 0)
    {
        GetComplexWeapon().Fire(time, GetOwnerNpc()->GetSkills().GetAttackNormalized(), show_effect);
    }
}

/* virtual override final */
void SpaceStation::UpdateInfo()
{
    GetInfo().clear();

    GetInfo().addTitleStr("StarBase" + getEntityTypeStr(GetSubTypeId()));

    GetInfo().addNameStr("id/ss_id:");    GetInfo().addValueStr(int2str(GetId()) + " / " + int2str(GetStarSystem()->GetId()));
    GetInfo().addNameStr("id:");          GetInfo().addValueStr(int2str(GetId()));
    GetInfo().addNameStr("mass:");        GetInfo().addValueStr(int2str(GetMass()));
    GetInfo().addNameStr("pos:");         GetInfo().addValueStr( str(GetCenter()) );
} 

void SpaceStation::UpdateRenderStuff_2D()
{
    //points.update(); 
    GetComplexProtector().GetShieldEffect()->Update();
    
    //if (ableTo.DRIVE == true)
    //{
        //drive_trail->update();
    //}
}

void SpaceStation::RenderInSpace_2D(const Renderer& render, float scale)
{     
    //UpdateRenderStuff_2D();
        
    RenderKorpus(render);
        
    //if (GetDataKorpus().draw_turrels == true)
    //{
        //GetComplexWeapon().RenderTurrels();
    //}
    
    //if (GetComplexProtector().GetProtectorSlot()->GetItem() != nullptr)
    //{
        //RenderShieldEffect(1.0 - GetColor().a); 
        //GetStarSystem()->RestoreSceneColor();
    //}
}

                         
void SpaceStation::RenderInSpace_3D(const Renderer& render, const glm::vec2& scroll_coords, float scale)
{         
    //UpdateRenderAnimation();    
    //RenderMeshLight(scroll_coords, GetStarSystem()->GetColor4f());        
}

void SpaceStation::SaveDataUniqueSpaceStation(boost::property_tree::ptree& save_ptree, const std::string& root) const
{
    #if SAVELOAD_LOG_ENABLED == 1
    Logger::Instance().Log(" SpaceStation("+int2str(GetId())+")::SaveDataUniqueSpaceStation", SAVELOAD_LOG_DIP);
    #endif
}

void SpaceStation::LoadDataUniqueSpaceStation(const boost::property_tree::ptree& load_ptree)
{
    #if SAVELOAD_LOG_ENABLED == 1
    Logger::Instance().Log(" SpaceStation("+int2str(GetId())+")::LoadDataUniqueSpaceStation", SAVELOAD_LOG_DIP);
    #endif
}

void SpaceStation::ResolveDataUniqueSpaceStation()
{
    #if SAVELOAD_LOG_ENABLED == 1
    Logger::Instance().Log(" SpaceStation("+int2str(GetId())+")::ResolveDataUniqueSpaceStation", SAVELOAD_LOG_DIP);
    #endif
}


/* virtual override final */
void SpaceStation::SaveData(boost::property_tree::ptree& save_ptree) const
{
    const std::string root = "spacestation."+int2str(GetId())+".";
    Base::Save(save_ptree, root);
    Orientation::Save(save_ptree, root);
    BaseDrawable::Save(save_ptree, root);
    SaveDataUniqueBaseSpaceEntity(save_ptree, root);
    SaveDataUniqueVehicle(save_ptree, root);
    SaveDataUniqueSpaceStation(save_ptree, root);
}

/* virtual override final */
void SpaceStation::LoadData(const boost::property_tree::ptree& load_ptree)
{
    Base::Load(load_ptree);
    Orientation::Load(load_ptree);
    BaseDrawable::Load(load_ptree);
    LoadDataUniqueBaseSpaceEntity(load_ptree);
    LoadDataUniqueVehicle(load_ptree);
    LoadDataUniqueSpaceStation(load_ptree);
}

/* virtual override final */
void SpaceStation::ResolveData()
{
    Base::Resolve();
    Orientation::Resolve();
    BaseDrawable::Resolve();
    ResolveDataUniqueBaseSpaceEntity();
    ResolveDataUniqueVehicle();
    ResolveDataUniqueSpaceStation();
}
