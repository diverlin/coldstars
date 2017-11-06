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


#include "GuiTextureObCollector.hpp"

namespace gui {

MaterialCollector& MaterialCollector::get()
{
    static MaterialCollector instance;
    return instance;
}

MaterialCollector::MaterialCollector() {
    starsystem_mark_war = __create("data/other/ss_mark_war.png");
    starsystem_mark_captured = __create("data/other/ss_mark_captured.png");
    starsystem_mark_player = __create("data/other/mark_player_ss.png");

    icon_minus = __create("data/icon/minus.png");
    icon_plus = __create("data/icon/plus.png");
    skill = __create("data/other/skill.png");
    skill_transparent = __create("data/other/skill_transparent.png");

    icon_map = __create("data/icon/starsystem_ICON.png");
    grapple_trail = __create("data/effect/grapple_jet.png");

    dot_blue = __create("data/other/dot_blue.png");
    dot_red = __create("data/other/dot_red.png");
    dot_green = __create("data/other/dot_green.png");
    dot_black = __create("data/other/dot_black.png");
    dot_yellow = __create("data/other/dot_yellow.png");
    dot_purple = __create("data/other/dot_purple.png");
    dot = __create("data/other/dot.png");

    radar_screenrect = __create("data/gui/radar_screenrect.png");
    radar_background = __create("data/gui/radar_background.png");
    radar_bar = __create("data/gui/radar_bar.png");
    radar_range = __create("data/gui/radar_range.png");
    bar_bottom = __create("data/gui/bar_bottom.png");
    bar_left = __create("data/gui/bar_left.png");
    bar_top = __create("data/gui/bar_top.png");
    bar_right = __create("data/gui/bar_right.png");

    text_background = __create("data/other/text_background.png");

    slot_mark_accept = __create("data/other/slot_mark_accept.png");
    slot_mark_reject = __create("data/other/slot_mark_reject.png");
    mask_round = __create("data/other/mask_round.png");
    mark_target = __create("data/gui/mark_target.png");
    mark_target_slot = __create("data/gui/mark_target_slot.png");
    slot = __create("data/other/slot.png");
}

MaterialCollector::~MaterialCollector()
{
    for (jeti::model::Material* model: m_models) {
        delete model;
    }
}

jeti::model::Material*
MaterialCollector::__create(const std::string& path)
{
    jeti::model::Material* model = new jeti::model::Material(path);
    m_models.push_back(model);
    return model;
}

void MaterialCollector::load() const {
    for (jeti::model::Material* model: m_models) {
        model->load();
    }
}

} // namespace gui
