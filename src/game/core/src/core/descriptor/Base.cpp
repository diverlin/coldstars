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

#include "Base.hpp"

#include <sstream>

namespace descriptor {

//IdGenerator BBase::m_idGenerator;

IdGenerator BaseOLD::m_idGenerator;

namespace {
const std::string KEY_STR_ID = "id";
const std::string KEY_STR_OBJ_ID = "obj_id";
const std::string KEY_STR_TYPE = "type";
const std::string KEY_STR_OBJ_TYPE = "obj_type";
const std::string KEY_STR_DESCRIPTOR = "descr";
const std::string KEY_STR_RACE = "race";
const std::string KEY_STR_DAMAGE = "damage";
const std::string KEY_STR_RADIUS = "radius";
const std::string KEY_STR_TECH = "tech";
const std::string KEY_STR_MODULES_NUM = "modules_num";
const std::string KEY_STR_MASS = "mass";
const std::string KEY_STR_CONDITION_MAX = "condition_max";
const std::string KEY_STR_DETERIORATION = "deterioration";
const std::string KEY_STR_FUEL_MAX = "fuel_max";
const std::string KEY_STR_SPEED = "speed";
const std::string KEY_STR_HYPER = "hyper";
const std::string KEY_STR_REPAIR = "repair";
const std::string KEY_STR_STRENGTH = "strength";
const std::string KEY_STR_SCAN = "scan";
const std::string KEY_STR_PROTECTION = "protection";
const std::string KEY_STR_PRICE = "price";
//vehicle
const std::string KEY_STR_SPACE = "space";
const std::string KEY_STR_ARMOR = "armor";
const std::string KEY_STR_TEMPERATURE = "temperature";
const std::string KEY_STR_DRAW_TURRELS = "draw_turrels";
const std::string KEY_STR_SIZE = "size";
const std::string KEY_STR_BAK_SLOT_NUM = "bak_slot_num";
const std::string KEY_STR_DRIVE_SLOT_NUM = "drive_slot_num";
const std::string KEY_STR_DROID_SLOT_NUM = "droid_slot_num";
#ifdef USE_EXTRA_EQUIPMENT
const std::string KEY_STR_ENERGIZER_SLOT_NUM = "energizer_slot_num";
const std::string KEY_STR_FREEZER_SLOT_NUM = "freezer_slot_num";
#endif // USE_EXTRA_EQUIPMENT
const std::string KEY_STR_GRAPPLE_SLOT_NUM = "grapple_slot_num";
const std::string KEY_STR_PROTECTOR_SLOT_NUM = "protector_slot_num";
const std::string KEY_STR_RADAR_SLOT_NUM = "radar_slot_num";
const std::string KEY_STR_SCANER_SLOT_NUM = "scaner_slot_num";
const std::string KEY_STR_WEAPON_SLOT_NUM = "weapon_slot_num";
const std::string KEY_STR_ARTEFACT_SLOT_NUM = "artefact_slot_num";
const std::string KEY_STR_CARGO_SLOT_NUM = "cargo_slot_num";

// dynamic
const std::string KEY_STR_OWNER = "owner";
const std::string KEY_STR_CHILD = "child";
const std::string KEY_STR_TARGET = "target";
} // namespace

std::string keyStr(const Key& key) {
    switch(key) {
    // const
    case Key::ID: return KEY_STR_ID; break;
    case Key::OBJ_ID: return KEY_STR_OBJ_ID; break;
    case Key::TYPE: return KEY_STR_TYPE; break;
    case Key::OBJ_TYPE: return KEY_STR_OBJ_TYPE; break;
    case Key::DESCRIPTOR: return KEY_STR_DESCRIPTOR; break;
    case Key::RACE: return KEY_STR_RACE; break;
    case Key::DAMAGE: return KEY_STR_DAMAGE; break;
    case Key::RADIUS: return KEY_STR_RADIUS; break;
    case Key::TECH: return KEY_STR_TECH; break;
    case Key::MODULES_NUM: return KEY_STR_MODULES_NUM; break;
    case Key::MASS: return KEY_STR_MASS; break;
    case Key::CONDITION_MAX: return KEY_STR_CONDITION_MAX; break;
    case Key::DETERIORATION: return KEY_STR_DETERIORATION; break;
    case Key::FUEL_MAX: return KEY_STR_FUEL_MAX; break;
    case Key::SPEED: return KEY_STR_SPEED; break;
    case Key::HYPER: return KEY_STR_HYPER; break;
    case Key::REPAIR: return KEY_STR_REPAIR; break;
    case Key::STRENGTH: return KEY_STR_STRENGTH; break;
    case Key::SCAN: return KEY_STR_SCAN; break;
    case Key::PROTECTION: return KEY_STR_PROTECTION; break;
    case Key::PRICE: return KEY_STR_PRICE; break;
    // vehicle
    case Key::SPACE: return KEY_STR_SPACE; break;
    case Key::ARMOR: return KEY_STR_ARMOR; break;
    case Key::TEMPERATURE: return KEY_STR_TEMPERATURE; break;
    case Key::DRAW_TURRELS: return KEY_STR_DRAW_TURRELS; break;
    case Key::SIZE: return KEY_STR_SIZE; break;
    case Key::BAK_SLOT_NUM: return KEY_STR_BAK_SLOT_NUM; break;
    case Key::DRIVE_SLOT_NUM: return KEY_STR_DRIVE_SLOT_NUM; break;
    case Key::DROID_SLOT_NUM: return KEY_STR_DROID_SLOT_NUM; break;
        #ifdef USE_EXTRA_EQUIPMENT
    case Key::ENERGIZER_SLOT_NUM: return KEY_STR_ENERGIZER_SLOT_NUM; break;
    case Key::FREEZER_SLOT_NUM: return KEY_STR_FREEZER_SLOT_NUM; break;
        #endif // USE_EXTRA_EQUIPMENT
    case Key::GRAPPLE_SLOT_NUM: return KEY_STR_GRAPPLE_SLOT_NUM; break;
    case Key::PROTECTOR_SLOT_NUM: return KEY_STR_PROTECTOR_SLOT_NUM; break;
    case Key::RADAR_SLOT_NUM: return KEY_STR_RADAR_SLOT_NUM; break;
    case Key::SCANER_SLOT_NUM: return KEY_STR_SCANER_SLOT_NUM; break;
    case Key::WEAPON_SLOT_NUM: return KEY_STR_WEAPON_SLOT_NUM; break;
    case Key::ARTEFACT_SLOT_NUM: return KEY_STR_ARTEFACT_SLOT_NUM; break;
    case Key::CARGO_SLOT_NUM: return KEY_STR_CARGO_SLOT_NUM; break;
    // dynamic
    case Key::OWNER: return KEY_STR_OWNER; break;
    case Key::CHILD: return KEY_STR_CHILD; break;
    case Key::TARGET: return KEY_STR_TARGET; break;

    default: throw std::runtime_error("ERROR: fixme: unknown descriptor key"); break;
    }
}

std::string typeStr(const Type& type) {
    switch(type) {
    case Type::DESCRIPTOR: return "Type::DESCRIPTOR"; break;
    case Type::HIT: return "Type::HIT"; break;
    case Type::CONTAINER: return "Type::CONTAINER"; break;
    case Type::BOMB: return "Type::BOMB"; break;
    case Type::STARSYSTEM: return "Type::STARSYSTEM"; break;
    case Type::STAR: return "Type::STAR"; break;
    case Type::PLANET: return "Type::PLANET"; break;
    case Type::ASTEROID: return "Type::ASTEROID"; break;
    case Type::BAK: return "Type::BAK"; break;
    case Type::DRIVE: return "Type::DRIVE"; break;
    case Type::DROID: return "Type::DROID"; break;
    case Type::GRAPPLE: return "Type::GRAPPLE"; break;
    case Type::SCANER: return "Type::SCANER"; break;
    case Type::RADAR: return "Type::RADAR"; break;
    case Type::PROTECTOR: return "Type::PROTECTOR"; break;
    case Type::VEHICLE: return "Type::VEHICLE"; break;
//    case Type::SHIP: return "Type::VEHICLE"; break;
//    case Type::SATELLITE: return "Type::SATELLITE"; break;
//    case Type::STARBASE: return "Type::STARBASE"; break;
    default: throw std::runtime_error("ERROR: fixme: unknown descriptor key"); break;
    }
}

BaseOLD::BaseOLD(const Type& type, bool generate_id)
{
    if (generate_id) {
        add(Key::ID, m_idGenerator.nextId());
    }
    add(Key::TYPE, (int)type);
}

BaseOLD::BaseOLD(const std::string& data)
{
    MACRO_READ_SERIALIZED_DATA
}

BaseOLD::~BaseOLD()
{
}

std::string
BaseOLD::data() const
{
    MACRO_SAVE_SERIALIZED_DATA
}

void
BaseOLD::add(const Key& key, int_t value)
{
    auto f = m_map.find(key);
    if (f == m_map.end()) {
        m_map.insert(std::make_pair(key, value));
    } else {
        throw std::runtime_error("CODE ERROR: attempt to add already existed key[" + keyStr(key) + "] to descriptor");
    }
}

int_t BaseOLD::id() const { return __getOrDie(Key::ID); }
int_t BaseOLD::objId() const { return __get(Key::OBJ_ID); }
int_t BaseOLD::type() const { return __getOrDie(Key::TYPE); }
int_t BaseOLD::objType() const { return __getOrDie(Key::OBJ_TYPE); }
int_t BaseOLD::descriptor() const { return __getOrDie(Key::DESCRIPTOR); }
int_t BaseOLD::race() const { return __getOrDie(Key::RACE); }
int_t BaseOLD::damage() const { return __getOrDie(Key::DAMAGE); }
int_t BaseOLD::radius() const { return __getOrDie(Key::RADIUS); }
int_t BaseOLD::tech() const { return __getOrDie(Key::TECH); }
int_t BaseOLD::modulesNum() const { return __getOrDie(Key::MODULES_NUM); }
int_t BaseOLD::mass() const { return __getOrDie(Key::MASS); }
int_t BaseOLD::conditionMax() const { return __getOrDie(Key::CONDITION_MAX); }
int_t BaseOLD::deterioration() const { return __getOrDie(Key::DETERIORATION); }
int_t BaseOLD::fuelMax() const { return __getOrDie(Key::FUEL_MAX); }
int_t BaseOLD::speed() const { return __getOrDie(Key::SPEED); }
int_t BaseOLD::hyper() const { return __getOrDie(Key::HYPER); }
int_t BaseOLD::repair() const { return __getOrDie(Key::REPAIR); }
int_t BaseOLD::strength() const { return __getOrDie(Key::STRENGTH); }
int_t BaseOLD::scan() const { return __getOrDie(Key::SCAN); }
int_t BaseOLD::protection() const { return __getOrDie(Key::PROTECTION); }
int_t BaseOLD::price() const { return __getOrDie(Key::PRICE); }
//vehicle
int_t BaseOLD::space() const { return __getOrDie(Key::SPACE); }
int_t BaseOLD::armor() const { return __getOrDie(Key::ARMOR); }
int_t BaseOLD::temperature() const { return __getOrDie(Key::TEMPERATURE); }
int_t BaseOLD::drawTurrels() const { return __getOrDie(Key::DRAW_TURRELS); }
int_t BaseOLD::size() const { return __getOrDie(Key::SIZE); }
int_t BaseOLD::bakSlotNum() const { return __getOrDie(Key::BAK_SLOT_NUM); }
int_t BaseOLD::driveSlotNum() const { return __getOrDie(Key::DRIVE_SLOT_NUM); }
int_t BaseOLD::droidSlotNum() const { return __getOrDie(Key::DROID_SLOT_NUM); }
#ifdef USE_EXTRA_EQUIPMENT
const id_type& Base::energizerSlotNum() const { return get(Key::ENERGIZER_SLOT_NUM); }
const id_type& Base::freezerSlotNum() const { return get(Key::FREEZER_SLOT_NUM); }
#endif // USE_EXTRA_EQUIPMENT
int_t BaseOLD::grappleSlotNum() const { return __getOrDie(Key::GRAPPLE_SLOT_NUM); }
int_t BaseOLD::protectorSlotNum() const { return __getOrDie(Key::PROTECTOR_SLOT_NUM); }
int_t BaseOLD::radarSlotNum() const { return __getOrDie(Key::RADAR_SLOT_NUM); }
int_t BaseOLD::scanerSlotNum() const { return __getOrDie(Key::SCANER_SLOT_NUM); }
int_t BaseOLD::weaponSlotNum() const { return __getOrDie(Key::WEAPON_SLOT_NUM); }
int_t BaseOLD::artefactSlotNum() const { return __getOrDie(Key::ARTEFACT_SLOT_NUM); }
int_t BaseOLD::cargoSlotNum() const { return __getOrDie(Key::CARGO_SLOT_NUM); }

// dynamic
int_t BaseOLD::owner() const { return __getOrDie(Key::OWNER); }
int_t BaseOLD::child() const { return __getOrDie(Key::CHILD); }
int_t BaseOLD::target() const { return __getOrDie(Key::TARGET); }

bool
BaseOLD::operator==(const BaseOLD& rhs) const
{
    return data() == rhs.data();
}

int_t
BaseOLD::__getOrDie(const Key& key) const
{
    auto f = m_map.find(key);
    if (f != m_map.end()) {
        return f->second;
    }
    throw std::runtime_error("CODE ERROR: key=[" + keyStr(key) + "] is not found in descriptor");
}

int_t
BaseOLD::__get(const Key& key) const
{
    auto f = m_map.find(key);
    if (f != m_map.end()) {
        return f->second;
    }

    return -1;
}

} // namespace descriptor

