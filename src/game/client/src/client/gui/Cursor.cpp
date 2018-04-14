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

#include <ceti/Logger.hpp>

#include <core/type/GuiType.hpp>

#include <jeti/Render.hpp>
#include <jeti/Screen.hpp>

#include <core/slot/ItemSlot.hpp>

#include <item/Item.hpp>

#include <core/spaceobject/ALL>

#include <client/pilot/Player.hpp>
#include <core/pilot/Npc.hpp>

#include <core/part/WeaponComplex.hpp>

#include <client/session/Shortcuts.hpp>
#include <client/gui/ButtonTrigger.hpp>
#include <client/gui/ButtonItemSlot.hpp>
#include <client/resources/GuiTextureObCollector.hpp>
#include <client/view/Base.hpp>
#include <client/gui/constants.hpp>

namespace gui {

Cursor::Cursor()
{
    m_itemSlot = new core::slot::Item(core::slot::Type::CARGO);

    m_markTargetMaterial = new jeti::control::Material(MaterialCollector::get().mark_target);

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
    delete m_markTargetMaterial;
    delete m_itemSlot;
    delete m_itemSlotGui;
}

void Cursor::reset()
{
    m_dataMouse.reset();
    
    m_focusedView = nullptr;
    m_focusedItemSlot = nullptr;
}

void Cursor::updateTakenItem()
{
    if (!m_itemSlot->item() && m_itemSlotGui) {
        delete m_itemSlotGui;
        m_itemSlotGui = nullptr;
        return;
    }

    if (m_itemSlot->item() && !m_itemSlotGui) {
        m_itemSlotGui = new gui::ButtonItemSlot(m_itemSlot);
        m_itemSlotGui->setSize(gui::itemslot::WIDTH_FOR_CURSOR, gui::itemslot::HEIGHT_FOR_CURSOR);
        m_itemSlotGui->setScale(0.8f);
        m_itemSlotGui->invalidate();
    }

    if (m_itemSlotGui) {
        m_itemSlotGui->setCenter(m_dataMouse.screenCoordGui());
        m_itemSlotGui->updateGeometry();
    }
}

void Cursor::update(client::Player* player, const jeti::Render& render)
{
    if (m_focusedView) {
        //if (!m_focusedView->isAlive()) {
        //    m_focusedView = nullptr;
        //}
    }

    switch(m_dataMouse.event()) {
    case MouseData::Event::LeftButtonPress: {
        if (m_focusedGuiElement) {
            m_focusedGuiElement->onPressEventMBL(player);
        }     
        break;
    }
    case MouseData::Event::RightButtonPress: {
        if (m_focusedGuiElement) {
            m_focusedGuiElement->onPressEventMBR(player);
        }    
        break;
    }
    }
}

void Cursor::updateMouseInput(const jeti::Render& render)
{    
//    if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
//        m_dataMouse.event = MouseData::LeftButtonClick;
//    } else if (sf::Mouse::isButtonPressed(sf::Mouse::Right)) {
//        m_dataMouse.event = MouseData::RightButtonClick;
//    }

    sf::Vector2i mouse_pos = sf::Mouse::getPosition(client::shortcuts::screen()->window());
    mouse_pos.y = render.height()-mouse_pos.y;
    m_dataMouse.setScreenCoord(glm::vec2(mouse_pos.x, mouse_pos.y));
    m_dataMouse.setScreenCoordGui(glm::vec2(mouse_pos.x-render.width()/2, mouse_pos.y-render.height()/2));
    m_dataMouse.setWorldCoord(render.toWorldCoord(glm::vec3(mouse_pos.x, mouse_pos.y, 0.0f)));
}

void Cursor::renderFocusedObjectStuff(const jeti::Render& render) const
{
    if (m_focusedView) {
        m_focusedView->drawCollisionRadius(render);
        //m_focusedView->drawAxis(render);

//        //m_FocusedSpaceObject->RenderStuffWhenFocusedInSpace(render);

//        ceti::Box2D box(meti::vec2(m_focusedView->position()), meti::vec2(m_focusedSpaceObject->size()));
//        box.SetScale(scale, scale);
//        //box.SetAngle(m_FocusedSpaceObject->GetAngle().z);

//        render.drawQuad(*GuiTextureObCollector::Instance().mark_target, box);
    }

//    if (m_itemSlot->item()) {
//        m_box.setCenter();
//        m_box.setSize(100, 100);

//        render.drawQuad_HUD(box, *m_markTargetMaterial);
//    }

//    float scale = 1.0f;
//    if (m_focusedGuiElement) {
//        if (m_focusedGuiElement->id() == Type::BUTTON_ITEMSLOT) {
//            ceti::Box2D box(m_focusedGuiElement->box());
//            box.setScale(scale);

//            render.drawQuad_HUD(box, *m_markTargetMaterial);
//        }
//    }
}

void Cursor::renderFocusedObjectInfo(const jeti::Render& render) const
{
    if (m_focusedGuiElement) {
        m_focusedGuiElement->renderInfo(render);
    }
    if (m_focusedView) {
        //m_FocusedSpaceObject->RenderInfoInSpace(render, client::shortcuts::screen()->GetBottomLeftScreenWC(), client::shortcuts::screen()->GetScale());
    }
}

void Cursor::renderTakenItem(const jeti::Render& render) const
{
    if (m_itemSlotGui) {
        m_itemSlotGui->renderItem(render);
    }
}

} // namespace gui
