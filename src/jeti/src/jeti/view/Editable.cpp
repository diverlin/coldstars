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


#include "Editable.hpp"

#include <jeti/Render.hpp>

namespace jeti {
namespace view {

Editable::Editable(Mesh* mesh, control::Material* material)
    :
      Base(mesh, material)
{
    m_controlMove = new Base(mesh, material);
    m_controlRotate = new Base(mesh, material);
    m_controlSizeX = new Base(mesh, material);
    m_controlSizeY = new Base(mesh, material);

    m_controls.push_back(m_controlMove);
    m_controls.push_back(m_controlRotate);
    m_controls.push_back(m_controlSizeX);
    m_controls.push_back(m_controlSizeY);

    glm::vec3 control_size(30.f, 30.f, 0.f);// = 0.2f*size();
    for (Base* control: m_controls) {
        control->setSize(control_size);
    }
}

Editable::~Editable()
{
    for (Base* control: m_controls) {
        delete control;
    }
}

Base* Editable::collisionWithControls(const glm::vec2& cursorPos) const
{
    for (Base* control: m_controls) {
        if (control->isPointInsideShape(cursorPos)) {
            return control;
        }
    }

    return nullptr;
}

void Editable::update()
{
    Base::update();

    m_controlMove->setPosition(position());
    m_controlSizeX->setPosition(position()+glm::vec3(radius(), 0.0f, 0.0f));
    m_controlSizeY->setPosition(position()+glm::vec3(0.0f, radius(), 0.0f));
    m_controlRotate->setPosition(position()+glm::vec3(-radius()/1.4f, radius()/1.4f, 0.0f));

    for (Base* control: m_controls) {
        control->update();
    }
}

void Editable::draw(const jeti::Render& render) const
{
    render.draw(_mesh(), _material(), modelMatrix());
    for (Base* control: m_controls) {
        control->draw(render);
    }
}

} // namespace view
} // namespace jeti
