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


#ifndef BASEGUI_H
#define BASEGUI_H

#include <map>

#include "BaseButton.hpp"
#include "MouseData.hpp"
class Player;


class BaseGui
{
    	public:
       		BaseGui();
       		~BaseGui();

       		BaseButton* GetButton(int) const;  
       		
  		void SetGuiOffset(const vec2f& gui_offset) { this->gui_offset = gui_offset; };
  		const vec2f& GetGuiOffset() const { return gui_offset; };
  		
  		void SetPlayer(Player* player) { this->player = player; };
  		
  		bool UpdateMouseInteractionWithButtons(const MouseData&);
  		
       		void RenderButtons() const;
       		void RenderFocusedButtonInfo(const MouseData&) const;  
              	
       	protected:
      		Player* player;
       		int button_w, button_h;
       		
       		std::map<int, BaseButton*> button_map;
       	
       	private:       				
		vec2f gui_offset;
};


#endif 
