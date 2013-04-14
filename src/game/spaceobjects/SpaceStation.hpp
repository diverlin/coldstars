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


#ifndef SPACESTATION_H
#define SPACESTATION_H

#include "Vehicle.hpp"
#include "../docking/BaseLand.hpp"


class SpaceStation : public Vehicle
{
    	public:  
        	SpaceStation(int);
        	virtual ~SpaceStation();
        	
        	virtual void PutChildsToGarbage() const;
        		
		BaseLand* GetLand() const { return land; };
		void BindLand(BaseLand* land);

		void UpdateInSpace(int, bool);
		
        	virtual void UpdateInfo(); 
        	
        	void UpdateRenderStuff();
        	void RenderInSpace() const;
		void RenderAtPlanet() const; 
        	
        	void RenderMesh_NEW(const vec2f&);
        			
        	void SaveData(boost::property_tree::ptree&) const;
    		void LoadData(const boost::property_tree::ptree&);
    		void ResolveData();
    		
        private:
                BaseLand* land;
              
                void SaveDataUniqueSpaceStation(boost::property_tree::ptree&, const std::string&) const;
		void LoadDataUniqueSpaceStation(const boost::property_tree::ptree&);
		void ResolveDataUniqueSpaceStation();
};


#endif 

