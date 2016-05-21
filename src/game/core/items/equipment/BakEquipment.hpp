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

#include "BaseEquipment.hpp"

class BakEquipment : public BaseEquipment
{
public:
    BakEquipment(const id_type& id);
    virtual ~BakEquipment();

    void setFuelMaxOrig(int fuelMaxOrig) { m_fuelMaxOrig = fuelMaxOrig; }
    void setFuel(int fuel)               { m_fuel = fuel; }
    void increaseFuel(int fuel);
    int fuelMiss() const { return (m_fuelMax - m_fuel); }

    int fuel() const    { return m_fuel; }
    int fuelMax() const { return m_fuelMax; }

    void updateProperties() override final;

    void countPrice();

    virtual void Save(boost::property_tree::ptree&) const;
    virtual void Load(const boost::property_tree::ptree&);
    virtual void Resolve();

private:
    int m_fuelMaxOrig = 0;
    int m_fuelMaxAdd = 0;
    int m_fuelMax = 0;
    int m_fuel = 0;

    void virtual addUniqueInfo();
    std::string getFuelStr();

    void SaveData(boost::property_tree::ptree&, const std::string&) const;
    void LoadData(const boost::property_tree::ptree&);
    void ResolveData();
};

