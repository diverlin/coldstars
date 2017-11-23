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

#include "Jet.hpp"

#include <client/resources/Utils.hpp>

#include <jeti/view/Base.hpp>
#include <jeti/Point.hpp>
#include <jeti/particlesystem/Jet.hpp>

namespace view {
namespace effect {

Jet::Jet(jeti::view::Base* parent, const meti::vec3& positionOrigin, float size)
    :
      m_parent(parent)
    , m_point(new jeti::Point(positionOrigin, parent))
    , m_particlesystem(jeti::particlesystem::genJet(utils::createMaterialByDescriptorType(texture::Type::DISTANTSTAR), size))
{
}

Jet::~Jet()
{
    delete m_point;
    delete m_particlesystem;
}

void Jet::draw(const jeti::Render& render) {
    m_point->update();
    m_particlesystem->setCenter(m_point->position());
    m_particlesystem->setDirection(-m_parent->direction());
    m_particlesystem->update();
    m_particlesystem->draw(render);
}

} // namespace effect
} // namepsace view
