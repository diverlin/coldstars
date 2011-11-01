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
                int* getpPlaceTypeId();
                int getArmor() const;
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

        	AbilitiesStatus ableTo;
                ShipPropetries propetries;
                KorpusData data_korpus;
                

        	Ship(TextureOb*, LifeData, IdData, KorpusData);
        	~Ship();    

         	void updatePosition();
                
        	void reloadWeapons();        
     		void selectWeapons();                                     
                     
                template <typename TARGET_TYPE>      
                void setWeaponsTarget(TARGET_TYPE*);     
       
        	void weaponsFire_TRUE(int timer);
        	void weaponsFire_FALSE(int timer);

        	void resetDeselectedWeaponTargets();                                          
        	void removeWeaponSlotDeadTargets();

        	void update_inSpace_inDynamic_TRUE();
        	void update_inSpace_inDynamic_FALSE();

        	void hit_TRUE(unsigned int _damage);
        	void hit_FALSE(unsigned int _damage);

        	void death_TRUE(); 
        	void death_FALSE(); 
        	
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

        	bool jumpingEvent();
        	bool dockingEvent();
        	bool launchingEvent();

		void updateRenderStuff();
		void render_inSpace() const;
		void render_atPlanet() const;
                
                void renderWeaponIcons() const;

        	void renderInfo(float _pos_x, float _pos_y, float _offset_x = 0, float _offset_y = 0);
        	void renderInfo();
        	        	
        	WeaponSelector weapon_selector; 
                
                bool repair();
          
        private:
        	LifeData data_life;
        	IdData   data_id;
                        
                Points points;
		InfoTable info;
		
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
             	
             	void dropRandomItemToSpace();
             	
                // WEPONS
        	int fire_delay, d_fire_delay;
        	std::vector<ItemSlot*> slot_weapon_pList;
        	std::vector<ItemSlot*> slot_weapon_equiped_pList;
        	std::vector<ItemSlot*> slot_weapon_reloaded_pList;
        	
             	Turrel* turrel1;
        	Turrel* turrel2;
        	Turrel* turrel3;
        	Turrel* turrel4;
        	Turrel* turrel5;

        	int place_type_id;
};

void equip(Ship* pTo_ship);
Ship* shipGenerator(int race_id, int subtype_id, int size_id);

#endif 
