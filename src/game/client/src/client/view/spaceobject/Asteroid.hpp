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

#include <client/view/BaseView.hpp>

namespace control {
class Asteroid;
} // namespace control

namespace view {

class Asteroid : public Base
{
public:
    Asteroid(control::Asteroid*);
    virtual ~Asteroid() override final;

//    model::Asteroid* model() const  { return m_asteroid->model(); }
//    descriptor::Asteroid* descriptor() const  { return m_asteroid->descriptor(); }

    void draw(const jeti::Renderer& render) const;

private:
    control::Asteroid* m_asteroid = nullptr;
    //        virtual void UpdateInfo() override final;
}; 

} // namespace view
