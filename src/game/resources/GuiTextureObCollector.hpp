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


#ifndef GUITEXTURECOLLECTOR_HPP
#define GUITEXTURECOLLECTOR_HPP

#include "textureOb.hpp"


class GuiTextureObCollector
{
    public:
        TextureOb* starsystem_mark_war;
        TextureOb* starsystem_mark_captured;    
        TextureOb* starsystem_mark_player;
    
        TextureOb* icon_minus;
        TextureOb* icon_plus;
        TextureOb* skill;    
        TextureOb* skill_transparent;    
    
        TextureOb* icon_map;
        TextureOb* grapple_trail;    

        TextureOb* dot_blue;
        TextureOb* dot_red;
        TextureOb* dot_green;
        TextureOb* dot_black;
        TextureOb* dot_yellow;
        TextureOb* dot_purple;

        TextureOb* radar_screenrect;
        TextureOb* radar_background;                
        TextureOb* radar_bar;
        TextureOb* radar_range;
        TextureOb* bar_bottom;
        TextureOb* bar_left;
        TextureOb* bar_top;
        TextureOb* bar_right;        
    
        TextureOb* text_background;

        TextureOb* slot_mark_accept;
        TextureOb* slot_mark_reject;
        TextureOb* mask_round;
        TextureOb* mark_target;
        TextureOb* mark_target_slot;
                        
        static GuiTextureObCollector& Instance();
            
    private:
        GuiTextureObCollector() {};
        ~GuiTextureObCollector() {};
        
        GuiTextureObCollector(const GuiTextureObCollector&) = delete;
        GuiTextureObCollector& operator=(const GuiTextureObCollector&) = delete;
};

#endif
