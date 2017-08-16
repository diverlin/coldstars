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

#include "WormHole.hpp"

#include <core/spaceobject/WormHole.hpp>

//#include <client/effect/ShockWaveEffect.hpp>

#include <jeti/Render.hpp>

namespace view {

WormHole::WormHole(control::WormHole* wormHole)
    :
      Base(wormHole)
    , m_control(wormHole)
{
    setOrientation(wormHole);
}

WormHole::~WormHole()
{
    //delete m_shockwave;
}

void WormHole ::draw(const jeti::Render& render) const
{
    render.draw(_mesh(), _material(), _modelMatrix());
}

//void BlackHoleDrawable::UpdateInSpace(int time, bool show_effect)
//{
//    m_shockwave->Update();
//}

/* virtual override final */
//void BlackHole::UpdateInfo()
//{
//    GetInfo().clear();

//    GetInfo().addTitleStr("BLACKHOLE");

//    GetInfo().addNameStr("id:");         GetInfo().addValueStr(std::to_string(id()));
//    GetInfo().addNameStr("mass:");       GetInfo().addValueStr(std::to_string(mass()));
//    GetInfo().addNameStr("pos:");        GetInfo().addValueStr( str(center()) );
//}
          
} // namespace view
