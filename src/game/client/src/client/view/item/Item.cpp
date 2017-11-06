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


#include "Item.hpp"
#include <common/constants.hpp>

#include <core/common/Global.hpp>

#include <core/slot/ItemSlot.hpp>

#include <core/descriptor/item/Item.hpp>
#include <core/model/item/Item.hpp>

#include <ceti/Logger.hpp>


namespace view {

//Item::Item(control::Item* item)
//    :
//      Base(descr, model)
//    , m_descriptor_item(descr)
//    , m_model_item(model)
//{
//}


//void Base::UpdateInfo()
//{
////    info.clear();

//    addUniqueInfo();
//    AddCommonInfo();
//}

//void Base::RenderInfo(const jeti::Renderer& render, const glm::vec2& pos)
//{
//    UpdateInfo();
    
//    //render.enable_BLEND();
//    jeti::drawInfoIn2Column(info.title_list, info.value_list, pos);
//    //render.disable_BLEND();
//}

///* virtual */
//void Base::Render(const jeti::Renderer& render, const ceti::Box2D& box, const glm::vec2& gui_offset, bool draw_text)
//{
//    RenderKorpus(render, box);
//}

//void Base::RenderKorpus(const jeti::Renderer& render, const ceti::Box2D& box)
//{
//    glm::vec2 v(0.0);
//    glm::vec4 c(1.0, 1.0, 1.0, 1.0);
//    glm::vec3 center(box.center().x, box.center().y, GUI::POS_Z);
//    setCenter(center);
//    //SetAngle(box.GetAngle());
//    //SetScale(box.size());
//    //RenderMeshLight(v, c);
//}

} // namespace view
