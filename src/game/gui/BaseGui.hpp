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
#include "../common/Quad.hpp" // to be removed
#include "../common/rect.hpp" // to be removed

class BaseGui
{
    	public:
       		BaseGui();
       		~BaseGui();
       		
  		void SetGuiOffset(const Vec2<float>& gui_offset) { this->gui_offset = gui_offset; };
  		void SetQuad(const Quad& quad) { this->quad = quad; }
  		void SetPlayer(Player* player) { this->player = player; };
  		  		
  		const Vec2<float>& GetGuiOffset() const { return gui_offset; };
  		const Quad& GetQuad() const { return quad; }
       		BaseButton* GetButton(int) const;  
       		  		
  		bool UpdateMouseInteractionWithButtons(const MouseData&);
  		
       		void RenderButtons() const;
       		void RenderFocusedButtonInfo(const MouseData&) const;  
              	
       	protected:
       		Quad quad;
      		Player* player;
       		int button_w, button_h;
       		
       		std::map<int, BaseButton*> button_map;
       	
       	private:       				
		Vec2<float> gui_offset;
};


#endif 
