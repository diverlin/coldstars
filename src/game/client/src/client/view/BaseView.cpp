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

#include "BaseView.hpp"

#include <core/common/Base.hpp>
#include <core/descriptor/Base.hpp>

#include <jeti/Render.hpp>

namespace view {

Base::Base(control::Base* base)
    :
      m_control_base(base)
{}

Base::~Base()
{
    for(Base* decor: m_decors) {
        delete decor;
    }
    m_decors.clear();
}

int_t Base::id() const { return m_control_base->id(); }
entity::Type Base::type() const { return m_control_base->type(); }
entity::Type Base::subType() const { return m_control_base->subType(); }
int_t Base::mesh() const { return m_control_base->descriptor()->mesh(); }
int_t Base::texture() const { return m_control_base->descriptor()->texture(); }

void Base::addDecor(Base* decor) {
    decor->setParent(this);
    m_decors.push_back(decor);
}

void Base::_drawDecors(const jeti::Renderer& render) const {
    for(Base* decor: m_decors) {
        decor->update();
        decor->draw(render);
    }
}

void Base::_drawCollisionRadius(const jeti::Renderer& render) const {
    if (render.showCollisionRadius()) {
        render.drawCollisionRadius(_calcCollisionModelMatrix());
    }
}

void Base::_drawAxis(const jeti::Renderer& render) const {
    if (render.showAxis()) {
        render.drawAxis(_modelMatrix());
    }
}

} // namespace view
