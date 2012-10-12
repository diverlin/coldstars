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

#ifndef SHOW_H
#define SHOW_H

class Show
{
	private:
		bool gui_scan;
		bool gui_galaxymap;
                bool gui_radar;
                
		bool all_path;
                bool all_orbits;
                
                bool info_ships;
		bool info_planets;
                
		bool range_radar;
	
	public:
		Show():
		gui_scan(false),
		gui_galaxymap(false),    
                gui_radar(false),            
		all_path(false),
                all_orbits(false),                
                info_ships(false),
		info_planets(false),                
		range_radar(false)
		{};
                
		~Show() {};
		
		void SetGuiGalaxyMap(bool gui_galaxymap) { this->gui_galaxymap = gui_galaxymap; };
		void SetGuiRadar(bool gui_radar) { this->gui_radar = gui_radar; };
                		
		bool GetAllOrbits()    const { return all_orbits; };
		bool GetAllPath()      const { return all_path; };

		bool GetGuiGalaxyMap() const { return gui_galaxymap; };
		bool GetGuiRadar() const { return gui_radar; };
                
		bool GetInfoShips() const { return info_ships; };
		bool GetRangeRadar() const { return range_radar; };
		
		void InverseAllPath() 
		{
			if (all_path == true) 	{ all_path = false; }
			else 			{ all_path = true; };
		};
		
		void InverseAllOrbits() 
		{
			if (all_orbits == true) { all_orbits = false; }
			else 			{ all_orbits = true; };
		};
		
		void InverseRangeRadar() 
		{
			if (range_radar == true) { range_radar = false; }
			else 			 { range_radar = true; };			
		};
};

#endif 



        
