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

#include "BaseView.hpp"

namespace control {
class Planet;
} // namespace control

namespace view {

class Planet : public Base
{
public:
    Planet(control::Planet*);
    virtual ~Planet() override final;

    void draw(const jeti::Renderer&) const override final;

//    model::Planet* model() const { return m_model_planet; }
//    descriptor::Planet* descriptor() const { return m_descriptor_planet; }

private:
    control::Planet* m_planet = nullptr;
    //virtual void UpdateInfo() override final;
}; 

} // namespace view







