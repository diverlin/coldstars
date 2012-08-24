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


#ifndef GUIRADAR_H
#define GUIRADAR_H

#include "../gui/BaseGui.hpp"
#include "../spaceobjects/BaseGameEntity.hpp"
#include "../spaceobjects/Vehicle.hpp"

class GuiRadar : public BaseGui
{
   	public:
      		GuiRadar();
      		~GuiRadar();
      		
      		void Resize(int, int);
     	
     		void Reset();
     		void ButtonsAction(Player* player) const;
     		
     		void Update();
     		bool UpdateMouseInteraction(const MouseData&);
     		void UpdateEquipmentIcons(Player* player) const;
     		
     		void Add(BaseGameEntity*);
     		void AddIfWithinRadarRange(BaseGameEntity*, const Vehicle&);
     		
		void Render() const;
		     			
      	private:
      		float scale;

      		TextureOb* textureOb_background;
      		TextureOb* textureOb_bar; 	
      		TextureOb* textureOb_screenrect; 
      		TextureOb* textureOb_range;
      		      		
      	       	Rect rect;
      	       	Rect screenrect;
      	       	      	       	      		
      		std::vector<BaseGameEntity*> entity_vec;
};

#endif
