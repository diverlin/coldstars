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
        m_labelSecondNum = sfg::Label::Create(std::to_string(m_secondNum));
        m_labelSecondNum->SetId(value_id);
    }

    void setSecondNum(int num) {
        if (m_secondNum == num) {
            return;
        }
        m_labelSecondNum->SetText(std::to_string(num));
        m_secondNum = num;
    }

    sfg::Label::Ptr labelSecondNum() const { return m_labelSecondNum; }

private:
    int m_secondNum = 0;
    sfg::Label::Ptr m_labelSecondNum;
};

} // namespace gui

