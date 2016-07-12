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

#include <common/IdGenerator.hpp>

#include <boost/serialization/map.hpp>
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>

#include <map>
#include <string>

namespace descriptor {

enum class Key: int {
    TYPE,
    OBJ_TYPE,
    DESCRIPTOR,
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
    SIZE,
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
    OBJ_ID,
    OWNER,
    CHILD,
    TARGET
};

enum class Type: int {
    DESCRIPTOR,
    HIT,
    CONTAINER,
    BOMB,
    STARSYSTEM,
    STAR,
    PLANET,
    ASTEROID,
    // equipment
    BAK,
    DRIVE,
    DROID,
    GRAPPLE,
    SCANER,
    RADAR,
    PROTECTOR,
    VEHICLE,
//    SHIP,
//    SATELLITE,
//    STARBASE
};

std::string keyStr(const Key&);
std::string typeStr(const Type&);

class BBase
{
public:
    BBase() {
        m_id = m_idGenerator.nextId();
    }
    ~BBase() {}

    const id_type& id() const { return m_id; }
private:
    id_type m_id;

    static IdGenerator m_idGenerator;
};

class Base
{
public:
    Base(const Type&, bool generate_id = true);
    Base(const std::string& data);
    ~Base();

    std::string data() const;

    bool operator==(const Base& rhs) const;

    const id_type& id() const;
    const id_type& objId() const;
    const id_type& type() const;
    const id_type& objType() const;
    const id_type& descriptor() const;
    const id_type& race() const;
    const id_type& damage() const;
    const id_type& radius() const;
    const id_type& tech() const;
    const id_type& modulesNum() const;
    const id_type& mass() const;
    const id_type& conditionMax() const;
    const id_type& deterioration() const;
    const id_type& fuelMax() const;
    const id_type& speed() const;
    const id_type& hyper() const;
    const id_type& repair() const;
    const id_type& strength() const;
    const id_type& scan() const;
    const id_type& protection() const;
    const id_type& price() const;

    //vehicle
    const id_type& space() const;
    const id_type& armor() const;
    const id_type& temperature() const;
    const id_type& drawTurrels() const;
    const id_type& size() const;
    const id_type& bakSlotNum() const;
    const id_type& driveSlotNum() const;
    const id_type& droidSlotNum() const;
#ifdef USE_EXTRA_EQUIPMENT
    const id_type& energizerSlotNum() const;
    const id_type& freezerSlotNum() const;
#endif
    const id_type& grappleSlotNum() const;
    const id_type& protectorSlotNum() const;
    const id_type& radarSlotNum() const;
    const id_type& scanerSlotNum() const;
    const id_type& weaponSlotNum() const;
    const id_type& artefactSlotNum() const;
    const id_type& cargoSlotNum() const;

    // dynamic
    const id_type& owner() const;
    const id_type& child() const;
    const id_type& target() const;

public: // todo make it protected
    void add(const Key& key, const id_type& value);

private:
    const id_type& __getOrDie(const Key& key) const;
    const id_type& __get(const Key& key) const;

    friend class boost::serialization::access;
    template<class Archive>
    void serialize(Archive & ar, const unsigned int version)
    {
        ar & m_map;
    }

    std::map<Key, id_type> m_map;
    static IdGenerator m_idGenerator;
};

} // namespace descriptor
