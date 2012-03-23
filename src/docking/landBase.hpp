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


#ifndef LANDBASE_H
#define LANDBASE_H

class LandBase
{
        public:
                LandBase();
                virtual ~LandBase();

		int getTypeId() const;
		
		virtual bool getPermissionToLand() const = 0;
		                
                virtual bool add(VehicleBase*) = 0;
                virtual bool add(Npc*) = 0;
                virtual bool remove(VehicleBase*) = 0;
                virtual bool remove(Npc*) = 0;
                
                virtual void ai() = 0;       
                
                void addToLaunchingQueue(Npc*);                
		void addToDockingQueue(Npc*);  
		
		void manageDockingQueue();
                void manageLaunchingQueue();
                         
        protected:
        	int type_id;
        	
                std::vector<Npc*>         NPC_vec;
                std::vector<VehicleBase*> VEHICLE_vec;        
                
                std::vector<Npc*> NPC_launching_vec;
                std::vector<Npc*> NPC_docking_vec;
};

#endif
