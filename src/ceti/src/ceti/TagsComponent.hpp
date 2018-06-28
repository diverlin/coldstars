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

#include <ceti/Pack.hpp>

#include <string>
#include <map>

namespace ceti {

class TagsComponent {
public:
    TagsComponent();
    ~TagsComponent();

    static void reg(const std::string& tag);
    static void reg(const ceti::pack<std::string>& tags);
    static void unreg(const std::string& tag);
    static void unreg(const ceti::pack<std::string>& tags);

    void add(const std::string& tag);

    void add(const ceti::pack<std::string>& tags);

    void remove(const std::string& tag);
    void remove(const ceti::pack<std::string>& tags);

    static ceti::pack<int> ids_from(const std::string& tags);
    static ceti::pack<int> ids_from(const ceti::pack<std::string>& tags);

    const ceti::pack<int>& tags() const { return m_data; }

    bool match(const ceti::pack<int> queue) const;

private:
    ceti::pack<int> m_data;

    static void __reg(const std::string& tag);

    static int __id(const std::string& tag);

    void __add(const std::string& tag);

    void __warn_not_registered_tag(const std::string& tag) const;

protected:
    static int counter;
    static std::map<std::string, int> dict;
    static std::map<int, std::string> rdict;
};

} // namespace ceti

