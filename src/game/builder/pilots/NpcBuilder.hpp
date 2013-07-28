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


#ifndef NPCBUILDER_HPP
#define NPCBUILDER_HPP

#include <types/MyInt.hpp>
#include <types/RaceTypes.hpp>
#include <types/EntityTypes.hpp>

class Npc;


class NpcBuilder
{
	public:
        static NpcBuilder& Instance();
        ~NpcBuilder();
        
        Npc* GetNewNpcTemplate(TYPE::ENTITY, TYPE::ENTITY, INTLONGEST id = NONE_ID) const; 
        Npc* GetNewNpc(TYPE::RACE, TYPE::ENTITY, TYPE::ENTITY) const;
                                       
    private:            
		NpcBuilder() {};
		NpcBuilder(const NpcBuilder&) = delete;
		NpcBuilder& operator=(const NpcBuilder&) = delete;
                
        void CreateNewInternals(Npc*, TYPE::RACE, TYPE::ENTITY, TYPE::ENTITY) const;
}; 



#endif 
    

        


