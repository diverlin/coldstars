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


#ifndef SLIDER_H
#define SLIDER_H

#include "BaseGuiElement.hpp"
#include "../resources/textureOb.hpp"
#include "../common/rect.hpp"
#include "../dock/Shop.hpp"
#include "MouseData.hpp"

class Slider : public BaseGuiElement
{
    	public:
    		Slider();		               		       
       		~Slider();  
		
		void Configure(int, int);
		
		//void SetSubTypeId(int subtype_id) { this->subtype_id = subtype_id; };
		//int GetSubTypeId() const { return subtype_id; };

		void UpdateSlidePosition(const MouseData&);
		void ButtonsAction(Shop*);
				
		void CheckButtonsLock();
						
       		void Render() const;    
       		
       	private:
       		int ammount_total;
       		int ammount_selected;
       		int price_selected;
       		int price_for_one;
       		
       		Rect rect;  
       		Rect rect_slide;     		
       		TextureOb* textureOb;
       		TextureOb* textureOb_scale;
};

#endif
