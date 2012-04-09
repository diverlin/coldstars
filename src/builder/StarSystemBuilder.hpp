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


#ifndef STARSYSTEMBUILDER_H
#define STARSYSTEMBUILDER_H


class StarSystemBuilder
{
	public:
		static StarSystemBuilder& Instance();
		~StarSystemBuilder();

        	void CreateNewStarSystem(int id = NONE_ID); 
                void CreateNewInternals();
                void CreateNewInternals2();
                StarSystem* GetStarSystem() const { return starsystem; };
                
                void Load(const boost::property_tree::ptree&);
                       	 		                
        private:
                StarSystem* starsystem;
                
		StarSystemBuilder() {};
		StarSystemBuilder(const StarSystemBuilder&) {};
		StarSystemBuilder& operator=(const StarSystemBuilder&) {};
		
                void CreateBackground(int, int, int);
        	void CreateStar();
        	void CreatePlanets(int);
        	void CreateSpaceStations(int);
        	void CreateShips(int, int);   
}; 



#endif 
    

        


