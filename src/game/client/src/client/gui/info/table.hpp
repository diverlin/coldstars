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

#include <string>
#include <map>

namespace info {

class Table
{
public:
    Table() = default;
    ~Table() = default;

public:
    void addRow(const std::string& key, const std::string& value) { m_data.insert(std::make_pair(key, value)); }
    void addRow(const std::string& key, int value) { m_data.insert(std::make_pair(key, std::to_string(value))); }
    void addRow(const std::string& key, float value) { m_data.insert(std::make_pair(key, std::to_string(value))); }
    void addRow(const std::string& key, size_t value) { m_data.insert(std::make_pair(key, std::to_string(value))); }

    void clear() { m_data.clear(); }

    std::string text() const {
        std::string result;
        for(auto pair: m_data) {
            result += pair.first + "    " + pair.second + "\n";
        }
        return result;
    }

private:
    std::map<std::string, std::string> m_data;
};

} // naemspace info

