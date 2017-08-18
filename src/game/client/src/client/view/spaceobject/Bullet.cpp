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

#include "Bullet.hpp"

#include <core/spaceobject/Bullet.hpp>

#include <client/resources/Utils.hpp>

#include <jeti/Render.hpp>
#include <jeti/particlesystem/Jet.hpp>

namespace view {

Bullet::Bullet(control::Bullet* control)
    :
      Base(control)
    , m_control(control)
{
    setOrientation(control);

    m_driveJet = jeti::particlesystem::genJet(utils::createMaterialByDescriptorType(texture::Type::DISTANTSTAR), 10.0f/*control->collisionRadius()*/);
}

Bullet::~Bullet()
{
    delete m_driveJet;
}

void Bullet::draw(const jeti::Render& render) const
{
    render.draw(_mesh(), _material(), _modelMatrix());

    glm::vec3 pos = m_control->position();
    pos -= m_control->size().x * m_control->direction();
    m_driveJet->setCenter(pos);
    m_driveJet->setDirection(-m_control->direction());
    m_driveJet->update();
    m_driveJet->draw(render);
}

//void Bullet::UpdateInfo()
//{
//    GetInfo().clear();

//    GetInfo().addTitleStr("ROCKET");
//    GetInfo().addNameStr("id/ss_id:");          GetInfo().addValueStr( std::to_string(id()) + " / " + std::to_string(starsystem()->id()) );
//    GetInfo().addNameStr("armor:");             GetInfo().addValueStr( std::to_string(dataLife().armor) );
//    if (m_Target != nullptr)
//    {
//        GetInfo().addNameStr("target_id:");       GetInfo().addValueStr(std::to_string(m_Target->id()));
//    }
//}

} // namespace view
