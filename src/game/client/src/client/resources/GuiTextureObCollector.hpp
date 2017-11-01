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

namespace gui {

class MaterialCollector
{
public:
    jeti::control::Material* starsystem_mark_war = nullptr;
    jeti::control::Material* starsystem_mark_captured = nullptr;
    jeti::control::Material* starsystem_mark_player = nullptr;
    
    jeti::control::Material* icon_minus = nullptr;
    jeti::control::Material* icon_plus = nullptr;
    jeti::control::Material* skill = nullptr;
    jeti::control::Material* skill_transparent = nullptr;
    
    jeti::control::Material* icon_map = nullptr;
    jeti::control::Material* grapple_trail = nullptr;

    jeti::control::Material* dot_blue = nullptr;
    jeti::control::Material* dot_red = nullptr;
    jeti::control::Material* dot_green = nullptr;
    jeti::control::Material* dot_black = nullptr;
    jeti::control::Material* dot_yellow = nullptr;
    jeti::control::Material* dot_purple = nullptr;

    jeti::control::Material* radar_screenrect = nullptr;
    jeti::control::Material* radar_background = nullptr;
    jeti::control::Material* radar_bar = nullptr;
    jeti::control::Material* radar_range = nullptr;
    jeti::control::Material* bar_bottom = nullptr;
    jeti::control::Material* bar_left = nullptr;
    jeti::control::Material* bar_top = nullptr;
    jeti::control::Material* bar_right = nullptr;
    
    jeti::control::Material* text_background = nullptr;

    jeti::control::Material* slot_mark_accept = nullptr;
    jeti::control::Material* slot_mark_reject = nullptr;
    jeti::control::Material* mask_round = nullptr;
    jeti::control::Material* mark_target = nullptr;
    jeti::control::Material* mark_target_slot = nullptr;

    static MaterialCollector& get();

private:
    MaterialCollector() {}
    ~MaterialCollector() {}

    MaterialCollector(const MaterialCollector&) = delete;
    MaterialCollector& operator=(const MaterialCollector&) = delete;
};

} // namespace gui
