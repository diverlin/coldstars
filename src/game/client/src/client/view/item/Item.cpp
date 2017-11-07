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

#include <core/item/Item.hpp>
#include <core/model/item/Item.hpp>
#include <core/manager/DescriptorManager.hpp>
#include <core/descriptor/Base.hpp>
#include <core/session/Shortcuts.hpp>

#include <client/resources/Utils.hpp>

#include <jeti/Render.hpp>


namespace view {

Item::Item(control::Item* item)
    :
      m_item(item)
{
    descriptor::Base* item_descr = core::shortcuts::descriptors()->get(item->model()->descriptor());
    m_material = utils::createMaterialFromDescriptorId(item_descr->texture());
}

Item::~Item()
{
    delete m_material;
    m_material = nullptr;
}

void Item::render(const jeti::Render& render)
{
    render.drawQuad_HUD(m_box, *m_material);
}



} // namespace view
