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

#include <glm/glm.hpp>

namespace jeti {

class Point;
class Base;
class Render;

namespace particlesystem {
class Jet;
} // namespace aprticlesystem

} // namespace jeti

namespace view {
namespace effect {

class Jet
{
public:
    Jet(jeti::Base*, const meti::vec3&, float);
    ~Jet();

    void draw(const jeti::Render&);

private:
    jeti::Base* m_parent = nullptr;
    jeti::Point* m_point = nullptr;
    jeti::particlesystem::Jet* m_particlesystem = nullptr;
}; 

} // namespace effect
} // namespace view

