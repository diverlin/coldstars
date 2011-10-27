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


#ifndef QUESTOBJECT_H
#define QUESTOBJECT_H


class QuestObject
{
	public:		
		QuestObject(Npc*);
		~QuestObject();		

		template <typename TARGET>
		void setTask(TARGET _target, int _action_id);
		
		StarSystem* getStarSystem();
		bool getExist() const;
		int getTypeId() const;
		int getActionId() const;
		Npc* getNpc();
		Planet* getPlanet();
				
		void reset();
		void validation();
	
	private:
		Npc* npc_owner;

		bool exist;
		
		int action_id;
		int ob_type_id;
		
		Npc*        npc;
		Planet*     planet;
		StarSystem* starsystem;
		
		void setObject(Npc*);
		void setObject(Planet*);		
		void setObject(StarSystem*);	
};


#endif
