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

namespace gui {

const std::string title_id = "title";
const std::string value_id = "value";

class Row {
public:
    Row(const std::string& title) {
        m_labelTitle = sfg::Label::Create(title+":");
        m_labelTitle->SetId(title_id);

        m_labelValue = sfg::Label::Create(m_value);
        m_labelValue->SetId(value_id);
    }

    void setValue(int value) {
        setValue(std::to_string(value));
    }

    void setValue(const std::string& value) {
        if (m_value == value) {
            return;
        }
        m_labelValue->SetText(value);
        m_value = value;
    }

    sfg::Label::Ptr labelTitle() const { return m_labelTitle; }
    sfg::Label::Ptr labelValue() const { return m_labelValue; }

private:
    std::string m_title;
    std::string m_value;

    sfg::Label::Ptr m_labelTitle;
    sfg::Label::Ptr m_labelValue;
};

} // namespace gui
