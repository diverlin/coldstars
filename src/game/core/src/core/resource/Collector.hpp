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

#include <client/common/global.hpp>

#include <core/type/CollectorType.hpp>
#include <core/resource/MdLoader.hpp>

#include <ceti/IdGenerator.hpp>

#include <ceti/descriptor/Mesh.hpp>
#include <ceti/descriptor/Texture.hpp>

#include <ceti/type/IdType.hpp>
#include <ceti/FsUtils.hpp>

#include <meti/RandUtils.hpp>

#include <map>
#include <vector>
#include <fstream>

namespace {

template<typename T>
void resolveTypeId(T* ob, const type::Collector& types)
{
    ob->setType(types.toInt(ob->typeStr()));
}

} // namespace

template<typename T>
class Collector
{
public:
    Collector(const std::string& fname)
        : m_fname(fname), m_failback(new T) {
        if (ceti::filesystem::is_file_exists(m_fname)) {
            __load();
        }
    }
    ~Collector() = default;

    bool loaded() const { return m_loaded; }
    T* failback() const { return m_failback; }

    void add(T* ob) {
        ob->setId(m_idGenerator.nextId());
        if (!contains(ob->id())) {
            m_descriptors.insert(std::make_pair( ob->id(), ob ));
            m_descriptorsTypes[ob->type()].push_back(ob);
        } else {
            throw std::runtime_error("fail add, id is already exist");
        }
    }

    T* get(int_t id) const {
        T* result = nullptr;
        auto it = m_descriptors.find(id);
        if (it != m_descriptors.end()) {
            result = it->second;
        }
#ifdef USE_FAILBACK_RESOURCES
        else {
            result = failback();
        }
#endif // USE_FAILBACK_RESOURCES
        assert(result);
        return result;
    }

    T* random(int_t type) const {
        T* result = nullptr;
        auto it = m_descriptorsTypes.find(type);
        if (it != m_descriptorsTypes.end()) {
            result = meti::rand_element(it->second);
        }
#ifdef USE_FAILBACK_RESOURCES
        else {
            result = failback();
        }
#endif // USE_FAILBACK_RESOURCES
        assert(result);
        return result;
    }

    bool contains(int_t id) const {
        return (m_descriptors.find(id) != m_descriptors.end());
    }

    void generate(const std::vector<std::string>& list, const type::Collector& types) {
        __clear();
        for(const auto& filepath: list) {
            T* ob = new T;
            InfoLoader::read(filepath, ob);

            resolveTypeId(ob, types);
            add(ob);
        }
        __save();
    }

private:
    IdGenerator m_idGenerator;

    bool m_loaded = false;
    std::string m_fname;
    T* m_failback = nullptr;
    std::map<int, T*> m_descriptors;
    std::map<int, std::vector<T*>> m_descriptorsTypes;

    void __clear() {
        m_descriptors.clear();
        m_descriptorsTypes.clear();
    }

    void __load()
    {
        __clear();

        std::fstream filestream;
        std::string line;
        filestream.open(m_fname);
        if(filestream.is_open()) {
            while(std::getline(filestream, line)) {
                if (!line.empty()) {
                    T* descr = new T(line);
                    add(descr);
                }
            }
        }
        filestream.close();
        m_loaded = true;
    }

    void __save() const
    {
#ifdef DUMP_DESCRIPTORS
        ceti::filesystem::touch_file(m_fname);

        std::fstream filestream;
        filestream.open(m_fname);
        if(filestream.is_open()) {
            for(const auto& lists: m_descriptorsTypes) {
                const auto& list = lists.second;
                for(T* descr: list) {
                    filestream<<descr->data()<<std::endl;
                }
            }
        } else {
            throw std::runtime_error("not able to open file="+m_fname);
        }
        filestream.close();
#endif // DUMP_DESCRIPTORS
    }

};



