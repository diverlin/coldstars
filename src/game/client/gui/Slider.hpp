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


#pragma once

#include "BaseGuiElement.hpp"
#include <jeti/TextureOb.hpp>
#include <ceti/rect.hpp>
#include <dock/Shop.hpp>
#include "MouseData.hpp"

class Slider : public BaseGuiElement
{
        public:
            Slider();                                      
               ~Slider();  
        
        void Configure(int, int);
        
        //void setSubTypeId(int subtype_id) { this->subtype_id = subtype_id; };
        //int subTypeId() const { return subtype_id; };

        void UpdateSlidePosition(const MouseData&);
        void ButtonsAction(Shop*);
                
        void CheckButtonsLock();
                        
               void Render() const;    
               
           private:
               int ammount_total;
               int ammount_selected;
               int price_selected;
               int price_for_one;
               
               ceti::Rect rect;
               ceti::Rect rect_slide;
               jeti::control::TextureOb* textureOb;
               jeti::control::TextureOb* textureOb_scale;
};

