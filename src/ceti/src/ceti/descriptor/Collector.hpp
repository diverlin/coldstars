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

#include <ceti/type/IdType.hpp>
#include <ceti/FsUtils.hpp>

#include <meti/RandUtils.hpp>

#include <map>
#include <vector>
#include <fstream>

namespace ceti {
namespace descriptor {


template<typename T>
class Collector
{
public:
    Collector(const std::string& fname): m_fname(fname) {
        if (ceti::filesystem::is_file_exists(m_fname)) {
            load();
        }
    }
    ~Collector() {}

    bool loaded() const { return m_loaded; }

    void add(const T& ob) {
        if (!__isExist(ob)) {
            m_descriptors.insert(std::make_pair( ob.id(), ob ));
            m_descriptorsTypes[ob.type()].push_back(ob);
        } else {
            throw std::runtime_error("fail add, id is already exist");
        }
    }

    const T& get(const int_t& id) const {
        auto it = m_descriptors.find(id);
        if (it != m_descriptors.end()) {
            return it->second;
        } else {
            throw std::runtime_error("fail get, id doesn't exist");
        }
        assert(false);
    }

    const T& getByType(int type) const {
        auto it = m_descriptorsTypes.find(type);
        if (it != m_descriptorsTypes.end()) {
            return meti::getRand(it->second);
        } else {
            throw std::runtime_error("fail get, type doesn't exist");
        }
        assert(false);
    }

    void save() const
    {
        ceti::filesystem::touch_file(m_fname);

        std::fstream filestream;
        filestream.open(m_fname);
        if(filestream.is_open()) {
            for(const auto& lists: m_descriptorsTypes) {
                const auto& list = lists.second;
                for(const T& descr: list) {
                    filestream<<descr.data()<<std::endl;
                }
            }
        } else {
            throw std::runtime_error("not able to open file="+m_fname);
        }
        filestream.close();
    }

    void load()
    {
        __clear();

        std::fstream filestream;
        std::string line;
        filestream.open(m_fname);
        if(filestream.is_open()) {
            while(std::getline(filestream, line)) {
                if (!line.empty()) {
                    const T& descr = T(line);
                    add(descr);
                }
            }
        }
        filestream.close();
        m_loaded = true;
    }


private:
    bool m_loaded = false;
    std::string m_fname;
    std::map<int, T> m_descriptors;
    std::map<int, std::vector<T>> m_descriptorsTypes;

    bool __isExist(const T& ob) const {
        return (m_descriptors.find(ob.id()) != m_descriptors.end());
    }

    void __clear() {
        m_descriptors.clear();
        m_descriptorsTypes.clear();
    }
};

} // namespace descriptor
} // namespace ceti


