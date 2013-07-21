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
#include "../common/common.hpp"
#include "../builder/ItemSlotBuilder.hpp"

#include "../pilots/Npc.hpp"
#include "../spaceobjects/Vehicle.hpp"
#include "ButtonItemSlot.hpp"
         
GuiVehicle::GuiVehicle(GUI::TYPE subtype_id)
:
BaseGuiElement(subtype_id),
m_TextureOb_korpus(nullptr),
m_Vehicle(nullptr)
{   
    int weapon_slot_max   = SLOT_WEAPON_TYPES.size();
    int otsec_slot_max    = SLOT_CARGO_TYPES.size();
    int artefact_slot_max = SLOT_ARTEFACT_TYPES.size();
    	
	float zpos = -2;
	float zsize = 1;
	
    /** WEAPON SLOTS */
    for (int i=0; i<weapon_slot_max; i++)
    {
        ButtonItemSlot* button = new ButtonItemSlot(GUI::getGuiItemSlotType(SLOT_WEAPON_TYPES[i]), "ENTITY::WEAPON_SLOT_ID");
        
        Vec3<float> size(GUI::ITEMSLOT::WIDTH_FOR_SHIP, GUI::ITEMSLOT::HEIGHT_FOR_SHIP, zsize);
        Box box(size); 
        button->SetBox(box);

        Vec3<float> offset((-5+1.1*i)*GUI::ITEMSLOT::WIDTH_FOR_SHIP,
                           (-1/2+2*1.1)*GUI::ITEMSLOT::HEIGHT_FOR_SHIP,
                           0);
                       
        AddChild(button, offset);
    } 
    
    /** EQUIPMENT SLOTS */
    {
        ButtonItemSlot* button = new ButtonItemSlot(GUI::getGuiItemSlotType(ENTITY::TYPE::RADAR_SLOT_ID), "ENTITY::RADAR_SLOT_ID");
        
        Vec3<float> size(GUI::ITEMSLOT::WIDTH_FOR_SHIP, GUI::ITEMSLOT::HEIGHT_FOR_SHIP, zsize);
        Box box(size);
        button->SetBox(box);
        
        Vec3<float> offset( 0*GUI::ITEMSLOT::WIDTH_FOR_SHIP,
                            -1*GUI::ITEMSLOT::HEIGHT_FOR_SHIP/2 + 1.1*GUI::ITEMSLOT::HEIGHT_FOR_SHIP/2,
                            0);
        AddChild(button, offset);
    }

    {
        ButtonItemSlot* button = new ButtonItemSlot(GUI::getGuiItemSlotType(ENTITY::TYPE::SCANER_SLOT_ID), "ENTITY::SCANER_SLOT_ID");
        Vec3<float> size(GUI::ITEMSLOT::WIDTH_FOR_SHIP, GUI::ITEMSLOT::HEIGHT_FOR_SHIP, zsize);
        Box box(size);
        button->SetBox(box);
                    
        Vec3<float> offset( 0*GUI::ITEMSLOT::WIDTH_FOR_SHIP,
                   -1*GUI::ITEMSLOT::HEIGHT_FOR_SHIP/2 - 1.1*GUI::ITEMSLOT::HEIGHT_FOR_SHIP/2,
                   0);
        AddChild(button, offset);
    }

    {
        ButtonItemSlot* button = new ButtonItemSlot(GUI::getGuiItemSlotType(ENTITY::TYPE::ENERGIZER_SLOT_ID), "ENTITY::ENERGIZER_SLOT_ID");
        Vec3<float> size(GUI::ITEMSLOT::WIDTH_FOR_SHIP, GUI::ITEMSLOT::HEIGHT_FOR_SHIP, zsize);
        Box box(size);
        button->SetBox(box);
                
        Vec3<float> offset(-2*GUI::ITEMSLOT::WIDTH_FOR_SHIP, 
                           -1*GUI::ITEMSLOT::HEIGHT_FOR_SHIP/2,
                            0); 
        AddChild(button, offset);
    }

    {
        ButtonItemSlot* button = new ButtonItemSlot(GUI::getGuiItemSlotType(ENTITY::TYPE::GRAPPLE_SLOT_ID), "ENTITY::GRAPPLE_SLOT_ID");
        Vec3<float> size(GUI::ITEMSLOT::WIDTH_FOR_SHIP, GUI::ITEMSLOT::HEIGHT_FOR_SHIP, zsize);
        Box box(size);
        button->SetBox(box);
        
        Vec3<float> offset(-2.5*GUI::ITEMSLOT::WIDTH_FOR_SHIP, 
                           -GUI::ITEMSLOT::HEIGHT_FOR_SHIP/2 + 1.1*GUI::ITEMSLOT::HEIGHT_FOR_SHIP,
                           0);
        AddChild(button, offset);
    }

    {
        ButtonItemSlot* button = new ButtonItemSlot(GUI::getGuiItemSlotType(ENTITY::TYPE::DROID_SLOT_ID), "ENTITY::DROID_SLOT_ID");
        Vec3<float> size(GUI::ITEMSLOT::WIDTH_FOR_SHIP, GUI::ITEMSLOT::HEIGHT_FOR_SHIP, zsize);
        Box box(size);
        button->SetBox(box);
                            
        Vec3<float> offset(-1.5*GUI::ITEMSLOT::WIDTH_FOR_SHIP, 
                           -1*GUI::ITEMSLOT::HEIGHT_FOR_SHIP/2 + 1.1*GUI::ITEMSLOT::HEIGHT_FOR_SHIP,
                           0);
        AddChild(button, offset);
    }

    //{
        //ButtonItemSlot* button = new ButtonItemSlot(GUI::getEquivalent(ENTITY::TYPE::FREEZER_SLOT_ID), "ENTITY::FREEZER_SLOT_ID");
        //Vec3<float> size(GUI::ITEMSLOT::WIDTH_FOR_SHIP, GUI::ITEMSLOT::HEIGHT_FOR_SHIP, zsize);
        //Box box(size);
        //button->SetBox(box);
                
        //Vec3<float> offset(-1.5*GUI::ITEMSLOT::WIDTH_FOR_SHIP, 
                           //-1*GUI::ITEMSLOT::HEIGHT_FOR_SHIP/2 - 1.1*GUI::ITEMSLOT::HEIGHT_FOR_SHIP,
                            //0);
        //AddChild(button, offset);
    //}
        		
    {
        ButtonItemSlot* button = new ButtonItemSlot(GUI::getGuiItemSlotType(ENTITY::TYPE::PROTECTOR_SLOT_ID), "ENTITY::PROTECTOR_SLOT_ID");
        Vec3<float> size(GUI::ITEMSLOT::WIDTH_FOR_SHIP, GUI::ITEMSLOT::HEIGHT_FOR_SHIP, zsize);
        Box box(size);
        button->SetBox(box);
                
        Vec3<float> offset(-2.5*GUI::ITEMSLOT::WIDTH_FOR_SHIP, 
                           -1*GUI::ITEMSLOT::HEIGHT_FOR_SHIP/2 - 1.1*GUI::ITEMSLOT::HEIGHT_FOR_SHIP,
                           0);
        AddChild(button, offset);
    }

    {
        ButtonItemSlot* button = new ButtonItemSlot(GUI::getGuiItemSlotType(ENTITY::TYPE::DRIVE_SLOT_ID), "ENTITY::DRIVE_SLOT_ID");
        Vec3<float> size(GUI::ITEMSLOT::WIDTH_FOR_SHIP, GUI::ITEMSLOT::HEIGHT_FOR_SHIP, zsize);
        Box box(size);
        button->SetBox(box);
                            
        Vec3<float> offset(-4*GUI::ITEMSLOT::WIDTH_FOR_SHIP, 
                           -1*GUI::ITEMSLOT::HEIGHT_FOR_SHIP/2 + 1.1*GUI::ITEMSLOT::HEIGHT_FOR_SHIP/2,
                           0);
        AddChild(button, offset);
    }

    {
        ButtonItemSlot* button = new ButtonItemSlot(GUI::getGuiItemSlotType(ENTITY::TYPE::BAK_SLOT_ID), "ENTITY::BAK_SLOT_ID");
        Vec3<float> size(GUI::ITEMSLOT::WIDTH_FOR_SHIP, GUI::ITEMSLOT::HEIGHT_FOR_SHIP, zsize);
        Box box(size);
        button->SetBox(box);
                    
        Vec3<float> offset(-4*GUI::ITEMSLOT::WIDTH_FOR_SHIP, 
                           -1*GUI::ITEMSLOT::HEIGHT_FOR_SHIP/2 - 1.1*GUI::ITEMSLOT::HEIGHT_FOR_SHIP/2,
                           0);
        AddChild(button, offset);
    }
    
    /** CARGO SLOTS */    		
    for (int i=0; i<otsec_slot_max; i++)
    {
        float scale_size =1/1.5;
        ButtonItemSlot* button = new ButtonItemSlot(GUI::getGuiItemSlotType(SLOT_CARGO_TYPES[i]), "ENTITY::CARGO_SLOT_ID");
        
        Vec3<float> size(GUI::ITEMSLOT::WIDTH_FOR_SHIP*scale_size, GUI::ITEMSLOT::HEIGHT_FOR_SHIP*scale_size, zsize);
        Box box(size);
        button->SetBox(box);

        Vec3<float> offset((-6+i)*GUI::ITEMSLOT::WIDTH_FOR_SHIP*scale_size, 
                            -3*GUI::ITEMSLOT::HEIGHT_FOR_SHIP,
                            0);        
        AddChild(button, offset);
    }

    /** ARTEFACT SLOTS */
    {
        float scale_size = 1/2.0;
        for (int i=0; i<artefact_slot_max; i++)
        {
            ButtonItemSlot* button = new ButtonItemSlot(GUI::getGuiItemSlotType(SLOT_ARTEFACT_TYPES[i]), "ENTITY::ARTEFACT_SLOT_ID");
            Vec3<float> size(GUI::ITEMSLOT::WIDTH_FOR_SHIP*scale_size, GUI::ITEMSLOT::HEIGHT_FOR_SHIP*scale_size, zsize);
            Box box(size);
            button->SetBox(box);
                             
            Vec3<float> offset(0*GUI::ITEMSLOT::WIDTH_FOR_SHIP + i*GUI::ITEMSLOT::WIDTH_FOR_SHIP*scale_size, 
                               -2.0*GUI::ITEMSLOT::HEIGHT_FOR_SHIP,
                               0);
            AddChild(button, offset);
        }      
    }
        
    /** GATE SLOT */
    {
        ButtonItemSlot* button = new ButtonItemSlot(GUI::getGuiItemSlotType(ENTITY::TYPE::GATE_SLOT_ID), "ENTITY::GATE_SLOT_ID");
        
        Vec3<float> size(GUI::ITEMSLOT::WIDTH_FOR_SHIP/2, GUI::ITEMSLOT::HEIGHT_FOR_SHIP/2, zsize);
        Box box(size);
        button->SetBox(box);
                            
        Vec3<float> offset(-5*GUI::ITEMSLOT::WIDTH_FOR_SHIP, 
                           3*GUI::ITEMSLOT::HEIGHT_FOR_SHIP,
                           0);                            
        AddChild(button, offset);  		
	}
	
	allow_full_control = false;
	block_manual_exit  = false;
}

GuiVehicle::~GuiVehicle()
{}

void GuiVehicle::BindVehicle(Vehicle* vehicle, const Vec2<float>& gui_offset, bool allow_full_control, bool block_manual_exit, float scale)
{      
	m_Vehicle = vehicle; 
     
	SetOffset(gui_offset);
	this->allow_full_control = allow_full_control;
	this->block_manual_exit = block_manual_exit;
                
	m_TextureOb_korpus = nullptr;

	CreateKorpusGui(vehicle, scale);
	CreateItemSlotsGeometry(vehicle, scale);
}

void GuiVehicle::UnbindVehicle()
{ 
    for (auto child : m_Child_vec)
    {  
        child->Hide();
        ((ButtonItemSlot*)child)->SetItemSlot(nullptr);
    }
    
	m_Vehicle = nullptr;
}

void GuiVehicle::CreateKorpusGui(Vehicle* vehicle, float scale)
{
	m_TextureOb_korpus = vehicle->GetTextureOb();

    float kontur_w, kontur_h;
    if (m_TextureOb_korpus->GetFrameWidth() > m_TextureOb_korpus->GetFrameHeight())
    {
        kontur_w = 500; 
        kontur_h = m_TextureOb_korpus->GetFrameHeight() * kontur_w / (float)m_TextureOb_korpus->GetFrameWidth();
    }
    else
    {
        kontur_h = 500; 
        kontur_w = m_TextureOb_korpus->GetFrameWidth() * kontur_h / (float)m_TextureOb_korpus->GetFrameHeight();
    }               

    rect_korpus.Set(-kontur_w/2 * scale, -kontur_h/2 * scale, kontur_w * scale, kontur_h * scale); 
}      
  
void GuiVehicle::CreateItemSlotsGeometry(Vehicle* vehicle, float scale)
{
    for (const auto itemslot : vehicle->slot_total_vec)
    { 
        ENTITY::TYPE request_type = itemslot->GetSubTypeId();
        if ((request_type == ENTITY::TYPE::WEAPON_SLOT_ID) or (request_type == ENTITY::TYPE::CARGO_SLOT_ID) or (request_type == ENTITY::TYPE::ARTEFACT_SLOT_ID))
        {
            request_type = itemslot->GetSubSubTypeId(); 
        }         
    
        BaseGuiElement* child = GetGuiElement(GUI::getGuiItemSlotType(request_type));
        if (child)
        {
            child->Show();
            ((ButtonItemSlot*)child)->SetItemSlot(itemslot);
        }
    }
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

void GuiVehicle::RenderVehicle(const MouseData& data_mouse, ENTITY::TYPE mark_slot_subtype_id) const
{
	glPushMatrix();
    {
		glTranslatef(GetOffset().x, GetOffset().y, 0);
		drawTexturedRect(m_TextureOb_korpus, rect_korpus, -1.0);
		if (mark_slot_subtype_id != ENTITY::TYPE::NONE_ID)
		{
			RenderMarksForEmptySlots(data_mouse, GUI::getGuiItemSlotType(mark_slot_subtype_id));
		}
	}
    glPopMatrix();
}

void GuiVehicle::RenderMarksForEmptySlots(const MouseData& data_mouse, GUI::TYPE mark_slot_subtype_id) const
{ 
	for(auto &child : m_Child_vec)
	{
        //if (child->GetTypeId() == GUI::TYPE::BUTTON_ITEMSLOT_ID)
        ButtonItemSlot* button_itemslot = (ButtonItemSlot*)child;
		if (button_itemslot->GetEquiped() == false) 
		{
            GUI::TYPE buton_subtype_id = button_itemslot->GetSubTypeId();
            for (ENTITY::TYPE type : SLOT_WEAPON_TYPES)
            {
                if (buton_subtype_id == GUI::getGuiItemSlotType(type))
                {
                   buton_subtype_id = GUI::TYPE::WEAPON_SLOT_ID;
                   break;
                }
            }
            for (ENTITY::TYPE type : SLOT_CARGO_TYPES)
            {
                if (buton_subtype_id == GUI::getGuiItemSlotType(type))
                {
                   buton_subtype_id = GUI::TYPE::CARGO_SLOT_ID;
                   break;
                }
            }
            for (ENTITY::TYPE type : SLOT_ARTEFACT_TYPES)
            {
                if (buton_subtype_id == GUI::getGuiItemSlotType(type))
                {
                   buton_subtype_id = GUI::TYPE::ARTEFACT_SLOT_ID;
                   break;
                }
            }
                                
			if (buton_subtype_id != GUI::TYPE::GATE_SLOT_ID)
            {            
                if ((mark_slot_subtype_id == buton_subtype_id) or (buton_subtype_id == GUI::TYPE::CARGO_SLOT_ID))  
                {
                    button_itemslot->RenderMark(button_itemslot->GetBox(), GuiTextureObCollector::Instance().slot_mark_accept);
                }
                else
                {
                    if (button_itemslot->GetBox().CheckInteraction(data_mouse.pos_screencoord) == true)
                    {
                        button_itemslot->RenderMark(button_itemslot->GetBox(), GuiTextureObCollector::Instance().slot_mark_reject);
                    }
                }
            }
		}
	}
}

/*virtual override final*/
void GuiVehicle::RenderUnique(Player* player) const
{
    if (player->GetCursor().GetItemSlot()->GetItem() != nullptr)
    {
        enable_BLEND();
        {
            RenderMarksForEmptySlots(player->GetCursor().GetMouseData(), GUI::getGuiItemSlotType(player->GetCursor().GetItemSlot()->GetItem()->GetParentSubTypeId()));
        }
        disable_BLEND();
    }
    
    player->GetCursor().Render(player);
    //drawTexturedRect(m_TextureOb_korpus, rect_korpus, -1.0);

	//RenderSlots();
	//if (mark_slot_subtype_id != NONE_ID)
	//{
		//RenderMarksForEmptySlots(data_mouse, mark_slot_subtype_id);
	//}
}        
        





