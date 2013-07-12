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
#include "../spaceobjects/Vehicle.hpp"
#include "ButtonItemSlot.hpp"
         
GuiVehicle::GuiVehicle()
{
	textureOb_korpus = nullptr;
	vehicle = nullptr;
	gate_slot   = GetNewItemSlotWithoutSaveAbility(ENTITY::GATE_SLOT_ID);
	
	allow_full_control = false;
	block_manual_exit  = false;
}

GuiVehicle::~GuiVehicle()
{
	delete gate_slot;
}

void GuiVehicle::BindVehicle(Vehicle* vehicle, const Vec2<float>& gui_offset, bool allow_full_control, bool block_manual_exit, float scale)
{      
	this->vehicle = vehicle;  
	SetOffset(gui_offset);
	this->allow_full_control = allow_full_control;
	this->block_manual_exit = block_manual_exit;
                
	textureOb_korpus = nullptr;

	CreateKorpusGui(vehicle, scale);
	CreateItemSlotsGeometry(vehicle, scale);
}

void GuiVehicle::UnbindVehicle()
{
    for (unsigned int i=0; i<m_Child_vec.size(); i++)
    {
        delete m_Child_vec[i];
    }
	m_Child_vec.clear();
	vehicle = nullptr;
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
	int weapon_slot_counter = 0;
	int otsec_slot_counter = 0;
	int artef_slot_counter = 0;
	
	float zpos = -2;
	float zsize = 1;
	
    for (const auto itemslot : vehicle->slot_total_vec)
    {
        switch (itemslot->GetSubTypeId())
        {        
            case ENTITY::WEAPON_SLOT_ID:
            {
                Vec3<float> size(GUI::ITEMSLOT::WIDTH_FOR_SHIP, GUI::ITEMSLOT::HEIGHT_FOR_SHIP, zsize);
                Box box(size*scale); 
                 
                ButtonItemSlot* button = new ButtonItemSlot(ENTITY::WEAPON_SLOT_ID, "ENTITY::WEAPON_SLOT_ID", itemslot);
                button->SetBox(box);
                Vec3<float> offset(-5*GUI::ITEMSLOT::WIDTH_FOR_SHIP + 1.1*weapon_slot_counter*GUI::ITEMSLOT::WIDTH_FOR_SHIP,
                                   -1*GUI::ITEMSLOT::HEIGHT_FOR_SHIP/2 + 2*1.1*GUI::ITEMSLOT::HEIGHT_FOR_SHIP,
                                   0);
                               
                AddChild(button, offset);
                weapon_slot_counter++;	
                
                break;
            } 
            
            case ENTITY::RADAR_SLOT_ID:
            {
                Vec3<float> size(GUI::ITEMSLOT::WIDTH_FOR_SHIP, GUI::ITEMSLOT::HEIGHT_FOR_SHIP, zsize);
                Box box(size*scale);
                    
                ButtonItemSlot* button = new ButtonItemSlot(ENTITY::WEAPON_SLOT_ID, "ENTITY::RADAR_SLOT_ID", itemslot);
                button->SetBox(box);
                Vec3<float> offset( 0*GUI::ITEMSLOT::WIDTH_FOR_SHIP,
                                   -1*GUI::ITEMSLOT::HEIGHT_FOR_SHIP/2 + 1.1*GUI::ITEMSLOT::HEIGHT_FOR_SHIP/2,
                                    0);
                AddChild(button, offset);
                
                break;
            }

        		//case ENTITY::SCANER_SLOT_ID:
        		//{
        		        //Vec3<float> center( 0*GUI::ITEMSLOT::WIDTH_FOR_SHIP,
        				           //-1*GUI::ITEMSLOT::HEIGHT_FOR_SHIP/2 - 1.1*GUI::ITEMSLOT::HEIGHT_FOR_SHIP/2,
        				           //zpos);
        			//Vec3<float> size(GUI::ITEMSLOT::WIDTH_FOR_SHIP, GUI::ITEMSLOT::HEIGHT_FOR_SHIP, zsize);
        		        //Box quad(center*scale, size*scale);
		           	
       			     	//GuiItemSlot gui_itemslot(vehicle->slot_total_vec[i], quad);
       			     	//gui_itemslot_vec.push_back(gui_itemslot);
        			
        			//break;
        		//}

        		//case ENTITY::ENERGIZER_SLOT_ID:
        		//{
        		        //Vec3<float> center(-2*GUI::ITEMSLOT::WIDTH_FOR_SHIP, 
		    			  	   //-1*GUI::ITEMSLOT::HEIGHT_FOR_SHIP/2,
        				           //zpos);
        			//Vec3<float> size(GUI::ITEMSLOT::WIDTH_FOR_SHIP, GUI::ITEMSLOT::HEIGHT_FOR_SHIP, zsize);
        		        //Box quad(center*scale, size*scale);
        		        
       			     	//GuiItemSlot gui_itemslot(vehicle->slot_total_vec[i], quad);
       			     	//gui_itemslot_vec.push_back(gui_itemslot);
        			
        			//break;
        		//}

        		//case ENTITY::GRAPPLE_SLOT_ID:
        		//{
        		        //Vec3<float> center(-2.5*GUI::ITEMSLOT::WIDTH_FOR_SHIP, 
                                          	   //-GUI::ITEMSLOT::HEIGHT_FOR_SHIP/2 + 1.1*GUI::ITEMSLOT::HEIGHT_FOR_SHIP,
        				           //zpos);
        			//Vec3<float> size(GUI::ITEMSLOT::WIDTH_FOR_SHIP, GUI::ITEMSLOT::HEIGHT_FOR_SHIP, zsize);
        		        //Box quad(center*scale, size*scale);
        		        
       			     	//GuiItemSlot gui_itemslot(vehicle->slot_total_vec[i], quad);
       			     	//gui_itemslot_vec.push_back(gui_itemslot);
        			
        			//break;
        		//}

        		//case ENTITY::DROID_SLOT_ID:
        		//{
        		        //Vec3<float> center(-1.5*GUI::ITEMSLOT::WIDTH_FOR_SHIP, 
		    			           //-1*GUI::ITEMSLOT::HEIGHT_FOR_SHIP/2 + 1.1*GUI::ITEMSLOT::HEIGHT_FOR_SHIP,
        				           //zpos);
        			//Vec3<float> size(GUI::ITEMSLOT::WIDTH_FOR_SHIP, GUI::ITEMSLOT::HEIGHT_FOR_SHIP, zsize);
        		        //Box quad(center*scale, size*scale);
        		        
       			     	//GuiItemSlot gui_itemslot(vehicle->slot_total_vec[i], quad);
       			     	//gui_itemslot_vec.push_back(gui_itemslot);
        			
        			//break;
        		//}

        		//case ENTITY::FREEZER_SLOT_ID:
        		//{
        		        //Vec3<float> center(-1.5*GUI::ITEMSLOT::WIDTH_FOR_SHIP, 
		    			           //-1*GUI::ITEMSLOT::HEIGHT_FOR_SHIP/2 - 1.1*GUI::ITEMSLOT::HEIGHT_FOR_SHIP,
        				           //zpos);
        			//Vec3<float> size(GUI::ITEMSLOT::WIDTH_FOR_SHIP, GUI::ITEMSLOT::HEIGHT_FOR_SHIP, zsize);
        		        //Box quad(center*scale, size*scale);
        		        
       			     	//GuiItemSlot gui_itemslot(vehicle->slot_total_vec[i], quad);
       			     	//gui_itemslot_vec.push_back(gui_itemslot);
        			
        			//break;
        		//}
        		
        		//case ENTITY::PROTECTOR_SLOT_ID:
        		//{
        		        //Vec3<float> center(-2.5*GUI::ITEMSLOT::WIDTH_FOR_SHIP, 
		    			           //-1*GUI::ITEMSLOT::HEIGHT_FOR_SHIP/2 - 1.1*GUI::ITEMSLOT::HEIGHT_FOR_SHIP,
        				           //zpos);
        			//Vec3<float> size(GUI::ITEMSLOT::WIDTH_FOR_SHIP, GUI::ITEMSLOT::HEIGHT_FOR_SHIP, zsize);
        		        //Box quad(center*scale, size*scale);
        		        
       			     	//GuiItemSlot gui_itemslot(vehicle->slot_total_vec[i], quad);
       			     	//gui_itemslot_vec.push_back(gui_itemslot);
        			
        			//break;
        		//}

        		//case ENTITY::DRIVE_SLOT_ID:
        		//{
        		        //Vec3<float> center(-4*GUI::ITEMSLOT::WIDTH_FOR_SHIP, 
		    			           //-1*GUI::ITEMSLOT::HEIGHT_FOR_SHIP/2 + 1.1*GUI::ITEMSLOT::HEIGHT_FOR_SHIP/2,
        				           //zpos);
        			//Vec3<float> size(GUI::ITEMSLOT::WIDTH_FOR_SHIP, GUI::ITEMSLOT::HEIGHT_FOR_SHIP, zsize);
        		        //Box quad(center*scale, size*scale);
        		        
       			     	//GuiItemSlot gui_itemslot(vehicle->slot_total_vec[i], quad);
       			     	//gui_itemslot_vec.push_back(gui_itemslot);
        			
        			//break;
        		//}

        		//case ENTITY::BAK_SLOT_ID:
        		//{
        		        //Vec3<float> center(-4*GUI::ITEMSLOT::WIDTH_FOR_SHIP, 
		    			           //-1*GUI::ITEMSLOT::HEIGHT_FOR_SHIP/2 - 1.1*GUI::ITEMSLOT::HEIGHT_FOR_SHIP/2,
        				           //zpos);
        			//Vec3<float> size(GUI::ITEMSLOT::WIDTH_FOR_SHIP, GUI::ITEMSLOT::HEIGHT_FOR_SHIP, zsize);
        		        //Box quad(center*scale, size*scale);
        		        
       			     	//GuiItemSlot gui_itemslot(vehicle->slot_total_vec[i], quad);
       			     	//gui_itemslot_vec.push_back(gui_itemslot);
        			
        			//break;
        		//}
        		
            case ENTITY::CARGO_SLOT_ID:
            {

                Vec3<float> size(GUI::ITEMSLOT::WIDTH_FOR_SHIP, GUI::ITEMSLOT::HEIGHT_FOR_SHIP, zsize);
                Box box(size*scale);
                    
                Vec3<float> offset((otsec_slot_counter-6)*GUI::ITEMSLOT::WIDTH_FOR_SHIP, 
                                  -3*GUI::ITEMSLOT::HEIGHT_FOR_SHIP,
                                  0);
                                  
                ButtonItemSlot* button = new ButtonItemSlot(ENTITY::CARGO_SLOT_ID, "ENTITY::CARGO_SLOT_ID", itemslot);
                button->SetBox(box);
                
                AddChild(button, offset);
                otsec_slot_counter++;
                
                break;
            }

        		//case ENTITY::ARTEFACT_SLOT_ID:
        		//{
        		        //Vec3<float> center(0*GUI::ITEMSLOT::WIDTH_FOR_SHIP + artef_slot_counter*GUI::ITEMSLOT::WIDTH_FOR_SHIP/2, 
    	        	    		           //-1.7*GUI::ITEMSLOT::HEIGHT_FOR_SHIP,
        				           //zpos);
        			//Vec3<float> size(GUI::ITEMSLOT::WIDTH_FOR_SHIP, GUI::ITEMSLOT::HEIGHT_FOR_SHIP, zsize);
        		        //Box quad(center*scale, size*scale);
        		        
       			     	//GuiItemSlot gui_itemslot(vehicle->slot_total_vec[i], quad);
       			     	//gui_itemslot_vec.push_back(gui_itemslot);
        			//artef_slot_counter++;
        			
        			//break;
        		//}
        }      
    }
        
        // GATE SLOT
        //{
	//Vec3<float> center(-5*GUI::ITEMSLOT::WIDTH_FOR_SHIP, 
    		           //3*GUI::ITEMSLOT::HEIGHT_FOR_SHIP,
			   //zpos);
	//Vec3<float> size(GUI::ITEMSLOT::WIDTH_FOR_SHIP, GUI::ITEMSLOT::HEIGHT_FOR_SHIP, zsize);
     	//Box quad(center*scale, size*scale);        		        
      
       	//GuiItemSlot gui_gate(gate_slot, quad);	   			   
	//gui_itemslot_vec.push_back(gui_gate);    		
	//}
} 

bool GuiVehicle::UpdateMouseInteraction(const MouseData& data_mouse)
{    /*
	for(unsigned int i=0; i<gui_itemslot_vec.size(); i++)
	{ 
		if (gui_itemslot_vec[i].GetBox().CheckInteraction(data_mouse.pos_screencoord) == true)
		{  
			if ( (gui_itemslot_vec[i].GetItemSlot()->GetItem() != nullptr) and (m_Player->GetCursor().GetItemSlot()->GetItem() == nullptr) )
			{
				m_Player->GetCursor().SetFocusedObject(gui_itemslot_vec[i].GetItemSlot()->GetItem());
			}
						
			if ( (data_mouse.left_click == true) and (allow_full_control == true) )
			{
				if (gui_itemslot_vec[i].GetItemSlot()->GetSubTypeId() != ENTITY::GATE_SLOT_ID)
				{
					m_Player->GetCursor().GetItemSlot()->SwapItem(gui_itemslot_vec[i].GetItemSlot()); 
				}
				else
				{
					if (m_Player->GetCursor().GetItemSlot()->GetItem() != nullptr)
					{
						if (m_Player->GetNpc()->GetVehicle()->GetPlaceTypeId() == ENTITY::SPACE_ID)
						{
							m_Player->GetCursor().GetItemSlot()->DropItemToSpace(m_Player->GetNpc()->GetVehicle());
						}
						else
						{
							m_Player->GetNpc()->GetVehicle()->SellItem(m_Player->GetCursor().GetItemSlot()->GetItem());
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
						if (gui_itemslot_vec[i].GetItemSlot()->GetItem() != nullptr)
						{
							if (data_mouse.right_click == true)
							{
								std::cout<<"DEBUG ACTION in GuiVehicle::UpdateMouseInteractionInSpace, ItemLOck testing"<<std::endl;
								if (gui_itemslot_vec[i].GetItemSlot()->GetItem()->GetFunctioning() == true)
								{
									gui_itemslot_vec[i].GetItemSlot()->GetItem()->LockEvent(2);
								}
								else
								{
									gui_itemslot_vec[i].GetItemSlot()->GetItem()->LockEvent(0);
								}
							}
						}
						
						break;
					}
					
					case 2:
					{						
						if (gui_itemslot_vec[i].GetItemSlot()->GetItem() != nullptr)
						{
							if (data_mouse.right_click == true)
							{
								std::cout<<"DEBUG ACTION in GuiVehicle::UpdateMouseInteractionInSpace, Item Damage testing"<<std::endl;
								if (gui_itemslot_vec[i].GetItemSlot()->GetItem()->GetFunctioning() == true)
								{
									gui_itemslot_vec[i].GetItemSlot()->GetItem()->SetCondition(0);
								}
								else
								{
									gui_itemslot_vec[i].GetItemSlot()->GetItem()->SetCondition(1000);
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
    */
}

bool GuiVehicle::UpdateMouseInteractionInStore(const MouseData& data_mouse, Store* store)
{ /*
	for(unsigned int i=0; i<gui_itemslot_vec.size(); i++)
	{ 
		if (gui_itemslot_vec[i].GetBox().CheckInteraction(data_mouse.pos_screencoord) == true)
		{  
			if (gui_itemslot_vec[i].GetItemSlot()->GetItem() != nullptr)
			{
				m_Player->GetCursor().SetFocusedObject(gui_itemslot_vec[i].GetItemSlot()->GetItem());
							
				if (data_mouse.left_click == true)
				{
					vehicle->SellItem(gui_itemslot_vec[i].GetItemSlot()->GetItem());
            			}
			} 
			
			return true;
       		}      
        }
	
	return false;
    */
}

void GuiVehicle::RenderVehicle(const MouseData& data_mouse, int mark_slot_subtype_id) const
{
	glPushMatrix();
		glTranslatef(GetOffset().x, GetOffset().y, 0);
		drawTexturedRect(textureOb_korpus, rect_korpus, -1.0);
		RenderSlots();
		if (mark_slot_subtype_id != NONE_ID)
		{
			RenderMarksForEmptySlots(data_mouse, mark_slot_subtype_id);
		}
	glPopMatrix();
}

void GuiVehicle::RenderSlots() const
{	  /*
	for(unsigned int i=0; i<gui_itemslot_vec.size(); i++)
	{
		gui_itemslot_vec[i].GetItemSlot()->Render(gui_itemslot_vec[i].GetBox(), GetOffset());
	}
    */
}

void GuiVehicle::RenderMarksForEmptySlots(const MouseData& data_mouse, int mark_slot_subtype_id) const
{
/*
	for(unsigned int i=0; i<gui_itemslot_vec.size(); i++)
	{
		if (gui_itemslot_vec[i].GetItemSlot()->GetItem() == nullptr) 
		{
			if ( (gui_itemslot_vec[i].GetItemSlot()->GetSubTypeId() != ENTITY::CARGO_SLOT_ID) and (gui_itemslot_vec[i].GetItemSlot()->GetSubTypeId() != ENTITY::GATE_SLOT_ID) )
               		{
               			if (mark_slot_subtype_id == gui_itemslot_vec[i].GetItemSlot()->GetSubTypeId())  
               			{
               				gui_itemslot_vec[i].GetItemSlot()->RenderMark(gui_itemslot_vec[i].GetBox(), GuiTextureObCollector::Instance().slot_mark_accept);
               			}
               			else
               			{
               				if (gui_itemslot_vec[i].GetBox().CheckInteraction(data_mouse.pos_screencoord) == true)
	               			{
	               				gui_itemslot_vec[i].GetItemSlot()->RenderMark(gui_itemslot_vec[i].GetBox(), GuiTextureObCollector::Instance().slot_mark_reject);
	               			}
               			}
               		}
		}
	}
    */
}

/*virtual final*/
void GuiVehicle::UpdateUnique(Player* player)
{
    const BaseSpaceEntity* scan_target = player->GetNpc()->GetScanTarget();
    if (vehicle == nullptr)
    {    
        if (scan_target)
        {
            if (scan_target->GetTypeId() == ENTITY::VEHICLE_ID)
            {
                BindVehicle((Vehicle*)scan_target, /*offset=*/Vec2<float>(0, 0), /*full_control_on*/true);
                return;
            }
        }
    }
     
    if (!scan_target)
    {               
        UnbindVehicle();
    }
}

/*virtual final*/
void GuiVehicle::RenderUnique() const
{
    if (vehicle != nullptr)
    {
        drawTexturedRect(textureOb_korpus, rect_korpus, -1.0);
    }
	//RenderSlots();
	//if (mark_slot_subtype_id != NONE_ID)
	//{
		//RenderMarksForEmptySlots(data_mouse, mark_slot_subtype_id);
	//}
}        
        





