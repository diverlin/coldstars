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

#include "Base.hpp"

namespace jeti {
namespace view {

class Control;

class Editable : public Base
{
public:
    Editable(Mesh*, control::Material*);
    ~Editable() override;

    void update() override;
    void draw(const jeti::Render& render) const override;

    Control* collisionWithControls(const glm::vec2&) const;

private:
    float m_controlSize = 10.0f;
    Control* m_controlMove = nullptr;
    Control* m_controlRotate = nullptr;
    Control* m_controlSizeX = nullptr;
    Control* m_controlSizeY = nullptr;
    Control* m_controlScale = nullptr;
    std::vector<Control*> m_controls;
};

} // namespace view
} // namespace jeti

