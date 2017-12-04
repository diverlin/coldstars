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


#include "BaseButton.hpp"
#include <common/constants.hpp>

#include <client/session/Shortcuts.hpp>

#include <ceti/Collision.hpp>
#include <jeti/Render.hpp>
#include <jeti/Screen.hpp>

namespace gui {

BaseButton::BaseButton(Type id,
                       Type group,
                       const std::string& info,
                       void (*pAction)(client::Player*),
                       jeti::model::Material* material)
    :
      Base(id, group, info, material),
      m_action(pAction)
{}

BaseButton::~BaseButton()
{}

void BaseButton::press()
{
    _setIsPressed(true);
    shadeOn();
}

void BaseButton::unpress()
{
    _setIsPressed(false);
    shadeOff();
}

/* virtual override */
void BaseButton::resetState()
{
    _setIsPressed(false);
    shadeOff();
}

void BaseButton::LockOn() 
{ 
    _setIsLocked(true);
    fullShadeOn();
};

void BaseButton::LockOff() 
{ 
    _setIsLocked(false);
    shadeOff();
};

void BaseButton::shadeOn()
{
    m_alpha = 0.4f;
}

void BaseButton::fullShadeOn()
{
    m_alpha = 0.05f;
}

void BaseButton::shadeOff()
{
    m_alpha = 1.0f;
}      

/* virtual override */               
void BaseButton::renderInfo(const jeti::Render&) const
{
    jeti::drawColoredTextWithBackground(_info(), 12, box().center(), glm::ivec4(255, 255, 255, 255));
}

/* virtual override */
void BaseButton::_renderUnique(const jeti::Render& render, client::Player*) const
{      
    //setColor4f(1.0f, 1.0f, 1.0f, m_Alpha);
    
    if (_hasTextureOb()) {
        render.drawQuad_HUD(box(), material());
    }
    
    if (m_material_additional) {
        render.drawQuad_HUD(box(), *m_material_additional);
    }
    //setColor4f(1.0f, 1.0f, 1.0f, 1.0f);
    
    if (m_material_mask) {
        render.drawQuad_HUD(box(), *m_material_mask);
    }
    
    if (_label() != "") {
        glm::vec2 pos(box().center().x, box().center().y + box().size().y);
        client::shortcuts::screen()->drawText(_label(), 12, pos);
    }
}

} // namespace gui
