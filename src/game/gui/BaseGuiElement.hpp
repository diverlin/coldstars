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
class AnimationEffect2D;

#include <common/GuiTypes.hpp>

#include <common/Box2D.hpp> 
#include <common/rect.hpp> // to be removed
#include <resources/TextureManager.hpp>
#include <common/constants.hpp>

          
class BaseGuiElement
{
	public:
		BaseGuiElement(GUI::TYPE subtype_id=GUI::TYPE::NONE_ID, const std::string& info="", TextureOb* textureOb=nullptr);
		virtual ~BaseGuiElement();
		
		void SetLabel(const std::string& label) { m_Label = label; }
		
		void SetTextureOb(TextureOb* textureOb) { m_TextureOb = textureOb; } 		
		void SetPlayer(Player* player) { m_Player = player; } // depr
		
        void SetSize(Vec2<float> size) { m_Box.SetSize(size); };
        	
		GUI::TYPE GetTypeId() const { return m_Type_id; }
		GUI::TYPE GetSubTypeId() const { return m_Subtype_id; }
					
		const Box2D& GetBox() const { return m_Box; }
		TextureOb* GetTextureOb() const { return m_TextureOb; }
				
        bool GetLock() const { return m_Lock; }
        bool GetPressed() const { return m_Pressed; }
        
        bool IsAnimationProgramActive() const { return (m_AnimationProgram != nullptr); }

        BaseGuiElement* GetGuiElement(GUI::TYPE) const;                     
			
		BaseGuiElement* UpdateMouseInteraction(const Vec2<float>&);
		
		void AddChild(BaseGuiElement*, const Vec2<float>&);

		void Show() { m_Show = true; }
		void Hide() { m_Show = false; }
								
		virtual void OnPressEventLMB(Player*) {}
		virtual void ResetState();

		void Update(Player*);
        void Render(Player*) const;		
		virtual void RenderInfo() const {};
				
	protected:
		GUI::TYPE m_Type_id;
		GUI::TYPE m_Subtype_id;
		
		bool m_Lock;
		bool m_Pressed;
		bool m_Show;
		bool m_Root;
		
		Box2D m_Box;
		Player* m_Player; // depr
				
		TextureOb* m_TextureOb;	
		std::string m_Info; 
		std::string m_Label; 
		
		std::vector<BaseGuiElement*> m_Child_vec;

		void SetScale(const Vec2<float>& scale) { m_Box.SetScale(scale); }		
        void SetRoot(bool root) { m_Root = root; }
                
		void SetAnimationProgram(AnimationEffect2D* animation_program) { m_AnimationProgram = animation_program; }

        bool GetAnimationProgramActive() const { return (m_AnimationProgram != nullptr); }
        void DeleteAnimationProgram();
        
		void PressEventOnGuiElement(GUI::TYPE);
		void ResetStateEventOnGuiElement(GUI::TYPE);			

		void UpdateGeometry(const Vec2<float>&, const Vec2<float>&);	
        
		virtual void UpdateUnique(Player*);		
		void UpdateCommon(Player*);
        				
		virtual void RenderUnique(Player*) const;		
		void RenderCommon(Player*) const;
       		       	
	private: 
        Vec2<float> m_Offset;      
        AnimationEffect2D* m_AnimationProgram;
        
		static std::map<GUI::TYPE, BaseGuiElement*> static_gui_element_map;

		void SetOffset(const Vec2<float>& offset) { m_Offset = offset; }	
		void SetOffset(float x, float y) { m_Offset.Set(x,y); }
                        
	friend class GuiManager;
};

#endif 
