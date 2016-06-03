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

// const
std::string Base::KEY_STR_TYPE = "type";
std::string Base::KEY_STR_RACE = "race";
std::string Base::KEY_STR_DAMAGE = "damage";
std::string Base::KEY_STR_RADIUS = "radius";
std::string Base::KEY_STR_TECH = "tech";
std::string Base::KEY_STR_MODULES_NUM = "modules_num";
std::string Base::KEY_STR_MASS = "mass";
std::string Base::KEY_STR_CONDITION_MAX = "condition_max";
std::string Base::KEY_STR_DETERIORATION = "deterioration";
std::string Base::KEY_STR_FUEL_MAX = "fuel_max";
std::string Base::KEY_STR_SPEED = "speed";
std::string Base::KEY_STR_HYPER = "hyper";
std::string Base::KEY_STR_REPAIR = "repair";
std::string Base::KEY_STR_STRENGTH = "strength";
std::string Base::KEY_STR_SCAN = "scan";
std::string Base::KEY_STR_PROTECTION = "protection";
std::string Base::KEY_STR_PRICE = "price";
//vehicle
std::string Base::KEY_STR_SPACE = "space";
std::string Base::KEY_STR_ARMOR = "armor";
std::string Base::KEY_STR_TEMPERATURE = "temperature";
std::string Base::KEY_STR_DRAW_TURRELS = "draw_turrels";
std::string Base::KEY_STR_BAK_SLOT_NUM = "bak_slot_num";
std::string Base::KEY_STR_DRIVE_SLOT_NUM = "drive_slot_num";
std::string Base::KEY_STR_DROID_SLOT_NUM = "droid_slot_num";
#ifdef USE_EXTRA_EQUIPMENT
std::string Base::KEY_STR_ENERGIZER_SLOT_NUM = "energizer_slot_num";
std::string Base::KEY_STR_FREEZER_SLOT_NUM = "freezer_slot_num";
#endif // USE_EXTRA_EQUIPMENT
std::string Base::KEY_STR_GRAPPLE_SLOT_NUM = "grapple_slot_num";
std::string Base::KEY_STR_PROTECTOR_SLOT_NUM = "protector_slot_num";
std::string Base::KEY_STR_RADAR_SLOT_NUM = "radar_slot_num";
std::string Base::KEY_STR_SCANER_SLOT_NUM = "scaner_slot_num";
std::string Base::KEY_STR_WEAPON_SLOT_NUM = "weapon_slot_num";
std::string Base::KEY_STR_ARTEFACT_SLOT_NUM = "artefact_slot_num";
std::string Base::KEY_STR_CARGO_SLOT_NUM = "cargo_slot_num";

// dynamic
std::string Base::KEY_STR_ID = "id";
std::string Base::KEY_STR_OWNER = "owner";
std::string Base::KEY_STR_CHILD = "child";
std::string Base::KEY_STR_TARGET = "target";

std::string keyStr(const Key& key) {
    switch(key) {
    // const
    case Key::TYPE: return Base::KEY_STR_TYPE; break;
    case Key::RACE: return Base::KEY_STR_RACE; break;
    case Key::DAMAGE: return Base::KEY_STR_DAMAGE; break;
    case Key::RADIUS: return Base::KEY_STR_RADIUS; break;
    case Key::TECH: return Base::KEY_STR_TECH; break;
    case Key::MODULES_NUM: return Base::KEY_STR_MODULES_NUM; break;
    case Key::MASS: return Base::KEY_STR_MASS; break;
    case Key::CONDITION_MAX: return Base::KEY_STR_CONDITION_MAX; break;
    case Key::DETERIORATION: return Base::KEY_STR_DETERIORATION; break;
    case Key::FUEL_MAX: return Base::KEY_STR_FUEL_MAX; break;
    case Key::SPEED: return Base::KEY_STR_SPEED; break;
    case Key::HYPER: return Base::KEY_STR_HYPER; break;
    case Key::REPAIR: return Base::KEY_STR_REPAIR; break;
    case Key::STRENGTH: return Base::KEY_STR_STRENGTH; break;
    case Key::SCAN: return Base::KEY_STR_SCAN; break;
    case Key::PROTECTION: return Base::KEY_STR_PROTECTION; break;
    case Key::PRICE: return Base::KEY_STR_PRICE; break;
    // vehicle
    case Key::SPACE: return Base::KEY_STR_SPACE; break;
    case Key::ARMOR: return Base::KEY_STR_ARMOR; break;
    case Key::TEMPERATURE: return Base::KEY_STR_TEMPERATURE; break;
    case Key::DRAW_TURRELS: return Base::KEY_STR_DRAW_TURRELS; break;
    case Key::BAK_SLOT_NUM: return Base::KEY_STR_BAK_SLOT_NUM; break;
    case Key::DRIVE_SLOT_NUM: return Base::KEY_STR_DRIVE_SLOT_NUM; break;
    case Key::DROID_SLOT_NUM: return Base::KEY_STR_DROID_SLOT_NUM; break;
        #ifdef USE_EXTRA_EQUIPMENT
    case Key::ENERGIZER_SLOT_NUM: return Base::KEY_STR_ENERGIZER_SLOT_NUM; break;
    case Key::FREEZER_SLOT_NUM: return Base::KEY_STR_FREEZER_SLOT_NUM; break;
        #endif // USE_EXTRA_EQUIPMENT
    case Key::GRAPPLE_SLOT_NUM: return Base::KEY_STR_GRAPPLE_SLOT_NUM; break;
    case Key::PROTECTOR_SLOT_NUM: return Base::KEY_STR_PROTECTOR_SLOT_NUM; break;
    case Key::RADAR_SLOT_NUM: return Base::KEY_STR_RADAR_SLOT_NUM; break;
    case Key::SCANER_SLOT_NUM: return Base::KEY_STR_SCANER_SLOT_NUM; break;
    case Key::WEAPON_SLOT_NUM: return Base::KEY_STR_WEAPON_SLOT_NUM; break;
    case Key::ARTEFACT_SLOT_NUM: return Base::KEY_STR_ARTEFACT_SLOT_NUM; break;
    case Key::CARGO_SLOT_NUM: return Base::KEY_STR_CARGO_SLOT_NUM; break;
    // dynamic
    case Key::ID: return Base::KEY_STR_ID; break;
    case Key::OWNER: return Base::KEY_STR_OWNER; break;
    case Key::CHILD: return Base::KEY_STR_CHILD; break;
    case Key::TARGET: return Base::KEY_STR_TARGET; break;

    default: throw std::runtime_error("ERROR: fixme: unknown descriptor key"); break;
    }
}

std::string typeStr(const Type& type) {
    switch(type) {
    case Type::HIT: return "Type::HIT"; break;
    case Type::CONTAINER: return "Type::CONTAINER"; break;
    case Type::BOMB: return "Type::BOMB"; break;
    case Type::STARSYSTEM: return "Type::STARSYSTEM"; break;
    case Type::BAK: return "Type::BAK"; break;
    case Type::DRIVE: return "Type::DRIVE"; break;
    case Type::DROID: return "Type::DROID"; break;
    case Type::GRAPPLE: return "Type::GRAPPLE"; break;
    case Type::SCANER: return "Type::SCANER"; break;
    case Type::RADAR: return "Type::RADAR"; break;
    case Type::PROTECTOR: return "Type::PROTECTOR"; break;
    default: throw std::runtime_error("ERROR: fixme: unknown descriptor key"); break;
    }
}

Base::Base()
{
}

Base::Base(const std::map<Key, int_type>& map)
    : m_map(map)
{
}

Base::Base(const std::string& data)
{
    std::stringstream ss;
    ss << data;
    boost::archive::text_iarchive ia(ss);
    ia >> *this;
}

Base::~Base()
{
}

std::string
Base::data() const
{
    std::stringstream ss;
    boost::archive::text_oarchive oa(ss);
    oa << *this;
    return ss.str();
}

void
Base::add(const Key& key, const int_type& value)
{
    auto f = m_map.find(key);
    if (f == m_map.end()) {
        m_map.insert(std::make_pair(key, value));
    } else {
        throw std::runtime_error("CODE ERROR: " + keyStr(key) + " is already existed in descriptor");
    }
}

const int_type& Base::id() const { return get(Key::ID); }
const int_type& Base::type() const { return get(Key::TYPE); }
const int_type& Base::race() const { return get(Key::RACE); }
const int_type& Base::owner() const { return get(Key::OWNER); }
const int_type& Base::child() const { return get(Key::CHILD); }
const int_type& Base::target() const { return get(Key::TARGET); }
const int_type& Base::damage() const { return get(Key::DAMAGE); }
const int_type& Base::radius() const { return get(Key::RADIUS); }
const int_type& Base::tech() const { return get(Key::TECH); }
const int_type& Base::modulesNum() const { return get(Key::MODULES_NUM); }
const int_type& Base::mass() const { return get(Key::MASS); }
const int_type& Base::conditionMax() const { return get(Key::CONDITION_MAX); }
const int_type& Base::deterioration() const { return get(Key::DETERIORATION); }
const int_type& Base::fuelMax() const { return get(Key::FUEL_MAX); }
const int_type& Base::speed() const { return get(Key::SPEED); }
const int_type& Base::hyper() const { return get(Key::HYPER); }
const int_type& Base::repair() const { return get(Key::REPAIR); }
const int_type& Base::strength() const { return get(Key::STRENGTH); }
const int_type& Base::scan() const { return get(Key::SCAN); }
const int_type& Base::protection() const { return get(Key::PROTECTION); }
const int_type& Base::price() const { return get(Key::PRICE); }
//vehicle
const int_type& Base::space() const { return get(Key::SPACE); }
const int_type& Base::armor() const { return get(Key::ARMOR); }
const int_type& Base::temperature() const { return get(Key::TEMPERATURE); }
const int_type& Base::drawTurrels() const { return get(Key::DRAW_TURRELS); }
const int_type& Base::bakSlotNum() const { return get(Key::BAK_SLOT_NUM); }
const int_type& Base::driveSlotNum() const { return get(Key::DRIVE_SLOT_NUM); }
const int_type& Base::droidSlotNum() const { return get(Key::DROID_SLOT_NUM); }
#ifdef USE_EXTRA_EQUIPMENT
const int_type& Base::energizerSlotNum() const { return get(Key::ENERGIZER_SLOT_NUM); }
const int_type& Base::freezerSlotNum() const { return get(Key::FREEZER_SLOT_NUM); }
#endif // USE_EXTRA_EQUIPMENT
const int_type& Base::grappleSlotNum() const { return get(Key::GRAPPLE_SLOT_NUM); }
const int_type& Base::protectorSlotNum() const { return get(Key::PROTECTOR_SLOT_NUM); }
const int_type& Base::radarSlotNum() const { return get(Key::RADAR_SLOT_NUM); }
const int_type& Base::scanerSlotNum() const { return get(Key::SCANER_SLOT_NUM); }
const int_type& Base::weaponSlotNum() const { return get(Key::WEAPON_SLOT_NUM); }
const int_type& Base::artefactSlotNum() const { return get(Key::ARTEFACT_SLOT_NUM); }
const int_type& Base::cargoSlotNum() const { return get(Key::CARGO_SLOT_NUM); }


bool
Base::operator==(const Base& rhs) const
{
    return data() == rhs.data();
}

const int_type&
Base::get(const Key& key) const
{
    auto f = m_map.find(key);
    if (f != m_map.end()) {
        return f->second;
    }
    throw std::runtime_error("CODE ERROR: " + keyStr(key) + " is not found in descriptor");
}

} // namespace descriptor

