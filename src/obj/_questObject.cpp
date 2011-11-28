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


QuestObject :: QuestObject()
{
        reset();
}


QuestObject :: ~QuestObject()
{}


StarSystem* QuestObject :: getStarSystem()
{
	if (ob_type_id == NPC_ID)
	{
		return npc->getStarSystem();
	}

	if (ob_type_id == PLANET_ID)
	{
		return planet->getStarSystem();
	}

	if (ob_type_id == STARSYSTEM_ID)
	{
		return starsystem;
	}
        
        return NULL;
}


bool QuestObject :: getExist()   const { return exist; }
int QuestObject :: getObTypeId() const { return ob_type_id; }

int QuestObject :: getObId() const { return ob_id; }

Npc* QuestObject :: getNpc()      { return npc; }
Planet* QuestObject :: getPlanet() { return planet; }
	
template <typename TARGET>
void QuestObject :: setObject(TARGET _target)
{
	set(_target);
	ob_type_id = _target->getTypeId();
	ob_id = _target->getId();

	exist = true;
}
void QuestObject :: set(Npc* _npc)               { npc = _npc;  }
void QuestObject :: set(Planet* _planet)         { planet = _planet; }
void QuestObject :: set(StarSystem* _starsystem) { starsystem = _starsystem; }


void QuestObject :: reset()
{
	npc = NULL;
	planet = NULL;
	starsystem = NULL;
	
	ob_type_id = NONE_ID;
	
        exist = false;
}

		

void QuestObject :: validation()
{
	/* check condition of quest object, if it is not valid then reset */
	
	if (ob_type_id == NPC_ID)
	{
		if (npc->getAlive() == false)
		{
			reset();
			return;
		}
	}
	
	//if (ob_type_id == PLANET_ID)
	//{
		//return; 
	//}
	
	if (ob_type_id == STARSYSTEM_ID)
	{
		if (starsystem->getCaptured() == false)
		{
			reset();
			return;
		} 
	}
}
