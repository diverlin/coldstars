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
                void setStarSystem(StarSystem*);
                void setNpc(Npc*);
                void setPlaceTypeId(int);
 
                Points* getPoints();
                Navigator* getNavigator();
                StarSystem* getStarSystem();
                Npc* getNpc();
                int getPlaceTypeId() const;
                int getTypeId() const;
                   
              
        	bool is_alive, is_dying, is_explosed;
        	int type_id, id;

        	int dying_time;
        	
		bool render_TURRELS;
		
        	bool in_SPACE;


        	TextureOb* texOb;

        	int size;
        	float collision_radius;

        	int w_orig, h_orig;

               

        	int space;
        	int armor_max;
        	int armor;
        	int korpus_protection;
        	int nominal_temperature;

        	int price;


        	//######### KONTUR RECT 
        	int w_kontur, h_kontur;
        	Rect kontur_rect; 


        	//######### SLOT
        	int total_weapon_slot_num;
        	ItemSlot weapon_slot1;
        	ItemSlot weapon_slot2;
        	ItemSlot weapon_slot3;
        	ItemSlot weapon_slot4;
        	ItemSlot weapon_slot5;
        
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




        	// simplification
        	int average_damage;
        	int average_fire_radius;


        	Ship(TextureOb* _texOb, 
        	     int _max_weapons, 
        	     bool _grapple_INHIBIT, 
        	     int _space, 
        	     int _armor_max, 
        	     int _protection, 
        	     int _nominal_temperature);
        	     
        	~Ship();    

         	void updatePosition();

        	void reloadAllWeapons();
        
     		void selectWeapons();                                     
                     
                template <typename TARGET_TYPE>      
                void setWeaponsTarget(TARGET_TYPE*);     
       
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

        	void renderInfo(float _pos_x, float _pos_y, float _offset_x = 0, float _offset_y = 0);
        	
        	float pos_z;
        	
        	WeaponSelector weapon_selector; 
                                          		
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

        	int place_type_id;
};

void equip(Ship* pTo_ship);
Ship* shipGenerator(int race_id, int subtype_id, int size_id);

#endif 
