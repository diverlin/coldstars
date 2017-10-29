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
#include <ceti/rect.hpp> // to be removed

namespace control {
class SpaceObject;
class Vehicle;
} // namespace model

namespace jeti {
class Render;
}

class GuiRadar : public BaseGuiElement
{
public:
    GuiRadar();
    virtual ~GuiRadar() override final;
    
    const ceti::Rect& GetRect() const { return m_rect; };
    void Resize(int, int);

    void ResetData();

    void Add(control::SpaceObject*);
    void AddIfWithinRadarRange(control::SpaceObject*, control::Vehicle*);

    virtual void _updateUnique(client::Player*) override final;

    virtual void _renderUnique(const jeti::Render&, client::Player*) const override final;

private:
    float scale;

    jeti::control::Material* m_textureOb_background = nullptr;
    jeti::control::Material* m_textureOb_bar = nullptr;
    jeti::control::Material* m_textureOb_screenrect = nullptr;
    jeti::control::Material* m_textureOb_range = nullptr;

    ceti::Rect m_rect;
    ceti::Rect m_screenrect;

    std::vector<control::SpaceObject*> m_entities;
};

