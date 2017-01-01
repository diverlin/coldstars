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

#include <meti/VectorUtils.hpp>


class SpaceObject;

namespace jeti {
class Renderer;
namespace control {
class Material;
} // namespace control
}

class ShieldEffect
{  
public:
    ShieldEffect();
    ~ShieldEffect();

    void SetTextureOb(jeti::control::Material* textureOb) { this->textureOb = textureOb; };
    void SetAlpha(float alpha) { color.a = alpha; };
    void setParent(SpaceObject*);

    void Update();
    void Render(const jeti::Renderer&, float) const;

private:
    glm::vec4 color;
    glm::vec3 size;

    float alpha_start;
    float d_alpha;

    jeti::control::Material* textureOb;
    SpaceObject* parent;

};

