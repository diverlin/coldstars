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

#include <jeti/BaseView.hpp>


namespace model {
class Asteroid;
} // namespace model

namespace view {

class Asteroid : public jeti::view::Base
{
    public:
        Asteroid(model::Asteroid*);
        virtual ~Asteroid() override final;

    private:
        model::Asteroid* model() const  { return m_model_asteroid; }
        model::Asteroid* m_model_asteroid = nullptr;
//        virtual void UpdateInfo() override final;
}; 

} // namespace view

