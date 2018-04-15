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

#include "Atmosphere.hpp"  
#include <jeti/Render.hpp>

namespace view {
namespace effect {

Atmosphere::Atmosphere(Base* parent)
{
    _setParent(parent);
    setColor(glm::vec4(1.0f, 1.0f, 1.0f, 0.5f));

    glm::vec3 size = 1.1f * _parent()->size();
    setSize(size);
}

Atmosphere::~Atmosphere()
{}
 
void Atmosphere::draw(const jeti::Render& render) const
{
    render.drawMeshWithLight(mesh(),
                             material(),
                             modelMatrix());

//    render.drawMeshWithOnlyPerlin(mesh(),
//                                  modelMatrix(),
//                                  _color());
}

} // namespace effect
} // namespace view