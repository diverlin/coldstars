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

#include "GuiVehicle2.hpp"
#include "ButtonItemSlot2.hpp"
#include <ceti/myStr.hpp>
#include "../common/common.hpp"
#include "../resources/GuiTextureObCollector.hpp"
#include "../spaceobjects/Vehicle.hpp"
#include "../slots/ItemSlot.hpp"
#include "../pilots/Player.hpp"
#include "../pilots/Npc.hpp"


GuiVehicle2::GuiVehicle2()
:
BaseGuiElement(TYPE::GUI::PLAYER_VEHICLE_ID, TYPE::GUI::PLAYER_VEHICLE_ID), 
m_Vehicle(nullptr) 
{

}        

void GuiVehicle2::Reset()
{
    for (unsigned int i=0; i<m_Child_vec.size(); i++)
    {
        delete m_Child_vec[i];
    }
    m_Child_vec.clear();
    
    m_Vehicle = nullptr;
}

void GuiVehicle2::BindVehicle(Vehicle* vehicle, float scale)
{
    CreateFunctionalItemSlotsWithCircleGeometry(vehicle, scale);
    
    m_Vehicle = vehicle;
}    
    
void GuiVehicle2::CreateFunctionalItemSlotsWithCircleGeometry(Vehicle* vehicle, float scale)
{   
    Reset();     
    int angle = 0;
    for (unsigned int i=0; i<vehicle->m_SlotTotal_vec.size(); i++)
    {    
        TYPE::ENTITY slot_subtype_id = vehicle->m_SlotTotal_vec[i]->GetSubTypeId();
        if ( (slot_subtype_id != TYPE::ENTITY::CARGO_SLOT_ID) and (slot_subtype_id != TYPE::ENTITY::ARTEFACT_SLOT_ID) )
        {  
            TYPE::ENTITY entity_type_id = slot_subtype_id;
            if (slot_subtype_id == TYPE::ENTITY::WEAPON_SLOT_ID)
            {
                entity_type_id = vehicle->m_SlotTotal_vec[i]->GetSubSubTypeId();
            }
                          
            //TextureOb* textureOb = GuiTextureObCollector::Instance().dot_purple;
            ButtonItemSlot2* button = new ButtonItemSlot2(getGuiItemSlotSelectorType(entity_type_id), getStr(entity_type_id), vehicle->m_SlotTotal_vec[i]);

            glm::vec2 size(GUI::ITEMSLOT::WIDTH_FOR_SHIP, GUI::ITEMSLOT::HEIGHT_FOR_SHIP);
            button->SetSize(size*scale);

            glm::vec2 offset = meti::getVec2f(160, angle);
            AddChild(button, offset*scale);

            angle += 20; 
        }
    }        
}    

/* virtual override final */
void GuiVehicle2::UpdateUnique(Player* player)
{
    bool need_update = false;
    if (m_Vehicle != nullptr)        
    {
        if (m_Vehicle != player->GetNpc()->GetVehicle())
        {
            need_update = true;
        }
    }
    else
    {
        need_update = true;
    }
    
    if (need_update)
    {
        BindVehicle(player->GetNpc()->GetVehicle(), 0.6);            
    }
}
