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

#include <jeti/Material.hpp>

class GuiTextureObCollector
{
    public:
        jeti::control::Material* starsystem_mark_war;
        jeti::control::Material* starsystem_mark_captured;
        jeti::control::Material* starsystem_mark_player;
    
        jeti::control::Material* icon_minus;
        jeti::control::Material* icon_plus;
        jeti::control::Material* skill;
        jeti::control::Material* skill_transparent;
    
        jeti::control::Material* icon_map;
        jeti::control::Material* grapple_trail;

        jeti::control::Material* dot_blue;
        jeti::control::Material* dot_red;
        jeti::control::Material* dot_green;
        jeti::control::Material* dot_black;
        jeti::control::Material* dot_yellow;
        jeti::control::Material* dot_purple;

        jeti::control::Material* radar_screenrect;
        jeti::control::Material* radar_background;
        jeti::control::Material* radar_bar;
        jeti::control::Material* radar_range;
        jeti::control::Material* bar_bottom;
        jeti::control::Material* bar_left;
        jeti::control::Material* bar_top;
        jeti::control::Material* bar_right;
    
        jeti::control::Material* text_background;

        jeti::control::Material* slot_mark_accept;
        jeti::control::Material* slot_mark_reject;
        jeti::control::Material* mask_round;
        jeti::control::Material* mark_target;
        jeti::control::Material* mark_target_slot;
                        
        static GuiTextureObCollector& Instance();
            
    private:
        GuiTextureObCollector() {};
        ~GuiTextureObCollector() {};
        
        GuiTextureObCollector(const GuiTextureObCollector&) = delete;
        GuiTextureObCollector& operator=(const GuiTextureObCollector&) = delete;
};

