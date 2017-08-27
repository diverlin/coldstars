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

#include "Base.hpp"

#include <core/descriptor/Base.hpp>
#include <core/model/Base.hpp>

#include <ceti/StringUtils.hpp>


namespace control {

Base::Base(descriptor::Base* descr, model::Base* model)
    :
      m_descriptor_base(descr)
    , m_model_base(model)
{}

entity::Type
Base::type() const { return descriptor()->obType(); }

entity::Type
Base::group() const { return descriptor()->obGroup(); }

void
Base::setId(int_t id) { model()->setId(id); }

int_t
Base::id() const { return model()->id(); }

bool
Base::isAlive() const
{
    return model()->isAlive();
}

void
Base::die()
{
    model()->setIsAlive(false);
    __putChildrenToGarbage();
}

} // namespace control
