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

GuiVehicle :: GuiVehicle()
{
	textureOb_korpus = NULL;
}

GuiVehicle :: ~GuiVehicle()
{}

void GuiVehicle::BindVehicle(Vehicle* vehicle, float scale, bool simple)
{
	this->simple = simple;

	rect_slot_vec.clear();
	textureOb_korpus = NULL;

	CreateFunctionalItemSlotsGeometry(vehicle, scale);
	if (simple == false)
	{
		CreateKorpusGui(vehicle, scale);
		CreateNonFunctionalItemSlotsGeometry(vehicle, scale);
	}
}	
	
void GuiVehicle::CreateKorpusGui(Vehicle* vehicle, float scale)
{
	textureOb_korpus = vehicle->GetTextureOb();         	

    	float kontur_w, kontur_h;
    	if (textureOb_korpus->GetFrameWidth() > textureOb_korpus->GetFrameHeight())
    	{
        	kontur_w = 500; 
    		vehicle->GetKorpusData().gui_scale = (float)kontur_w/textureOb_korpus->GetFrameWidth();
        	kontur_h = textureOb_korpus->GetFrameHeight() * kontur_w / (float)textureOb_korpus->GetFrameWidth();
    	}
    	else
    	{
        	kontur_h = 500; 
    		vehicle->GetKorpusData().gui_scale = (float)kontur_h/textureOb_korpus->GetFrameHeight();
        	kontur_w = textureOb_korpus->GetFrameWidth() * kontur_h / (float)textureOb_korpus->GetFrameHeight();
    	}               

    	rect_korpus.Set(-kontur_w/2 * scale, -kontur_h/2 * scale, kontur_w * scale, kontur_h * scale); 
}      
  
void GuiVehicle::CreateFunctionalItemSlotsGeometry(Vehicle* vehicle, float scale)
{        
	int weapon_slot_counter = 0;
	int artef_slot_counter = 0;
        for (unsigned int i=0; i<vehicle->slot_total_vec.size(); i++)
        {		
        	switch (vehicle->slot_total_vec[i]->GetSubTypeId())
        	{        
        		case ENTITY::WEAPON_SLOT_ID:
        		{
        		       	Rect rect(-3*GUI::ITEMSLOT::WIDTH_FOR_SHIP + 1.1*weapon_slot_counter*GUI::ITEMSLOT::WIDTH_FOR_SHIP, 
                                          -1*GUI::ITEMSLOT::HEIGHT_FOR_SHIP/2 + 2*1.1*GUI::ITEMSLOT::HEIGHT_FOR_SHIP,
       			                  GUI::ITEMSLOT::WIDTH_FOR_SHIP, GUI::ITEMSLOT::HEIGHT_FOR_SHIP); 
       			     
       			     	rect.Scale(scale);
       			     	GuiPair<ItemSlot*> gui_pair(rect, vehicle->slot_total_vec[i]);
       			     	rect_slot_vec.push_back(gui_pair);
        			weapon_slot_counter++;	
        			
        			break;
        		} 
        		
        		case ENTITY::RADAR_SLOT_ID:
        		{
        		        Rect rect(4*GUI::ITEMSLOT::WIDTH_FOR_SHIP, 
		    			  -1*GUI::ITEMSLOT::HEIGHT_FOR_SHIP/2 + 1.1*GUI::ITEMSLOT::HEIGHT_FOR_SHIP/2,
		    			  GUI::ITEMSLOT::WIDTH_FOR_SHIP, GUI::ITEMSLOT::HEIGHT_FOR_SHIP);
		           		
		           	rect.Scale(scale);	     	
		       		GuiPair<ItemSlot*> gui_pair(rect, vehicle->slot_total_vec[i]);
        			rect_slot_vec.push_back(gui_pair);
        			
        			break;
        		}

        		case ENTITY::SCANER_SLOT_ID:
        		{
				Rect rect(4*GUI::ITEMSLOT::WIDTH_FOR_SHIP, 
		    			  -1*GUI::ITEMSLOT::HEIGHT_FOR_SHIP/2 - 1.1*GUI::ITEMSLOT::HEIGHT_FOR_SHIP/2,
		    			  GUI::ITEMSLOT::WIDTH_FOR_SHIP, GUI::ITEMSLOT::HEIGHT_FOR_SHIP);
		           	
		           	rect.Scale(scale);		     	
		       		GuiPair<ItemSlot*> gui_pair(rect, vehicle->slot_total_vec[i]);
        			rect_slot_vec.push_back(gui_pair);
        			
        			break;
        		}

        		case ENTITY::ENERGIZER_SLOT_ID:
        		{
				Rect rect(-2*GUI::ITEMSLOT::WIDTH_FOR_SHIP, 
		    			  -1*GUI::ITEMSLOT::HEIGHT_FOR_SHIP/2,
		    			  GUI::ITEMSLOT::WIDTH_FOR_SHIP, GUI::ITEMSLOT::HEIGHT_FOR_SHIP);
		           	
		           	rect.Scale(scale);		     	
		       		GuiPair<ItemSlot*> gui_pair(rect, vehicle->slot_total_vec[i]);
        			rect_slot_vec.push_back(gui_pair);
        			
        			break;
        		}

        		case ENTITY::GRAPPLE_SLOT_ID:
        		{
				Rect rect(-3*GUI::ITEMSLOT::WIDTH_FOR_SHIP, 
                                          -GUI::ITEMSLOT::HEIGHT_FOR_SHIP/2 + 1.1*GUI::ITEMSLOT::HEIGHT_FOR_SHIP,
                                          GUI::ITEMSLOT::WIDTH_FOR_SHIP, GUI::ITEMSLOT::HEIGHT_FOR_SHIP);
		           		
		           	rect.Scale(scale);	     	
		       		GuiPair<ItemSlot*> gui_pair(rect, vehicle->slot_total_vec[i]);
        			rect_slot_vec.push_back(gui_pair);
        			
        			break;
        		}

        		case ENTITY::DROID_SLOT_ID:
        		{
				Rect rect(-1*GUI::ITEMSLOT::WIDTH_FOR_SHIP, 
		    			  -1*GUI::ITEMSLOT::HEIGHT_FOR_SHIP/2 + 1.1*GUI::ITEMSLOT::HEIGHT_FOR_SHIP,
		    			  GUI::ITEMSLOT::WIDTH_FOR_SHIP, GUI::ITEMSLOT::HEIGHT_FOR_SHIP);	
		           		
		           	rect.Scale(scale);	     	
		       		GuiPair<ItemSlot*> gui_pair(rect, vehicle->slot_total_vec[i]);
        			rect_slot_vec.push_back(gui_pair);
        			
        			break;
        		}

        		case ENTITY::FREEZER_SLOT_ID:
        		{
				Rect rect(-1*GUI::ITEMSLOT::WIDTH_FOR_SHIP, 
		    			  -1*GUI::ITEMSLOT::HEIGHT_FOR_SHIP/2 - 1.1*GUI::ITEMSLOT::HEIGHT_FOR_SHIP,
		    			  GUI::ITEMSLOT::WIDTH_FOR_SHIP, GUI::ITEMSLOT::HEIGHT_FOR_SHIP);		
		           		
		           	rect.Scale(scale);	     	
		       		GuiPair<ItemSlot*> gui_pair(rect, vehicle->slot_total_vec[i]);
        			rect_slot_vec.push_back(gui_pair);
        			
        			break;
        		}
        		
        		case ENTITY::PROTECTOR_SLOT_ID:
        		{
				Rect rect(-3*GUI::ITEMSLOT::WIDTH_FOR_SHIP, 
		    			  -1*GUI::ITEMSLOT::HEIGHT_FOR_SHIP/2 - 1.1*GUI::ITEMSLOT::HEIGHT_FOR_SHIP,
		                          GUI::ITEMSLOT::WIDTH_FOR_SHIP, GUI::ITEMSLOT::HEIGHT_FOR_SHIP);	 		
		           	
		           	rect.Scale(scale);		     	
		       		GuiPair<ItemSlot*> gui_pair(rect, vehicle->slot_total_vec[i]);
        			rect_slot_vec.push_back(gui_pair);
        			
        			break;
        		}

        		case ENTITY::DRIVE_SLOT_ID:
        		{
				Rect rect(-5*GUI::ITEMSLOT::WIDTH_FOR_SHIP, 
		    			   -1*GUI::ITEMSLOT::HEIGHT_FOR_SHIP/2 + 1.1*GUI::ITEMSLOT::HEIGHT_FOR_SHIP/2,
                    			   GUI::ITEMSLOT::WIDTH_FOR_SHIP, GUI::ITEMSLOT::HEIGHT_FOR_SHIP); 		
		           		
		           	rect.Scale(scale);	     	
		       		GuiPair<ItemSlot*> gui_pair(rect, vehicle->slot_total_vec[i]);
        			rect_slot_vec.push_back(gui_pair);
        			
        			break;
        		}

        		case ENTITY::BAK_SLOT_ID:
        		{
				Rect rect(-5*GUI::ITEMSLOT::WIDTH_FOR_SHIP, 
		    			   -1*GUI::ITEMSLOT::HEIGHT_FOR_SHIP/2 - 1.1*GUI::ITEMSLOT::HEIGHT_FOR_SHIP/2,
		    			   GUI::ITEMSLOT::WIDTH_FOR_SHIP, GUI::ITEMSLOT::HEIGHT_FOR_SHIP);
		    			   		
		           	rect.Scale(scale);		     	
		       		GuiPair<ItemSlot*> gui_pair(rect, vehicle->slot_total_vec[i]);
        			rect_slot_vec.push_back(gui_pair);
        			
        			break;
        		}

        		case ENTITY::ARTEFACT_SLOT_ID:
        		{
   				Rect rect(artef_slot_counter*GUI::ITEMSLOT::WIDTH_FOR_SHIP, 
    	        	    		  4*GUI::ITEMSLOT::HEIGHT_FOR_SHIP,
    		   	    		  GUI::ITEMSLOT::WIDTH_FOR_SHIP, GUI::ITEMSLOT::HEIGHT_FOR_SHIP);	
		           		
		           	rect.Scale(scale);	   
				GuiPair<ItemSlot*> gui_pair(rect, vehicle->slot_total_vec[i]);
        			rect_slot_vec.push_back(gui_pair);
        			artef_slot_counter++;
        			
        			break;
        		}
        	}      
        }    	
}	
 
void GuiVehicle::CreateNonFunctionalItemSlotsGeometry(Vehicle* vehicle, float scale)
{        
	int otsec_slot_counter = 0;
        for (unsigned int i=0; i<vehicle->slot_total_vec.size(); i++)
        {		
        	switch (vehicle->slot_total_vec[i]->GetSubTypeId())
        	{   
      		 	case ENTITY::CARGO_SLOT_ID:
        		{
         			Rect rect((otsec_slot_counter-6)*GUI::ITEMSLOT::WIDTH_FOR_SHIP, 
         		  		   -3*GUI::ITEMSLOT::HEIGHT_FOR_SHIP,
         		  		   GUI::ITEMSLOT::WIDTH_FOR_SHIP, GUI::ITEMSLOT::HEIGHT_FOR_SHIP);  		
		           	
		           	rect.Scale(scale);		   
				GuiPair<ItemSlot*> gui_pair(rect, vehicle->slot_total_vec[i]);
        			rect_slot_vec.push_back(gui_pair);
        			otsec_slot_counter++;
        			
        			break;
        		}
        	}      
        }    		

	// GATE SLOT
   	Rect rect(-5*GUI::ITEMSLOT::WIDTH_FOR_SHIP, 
    		   3*GUI::ITEMSLOT::HEIGHT_FOR_SHIP,
    		   GUI::ITEMSLOT::WIDTH_FOR_SHIP, GUI::ITEMSLOT::HEIGHT_FOR_SHIP);		
		
	rect.Scale(scale);           			   
	GuiPair<ItemSlot*> gui_pair(rect, vehicle->gate_slot);
	rect_slot_vec.push_back(gui_pair);
}	

bool GuiVehicle::UpdateMouseInteractionInSpace(const MouseData& data_mouse)
{
	for(unsigned int i=0; i<rect_slot_vec.size(); i++)
	{ 
		if (rect_slot_vec[i].rect.CheckInteraction(data_mouse.mx - offset.x, data_mouse.my - offset.y) == true)
		{  
			if (data_mouse.left_click == true)
			{
				if (rect_slot_vec[i].object->GetSubTypeId() == ENTITY::GATE_SLOT_ID)
				{
					if (player->GetCursor().GetItemSlot()->GetEquiped() == true)
					{
						player->GetCursor().GetItemSlot()->DropItemToSpace(player->GetNpc()->GetVehicle());
					}
				}
				else
				{
					player->GetCursor().GetItemSlot()->SwapItemWith(rect_slot_vec[i].object);     
				}
			} 
			
			#if DEBUG_ITEMDAMAGELOCKVIAGUI > 0
			{
				switch(DEBUG_ITEMDAMAGELOCKVIAGUI)
				{
					case 1:
					{
						if (rect_slot_vec[i].object->GetEquiped() == true)
						{
							if (data_mouse.right_click == true)
							{
								std::cout<<"DEBUG ACTION in GuiVehicle::UpdateMouseInteractionInSpace, ItemLOck testing"<<std::endl;
								if (rect_slot_vec[i].object->GetItem()->GetFunctioning() == true)
								{
									rect_slot_vec[i].object->GetItem()->LockEvent(2);
								}
								else
								{
									rect_slot_vec[i].object->GetItem()->LockEvent(0);
								}
							}
						}
						
						break;
					}
					
					case 2:
					{						
						if (rect_slot_vec[i].object->GetEquiped() == true)
						{
							if (data_mouse.right_click == true)
							{
								std::cout<<"DEBUG ACTION in GuiVehicle::UpdateMouseInteractionInSpace, Item Damage testing"<<std::endl;
								if (rect_slot_vec[i].object->GetItem()->GetFunctioning() == true)
								{
									rect_slot_vec[i].object->GetItem()->SetCondition(0);
								}
								else
								{
									rect_slot_vec[i].object->GetItem()->SetCondition(1000);
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


ItemSlot* GuiVehicle::GetInreactedItemSlot(const MouseData& data_mouse)
{
	for(unsigned int i=0; i<rect_slot_vec.size(); i++)
	{ 
		if (rect_slot_vec[i].rect.CheckInteraction(data_mouse.mx - offset.x, data_mouse.my - offset.y) == true)
		{  
			if (data_mouse.left_click == true)
			{
				return rect_slot_vec[i].object;
			} 
       		}
        }  
        
        return NULL;                     
}

bool GuiVehicle::UpdateMouseInteractionInStore(const MouseData& data_mouse, Vehicle* vehicle, Store* store)
{
	for(unsigned int i=0; i<rect_slot_vec.size(); i++)
	{ 
		if (rect_slot_vec[i].rect.CheckInteraction(data_mouse.mx - offset.x, data_mouse.my - offset.y) == true)
		{  
			if (data_mouse.left_click == true)
			{
				if (rect_slot_vec[i].object->GetEquiped() == true)
				{
					if (rect_slot_vec[i].object->GetItem()->GetTypeId() != ENTITY::GOODS_ID)
					{
						store->BuyItemFromSlot(player->GetNpc(), rect_slot_vec[i].object);
					}
					else
					{
						store->GetOwnerKosmoport()->GetShop()->BuyGoods(player->GetNpc(), (GoodsPack*)rect_slot_vec[i].object->GetItem());
					}
            			}
			} 
			
			return true;
       		}      
        }
	
	return false;
}

void GuiVehicle::RenderVehicle(const MouseData& data_mouse, int requested_subtype_id) const
{
	glPushMatrix();
		glTranslatef(offset.x, offset.y, 0);
		if (!simple)
		{
			drawTexturedRect(textureOb_korpus, rect_korpus, -1.0);
		}
		RenderSlots();
		if (requested_subtype_id != NONE_ID)
		{
			RenderMarksForEmptySlots(data_mouse, requested_subtype_id);
		}
	glPopMatrix();
}

void GuiVehicle::RenderSlots() const
{
	for(unsigned int i=0; i<rect_slot_vec.size(); i++)
	{
		rect_slot_vec[i].object->Render(rect_slot_vec[i].rect, offset, !simple);
	}
}

void GuiVehicle::RenderMarksForEmptySlots(const MouseData& data_mouse, int requested_subtype_id) const
{
	for(unsigned int i=0; i<rect_slot_vec.size(); i++)
	{
		if ( (rect_slot_vec[i].object->GetEquiped() == false) and (rect_slot_vec[i].object->GetSubTypeId() != ENTITY::CARGO_SLOT_ID) and (rect_slot_vec[i].object->GetSubTypeId() != ENTITY::GATE_SLOT_ID) )
               	{
               		if (requested_subtype_id == rect_slot_vec[i].object->GetSubTypeId())  
               		{
               			rect_slot_vec[i].object->RenderMark(rect_slot_vec[i].rect, GuiTextureObCollector::Instance().slot_mark_accept);
               		}
               		else
               		{
               			if (rect_slot_vec[i].rect.CheckInteraction(data_mouse.mx - offset.x, data_mouse.my - offset.y) == true)
               			{
               				rect_slot_vec[i].object->RenderMark(rect_slot_vec[i].rect, GuiTextureObCollector::Instance().slot_mark_reject);
               			}
               		}
               	}
	}
}

void GuiVehicle::RenderFocusedItemInfo(const MouseData& data_mouse) const
{
	for(unsigned int i=0; i<rect_slot_vec.size(); i++)
	{ 
		if (rect_slot_vec[i].rect.CheckInteraction(data_mouse.mx - offset.x, data_mouse.my - offset.y) == true)
		{  
			rect_slot_vec[i].object->RenderItemInfo(rect_slot_vec[i].rect, -offset.x, -offset.y);
		}
	}
}





