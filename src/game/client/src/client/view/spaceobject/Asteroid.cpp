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

#include "Asteroid.hpp"

#include <core/spaceobject/Asteroid.hpp>
#include <core/model/spaceobject/Asteroid.hpp>

#include <jeti/Render.hpp>

namespace view {

Asteroid::Asteroid(control::Asteroid* asteroid)
    :
      Base(asteroid)
    , m_control(asteroid)
{   
    setOrientation(asteroid);
}

Asteroid::~Asteroid()
{}

/* virtual override final */
//void AsteroidDrawable::UpdateInfo()
//{
//    m_Info.clear();

//    m_Info.addTitleStr("ASTEROID");
//    m_Info.addNameStr("id/ss_id:");    m_Info.addValueStr(std::to_string(id()) + " / " + std::to_string(starsystem()->id()));
//    m_Info.addNameStr("armor:");       m_Info.addValueStr(std::to_string(dataLife().armor));
//    m_Info.addNameStr("mass:");        m_Info.addValueStr(std::to_string(mass()));
//    m_Info.addNameStr("speed x 100:"); m_Info.addValueStr(std::to_string(int(GetDataPlanet().speed*100)));
//    m_Info.addNameStr("pos:");         m_Info.addValueStr( str(center()) );
//}

void Asteroid::draw(const jeti::Render& render) const
{
    render.draw(_mesh(), _material(), _modelMatrix());

    //    for (BaseDecor* decor : m_Decorations) {
//        decor->Render(render, center());
//    }
}


} // namespace view
