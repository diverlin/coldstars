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
#include <descriptors/SectorDescriptor.hpp>

#include <map>
#include <string>

namespace descriptor {

template<typename T>
class MManager {
public:
    MManager() {}
    ~MManager() {}

    void add(const T& descriptor) {
        if (!m_descriptors.contains(descriptor.id())) {
            m_descriptors.insert(std::make_pair(descriptor.id(), descriptor));
        }
        throw std::runtime_error("descriptor with that id already exist");
    }

    const T& get(const id_type& id) const {
        if (m_descriptors.contains(id)) {
            return m_descriptors[id];
        }
        throw std::runtime_error("descriptor id doesn't exist");
    }

private:
    std::map<id_type, T> m_descriptors;
};

class Manager
{
public:
    Manager();
    ~Manager();


    void add(const Base&);
    Base getRand(const Type&);
    Base get(const id_type&);

    void save();
    void load();

    int size() const { return m_descriptors.size(); }

private:
    MManager<Sector> sector;

    std::map<id_type, Base> m_descriptors;
    std::map<int, std::vector<Base>> m_descriptorsTypes;

    void clear();
    void generate();
}; 

} // namespace descriptor
