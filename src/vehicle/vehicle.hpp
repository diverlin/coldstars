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


#ifndef VEHICLE_H
#define VEHICLE_H


class Vehicle : public BaseSpaceObject
{   
    	public:
                void setNpc(Npc*);
                void setKorpusData(KorpusData);
                void add(ItemSlot*);

                float getVisionRadius() const;
                
                WeaponComplex* getWeaponComplex() const;
                        	
                Navigator* getNavigator();
                Npc* getNpc();
       	        ItemSlot* getEmptyOtsecSlot();
       	        ItemSlot* getOtsecSlotWithGoods(int);
       	        
       	        Vehicle();
        	~Vehicle();  
        	
        	void postCreateInit();
        	
       	        //
       	        int getFunctionalSlotSubTypeId() const;    // return NONE_ID
       	        void bindSlot(ItemSlot*);		   // do nothing	
       	        void updateOwnerPropetries();		   // do nothing
       	               	        	
        	//######### KONTUR RECT 
        	int w_kontur, h_kontur;
        	Rect kontur_rect; 
                TextureOb* texOb_korpus;

        	//######### SLOT        
        	ItemSlot drive_slot;
        	ItemSlot bak_slot;
        	ItemSlot radar_slot;
        	ItemSlot scaner_slot;
        	ItemSlot energizer_slot;
        	ItemSlot grapple_slot;
        	ItemSlot protector_slot;
        	ItemSlot droid_slot;
        	ItemSlot freezer_slot;
                                                
        	std::vector<ItemSlot*> slot_total_vec;
        	std::vector<ItemSlot*> slot_otsec_vec;
        
        	ItemSlot gate_slot;

        	AbilitiesStatus ableTo;
                ShipPropetries propetries;
                KorpusData data_korpus;
                

  
               
        	void update_inSpace_inDynamic_TRUE();
        	void update_inSpace_inDynamic_FALSE();
       	
        	void droidRepair();
        	
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

        	void setMaxArmor();
        	void setMaxFuel();

        	bool jumpEvent();
        	bool dockEvent();
        	bool launchingEvent();

		void updateRenderStuff();
		void render_inSpace() const;
		void render_atPlanet() const;                


        	void renderInfo(float _pos_x, float _pos_y, float _offset_x = 0.0, float _offset_y = 0.0);
        	void renderInfo();
        	
        	void renderRadarRange();
        	void renderGrappleRange();

        	        	

                
                bool repair();
                
                void grappleScenario();
                void moveExternalyToPosition(vec2f);
                
                void updateDyingEffect_TRUE();
        	void updateDyingEffect_FALSE();
        	
        	void calcCollisionRadius();

         
        private:
            	Navigator* navigator;

            	TextureOb* texOb_slot;
     	
		Npc* npc_owner;
		
		TrailEffect* drive_trail; 
		ShieldEffect* shield;
		        	        	
		void updateInfo();
             	std::string returnProtectionStr();	
             		
                void renderGrappleTrail() const;
		void renderKorpus() const;
             	//void renderTurrels() const;
             	void renderDriveTrail() const;
          	void renderShield() const;
             	             	
             	void dropRandomItemToSpace();             	


        	WeaponComplex* weapon_complex;

};

void equip(Ship* pTo_ship);
Ship* shipGenerator(int race_id, int subtype_id, int size_id, int weapons_num);

#endif 
