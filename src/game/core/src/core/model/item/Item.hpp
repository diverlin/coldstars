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

#include <core/common/Base.hpp>
#include <core/types/TechLevelTypes.hpp>
#include <core/types/RaceTypes.hpp>

#include <ceti/type/IdType.hpp>

//to be removed
#include <core/item/ItemCommonData.hpp>

namespace model {
namespace item {

class Item : public ::model::Base
{
public:
    Item() = default;
    ~Item() = default;

    void setParentSubTypeId(entity::type parent_subtype_id) { m_parent_subtype_id = parent_subtype_id; }
    void setItemCommonData(const ItemCommonData& data_item)
    {
        m_data = data_item;
        m_deterioration = data_item.deterioration;
        setCondition(data_item.condition_max);
    }
    void setSlot(int_t slot)  { m_slot = slot; }
    void setCondition(int condition) { m_condition = condition; }

    int_t slot() const { return m_slot; }

    int mass()          const { return m_data.mass; }
    int condition()     const { return m_condition; }
    int price()         const { return m_price; }
    int basePrice()     const { return m_data.price; }
    int deterioration() const { return m_data.deterioration; }

    [[deprecated("remove")]]
    int modulesNum() const { return m_data.modules_num; }
    int descriptorType() const { return m_data.descriptor_type; }

    tech::type tech() const { return m_data.tech; }

    entity::type parentSubtype() const { return m_parent_subtype_id; }
    race::type race() const { return m_race_id; }

    int lockedTurns() const { return m_locked_turns; }

private:
    race::type m_race_id = race::type::NONE_ID;

    int m_locked_turns = 0;
    int m_condition = 0;
    int m_price = 0;
    int m_deterioration = 0;

    entity::type m_parent_subtype_id = entity::type::NONE_ID;

    ItemCommonData m_data;

    int_t m_slot = NONE;

private:
    friend class boost::serialization::access;
    template<class Archive>
    void serialize(Archive & ar, const unsigned int version) {
        ar & boost::serialization::base_object<::model::Base>(*this);
        // ..
    }
};

} // naemspace item
} // namespace model


