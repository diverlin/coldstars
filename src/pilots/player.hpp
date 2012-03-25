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
     
          	void setWorldMapShowFlag(bool);
          	
          	void setShowAllOrbit(bool);
          	void setShowAllPath(bool);
          	void setShowRadarRange(bool);
          	void setShowGrappleRange(bool);
          	          	
          	bool getWorldMapShowFlag() const;
          	bool getShowAllOrbit() const;
          	bool getShowAllPath() const;
          	bool getShowRadarRange() const;
          	bool getShowGrappleRange() const;
          	  
          	bool getNextTurnReady() const;
          	  		        	
		Npc* getNpc() const; 	     
		Cursor* getCursor() const;    
		Screen* getScreen() const;     
   
     		void bindNpc(Npc*);
     		
     		void clearVisibleEntities();
     		
     		void addIfVisible(Star*);
     		void addIfVisible(Planet*);
     		void addIfVisible(Asteroid*);     		
     		void addIfVisible(Mineral*);
     		void addIfVisible(Container*);     	
     		void addIfVisible(RocketBullet*);  
     		void addIfVisible(BlackHole*);  
     		void addIfVisible(SpaceStation*);  
     		void addIfVisible(Satellite*); 
     		void addIfVisible(Ship*); 

		//effect
     		void addIfVisible(ShockWaveEffect*);  
     		void addIfVisible(LazerTraceEffect*);  
     		void addIfVisible(BaseParticleSystem*); 
     		void addIfVisible(VerticalFlowText*); 
     		//	


     		
     		void runSession(GameTimer*); 
     		     		     		     		     	
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
    		
    		void render(bool, bool, bool); 
     			void renderEntities_NEW();
    			void renderEntities_OLD();
    		
    		
    		void outerspace(GameTimer*);
    		void kosmoport();
    		
    		void mouseControl();
    		void update_global(); 
    		
    		bool isObjectOnScreen(const Points&) const;
};

#endif 



        
