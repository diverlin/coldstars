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

#include <SFGUI/Widgets.hpp>

#include "Row.hpp"

namespace gui {

class Row2 : public Row {
public:
    Row2(const std::string& title): Row(title) {
        m_labelValueSecond = sfg::Label::Create(m_valueSecond);
        m_labelValueSecond->SetId(value_id);
    }

    void setValueSecond(int value) {
        setValueSecond(std::to_string(value));
    }

    void setValueSecond(const std::string value) {
        if (m_valueSecond == value) {
            return;
        }
        m_labelValueSecond->SetText(value);
        m_valueSecond = value;
    }

    sfg::Label::Ptr labelValueSecond() const { return m_labelValueSecond; }

private:
    std::string m_valueSecond;
    sfg::Label::Ptr m_labelValueSecond;
};

} // namespace gui

