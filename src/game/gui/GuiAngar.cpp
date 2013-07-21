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
#include "../docking/Angar.hpp"
#include "ButtonSingle.hpp"
#include "../config/config.hpp"
#include "../slots/VehicleSlot.hpp"
#include "../slots/ItemSlot.hpp"
#include "../items/BaseItem.hpp"
#include "../resources/GuiTextureObCollector.hpp"

#include "../spaceobjects/Vehicle.hpp"

#include "../pilots/Player.hpp"
#include "../pilots/Npc.hpp"

#include "../builder/ItemSlotBuilder.hpp"

#include "../render/Render.hpp"
#include "../gui/GuiManager.hpp"

GuiAngar::GuiAngar():angar(nullptr)
{
	int screen_w = Config::Instance().SCREEN_WIDTH;
	int screen_h = Config::Instance().SCREEN_HEIGHT;
	
	TextureOb* texOb_button = GuiTextureObCollector::Instance().dot_green; // fake
	
	float zpos = -1;
	float zsize = 1;
	
	{
		//ButtonSingle* repair_button = new ButtonSingle(texOb_button, GUI::BUTTON::BUYARMOR_ID, "buy_repair");
		//Vec3<float> center(screen_w - 1 * (GUI::ICON_SIZE + 5), screen_h - 2 * GUI::ICON_SIZE, zpos); 
		//Vec3<float> size(GUI::ICON_SIZE, GUI::ICON_SIZE, zsize);
		//Box box(center, size);		
		//repair_button->SetBox(box);
		//button_map.insert(std::make_pair(GUI::BUTTON::BUYARMOR_ID, repair_button));
	}
	
	{			   
		//ButtonSingle* fuel_button = new ButtonSingle(texOb_button, GUI::BUTTON::BUYFUEL_ID, "buy fuel");  
		//Vec3<float> center(screen_w - 1 * (GUI::ICON_SIZE + 5), screen_h - 3*GUI::ICON_SIZE, zpos); 
		//Vec3<float> size(GUI::ICON_SIZE, GUI::ICON_SIZE, zsize);
		//Box box(center, size);		
		//fuel_button->SetBox(box);
		//button_map.insert(std::make_pair(GUI::BUTTON::BUYFUEL_ID, fuel_button));
	}
		
	{		   
		//ButtonSingle* launch_button = new ButtonSingle(texOb_button, GUI::BUTTON::GETLAUNCH_ID, "launch");
		//Vec3<float> center(screen_w - 1 * (GUI::ICON_SIZE + 5), screen_h - 4*GUI::ICON_SIZE, zpos); 
		//Vec3<float> size(GUI::ICON_SIZE, GUI::ICON_SIZE, zsize);
		//Box box(center, size);		
		//launch_button->SetBox(box);
		//button_map.insert(std::make_pair(GUI::BUTTON::GETLAUNCH_ID, launch_button));
	}
	
	repair_slot = GetNewItemSlotWithoutSaveAbility(ENTITY::TYPE::REPAIR_SLOT_ID);
	charge_slot = GetNewItemSlotWithoutSaveAbility(ENTITY::TYPE::CHARGE_SLOT_ID);
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
        for (int i=0; i<angar->vehicle_visitors_slot_vec.size(); i++)
 	{
 		Rect _rect(column_counter*GUI::VEHICLESLOT::WIDTH_FOR_ANGAR, row_counter*GUI::VEHICLESLOT::HEIGHT_FOR_ANGAR, 
 			   GUI::VEHICLESLOT::WIDTH_FOR_ANGAR, GUI::VEHICLESLOT::HEIGHT_FOR_ANGAR);
        	rect_vehicleslot_vec.push_back(GuiPair<Rect, VehicleSlot*>(_rect, angar->vehicle_visitors_slot_vec[i]));
                
                column_counter++;                
	}
        
        column_counter = 1;
        row_counter = 2;
        for (int i=0; i<angar->vehicle_military_slot_vec.size(); i++)
 	{
 		Rect _rect(column_counter*GUI::VEHICLESLOT::WIDTH_FOR_ANGAR, row_counter*GUI::VEHICLESLOT::HEIGHT_FOR_ANGAR, 
 			   GUI::VEHICLESLOT::WIDTH_FOR_ANGAR, GUI::VEHICLESLOT::HEIGHT_FOR_ANGAR);
        	rect_vehicleslot_vec.push_back(GuiPair<Rect, VehicleSlot*>(_rect, angar->vehicle_military_slot_vec[i]));
                
                column_counter++;                
	}
	
	column_counter = 0;
        row_counter = 0;
        for (int i=0; i<angar->item_slot_vec.size(); i++)
 	{
 		Rect _rect(column_counter*GUI::ITEMSLOT::WIDTH_FOR_ANGAR, row_counter*GUI::ITEMSLOT::HEIGHT_FOR_ANGAR, 
 			   GUI::ITEMSLOT::WIDTH_FOR_ANGAR, GUI::ITEMSLOT::HEIGHT_FOR_ANGAR);
        	rect_itemslot_vec.push_back(GuiPair<Rect, ItemSlot*>(_rect, angar->item_slot_vec[i]));
                
                row_counter++;                
	}
	
        {
   	Rect rect(GUI::ITEMSLOT::WIDTH_FOR_SHIP, 
    		   3*GUI::ITEMSLOT::HEIGHT_FOR_SHIP,
    		   GUI::ITEMSLOT::WIDTH_FOR_SHIP, GUI::ITEMSLOT::HEIGHT_FOR_SHIP);
	rect_itemslot_vec.push_back(GuiPair<Rect, ItemSlot*>(rect, repair_slot));   
        }

        {
        Rect rect(GUI::ITEMSLOT::WIDTH_FOR_SHIP, 
    		   4*GUI::ITEMSLOT::HEIGHT_FOR_SHIP,
    		   GUI::ITEMSLOT::WIDTH_FOR_SHIP, GUI::ITEMSLOT::HEIGHT_FOR_SHIP);
	rect_itemslot_vec.push_back(GuiPair<Rect, ItemSlot*>(rect, charge_slot));  
        }
}

void GuiAngar::UnbindAngar()
{
	angar = nullptr;
	
	rect_vehicleslot_vec.clear();
	rect_itemslot_vec.clear();
}

void GuiAngar::CheckButtonsLock()
{    	   	
	//if (player->GetNpc()->GetVehicle()->IsFuelFull() == true) 	{ GetButton(GUI::BUTTON::BUYFUEL_ID)->LockOn(); }
	//else								{ GetButton(GUI::BUTTON::BUYFUEL_ID)->LockOff(); }

	//if (player->GetNpc()->GetVehicle()->IsArmorFull() == true) 	{ GetButton(GUI::BUTTON::BUYARMOR_ID)->LockOn(); }
	//else								{ GetButton(GUI::BUTTON::BUYARMOR_ID)->LockOff(); }
}

void GuiAngar::ButtonsAction() const     
{
	//for (std::map<int, BaseButton*>::const_iterator iterator = button_map.begin(); iterator!=button_map.end(); iterator++)
	//{
		//BaseButton* button = iterator->second;
		//if (button->GetPressed() == true)
		//{
			//switch(button->GetSubTypeId())
	   		//{
	   			//case GUI::BUTTON::BUYARMOR_ID: 
	   			//{
	   				//if (button->GetLock() == false)
	   				//{  			
						//button->OnPressEventLMB(player);
						
						//angar->RepairVehicle(player->GetNpc()->GetVehicle());
						//return; 
	   				//}
	   						
	   				//break;
	  	 		//}
	   		
	   			//case GUI::BUTTON::BUYFUEL_ID:
	   			//{
	   				//if (button->GetLock() == false)
	   				//{
						//button->OnPressEventLMB(player);
						
						//angar->TankUpVehicle(player->GetNpc()->GetVehicle());
						//return; 
	   				//}
                        
	   				//break;
	   			//}
	   			
	   			//case GUI::BUTTON::GETLAUNCH_ID:
	   			//{
       					//player->GetNpc()->GetVehicle()->LaunchingEvent();

       		   			//return; 
 
       		   			//break;
       		   		//}
       			//}
        	//}
        //}
}

bool GuiAngar::UpdateMouseInteractionWithVehicleSlots(const MouseData& data_mouse)
{	
        for (unsigned int i=0; i<rect_vehicleslot_vec.size(); i++)
        { 
                if (rect_vehicleslot_vec[i].first.CheckInteraction(data_mouse.pos_screencoord) == true)
                {         
                       	if (data_mouse.right_click == true)
                       	{
                 		m_Player->GetNpc()->SetScanTarget(rect_vehicleslot_vec[i].second->GetVehicle());
                                GuiManager::Instance().GetGuiKosmoport().EnterGuiScanInAngar();
                                return true;
                        }
                        
                        if (rect_vehicleslot_vec[i].second->GetVehicle() != nullptr)
                        {       
                        	m_Player->GetCursor().SetFocusedObject(rect_vehicleslot_vec[i].second->GetVehicle());
                        }           
                                   
                }
        }

        for (unsigned int i=0; i<rect_itemslot_vec.size(); i++)
        { 
                if (rect_itemslot_vec[i].first.CheckInteraction(data_mouse.pos_screencoord) == true)
                {
                	if (data_mouse.left_click == true)
                        {
                		switch (rect_itemslot_vec[i].second->GetSubTypeId())
                                {
                                        case ENTITY::TYPE::REPAIR_SLOT_ID:
                                        {        
                                                if (m_Player->GetCursor().GetItemSlot()->GetItem() != nullptr)
                                                {                                        
                                                        angar->RepairItem(m_Player->GetNpc(), m_Player->GetCursor().GetItemSlot()->GetItem());
                                                }
                                                
                                                break;
                                        }
                                        
                                        case ENTITY::TYPE::CHARGE_SLOT_ID:
                                        {
                                                if (m_Player->GetCursor().GetItemSlot()->GetItem() != nullptr)
                                                {
                                                        switch (m_Player->GetCursor().GetItemSlot()->GetItem()->GetSubTypeId())
                                                        {
                                                                case ENTITY::TYPE::ROCKET_EQUIPMENT_ID:
                                                                {
                                                                        angar->ChargeRocketEquipment(m_Player->GetNpc(), (RocketEquipment*)m_Player->GetCursor().GetItemSlot()->GetItem());
                                                                        
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
                        	
                        if (rect_itemslot_vec[i].second->GetItem() != nullptr)
                        {                         
                		m_Player->GetCursor().SetFocusedObject(rect_itemslot_vec[i].second->GetItem());
                	}
                }
        }
                
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

           
