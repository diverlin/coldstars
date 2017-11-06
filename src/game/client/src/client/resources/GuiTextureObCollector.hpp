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
    jeti::model::Material* starsystem_mark_war = nullptr;
    jeti::model::Material* starsystem_mark_captured = nullptr;
    jeti::model::Material* starsystem_mark_player = nullptr;
    
    jeti::model::Material* icon_minus = nullptr;
    jeti::model::Material* icon_plus = nullptr;
    jeti::model::Material* skill = nullptr;
    jeti::model::Material* skill_transparent = nullptr;
    
    jeti::model::Material* icon_map = nullptr;
    jeti::model::Material* grapple_trail = nullptr;

    jeti::model::Material* dot_blue = nullptr;
    jeti::model::Material* dot_red = nullptr;
    jeti::model::Material* dot_green = nullptr;
    jeti::model::Material* dot_black = nullptr;
    jeti::model::Material* dot_yellow = nullptr;
    jeti::model::Material* dot_purple = nullptr;
    jeti::model::Material* dot = nullptr;

    jeti::model::Material* radar_screenrect = nullptr;
    jeti::model::Material* radar_background = nullptr;
    jeti::model::Material* radar_bar = nullptr;
    jeti::model::Material* radar_range = nullptr;
    jeti::model::Material* bar_bottom = nullptr;
    jeti::model::Material* bar_left = nullptr;
    jeti::model::Material* bar_top = nullptr;
    jeti::model::Material* bar_right = nullptr;
    
    jeti::model::Material* text_background = nullptr;

    jeti::model::Material* slot_mark_accept = nullptr;
    jeti::model::Material* slot_mark_reject = nullptr;
    jeti::model::Material* mask_round = nullptr;
    jeti::model::Material* mark_target = nullptr;
    jeti::model::Material* mark_target_slot = nullptr;
    jeti::model::Material* slot = nullptr;

    static MaterialCollector& get();

    void load() const;

private:
    MaterialCollector();
    ~MaterialCollector();

    MaterialCollector(const MaterialCollector&) = delete;
    MaterialCollector& operator=(const MaterialCollector&) = delete;

    std::vector<jeti::model::Material*> m_models;

    jeti::model::Material* __create(const std::string&);
};

} // namespace gui
