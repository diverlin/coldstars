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

#include <core/model/Base.hpp>

#include <ceti/type/IdType.hpp>

namespace core {

class ItemModel : public BaseModel
{
public:
    ItemModel() = default;
    ~ItemModel() = default;

    void setSlot(int slot)  { m_slot = slot; }
    void setLockedTurns(int lockedTurns) { m_lockedTurns = lockedTurns; }
    void setCondition(int condition) { m_condition = condition; }

    int_t slot() const { return m_slot; }
    int lockedTurns() const { return m_lockedTurns; }
    int condition() const { return m_condition; }

    ceti::InfoTable info() const override {
        ceti::InfoTable result = BaseModel::info();
        result.add("Item");
        result.add("slot", m_slot);
        result.add("lockedTurns", m_lockedTurns);
        result.add("condition", m_condition);
        return result;
    }

private:
    int m_slot = NONE;
    int m_lockedTurns = 0;
    int m_condition = 0;

private:
    friend class boost::serialization::access;
    template<class Archive>
    void serialize(Archive & ar, const unsigned int version) {
        ar & boost::serialization::base_object<::core::BaseModel>(*this);
        ar & m_slot;
        ar & m_lockedTurns;
        ar & m_condition;
    }
};

} // namespace core


