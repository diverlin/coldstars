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


namespace gui {

Item::Item(core::control::Item* item, const ceti::Box2D& box)
    :
      m_item(item)
{
    _setBox(box);
    descriptor::Base* item_descr = core::shortcuts::descriptors()->get(item->model()->descriptor());
    setMaterial(utils::createMaterialFromDescriptorId(item_descr->material()));
}

Item::~Item()
{}

void Item::render(const jeti::Render& render)
{
    render.drawQuad_HUD(box(), material());
}

} // namespace gui
