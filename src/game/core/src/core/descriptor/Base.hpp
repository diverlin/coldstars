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
#include <ceti/IdGenerator.hpp>
#include <ceti/descriptor/Id.hpp>
#include <ceti/descriptor/Base.hpp>

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
    OBJ,
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
    OBJ,
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

//class BBase
//{
//public:
//    BBase() {
//        m_id = m_idGenerator.nextId();
//    }
//    ~BBase() {}

//    int_t id() const { return m_id; }
//    int_t texture() const { return m_texture; }
//    int_t mesh() const { return m_mesh; }

//    void setTexture(int_t texture) { m_texture = texture; }
//    void setMesh(int_t mesh) { m_mesh = mesh; }
//    virtual std::string info() const {
//        std::string result;
//        result += std::string(" id=") + std::to_string(m_id);
//        result += std::string(" material=") + std::to_string(m_texture);
//        result += std::string(" geometry=") + std::to_string(m_mesh);
//        return result;
//    }

//protected:
//    std::string _str(const std::string& label, const std::vector<int_t>& ids) const {
//        std::string result = label;
//        for (int_t id: ids) {
//            result += std::to_string(id) + ",";
//        }
//        return result;
//    }

//private:
//    friend class boost::serialization::access;
//    template<class Archive>
//    void serialize(Archive & ar, const unsigned int version) {
//        ar & m_id;
//        ar & m_texture;
//        ar & m_mesh;
//    }

//private:
//    int_t m_id = -1;
//    int_t m_texture = -1;
//    int_t m_mesh = -1;

//    static IdGenerator m_idGenerator;
//};

class BaseOLD
{
public:
    BaseOLD(const Type&, bool generate_id = true);
    BaseOLD(const std::string& data);
    ~BaseOLD();

    std::string data() const;

    bool operator==(const BaseOLD& rhs) const;

    int_t texture() const;
    int_t mesh() const;

    int_t id() const;
    int_t objId() const;
    int_t type() const;
    int_t objType() const;
    int_t descriptor() const;
    int_t race() const;
    int_t damage() const;
    int_t radius() const;
    int_t tech() const;
    int_t modulesNum() const;
    int_t mass() const;
    int_t conditionMax() const;
    int_t deterioration() const;
    int_t fuelMax() const;
    int_t speed() const;
    int_t hyper() const;
    int_t repair() const;
    int_t strength() const;
    int_t scan() const;
    int_t protection() const;
    int_t price() const;

    //vehicle
    int_t space() const;
    int_t armor() const;
    int_t temperature() const;
    int_t drawTurrels() const;
    int_t size() const;
    int_t bakSlotNum() const;
    int_t driveSlotNum() const;
    int_t droidSlotNum() const;
#ifdef USE_EXTRA_EQUIPMENT
    const id_type& energizerSlotNum() const;
    const id_type& freezerSlotNum() const;
#endif
    int_t grappleSlotNum() const;
    int_t protectorSlotNum() const;
    int_t radarSlotNum() const;
    int_t scanerSlotNum() const;
    int_t weaponSlotNum() const;
    int_t artefactSlotNum() const;
    int_t cargoSlotNum() const;

    // dynamic
    int_t owner() const;
    int_t child() const;
    int_t target() const;

public: // todo make it protected
    void add(const Key& key, int_t value);

private:
    int_t __getOrDie(const Key& key) const;
    int_t __get(const Key& key) const;

    friend class boost::serialization::access;
    template<class Archive>
    void serialize(Archive & ar, const unsigned int version)
    {
        ar & m_map;
    }

    std::map<Key, int_t> m_map;
    static IdGenerator m_idGenerator;
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
//const Id objIdId( OBJ, "obj_id" );
//const Id ownerId( OWNER, "owner" );
//const Id childId( CHILD, "child" );
//const Id targetId( TARGET, "target" );

using namespace ceti::descriptor;

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
    , { OBJ, Id( OBJ, "obj_id" ) }
    , { OWNER, Id( OWNER, "owner" ) }
    , { CHILD, Id( CHILD, "child" ) }
    , { TARGET, Id( TARGET, "target" ) }
    , { IDLIST, Id( IDLIST, "id_list" ) }

};


} // namespace descriptor
