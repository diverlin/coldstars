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

#include <MyGl.hpp>
#include <Material.hpp>

#include <glm/glm.hpp>

#include <string>
#include <vector>

namespace jeti {

class TextureOb
{
public:
    TextureOb();
    TextureOb(const model::Material& material);
    ~TextureOb();

    int id() const { return m_id; }
    //const glm::vec3 size() const { return glm::vec3(0.5*m_Material.w_slice, 0.5*m_Material.h_slice, 1.0f); }     // ugly
    const glm::vec3 size() const { return glm::vec3(50.0f, 50.0f, 1.0f); }     // ugly

    int frameWidth() const  { return m_model.w_slice; }
    int frameHeight() const { return m_model.h_slice; }

    bool isLoaded() const { return m_isLoaded; }
    void load();
    void unloadFromVRAM();

    int updateAnimationFrame(float);

    const model::Material& model() const { return m_model; }

private:
    int m_id = 0;
    model::Material m_model;

    bool m_isLoaded = false;

    unsigned int m_currentFrame;
    unsigned int m_framesCount;
    float m_lastUpdateTime;
    float m_delay;
    float m_frameNum;

    void __createTextureCoords(int _rows_num, int _columns_num, int _fps);
    void __addTexCoordQuad(float _w_start, float _h_start, float _w_offset, float _h_offset);
};

} // namespace jeti
