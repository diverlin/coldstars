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

struct KorpusData
{
	/* this data depends only on korpus and cannot be changed by artefacts/items */        
	KorpusData();

	unsigned int space;
	unsigned int armor;
	unsigned int protection; 
	unsigned int temperature;   

	unsigned int price;

	bool draw_turrels;
	float gui_scale;

        int slot_grapple_num;
        int slot_drive_num;
        int slot_protector_num;
        int slot_radar_num;
        int slot_scaner_num;
        int slot_freezer_num;
	int slot_weapon_num;
};

struct UnresolvedDataUniqueVehicle
{
	int parent_vehicleslot_id;
	std::string textureOb_gui_path; 	
};

class Vehicle : public BaseGameEntity
{   
    	public:
       	        Vehicle();
        	virtual ~Vehicle(); 
        	
                void SetNpc(Npc* owner_npc) { this->owner_npc = owner_npc; };
		void SetParentVehicleSlot(VehicleSlot* parent_vehicleslot) { this->parent_vehicleslot = parent_vehicleslot; };
		
                void SetWeaponComplex(WeaponComplex* weapon_complex) { this->weapon_complex = weapon_complex; };
                void SetDriveComplex(DriveComplex* drive_complex)    { this->drive_complex  = drive_complex; };
		void SetProtectionComplex(ProtectionComplex* protection_complex) { this->protection_complex = protection_complex; };
                                
                void SetKorpusData(KorpusData data_korpus) { this->data_korpus = data_korpus; };
                void SetGuiTextureOb(TextureOb* textureOb_gui) { this->textureOb_gui = textureOb_gui; };
        	void SetGuiRect(Rect rect) { kontur_rect = rect; };
        	
        	void SetColor(Color4f color) { this->color = color; }
        	        	
                void AddItemSlot(ItemSlot*, const Rect&); 
                bool AddItemToOtsec(BaseItem*);

                float GetVisionRadius() const { return propetries.radius; };
                
                WeaponComplex* GetWeaponComplex()         const { return weapon_complex; };
                DriveComplex* GetDriveComplex()           const { return drive_complex; };
                ProtectionComplex* GetProtectionComplex() const { return protection_complex; };
                
        	ItemSlot* GetRadarSlot()     const { return radar_slot; };
        	ItemSlot* GetScanerSlot()    const { return scaner_slot; };
        	ItemSlot* GetEnergizerSlot() const { return energizer_slot; };
        	ItemSlot* GetGrappleSlot()   const { return grapple_slot; };
        	ItemSlot* GetDroidSlot()     const { return droid_slot; };
        	ItemSlot* GetFreezerSlot()   const { return freezer_slot; };
        	ItemSlot* GetGateSlot()      const { return gate_slot; };

                Npc* GetOwnerNpc() const { return owner_npc; };
       	        ItemSlot* GetEmptyOtsecSlot();
       	        ItemSlot* GetCargoSlotWithGoods(int);
        	
        	const Rect& GetGuiRect() const { return kontur_rect; };
        	
        	void PostCreateInit();
        	
        	AbilitiesStatus ableTo;
                ShipPropetries propetries;
                KorpusData data_korpus;
                       	
        	void SelfRepairEvent();
        	bool ExternalRepairEvent();
        	                
        	void Hit(int, bool);

        	virtual void PostDeathUniqueEvent(bool); 
        	
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
        	
        	bool DockingEffect();
        	bool LaunchingEffect();
        	
        	void RenderInfo(float, float, float, float);
        	void RenderInfoInSpace(vec2f);
        	
        	void RenderRadarRange();
        	void RenderGrappleRange();        

                void GrappleMicroProgramm();               

        	
        	void RecalculateCollisionRadius();

	protected:
		virtual void UpdateInfo() = 0;
             	std::string returnProtectionStr();

        	WeaponComplex*     weapon_complex;
            	DriveComplex*      drive_complex;
        	ProtectionComplex* protection_complex;
                
		Npc* owner_npc;
             		
                void RenderGrappleTrail() const;
		void RenderKorpus() const;
             	void RenderTurrels() const;
             	void RenderDriveTrail() const;
          	void RenderShield() const;
        	
        	ItemSlot* radar_slot;
        	ItemSlot* scaner_slot;
        	ItemSlot* energizer_slot;
        	ItemSlot* grapple_slot;
        	ItemSlot* droid_slot;
        	ItemSlot* freezer_slot;
        
                ItemSlot* gate_slot;
                
                std::vector<ItemSlot*> slot_total_vec;
        	std::vector<ItemSlot*> slot_otsec_vec;
		        	
        	// KONTUR RECT 
        	Rect kontur_rect; 
                TextureOb* textureOb_gui;
                //                
                
                Color4f color;
                                
                VehicleSlot* parent_vehicleslot;
                
                UnresolvedDataUniqueVehicle data_unresolved_Vehicle;
                
                void SaveDataUniqueVehicle(boost::property_tree::ptree&, const std::string&) const;		
		void LoadDataUniqueVehicle(const boost::property_tree::ptree&);
		void ResolveDataUniqueVehicle();

        private:
             	void DropRandomItemToSpace();   
             	
        friend class GuiVehicle;
             	
};

#endif 
