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

#include "Container.hpp"

namespace view {

//Container::Container(jeti::control::TextureOb* texture, jeti::Mesh* mesh)
//    :
//      BaseDrawable(texture, mesh)
//{
//}

///* virtual */
//Container::~Container()
//{}

///* virtual override final */
////void Container::UpdateInfo()
////{
////    GetInfo().clear();
////    GetInfo().addTitleStr("CONTAINER");
////    GetInfo().addNameStr("id/ss_id:");    GetInfo().addValueStr(std::to_string(id()) + " / " + std::to_string(starsystem()->id()));
////    GetInfo().addNameStr("armor:");       GetInfo().addValueStr(std::to_string(dataLife().armor));
////    GetInfo().addNameStr("pos:");         GetInfo().addValueStr( str(center()) );
////}
 
///* virtual override final */
////void Container::RenderInfoInSpace(const jeti::Renderer& render, const glm::vec2& scroll_coords, float zoom)
////{
////    UpdateInfo();
////    glm::vec2 pos(center().x - scroll_coords.x, center().y - scroll_coords.y);
////    pos /= zoom;
////    jeti::drawInfoIn2Column(GetInfo().title_list, GetInfo().value_list, pos);
    
////    pos.x += 300;
////    m_ItemSlot->item()->RenderInfo(render, pos);
////}

} // namespace view