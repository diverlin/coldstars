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


#ifndef BASEBUTTON_HPP
#define BASEBUTTON_HPP

#include "BaseGuiElement.hpp"

class Renderer;

class BaseButton : public BaseGuiElement
{
    public:
        BaseButton(TYPE::GUI, TYPE::GUI, const std::string&,void (*pAction)(Player*) = nullptr, TextureOb* textureOb = nullptr);                      
        virtual ~BaseButton();  
        
        void SetTextureObAdditional(TextureOb* textureOb_additional) { m_TextureOb_additional = textureOb_additional; }
        void SetTextureObMask(TextureOb* textureOb_mask) { m_TextureOb_mask = textureOb_mask; }
        
        //void SetCallBack(void (*funcp)()) { this->pAction = pAction; }              
        void LockOn();
        void LockOff();
        
        virtual void ResetState() override;
        
        virtual void RenderInfo(const Renderer&) const override;                
        virtual void RenderUnique(const Renderer&, Player*) const override;   
                       
    protected:          
        float m_Alpha;                        
        
        TextureOb* m_TextureOb_additional;
        TextureOb* m_TextureOb_mask;
        
        void (*m_pAction)(Player*);
        
        void FullShadeOn();
        void ShadeOn();
        void ShadeOff();
};

#endif
