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
#include "../pilots/Player.hpp"
#include "../resources/GuiTextureObCollector.hpp"
#include "../docking/Kosmoport.hpp"
#include "../render/Render.hpp"
#include "../items/BaseItem.hpp"
#include "../slots/ItemSlot.hpp"
#include "../common/myStr.hpp"
#include "../builder/ItemSlotBuilder.hpp"

#include "../pilots/Npc.hpp"

GuiVehicle::GuiVehicle()
{
	textureOb_korpus = NULL;
	gate_slot   = GetNewItemSlotWithoutSaveAbility(ENTITY::GATE_SLOT_ID);
}

GuiVehicle::~GuiVehicle()
{
	delete gate_slot;
}

void GuiVehicle::BindVehicle(Vehicle* vehicle, float scale)
{
	textureOb_korpus = NULL;

	CreateKorpusGui(vehicle, scale);
	CreateItemSlotsGeometry(vehicle, scale);
}	
	
void GuiVehicle::CreateKorpusGui(Vehicle* vehicle, float scale)
{
	textureOb_korpus = vehicle->GetTextureOb();         	

    	float kontur_w, kontur_h;
    	if (textureOb_korpus->GetFrameWidth() > textureOb_korpus->GetFrameHeight())
    	{
        	kontur_w = 500; 
        	kontur_h = textureOb_korpus->GetFrameHeight() * kontur_w / (float)textureOb_korpus->GetFrameWidth();
    	}
    	else
    	{
        	kontur_h = 500; 
        	kontur_w = textureOb_korpus->GetFrameWidth() * kontur_h / (float)textureOb_korpus->GetFrameHeight();
    	}               

    	rect_korpus.Set(-kontur_w/2 * scale, -kontur_h/2 * scale, kontur_w * scale, kontur_h * scale); 
}      
  
void GuiVehicle::CreateItemSlotsGeometry(Vehicle* vehicle, float scale)
{        
	rect_slot_vec.clear();
	
	int weapon_slot_counter = 0;
	int otsec_slot_counter = 0;
	int artef_slot_counter = 0;
        for (unsigned int i=0; i<vehicle->slot_total_vec.size(); i++)
        {		
        	switch (vehicle->slot_total_vec[i]->GetSubTypeId())
        	{        
        		case ENTITY::WEAPON_SLOT_ID:
        		{
        		       	Rect rect(-5*GUI::ITEMSLOT::WIDTH_FOR_SHIP + 1.1*weapon_slot_counter*GUI::ITEMSLOT::WIDTH_FOR_SHIP, 
                                          -1*GUI::ITEMSLOT::HEIGHT_FOR_SHIP/2 + 2*1.1*GUI::ITEMSLOT::HEIGHT_FOR_SHIP,
       			                  GUI::ITEMSLOT::WIDTH_FOR_SHIP, GUI::ITEMSLOT::HEIGHT_FOR_SHIP); 
       			     
       			     	rect.Scale(scale);
       			     	rect_slot_vec.push_back(GuiPair<Rect, ItemSlot*>(rect, vehicle->slot_total_vec[i]));
        			weapon_slot_counter++;	
        			
        			break;
        		} 
        		
        		case ENTITY::RADAR_SLOT_ID:
        		{
        		        Rect rect(0*GUI::ITEMSLOT::WIDTH_FOR_SHIP, 
		    			  -1*GUI::ITEMSLOT::HEIGHT_FOR_SHIP/2 + 1.1*GUI::ITEMSLOT::HEIGHT_FOR_SHIP/2,
		    			  GUI::ITEMSLOT::WIDTH_FOR_SHIP, GUI::ITEMSLOT::HEIGHT_FOR_SHIP);
		           		
		           	rect.Scale(scale);	     	
        			rect_slot_vec.push_back(GuiPair<Rect, ItemSlot*>(rect, vehicle->slot_total_vec[i]));
        			
        			break;
        		}

        		case ENTITY::SCANER_SLOT_ID:
        		{
				Rect rect(0*GUI::ITEMSLOT::WIDTH_FOR_SHIP, 
		    			  -1*GUI::ITEMSLOT::HEIGHT_FOR_SHIP/2 - 1.1*GUI::ITEMSLOT::HEIGHT_FOR_SHIP/2,
		    			  GUI::ITEMSLOT::WIDTH_FOR_SHIP, GUI::ITEMSLOT::HEIGHT_FOR_SHIP);
		           	
		           	rect.Scale(scale);		     	
        			rect_slot_vec.push_back(GuiPair<Rect, ItemSlot*>(rect, vehicle->slot_total_vec[i]));
        			
        			break;
        		}

        		case ENTITY::ENERGIZER_SLOT_ID:
        		{
				Rect rect(-2*GUI::ITEMSLOT::WIDTH_FOR_SHIP, 
		    			  -1*GUI::ITEMSLOT::HEIGHT_FOR_SHIP/2,
		    			  GUI::ITEMSLOT::WIDTH_FOR_SHIP, GUI::ITEMSLOT::HEIGHT_FOR_SHIP);
		           	
		           	rect.Scale(scale);		     	
        			rect_slot_vec.push_back(GuiPair<Rect, ItemSlot*>(rect, vehicle->slot_total_vec[i]));
        			
        			break;
        		}

        		case ENTITY::GRAPPLE_SLOT_ID:
        		{
				Rect rect(-2.5*GUI::ITEMSLOT::WIDTH_FOR_SHIP, 
                                          -GUI::ITEMSLOT::HEIGHT_FOR_SHIP/2 + 1.1*GUI::ITEMSLOT::HEIGHT_FOR_SHIP,
                                          GUI::ITEMSLOT::WIDTH_FOR_SHIP, GUI::ITEMSLOT::HEIGHT_FOR_SHIP);
		           		
		           	rect.Scale(scale);	     	
        			rect_slot_vec.push_back(GuiPair<Rect, ItemSlot*>(rect, vehicle->slot_total_vec[i]));
        			
        			break;
        		}

        		case ENTITY::DROID_SLOT_ID:
        		{
				Rect rect(-1.5*GUI::ITEMSLOT::WIDTH_FOR_SHIP, 
		    			  -1*GUI::ITEMSLOT::HEIGHT_FOR_SHIP/2 + 1.1*GUI::ITEMSLOT::HEIGHT_FOR_SHIP,
		    			  GUI::ITEMSLOT::WIDTH_FOR_SHIP, GUI::ITEMSLOT::HEIGHT_FOR_SHIP);	
		           		
		           	rect.Scale(scale);	     	
        			rect_slot_vec.push_back(GuiPair<Rect, ItemSlot*>(rect, vehicle->slot_total_vec[i]));
        			
        			break;
        		}

        		case ENTITY::FREEZER_SLOT_ID:
        		{
				Rect rect(-1.5*GUI::ITEMSLOT::WIDTH_FOR_SHIP, 
		    			  -1*GUI::ITEMSLOT::HEIGHT_FOR_SHIP/2 - 1.1*GUI::ITEMSLOT::HEIGHT_FOR_SHIP,
		    			  GUI::ITEMSLOT::WIDTH_FOR_SHIP, GUI::ITEMSLOT::HEIGHT_FOR_SHIP);		
		           		
		           	rect.Scale(scale);	     	
        			rect_slot_vec.push_back(GuiPair<Rect, ItemSlot*>(rect, vehicle->slot_total_vec[i]));
        			
        			break;
        		}
        		
        		case ENTITY::PROTECTOR_SLOT_ID:
        		{
				Rect rect(-2.5*GUI::ITEMSLOT::WIDTH_FOR_SHIP, 
		    			  -1*GUI::ITEMSLOT::HEIGHT_FOR_SHIP/2 - 1.1*GUI::ITEMSLOT::HEIGHT_FOR_SHIP,
		                          GUI::ITEMSLOT::WIDTH_FOR_SHIP, GUI::ITEMSLOT::HEIGHT_FOR_SHIP);	 		
		           	
		           	rect.Scale(scale);		     	
        			rect_slot_vec.push_back(GuiPair<Rect, ItemSlot*>(rect, vehicle->slot_total_vec[i]));
        			
        			break;
        		}

        		case ENTITY::DRIVE_SLOT_ID:
        		{
				Rect rect(-4*GUI::ITEMSLOT::WIDTH_FOR_SHIP, 
		    			   -1*GUI::ITEMSLOT::HEIGHT_FOR_SHIP/2 + 1.1*GUI::ITEMSLOT::HEIGHT_FOR_SHIP/2,
                    			   GUI::ITEMSLOT::WIDTH_FOR_SHIP, GUI::ITEMSLOT::HEIGHT_FOR_SHIP); 		
		           		
		           	rect.Scale(scale);	     	
        			rect_slot_vec.push_back(GuiPair<Rect, ItemSlot*>(rect, vehicle->slot_total_vec[i]));
        			
        			break;
        		}

        		case ENTITY::BAK_SLOT_ID:
        		{
				Rect rect(-4*GUI::ITEMSLOT::WIDTH_FOR_SHIP, 
		    			   -1*GUI::ITEMSLOT::HEIGHT_FOR_SHIP/2 - 1.1*GUI::ITEMSLOT::HEIGHT_FOR_SHIP/2,
		    			   GUI::ITEMSLOT::WIDTH_FOR_SHIP, GUI::ITEMSLOT::HEIGHT_FOR_SHIP);
		    			   		
		           	rect.Scale(scale);		     	
        			rect_slot_vec.push_back(GuiPair<Rect, ItemSlot*>(rect, vehicle->slot_total_vec[i]));
        			
        			break;
        		}
        		
        		case ENTITY::CARGO_SLOT_ID:
        		{
         			Rect rect((otsec_slot_counter-6)*GUI::ITEMSLOT::WIDTH_FOR_SHIP, 
         		  		   -3*GUI::ITEMSLOT::HEIGHT_FOR_SHIP,
         		  		   GUI::ITEMSLOT::WIDTH_FOR_SHIP, GUI::ITEMSLOT::HEIGHT_FOR_SHIP);  		
		           	
		           	rect.Scale(scale);		   
        			rect_slot_vec.push_back(GuiPair<Rect, ItemSlot*>(rect, vehicle->slot_total_vec[i]));
        			otsec_slot_counter++;
        			
        			break;
        		}

        		case ENTITY::ARTEFACT_SLOT_ID:
        		{
   				Rect rect(0*GUI::ITEMSLOT::WIDTH_FOR_SHIP + artef_slot_counter*GUI::ITEMSLOT::WIDTH_FOR_SHIP/2, 
    	        	    		  -1.7*GUI::ITEMSLOT::HEIGHT_FOR_SHIP,
    		   	    		  GUI::ITEMSLOT::WIDTH_FOR_SHIP/2, GUI::ITEMSLOT::HEIGHT_FOR_SHIP/2);	
		           		
		           	rect.Scale(scale);	   
        			rect_slot_vec.push_back(GuiPair<Rect, ItemSlot*>(rect, vehicle->slot_total_vec[i]));
        			artef_slot_counter++;
        			
        			break;
        		}
        	}      
        }
        
        // GATE SLOT
   	Rect rect(-5*GUI::ITEMSLOT::WIDTH_FOR_SHIP, 
    		   3*GUI::ITEMSLOT::HEIGHT_FOR_SHIP,
    		   GUI::ITEMSLOT::WIDTH_FOR_SHIP, GUI::ITEMSLOT::HEIGHT_FOR_SHIP);		
		
	rect.Scale(scale);           			   
	rect_slot_vec.push_back(GuiPair<Rect, ItemSlot*>(rect, gate_slot));    		
} 

bool GuiVehicle::UpdateMouseInteractionInSpace(const MouseData& data_mouse, bool control)
{
	for(unsigned int i=0; i<rect_slot_vec.size(); i++)
	{ 
		if (rect_slot_vec[i].first.CheckInteraction(data_mouse.mx - offset.x, data_mouse.my - offset.y) == true)
		{  
			if ( (rect_slot_vec[i].second->GetEquiped() == true) and (player->GetCursor().GetItemSlot()->GetEquiped() == false) )
			{
				player->GetCursor().SetFocusedObject(rect_slot_vec[i].second->GetItem());
			}
						
			if ( (data_mouse.left_click == true) and (control == true) )
			{
				if (rect_slot_vec[i].second->GetSubTypeId() != ENTITY::GATE_SLOT_ID)
				{
					player->GetCursor().GetItemSlot()->SwapItem(rect_slot_vec[i].second); 
				}
				else
				{
					if (player->GetCursor().GetItemSlot()->GetEquiped() == true)
					{
						if (player->GetNpc()->GetVehicle()->GetPlaceTypeId() == ENTITY::SPACE_ID)
						{
							player->GetCursor().GetItemSlot()->DropItemToSpace(player->GetNpc()->GetVehicle());
						}
						else
						{
							player->GetNpc()->GetVehicle()->SellItem(player->GetCursor().GetItemSlot()->GetItem());
						}
					}    
				}
			} 
			
			#if DEBUG_ITEMDAMAGELOCKVIAGUI > 0
			{
				switch(DEBUG_ITEMDAMAGELOCKVIAGUI)
				{
					case 1:
					{
						if (rect_slot_vec[i].second->GetEquiped() == true)
						{
							if (data_mouse.right_click == true)
							{
								std::cout<<"DEBUG ACTION in GuiVehicle::UpdateMouseInteractionInSpace, ItemLOck testing"<<std::endl;
								if (rect_slot_vec[i].second->GetItem()->GetFunctioning() == true)
								{
									rect_slot_vec[i].second->GetItem()->LockEvent(2);
								}
								else
								{
									rect_slot_vec[i].second->GetItem()->LockEvent(0);
								}
							}
						}
						
						break;
					}
					
					case 2:
					{						
						if (rect_slot_vec[i].second->GetEquiped() == true)
						{
							if (data_mouse.right_click == true)
							{
								std::cout<<"DEBUG ACTION in GuiVehicle::UpdateMouseInteractionInSpace, Item Damage testing"<<std::endl;
								if (rect_slot_vec[i].second->GetItem()->GetFunctioning() == true)
								{
									rect_slot_vec[i].second->GetItem()->SetCondition(0);
								}
								else
								{
									rect_slot_vec[i].second->GetItem()->SetCondition(1000);
								}
							}
						}
						
						break;
					}
				}
			}
			#endif
			
			return true;
       		}
        }                       

	return false;
}

bool GuiVehicle::UpdateMouseInteractionInStore(const MouseData& data_mouse, Vehicle* vehicle, Store* store)
{
	for(unsigned int i=0; i<rect_slot_vec.size(); i++)
	{ 
		if (rect_slot_vec[i].first.CheckInteraction(data_mouse.mx - offset.x, data_mouse.my - offset.y) == true)
		{  
			if (rect_slot_vec[i].second->GetEquiped() == true)
			{
				player->GetCursor().SetFocusedObject(rect_slot_vec[i].second->GetItem());
							
				if (data_mouse.left_click == true)
				{
					vehicle->SellItem(rect_slot_vec[i].second->GetItem());
            			}
			} 
			
			return true;
       		}      
        }
	
	return false;
}

void GuiVehicle::RenderVehicle(const MouseData& data_mouse, int mark_slot_subtype_id) const
{
	glPushMatrix();
		glTranslatef(offset.x, offset.y, 0);
		drawTexturedRect(textureOb_korpus, rect_korpus, -1.0);
		RenderSlots();
		if (mark_slot_subtype_id != NONE_ID)
		{
			RenderMarksForEmptySlots(data_mouse, mark_slot_subtype_id);
		}
	glPopMatrix();
}

void GuiVehicle::RenderSlots() const
{	
	for(unsigned int i=0; i<rect_slot_vec.size(); i++)
	{
		rect_slot_vec[i].second->Render(rect_slot_vec[i].first, offset);
	}
}

void GuiVehicle::RenderMarksForEmptySlots(const MouseData& data_mouse, int mark_slot_subtype_id) const
{
	for(unsigned int i=0; i<rect_slot_vec.size(); i++)
	{
		if (rect_slot_vec[i].second->GetEquiped() == false) 
		{
			if ( (rect_slot_vec[i].second->GetSubTypeId() != ENTITY::CARGO_SLOT_ID) and (rect_slot_vec[i].second->GetSubTypeId() != ENTITY::GATE_SLOT_ID) )
               		{
               			if (mark_slot_subtype_id == rect_slot_vec[i].second->GetSubTypeId())  
               			{
               				rect_slot_vec[i].second->RenderMark(rect_slot_vec[i].first, GuiTextureObCollector::Instance().slot_mark_accept);
               			}
               			else
               			{
               				if (rect_slot_vec[i].first.CheckInteraction(data_mouse.mx - offset.x, data_mouse.my - offset.y) == true)
	               			{
	               				rect_slot_vec[i].second->RenderMark(rect_slot_vec[i].first, GuiTextureObCollector::Instance().slot_mark_reject);
	               			}
               			}
               		}
		}
	}
}







