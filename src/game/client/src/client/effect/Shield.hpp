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

#include <jeti/BaseView.hpp>

#include <glm/glm.hpp>

namespace jeti {

class Render;

namespace animation {
class Opacity;
} // namespace animation

} // namespace jeti

namespace view {
namespace effect {

class Shield : public jeti::Base
{  
public:
    Shield(jeti::Base*);
    ~Shield();

    void dissipate();
    void update();
    void draw(const jeti::Render&) const;

private:
    glm::mat4 m_scaleMatrix;
    jeti::animation::Opacity* m_opacityAnimation = nullptr;
};

} // namespace effect
} // namespace view

