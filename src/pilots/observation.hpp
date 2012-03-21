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

class MineralObservationData
{
	public:
		Mineral* mineral;
		float dist;
		
		MineralObservationData(Mineral*, float);
};

class ContainerObservationData
{
	public:
		Container* container;
		float dist;
		
		ContainerObservationData(Container*, float);
};

class AsteroidObservationData
{
	public:
		Asteroid* asteroid;
		float dist;
		
		AsteroidObservationData(Asteroid*, float);
};

class NpcObservationData
{
	public:
		Npc* npc;
		float dist;
		
		NpcObservationData(Npc*, float);
};


class StarSystemObservationData
{
	public:
		StarSystem* starsystem;
		float dist;
		
		StarSystemObservationData(StarSystem*, float);
};



class Observation 
{
   	public:
      		Observation(Npc*);
     		~Observation();

     		std::vector<StarSystemObservationData> visible_STARSYSTEM_vec; 
     		                                
     		std::vector<AsteroidObservationData>  visible_ASTEROID_vec; 		
     		std::vector<MineralObservationData>   visible_MINERAL_vec;                
     		std::vector<ContainerObservationData> visible_CONTAINER_vec;

     		std::vector<NpcObservationData> visible_NPC_vec;                
     		std::vector<NpcObservationData> visible_NPC_RANGER_vec;
     		std::vector<NpcObservationData> visible_NPC_WARRIOR_vec;
     		std::vector<NpcObservationData> visible_NPC_TRADER_vec;
     		std::vector<NpcObservationData> visible_NPC_PIRAT_vec;
     		std::vector<NpcObservationData> visible_NPC_DIPLOMAT_vec;

     		VisionStatus see;

 		void observeAll_inSpace_inStatic();
          	
          	void findEchievableStarSystems_inStatic(Galaxy*);
          	StarSystem* getClosestStarSystem(bool) const;
          	Npc* getClosestNpc(std::vector<int>*) const;
          	          	          	                
          	void findVisibleAsteroids_inSpace_inStatic();
          	void findVisibleMinerals_inSpace_inStatic();
          	void findVisibleContainers_inSpace_inStatic();
          	void findVisibleNpcs_inSpace_inStatic();
               	void findVisibleRangerNpcs_inSpace_inStatic();
               	void findVisibleWarriorNpcs_inSpace_inStatic();
               	void findVisibleTraderNpcs_inSpace_inStatic();
               	void findVisiblePiratNpcs_inSpace_inStatic();
               	void findVisibleDiplomatNpcs_inSpace_inStatic();

                template <typename OBSERVED_DATA_TYPE>
		void sort(std::vector<OBSERVED_DATA_TYPE>*);

              	
               	void printVisibleMineralInformation() const;  // debug
               	
	private:
                Npc* npc_owner;	
};

#endif 
     
