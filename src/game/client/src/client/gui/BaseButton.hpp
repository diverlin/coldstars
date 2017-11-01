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

#include "BaseGuiElement.hpp"

namespace jeti {
class Render;
}

namespace gui {

class BaseButton : public Base
{
public:
    BaseButton(gui::type, gui::type, const std::string&,void (*pAction)(client::Player*) = nullptr, jeti::control::Material* textureOb = nullptr);
    virtual ~BaseButton();

    void SetTextureObAdditional(jeti::control::Material* textureOb_additional) { m_TextureOb_additional = textureOb_additional; }
    void SetTextureObMask(jeti::control::Material* textureOb_mask) { m_textureOb_mask = textureOb_mask; }

    //void SetCallBack(void (*funcp)()) { this->pAction = pAction; }
    void LockOn();
    void LockOff();

    virtual void resetState() override;

    virtual void renderInfo(const jeti::Render&) const override;
    virtual void _renderUnique(const jeti::Render&, client::Player*) const override;

protected:
    float m_alpha;

    jeti::control::Material* m_TextureOb_additional;
    jeti::control::Material* m_textureOb_mask;

    void (*m_action)(client::Player*);

    void fullShadeOn();
    void ShadeOn();
    void shadeOff();
};

} // namespace gui
