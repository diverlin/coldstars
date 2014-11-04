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

#include <string>
#include <vector>
#include <MyGl.hpp>
#include <glm/glm.hpp>
#include <Material.hpp>

namespace jeti {

class TextureOb
{
    public:
        TextureOb(const Material& material);
        ~TextureOb();

        const glm::vec3 GetSize() const { return glm::vec3(0.5*m_Material.w_slice, 0.5*m_Material.h_slice, 1.0f); }     // ugly

        int GetFrameWidth() const  { return m_Material.w_slice; }
        int GetFrameHeight() const { return m_Material.h_slice; }
        
        bool GetIsLoaded() const { return m_IsLoaded; }
        void Load();
        void RemoveFromVRAM();

        int UpdateAnimationFrame(float);

        const Material& GetMaterial() const { return m_Material; }

    private:
        Material m_Material;

        bool m_IsLoaded;

        unsigned int m_CurrentFrame;
        unsigned int m_FramesCount; 
        float m_LastUpdateTime;
        float m_Delay;
        float m_Fps; 
                    
        void CreateTextureCoords(int _rows_num, int _columns_num, int _fps);
        void AddTexCoordQuad(float _w_start, float _h_start, float _w_offset, float _h_offset);
};

void loadToVRAM(const std::string&, GLuint&, int&, int&);
            
}
