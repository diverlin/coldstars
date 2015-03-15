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


#pragma once

#include <boost/property_tree/ptree.hpp>
#include <ceti/points.hpp>

namespace ceti {

struct UnresolvedDataOrientation
{    
    glm::vec3 center;
    glm::vec3 direction; 
};

class Orientation
{
    public:      
        Orientation();
        virtual ~Orientation();

        void setParentCenter(float x, float y, float z) { m_parentCenter = glm::vec3(x, y, z); }
        void setParentCenter(const glm::vec3& parent_center) { m_parentCenter = parent_center; }
        
        void setCenter(float x, float y, float z)    { m_center = glm::vec3(x, y, z); m_isUpdated = false; }
        void setCenter(const glm::vec3& center)   { m_center = center; m_isUpdated = false; }
        
        void setSize(float x, float y, float z) { m_size = glm::vec3(x, y, z); m_isUpdated = false; }
        void setSize(const glm::vec3& size) { m_size = size; m_isUpdated = false; }
    
        const glm::vec3& direction() const { return m_direction; }
       
        const glm::vec3& center() const { return m_center; }
        const glm::vec3& size()  const { return m_size; }
        
        glm::vec3* const pCenter() { return &m_center; }
        const glm::vec3* const pParentCenter() { return &m_parentCenter; }
                        
        ceti::Points& points()          { return m_points; }  // depr !!!
           
        float collisionRadius() const  { return m_collisionRadius; }

        void updateOrientation();     //depr

        void setDirection(const glm::vec3& direction)   { m_direction = glm::normalize(direction); m_isUpdated = false; }
        void setCollisionRadius(float collision_radius) { m_collisionRadius = collision_radius; }

    protected:            
        UnresolvedDataOrientation data_unresolved_Orientation;
        void SaveData(boost::property_tree::ptree&, const std::string&) const;
        void LoadData(const boost::property_tree::ptree&);
        void ResolveData();

    private:
        bool m_isUpdated;

        float m_collisionRadius;
                
        glm::vec3 m_center;
        glm::vec3 m_size;
     
        glm::vec3 m_direction;
        
        glm::vec3 m_parentCenter;

        ceti::Points m_points;
};

} // namespace ceti
