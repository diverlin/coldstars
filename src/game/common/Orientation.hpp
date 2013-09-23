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


#ifndef ORIENTATION_HPP
#define ORIENTATION_HPP

#include <common/Base.hpp>
#include <common/points.hpp>

struct UnresolvedDataUniqueOrientation
{    
    glm::vec3 center;
    glm::vec3 orient; 
};

class Orientation : public Base
{
    public:      
        Orientation();
        virtual ~Orientation() override;

        void SetParentCenter(float x, float y, float z) { m_ParentCenter = glm::vec3(x, y, z); }        
        void SetParentCenter(const glm::vec3& parent_center) { m_ParentCenter = parent_center; }
        
        void SetCenter(float x, float y, float z)    { m_Center = glm::vec3(x, y, z); m_IsUpdated = false; }
        void SetCenter(const glm::vec3& center)   { m_Center = center; m_IsUpdated = false; }
        
        void SetSize(float x, float y, float z) { m_Size = glm::vec3(x, y, z); m_IsUpdated = false; }
        void SetSize(const glm::vec3& size) { m_Size = size; m_IsUpdated = false; }

        void SetOrientationOrigin(const glm::vec3& orient_origin) { m_OrientOrigin = orient_origin; m_IsUpdated = false; }        
        void SetOrientation(const glm::vec3& orient)              { m_Orient = orient; m_IsUpdated = false; }
        
        const glm::vec3& GetOrientOrigin() const { return m_OrientOrigin; }        
        const glm::vec3& GetOrient() const { return m_Orient; }
       
        const glm::vec3& GetCenter() const { return m_Center; }
        const glm::vec3& GetSize()  const { return m_Size; } 
        
        glm::vec3* const GetpCenter() { return &m_Center; }
        const glm::vec3* const GetpParentCenter() { return &m_ParentCenter; }
                        
        Points& GetPoints()          { return m_Points; }  // !!!
           
        float GetCollisionRadius() const  { return m_CollisionRadius; }

        void UpdateOrientation();
                                
    protected:            
        UnresolvedDataUniqueOrientation data_unresolved_Orientation;
        void SaveDataUniqueOrientation(boost::property_tree::ptree&, const std::string&) const;
        void LoadDataUniqueOrientation(const boost::property_tree::ptree&);
        void ResolveDataUniqueOrientation();

        void SetCollisionRadius(float collision_radius) { m_CollisionRadius = collision_radius; }    
                        
    private:
        bool m_IsUpdated;

        float m_CollisionRadius;
                
        glm::vec3 m_Center;                  
        glm::vec3 m_Size;

        glm::vec3 m_OrientOrigin;        
        glm::vec3 m_Orient;
        
        glm::vec3 m_ParentCenter; 

        Points m_Points;
                                
    friend class BaseVehicleBuilder;
};

#endif 
