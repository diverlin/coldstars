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


#ifndef GALAXY_H
#define GALAXY_H


class Galaxy 
{
  	public:
     		Rect map_rect;

     		int starsytem_counter;
     		int star_counter;      
     		int ship_counter;
     		int planet_counter;
     		StarSystem* pTo_ss_active;
     		std::vector<StarSystem*> STARSYSTEM_pList;
     		std::vector<StarSystem*> hSTARSYSTEM_pList;

     		Galaxy();
     
     		void generateEntireStarSystem();
     		void generateBackground(StarSystem* _pTo_starsystem, int distNebula_maxNum, int distStar_maxNum);
     		void generateNumPlanets(StarSystem* _pTo_starsystem, int planet_per_system);
     
     		void generateNumFriendlyNPC(StarSystem* _pTo_starsystem, int ship_per_system);
     		void generateNumEnemyNPC(StarSystem* _pTo_starsystem, int ship_per_system);

     		void manageHiddenStarSystemList(StarSystem* _pTo_ss);

     		bool manage_map();
     		void render_map();
};

#endif 
