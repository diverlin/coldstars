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


#ifndef DOCKINGSTATION_H
#define DOCKINGSTATION_H

class DockingStation 
{
        public:
                DockingStation(int);
    	        ~DockingStation();
		
                bool getPermissionToLand() const;
                Kosmoport* getKosmoport();
                Land* getLand();

                bool add(Ship*);
                bool add(Npc*);

		void addToLaunchingQueue(Npc*);                
                void launchingProcedure();
                
                bool removeShipById(int);
                bool removeNpcById(int);
                
                void update_inSpace_inDynamic();
                void update_inSpace_inStatic();
                
                void updateInfo();
                void renderInfo();
                
                void createInternals();
                
        private:
        	int race_id;
                Kosmoport* kosmoport;
                Land*      land;
                
                std::vector<Npc*> NPC_launching_vec;
                
		void createKosmoport();
                void createLand();
}; 


DockingStation* getNewDockingStation(int);


#endif 
    

        


