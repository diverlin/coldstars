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
#include <dock/Kosmoport.hpp>
#include <jeti/Render.hpp>
#include <items/BaseItem.hpp>
#include <slots/ItemSlot.hpp>
//#include <ceti/StringUtils.hpp>
#include <common/common.hpp>
#include <builder/slots/ItemSlotBuilder.hpp>

#include <pilots/Npc.hpp>
#include <spaceobjects/Vehicle.hpp>
#include "ButtonItemSlot.hpp"

         
GuiVehicle::GuiVehicle()
:
BaseGuiElement(TYPE::GUI::SCAN_VEHICLE_ID, TYPE::GUI::SCAN_VEHICLE_ID),
m_Vehicle(nullptr)
{   
    int weapon_slot_max   = SLOT_WEAPON_TYPES.size();
    int otsec_slot_max    = SLOT_CARGO_TYPES.size();
    int artefact_slot_max = SLOT_ARTEFACT_TYPES.size();
    
    float dist_rate = 1.1;
    /** WEAPON SLOTS */
    for (int i=0; i<weapon_slot_max; i++)
    {
        ButtonItemSlot* button = new ButtonItemSlot(getGuiItemSlotType(SLOT_WEAPON_TYPES[i]), "ENTITY::WEAPON_SLOT_ID");
        
        glm::vec2 size(GUI::ITEMSLOT::WIDTH_FOR_SHIP, GUI::ITEMSLOT::HEIGHT_FOR_SHIP);
        button->setSize(size);

        glm::vec2 offset((-2+i)*dist_rate*GUI::ITEMSLOT::WIDTH_FOR_SHIP, (2)*dist_rate*GUI::ITEMSLOT::HEIGHT_FOR_SHIP);                       
        AddChild(button, offset);
    } 
    
    /** EQUIPMENT SLOTS */
    {
        ButtonItemSlot* button = new ButtonItemSlot(getGuiItemSlotType(TYPE::ENTITY::RADAR_SLOT_ID), "ENTITY::RADAR_SLOT_ID");
        
        glm::vec2 size(GUI::ITEMSLOT::WIDTH_FOR_SHIP, GUI::ITEMSLOT::HEIGHT_FOR_SHIP);
        button->setSize(size);
        
        glm::vec2 offset((3)*dist_rate*GUI::ITEMSLOT::WIDTH_FOR_SHIP, (-0.5)*dist_rate*GUI::ITEMSLOT::HEIGHT_FOR_SHIP);
        AddChild(button, offset);
    }

    {
        ButtonItemSlot* button = new ButtonItemSlot(getGuiItemSlotType(TYPE::ENTITY::SCANER_SLOT_ID), "ENTITY::SCANER_SLOT_ID");

        glm::vec2 size(GUI::ITEMSLOT::WIDTH_FOR_SHIP, GUI::ITEMSLOT::HEIGHT_FOR_SHIP);
        button->setSize(size);
                    
        glm::vec2 offset((3)*dist_rate*GUI::ITEMSLOT::WIDTH_FOR_SHIP, (0.5)*dist_rate*GUI::ITEMSLOT::HEIGHT_FOR_SHIP);
        AddChild(button, offset);
    }

    {
        ButtonItemSlot* button = new ButtonItemSlot(getGuiItemSlotType(TYPE::ENTITY::ENERGIZER_SLOT_ID), "ENTITY::ENERGIZER_SLOT_ID");

        glm::vec2 size(GUI::ITEMSLOT::WIDTH_FOR_SHIP, GUI::ITEMSLOT::HEIGHT_FOR_SHIP);
        button->setSize(size);
                
        glm::vec2 offset((0)*dist_rate*GUI::ITEMSLOT::WIDTH_FOR_SHIP, (0)*dist_rate*GUI::ITEMSLOT::HEIGHT_FOR_SHIP); 
        AddChild(button, offset);
    }

    {
        ButtonItemSlot* button = new ButtonItemSlot(getGuiItemSlotType(TYPE::ENTITY::GRAPPLE_SLOT_ID), "ENTITY::GRAPPLE_SLOT_ID");

        glm::vec2 size(GUI::ITEMSLOT::WIDTH_FOR_SHIP, GUI::ITEMSLOT::HEIGHT_FOR_SHIP);
        button->setSize(size);
        
        glm::vec2 offset((-0.75)*dist_rate*GUI::ITEMSLOT::WIDTH_FOR_SHIP, (0.75)*dist_rate*GUI::ITEMSLOT::HEIGHT_FOR_SHIP);
        AddChild(button, offset);
    }

    {
        ButtonItemSlot* button = new ButtonItemSlot(getGuiItemSlotType(TYPE::ENTITY::DROID_SLOT_ID), "ENTITY::DROID_SLOT_ID");

        glm::vec2 size(GUI::ITEMSLOT::WIDTH_FOR_SHIP, GUI::ITEMSLOT::HEIGHT_FOR_SHIP);
        button->setSize(size);
                            
        glm::vec2 offset((0.75)*dist_rate*GUI::ITEMSLOT::WIDTH_FOR_SHIP,(0.75)*dist_rate*GUI::ITEMSLOT::HEIGHT_FOR_SHIP);
        AddChild(button, offset);
    }

    //{
        //ButtonItemSlot* button = new ButtonItemSlot(GUI::getEquivalent(TYPE::ENTITY::FREEZER_SLOT_ID), "ENTITY::FREEZER_SLOT_ID");

        //glm::vec2 size(GUI::ITEMSLOT::WIDTH_FOR_SHIP, GUI::ITEMSLOT::HEIGHT_FOR_SHIP);
        //button->setSize(size);
                
        //glm::vec2 offset((-0.75)*dist_rate*GUI::ITEMSLOT::WIDTH_FOR_SHIP,(-0.75)*dist_rate*GUI::ITEMSLOT::HEIGHT_FOR_SHIP);
        //AddChild(button, offset);
    //}
                
    {
        ButtonItemSlot* button = new ButtonItemSlot(getGuiItemSlotType(TYPE::ENTITY::PROTECTOR_SLOT_ID), "ENTITY::PROTECTOR_SLOT_ID");

        glm::vec2 size(GUI::ITEMSLOT::WIDTH_FOR_SHIP, GUI::ITEMSLOT::HEIGHT_FOR_SHIP);
        button->setSize(size);
                
        glm::vec2 offset((0.75)*dist_rate*GUI::ITEMSLOT::WIDTH_FOR_SHIP,(-0.75)*dist_rate*GUI::ITEMSLOT::HEIGHT_FOR_SHIP);
        AddChild(button, offset);
    }

    {
        ButtonItemSlot* button = new ButtonItemSlot(getGuiItemSlotType(TYPE::ENTITY::DRIVE_SLOT_ID), "ENTITY::DRIVE_SLOT_ID");

        glm::vec2 size(GUI::ITEMSLOT::WIDTH_FOR_SHIP, GUI::ITEMSLOT::HEIGHT_FOR_SHIP);
        button->setSize(size);
                            
        glm::vec2 offset((-2.5)*dist_rate*GUI::ITEMSLOT::WIDTH_FOR_SHIP, (0.5)*dist_rate*GUI::ITEMSLOT::HEIGHT_FOR_SHIP);
        AddChild(button, offset);
    }

    {
        ButtonItemSlot* button = new ButtonItemSlot(getGuiItemSlotType(TYPE::ENTITY::BAK_SLOT_ID), "ENTITY::BAK_SLOT_ID");

        glm::vec2 size(GUI::ITEMSLOT::WIDTH_FOR_SHIP, GUI::ITEMSLOT::HEIGHT_FOR_SHIP);
        button->setSize(size);
                    
        glm::vec2 offset((-2.5)*dist_rate*GUI::ITEMSLOT::WIDTH_FOR_SHIP, (-0.5)*dist_rate*GUI::ITEMSLOT::HEIGHT_FOR_SHIP);
        AddChild(button, offset);
    }

    /** ARTEFACT SLOTS */
    {
        float scale_size = 1/2.0;
        for (int i=0; i<artefact_slot_max; i++)
        {
            ButtonItemSlot* button = new ButtonItemSlot(getGuiItemSlotType(SLOT_ARTEFACT_TYPES[i]), "ENTITY::ARTEFACT_SLOT_ID");

            glm::vec2 size(GUI::ITEMSLOT::WIDTH_FOR_SHIP*scale_size, GUI::ITEMSLOT::HEIGHT_FOR_SHIP*scale_size);
            button->setSize(size);
                             
            glm::vec2 offset((i+1)*GUI::ITEMSLOT::WIDTH_FOR_SHIP*scale_size, (-2.5)*dist_rate*GUI::ITEMSLOT::HEIGHT_FOR_SHIP);
            AddChild(button, offset);
        }      
    }
        
    /** CARGO SLOTS */            
    for (int i=0; i<otsec_slot_max; i++)
    {
        float scale_size =1/1.5;
        ButtonItemSlot* button = new ButtonItemSlot(getGuiItemSlotType(SLOT_CARGO_TYPES[i]), "ENTITY::CARGO_SLOT_ID");
        
        glm::vec2 size(GUI::ITEMSLOT::WIDTH_FOR_SHIP*scale_size, GUI::ITEMSLOT::HEIGHT_FOR_SHIP*scale_size);
        button->setSize(size);

        glm::vec2 offset((-5+i)*GUI::ITEMSLOT::WIDTH_FOR_SHIP*scale_size, -1.75*dist_rate*GUI::ITEMSLOT::HEIGHT_FOR_SHIP);        
        AddChild(button, offset);
    }
        
    /** GATE SLOT */
    {
        ButtonItemSlot* button = new ButtonItemSlot(getGuiItemSlotType(TYPE::ENTITY::GATE_SLOT_ID), "ENTITY::GATE_SLOT_ID");
        
        glm::vec2 size(GUI::ITEMSLOT::WIDTH_FOR_SHIP, GUI::ITEMSLOT::HEIGHT_FOR_SHIP);
        button->setSize(size);
                            
        glm::vec2 offset((-3.2)*GUI::ITEMSLOT::WIDTH_FOR_SHIP, (3.2)*GUI::ITEMSLOT::HEIGHT_FOR_SHIP);
        AddChild(button, offset);          
    }
    
    allow_full_control = false;
    block_manual_exit  = false;
}

GuiVehicle::~GuiVehicle()
{}

void GuiVehicle::BindVehicle(Vehicle* vehicle, const glm::vec2& gui_offset, bool allow_full_control, bool block_manual_exit, float scale)
{      
    m_Vehicle = vehicle; 
     
    this->allow_full_control = allow_full_control;
    this->block_manual_exit = block_manual_exit;

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
    SetTextureOb(GuiTextureObCollector::Instance().radar_range);

    float kontur_w = 400;
    float kontur_h = 400;           

    GetBox().setSize(kontur_w * scale, kontur_h * scale); 
}      
  
void GuiVehicle::CreateItemSlotsGeometry(Vehicle* vehicle, float scale)
{
    for (const auto itemslot : vehicle->m_SlotTotal_vec)
    { 
        TYPE::ENTITY request_type = itemslot->subTypeId();
        if ((request_type == TYPE::ENTITY::WEAPON_SLOT_ID) or (request_type == TYPE::ENTITY::CARGO_SLOT_ID) or (request_type == TYPE::ENTITY::ARTEFACT_SLOT_ID))
        {
            request_type = itemslot->subSubTypeId(); 
        }         
    
        BaseGuiElement* child = GetGuiElement(getGuiItemSlotType(request_type));
        if (child)
        {
            child->Show();
            ((ButtonItemSlot*)child)->SetItemSlot(itemslot);
        }
    }
} 

/*
bool GuiVehicle::UpdateMouseInteraction(const MouseData& data_mouse)
{    
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
                if (gui_itemslot_vec[i].GetItemSlot()->subTypeId() != ENTITY::GATE_SLOT_ID)
                {
                    m_Player->GetCursor().GetItemSlot()->SwapItem(gui_itemslot_vec[i].GetItemSlot()); 
                }
                else
                {
                    if (m_Player->GetCursor().GetItemSlot()->GetItem() != nullptr)
                    {
                        if (m_Player->GetNpc()->GetVehicle()->placeTypeId() == ENTITY::SPACE_ID)
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
}
*/   
     
/* virtual override final */
void GuiVehicle::RenderUnique(const jeti::Renderer& render, Player* player) const
{
    //enable_BLEND(); 
    //{
        //drawQuad(GetTextureOb(), GetBox());
    //}
    //disable_BLEND();
}        
        





