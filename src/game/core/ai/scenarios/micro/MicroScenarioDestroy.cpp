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
#include "../../../spaceobjects/Vehicle.hpp"
#include "../../../ai/StateMachine.hpp"
#include "../../../parts/WeaponComplex.hpp"

MicroScenarioDestroy::MicroScenarioDestroy()
{
    setTypeId(type::AISCENARIO::MICRO_DESTROY_ID);
}

/* virtual */
MicroScenarioDestroy::~MicroScenarioDestroy()
{}

/* virtual */    
bool MicroScenarioDestroy::Validate(Npc* npc) const
{    
    if (npc->stateMachine().microTaskManager().target()->isAlive() == false)
    {
        return false;
    } 
    
    if (npc->starsystem() != npc->stateMachine().microTaskManager().target()->starsystem())
    {
         return false;
    }
    
    return true;        
}

/* virtual */                
void MicroScenarioDestroy::enter(Npc* npc) const
{    
    LOG("npc_id=" + std::to_string(npc->id()) + " ENTER MicroScenarioDestroy");
}

/* virtual */
void MicroScenarioDestroy::UpdateInStaticInSpace(Npc* npc) const
{
    npc->vehicle()->weaponComplex().activateWeapons();
    npc->stateMachine().microTaskManager().target()->id();
    npc->vehicle()->weaponComplex().setTarget(npc->stateMachine().microTaskManager().target());
    npc->vehicle()->driveComplex().SetTarget(npc->stateMachine().microTaskManager().target(), NAVIGATOR_ACTION::KEEP_FIRE_DISTANCE_ID);
}

/* virtual */
void MicroScenarioDestroy::UpdateInDynamicInSpace(Npc* npc) const
{}

/* virtual */
void MicroScenarioDestroy::exit(Npc* npc) const
{
    LOG("npc_id=" + std::to_string(npc->id()) + " EXIT MicroScenarioDestroy");
}

/* virtual */
std::string MicroScenarioDestroy::GetDescription(Npc* npc) const
{
    return "DESTROY ob_id=" + std::to_string( npc->stateMachine().microTaskManager().target()->id()) ;
}
