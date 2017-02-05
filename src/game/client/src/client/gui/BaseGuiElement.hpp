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

#include <map>
#include <vector>

#include <types/GuiTypes.hpp>
#include <ceti/Box2D.hpp>

class Player;

namespace jeti {
class AnimationEffect2D;

namespace control {
class Material;
} // namespace control

class Renderer;
}
          
class BaseGuiElement
{
    public:
        BaseGuiElement(gui::type type_id=gui::type::NONE_ID, gui::type subtype_id=gui::type::NONE_ID, const std::string& info="", jeti::control::Material* textureOb=nullptr);
        virtual ~BaseGuiElement();
        
        void SetLabel(const std::string& label) { m_Label = label; }
        
        void SetTextureOb(jeti::control::Material* textureOb) { m_TextureOb = textureOb; }
        
        void setSize(glm::vec2 size) { m_Box.setSize(size); }
            
        gui::type typeId() const { return m_Type_id; }
        gui::type subTypeId() const { return m_Subtype_id; }
                    
        const ceti::Box2D& GetBox() const { return m_Box; }
        ceti::Box2D& GetBox() { return m_Box; } // !!!
                
        const jeti::control::Material& textureOb() const { return *m_TextureOb; }
                
        bool GetLock() const { return m_Locked; }
        bool GetPressed() const { return m_Pressed; }
        
        bool IsAnimationProgramActive() const { return (m_AnimationProgram != nullptr); }

        BaseGuiElement* GetGuiElement(gui::type) const;
            
        BaseGuiElement* UpdateMouseInteraction(const glm::vec2&);
        
        void AddChild(BaseGuiElement*, const glm::vec2&);

        void Show() { m_Show = true; }
        void Hide() { m_Show = false; }
                                
        virtual void OnPressEventMBL(Player*) {}
        virtual void OnPressEventMBR(Player*) {}
        virtual void ResetState();

        void Update(Player*);
        void Render(const jeti::Renderer&, Player*) const;
        virtual void RenderInfo(const jeti::Renderer&) const {};
                
    protected:
        std::vector<BaseGuiElement*> m_Child_vec;

        void setSubTypeId(gui::type subtype_id) { m_Subtype_id = subtype_id; }
        
        void SetBox(const ceti::Box2D& box) { m_Box = box; }
        
        void SetScale(const glm::vec2& scale) { m_Box.SetScale(scale); }        
        void SetRoot(bool root) { m_Root = root; }
        void SetPressed(bool pressed) { m_Pressed = pressed; } 
        void SetLocked(bool locked) { m_Locked = locked; } 
                 
        void SetAnimationProgram(jeti::AnimationEffect2D* animation_program) { m_AnimationProgram = animation_program; }

        bool HasTextureOb() const { return (m_TextureOb != nullptr); }

        const std::string& GetInfo() const { return m_Info; }
        const std::string& GetLabel() const { return m_Label; }
                
        bool GetLocked() const { return m_Locked; }
                
        bool GetAnimationProgramActive() const { return (m_AnimationProgram != nullptr); }
        void DeleteAnimationProgram();
        
        void PressEventMBL_onGuiElement(gui::type, Player*);
        void ResetStateEventOnGuiElement(gui::type);

        void UpdateGeometry(const glm::vec2&, const glm::vec2&);    
        
        virtual void UpdateUnique(Player*);        
        void UpdateCommon(Player*);
                        
        virtual void RenderUnique(const jeti::Renderer&, Player*) const;
        void RenderCommon(const jeti::Renderer&, Player*) const;
                          
    private: 
        gui::type m_Type_id;
        gui::type m_Subtype_id;
        
        jeti::control::Material* m_TextureOb;
        
        std::string m_Info; 
        std::string m_Label; 
        
        ceti::Box2D m_Box;
            
        bool m_Locked;
        bool m_Pressed;
        bool m_Show;
        bool m_Root;
        
        glm::vec2 m_Offset;      
        jeti::AnimationEffect2D* m_AnimationProgram;
        
        static std::map<gui::type, BaseGuiElement*> static_gui_element_map;

        void SetOffset(const glm::vec2& offset) { m_Offset = offset; }    
        void SetOffset(float x, float y) { m_Offset.x = x; m_Offset.y = y; }
                        
    friend class GuiManager;
};


