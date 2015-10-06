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


#ifndef RADAREQUIPMENT_H
#define RADAREQUIPMENT_H

#include "BaseEquipment.hpp"

class RadarEquipment : public BaseEquipment
{
    public:
        RadarEquipment(const IDTYPE& id);
        virtual ~RadarEquipment();

        void SetRadiusOrig(int radius_orig)   { this->radius_orig = radius_orig; };
        int GetRadius() const { return radius; };

        virtual void updateProperties();

        void CountPrice();

        virtual void Save(boost::property_tree::ptree&) const;
        virtual void Load(const boost::property_tree::ptree&);
        virtual void Resolve();

    private:
        int radius_orig;
        int radius_add;
        int radius;

        void virtual AddUniqueInfo();
        std::string GetRadiusStr();

        void SaveData(boost::property_tree::ptree&, const std::string&) const;
        void LoadData(const boost::property_tree::ptree&);
        void ResolveData();
};

#endif 









