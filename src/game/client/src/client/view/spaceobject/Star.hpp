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

namespace control {
class Star;
} // namespace descriptor

namespace view {

class Star : public Base
{
public:
    Star(control::Star*);
    ~Star() override final;

    void draw(const jeti::Render& render) const override final;

    control::Star* star() const { return m_star; }

private:
    control::Star* m_star = nullptr;
}; 

} // namespace view




