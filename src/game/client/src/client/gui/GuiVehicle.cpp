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

#include "GuiVehicle.hpp"
#include <client/pilot/Player.hpp>
#include <client/gui/constants.hpp>
#include <client/resources/GuiTextureObCollector.hpp>
#include <client/gui/ButtonItemSlot.hpp>
#include <client/gui/constants.hpp>

#include <core/dock/Kosmoport.hpp>
#include <core/item/Item.hpp>
#include <core/slot/ItemSlot.hpp>
#include <core/pilot/Npc.hpp>
#include <core/spaceobject/Vehicle.hpp>
#include <core/common/common.hpp>

#include <jeti/Render.hpp>

#include <ceti/Logger.hpp>


namespace gui {

Vehicle::Vehicle(const glm::vec2& size)
    :
      Base(Type::SCAN_VEHICLE, Type::SCAN_VEHICLE)
{
    m_slot_gate = new slot::Item(slot::Type::GATE);
    setSize(size);
    setMaterial(new jeti::control::Material(gui::MaterialCollector::get().slot));
}

Vehicle::~Vehicle()
{}


void Vehicle::__createItemSlotsGeometry(control::Vehicle* vehicle)
{
    float dist_rate = 2.1f;
    /** WEAPON SLOTS */
    int i=0;
    for (slot::Item* slot: vehicle->weaponSlots()) {
        ButtonItemSlot* button = new ButtonItemSlot(slot);

        glm::vec2 size(gui::itemslot::WIDTH_FOR_SHIP, gui::itemslot::HEIGHT_FOR_SHIP);
        button->setSize(size);

        glm::vec2 offset((-2.f+i)*dist_rate*gui::itemslot::WIDTH_FOR_SHIP, (2.f)*dist_rate*gui::itemslot::HEIGHT_FOR_SHIP);
        add(button, offset);
        m_buttonslots.push_back(button);
        i++;
    }

    /** EQUIPMENT SLOTS */
    for (slot::Item* slot: vehicle->radarSlots()) {
        ButtonItemSlot* button = new ButtonItemSlot(slot);

        glm::vec2 size(gui::itemslot::WIDTH_FOR_SHIP, gui::itemslot::HEIGHT_FOR_SHIP);
        button->setSize(size);

        glm::vec2 offset((3.f)*dist_rate*gui::itemslot::WIDTH_FOR_SHIP, (-0.5f)*dist_rate*gui::itemslot::HEIGHT_FOR_SHIP);
        add(button, offset);
        m_buttonslots.push_back(button);
    }

    for (slot::Item* slot: vehicle->scanerSlots()) {
        ButtonItemSlot* button = new ButtonItemSlot(slot);

        glm::vec2 size(gui::itemslot::WIDTH_FOR_SHIP, gui::itemslot::HEIGHT_FOR_SHIP);
        button->setSize(size);

        glm::vec2 offset((3.f)*dist_rate*gui::itemslot::WIDTH_FOR_SHIP, (0.5f)*dist_rate*gui::itemslot::HEIGHT_FOR_SHIP);
        add(button, offset);
        m_buttonslots.push_back(button);
    }

//    for (slot::Item* slot: vehicle->energizerSlots()) {
//        ButtonItemSlot* button = new ButtonItemSlot(slot);

//        glm::vec2 size(GUI::ITEMSLOT::WIDTH_FOR_SHIP, GUI::ITEMSLOT::HEIGHT_FOR_SHIP);
//        button->setSize(size);

//        glm::vec2 offset((0)*dist_rate*GUI::ITEMSLOT::WIDTH_FOR_SHIP, (0)*dist_rate*GUI::ITEMSLOT::HEIGHT_FOR_SHIP);
//        add(button, offset);
//        m_buttonslots.push_back(button);
    //    }

    //{
    //ButtonItemSlot* button = new ButtonItemSlot(GUI::getEquivalent(entity::Type::FREEZER_SLOT), "ENTITY::FREEZER_SLOT");

    //glm::vec2 size(GUI::ITEMSLOT::WIDTH_FOR_SHIP, GUI::ITEMSLOT::HEIGHT_FOR_SHIP);
    //button->setSize(size);

    //glm::vec2 offset((-0.75)*dist_rate*GUI::ITEMSLOT::WIDTH_FOR_SHIP,(-0.75)*dist_rate*GUI::ITEMSLOT::HEIGHT_FOR_SHIP);
    //AddChild(button, offset);
    //        m_buttonslots.push_back(button);
    //}

    for (slot::Item* slot: vehicle->grappleSlots()) {
        ButtonItemSlot* button = new ButtonItemSlot(slot);

        glm::vec2 size(gui::itemslot::WIDTH_FOR_SHIP, gui::itemslot::HEIGHT_FOR_SHIP);
        button->setSize(size);

        glm::vec2 offset((-0.75f)*dist_rate*gui::itemslot::WIDTH_FOR_SHIP, (0.75f)*dist_rate*gui::itemslot::HEIGHT_FOR_SHIP);
        add(button, offset);
        m_buttonslots.push_back(button);
    }

    for (slot::Item* slot: vehicle->droidSlots()) {
        ButtonItemSlot* button = new ButtonItemSlot(slot);

        glm::vec2 size(gui::itemslot::WIDTH_FOR_SHIP, gui::itemslot::HEIGHT_FOR_SHIP);
        button->setSize(size);

        glm::vec2 offset((0.75f)*dist_rate*gui::itemslot::WIDTH_FOR_SHIP,(0.75f)*dist_rate*gui::itemslot::HEIGHT_FOR_SHIP);
        add(button, offset);
        m_buttonslots.push_back(button);
    }

    for (slot::Item* slot: vehicle->protectorSlots()) {
        ButtonItemSlot* button = new ButtonItemSlot(slot);

        glm::vec2 size(gui::itemslot::WIDTH_FOR_SHIP, gui::itemslot::HEIGHT_FOR_SHIP);
        button->setSize(size);

        glm::vec2 offset((0.75f)*dist_rate*gui::itemslot::WIDTH_FOR_SHIP,(-0.75f)*dist_rate*gui::itemslot::HEIGHT_FOR_SHIP);
        add(button, offset);
        m_buttonslots.push_back(button);
    }

    for (slot::Item* slot: vehicle->driveSlots()) {
        ButtonItemSlot* button = new ButtonItemSlot(slot);

        glm::vec2 size(gui::itemslot::WIDTH_FOR_SHIP, gui::itemslot::HEIGHT_FOR_SHIP);
        button->setSize(size);

        glm::vec2 offset((-2.5f)*dist_rate*gui::itemslot::WIDTH_FOR_SHIP, (0.5f)*dist_rate*gui::itemslot::HEIGHT_FOR_SHIP);
        add(button, offset);
        m_buttonslots.push_back(button);
    }

    for (slot::Item* slot: vehicle->bakSlots()) {
        ButtonItemSlot* button = new ButtonItemSlot(slot);

        glm::vec2 size(gui::itemslot::WIDTH_FOR_SHIP, gui::itemslot::HEIGHT_FOR_SHIP);
        button->setSize(size);

        glm::vec2 offset((-2.5f)*dist_rate*gui::itemslot::WIDTH_FOR_SHIP, (-0.5f)*dist_rate*gui::itemslot::HEIGHT_FOR_SHIP);
        add(button, offset);
        m_buttonslots.push_back(button);
    }

    /** ARTEFACT SLOTS */
#ifdef USE_ARTEFACTS
    for (slot::Item* slot: vehicle->artefactSlots()) {
        float scale_size = 1/2.0;
        ButtonItemSlot* button = new ButtonItemSlot(slot);

        glm::vec2 size(GUI::ITEMSLOT::WIDTH_FOR_SHIP*scale_size, GUI::ITEMSLOT::HEIGHT_FOR_SHIP*scale_size);
        button->setSize(size);

        glm::vec2 offset((i+1)*GUI::ITEMSLOT::WIDTH_FOR_SHIP*scale_size, (-2.5)*dist_rate*GUI::ITEMSLOT::HEIGHT_FOR_SHIP);
        add(button, offset);
    m_buttonslots.push_back(button);
    }
#endif // USE_ARTEFACTS


    /** CARGO SLOTS */
    i=0;
    for (slot::Item* slot: vehicle->cargoSlots()) {
        float scale_size =1/1.5f;
        ButtonItemSlot* button = new ButtonItemSlot(slot);

        glm::vec2 size(gui::itemslot::WIDTH_FOR_SHIP*scale_size, gui::itemslot::HEIGHT_FOR_SHIP*scale_size);
        button->setSize(size);

        glm::vec2 offset((-5.f+i)*dist_rate*gui::itemslot::WIDTH_FOR_SHIP*scale_size, -1.75f*dist_rate*gui::itemslot::HEIGHT_FOR_SHIP);
        add(button, offset);
        m_buttonslots.push_back(button);
        i++;
    }

    /** GATE SLOT */
    {
        ButtonItemSlot* button = new ButtonItemSlot(m_slot_gate);

        glm::vec2 size(0.5f*gui::itemslot::WIDTH_FOR_SHIP, 0.5f*gui::itemslot::WIDTH_FOR_SHIP);
        button->setSize(size);

        glm::vec2 offset((-3.2f)*gui::itemslot::WIDTH_FOR_SHIP, (3.0f)*gui::itemslot::WIDTH_FOR_SHIP);
        add(button, offset);
        m_buttonslots.push_back(button);
    }

    m_allowFullControl = false;
    m_blockManualExit  = false;
}


void Vehicle::bindVehicle(control::Vehicle* vehicle,
                          const glm::vec2& gui_offset,
                          bool allow_full_control,
                          bool block_manual_exit,
                          float scale)
{      
    assert(vehicle);
    if (m_vehicle == vehicle) {
        return;
    }
    Logger::get().log("Vehicle::bindVehicle", Logger::Code::GUI);
    m_vehicle = vehicle;

    m_allowFullControl = allow_full_control;
    m_blockManualExit = block_manual_exit;

    __createKorpusGui(vehicle, scale);
    __createItemSlotsGeometry(vehicle);
}

void Vehicle::unbindVehicle()
{ 
    Logger::get().log("Vehicle::unbindVehicle", Logger::Code::GUI);
    for (auto* child : _children()) {
        delete child;
    }
    _children().clear();
    m_buttonslots.clear();
    
    m_vehicle = nullptr;
}

void Vehicle::__createKorpusGui(control::Vehicle* vehicle, float scale)
{
//    float kontur_w = 350;
//    float kontur_h = 250;

//    box().setSize(kontur_w * scale, kontur_h * scale);
}      


bool
Vehicle::updateMouseInteraction(client::Player* player)
{    
    const MouseData& data_mouse = player->cursor().mouseData();
    for(ButtonItemSlot* slot: m_buttonslots) {
        bool result = __updateMouseInteractionWithSlot(slot, player, data_mouse);
        if (result) {
            return true;
        }
    }
    return false;
}

bool
Vehicle::__updateMouseInteractionWithSlot(ButtonItemSlot* gui_slot, client::Player* player, const MouseData& data_mouse)
{
    if (!gui_slot->box().checkInteraction(data_mouse.screenCoordGui())) {
        return false;
    } else {
        //std::cout<<"collide with="<<slot::to_string(gui_slot->itemSlot()->type())<<" "<<gui_slot->itemSlot()->offset()<<std::endl;
    }

    if (gui_slot->itemSlot()->item() && !player->cursor().itemSlot()->item()) {
        player->cursor().setFocusedItemSlot(gui_slot->itemSlot());
    }

    m_allowFullControl = true; // debug
    if (data_mouse.event() == MouseData::Event::LeftButtonPress && m_allowFullControl) {
        if (gui_slot->itemSlot()->type() != slot::Type::GATE) {
            bool result = player->cursor().itemSlot()->swapItem(gui_slot->itemSlot());
            return true;
        } else {
            if (player->cursor().itemSlot()->item()) {
                if (player->npc()->vehicle()->place() == place::Type::SPACE) {
                    std::cout<<"push telegram here to drop item"<<std::endl;
                    //player->cursor().itemSlot()->dropItemToSpace(player->npc()->vehicle());
                    return true;
                } else {
                    player->npc()->vehicle()->sellItem(player->cursor().itemSlot()->item());
                    return true;
                }
            }
        }
    }

//#if DEBUG_ITEMDAMAGELOCKVIAGUI > 0
//    {
//        switch(DEBUG_ITEMDAMAGELOCKVIAGUI)
//        {
//        case 1:
//        {
//            if (gui_itemslot_vec[i].GetItemSlot()->item() != nullptr)
//            {
//                if (data_mouse.right_click == true)
//                {
//                    std::cout<<"DEBUG ACTION in GuiVehicle::UpdateMouseInteractionInSpace, ItemLOck testing"<<std::endl;
//                    if (gui_itemslot_vec[i].GetItemSlot()->item()->GetFunctioning() == true)
//                    {
//                        gui_itemslot_vec[i].GetItemSlot()->item()->LockEvent(2);
//                    }
//                    else
//                    {
//                        gui_itemslot_vec[i].GetItemSlot()->item()->LockEvent(0);
//                    }
//                }
//            }

//            break;
//        }

//        case 2:
//        {
//            if (gui_itemslot_vec[i].GetItemSlot()->item() != nullptr)
//            {
//                if (data_mouse.right_click == true)
//                {
//                    std::cout<<"DEBUG ACTION in GuiVehicle::UpdateMouseInteractionInSpace, Item Damage testing"<<std::endl;
//                    if (gui_itemslot_vec[i].GetItemSlot()->item()->GetFunctioning() == true)
//                    {
//                        gui_itemslot_vec[i].GetItemSlot()->item()->SetCondition(0);
//                    }
//                    else
//                    {
//                        gui_itemslot_vec[i].GetItemSlot()->item()->SetCondition(1000);
//                    }
//                }
//            }

//            break;
//        }
//        }
//    }
//#endif

    return false;
}


void Vehicle::update(client::Player* player)
{
    if (!m_vehicle) {
        return;
    }

    if (isRoot()) {
        updatePosition(/*box().center(), box().scale()*/);
    }

    _updateChildren(player);
    _updateUnique(player);
    player->cursor().updateTakenItem();
}

void Vehicle::render(const jeti::Render& render, client::Player* player) const
{
    if (!m_vehicle) {
        return;
    }
    //__renderKorpus(render, player);
    _renderChildren(render, player);
    player->cursor().renderTakenItem(render);
}

void Vehicle::__renderKorpus(const jeti::Render& render, client::Player* player) const
{
    render.drawQuad_HUD(box(), material());
}

} // namespace gui





