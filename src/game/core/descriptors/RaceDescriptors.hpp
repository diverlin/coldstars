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

#include <vector>
#include <map>
#include <types/RaceTypes.hpp>
#include <types/EntityTypes.hpp>

class RaceDescriptors
{
    public:
        RaceDescriptors();
        ~RaceDescriptors();

        const std::vector<type::race>& getRaces(type::KIND) const;
        const std::vector<type::ENTITY>& getSubTypes(type::race) const;

        bool isGood(type::race) const;

    private:
        std::map<type::KIND, std::vector<type::race>> m_races;
        std::map<type::race, std::vector<type::ENTITY>> m_subtypes;
}; 


