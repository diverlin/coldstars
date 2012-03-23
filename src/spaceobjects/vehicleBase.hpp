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


#ifndef VEHICLEBASE_H
#define VEHICLEBASE_H


class VehicleBase : public BaseGameEntity
{   
    	public:
       	        VehicleBase();
        	virtual ~VehicleBase(); 
        	
                void setNpc(Npc*);
                void setKorpusData(KorpusData);
        	
                void add(ItemSlot*);

                float getVisionRadius() const;
                
                WeaponComplex* getWeaponComplex() const;
                DriveComplex* getDriveComplex() const;
                
        	ItemSlot* getRadarSlot()     const;
        	ItemSlot* getScanerSlot()    const;
        	ItemSlot* getEnergizerSlot() const;
        	ItemSlot* getGrappleSlot()   const;
        	ItemSlot* getProtectorSlot() const;
        	ItemSlot* getDroidSlot()     const;
        	ItemSlot* getFreezerSlot()   const;
        	ItemSlot* getGateSlot()   const;
        	
        	TextureOb* getSlotTexOb() const;
        	Rect getKonturRect() const;
        	                        	
                Npc* getNpc();
       	        ItemSlot* getEmptyOtsecSlot();
       	        ItemSlot* getOtsecSlotWithGoods(int);
        	
        	void postCreateInit();
        	
                //
       	        int getFunctionalSlotSubTypeId() const;    // return NONE_ID
       	        void bindSlot(ItemSlot*);		   // do nothing	
       	        void updateOwnerPropetries();		   // do nothing
       	               	        	
        	//######### KONTUR RECT 
        	int w_kontur, h_kontur;
        	Rect kontur_rect; 
                TextureOb* texOb_korpus;

        	std::vector<ItemSlot*> slot_total_vec;
        	std::vector<ItemSlot*> slot_otsec_vec;
        
        	ItemSlot* gate_slot;

        	AbilitiesStatus ableTo;
                ShipPropetries propetries;
                KorpusData data_korpus;
                       	
        	void droidRepair();
        	
        	void hit(int, bool);

        	virtual void postDeathUniqueEvent(bool); 
        	
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

        	void jumpEvent();
        	void dockEvent();
        	void launchingEvent();

		void updateRenderStuff();      


        	void renderInfo(float _pos_x, float _pos_y, float _offset_x, float _offset_y);
        	void renderInfo_inSpace(vec2f);
        	
        	void renderRadarRange();
        	void renderGrappleRange();        	        	

                
                bool repair();
                
                void grappleScenario();                

        	
        	void calcCollisionRadius();

	protected:
		virtual void updateInfo() = 0;
             	std::string returnProtectionStr();
            	DriveComplex* drive_complex;
     	
		Npc* npc_owner;
		
		TrailEffect* drive_trail; 
		ShieldEffect* shield;
             		
                void renderGrappleTrail() const;
		void renderKorpus() const;
             	void renderTurrels() const;
             	void renderDriveTrail() const;
          	void renderShield() const;
             	
        	WeaponComplex* weapon_complex;
        	
        	ItemSlot* radar_slot;
        	ItemSlot* scaner_slot;
        	ItemSlot* energizer_slot;
        	ItemSlot* grapple_slot;
        	ItemSlot* protector_slot;
        	ItemSlot* droid_slot;
        	ItemSlot* freezer_slot;
        	
        private:
               	TextureOb* texOb_slot;
             	void dropRandomItemToSpace();   
             	
};

void equip(VehicleBase*);

#endif 
