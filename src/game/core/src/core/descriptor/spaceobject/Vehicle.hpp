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

#include <core/descriptor/spaceobject/SpaceObject.hpp>

#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <boost/serialization/vector.hpp>

namespace core {

class VehicleDescr : public SpaceObjectDescr
{

public:
    VehicleDescr() = default;
    virtual ~VehicleDescr() = default;

    const std::vector<meti::vec3>& turrelPoints() const { return m_turrelPoints; }
    const std::vector<meti::vec3>& drivePoints() const { return m_drivePoints; }
    const std::vector<meti::vec3>& protectorPoints() const { return m_protectorPoints; }

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

    void addTurrelPoint(const meti::vec3& p) { m_turrelPoints.push_back(p); }
    void addDrivePoint(const meti::vec3& p) { m_drivePoints.push_back(p); }
    void addProtectorPoint(const meti::vec3& p) { m_protectorPoints.push_back(p); }

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

    ceti::InfoTable info() const override {
        ceti::InfoTable result = SpaceObjectDescr::info();
        result.add("Vehicle");
        result.add("space", m_space);
        result.add("protection", m_protection);
#ifdef USE_EXTRA_EQUIPMENT
        result.add("temperature", m_temperature);
#endif // USE_EXTRA_EQUIPMENT
        result.add("price", m_price);

        result.add("drawTurrel", m_drawTurrels);
        result.add("bakSlotNum", m_bakSlotNum);
        result.add("driveSlotNum", m_driveSlotNum);
        result.add("droidSlotNum", m_droidSlotNum);
#ifdef USE_EXTRA_EQUIPMENT
        result.add("energizerSlotNum", m_energizerSlotNum);
        result.add("freezerSlotNum", m_freezerSlotNum);
#endif // USE_EXTRA_EQUIPMENT
        result.add("grappleSlotNum", m_grappleSlotNum);
        result.add("protectorSlotNum", m_protectorSlotNum);
        result.add("radarSlotNum", m_radarSlotNum);
        result.add("scanerSlotNum", m_scanerSlotNum);
        result.add("weaponSlotNum", m_weaponSlotNum);
        result.add("artefactSlotNum", m_artefactSlotNum);
        result.add("cargoSlotNum", m_cargoSlotNum);

        return result;
    }

private:
    std::vector<meti::vec3> m_turrelPoints;
    std::vector<meti::vec3> m_drivePoints;
    std::vector<meti::vec3> m_protectorPoints;

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
        ar & boost::serialization::base_object<SpaceObjectDescr>(*this);

        ar & m_turrelPoints;
        ar & m_drivePoints;
        ar & m_protectorPoints;

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

} // namespace descriptor
