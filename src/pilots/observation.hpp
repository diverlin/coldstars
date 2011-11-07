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


#ifndef OBSERVATION_H
#define OBSERVATION_H


class Observation 
{
   	public:
      		Observation(Npc*);
     		~Observation();
                                
   	//private:
                Npc* npc;
        
     		std::vector<Asteroid*>  visible_ASTEROID_vec;
     		std::vector<Asteroid*>  sorted_visible_ASTEROID_vec;
     		     		
     		std::vector<Mineral*>   visible_MINERAL_vec;
                std::vector<Mineral*>   sorted_visible_MINERAL_vec;
                
     		std::vector<Container*> visible_CONTAINER_vec;
     		std::vector<Container*> sorted_visible_CONTAINER_vec;
                
     		std::vector<Npc*> visible_NPC_RANGER_vec;
     		std::vector<Npc*> visible_NPC_WARRIOR_vec;
     		std::vector<Npc*> visible_NPC_TRADER_vec;
     		std::vector<Npc*> visible_NPC_PIRAT_vec;
     		std::vector<Npc*> visible_NPC_DIPLOMAT_vec;

     		VisionStatus see;

 		void observeAll_inSpace_inStatic();
     		//void observe_inPlanet_inStatic();  //inhabited <-> uninhabited
                
          	void findVisibleAsteroids_inSpace_inStatic();
          	void findVisibleMinerals_inSpace_inStatic();
          	void findVisibleContainers_inSpace_inStatic();
          	void findVisibleNpcs_inSpace_inStatic();
               	void findVisibleRangerNpcs_inSpace_inStatic();
               	void findVisibleWarriorNpcs_inSpace_inStatic();
               	void findVisibleTraderNpcs_inSpace_inStatic();
               	void findVisiblePiratNpcs_inSpace_inStatic();
               	void findVisibleDiplomatNpcs_inSpace_inStatic();

                void sortVisibleMinerals_inSpace_inStatic();
               	void sortVisibleAsteroids_inSpace_inStatic(); 
               	
	private:
	     	std::vector<float> asteroid_distance_vec;
     		std::vector<float> mineral_distance_vec;
     		std::vector<float> container_distance_vec;

     		std::vector<float> npc_ranger_distance_vec;
     		std::vector<float> npc_warrior_distance_vec;
     		std::vector<float> npc_trader_distance_vec;
     		std::vector<float> npc_pirat_distance_vec;
     		std::vector<float> npc_diplomat_distance_vec;
};

#endif 
     
