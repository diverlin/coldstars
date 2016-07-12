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

#include <descriptors/GalaxyDescriptor.hpp>
#include <descriptors/SectorDescriptor.hpp>

#include <meti/RandUtils.hpp>

#include <map>
#include <string>

namespace descriptor {

template<typename T>
class MManager {
public:
    MManager() {}
    ~MManager() {}

    void add(const T& descriptor) {
        const auto it = m_descriptors.find(descriptor.id());
        if (it == m_descriptors.end()) {
            m_descriptors.insert(std::make_pair(descriptor.id(), descriptor));
        }
        throw std::runtime_error("descriptor with that id already exist");
    }

    const T& get(const id_type& id) const {
        if (id == -1) {
            return getRand();
        }

        const auto it = m_descriptors.find(id);
        if (it != m_descriptors.end()) {
            return it->second;
        }
        throw std::runtime_error("descriptor id doesn't exist");
    }

    const T& getRand() const
    {
        auto it = m_descriptors.begin();
        std::advance( it, meti::getRandInt(0, m_descriptors.size()) );
        return it->second;
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

    void add(const Galaxy& galaxy) {
        m_galaxy.add(galaxy);
    }
    void add(const Sector& sector) {
        m_sector.add(sector);
    }

    const MManager<Galaxy>& galaxy() const { return m_galaxy; }
    const MManager<Sector>& sector() const { return m_sector; }
private:
    MManager<Galaxy> m_galaxy;
    MManager<Sector> m_sector;

    std::map<id_type, Base> m_descriptors;
    std::map<int, std::vector<Base>> m_descriptorsTypes;

    void clear();
    void generate();
}; 

} // namespace descriptor
