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



enum Code {
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
    TARGET,

    // string
    IDLIST
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
    const id_type& texture() const { return m_texture; }
    const id_type& mesh() const { return m_mesh; }

    void setTexture(const id_type& texture) { m_texture = texture; }
    void setMesh(const id_type& mesh) { m_mesh = mesh; }
    virtual std::string info() const {
        std::string result;
        result += std::string("id=") + std::to_string(m_id);
        result += std::string(" material=") + std::to_string(m_texture);
        result += std::string(" geometry=") + std::to_string(m_mesh);
        return result;
    }

protected:
    std::string _str(const std::string& label, const std::vector<id_type>& ids) const {
        std::string result = label;
        for (const id_type& id: ids) {
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
    id_type m_id = -1;
    id_type m_texture = -1;
    id_type m_mesh = -1;

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

    const id_type& texture() const;
    const id_type& mesh() const;

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



struct Id {
    Id(int c, const std::string& n)
        :
          code(c)
        , name(n)
    {}
    Id(const Id& id)
        :
          code(id.code)
        , name(id.name)
    {}
    int code = 0;
    std::string name = "";
};

class Property : public Id {
public:
    enum {INT, STR};

    Property(const Id& id, const int_type& value)
        :
          Id(id)
        , valueType(INT)
        , intValue(value)
    {}
    Property(const Id& id, const std::string& value)
        :
          Id(id)
        , valueType(STR)
        , strValue(value)
    {}
    int valueType;
    int_type intValue = 0;
    std::string strValue = "";
};

class BaseD
{
public:
    BaseD(/*const id_type&, bool generate_id = true*/);
    BaseD(const std::string& data);
    ~BaseD();

    std::string data() const;

    bool operator==(const BaseD& rhs) const;

    const int_type& get(int) const;

    void add(const Property&);
    void add(const std::vector<Property>&);

    std::string info() const;

private:
    friend class boost::serialization::access;
    template<class Archive>
    void serialize(Archive & ar, const unsigned int version) {
        ar & m_type;
        ar & m_intValues;
        if (!m_strValues.empty()) {
            ar & m_strValues;
        }
    }

    id_type m_type = -1;
    std::map<int, int_type> m_intValues;
    std::map<int, std::string> m_strValues;
    static IdGenerator m_idGenerator; // ?
};



//const Id typeId( TYPE, "type" );
//const Id objTypeId( OBJ_TYPE, "obj_type" );
//const Id descriptorId( DESCRIPTOR, "descriptor" );
//const Id raceId( RACE, "race");
//const Id damageId( DAMAGE, "damage" );
//const Id radiusId( RADIUS, "radius" );
//const Id techId( TECH, "tech" );
//const Id modulesNumId( MODULES_NUM, "modules_num" );
//const Id massId( MASS, "mass" );
//const Id conditionMaxId( CONDITION_MAX, "condition_max" );
//const Id deteriorationId( DETERIORATION, "deterioretion" );
//const Id fuelMaxId( FUEL_MAX, "fuel_max" );
//const Id speedId( SPEED, "speed" );
//const Id hyperId( HYPER, "hyper" );
//const Id repairId( REPAIR, "repair" );
//const Id strengthId( STRENGTH, "strength" );
//const Id scanId( SCAN, "scan" );
//const Id protectionId( PROTECTION, "protection" );
//const Id priceId( PRICE, "price" );
//// vehicle
//const Id spaceId( SPACE, "space" );
//const Id armorId( ARMOR, "armor" );
//const Id temperatureId( TEMPERATURE, "temperature" );
//const Id drawTurrelsId( DRAW_TURRELS, "draw_turrels" );
//const Id sizeId( SIZE, "size" );
//const Id bakSlotNumId( BAK_SLOT_NUM, "bak_slot_num" );
//const Id driveSlotNumId( DRIVE_SLOT_NUM, "drive_slot_num" );
//const Id droidSlotNumId( DROID_SLOT_NUM, "droid_slot_num" );
//#ifdef USE_EXTRA_EQUIPMENT
//const Id energizerSlotNumId( ENERGIZER_SLOT_NUM, "energizer_slot_num" );
//const Id freezerSlotNumId( FREEZER_SLOT_NUM, "freezer_slot_num" );
//#endif // USE_EXTRA_EQUIPMENT
//const Id grappleSlotNumId( GRAPPLE_SLOT_NUM, "grapple_slot_num" );
//const Id protectorSlotNumId( PROTECTOR_SLOT_NUM, "protector_slot_num" );
//const Id radarSlotNumId( RADAR_SLOT_NUM, "radar_slot_num" );
//const Id scanerSlotNumId( SCANER_SLOT_NUM, "scaner_slot_num" );
//const Id weaponSlotNumId( WEAPON_SLOT_NUM, "weapon_slot_num" );
//const Id artefactSlotNumId( ARTEFACT_SLOT_NUM, "artefact_slot_num" );
//const Id cargoSlotNumId( CARGO_SLOT_NUM, "cargo_slot_num" );
//// dynamic
//const Id idId( ID, "id" );
//const Id objIdId( OBJ_ID, "obj_id" );
//const Id ownerId( OWNER, "owner" );
//const Id childId( CHILD, "child" );
//const Id targetId( TARGET, "target" );

const std::map<int, Id> IDs = {

    { TYPE, Id( TYPE, "type" ) }
    , { OBJ_TYPE, Id( OBJ_TYPE, "obj_type" ) }
    , { DESCRIPTOR, Id( DESCRIPTOR, "descriptor" ) }
    , { RACE, Id( RACE, "race") }
    , { DAMAGE, Id( DAMAGE, "damage" ) }
    , { RADIUS, Id( RADIUS, "radius" ) }
    , { TECH, Id( TECH, "tech" ) }
    , { MODULES_NUM, Id( MODULES_NUM, "modules_num" ) }
    , { MASS, Id( MASS, "mass" ) }
    , { CONDITION_MAX, Id( CONDITION_MAX, "condition_max" ) }
    , { DETERIORATION, Id( DETERIORATION, "deterioretion" ) }
    , { FUEL_MAX, Id( FUEL_MAX, "fuel_max" ) }
    , { SPEED, Id( SPEED, "speed" ) }
    , { HYPER, Id( HYPER, "hyper" ) }
    , { REPAIR, Id( REPAIR, "repair" ) }
    , { STRENGTH, Id( STRENGTH, "strength" ) }
    , { SCAN, Id( SCAN, "scan" ) }
    , { PROTECTION, Id( PROTECTION, "protection" ) }
    , { PRICE, Id( PRICE, "price" ) }
    // vehicle
    , { SPACE, Id( SPACE, "space" ) }
    , { ARMOR, Id( ARMOR, "armor" ) }
    , { TEMPERATURE, Id( TEMPERATURE, "temperature" ) }
    , { DRAW_TURRELS, Id( DRAW_TURRELS, "draw_turrels" ) }
    , { SIZE, Id( SIZE, "size" ) }
    , { BAK_SLOT_NUM, Id( BAK_SLOT_NUM, "bak_slot_num" ) }
    , { DRIVE_SLOT_NUM, Id( DRIVE_SLOT_NUM, "drive_slot_num" ) }
    , { DROID_SLOT_NUM, Id( DROID_SLOT_NUM, "droid_slot_num" ) }
    #ifdef USE_EXTRA_EQUIPMENT
    , { ENERGIZER_SLOT_NUM, Id( ENERGIZER_SLOT_NUM, "energizer_slot_num" ) }
    , { FREEZER_SLOT_NUM, Id( FREEZER_SLOT_NUM, "freezer_slot_num" ) }
    #endif // USE_EXTRA_EQUIPMENT
    , { GRAPPLE_SLOT_NUM, Id( GRAPPLE_SLOT_NUM, "grapple_slot_num" ) }
    , { PROTECTOR_SLOT_NUM, Id( PROTECTOR_SLOT_NUM, "protector_slot_num" ) }
    , { RADAR_SLOT_NUM, Id( RADAR_SLOT_NUM, "radar_slot_num" ) }
    , { SCANER_SLOT_NUM, Id( SCANER_SLOT_NUM, "scaner_slot_num" ) }
    , { WEAPON_SLOT_NUM, Id( WEAPON_SLOT_NUM, "weapon_slot_num" ) }
    , { ARTEFACT_SLOT_NUM, Id( ARTEFACT_SLOT_NUM, "artefact_slot_num" ) }
    , { CARGO_SLOT_NUM, Id( CARGO_SLOT_NUM, "cargo_slot_num" ) }
    // dynamic
    , { ID, Id( ID, "id" ) }
    , { OBJ_ID, Id( OBJ_ID, "obj_id" ) }
    , { OWNER, Id( OWNER, "owner" ) }
    , { CHILD, Id( CHILD, "child" ) }
    , { TARGET, Id( TARGET, "target" ) }
    , { IDLIST, Id( IDLIST, "id_list" ) }

};


} // namespace descriptor
