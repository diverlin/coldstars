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



QuestObject :: QuestObject(Npc* _npc_owner)
{
	npc_owner = _npc_owner;
	
	type_id = NONE_ID;
	action_id = NONE_ID;
		
	npc = NULL;
	planet = NULL;
	
	exist = false;
}


QuestObject :: ~QuestObject()
{}
	
	
StarSystem* QuestObject :: getObStarSystem()
{
	if (type_id == NPC_ID)
		return npc->getStarSystem();
	if (type_id == PLANET_TYPE_ID)
		return planet->getStarSystem();
}

bool QuestObject :: getExist() const { return exist; }
int QuestObject :: getTypeId() const { return type_id; }
int QuestObject :: getActionId() const { return action_id; }

Npc* QuestObject :: getNpc()      { return npc; }
Planet* QuestObject :: getPlanet() { return planet; }
		
template <typename TARGET>
void QuestObject :: setTask(TARGET _target, int _action_id)
{
	setObject(_target);
	type_id = _target->getTypeId();
	action_id = _action_id;
	
	exist = true;
}


void QuestObject :: setObject(Npc* _npc)       { npc = _npc;  }
void QuestObject :: setObject(Planet* _planet) { planet = _planet; }


void QuestObject :: clear()
{
	if (type_id == NPC_ID)
		npc = NULL;
	if (type_id == PLANET_TYPE_ID)
		planet = NULL;
	
	type_id = NONE_ID;
	action_id = NONE_ID;
	exist = false;
}

		

void QuestObject :: validation()
{
	if (type_id == NPC_ID)
	{
		if (npc->getAlive() == false)
		{
			clear();
			return;
		}
	}
	
	if (type_id == PLANET_TYPE_ID)
	{
		//return planet->getStarSystem();
	}
}
