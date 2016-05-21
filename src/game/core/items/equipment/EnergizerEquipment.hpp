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
#include <items/equipment/BaseEquipment.hpp>


class EnergizerEquipment : public item::equipment::Base
{
    public:
        EnergizerEquipment(const id_type& id);
        virtual ~EnergizerEquipment();

        void SetEnergyMaxOrig(int energy_max_orig)    { this->energy_max_orig  = energy_max_orig; };
        void SetRestorationOrig(int restoration_orig) { this->restoration_orig = restoration_orig; };
        void SetEnergy(int energy) { this->energy  = energy; };

        int GetEnergyMax() const { return energy_max; };
        int GetEnergy() const { return energy; };

        void IncreaseEnergy(int energy) { this->energy += energy; };
        void DecreaseEnergy(int energy) { this->energy -= energy; };

        void CountPrice();
        virtual void updateProperties();

        virtual void updateInStatic();

        virtual void Save(boost::property_tree::ptree&) const;
        virtual void Load(const boost::property_tree::ptree&);
        virtual void Resolve();
        
    private:
        int energy_max_orig = 0;
        int energy_max_add = 0;
        int energy_max = 0;
        int energy = 0;
        
        int restoration_orig = 0;
        int restoration_add = 0;
        int restoration = 0;
        
        void virtual addUniqueInfo();
        std::string GetEnergyStr();
        std::string GetRestorationStr();
        
        void SaveData(boost::property_tree::ptree&, const std::string&) const;
        void LoadData(const boost::property_tree::ptree&);
        void ResolveData();
};


