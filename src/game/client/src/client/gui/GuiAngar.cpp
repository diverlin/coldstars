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
#include <slots/VehicleSlot.hpp>
#include <slots/ItemSlot.hpp>
#include <item/BaseItem.hpp>
#include <client/resources/GuiTextureObCollector.hpp>

#include <spaceobjects/Vehicle.hpp>

#include <client/pilots/Player.hpp>
#include <pilots/Npc.hpp>

#include <builder/slots/ItemSlotBuilder.hpp>

#include <jeti/Render.hpp>
#include <client/gui/GuiManager.hpp>

GuiAngar::GuiAngar():angar(nullptr)
{
    //int screen_w = core::global::get().config().SCREEN_WIDTH;
    //int screen_h = core::global::get().config().SCREEN_HEIGHT;
    
    //TextureOb* texOb_button = GuiTextureObCollector::Instance().dot_green; // fake
    
    //float zpos = -1;
    //float zsize = 1;
    
    {
        //ButtonSingle* repair_button = new ButtonSingle(texOb_button, GUI::BUTTON::BUYARMOR_ID, "buy_repair");
        //glm::vec3 center(screen_w - 1 * (GUI::ICON_SIZE + 5), screen_h - 2 * GUI::ICON_SIZE, zpos);
        //glm::vec3 size(GUI::ICON_SIZE, GUI::ICON_SIZE, zsize);
        //Box box(center, size);
        //repair_button->SetBox(box);
        //button_map.insert(std::make_pair(GUI::BUTTON::BUYARMOR_ID, repair_button));
    }
    
    {
        //ButtonSingle* fuel_button = new ButtonSingle(texOb_button, GUI::BUTTON::BUYFUEL_ID, "buy fuel");
        //glm::vec3 center(screen_w - 1 * (GUI::ICON_SIZE + 5), screen_h - 3*GUI::ICON_SIZE, zpos);
        //glm::vec3 size(GUI::ICON_SIZE, GUI::ICON_SIZE, zsize);
        //Box box(center, size);
        //fuel_button->SetBox(box);
        //button_map.insert(std::make_pair(GUI::BUTTON::BUYFUEL_ID, fuel_button));
    }

    {
        //ButtonSingle* launch_button = new ButtonSingle(texOb_button, GUI::BUTTON::GETLAUNCH_ID, "launch");
        //glm::vec3 center(screen_w - 1 * (GUI::ICON_SIZE + 5), screen_h - 4*GUI::ICON_SIZE, zpos);
        //glm::vec3 size(GUI::ICON_SIZE, GUI::ICON_SIZE, zsize);
        //Box box(center, size);
        //launch_button->SetBox(box);
        //button_map.insert(std::make_pair(GUI::BUTTON::GETLAUNCH_ID, launch_button));
    }
    
//    repair_slot = GetNewItemSlotWithoutSaveAbility(entity::Type::REPAIR_SLOT_ID);
//    charge_slot = GetNewItemSlotWithoutSaveAbility(entity::Type::CHARGE_SLOT_ID);
}


GuiAngar::~GuiAngar()
{
    delete repair_slot;
    delete charge_slot;
}    

void GuiAngar::BindAngar(Angar* angar)
{
    this->angar = angar;
    
    int column_counter = 1;
    int row_counter = 0;
    for (unsigned int i=0; i<angar->vehicle_visitors_slot_vec.size(); i++)
    {
        ceti::Rect _rect(column_counter*GUI::VEHICLESLOT::WIDTH_FOR_ANGAR, row_counter*GUI::VEHICLESLOT::HEIGHT_FOR_ANGAR,
                   GUI::VEHICLESLOT::WIDTH_FOR_ANGAR, GUI::VEHICLESLOT::HEIGHT_FOR_ANGAR);
        m_vehicleslot_rects.push_back(GuiPair<ceti::Rect, control::VehicleSlot*>(_rect, angar->vehicle_visitors_slot_vec[i]));

        column_counter++;
    }

    column_counter = 1;
    row_counter = 2;
    for (unsigned int i=0; i<angar->vehicle_military_slot_vec.size(); i++)
    {
        ceti::Rect _rect(column_counter*GUI::VEHICLESLOT::WIDTH_FOR_ANGAR, row_counter*GUI::VEHICLESLOT::HEIGHT_FOR_ANGAR,
                   GUI::VEHICLESLOT::WIDTH_FOR_ANGAR, GUI::VEHICLESLOT::HEIGHT_FOR_ANGAR);
        m_vehicleslot_rects.push_back(GuiPair<ceti::Rect, control::VehicleSlot*>(_rect, angar->vehicle_military_slot_vec[i]));

        column_counter++;
    }
    
    column_counter = 0;
    row_counter = 0;
    for (unsigned int i=0; i<angar->item_slot_vec.size(); i++)
    {
        ceti::Rect _rect(column_counter*GUI::ITEMSLOT::WIDTH_FOR_ANGAR, row_counter*GUI::ITEMSLOT::HEIGHT_FOR_ANGAR,
                   GUI::ITEMSLOT::WIDTH_FOR_ANGAR, GUI::ITEMSLOT::HEIGHT_FOR_ANGAR);
        m_itemslot_rects.push_back(GuiPair<ceti::Rect, control::ItemSlot*>(_rect, angar->item_slot_vec[i]));

        row_counter++;
    }
    
    {
        ceti::Rect rect(GUI::ITEMSLOT::WIDTH_FOR_SHIP,
                  3*GUI::ITEMSLOT::HEIGHT_FOR_SHIP,
                  GUI::ITEMSLOT::WIDTH_FOR_SHIP, GUI::ITEMSLOT::HEIGHT_FOR_SHIP);
        m_itemslot_rects.push_back(GuiPair<ceti::Rect, control::ItemSlot*>(rect, repair_slot));
    }

    {
        ceti::Rect rect(GUI::ITEMSLOT::WIDTH_FOR_SHIP,
                  4*GUI::ITEMSLOT::HEIGHT_FOR_SHIP,
                  GUI::ITEMSLOT::WIDTH_FOR_SHIP, GUI::ITEMSLOT::HEIGHT_FOR_SHIP);
        m_itemslot_rects.push_back(GuiPair<ceti::Rect, control::ItemSlot*>(rect, charge_slot));
    }
}

void GuiAngar::UnbindAngar()
{
    angar = nullptr;
    
    m_vehicleslot_rects.clear();
    m_itemslot_rects.clear();
}

void GuiAngar::CheckButtonsLock()
{               
    //if (player->GetNpc()->vehicle()->IsFuelFull() == true)     { GetButton(GUI::BUTTON::BUYFUEL_ID)->LockOn(); }
    //else                                { GetButton(GUI::BUTTON::BUYFUEL_ID)->LockOff(); }

    //if (player->GetNpc()->vehicle()->IsArmorFull() == true)     { GetButton(GUI::BUTTON::BUYARMOR_ID)->LockOn(); }
    //else                                { GetButton(GUI::BUTTON::BUYARMOR_ID)->LockOff(); }
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
    //case GUI::BUTTON::BUYARMOR_ID:
    //{
    //if (button->GetLock() == false)
    //{
    //button->OnPressEventMBL(player);

    //angar->RepairVehicle(player->GetNpc()->vehicle());
    //return;
    //}

    //break;
    //}

    //case GUI::BUTTON::BUYFUEL_ID:
    //{
    //if (button->GetLock() == false)
    //{
    //button->OnPressEventMBL(player);

    //angar->TankUpVehicle(player->GetNpc()->vehicle());
    //return;
    //}

    //break;
    //}

    //case GUI::BUTTON::GETLAUNCH_ID:
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
                                        case entity::Type::REPAIR_SLOT_ID:
                                        {
                                                if (m_Player->GetCursor().GetItemSlot()->item() != nullptr)
                                                {
                                                        angar->RepairItem(m_Player->GetNpc(), m_Player->GetCursor().GetItemSlot()->item());
                                                }
                                                
                                                break;
                                        }
                                        
                                        case entity::Type::CHARGE_SLOT_ID:
                                        {
                                                if (m_Player->GetCursor().GetItemSlot()->item() != nullptr)
                                                {
                                                        switch (m_Player->GetCursor().GetItemSlot()->item()->subTypeId())
                                                        {
                                                                case entity::Type::ROCKET_EQUIPMENT_ID:
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


