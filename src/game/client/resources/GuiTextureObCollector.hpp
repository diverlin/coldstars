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
        jeti::control::TextureOb* starsystem_mark_war;
        jeti::control::TextureOb* starsystem_mark_captured;
        jeti::control::TextureOb* starsystem_mark_player;
    
        jeti::control::TextureOb* icon_minus;
        jeti::control::TextureOb* icon_plus;
        jeti::control::TextureOb* skill;
        jeti::control::TextureOb* skill_transparent;
    
        jeti::control::TextureOb* icon_map;
        jeti::control::TextureOb* grapple_trail;

        jeti::control::TextureOb* dot_blue;
        jeti::control::TextureOb* dot_red;
        jeti::control::TextureOb* dot_green;
        jeti::control::TextureOb* dot_black;
        jeti::control::TextureOb* dot_yellow;
        jeti::control::TextureOb* dot_purple;

        jeti::control::TextureOb* radar_screenrect;
        jeti::control::TextureOb* radar_background;
        jeti::control::TextureOb* radar_bar;
        jeti::control::TextureOb* radar_range;
        jeti::control::TextureOb* bar_bottom;
        jeti::control::TextureOb* bar_left;
        jeti::control::TextureOb* bar_top;
        jeti::control::TextureOb* bar_right;
    
        jeti::control::TextureOb* text_background;

        jeti::control::TextureOb* slot_mark_accept;
        jeti::control::TextureOb* slot_mark_reject;
        jeti::control::TextureOb* mask_round;
        jeti::control::TextureOb* mark_target;
        jeti::control::TextureOb* mark_target_slot;
                        
        static GuiTextureObCollector& Instance();
            
    private:
        GuiTextureObCollector() {};
        ~GuiTextureObCollector() {};
        
        GuiTextureObCollector(const GuiTextureObCollector&) = delete;
        GuiTextureObCollector& operator=(const GuiTextureObCollector&) = delete;
};

