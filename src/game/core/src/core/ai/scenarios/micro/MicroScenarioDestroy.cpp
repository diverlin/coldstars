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

#include "MicroScenarioDestroy.hpp"
#include "../../../common/constants.hpp"
#include <ceti/Logger.hpp>
//#include <ceti/StringUtils.hpp>
#include <core/spaceobject/Vehicle.hpp>
#include "../../../ai/StateMachine.hpp"
#include "../../../parts/WeaponComplex.hpp"

MicroScenarioDestroy::MicroScenarioDestroy()
{
    setTypeId(ai::type::MICRO_DESTROY);
}

/* virtual */
MicroScenarioDestroy::~MicroScenarioDestroy()
{}

/* virtual */    
bool MicroScenarioDestroy::Validate(Npc* npc) const
{
    assert(false);
//    if (!npc->stateMachine().microTaskManager().target()->isAlive()) {
//        return false;
//    }
    
//    if (npc->starsystem() != npc->stateMachine().microTaskManager().target()->starsystem()) {
//         return false;
//    }
    
    return true;        
}

/* virtual */                
void MicroScenarioDestroy::enter(Npc* npc) const
{    
    assert(false);
    //LOG("npc_id=" + std::to_string(npc->id()) + " ENTER MicroScenarioDestroy");
}

/* virtual */
void MicroScenarioDestroy::UpdateInStaticInSpace(Npc* npc) const
{
    assert(false);
//    npc->vehicle()->weaponComplex().activateWeapons();
//    npc->stateMachine().microTaskManager().target()->id();
//    npc->vehicle()->weaponComplex().setTarget(npc->stateMachine().microTaskManager().target());
//    npc->vehicle()->driveComplex().SetTarget(npc->stateMachine().microTaskManager().target(), NAVIGATOR_ACTION::KEEP_FIRE_DISTANCE);
}

/* virtual */
void MicroScenarioDestroy::UpdateInDynamicInSpace(Npc* npc) const
{}

/* virtual */
void MicroScenarioDestroy::exit(Npc* npc) const
{
    assert(false);
    //LOG("npc_id=" + std::to_string(npc->id()) + " EXIT MicroScenarioDestroy");
}

/* virtual */
std::string MicroScenarioDestroy::GetDescription(Npc* npc) const
{
    assert(false);
    //return "DESTROY ob_id=" + std::to_string( npc->stateMachine().microTaskManager().target()->id()) ;
}
