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
#include <jeti/PathVisual.hpp>

namespace view {

Base::Base(control::Base* base)
    :
      jeti::Base()
    , m_control_base(base)
{}

Base::~Base()
{
    for(Base* decor: m_childs) {
        delete decor;
    }
    m_childs.clear();

    if (m_shield) {
        delete m_shield;
        m_shield = nullptr;
    }

    if (m_path) {
        delete m_path;
        m_path= nullptr;
    }
}

void Base::update()
{
    _updateModelMatrix();
}

int_t Base::id() const { return m_control_base->id(); }
entity::Type Base::type() const { return m_control_base->type(); }
entity::Type Base::group() const { return m_control_base->group(); }
int_t Base::mesh() const { return m_control_base->descriptor()->mesh(); }
int_t Base::texture() const { return m_control_base->descriptor()->texture(); }

effect::Shield*
Base::_createShield() {
    assert(m_shield == nullptr);
    m_shield = new effect::Shield(this);
    return m_shield;
}

void
Base::_createPath(jeti::control::Material* material) {
    assert(m_path == nullptr);
    m_path = new jeti::view::Path(material);
}

void Base::_addChild(Base* child) {
    child->_setParent(this);
    m_childs.push_back(child);
}

void Base::_drawChilds(const jeti::Render& render) const {
    for(Base* child: m_childs) {
        child->update();
        child->draw(render);
    }
}

void Base::_drawShield(const jeti::Render& render) const {
    assert(m_shield);
    m_shield->update();
    m_shield->draw(render);
}

void Base::_drawPath(const jeti::Render& render) const {
    assert(m_path);
    //m_path->update();
    m_path->draw(render);
}

} // namespace view
