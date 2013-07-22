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

#ifndef GUIVEHICLE_H
#define GUIVEHICLE_H

#include "BaseGuiElement.hpp"
#include <docking/Store.hpp>
#include <common/constants.hpp>
class Vehicle;
#include "MouseData.hpp" // to be removed

class GuiVehicle : public BaseGuiElement
{
    public:
        GuiVehicle(GUI::TYPE);
        virtual ~GuiVehicle();
        
        Vehicle* GetVehicle() const { return m_Vehicle; };
        bool GetBlockManualExit() const { return block_manual_exit; };
        bool GetAllowFullControl() const { return allow_full_control; };
                        
        void BindVehicle(Vehicle*, const Vec2<float>& offset, bool full_control_on, bool block_manual_closing = false, float scale = 1.0f);
        void UnbindVehicle();
        
        //bool UpdateMouseInteraction(const MouseData&);   
        //bool UpdateMouseInteractionInStore(const MouseData&, Store*); 
        
        //void RenderVehicle(const MouseData&, ENTITY::TYPE mark_slot_subtype_id = ENTITY::TYPE::NONE_ID) const;
    
    private:     
        bool block_manual_exit;
        bool allow_full_control;
        
        Rect rect_korpus; 
        TextureOb* m_TextureOb_korpus;
            
        Vehicle* m_Vehicle;

        virtual void RenderUnique(Player*) const override final;            
                    
        void RenderMarksForEmptySlots(const MouseData&, GUI::TYPE) const;  
        
        void CreateKorpusGui(Vehicle*, float);
        void CreateItemSlotsGeometry(Vehicle*, float);
        void CreateFunctionalItemSlotsCircleGeometry(Vehicle*, float);
};



#endif
