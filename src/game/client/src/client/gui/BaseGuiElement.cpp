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


std::map<gui::type, BaseGuiElement*> BaseGuiElement::m_elements;

   
BaseGuiElement::BaseGuiElement(gui::type type_id, gui::type group, const std::string& info, jeti::control::Material* textureOb)
:
m_type(type_id),
m_group(group),
m_textureOb(textureOb),
m_info(info),
m_isLocked(false),
m_isPressed(false),
m_isVisible(true),
m_isRoot(true),
m_animationProgram(nullptr)
{}

/* virtual */
BaseGuiElement::~BaseGuiElement()
{
    //for (std::vector<BaseGuiElement*>::iterator it=m_Child_vec.begin(); it!=m_Child_vec.end(); it++)
    //{
        //delete *it;
    //}
    
    delete m_animationProgram;
}    
 
void BaseGuiElement::_deleteAnimationProgram()
{
    if (m_animationProgram != nullptr) {
        delete m_animationProgram;
        m_animationProgram = nullptr;
    }
}

          
BaseGuiElement* BaseGuiElement::element(gui::type request_group) const
{
    std::map<gui::type, BaseGuiElement*>::const_iterator it = m_elements.find(request_group);
    if (it != m_elements.cend()) {
        return it->second;
    }
    
    return nullptr;
}   
    
void BaseGuiElement::_pressEventMBL_onGuiElement(gui::type group, client::Player* player)
{
    BaseGuiElement* button = element(group);
    if (button) {
        button->onPressEventMBL(player);
    }
}    

void BaseGuiElement::_resetStateEventOnGuiElement(gui::type group)
{
    BaseGuiElement* button = element(group);
    if (button) {
        button->resetState();
    }
}    
            
/* virtual */
void BaseGuiElement::resetState()
{
    m_isPressed = false;
}

void BaseGuiElement::add(BaseGuiElement* child, const glm::vec2& offset)
{ 
    child->SetOffset(offset);
    child->_setIsRoot(false);
    
    m_children.push_back(child);
    m_elements.insert(std::make_pair(child->group(), child));
}
        
BaseGuiElement*
BaseGuiElement::updateMouseInteraction(const glm::vec2& mouse_pos)
{
    if (!m_isVisible) {
        return nullptr;
    }
    
    BaseGuiElement* child_interacted = nullptr;
    for (const auto &child : m_children)
    {
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

void BaseGuiElement::_updateGeometry(const glm::vec2& parent_offset, const glm::vec2& parent_scale)
{
    if (!m_isVisible)
    {
        return;
    }
    
    glm::vec2 next_offset = parent_offset + m_offset;
    glm::vec2 next_scale = parent_scale * m_box.scale();

    m_box.setCenter(next_offset);
    m_box.setScale(next_scale);
            
    for (auto &child : m_children)
    {
        child->_updateGeometry(next_offset, next_scale);
    }
}

void BaseGuiElement::update(client::Player* player)
{
    if (!m_isVisible)
    {
        return;
    }
    
    if (m_isRoot)
    {
        _updateGeometry(m_offset, glm::vec2(1,1));
    }
    
    _updateCommon(player);
    _updateUnique(player);
}
 
/* virtual */
void BaseGuiElement::_updateUnique(client::Player*)
{}

void BaseGuiElement::_updateCommon(client::Player* player)
{
    for (auto* child : m_children) {
        child->update(player);
    }
    
    if (m_animationProgram != nullptr)
       {    
           m_animationProgram->Update(m_box);
       }
}

void BaseGuiElement::render(const jeti::Render& render, client::Player* player) const
{
    if (!m_isVisible)
    {
        return;
    }
    
    if (m_isRoot)
    {
        //resetRenderTransformation();
    }
    
    //render.enable_BLEND();
    {
        _renderUnique(render, player);
        _renderCommon(render, player);
    }
    //render.disable_BLEND();
}

/* virtual */
void BaseGuiElement::_renderUnique(const jeti::Render& render, client::Player* player) const
{
    if (m_textureOb) {
        render.drawQuad(*m_textureOb, m_box);
    }
}

void BaseGuiElement::_renderCommon(const jeti::Render& render, client::Player* player) const
{
    for (const auto* gui_element : m_children) {
        gui_element->render(render, player);
    }
}
