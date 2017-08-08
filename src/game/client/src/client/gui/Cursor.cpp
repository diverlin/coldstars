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


#include <client/gui/Cursor.hpp>

#include <client/common/global.hpp>

#include <ceti/Logger.hpp>

#include <core/type/GuiType.hpp>

#include <jeti/Render.hpp>
#include <jeti/Screen.hpp>

#include <core/slot/ItemSlot.hpp>

#include <item/Item.hpp>

#include <core/spaceobject/ALL>

#include <client/pilots/Player.hpp>
#include <core/pilot/Npc.hpp>

#include <core/part/WeaponComplex.hpp>
#include <client/gui/ButtonTrigger.hpp>
#include <client/resources/GuiTextureObCollector.hpp>
#include <client/view/BaseView.hpp>

namespace gui {

Cursor::Cursor()
{
    //m_ItemSlot = GetNewItemSlotWithoutSaveAbility(entity::Type::CARGO_SLOT);
    
    m_box.setSize(GUI::ITEMSLOT::WIDTH_FOR_CURSOR, GUI::ITEMSLOT::HEIGHT_FOR_CURSOR);
    
    //ButtonTrigger* button; // EXPERIMENTAL GUI
    //button = new ButtonTrigger(GuiTextureObCollector::Instance().dot_red, GUI::BUTTON::ACTION_ATTACK, "attack");  
    //button_map.insert(std::make_pair(button->subTypeId(), button));
    
    //button = new ButtonTrigger(GuiTextureObCollector::Instance().dot_purple, GUI::BUTTON::ACTION_PRECISEATTACK, "presize_attack");  
    //button_map.insert(std::make_pair(button->subTypeId(), button));
    
    //button = new ButtonTrigger(GuiTextureObCollector::Instance().dot_green, GUI::BUTTON::ACTION_SCAN, "scan");  
    //button_map.insert(std::make_pair(button->subTypeId(), button));
    
    //button = new ButtonTrigger(GuiTextureObCollector::Instance().dot_blue, GUI::BUTTON::ACTION_GRAB, "grab");  
    //button_map.insert(std::make_pair(button->subTypeId(), button));                
    
    //button = new ButtonTrigger(GuiTextureObCollector::Instance().dot_yellow, GUI::BUTTON::ACTION_FOLLOW, "follow");  
    //button_map.insert(std::make_pair(button->subTypeId(), button));
        
    //int angle = 0;
    //for (std::map<int, BaseButton*>::const_iterator iterator = button_map.begin(); iterator!=button_map.end(); iterator++)
    //{
    //float scale = 0.4;
        //glm::vec2 pos = genVec2f(100*scale, angle);    
    //rect.setCenter(pos);
    //rect.setSize(GUI::ITEMSLOT::WIDTH_FOR_SHIP, GUI::ITEMSLOT::HEIGHT_FOR_SHIP);                           
        //rect.Scale(scale);    
        //iterator->second->SetRect(rect);   
    
    //angle += 360/button_map.size();
    //}
}

/* virtual */
Cursor::~Cursor()
{
    delete m_itemSlot;
}

void Cursor::__reset()
{
    m_dataMouse.left_click  = false;
    m_dataMouse.right_click = false;
    
    m_focusedView = nullptr;
    m_focusedGuiElement = nullptr;
}

void Cursor::update(Player* player)
{
    if (m_focusedView) {
        //if (!m_focusedView->isAlive()) {
        //    m_focusedView = nullptr;
        //}
    }
        
    m_box.setCenter(m_dataMouse.screen_coord.x, m_dataMouse.screen_coord.y);
        
    if (m_dataMouse.left_click) {
        if (m_focusedGuiElement)
        {
            #if GUI_LOG_ENABLED == 1
            Logger::Instance().Log("OnPressEventMBL="+getGuiTypeStr(m_FocusedGuiElement->subTypeId()), GUI_LOG_DIP);
            #endif
        
            m_focusedGuiElement->OnPressEventMBL(player);
        }
        
        if (m_focusedView)
        {
            //..
        }        
    }
    else if (m_dataMouse.right_click == true)
    {
        if (m_focusedGuiElement != nullptr)
        {
            #if GUI_LOG_ENABLED == 1
            Logger::Instance().Log("OnPressEventMBR="+getGuiTypeStr(m_FocusedGuiElement->subTypeId()), GUI_LOG_DIP);
            #endif
        
            m_focusedGuiElement->OnPressEventMBR(player);
        }
                
        if (m_focusedView)
        {
            //..
        }
        
    }
               
}

void Cursor::updateMouseStuff(const jeti::Render& render)
{    
    __reset();

    m_dataMouse.left_press  = sf::Mouse::isButtonPressed(sf::Mouse::Left);
    m_dataMouse.right_press = sf::Mouse::isButtonPressed(sf::Mouse::Right);       

    sf::Vector2i mouse_pos = sf::Mouse::getPosition(client::global::get().screen().window());
    mouse_pos.y = render.height()-mouse_pos.y;
    m_dataMouse.screen_coord = glm::vec3(mouse_pos.x, mouse_pos.y, 0.0f);
    m_dataMouse.world_coord = render.toWorldCoord(glm::vec3(mouse_pos.x, mouse_pos.y, 0.0f));
}

void Cursor::renderFocusedObjectStuff(const jeti::Render& render) const
{
    if (m_focusedView) {
        m_focusedView->drawCollisionRadius(render);
        m_focusedView->drawAxis(render);

//        //m_FocusedSpaceObject->RenderStuffWhenFocusedInSpace(render);

//        ceti::Box2D box(meti::vec2(m_focusedView->position()), meti::vec2(m_focusedSpaceObject->size()));
//        box.SetScale(scale, scale);
//        //box.SetAngle(m_FocusedSpaceObject->GetAngle().z);

//        render.drawQuad(*GuiTextureObCollector::Instance().mark_target, box);
    }

    float scale = 1.1;
    if (m_focusedGuiElement) {
        if (m_focusedGuiElement->typeId() == gui::type::BUTTON_ITEMSLOT) {
            ceti::Box2D box(m_focusedGuiElement->GetBox());
            box.SetScale(scale, scale);

            render.drawQuad(*GuiTextureObCollector::Instance().mark_target, box);
        }
    }
}

void Cursor::renderFocusedObjectInfo(const jeti::Render& render) const
{
    if (m_focusedGuiElement) {
        m_focusedGuiElement->RenderInfo(render);
    }
    if (m_focusedView) {
        //m_FocusedSpaceObject->RenderInfoInSpace(render, client::global::get().screen().GetBottomLeftScreenWC(), client::global::get().screen().GetScale());
    }
}

void Cursor::renderItem(const jeti::Render& render) const
{
    //m_ItemSlot->RenderItem(render, m_Box, glm::vec2(0));
}

} // namespace gui
