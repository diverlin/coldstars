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

#ifndef GUIRADAR_HPP
#define GUIRADAR_HPP

#include "BaseGuiElement.hpp"
#include <common/rect.hpp> // to be removed

class BaseSpaceEntity;
class Vehicle;

class GuiRadar : public BaseGuiElement
{
    public:
        GuiRadar();
        virtual ~GuiRadar() override final;
    
        const Rect& GetRect() const { return rect; };
        void Resize(int, int);
        
        void ResetData();
        
        void Add(BaseSpaceEntity*);
        void AddIfWithinRadarRange(BaseSpaceEntity*, const Vehicle&);

        virtual void UpdateUnique(Player*) override final;
                     
        virtual void RenderUnique(Player*) const override final;
            
    private:
        float scale;
        
        TextureOb* textureOb_background;
        TextureOb* textureOb_bar;     
        TextureOb* textureOb_screenrect; 
        TextureOb* textureOb_range;
                
        Rect rect;
        Rect screenrect;
                                    
        std::vector<BaseSpaceEntity*> entity_vec;
};

#endif
