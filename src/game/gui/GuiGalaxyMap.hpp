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

#ifndef GUIGALAXYMAP_H
#define GUIGALAXYMAP_H

#include "BaseGui.hpp"
class Galaxy;
#include "../render/PathVisual.hpp"
#include "../common/rect.hpp"

class GuiGalaxyMap : public BaseGui
{
  	public:
     		GuiGalaxyMap();
     		~GuiGalaxyMap();
                
                void BindGalaxy(Galaxy* galaxy);
                void UnbindGalaxy();
                   
                Galaxy* GetGalaxy() const { return galaxy; };
                   
     		bool UpdateMouseInteraction(const MouseData&);
     		void Render();

     	private:
     		float scale_parsec2screencoord;
     		
                Galaxy* galaxy;
                
     		Rect rect;
     		
     		TextureOb* texOb_background;
     		
     		PathVisual visual_hyperjump_range;
		PathVisual visual_hyperjump_path;
};
     		
#endif 
