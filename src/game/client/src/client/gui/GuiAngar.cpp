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

#include "GuiAngar.hpp"
#include <dock/Angar.hpp>
#include "ButtonSingle.hpp"
#include <common/Global.hpp>
#include <slot/VehicleSlot.hpp>
#include <slot/ItemSlot.hpp>
#include <item/Item.hpp>

#include <core/spaceobject/Vehicle.hpp>
#include <core/pilot/Npc.hpp>

#include <client/pilot/Player.hpp>
#include <client/resources/GuiTextureObCollector.hpp>
#include <client/gui/GuiManager.hpp>
#include <client/gui/constants.hpp>

#include <jeti/Render.hpp>

namespace gui {

GuiAngar::GuiAngar()
{
    //int screen_w = core::global::get().config().SCREEN_WIDTH;
    //int screen_h = core::global::get().config().SCREEN_HEIGHT;
    
    //TextureOb* texOb_button = GuiTextureObCollector::Instance().dot_green; // fake
    
    //float zpos = -1;
    //float zsize = 1;
    
    {
        //ButtonSingle* repair_button = new ButtonSingle(texOb_button, GUI::BUTTON::BUYARMOR, "buy_repair");
        //glm::vec3 center(screen_w - 1 * (GUI::ICON_SIZE + 5), screen_h - 2 * GUI::ICON_SIZE, zpos);
        //glm::vec3 size(GUI::ICON_SIZE, GUI::ICON_SIZE, zsize);
        //Box box(center, size);
        //repair_button->SetBox(box);
        //button_map.insert(std::make_pair(GUI::BUTTON::BUYARMOR, repair_button));
    }
    
    {
        //ButtonSingle* fuel_button = new ButtonSingle(texOb_button, GUI::BUTTON::BUYFUEL, "buy fuel");
        //glm::vec3 center(screen_w - 1 * (GUI::ICON_SIZE + 5), screen_h - 3*GUI::ICON_SIZE, zpos);
        //glm::vec3 size(GUI::ICON_SIZE, GUI::ICON_SIZE, zsize);
        //Box box(center, size);
        //fuel_button->SetBox(box);
        //button_map.insert(std::make_pair(GUI::BUTTON::BUYFUEL, fuel_button));
    }

    {
        //ButtonSingle* launch_button = new ButtonSingle(texOb_button, GUI::BUTTON::GETLAUNCH, "launch");
        //glm::vec3 center(screen_w - 1 * (GUI::ICON_SIZE + 5), screen_h - 4*GUI::ICON_SIZE, zpos);
        //glm::vec3 size(GUI::ICON_SIZE, GUI::ICON_SIZE, zsize);
        //Box box(center, size);
        //launch_button->SetBox(box);
        //button_map.insert(std::make_pair(GUI::BUTTON::GETLAUNCH, launch_button));
    }
    
//    repair_slot = GetNewItemSlotWithoutSaveAbility(entity::Type::REPAIR_SLOT);
//    charge_slot = GetNewItemSlotWithoutSaveAbility(entity::Type::CHARGE_SLOT);
}


GuiAngar::~GuiAngar()
{
    delete m_repair_slot;
    delete m_charge_slot;
}    

void GuiAngar::BindAngar(core::control::Angar* angar)
{
    m_angar = angar;
    
    int column_counter = 1;
    int row_counter = 0;
    for (core::slot::Vehicle* slot: angar->vehicleSlots()) {
        ceti::Rect rect(column_counter*GUI::VEHICLESLOT::WIDTH_FOR_ANGAR, row_counter*GUI::VEHICLESLOT::HEIGHT_FOR_ANGAR,
                   GUI::VEHICLESLOT::WIDTH_FOR_ANGAR, GUI::VEHICLESLOT::HEIGHT_FOR_ANGAR);
        m_vehicleslot_rects.push_back(GuiPair<ceti::Rect, core::slot::Vehicle*>(rect, slot));

        column_counter++;
    }

//    column_counter = 1;
//    row_counter = 2;
//    for (slot::Vehicle* slot: angar->vehicleSlots()) {
//    {
//        ceti::Rect rect(column_counter*GUI::VEHICLESLOT::WIDTH_FOR_ANGAR, row_counter*GUI::VEHICLESLOT::HEIGHT_FOR_ANGAR,
//                   GUI::VEHICLESLOT::WIDTH_FOR_ANGAR, GUI::VEHICLESLOT::HEIGHT_FOR_ANGAR);
//        m_vehicleslot_rects.push_back(GuiPair<ceti::Rect, slot::Vehicle*>(rect, slot));

//        column_counter++;
//    }
    
    column_counter = 0;
    row_counter = 0;
    for (core::slot::Item* slot: angar->itemSlots()) {
        ceti::Rect rect(column_counter*GUI::ITEMSLOT::WIDTH_FOR_ANGAR, row_counter*GUI::ITEMSLOT::HEIGHT_FOR_ANGAR,
                   GUI::ITEMSLOT::WIDTH_FOR_ANGAR, GUI::ITEMSLOT::HEIGHT_FOR_ANGAR);
        m_itemslot_rects.push_back(GuiPair<ceti::Rect, core::slot::Item*>(rect, slot));

        row_counter++;
    }
    
    {
        ceti::Rect rect(gui::itemslot::WIDTH_FOR_SHIP,
                  3*gui::itemslot::HEIGHT_FOR_SHIP,
                  gui::itemslot::WIDTH_FOR_SHIP, gui::itemslot::HEIGHT_FOR_SHIP);
        m_itemslot_rects.push_back(GuiPair<ceti::Rect, core::slot::Item*>(rect, m_repair_slot));
    }

    {
        ceti::Rect rect(gui::itemslot::WIDTH_FOR_SHIP,
                  4*gui::itemslot::HEIGHT_FOR_SHIP,
                  gui::itemslot::WIDTH_FOR_SHIP, gui::itemslot::HEIGHT_FOR_SHIP);
        m_itemslot_rects.push_back(GuiPair<ceti::Rect, core::slot::Item*>(rect, m_charge_slot));
    }
}

void GuiAngar::UnbindAngar()
{
    m_angar = nullptr;
    
    m_vehicleslot_rects.clear();
    m_itemslot_rects.clear();
}

void GuiAngar::CheckButtonsLock()
{               
    //if (player->GetNpc()->vehicle()->IsFuelFull() == true)     { GetButton(GUI::BUTTON::BUYFUEL)->LockOn(); }
    //else                                { GetButton(GUI::BUTTON::BUYFUEL)->LockOff(); }

    //if (player->GetNpc()->vehicle()->IsArmorFull() == true)     { GetButton(GUI::BUTTON::BUYARMOR)->LockOn(); }
    //else                                { GetButton(GUI::BUTTON::BUYARMOR)->LockOff(); }
}

void GuiAngar::ButtonsAction() const     
{
    //for (std::map<int, BaseButton*>::const_iterator iterator = button_map.begin(); iterator!=button_map.end(); iterator++)
    //{
    //BaseButton* button = iterator->second;
    //if (button->GetPressed() == true)
    //{
    //switch(button->subTypeId())
    //{
    //case GUI::BUTTON::BUYARMOR:
    //{
    //if (button->GetLock() == false)
    //{
    //button->OnPressEventMBL(player);

    //angar->RepairVehicle(player->GetNpc()->vehicle());
    //return;
    //}

    //break;
    //}

    //case GUI::BUTTON::BUYFUEL:
    //{
    //if (button->GetLock() == false)
    //{
    //button->OnPressEventMBL(player);

    //angar->TankUpVehicle(player->GetNpc()->vehicle());
    //return;
    //}

    //break;
    //}

    //case GUI::BUTTON::GETLAUNCH:
    //{
    //player->GetNpc()->vehicle()->LaunchingEvent();

    //return;

    //break;
    //}
    //}
    //}
    //}
}

bool GuiAngar::UpdateMouseInteractionWithVehicleSlots(const MouseData& data_mouse)
{    
    /*
        for (unsigned int i=0; i<rect_vehicleslot_vec.size(); i++)
        {
                if (rect_vehicleslot_vec[i].first.CheckInteraction(data_mouse.pos_screencoord) == true)
                {
                           if (data_mouse.right_click == true)
                           {
                         m_Player->GetNpc()->SetScanTarget(rect_vehicleslot_vec[i].second->vehicle());
                                GuiManager::Instance().GetGuiKosmoport().EnterGuiScanInAngar();
                                return true;
                        }
                        
                        if (rect_vehicleslot_vec[i].second->vehicle() != nullptr)
                        {
                            m_Player->GetCursor().SetFocusedObject(rect_vehicleslot_vec[i].second->vehicle());
                        }

                }
        }

        for (unsigned int i=0; i<rect_itemslot_vec.size(); i++)
        {
                if (rect_itemslot_vec[i].first.CheckInteraction(data_mouse.pos_screencoord) == true)
                {
                    if (data_mouse.left_click == true)
                        {
                        switch (rect_itemslot_vec[i].second->subTypeId())
                                {
                                        case entity::Type::REPAIR_SLOT:
                                        {
                                                if (m_Player->GetCursor().GetItemSlot()->item() != nullptr)
                                                {
                                                        angar->RepairItem(m_Player->GetNpc(), m_Player->GetCursor().GetItemSlot()->item());
                                                }
                                                
                                                break;
                                        }
                                        
                                        case entity::Type::CHARGE_SLOT:
                                        {
                                                if (m_Player->GetCursor().GetItemSlot()->item() != nullptr)
                                                {
                                                        switch (m_Player->GetCursor().GetItemSlot()->item()->subTypeId())
                                                        {
                                                                case entity::Type::ROCKET_EQUIPMENT:
                                                                {
                                                                        angar->ChargeRocketEquipment(m_Player->GetNpc(), (RocketEquipment*)m_Player->GetCursor().GetItemSlot()->item());
                                                                        
                                                                        break;
                                                                }
                                                        }
                                                }
                                                
                                                break;
                                        }
                                        
                                        default:
                                        {
                                                m_Player->GetCursor().GetItemSlot()->SwapItem(rect_itemslot_vec[i].second);
                                                
                                                break;
                                        }
                                }

                        }

                        if (rect_itemslot_vec[i].second->item() != nullptr)
                        {
                        m_Player->GetCursor().SetFocusedObject(rect_itemslot_vec[i].second->item());
                    }
                }
        }
        */
    return false;
}

void GuiAngar::RenderVehicleAndItemSlots() const
{
    //glPushMatrix();
    //glTranslatef(GetGuiOffset().x, GetGuiOffset().y, 0);
    //for (unsigned int i=0; i<rect_vehicleslot_vec.size(); i++)
    //{
    //rect_vehicleslot_vec[i].second->Render(rect_vehicleslot_vec[i].first);
    //}
    //for (unsigned int i=0; i<rect_itemslot_vec.size(); i++)
    //{
    //rect_itemslot_vec[i].second->Render(rect_itemslot_vec[i].first, GetGuiOffset());
    //}
    //glPopMatrix();
}

} // namespace gui
