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

class Player;
#include "../common/Box.hpp" // to be removed
#include "../common/rect.hpp" // to be removed
#include "../resources/TextureManager.hpp"

class BaseGuiElement
{
	public:
		BaseGuiElement(int subtype_id=0, const std::string info="", TextureOb* textureOb=nullptr, BaseGuiElement* parent=nullptr);
		~BaseGuiElement();
		
		//void SetSubTypeId(int subtype_id) { this->subtype_id = subtype_id; } 
		
		//void SetInfo(const std::string& info) { this->info = info; }
		void SetLabel(const std::string& label) { this->label = label; }

		void SetRoot(bool root) { this->root = root; }
		
		void SetTextureOb(TextureOb* textureOb) { this->textureOb = textureOb; } 		
		void SetPlayer(Player* player) { this->player = player; } // depr

		void SetScale(const Vec3<float>& scale) { this->scale = scale; }		
				
		void SetOffset(const Vec3<float>& offset) { this->offset = offset; }	// depr				
		void SetOffset(const Vec2<float>& offset) { this->offset.Set(offset.x, offset.y, 0); }	// depr	
		
		void SetParent(BaseGuiElement* parent) { this->parent = parent; }
		
		void SetBox(const Box& box) { this->box = box; }
	
		int GetTypeId() const { return type_id; }
		int GetSubTypeId() const { return subtype_id; }
					
		const Vec3<float>& GetOffset() const { return offset; } // depr
		const Box& GetBox() const { return box; }
		TextureOb* GetTextureOb() const { return textureOb; }
				
		void UpdateGeometry(const Vec3<float>&, const Vec3<float>&);					
		BaseGuiElement* UpdateMouseInteraction(const Vec2<float>&);
		
		void AddChild(BaseGuiElement* child, const Vec3<float>& offset);

		void Show() { show = true; }
		void Hide() { show = false; }
								
		virtual void Update() {}
		virtual void PressEvent(Player*) {}
		virtual void ResetState();

		void Render() const;		
		virtual void RenderInfo() const {};
				
	protected:
		int type_id;
		int subtype_id;
		
		bool lock;
		bool pressed;
		bool show;
		bool root;
		
		Box box;
		Player* player; // depr
				
		TextureOb* textureOb;	
		std::string info; 
		std::string label; 
		
		BaseGuiElement* parent;
		std::vector<BaseGuiElement*> child_vec;

		void PressEventOnGuiElement(int);
		void ResetStateEventOnGuiElement(int);			
		BaseGuiElement* GetGuiElement(int request_subtype_id) const;
				
		virtual void RenderUnique() const;		
		void RenderCommon() const;
       		       	
	private:       				
		Vec3<float> offset;
		Vec3<float> scale;
		
		static std::map<int, BaseGuiElement*> static_gui_element_map;
		
	friend class GuiManager;
};

#endif 
