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

#include <boost/serialization/map.hpp>
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>

#include <map>
#include <string>

namespace descriptor {

enum class Key: int {
    // const
    TYPE,
    RACE,
    DAMAGE,
    RADIUS,
    TECH,
    MODULES_NUM,
    MASS,
    CONDITION_MAX,
    DETERIORATION,
    FUEL_MAX,
    SPEED,
    HYPER,
    REPAIR,
    STRENGTH,
    SCAN,
    PROTECTION,
    PRICE,
    // vehicle
    SPACE,
    ARMOR,
    TEMPERATURE,
    DRAW_TURRELS,
    BAK_SLOT_NUM,
    DRIVE_SLOT_NUM,
    DROID_SLOT_NUM,
#ifdef USE_EXTRA_EQUIPMENT
    ENERGIZER_SLOT_NUM,
    FREEZER_SLOT_NUM,
#endif // USE_EXTRA_EQUIPMENT
    GRAPPLE_SLOT_NUM,
    PROTECTOR_SLOT_NUM,
    RADAR_SLOT_NUM,
    SCANER_SLOT_NUM,
    WEAPON_SLOT_NUM,
    ARTEFACT_SLOT_NUM,
    CARGO_SLOT_NUM,
    // dynamic
    ID,
    OWNER,
    CHILD,
    TARGET
};

enum class Type: int {
    HIT,
    CONTAINER,
    BOMB,
    STARSYSTEM,
    BAK,
    DRIVE,
    DROID,
    GRAPPLE,
    SCANER,
    RADAR,
    PROTECTOR
};

std::string keyStr(const Key&);
std::string typeStr(const Type&);

class Base
{
public:
    Base();
    Base(const std::map<Key, int_type>&);
    Base(const std::string& data);
    ~Base();

    std::string data() const;

    bool operator==(const Base& rhs) const;

    const int_type& id() const;
    const int_type& type() const;
    const int_type& race() const;
    const int_type& owner() const;
    const int_type& child() const;
    const int_type& target() const;
    const int_type& damage() const;
    const int_type& radius() const;
    const int_type& tech() const;
    const int_type& modulesNum() const;
    const int_type& mass() const;
    const int_type& conditionMax() const;
    const int_type& deterioration() const;
    const int_type& fuelMax() const;
    const int_type& speed() const;
    const int_type& hyper() const;
    const int_type& repair() const;
    const int_type& strength() const;
    const int_type& scan() const;
    const int_type& protection() const;
    const int_type& price() const;

    //vehicle
    const int_type& space() const;
    const int_type& armor() const;
    const int_type& temperature() const;
    const int_type& drawTurrels() const;
    const int_type& bakSlotNum() const;
    const int_type& driveSlotNum() const;
    const int_type& droidSlotNum() const;
#ifdef USE_EXTRA_EQUIPMENT
    const int_type& energizerSlotNum() const;
    const int_type& freezerSlotNum() const;
#endif
    const int_type& grappleSlotNum() const;
    const int_type& protectorSlotNum() const;
    const int_type& radarSlotNum() const;
    const int_type& scanerSlotNum() const;
    const int_type& weaponSlotNum() const;
    const int_type& artefactSlotNum() const;
    const int_type& cargoSlotNum() const;

public: // todo make it protected
    void add(const Key& key, const int_type& value);

private:
    const int_type& get(const Key& key) const;

    friend class boost::serialization::access;
    template<class Archive>
    void serialize(Archive & ar, const unsigned int version)
    {
        ar & m_map;
    }

    std::map<Key, int_type> m_map;
}; 

} // namespace descriptor
