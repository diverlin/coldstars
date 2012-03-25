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


class Vehicle : public BaseGameEntity
{   
    	public:
       	        Vehicle();
        	virtual ~Vehicle(); 
        	
                void SetNpc(Npc*);
                void SetDriveComplex(DriveComplex*);
                void SetWeaponComplex(WeaponComplex*);
                void SetShieldEffect(ShieldEffect*);
                                
                void SetKorpusData(KorpusData);
                void SetGuiTextureOb(TextureOb*);
        	void SetGuiRect(Rect);
        	
                void Add(ItemSlot*);

                float GetVisionRadius() const;
                
                WeaponComplex* GetWeaponComplex() const;
                DriveComplex* GetDriveComplex() const;
                
        	ItemSlot* GetRadarSlot()     const;
        	ItemSlot* GetScanerSlot()    const;
        	ItemSlot* GetEnergizerSlot() const;
        	ItemSlot* GetGrappleSlot()   const;
        	ItemSlot* GetProtectorSlot() const;
        	ItemSlot* GetDroidSlot()     const;
        	ItemSlot* GetFreezerSlot()   const;
        	ItemSlot* GetGateSlot()   const;
        	
        	TextureOb* GetSlotTexOb() const;
        	                        	
                Npc* GetOwnerNpc() const;
       	        ItemSlot* GetEmptyOtsecSlot();
       	        ItemSlot* GetCargoSlotWithGoods(int);
        	
        	const Rect& GetGuiRect() const;
        	
        	void PostCreateInit();
        	
                // needs when vehicle is grabbed by other vehicle 
       	        //int GetFunctionalSlotSubTypeId() const;  // return NONE_ID
       	        //void BindSlot(ItemSlot*);		   // do nothing	
       	        //void UpdateOwnerPropetries();		   // do nothing

        	AbilitiesStatus ableTo;
                ShipPropetries propetries;
                KorpusData data_korpus;
                       	
        	void SelfRepairEvent();
        	bool ExternalRepairEvent();
        	                
        	void Hit(int, bool);

        	virtual void postDeathUniqueEvent(bool); 
        	
        	void UpdateAllPropertiesAndAbilities();
             		void RecalculateMass();
             		void UpdateFireAbility();
             		void UpdateRadarAbility();
             		void UpdateDriveAbility();
             		void UpdateJumpAbility();
             		void UpdateEnergyAbility();
             		void UpdateProtectionAbility();
             		void UpdateRepairAbility();
             		void UpdateFreezeAbility();
             		void UpdateGrabAbility();
             		void UpdateScanAbility();

        	void SetMaxArmor();
        	void SetMaxFuel();

        	void HyperJumpEvent();
        	void DockingEvent();
        	void LaunchingEvent();

        	void RenderInfo(float, float, float, float);
        	void RenderInfo_inSpace(vec2f);
        	
        	void RenderRadarRange();
        	void RenderGrappleRange();        	        	

                void GrappleMicroProgramm();               

        	
        	void RecalculateCollisionRadius();

	protected:
		virtual void updateInfo() = 0;
             	std::string returnProtectionStr();
            	DriveComplex* drive_complex;
     	
		Npc* owner_npc;
		
		ShieldEffect* shield;
             		
                void RenderGrappleTrail() const;
		void RenderKorpus() const;
             	void RenderTurrels() const;
             	void RenderDriveTrail() const;
          	void RenderShield() const;
             	
        	WeaponComplex* weapon_complex;
        	
        	ItemSlot* radar_slot;
        	ItemSlot* scaner_slot;
        	ItemSlot* energizer_slot;
        	ItemSlot* grapple_slot;
        	ItemSlot* protector_slot;
        	ItemSlot* droid_slot;
        	ItemSlot* freezer_slot;
        
                ItemSlot* gate_slot;
                
                std::vector<ItemSlot*> slot_total_vec;
        	std::vector<ItemSlot*> slot_otsec_vec;
        	
        	// KONTUR RECT 
        	Rect kontur_rect; 
                TextureOb* texOb_korpus;
                //                
                		
        private:
               	TextureOb* texOb_slot;
             	void DropRandomItemToSpace();   
             	
        friend class GuiVehicle;
             	
};

void equip(Vehicle*);

#endif 
