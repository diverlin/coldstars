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
//#include <ceti/StringUtils.hpp>
#include <common/common.hpp>
#include <client/resources/GuiTextureObCollector.hpp>
#include <spaceobjects/Vehicle.hpp>
#include <slots/ItemSlot.hpp>
#include <client/pilots/Player.hpp>
#include <pilots/Npc.hpp>


GuiVehicle2::GuiVehicle2()
:
BaseGuiElement(type::GUI::PLAYER_VEHICLE_ID, type::GUI::PLAYER_VEHICLE_ID),
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
    for (unsigned int i=0; i<vehicle->m_slots.size(); i++)
    {    
        type::entity slot_subtype_id = vehicle->m_slots[i]->subtype();
        if ( (slot_subtype_id != type::entity::CARGO_SLOT_ID) && (slot_subtype_id != type::entity::ARTEFACT_SLOT_ID) )
        {  
            type::entity entity_type_id = slot_subtype_id;
            if (slot_subtype_id == type::entity::WEAPON_SLOT_ID)
            {
                entity_type_id = vehicle->m_slots[i]->subsubtype();
            }
                          
            //TextureOb* textureOb = GuiTextureObCollector::Instance().dot_purple;
            ButtonItemSlot2* button = new ButtonItemSlot2(getGuiItemSlotSelectorType(entity_type_id), str(entity_type_id), vehicle->m_slots[i]);

            glm::vec2 size(GUI::ITEMSLOT::WIDTH_FOR_SHIP, GUI::ITEMSLOT::HEIGHT_FOR_SHIP);
            button->setSize(size*scale);

            glm::vec2 offset = meti::genVec2f(160, angle);
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
        if (m_Vehicle != player->GetNpc()->vehicle())
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
        BindVehicle(player->GetNpc()->vehicle(), 0.6);
    }
}