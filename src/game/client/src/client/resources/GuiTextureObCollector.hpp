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
    jeti::MaterialModel* starsystem_mark_war = nullptr;
    jeti::MaterialModel* starsystem_mark_captured = nullptr;
    jeti::MaterialModel* starsystem_mark_player = nullptr;
    
    jeti::MaterialModel* icon_minus = nullptr;
    jeti::MaterialModel* icon_plus = nullptr;
    jeti::MaterialModel* skill = nullptr;
    jeti::MaterialModel* skill_transparent = nullptr;
    
    jeti::MaterialModel* icon_map = nullptr;
    jeti::MaterialModel* grapple_trail = nullptr;

    jeti::MaterialModel* dot_blue = nullptr;
    jeti::MaterialModel* dot_red = nullptr;
    jeti::MaterialModel* dot_green = nullptr;
    jeti::MaterialModel* dot_black = nullptr;
    jeti::MaterialModel* dot_yellow = nullptr;
    jeti::MaterialModel* dot_purple = nullptr;
    jeti::MaterialModel* dot = nullptr;

    jeti::MaterialModel* radar_screenrect = nullptr;
    jeti::MaterialModel* radar_background = nullptr;
    jeti::MaterialModel* radar_bar = nullptr;
    jeti::MaterialModel* radar_range = nullptr;
    jeti::MaterialModel* bar_bottom = nullptr;
    jeti::MaterialModel* bar_left = nullptr;
    jeti::MaterialModel* bar_top = nullptr;
    jeti::MaterialModel* bar_right = nullptr;
    
    jeti::MaterialModel* text_background = nullptr;

    jeti::MaterialModel* slot_mark_accept = nullptr;
    jeti::MaterialModel* slot_mark_reject = nullptr;
    jeti::MaterialModel* mask_round = nullptr;
    jeti::MaterialModel* mark_target = nullptr;
    jeti::MaterialModel* mark_target_slot = nullptr;
    jeti::MaterialModel* slot = nullptr;

    static MaterialCollector& get();

    void load() const;

private:
    MaterialCollector();
    ~MaterialCollector();

    MaterialCollector(const MaterialCollector&) = delete;
    MaterialCollector& operator=(const MaterialCollector&) = delete;

    std::vector<jeti::MaterialModel*> m_models;

    jeti::MaterialModel* __create(const std::string&);
};

} // namespace gui
