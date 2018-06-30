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

#include <core/struct/IdData.hpp>
#include <core/type/DescriptorType.hpp>

#include <ceti/NonCopyable.hpp>
#include <ceti/Base.hpp>
#include <ceti/InfoTable.hpp>

#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>

#include <vector>

namespace core {
class BaseDescr;
} // namespace core

class EntityManager;

namespace core {

class BaseModel : public NonCopyable
{
public:
    BaseModel() = default;
    virtual ~BaseModel() = default;

    void setIsAlive(bool alive) { m_isAlive = alive; }
    void setId(int_t id) { m_id = id; }
    void setDescriptor(int_t descriptor) { m_descriptor = descriptor; }

    bool isAlive() const { return m_isAlive; }
    int_t id() const { return m_id; }
    int_t descriptor() const { return m_descriptor; }

    void setWritable(bool writable) { m_writable = writable; }

    virtual ceti::InfoTable info() const {
        ceti::InfoTable result;
        result.add("BaseModel");
        result.add("isAlive", m_isAlive);
        result.add("id", m_id);
        result.add("descriptor", m_descriptor);
        return result;
    }

protected:
    bool _isWritable() const { return m_writable; }

private:
    bool m_writable = true;
    bool m_isAlive = true;
    int_t m_id = NONE;
    int_t m_descriptor = NONE;

private:
    friend class boost::serialization::access;
    template<class Archive>
    void serialize(Archive & ar, const unsigned int version) {
        ar & m_isAlive;
        ar & m_id;
        ar & m_descriptor;
    }
};

} // namespace core

