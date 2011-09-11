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


#ifndef SHIP_H
#define SHIP_H


struct NeedsToDo
{
  	bool REPAIR;
  	bool CHARGE;
   	bool GETBULLETS;
   	bool BUY;
   	bool SELL;
};

struct Abilities
{
   	bool RADAR;
   	bool DRIVE;
   	bool HJUMP;
   	bool ENERGIZE;
   	bool PROTECT;
   	bool REPAIR;
   	bool FREEZE;
   	bool GRAB;
   	bool SCAN;
   	bool FIRE;
};

    
class Ship
{   
    	public:
                Points* getPoints();
                Navigator* getNavigator();
                StarSystem* getStarSystem();
                Npc* getNpc();
        
                void setStarSystem(StarSystem*);
                void setNpc(Npc*);
                                        
        	bool is_alive, is_dying, is_explosed;
        	int type_id, id;

        	int dying_time;
        	
		bool render_TURRELS;
		
        	bool in_SPACE;

        	bool is_FOLLOWING_PLANET;
        	bool is_FOLLOWING_SHIP;
        	bool is_FOLLOWING_STARSYSTEM;



        	TextureOb* texOb;

        	int size;
        	float collision_radius;

        	int w_orig, h_orig;



        	bool controlled_by_player;
        	PlayerInstance* pTo_playerOwner;



        	int space;
        	int armor_max;
        	int armor;
        	int korpus_protection;
        	int nominal_temperature;

        	int race_id;
        	int subtype_id;
        	int size_id;
        	int mod_id;

        	int color_id;
        	int price;


        	//######### KONTUR RECT 
        	int w_kontur, h_kontur;
        	Rect kontur_rect; 






        	int total_weapon_slot_num;
        	ItemSlot weapon_slot1;
        	ItemSlot weapon_slot2;
        	ItemSlot weapon_slot3;
        	ItemSlot weapon_slot4;
        	ItemSlot weapon_slot5;
        

        
        	//######### EQUPMENT SLOT
        	ItemSlot drive_slot;
        	ItemSlot bak_slot;
        	ItemSlot radar_slot;
        	ItemSlot scaner_slot;
        	ItemSlot energizer_slot;
        	ItemSlot grapple_slot;
        	ItemSlot protector_slot;
        	ItemSlot droid_slot;
        	ItemSlot freezer_slot;
                                                
        	//######### OTSEC SLOT
        	std::vector<ItemSlot*> slot_total_pList;
        	std::vector<ItemSlot*> slot_otsec_pList;
        
        	//######### GATE SLOT
        	ItemSlot gate_slot;

        	///////////////////////////////
        	Abilities ableTo;
        	NeedsToDo needsToDo;
                
        	bool inhibit_GRAPPLE;

        	//////////////////////////////
        	/////// PROPERTIES depends on items
        	int protection;
        	int radius;
        	int mass;   // depends on all items mass
        	int speed;  // depends on mass and drive

        	int hyper;  // depends on drive and bak
        	int repair; // depends on droid
        	int freeze; // depends on freezer
        	int scan;   // depends on scaner
        
        	int energy;
        	int temperature;

        	int dist2star_rate;
        	int energy_restoration_rate;


        	//////// TARGET COORDINATES //////
        	//self.Gl_LIST_direction_ID = None
        	std::vector<float> direction_x_list;
        	std::vector<float> direction_y_list;
        	std::vector<float> angle_inD_list;

        	int len_direction_list;
        	bool direction_list_END;
        	int move_it;

        	float target_pos_x;
        	float target_pos_y;
        
        	float jump_pos_x;
        	float jump_pos_y;
        	//////////////////////////////////

        	// simplification
        	int average_damage;
        	int average_fire_radius;


        	Ship(TextureOb* _pTo_texOb, 
        	     int _max_weapons, 
        	     bool _grapple_INHIBIT, 
        	     int _space, 
        	     int _armor_max, 
        	     int _protection, 
        	     int _nominal_temperature);
        	     
        	~Ship();    

        	void calculateDetaledWayToPosition();
        	void updatePosition();

        	void reloadAllWeapons();
        
        	void selectWeapons(bool _wslot_1_SELECTED = true, 
                              	   bool _wslot_2_SELECTED = true, 
                               	   bool _wslot_3_SELECTED = true, 
                                   bool _wslot_4_SELECTED = true, 
                                   bool _wslot_5_SELECTED = true);
                     
        	void setWeaponsTarget(Ship* _ship);
        	void setWeaponsTarget(Asteroid* _asteroid);
		void setWeaponsTarget(Mineral* _mineral);
	  	void setWeaponsTarget(Container* _container);
       
        	void weaponsFire_TRUE(int timer);
        	void weaponsFire_FALSE(int timer);

        	void resetDeselectedWeaponTargets();                                          
        	void removeWeaponSlotDeadTargets();

        	void update_inSpace_inDynamic_TRUE();
        	void update_inSpace_inDynamic_FALSE();

        	void hit_TRUE(int _damage);
        	void hit_FALSE(int _damage);

        	void death(); 

        	void updateAllStuff();
             		void calculateMass();
             		void updateFireAbility();
             		void updateRadarAbility();
             		void updateDriveAbility();
             		void updateJumpAbility();
             		void updateEnergyAbility();
             		void updateProtectionAbility();
             		void updateRepairAbility();
             		void updateFreezeAbility();
             		void updateGrabAbility();
             		void updateScanAbility();

        	ItemSlot* return_pToEmptyOtsecSlot();

        	void setMaxArmor();
        	void setMaxFuel();

        	//// docking/launching
        	bool checkDocking();
        	bool getDockingPermission();
        	bool dockingEvent();

        	bool launchingEvent();
        	//// docking/launching

		void updateRenderStuff();
		void render_inSpace() const;
		void render_atPlanet() const;

        	void renderInfo(float _pos_x, float _pos_y, float _offset_x, float _offset_y);
        	
        	float pos_z;
                                           		
        private:
                float angle_inD;
                Points points;
		InfoTable info;
		
        	std::vector<vec2f*> turrel_center_pList;
		std::vector<Turrel*> turrel_pList;

             		
            	Navigator* navigator;
            	
            	TextureOb* texOb_slot;
            			
		StarSystem* starsystem;
		        	
		Npc* npc_owner;
		
		DriveTrailEffect* drive_jet; 
		ShieldEffect* shield;
		        	        	
		void updateInfo();
             	std::string returnProtectionStr();	
             		
		void renderKorpus() const;
             	void renderTurrels() const;
             	void renderShield() const;
             	
             	        	// WEPONS
        	int fire_delay, d_fire_delay;
        	std::vector<ItemSlot*> slot_weapon_pList;
        	std::vector<ItemSlot*> slot_weapon_equiped_pList;
        	std::vector<ItemSlot*> slot_weapon_reloaded_pList;
        	
             	Turrel turrel1;
        	Turrel turrel2;
        	Turrel turrel3;
        	Turrel turrel4;
        	Turrel turrel5;

};

void equip(Ship* pTo_ship);
Ship* shipGenerator(int race_id, int subtype_id, int size_id);

#endif 
