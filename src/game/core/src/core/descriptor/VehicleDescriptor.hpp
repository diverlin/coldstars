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

#include <core/descriptor/SpaceobjectDescriptor.hpp>

#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>

namespace descriptor {

class Vehicle : public SpaceObject
{

public:
    Vehicle() = default;
    Vehicle(const std::string& data) {
        MACRO_READ_SERIALIZED_DATA
    }
    virtual ~Vehicle() = default;

    int_t race() const { return m_race; }

    int space() const { return m_space; }
    int protection() const { return m_protection; }
#ifdef USE_EXTRA_EQUIPMENT
    int temperature() const { return m_temperature; }
#endif // USE_EXTRA_EQUIPMENT
    int price() const { return m_price; }

    bool drawTurrels() const { return m_drawTurrels; }

    int bakSlotNum() const { return m_bakSlotNum; }
    int driveSlotNum() const { return m_driveSlotNum; }
    int droidSlotNum() const { return m_droidSlotNum; }
#ifdef USE_EXTRA_EQUIPMENT
    int energizerSlotNum() const { return m_energizerSlotNum; }
    int freezerSlotNum() const { return m_freezerSlotNum; }
#endif // USE_EXTRA_EQUIPMENT
    int grappleSlotNum() const { return m_grappleSlotNum; }
    int protectorSlotNum() const { return m_protectorSlotNum; }
    int radarSlotNum() const { return m_radarSlotNum; }
    int scanerSlotNum() const { return m_scanerSlotNum; }
    int weaponSlotNum() const { return m_weaponSlotNum; }
    int artefactSlotNum() const { return m_artefactSlotNum; }
    int cargoSlotNum() const { return m_cargoSlotNum; }


    void setRace(int_t race) { m_race = race; }

    void setSpace(int space) { m_space = space; }
    void setProtection(int protection) { m_protection = protection; }
#ifdef USE_EXTRA_EQUIPMENT
    void setTemperature(int temperature) { m_temperature = temperature; }
#endif // USE_EXTRA_EQUIPMENT
    void setPrice(int price) { m_price = price; }
    void setDrawTurrels(bool drawTurrels) { m_drawTurrels = drawTurrels; }

    void setBakSlotNum(int bakSlotNum) { m_bakSlotNum = bakSlotNum; }
    void setDriveSlotNum(int driveSlotNum) { m_driveSlotNum = driveSlotNum; }
    void setDroidSlotNum(int droidSlotNum) { m_droidSlotNum = droidSlotNum; }
#ifdef USE_EXTRA_EQUIPMENT
    void setEnergizerSlotNum(int energizerSlotNum) { m_energizerSlotNum = energizerSlotNum; }
    void setFreezerSlotNum(int freezerSlotNum) { m_freezerSlotNum = freezerSlotNum; }
#endif // USE_EXTRA_EQUIPMENT
    void setGrappleSlotNum(int grappleSlotNum) { m_grappleSlotNum = grappleSlotNum; }
    void setProtectorSlotNum(int protectorSlotNum) { m_protectorSlotNum = protectorSlotNum; }
    void setRadarSlotNum(int radarSlotNum) { m_radarSlotNum = radarSlotNum; }
    void setScanerSlotNum(int scanerSlotNum) { m_scanerSlotNum = scanerSlotNum; }
    void setWeaponSlotNum(int weaponSlotNum) { m_weaponSlotNum = weaponSlotNum; }
    void setArtefactSlotNum(int artefactSlotNum) { m_artefactSlotNum = artefactSlotNum; }
    void setCargoSlotNum(int otsecSlotNum) { m_cargoSlotNum = otsecSlotNum; }

    std::string info() const {
        std::string result = "Vehicle descriptor:\n";
        result += std::string(" race = ") + meti::to_string(m_race) + "\n";

        result += std::string(" space = ") + meti::to_string(m_space) + "\n";
        result += std::string(" protection = ") + meti::to_string(m_protection) + "\n";
#ifdef USE_EXTRA_EQUIPMENT
        result += std::string(" temperature = ") + meti::to_string(m_temperature) + "\n";
#endif // USE_EXTRA_EQUIPMENT
        result += std::string(" price = ") + meti::to_string(m_price) + "\n";

        result += std::string(" drawTurrel = ") + meti::to_string(m_drawTurrels) + "\n";
        result += std::string(" bakSlotNum = ") + meti::to_string(m_bakSlotNum) + "\n";
        result += std::string(" driveSlotNum = ") + meti::to_string(m_driveSlotNum) + "\n";
        result += std::string(" droidSlotNum = ") + meti::to_string(m_droidSlotNum) + "\n";
#ifdef USE_EXTRA_EQUIPMENT
        result += std::string(" energizerSlotNum = ") + meti::to_string(m_energizerSlotNum) + "\n";
        result += std::string(" freezerSlotNum = ") + meti::to_string(m_freezerSlotNum) + "\n";
#endif // USE_EXTRA_EQUIPMENT
        result += std::string(" grappleSlotNum = ") + meti::to_string(m_grappleSlotNum) + "\n";
        result += std::string(" protectorSlotNum = ") + meti::to_string(m_protectorSlotNum) + "\n";
        result += std::string(" radarSlotNum = ") + meti::to_string(m_radarSlotNum) + "\n";
        result += std::string(" scanerSlotNum = ") + meti::to_string(m_scanerSlotNum) + "\n";
        result += std::string(" weaponSlotNum = ") + meti::to_string(m_weaponSlotNum) + "\n";
        result += std::string(" artefactSlotNum = ") + meti::to_string(m_artefactSlotNum) + "\n";
        result += std::string(" cargoSlotNum = ") + meti::to_string(m_cargoSlotNum) + "\n";

        result += SpaceObject::info();
        return result;
    }

private:
    int_t m_race = 0;

    int m_space = 0;
    int m_protection = 0;
#ifdef USE_EXTRA_EQUIPMENT
    int m_temperature = 0;
#endif // USE_EXTRA_EQUIPMENT
    int m_price = 0;

    bool m_drawTurrels = false;

    int m_bakSlotNum = 0;
    int m_driveSlotNum = 0;
    int m_droidSlotNum = 0;
#ifdef USE_EXTRA_EQUIPMENT
    int m_energizerSlotNum = 0;
    int m_freezerSlotNum = 0;
#endif // USE_EXTRA_EQUIPMENT
    int m_grappleSlotNum = 0;
    int m_protectorSlotNum = 0;
    int m_radarSlotNum = 0;
    int m_scanerSlotNum = 0;
    int m_weaponSlotNum = 0;
    int m_artefactSlotNum = 0;
    int m_cargoSlotNum = 0;

private:
    friend class boost::serialization::access;
    template<class Archive>
    void serialize(Archive & ar, const unsigned int version) {
        ar & boost::serialization::base_object<SpaceObject>(*this);
        ar & m_race;

        ar & m_space;
        ar & m_protection;
#ifdef USE_EXTRA_EQUIPMENT
        ar & m_temperature;
#endif // USE_EXTRA_EQUIPMENT
        ar & m_price;

        ar & m_drawTurrels;

        ar & m_bakSlotNum;
        ar & m_driveSlotNum;
        ar & m_droidSlotNum;
#ifdef USE_EXTRA_EQUIPMENT
        ar & m_energizerSlotNum;
        ar & m_freezerSlotNum;
#endif // USE_EXTRA_EQUIPMENT
        ar & m_grappleSlotNum;
        ar & m_protectorSlotNum;
        ar & m_radarSlotNum;
        ar & m_scanerSlotNum;
        ar & m_weaponSlotNum;
        ar & m_artefactSlotNum;
        ar & m_cargoSlotNum;
    }

};

class Ship : public Vehicle {

};

class SpaceStation : public Vehicle {

};

class Satellite : public Vehicle {

};

} // namespace descriptor