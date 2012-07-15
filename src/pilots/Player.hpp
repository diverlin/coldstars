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

#ifndef PLAYER_H
#define PLAYER_H



class ControlFlags
{
	private:
		bool scan_mode;
		bool grab_mode;

		bool show_galaxymap;
		bool show_all_path;
		bool show_all_shipsinfo;
		bool show_planets_info;	
		bool show_all_orbits;
		bool show_radar_range;
	
	public:
		ControlFlags():
		scan_mode(false),
		grab_mode(false),
		show_galaxymap(false),
		show_all_path(false),
		show_all_shipsinfo(false),
		show_planets_info(false),
		show_all_orbits(false),
		show_radar_range(false)
		{}
		~ControlFlags() {};

		//void SetShowAllOrbit(bool show_all_orbit)     { this->show_all_orbit = show_all_orbit; }
		//void SetShowAllPath(bool show_all_path)       { this->show_all_path = show_all_path; }
		//void SetShowRadarRange(bool show_radar_range) { this->show_radar_range = show_radar_range; }
		//void SetShowGrappleRange(bool show_grapple_range)  { this->show_grapple_range = show_grapple_range; }
		void SetShowGalaxyMapFlag(bool show_galaxymap) { this->show_galaxymap = show_galaxymap; };
		//void SetShowAllShipsInfo(bool show_all_shipsinfo) { this->show_all_shipsinfo = show_all_shipsinfo; };

		bool GetShowAllOrbitsFlag()     const { return show_all_orbits; };
		bool GetShowAllPathFlag()      const { return show_all_path; };

		bool GetShowGalaxyMapFlag() const { return show_galaxymap; };
		bool GetShowAllShipsInfoFlag() const { return show_all_shipsinfo; };
		bool GetShowRadarRangeFlag() const { return show_radar_range; };
		bool GetGrabModeFlag() const { return grab_mode; };
		
		//bool GetShowRadarRange()   const { return show_radar_range; }
		//bool GetShowGrappleRange() const { return show_grapple_range; }        
				
		//void InverseShowGalaxyMapFlag() 
		//{
			//if (show_galaxymap == true) 	{ show_galaxymap = false; }
			//else 				{ show_galaxymap = true; };			
		//};

		void InverseShowAllPathFlag() 
		{
			if (show_all_path == true) 	{ show_all_path = false; }
			else 				{ show_all_path = true; };			
		};
		
		void InverseShowAllOrbitsFlag() 
		{
			if (show_all_orbits == true) 	{ show_all_orbits = false; }
			else 				{ show_all_orbits = true; };			
		};
		
		void InverseShowRadarRangeFlag() 
		{
			if (show_radar_range == true) 	{ show_radar_range = false; }
			else 				{ show_radar_range = true; };			
		};
		
		void InverseGrabModeFlag() 
		{
			if (grab_mode == true) 	{ grab_mode = false; }
			else 				{ grab_mode = true; };			
		};
};

class WeaponSelector
{
	public:
		WeaponSelector();
		void SetSingle(unsigned int, bool);		
		void SetAll(bool);
		
		bool GetSingle(unsigned int) const;
		bool StatesAreMixed() const;
	
	private:
		bool state[GAME::WEAPONS_NUM_MAX];	
};


struct UnresolvedDataUniquePlayer
{
	int npc_id;	
	vec2f screen_pos;
};


class Player : public Base
{
   	public:
    		Player(int);
     		~Player();

		ControlFlags& GetControlFlags() 	{ return control_flags; };
		WeaponSelector& GetWeaponsSelector()	{ return weapons_selector; };
          	
		Npc* GetNpc()       const { return npc; }
		Cursor* GetCursor() const { return cursor; }
   
     		void BindNpc(Npc*);
     		
     		void ClearVisibleEntities();
     		
     		void AddIfVisible(Star*);
     		void AddIfVisible(Planet*);
     		void AddIfVisible(Asteroid*);     		
     		void AddIfVisible(Container*);     	
     		void AddIfVisible(RocketBullet*);  
     		void AddIfVisible(BlackHole*);  
     		void AddIfVisible(Vehicle*); 

		//effect
     		void AddIfVisible(ShockWaveEffect*);  
     		void AddIfVisible(LazerTraceEffect*);  
     		void AddIfVisible(BaseParticleSystem*); 
     		void AddIfVisible(VerticalFlowText*); 
     		//	
  		
     		void RunSession(const TurnTimer&); 
    		
    		void ForceStateMachineReset() const;
    		                
                void SaveData(boost::property_tree::ptree&) const;		
		void LoadData(const boost::property_tree::ptree&);
		void ResolveData();
		 
     	private:
    	     	Npc*     npc;
     	     	
     	     	Cursor* cursor;

     	     	ControlFlags control_flags;  
     		WeaponSelector weapons_selector;     		     	     	
     	     	
     	     	// VISIBLE ENTITY LIST
    		std::vector<Star*>         visible_STAR_vec;
    		std::vector<Planet*>       visible_PLANET_vec;
    		std::vector<Asteroid*>     visible_ASTEROID_vec;
    		std::vector<Container*>    visible_CONTAINER_vec;
    		std::vector<RocketBullet*> visible_ROCKET_vec;
    		std::vector<BlackHole*>    visible_BLACKHOLE_vec; 		
    		std::vector<Ship*>         visible_SHIP_vec;
    		std::vector<Satellite*>    visible_SATELLITE_vec;
    		std::vector<SpaceStation*> visible_SPACESTATION_vec;
    		
    		//effects
    		std::vector<ShockWaveEffect*>    visible_effect_SHOCKWAVE_vec;
    		std::vector<LazerTraceEffect*>   visible_effect_LAZERTRACE_vec;
    		std::vector<BaseParticleSystem*> visible_effect_PARTICLESYSTEM_vec;  		
    		std::vector<VerticalFlowText*>   visible_text_DAMAGE_vec;
    		//  
    		
    		UnresolvedDataUniquePlayer data_unresolved_player;
    		
    		GuiManager*   GUI_MANAGER;    
    		
    		void RenderInSpace(bool, bool, bool); 
     			void RenderInSpace_NEW();
    			void RenderInSpace_OLD();
    		
    		
    		void SessionInSpace(const TurnTimer&);
    		void SessionInKosmoport();
    		
    		void MouseInteractionInSpace(float, float, bool, bool);
    		bool MouseInteractionWithRockets(float, float, bool, bool) const;
    		bool MouseInteractionWithContainers(float, float, bool, bool) const;
    		bool MouseInteractionWithSatellites(float, float, bool, bool) const;
    		bool MouseInteractionWithAsteroids(float, float, bool, bool) const;
    		bool MouseInteractionWithShips(float, float, bool, bool) const;
    		bool MouseInteractionWithBlackHoles(float, float, bool, bool) const;
    		bool MouseInteractionWithSpaceStations(float, float, bool, bool) const;
    		bool MouseInteractionWithPlanets(float, float, bool, bool) const;
    		bool MouseInteractionWithStars(float, float, bool, bool) const;
    		void MouseNavigation(float, float, bool, bool) const;
    		
    		bool IsObjectOnScreen(const Points&) const;
    		bool IsObjectOnScreen(const vec2f&, float) const;
    		
    		void SaveDataUniquePlayer(boost::property_tree::ptree&, const std::string&) const;		
		void LoadDataUniquePlayer(const boost::property_tree::ptree&);
		void ResolveDataUniquePlayer();

    		friend class UserInput;
};

#endif 



        
