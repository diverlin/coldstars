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

#include <jeti/TextureOb.hpp>

class GuiTextureObCollector
{
    public:
        jeti::TextureOb* starsystem_mark_war;
        jeti::TextureOb* starsystem_mark_captured;
        jeti::TextureOb* starsystem_mark_player;
    
        jeti::TextureOb* icon_minus;
        jeti::TextureOb* icon_plus;
        jeti::TextureOb* skill;
        jeti::TextureOb* skill_transparent;
    
        jeti::TextureOb* icon_map;
        jeti::TextureOb* grapple_trail;

        jeti::TextureOb* dot_blue;
        jeti::TextureOb* dot_red;
        jeti::TextureOb* dot_green;
        jeti::TextureOb* dot_black;
        jeti::TextureOb* dot_yellow;
        jeti::TextureOb* dot_purple;

        jeti::TextureOb* radar_screenrect;
        jeti::TextureOb* radar_background;
        jeti::TextureOb* radar_bar;
        jeti::TextureOb* radar_range;
        jeti::TextureOb* bar_bottom;
        jeti::TextureOb* bar_left;
        jeti::TextureOb* bar_top;
        jeti::TextureOb* bar_right;
    
        jeti::TextureOb* text_background;

        jeti::TextureOb* slot_mark_accept;
        jeti::TextureOb* slot_mark_reject;
        jeti::TextureOb* mask_round;
        jeti::TextureOb* mark_target;
        jeti::TextureOb* mark_target_slot;
                        
        static GuiTextureObCollector& Instance();
            
    private:
        GuiTextureObCollector() {};
        ~GuiTextureObCollector() {};
        
        GuiTextureObCollector(const GuiTextureObCollector&) = delete;
        GuiTextureObCollector& operator=(const GuiTextureObCollector&) = delete;
};

