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

#ifndef GOD_H
#define GOD_H

class StarSystem;
#include "../common/constants.hpp"

class God
{
	public:
		static God& Instance();
		~God();

		void CreateLifeInStarSystem(StarSystem*) const;
                       	 		                
        private:
		God() {};
		God(const God&) = delete;
		God& operator=(const God&) = delete;
		                
        	void CreateLifeToPlanets(StarSystem*) const;
        	void CreateSpaceStations(StarSystem*, int) const;
        	void CreateShipsInSpace(StarSystem*, int, int, int requestedclass = NONE_ID) const;   
}; 

#endif 
    

        


