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
     		Galaxy();
     		~Galaxy();
     		     		
     		void Add(StarSystem* starsystem) { STARSYSTEM_vec.push_back(starsystem); };
     		
     		int GetId() { return data_id.id; };
     		StarSystem* GetRandomStarSystem();
     		StarSystem* GetRandomCapturedStarSystem();
     		     
    		void Update(int);
    		void SaveEvent() const;
    		void LoadEvent() const;

     	private:
     		IdData data_id;

  	     	std::vector<StarSystem*> STARSYSTEM_vec;
  	     	
  	     	friend class GuiMap;
  	     	friend class Observation;
};

Galaxy* GetNewGalaxy(int id);


#endif 
