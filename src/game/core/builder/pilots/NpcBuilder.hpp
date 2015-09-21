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

#include <types/MyInt.hpp>
#include <types/RaceTypes.hpp>
#include <types/EntityTypes.hpp>

class Npc;


class NpcBuilder
{
    public:
        NpcBuilder();
        ~NpcBuilder();
        
        Npc* createTemplate(TYPE::ENTITY, TYPE::ENTITY, INTLONGEST id = NONE_ID) const;
        Npc* create(TYPE::RACE, TYPE::ENTITY, TYPE::ENTITY) const;
                                       
    private:
        void CreateNewInternals(Npc*, TYPE::RACE, TYPE::ENTITY, TYPE::ENTITY) const;
}; 
