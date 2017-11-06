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


#include "BaseGuiElement.hpp"
#include <common/constants.hpp>
#include <jeti/Render.hpp>
#include <ceti/Logger.hpp>

#include <jeti/AnimationEffect2D.hpp>


namespace gui {

std::map<Type, Base*> Base::m_elements;

Base::Base(Type id,
           Type group,
           const std::string& info,
           jeti::model::Material* material)
    :
      m_id(id),
      m_group(group),
      m_info(info)
{
    if (material) {
        setMaterial(new jeti::control::Material(material));
    }

    if (id != gui::Type::NONE) {
        m_elements.insert(std::make_pair(id, this));
    }
}

/* virtual */
Base::~Base()
{
    //for (std::vector<BaseGuiElement*>::iterator it=m_Child_vec.begin(); it!=m_Child_vec.end(); it++)
    //{
    //delete *it;
    //}
    
    delete m_material;
    delete m_animation;
}    

void Base::_deleteAnimationProgram()
{
    if (m_animation != nullptr) {
        delete m_animation;
        m_animation = nullptr;
    }
}


Base* Base::element(Type id)
{
    std::map<Type, Base*>::const_iterator it = m_elements.find(id);
    if (it != m_elements.cend()) {
        return it->second;
    }
    
    return nullptr;
}   

void Base::_pressEventMBL_onGuiElement(Type group, client::Player* player)
{
    Base* button = element(group);
    if (button) {
        button->onPressEventMBL(player);
    }
}    

void Base::_resetStateEventOnGuiElement(Type group)
{
    Base* button = element(group);
    if (button) {
        button->resetState();
    }
}    

void Base::resetState()
{
    m_isPressed = false;
}

void Base::add(Base* child, const glm::vec2& offset)
{ 
    child->__setOffset(offset);
    child->_setIsRoot(false);
    
    m_children.push_back(child);
}

Base*
Base::updateMouseInteraction(const glm::vec2& mouse_pos)
{
    if (!m_isVisible) {
        return nullptr;
    }
    
    Base* child_interacted = nullptr;
    for (const auto &child : m_children) {
        child_interacted = child->updateMouseInteraction(mouse_pos);
        if (child_interacted) {
            return child_interacted;
        }
    }
    
    if (!m_isRoot) {
        if (m_box.checkInteraction(mouse_pos)) {
            return this;
        }
    }

    return nullptr;
}

void Base::_updateGeometry(const glm::vec2& parent_offset, const glm::vec2& parent_scale)
{   
    glm::vec2 next_offset = parent_offset + m_offset;
    glm::vec2 next_scale = parent_scale * m_box.scale();

    m_box.setCenter(next_offset);
    m_box.setScale(next_scale);

    for (auto &child : m_children) {
        child->_updateGeometry(next_offset, next_scale);
    }
}

void Base::update(client::Player* player)
{
    if (!m_isVisible) {
        return;
    }
    
    if (m_isRoot) {
        _updateGeometry(m_offset, glm::vec2(1,1));
    }
    
    _updateChildren(player);
    _updateUnique(player);
}

void Base::_updateUnique(client::Player*)
{}

void Base::_updateChildren(client::Player* player)
{
    for (auto* child : m_children) {
        child->update(player);
    }
    
    if (m_animation) {
        m_animation->update(m_box);
    }
}

void Base::render(const jeti::Render& render, client::Player* player) const
{
    if (!m_isVisible) {
        return;
    }    
    
    _renderUnique(render, player);
    _renderChildren(render, player);
}

void Base::_renderUnique(const jeti::Render& render, client::Player* player) const
{
//    if (m_material) {
//        render.drawQuad_HUD(m_box, *m_material);
//    }
}

void Base::_renderChildren(const jeti::Render& render, client::Player* player) const
{
    for (const auto* child : m_children) {
        child->render(render, player);
    }
}

} // namespace gui
