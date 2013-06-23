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


#ifndef BASEGUIELEMENT_HPP
#define BASEGUIELEMENT_HPP

#include <map>
#include <vector>

#include "MouseData.hpp"
class Player;
#include "../common/Box.hpp" // to be removed
#include "../common/rect.hpp" // to be removed
#include "../resources/TextureManager.hpp"

class BaseGuiElement
{
	public:
       		BaseGuiElement(int, const std::string&, TextureOb*);
       		~BaseGuiElement();
       		
			void SetSubTypeId(int subtype_id) { this->subtype_id = subtype_id; } 
			
			void SetInfo(const std::string& info) { this->info = info; }
			void SetLabel(const std::string& label) { this->label = label; }
			
			void SetCenter(const Vec2<float>& center) { this->center = center; }
			void SetBox(const Box& box) { this->box = box; }
			
			int GetTypeId() const { return type_id; }
			int GetSubTypeId() const { return subtype_id; }
						
			const Vec2<float>& GetCenter() const { return center; }
			const Box& GetBox() const { return box; }
			TextureOb* GetTextureOb() const { return textureOb; }
								
			bool UpdateMouseInteraction(const MouseData&);
			
			virtual void Update() {}
			virtual void PressEvent(Player*) {}
				
			void Render() const;
			void RenderInfo(const MouseData&) const;  
              	
	protected:
			int type_id;
			int subtype_id;
			
			Box box;
			
			TextureOb* textureOb;	
			std::string info; 
			std::string label; 
			
			std::vector<BaseGuiElement*> child_vec;
       		       	
	private:       				
			Vec2<float> center;
};


#endif 
