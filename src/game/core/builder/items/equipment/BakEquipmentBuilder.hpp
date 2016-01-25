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
#include <descriptors/Descriptor.hpp>

class BakEquipment;


class BakBuilder
{
    public:
        BakBuilder();
        ~BakBuilder();

        BakEquipment* createTemplate(id_type id = NONE_ID) const;
        BakEquipment* create(const Descriptor&) const;
                                     
    private:                
        BakBuilder(const BakBuilder&) = delete;
        BakBuilder& operator=(const BakBuilder&) = delete;

        void createInternals(BakEquipment*, const Descriptor&) const;
}; 

    

        


