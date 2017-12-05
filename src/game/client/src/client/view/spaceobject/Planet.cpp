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


#include "Planet.hpp"

#include <core/spaceobject/Planet.hpp>
#include <core/model/spaceobject/Planet.hpp>

#include <client/effect/Atmosphere.hpp>
//#include <client/effect/BaseDecor.hpp>

#include <jeti/Render.hpp>

namespace view {

Planet::Planet(control::Planet* planet)
    :
      Base(planet)
    , m_control(planet)
{
    _setOrientation(planet);

    atmosphere = new Atmosphere(this);
    _addChild(atmosphere);
}

/* virtual */
Planet::~Planet()
{  
//    for (BaseDecor* decor : m_Decorations) {
//        delete decor;
//    }
//    m_Decorations.clear();
}

/* virtual override final */
//void Planet::UpdateInfo()
//{
//    GetInfo().clear();
    
//    GetInfo().addTitleStr("PLANET");
//    GetInfo().addNameStr("id/ss_id:");    GetInfo().addValueStr(std::to_string(id()) + " / " + std::to_string(starsystem()->id()));
//    GetInfo().addNameStr("armor:");       GetInfo().addValueStr(std::to_string(dataLife().armor));
//    GetInfo().addNameStr("population:");  GetInfo().addValueStr(std::to_string(m_Population));
//    GetInfo().addNameStr("dock_veh:");    GetInfo().addValueStr(m_Land->GetDockVehicleStr());
//    GetInfo().addNameStr("pos:");         GetInfo().addValueStr( str(center()) );
//}

void Planet::update()
{
    Base::update();
   // for (Base* child: children()) {
//        child->update(this);
  //      child->update();
 //   }
}

void Planet::draw(const jeti::Render& render) const
{
   //render.draw(_mesh(), _material(), modelMatrix());
   //render.drawMeshWithPerlin(_mesh(), material(), modelMatrix());
   //    for (Base* child: children()) {
//        child->draw(render);
//    }
   //render.draw(_mesh(), _material(), modelMatrix());
   //atmosphere->draw(render);
}

} // namespace view
