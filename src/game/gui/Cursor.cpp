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


#include <gui/Cursor.hpp>

#include <common/Logger.hpp>

#include <types/GuiTypes.hpp>

#include <jeti/Render.hpp>
#include <jeti/Screen.hpp>

#include <builder/slots/ItemSlotBuilder.hpp>

#include <slots/ItemSlot.hpp>

#include <items/BaseItem.hpp>

#include <spaceobjects/IncludeSpaceObjects.hpp>

#include <pilots/Player.hpp>
#include <pilots/Npc.hpp>

#include <parts/WeaponComplex.hpp>
#include <gui/ButtonTrigger.hpp>
#include <resources/GuiTextureObCollector.hpp>


Cursor::Cursor()
: 
m_FocusedSpaceObject(nullptr),
m_FocusedGuiElement(nullptr)
{
    m_ItemSlot = GetNewItemSlotWithoutSaveAbility(TYPE::ENTITY::CARGO_SLOT_ID);
    
    m_Box.SetSize(GUI::ITEMSLOT::WIDTH_FOR_CURSOR, GUI::ITEMSLOT::HEIGHT_FOR_CURSOR);
    
    //ButtonTrigger* button; // EXPERIMENTAL GUI
    //button = new ButtonTrigger(GuiTextureObCollector::Instance().dot_red, GUI::BUTTON::ACTION_ATTACK_ID, "attack");  
    //button_map.insert(std::make_pair(button->subTypeId(), button));
    
    //button = new ButtonTrigger(GuiTextureObCollector::Instance().dot_purple, GUI::BUTTON::ACTION_PRECISEATTACK_ID, "presize_attack");  
    //button_map.insert(std::make_pair(button->subTypeId(), button));
    
    //button = new ButtonTrigger(GuiTextureObCollector::Instance().dot_green, GUI::BUTTON::ACTION_SCAN_ID, "scan");  
    //button_map.insert(std::make_pair(button->subTypeId(), button));
    
    //button = new ButtonTrigger(GuiTextureObCollector::Instance().dot_blue, GUI::BUTTON::ACTION_GRAB_ID, "grab");  
    //button_map.insert(std::make_pair(button->subTypeId(), button));                
    
    //button = new ButtonTrigger(GuiTextureObCollector::Instance().dot_yellow, GUI::BUTTON::ACTION_FOLLOW_ID, "follow");  
    //button_map.insert(std::make_pair(button->subTypeId(), button));
        
    //int angle = 0;
    //for (std::map<int, BaseButton*>::const_iterator iterator = button_map.begin(); iterator!=button_map.end(); iterator++)
    //{
    //float scale = 0.4;
        //glm::vec2 pos = genVec2f(100*scale, angle);    
    //rect.SetCenter(pos);
    //rect.SetSize(GUI::ITEMSLOT::WIDTH_FOR_SHIP, GUI::ITEMSLOT::HEIGHT_FOR_SHIP);                           
        //rect.Scale(scale);    
        //iterator->second->SetRect(rect);   
    
    //angle += 360/button_map.size();
    //}
}

/* virtual */
Cursor::~Cursor()
{
    delete m_ItemSlot;
}

void Cursor::Reset()
{
    m_DataMouse.left_click  = false;
    m_DataMouse.right_click = false;
    
    m_FocusedSpaceObject = nullptr;
    m_FocusedGuiElement = nullptr;
}

void Cursor::Update(Player* player)
{
    if (m_FocusedSpaceObject != nullptr)
    {
        if (m_FocusedSpaceObject->GetAlive() == false)
        {
            m_FocusedSpaceObject = nullptr;
        }
    }
        
    UpdateMouseStuff();
    
    m_Box.SetCenter(m_DataMouse.pos_screencoord.x, m_DataMouse.pos_screencoord.y);  
        
    if (m_DataMouse.left_click == true)
    {
        if (m_FocusedGuiElement != nullptr)
        {
            #if GUI_LOG_ENABLED == 1
            Logger::Instance().Log("OnPressEventMBL="+getGuiTypeStr(m_FocusedGuiElement->subTypeId()), GUI_LOG_DIP);
            #endif
        
            m_FocusedGuiElement->OnPressEventMBL(player);
        }
        
        if (m_FocusedSpaceObject != nullptr)
        {
            //..
        }
        
    }
    else if (m_DataMouse.right_click == true)
    {
        if (m_FocusedGuiElement != nullptr)
        {
            #if GUI_LOG_ENABLED == 1
            Logger::Instance().Log("OnPressEventMBR="+getGuiTypeStr(m_FocusedGuiElement->subTypeId()), GUI_LOG_DIP);
            #endif
        
            m_FocusedGuiElement->OnPressEventMBR(player);
        }
                
        if (m_FocusedSpaceObject != nullptr)
        {
            //..
        }
        
    }
               
}

void Cursor::UpdateMouseStuff()
{    
    m_DataMouse.left_press  = sf::Mouse::isButtonPressed(sf::Mouse::Left);
    m_DataMouse.right_press = sf::Mouse::isButtonPressed(sf::Mouse::Right);       

    sf::Vector2i mouse_pos = sf::Mouse::getPosition(jeti::Screen::Instance().GetWindow());
    m_DataMouse.pos_screencoord = glm::vec2(mouse_pos.x, jeti::Screen::Instance().GetHeight() - mouse_pos.y);
    m_DataMouse.pos_worldcoord = m_DataMouse.pos_screencoord*jeti::Screen::Instance().GetScale() + jeti::Screen::Instance().GetBottomLeftScreenWC();
}

void Cursor::RenderFocusedObjectStuff(const jeti::Renderer& render) const
{
    //render.enable_BLEND();
    {
        float scale = 1.1;
        if (m_FocusedSpaceObject != nullptr)
        {                    
            //m_FocusedSpaceObject->RenderStuffWhenFocusedInSpace(render);
            
            ceti::Box2D box(meti::vec2(m_FocusedSpaceObject->GetCenter()), meti::vec2(m_FocusedSpaceObject->GetSize()));
            box.SetScale(scale, scale);
            //box.SetAngle(m_FocusedSpaceObject->GetAngle().z);
            
            render.DrawQuad(*GuiTextureObCollector::Instance().mark_target, box);
        }
        
        if (m_FocusedGuiElement != nullptr)
        {
            if (m_FocusedGuiElement->typeId() == TYPE::GUI::BUTTON_ITEMSLOT_ID)
            {
                ceti::Box2D box(m_FocusedGuiElement->GetBox());
                box.SetScale(scale, scale);
            
                render.DrawQuad(*GuiTextureObCollector::Instance().mark_target, box);
            }
        }
    }
    //render.disable_BLEND();  
}

void Cursor::RenderFocusedObjectInfo(const jeti::Renderer& render) const
{
    //render.enable_BLEND();
    {
        if (m_FocusedGuiElement) {
            m_FocusedGuiElement->RenderInfo(render);
        }        
        if (m_FocusedSpaceObject) {
            //m_FocusedSpaceObject->RenderInfoInSpace(render, jeti::Screen::Instance().GetBottomLeftScreenWC(), jeti::Screen::Instance().GetScale());
        }
    }
    //render.disable_BLEND();  
}

void Cursor::RenderItem(const jeti::Renderer& render) const
{
    //render.enable_BLEND();
    {
        m_ItemSlot->RenderItem(render, m_Box, glm::vec2(0));   
    }
    //render.disable_BLEND();
}
