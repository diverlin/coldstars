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

#include "GuiStore.hpp"
#include <dock/Store.hpp>
#include <core/item/Item.hpp>
#include <core/slot/ItemSlot.hpp>
#include <core/slot/VehicleSlot.hpp>
#include <core/pilot/Npc.hpp>
#include <core/spaceobject/Vehicle.hpp>

#include <client/pilot/Player.hpp>
#include <client/resources/GuiTextureObCollector.hpp>
#include <client/gui/GuiManager.hpp>

namespace gui {

GuiStore::GuiStore()
{}

GuiStore::~GuiStore()
{}

void GuiStore::bindStore(core::control::Store* store)
{
    this->m_store = store;

    int clm = 0;
    int row = 0;
    for (core::ItemSlot* slot: store->itemSlots()) {
        ceti::Rect rect(clm * 1.1 * GUI::ITEMSLOT::WIDTH_FOR_STORE,
                  -row * 1.1 * GUI::ITEMSLOT::HEIGHT_FOR_STORE,
                  GUI::ITEMSLOT::WIDTH_FOR_STORE,
                  GUI::ITEMSLOT::HEIGHT_FOR_STORE);

        m_itemslot_rects.push_back(GuiPair<ceti::Rect, core::ItemSlot*>(rect, slot));

        clm++;
        if (clm > GUI::STORE_SLOTS_INROW) {
            clm = 0;
            row++;
        }
    }


    for (core::slot::Vehicle* slot: store->vehicleSlots()) {
        ceti::Rect rect(clm * 1.1 * GUI::ITEMSLOT::WIDTH_FOR_STORE,
                  -row * 1.1 * GUI::ITEMSLOT::HEIGHT_FOR_STORE,
                  GUI::ITEMSLOT::WIDTH_FOR_STORE,
                  GUI::ITEMSLOT::HEIGHT_FOR_STORE);

        m_vehicleslot_rects.push_back(GuiPair<ceti::Rect, core::slot::Vehicle*>(rect, slot));

        clm++;
        if (clm > GUI::STORE_SLOTS_INROW) {
            clm = 0;
            row++;
        }
    }
}

void GuiStore::UnbindStore()
{
    m_store = nullptr;

    m_itemslot_rects.clear();
    m_vehicleslot_rects.clear();
}

bool GuiStore::updateMouseInteraction(const MouseData& data_mouse)
{
    /*
        for (unsigned int i=0; i<rect_itemslot_vec.size(); i++)
        {
                if (rect_itemslot_vec[i].second->item() != nullptr)
                {
                    if (rect_itemslot_vec[i].first.CheckInteraction(data_mouse.pos_screencoord.x, data_mouse.pos_screencoord.y) == true)
                    {
                        m_Player->GetCursor().SetFocusedObject(rect_itemslot_vec[i].second->item());

                        if (data_mouse.left_click == true)
                        {
                            if (m_Player->GetNpc()->GetCredits() >= rect_itemslot_vec[i].second->item()->GetPrice())
                                {
                                m_Player->GetNpc()->vehicle()->BuyItem(rect_itemslot_vec[i].second->item());
                            }
                        }
                        return true;
                    }
            }
        }

        for (unsigned int i=0; i<rect_vehicleslot_vec.size(); i++)
        {
                if (rect_vehicleslot_vec[i].second->vehicle() != nullptr)
                {
                    if (rect_vehicleslot_vec[i].first.CheckInteraction(data_mouse.pos_screencoord.x, data_mouse.pos_screencoord.y) == true)
                    {
                m_Player->GetCursor().SetFocusedObject(rect_vehicleslot_vec[i].second->vehicle());

                            if (data_mouse.left_click == true)
                            {
                                int price = rect_vehicleslot_vec[i].second->vehicle()->GetKorpusData().price;
                                if (m_Player->GetNpc()->GetCredits() >= price)
                                      {
                                          store->SellVehicle(m_Player->GetNpc(), rect_vehicleslot_vec[i].second, price);
                                                GuiManager::Instance().GetGuiKosmoport().ExitGuiStoreScreen();
                                                GuiManager::Instance().GetGuiKosmoport().EnterGuiStoreScreen();
                                }
                            }
                            return true;
                    }
            }
        }

        return false;
        */

    return false;
}

void GuiStore::renderSlots(int credits) const
{      
    //glPushMatrix();
    //glTranslatef(GetOffset().x, GetOffset().y, 0);
    //for (unsigned int i=0; i<rect_itemslot_vec.size(); i++)
    //{
    //rect_itemslot_vec[i].second->Render(rect_itemslot_vec[i].first, GetOffset());
    //if (rect_itemslot_vec[i].second->item() != nullptr)
    //{
    //if (rect_itemslot_vec[i].second->item()->GetPrice() > credits)
    //{
    //rect_itemslot_vec[i].second->RenderMark(rect_itemslot_vec[i].first, GuiTextureObCollector::Instance().slot_mark_reject);
    //}
    //}
    //}

    //for (unsigned int i=0; i<rect_vehicleslot_vec.size(); i++)
    //{
    //rect_vehicleslot_vec[i].second->Render(rect_vehicleslot_vec[i].first);
    //if (rect_vehicleslot_vec[i].second->vehicle() != nullptr)
    //{
    ////if (rect_vehicleslot_vec[i].second->item()->GetPrice() > credits)
    ////{
    ////rect_vehicleslot_vec[i].second->RenderMark(rect_vehicleslot_vec[i].first, GuiTextureObCollector::Instance().slot_mark_reject);
    ////}
    //}
    //}
    //glPopMatrix();
}

} // namespace gui
