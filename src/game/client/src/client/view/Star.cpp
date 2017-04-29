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

#include "Star.hpp"

#include <core/spaceobject/Star.hpp>
#include <core/model/spaceobject/Star.hpp>

namespace view {

Star::Star(control::Star* star)
    :
      Base(star)
    , m_star(star)
{
    setOrientationModel(star->model());
}
  
Star::~Star()
{}

//void Star::draw(const jeti::Renderer& render)
//{
//}

//void Star::UpdateInfo()
//{
//    GetInfo().clear();
//    GetInfo().addTitleStr("STAR");
//    GetInfo().addNameStr("id/ss_id:");  GetInfo().addValueStr(std::to_string(id()) + " / " + std::to_string(starsystem()->id()));
//    GetInfo().addNameStr("armor:");     GetInfo().addValueStr(std::to_string(dataLife().armor));
//    GetInfo().addNameStr("pos:");       GetInfo().addValueStr( str(center()) );
//}

} // namespace view
