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

#include <types/IdType.hpp>

#include <meti/RandUtils.hpp>

#include <map>
#include <vector>

namespace descriptor {


template<typename T>
class Collector
{
public:
    Collector() {}
    ~Collector() {}

    void add(const T& ob) {
        if (!__isExist(ob)) {
            m_descriptorsById.insert(std::make_pair( ob.id(), ob ));
            m_descriptorsByTypes[ob.type()].push_back(ob);
        } else {
            throw std::runtime_error("fail add, id is already exist");
        }
    }

    const T& get(const id_type& id) const {
        auto it = m_descriptorsById.find(id);
        if (it != m_descriptorsById.end()) {
            return it->second;
        } else {
            throw std::runtime_error("fail get, id doesn't exist");
        }
        assert(false);
    }

    const T& getByType(int type) const {
        auto it = m_descriptorsByTypes.find(type);
        if (it != m_descriptorsByTypes.end()) {
            return meti::getRand(it->second);
        } else {
            throw std::runtime_error("fail get, type doesn't exist");
        }
        assert(false);
    }


private:
    std::map<int, T> m_descriptorsById;
    std::map<int, std::vector<T>> m_descriptorsByTypes;

    bool __isExist(const T& ob) const {
        return (m_descriptorsById.find(ob.id()) != m_descriptorsById.end());
    }
};

} // namespace descriptor



