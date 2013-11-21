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


#ifndef GUIGALAXYMAP_HPP
#define GUIGALAXYMAP_HPP

#include <gui/BaseGuiElement.hpp>
#include <gui/MouseData.hpp>
#include <render/PathVisual.hpp>

class Galaxy;
class StarSystem;
class Renderer;


class GuiGalaxyMap : public BaseGuiElement
{
    public:
        GuiGalaxyMap();
        ~GuiGalaxyMap();
        
        void BindGalaxy(Galaxy*);
        void UnbindGalaxy();
           
        Galaxy* GetGalaxy() const { return m_Galaxy; }

    private:
        float m_ScaleParsecToScreenCoord;
        
        Galaxy* m_Galaxy;
        
        PathVisual m_VisualHyperJumpRange;
        PathVisual m_VisualHyperJumpPath;
        
        virtual void UpdateUnique(Player*) override final;
        virtual void RenderUnique(const Renderer&, Player*) const override final;
        
        glm::vec3 GetAbsoluteStarSystemPosition(const StarSystem&) const;
};
             
#endif 
