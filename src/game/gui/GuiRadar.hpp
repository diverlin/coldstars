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

#include "BaseGuiElement.hpp"
#include <ceti/rect.hpp> // to be removed

class BaseSpaceEntity;
class Vehicle;

namespace jeti {
class Renderer;
}

class GuiRadar : public BaseGuiElement
{
    public:
        GuiRadar();
        virtual ~GuiRadar() override final;
    
        const ceti::Rect& GetRect() const { return rect; };
        void Resize(int, int);
        
        void ResetData();
        
        void Add(BaseSpaceEntity*);
        void AddIfWithinRadarRange(BaseSpaceEntity*, const Vehicle&);

        virtual void UpdateUnique(Player*) override final;
                     
        virtual void RenderUnique(const jeti::Renderer&, Player*) const override final;
            
    private:
        float scale;
        
        jeti::TextureOb* textureOb_background;
        jeti::TextureOb* textureOb_bar;
        jeti::TextureOb* textureOb_screenrect;
        jeti::TextureOb* textureOb_range;
                
        ceti::Rect rect;
        ceti::Rect screenrect;
                                    
        std::vector<BaseSpaceEntity*> entity_vec;
};

