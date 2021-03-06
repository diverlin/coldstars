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


#include "BasePlanet.hpp"

#include <render/Render.hpp>

#include <common/Logger.hpp> 
#include <common/myStr.hpp>


BasePlanet::BasePlanet()
{}

/* virtual */
BasePlanet::~BasePlanet()
{
    #if CREATEDESTROY_LOG_ENABLED == 1
    Logger::Instance().Log("___::~BasePlanet("+int2str(GetId())+")");
    #endif
}

void BasePlanet::BindParent(const BaseSpaceEntity* const parent, int it)
{
    SetParent(parent);
    CreateOrbit();
    m_Orbit.SetIt(it);
    UpdatePosition();
}
        
void BasePlanet::CreateOrbit()
{
    m_Orbit.CalcPath(m_DataPlanet.radius_A, m_DataPlanet.radius_B, m_DataPlanet.speed, m_DataPlanet.orbit_phi_inD, m_DataPlanet.clockwise);
}

/* virtual */
void BasePlanet::PostDeathUniqueEvent(bool)  
{}

void BasePlanet::UpdatePosition()
{
    m_Orbit.UpdatePosition();  
    if (GetParent() == nullptr)
    {
        SetCenter(m_Orbit.GetPosition());
    }
    else
    {
        SetCenter(GetParent()->GetCenter() + m_Orbit.GetPosition());
    }
}

/* virtual override final */
void BasePlanet::RenderStuffWhenFocusedInSpace(const Renderer& render)
{
    m_Orbit.DrawPath(render);
}

void BasePlanet::SaveData(boost::property_tree::ptree& save_ptree, const std::string& root) const
{
    #if SAVELOAD_LOG_ENABLED == 1
    Logger::Instance().Log(" BasePlanet("+int2str(GetId())+")::SaveData", SAVELOAD_LOG_DIP);
    #endif
    
    save_ptree.put(root+"data.m_Orbit_center.x", m_DataPlanet.orbit_center.x);
    save_ptree.put(root+"data.m_Orbit_center.y", m_DataPlanet.orbit_center.y);
    save_ptree.put(root+"data.radius_A", m_DataPlanet.radius_A);
    save_ptree.put(root+"data.radius_B", m_DataPlanet.radius_B);
    save_ptree.put(root+"data.m_Orbit_phi_inD", m_DataPlanet.orbit_phi_inD);
    save_ptree.put(root+"data.speed", m_DataPlanet.speed);
    save_ptree.put(root+"data.clockwise", m_DataPlanet.clockwise);
    
    save_ptree.put(root+"unresolved.orbit_it", m_Orbit.GetIt());
}

void BasePlanet::LoadData(const boost::property_tree::ptree& load_ptree)
{
    #if SAVELOAD_LOG_ENABLED == 1
    Logger::Instance().Log(" BasePlanet("+int2str(GetId())+")::LoadData", SAVELOAD_LOG_DIP);
    #endif
    
    m_DataPlanet.orbit_center.x = load_ptree.get<float>("data.orbit_center.x");    
    m_DataPlanet.orbit_center.y = load_ptree.get<float>("data.orbit_center.y");    
    m_DataPlanet.radius_A = load_ptree.get<float>("data.radius_A");    
    m_DataPlanet.radius_B = load_ptree.get<float>("data.radius_B");
    m_DataPlanet.orbit_phi_inD = load_ptree.get<float>("data.orbit_phi_inD");
    m_DataPlanet.speed = load_ptree.get<float>("data.speed");
    m_DataPlanet.clockwise = load_ptree.get<bool>("data.clockwise");
    
    data_unresolved_BasePlanet.orbit_it = load_ptree.get<int>("unresolved.orbit_it");
}

void BasePlanet::ResolveData()
{
    #if SAVELOAD_LOG_ENABLED == 1
    Logger::Instance().Log(" BasePlanet("+int2str(GetId())+")::ResolveData", SAVELOAD_LOG_DIP);
    #endif
}


