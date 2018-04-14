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
//#include <ceti/InfoTable.hpp>

//#include <boost/archive/text_oarchive.hpp>
//#include <boost/archive/text_iarchive.hpp>

//#include <vector>

namespace descriptor {
class Base;
} // namespace descriptor

namespace model {
class Base;
} // namespace model

namespace core {
namespace control {

class Base : private NonCopyable
{
public:
    Base(descriptor::Base*, model::Base*);
    virtual ~Base() = default;

    void setId(int_t id);

    int_t id() const;
    entity::Type type() const;
    entity::Type group() const;

    bool isAlive() const;
    void die();

    descriptor::Base* descriptor() const { return m_descriptor_base; }
    model::Base* model() const { return m_model_base; }

private:
    descriptor::Base* m_descriptor_base = nullptr;
    model::Base* m_model_base = nullptr;

    virtual void __putChildrenToGarbage() const {}
};

} // namespace control
} // namespace core

//class Base : private NonCopyable
//{
//public:
//    Base() = default;
//    virtual ~Base() = default;

//    void setId(int_t id) { m_id = id; }

//    int_t id() { return m_id; }

//private:
//    int_t m_id = NONE;
//};

