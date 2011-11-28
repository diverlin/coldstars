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


AiModelRanger :: AiModelRanger() 
{}

AiModelRanger :: ~AiModelRanger() 
{}

void AiModelRanger :: update_inStatic(Npc* _npc) const
{
	if (_npc->getMacroTaskMain()->getValid() != true)
        {
        	StarSystem* ss_to_free = _npc->getClosestStarSystem(true);
        	if (ss_to_free != NULL)
        	{
        		_npc->getMacroTaskMain()->set(g_MACROSCENARIO_STARSYSTEMLIBERATION, ss_to_free);        			
			_npc->getMacroTaskStateMachine()->setCurrentState(g_MACROSCENARIO_STARSYSTEMLIBERATION, ss_to_free);    // work around
        	}
        }            
}

std::string AiModelRanger :: getDescription(Npc* _npc) const
{
	return "AiModelRanger";
}
