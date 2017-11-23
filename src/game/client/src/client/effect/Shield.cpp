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

#include "Shield.hpp"

#include <jeti/Render.hpp>
#include <jeti/Material.hpp>
#include <jeti/view/Base.hpp>

#include <jeti/animation/OpacityAnimation.hpp>

#include <glm/gtx/transform.hpp>

namespace view {
namespace effect {

Shield::Shield(jeti::view::Base* parent)
    :
      jeti::view::Base()
{       
    _setParent(parent);
    m_opacityAnimation = new jeti::animation::Opacity(_color().a, 0.02f, 0.5f, 0.95f, 1.5f, true);

    _color().r = 1.0;
    _color().g = 1.0;
    _color().b = 1.0;

    m_scaleMatrix = glm::scale(glm::vec3(1.4f, 1.4f, 1.0f));
}

Shield::~Shield()
{
    delete m_opacityAnimation;
    m_opacityAnimation = nullptr;
}

void Shield::dissipate()
{
    m_opacityAnimation->run();
}

void Shield::update()
{
    m_opacityAnimation->update();
}

void Shield::draw(const jeti::Render& render) const
{
    render.drawQuad(_material(), _parent()->modelMatrix()*m_scaleMatrix, _color());
}

} // namespace effect
} // namespace view

