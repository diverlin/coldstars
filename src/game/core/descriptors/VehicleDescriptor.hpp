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

#include <string>

#include <types/IdType.hpp>
#include <types/RaceTypes.hpp>
#include <types/EntityTypes.hpp>

#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>

class VehicleDescriptor
{
    public:
        ID id = 0;
        TYPE::RACE race_id = TYPE::RACE::R0_ID;
        TYPE::ENTITY type_id = TYPE::ENTITY::WARRIOR_ID;
        int size_id = 0;

        int space = 0;
        int armor = 0;
        int protection = 0;
        int temperature = 0;
        int price = 0;

        bool draw_turrels = false;

        int slot_bak_num = 0;
        int slot_drive_num = 0;
        int slot_droid_num = 0;
        int slot_energizer_num = 0;
        int slot_grapple_num = 0;
        int slot_protector_num = 0;
        int slot_radar_num = 0;
        int slot_scaner_num = 0;
        int slot_freezer_num = 0;
        int slot_weapon_num = 0;
        int slot_artefact_num = 0;
        int slot_otsec_num = 0;
                
    VehicleDescriptor() {}
    VehicleDescriptor(const std::string& data);
    ~VehicleDescriptor() {}

    std::string data() const;

private:
    friend class boost::serialization::access;
    template<class Archive>
    void serialize(Archive & ar, const unsigned int version)
    {
        ar & id;
        ar & race_id;
        ar & type_id;
        ar & size_id;

        ar & space;
        ar & armor;
        ar & protection;
        ar & temperature;
        ar & price;

        ar & draw_turrels;

        ar & slot_bak_num;
        ar & slot_drive_num;
        ar & slot_droid_num;
        ar & slot_energizer_num;
        ar & slot_grapple_num;
        ar & slot_protector_num;
        ar & slot_radar_num;
        ar & slot_scaner_num;
        ar & slot_freezer_num;
        ar & slot_weapon_num;
        ar & slot_artefact_num;
        ar & slot_otsec_num;
    }
};

