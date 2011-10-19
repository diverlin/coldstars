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
        /* this structure explain hat feature are avaliable for ship */ 
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


struct KorpusData
{
        /* this data depends only on korpus and cannot be changed by artefacts/items */
        unsigned int protection; 
        unsigned int space;
        unsigned int armor;
        unsigned int temperature;   //???
        
        unsigned int price;
        
        unsigned int size_id;
        float collision_radius;
        
        bool inhibit_GRAPPLE;
        bool render_TURRELS;
        unsigned int weapon_slot_num;
};


struct ShipPropetries
{       
        // this data is changed during game play, the propetries depends on many factors
        int armor;
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
        
        // simplification
        int average_damage;
        int average_fire_radius;
};

    
class WeaponSelector
{
	public:
    		bool slot_1;
     		bool slot_2;
     		bool slot_3;
     		bool slot_4;
     		bool slot_5;
     	
		void setAll(bool status)
		{
			slot_1 = status;
     			slot_2 = status;
     			slot_3 = status;
     			slot_4 = status;
     			slot_5 = status;
		}
};


     		


class Ship
{   
    	public:
                void setStarSystem(StarSystem*);
                void setNpc(Npc*);
                void setPlaceTypeId(int);
                 
                int getTypeId() const;
                int getId() const;
                int getPlaceTypeId() const;
                
                bool getAlive() const;
                bool* getpAlive();
                int getCollisionRadius() const;
                
                Points* getPoints();
                Navigator* getNavigator();
                StarSystem* getStarSystem();
                Npc* getNpc();
       	
        	//######### KONTUR RECT 
        	int w_kontur, h_kontur;
        	Rect kontur_rect; 
                TextureOb* texOb_korpus;

        	//######### SLOT
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
                                                
        	std::vector<ItemSlot*> slot_total_pList;
        	std::vector<ItemSlot*> slot_otsec_pList;
        
        	ItemSlot gate_slot;

        	Abilities ableTo;
        	NeedsToDo needsToDo;
                ShipPropetries propetries;
                KorpusData korpus_data;
                

        	Ship(TextureOb* _texOb, KorpusData _korpusData);
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
        	bool dockingEvent();
        	bool launchingEvent();
        	//// docking/launching

		void updateRenderStuff();
		void render_inSpace() const;
		void render_atPlanet() const;
                
                void renderWeaponIcons() const;

        	void renderInfo(float _pos_x, float _pos_y, float _offset_x = 0, float _offset_y = 0);
        	void renderInfo();
        	        	
        	WeaponSelector weapon_selector; 
          
        private:
                bool is_alive, is_dying, is_explosed;
                int type_id, id;
                
                int dying_time;
                        
                float angle_inD;
                Points points;
		InfoTable info;
		
        	std::vector<vec2f*> turrel_center_pList;

            	Navigator* navigator;
            	
                TextureOb* texOb;
            	TextureOb* texOb_slot;
            			
		StarSystem* starsystem;
		        	
		Npc* npc_owner;
		
		TrailEffect* drive_trail; 
		ShieldEffect* shield;
		        	        	
		void updateInfo();
             	std::string returnProtectionStr();	
             		
		void renderKorpus() const;
             	void renderTurrels() const;
             	void renderDriveTrail() const;
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
