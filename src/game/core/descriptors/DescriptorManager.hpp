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

#include <descriptors/Base.hpp>

#include <map>
#include <string>

class DescriptorManager
{
public:
    DescriptorManager();
    ~DescriptorManager();

    void add(const descriptor::Base&);
    descriptor::Base getRandom(const descriptor::Type&);
    descriptor::Base get(const id_type&);

    void init();
    void save();
    void load();

    int size() const { return m_descriptors.size(); }

private:
    std::map<id_type, descriptor::Base> m_descriptors;
    std::map<int, std::vector<descriptor::Base>> m_descriptorsTypes;

    void clear();
    void generate();
}; 
