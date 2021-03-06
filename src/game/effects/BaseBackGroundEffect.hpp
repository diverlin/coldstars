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

#ifndef BASEBACKGROUNDEFFECT_HPP
#define BASEBACKGROUNDEFFECT_HPP

#include <boost/property_tree/ptree.hpp>
#include <glm/glm.hpp>

class TextureOb;
class Mesh;


class BaseBackGroundEffect
{
    public:
        BaseBackGroundEffect();
        ~BaseBackGroundEffect();

        void SetTextureOb(TextureOb* textureOb, const glm::vec3& scale_factor = glm::vec3(1.0, 1.0, 1.0));

        void SetCenter(const glm::vec3& center)     { m_Center = center; }        
        void SetSize(const glm::vec3& size)         { m_Size = size; }

        void SetAngle(float angle)              { m_Angle = angle; }                       
        void SetDeltaAngle(float delta_angle)   { m_DeltaAngle = delta_angle; }

        const glm::vec3& GetCenter() const { return m_Center; }
        const TextureOb& GetTextureOb() const { return *m_TextureOb; }

        const glm::vec4& GetColor() const { return m_Color; }

        const Mesh& GetMesh() const { return *m_Mesh; } 

        const glm::mat4& GetActualModelMatrix();
                
    protected:
        unsigned long int id;
        
        static unsigned long int counter;
        
        TextureOb* m_TextureOb;
        std::string m_TextureObPath;
        
        glm::vec3 m_Center;
        glm::vec3 m_Size;  
        glm::vec4 m_Color; 
        
        float m_Angle;
        float m_DeltaAngle;
           
        glm::mat4 m_Mm;     
        glm::mat4 m_Tm;
        glm::mat4 m_Rm;
        glm::mat4 m_Sm;

        Mesh* m_Mesh;
        
        void SaveData(boost::property_tree::ptree&, const std::string&) const;        
        void LoadData(const boost::property_tree::ptree&);
        void ResolveData();
    
};

#endif 

