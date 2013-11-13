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

#include <common/Orientation.hpp>
#include <common/Logger.hpp>

Orientation::Orientation()
:
m_IsUpdated(false)
{
    m_OrientOrigin = glm::vec3(0.0f, 0.0f, 1.0f);
    m_Orient       = glm::vec3(0.0f, 0.0f, 1.0f); 
}

/* virtual */
Orientation::~Orientation()
{
    #if CREATEDESTROY_LOG_ENABLED == 1
    Logger::Instance().Log("___::~Orientation("+int2str(GetId())+")");
    #endif
}

void Orientation::UpdateOrientation()
{
    if (m_IsUpdated == false)
    {   
        //float angle_radian = m_Angle.z/RADIAN_TO_DEGREE_RATE;
        
        //m_Axis.x = cos(angle_radian);
        //m_Axis.y = sin(angle_radian);
        //m_Axis.z = 0.0; 
        
        //m_Points.Update(m_Center, m_Angle, m_Size, m_Axis);
        
        m_IsUpdated = true;
    }
            
}        

void Orientation::SaveDataUniqueOrientation(boost::property_tree::ptree& save_ptree, const std::string& root) const
{
    #if SAVELOAD_LOG_ENABLED == 1
    Logger::Instance().Log(" Orientation("+int2str(GetId())+")::SaveDataUniqueOrientation", SAVELOAD_LOG_DIP);
    #endif
        
    save_ptree.put(root+"data_unresolved_Orientation.center.x", m_Center.x);
    save_ptree.put(root+"data_unresolved_Orientation.center.y", m_Center.y);
    save_ptree.put(root+"data_unresolved_Orientation.center.z", m_Center.z);
    
    save_ptree.put(root+"data_unresolved_Orientation.orient.x", m_Orient.x);
    save_ptree.put(root+"data_unresolved_Orientation.orient.y", m_Orient.y);
    save_ptree.put(root+"data_unresolved_Orientation.orient.z", m_Orient.z);
        
}

void Orientation::LoadDataUniqueOrientation(const boost::property_tree::ptree& load_ptree)
{
    #if SAVELOAD_LOG_ENABLED == 1
    Logger::Instance().Log(" Orientation("+int2str(GetId())+")::LoadDataUniqueOrientation", SAVELOAD_LOG_DIP);
    #endif
        
    data_unresolved_Orientation.center.x = load_ptree.get<float>("data_unresolved_Orientation.center.x");
    data_unresolved_Orientation.center.y = load_ptree.get<float>("data_unresolved_Orientation.center.y");
    data_unresolved_Orientation.center.z = load_ptree.get<float>("data_unresolved_Orientation.center.y");
    
    data_unresolved_Orientation.orient.x = load_ptree.get<float>("data_unresolved_Orientation.orient.x");
    data_unresolved_Orientation.orient.y = load_ptree.get<float>("data_unresolved_Orientation.orient.y");
    data_unresolved_Orientation.orient.z = load_ptree.get<float>("data_unresolved_Orientation.orient.z");
}

void Orientation::ResolveDataUniqueOrientation()
{
    #if SAVELOAD_LOG_ENABLED == 1
    Logger::Instance().Log(" Orientation("+int2str(GetId())+")::ResolveDataUniqueOrientation", SAVELOAD_LOG_DIP);
    #endif
}
