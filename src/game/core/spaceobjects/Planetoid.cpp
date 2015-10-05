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


#include "Planetoid.hpp"

//#include <jeti/Render.hpp>

#include <ceti/Logger.hpp> 
//#include <ceti/StringUtils.hpp>


Planetoid::Planetoid()
{}

/* virtual */
Planetoid::~Planetoid()
{
    Logger::Instance().Log("___::~Planetoid("+std::to_string(id())+")");
}

void Planetoid::BindParent(const SpaceObject* const parent, int it)
{
    setParent(parent);
    CreateOrbit();
    m_Orbit.SetIt(it);
    UpdatePosition();
}
        
void Planetoid::CreateOrbit()
{
    m_Orbit.CalcPath(m_PlanetDescriptor.radius_A, m_PlanetDescriptor.radius_B, m_PlanetDescriptor.speed, m_PlanetDescriptor.orbit_phi_inD, m_PlanetDescriptor.clockwise);
}

/* virtual */
void Planetoid::postDeathUniqueEvent(bool)  
{}

void Planetoid::UpdatePosition()
{
    m_Orbit.UpdatePosition();  
    if (parent() == nullptr) {
        setCenter(m_Orbit.GetPosition());
    } else {
        setCenter(parent()->center() + m_Orbit.GetPosition());
    }
}

///* virtual override final */
//void Planetoid::RenderStuffWhenFocusedInSpace(const jeti::Renderer& render)
//{
//    m_Orbit.DrawPath(render);
//}

void Planetoid::SaveData(boost::property_tree::ptree& save_ptree, const std::string& root) const
{
    //Logger::Instance().Log(" Planetoid("+std::to_string(id())+")::SaveData", SAVELOAD_LOG_DIP);
    
    save_ptree.put(root+"data.m_Orbit_center.x", m_PlanetDescriptor.orbit_center.x);
    save_ptree.put(root+"data.m_Orbit_center.y", m_PlanetDescriptor.orbit_center.y);
    save_ptree.put(root+"data.radius_A", m_PlanetDescriptor.radius_A);
    save_ptree.put(root+"data.radius_B", m_PlanetDescriptor.radius_B);
    save_ptree.put(root+"data.m_Orbit_phi_inD", m_PlanetDescriptor.orbit_phi_inD);
    save_ptree.put(root+"data.speed", m_PlanetDescriptor.speed);
    save_ptree.put(root+"data.clockwise", m_PlanetDescriptor.clockwise);
    
    save_ptree.put(root+"unresolved.orbit_it", m_Orbit.GetIt());
}

void Planetoid::LoadData(const boost::property_tree::ptree& load_ptree)
{
    //Logger::Instance().Log(" Planetoid("+std::to_string(id())+")::LoadData", SAVELOAD_LOG_DIP);
    
    m_PlanetDescriptor.orbit_center.x = load_ptree.get<float>("data.orbit_center.x");
    m_PlanetDescriptor.orbit_center.y = load_ptree.get<float>("data.orbit_center.y");
    m_PlanetDescriptor.radius_A = load_ptree.get<float>("data.radius_A");
    m_PlanetDescriptor.radius_B = load_ptree.get<float>("data.radius_B");
    m_PlanetDescriptor.orbit_phi_inD = load_ptree.get<float>("data.orbit_phi_inD");
    m_PlanetDescriptor.speed = load_ptree.get<float>("data.speed");
    m_PlanetDescriptor.clockwise = load_ptree.get<bool>("data.clockwise");
    
    data_unresolved_Planetoid.orbit_it = load_ptree.get<int>("unresolved.orbit_it");
}

void Planetoid::ResolveData()
{
    //Logger::Instance().Log(" Planetoid("+std::to_string(id())+")::ResolveData", SAVELOAD_LOG_DIP);
}


