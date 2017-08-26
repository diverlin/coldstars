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

#include <string>
#include <map>

namespace gui {
namespace info {

class Table
{
public:
    Table(const std::map<std::string, std::string>&);
    ~Table();

    void update(const std::map<std::string, std::string>&);
    sfg::Table::Ptr widget() { return m_table; }

private:
    std::string m_id;
    sfg::Table::Ptr m_table;

    void __clear();
    void __create(const std::map<std::string, std::string>&);
};

} // naemspace info
} // namespace gui
