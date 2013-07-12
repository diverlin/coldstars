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
#include <common/Box.hpp> // to be removed
#include <common/rect.hpp> // to be removed
#include <resources/TextureManager.hpp>
#include <common/constants.hpp>

          
class BaseGuiElement
{
	public:
		BaseGuiElement(GUI::eTYPE subtype_id=GUI::eTYPE::NONE_ID, const std::string info="", TextureOb* textureOb=nullptr, BaseGuiElement* parent=nullptr);
		~BaseGuiElement();
		
		//void SetSubTypeId(int subtype_id) { this->subtype_id = subtype_id; } 
		
		//void SetInfo(const std::string& info) { this->info = info; }
		void SetLabel(const std::string& label) { m_Label = label; }

		void SetRoot(bool root) { m_Root = root; }
		
		void SetTextureOb(TextureOb* textureOb) { m_TextureOb = textureOb; } 		
		void SetPlayer(Player* player) { m_Player = player; } // depr

		void SetScale(const Vec3<float>& scale) { m_Scale = scale; }		
				
		void SetOffset(const Vec3<float>& offset) { m_Offset = offset; }	// depr				
		void SetOffset(const Vec2<float>& offset) { m_Offset.Set(offset.x, offset.y, 0); }	// depr	
		
		//void SetParent(BaseGuiElement* parent) { m_Parent = parent; }
		
		void SetBox(const Box& box) { m_Box = box; }
	
		GUI::eTYPE GetTypeId() const { return m_Type_id; }
		GUI::eTYPE GetSubTypeId() const { return m_Subtype_id; }
					
		const Vec3<float>& GetOffset() const { return m_Offset; } // depr
		const Box& GetBox() const { return m_Box; }
		TextureOb* GetTextureOb() const { return m_TextureOb; }
				
        bool GetLock() const { return m_Lock; }
        bool GetPressed() const { return m_Pressed; }
            
        BaseGuiElement* GetGuiElement(GUI::eTYPE) const;                     
			
		BaseGuiElement* UpdateMouseInteraction(const Vec2<float>&);
		
		void AddChild(BaseGuiElement*, const Vec3<float>&);

		void Show() { m_Show = true; }
		void Hide() { m_Show = false; }
								
		virtual void PressEvent(Player*) {}
		virtual void ResetState();

		void Update(Player*);
        void Render() const;		
		virtual void RenderInfo() const {};
				
	protected:
		GUI::eTYPE m_Type_id;
		GUI::eTYPE m_Subtype_id;
		
		bool m_Lock;
		bool m_Pressed;
		bool m_Show;
		bool m_Root;
		
		Box m_Box;
		Player* m_Player; // depr
				
		TextureOb* m_TextureOb;	
		std::string m_Info; 
		std::string m_Label; 
		
		//BaseGuiElement* m_Parent;
		std::vector<BaseGuiElement*> m_Child_vec;

		void PressEventOnGuiElement(GUI::eTYPE);
		void ResetStateEventOnGuiElement(GUI::eTYPE);			

		void UpdateGeometry(const Vec3<float>&, const Vec3<float>&);	
        
		virtual void UpdateUnique(Player*);		
		void UpdateCommon(Player*);
        				
		virtual void RenderUnique() const;		
		void RenderCommon() const;
       		       	
	private:       				
		Vec3<float> m_Offset;
		Vec3<float> m_Scale;
		
		static std::map<GUI::eTYPE, BaseGuiElement*> static_gui_element_map;
		
	friend class GuiManager;
};

#endif 
