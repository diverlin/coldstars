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




class Player 
{
   	public:
     		WeaponSelector weapon_selector;
     		
    		Player();
     		~Player();
   
   		void SetWorldMapShowFlag(bool _show_worldmap) { control.worldmap = _show_worldmap; }
          	
		void SetShowAllOrbit(bool show_all_orbit)     { this->show_all_orbit = show_all_orbit; }
		void SetShowAllPath(bool show_all_path)       { this->show_all_path = show_all_path; }
		void SetShowRadarRange(bool show_radar_range) { this->show_radar_range = show_radar_range; }
		void SetShowGrappleRange(bool show_grapple_range)  { this->show_grapple_range = show_grapple_range; }
          	
		bool GetWorldMapShowFlag() const { return control.worldmap; }         	
		Npc* GetNpc()       const { return npc; }
		Cursor* GetCursor() const { return cursor; }
		Screen* GetScreen() const { return screen; }
         
		bool GetShowAllOrbit()     const { return show_all_orbit; }
		bool GetShowAllPath()      const { return show_all_path; }
		bool GetShowRadarRange()   const { return show_radar_range; }
		bool GetShowGrappleRange() const { return show_grapple_range; }          	 
   
		bool GetNextTurnReady() const { return USERINPUT->getNextTurnReady(); }   


     		void BindNpc(Npc*);
     		
     		void ClearVisibleEntities();
     		
     		void AddIfVisible(Star*);
     		void AddIfVisible(Planet*);
     		void AddIfVisible(Asteroid*);     		
     		void AddIfVisible(Mineral*);
     		void AddIfVisible(Container*);     	
     		void AddIfVisible(RocketBullet*);  
     		void AddIfVisible(BlackHole*);  
     		void AddIfVisible(SpaceStation*);  
     		void AddIfVisible(Satellite*); 
     		void AddIfVisible(Ship*); 

		//effect
     		void AddIfVisible(ShockWaveEffect*);  
     		void AddIfVisible(LazerTraceEffect*);  
     		void AddIfVisible(BaseParticleSystem*); 
     		void AddIfVisible(VerticalFlowText*); 
     		//	
  		
     		void RunSession(GameTimer*); 
     		     		     		     		     	
     	private:
     	     	int type_id, id;
     	     		
     	     	Npc*     npc;
     	     	
     	     	Cursor* cursor;
     	     	Screen* screen;
     	     	
     	     	ControlWord control;  
     	     	
     	     	bool show_all_orbit;
     	     	bool show_all_path;
     	     	bool show_radar_range;
     	     	bool show_grapple_range;
     	     	
     	     	// VISIBLE ENTITY LIST
    		std::vector<Star*>         visible_STAR_vec;
    		std::vector<Planet*>       visible_PLANET_vec;
    		std::vector<Asteroid*>     visible_ASTEROID_vec;
    		std::vector<Mineral*>      visible_MINERAL_vec;
    		std::vector<Container*>    visible_CONTAINER_vec;
    		std::vector<RocketBullet*> visible_ROCKET_vec;
    		std::vector<BlackHole*>    visible_BLACKHOLE_vec;
    		std::vector<SpaceStation*> visible_SPACESTATION_vec;
    		std::vector<Satellite*>    visible_SATELLITE_vec;    		
    		std::vector<Ship*>         visible_SHIP_vec;
    		
    		//effects
    		std::vector<ShockWaveEffect*>    visible_effect_SHOCKWAVE_vec;
    		std::vector<LazerTraceEffect*>   visible_effect_LAZERTRACE_vec;
    		std::vector<BaseParticleSystem*> visible_effect_PARTICLESYSTEM_vec;  		
    		std::vector<VerticalFlowText*>   visible_text_DAMAGE_vec;
    		//  
    		
    		GuiManager*   GUI_MANAGER;    
 		GuiSpace*     GUI_SPACE;      
 		GuiKosmoport* GUI_KOSMOPORT;  
		GuiMap*       GUI_MAP;         
		UserInput*    USERINPUT;       
    		
    		void Render(bool, bool, bool); 
     			void RenderEntities_NEW();
    			void RenderEntities_OLD();
    		
    		
    		void InOuterspace(GameTimer*);
    		void InKosmoport();
    		
    		void MouseInteraction_inOuterSpace();
    		void Update_global(); 
    		
    		bool IsObjectOnScreen(const Points&) const;
};

#endif 



        
