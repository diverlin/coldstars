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
#include <ceti/NonCopyable.hpp>
#include <ceti/IdGenerator.hpp>

#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>

namespace ceti {

namespace descriptor {

class BaseView
{
public:
    BaseView() {
        m_id = m_idGenerator.nextId();
    }
    ~BaseView() = default;

    int_t id() const { return m_id; }
    int_t texture() const { return m_texture; }
    int_t mesh() const { return m_mesh; }

    void setTexture(int_t texture) { m_texture = texture; }
    void setMesh(int_t mesh) { m_mesh = mesh; }
    virtual std::string info() const {
        std::string result = "BaseView descriptor:\n";
        result += std::string(" id = ") + std::to_string(m_id) + "\n";
        result += std::string(" material = ") + std::to_string(m_texture) + "\n";
        result += std::string(" geometry = ") + std::to_string(m_mesh) + "\n";
        return result;
    }

protected:
    std::string _str(const std::string& label, const std::vector<int_t>& ids) const {
        std::string result = label;
        for (int_t id: ids) {
            result += std::to_string(id) + ",";
        }
        return result;
    }

private:
    friend class boost::serialization::access;
    template<class Archive>
    void serialize(Archive & ar, const unsigned int version) {
        ar & m_id;
        ar & m_texture;
        ar & m_mesh;
    }

private:
    int_t m_id = -1;
    int_t m_texture = -1;
    int_t m_mesh = -1;

    static IdGenerator m_idGenerator;
};

} // namespace descriptor

} // namespace ceti
