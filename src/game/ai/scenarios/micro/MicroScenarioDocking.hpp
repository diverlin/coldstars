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


#ifndef MICROSCENARIODOCKING_H
#define MICROSCENARIODOCKING_H

#include "../BaseScenario.hpp"
class Npc; //#include "../../../pilots/Npc.hpp"

class MicroScenarioDocking : public BaseScenario
{
    public:
        MicroScenarioDocking();
        virtual ~MicroScenarioDocking();
        
        virtual void Enter(Npc*) const;
        virtual bool Validate(Npc* npc) const;
        virtual void UpdateInStaticInSpace(Npc*) const;
        virtual void UpdateInDynamicInSpace(Npc*) const;    
        virtual void Exit(Npc*) const;
        
        virtual std::string GetDescription(Npc*) const;
};

#endif 
     
