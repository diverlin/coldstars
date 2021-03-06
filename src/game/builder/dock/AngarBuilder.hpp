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


#ifndef ANGARBUILDER_HPP
#define ANGARBUILDER_HPP

#include <types/MyInt.hpp>

class Angar;

const unsigned int ANGAR_ITEM_SLOTS_NUM = 10;
const unsigned int ANGAR_VEHICLE_SLOTS_FOR_MILITARY_NUM = 6;
const unsigned int ANGAR_VEHICLE_SLOTS_FOR_VISITORS_NUM = 6;
const unsigned int ANGAR_VEHICLE_SLOTS_NUM = ANGAR_VEHICLE_SLOTS_FOR_MILITARY_NUM + ANGAR_VEHICLE_SLOTS_FOR_VISITORS_NUM;


class AngarBuilder
{
    public:
        static AngarBuilder& Instance();
        ~AngarBuilder();

        Angar* GetNewAngarTemplate(INTLONGEST id = NONE_ID) const; 
        Angar* GetNewAngar() const;

    private:
        AngarBuilder() {};
        AngarBuilder(const AngarBuilder&) = delete;
        AngarBuilder& operator=(const AngarBuilder&) = delete;

        void CreateNewInternals(Angar*) const;
}; 

#endif 
    

        


