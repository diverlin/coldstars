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
#include <jeti/view/Control.hpp>

#include <jeti/Render.hpp>

namespace jeti {
namespace view {

Editable::Editable(Mesh* mesh, control::Material* material)
    :
      Base(mesh, material)
{
    m_controlMove = new Control(Control::Role::MOVE, mesh, material);
    m_controlRotate = new Control(Control::Role::ROTATE, mesh, material);
    m_controlSizeX = new Control(Control::Role::RESIZEX, mesh, material);
    m_controlSizeY = new Control(Control::Role::RESIZEY, mesh, material);
    m_controlScale = new Control(Control::Role::SCALE, mesh, material);

    m_controls.push_back(m_controlMove);
    m_controls.push_back(m_controlRotate);
    m_controls.push_back(m_controlSizeX);
    m_controls.push_back(m_controlSizeY);
    m_controls.push_back(m_controlScale);

    glm::vec3 control_size(m_controlSize, m_controlSize, 0.0f);
    for (Control* control: m_controls) {
        control->setSize(control_size);
    }
}

Editable::~Editable()
{
    for (Control* control: m_controls) {
        delete control;
    }
}

Control* Editable::collisionWithControls(const glm::vec2& cursorPos) const
{
    for (Control* control: m_controls) {
        if (control->isPointInsideCircle(cursorPos)) {
            return control;
        }
    }

    return nullptr;
}

void Editable::update()
{
    Base::update();

    float w = size().x - m_controlSize;
    float h = size().y - m_controlSize;

    float r = 0.5f*radius();
    m_controlMove->setPosition(position());
    m_controlSizeX->setPosition(position()+glm::vec3(w, 0.0f, 0.0f));
    m_controlSizeY->setPosition(position()+glm::vec3(0.0f, h, 0.0f));
    m_controlRotate->setPosition(position()+direction()*r);
    m_controlScale->setPosition(position()+glm::vec3(-r, r, 0.0f));

    for (Control* control: m_controls) {
        control->update();
    }
}

void Editable::draw(const jeti::Render& render) const
{
    render.draw(_mesh(), _material(), modelMatrix());
    for (Control* control: m_controls) {
        control->draw(render);
    }
}

} // namespace view
} // namespace jeti
