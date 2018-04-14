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

#include <client/view/Base.hpp>

namespace core {
namespace control {
class Bullet;
} // namespace control
} // namespace core

namespace view {

namespace effect {
class Jet;
} // namespace effect

class Bullet : public Base
{
public:
    Bullet(core::control::Bullet*);
    ~Bullet() final override;

    void draw(const jeti::Render& render) const override final;
    core::control::Bullet* control() { return m_control; }

private:
    core::control::Bullet* m_control = nullptr;
    view::effect::Jet* m_driveJet = nullptr;
    //virtual void UpdateInfo() override final;
};

} // namespace view
