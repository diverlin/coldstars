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

#include "../spaceobjects/BaseGameEntity.hpp"
#include "../docking/VehicleSlot.hpp"
#include "../spaceobjects/WeaponComplex.hpp"
#include "../spaceobjects/DriveComplex.hpp"
#include "../spaceobjects/ProtectionComplex.hpp"

#include "../docking/BaseLand.hpp"
#include "../pilots/Npc.hpp"

struct VehicleKorpusData
{
	/* this data depends only on korpus and cannot be changed by artefacts/items */        
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

	VehicleKorpusData():
	space(0),
        armor(0),
        protection(0), 
        temperature(0),   
        
        price(0),
       
        draw_turrels(false),
        gui_scale(1.0f),
        
        slot_grapple_num(0),
        slot_drive_num(0),
        slot_protector_num(0),
        slot_radar_num(0),
        slot_scaner_num(0),
        slot_freezer_num(0),
	slot_weapon_num(0)	
	{}
};


struct VehiclePropetries
{    
	/* this data is changed during game play, the propetries depends on many factors */
	int free_space;
	
	int protection;
	int radius;
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
	

	VehiclePropetries():
	free_space(0),
	protection(0),
        radius(0),
        speed(0),
        hyper(0),
        repair(0),
        freeze(0),
        scan(0),        
        energy(0),
        temperature(0),
        average_damage(0),
        average_fire_radius(0) 
        {}
};

struct UnresolvedDataUniqueVehicle
{
	int parent_vehicleslot_id;
	int land_id;
	std::string textureOb_gui_path; 	
};

class Vehicle : public BaseGameEntity
{   
    	public:
       	        Vehicle();
        	virtual ~Vehicle(); 

		void SetSpecialActionId(int special_action_id) { this->special_action_id = special_action_id; };
		void SetParentVehicleSlot(VehicleSlot* parent_vehicleslot) { this->parent_vehicleslot = parent_vehicleslot; };
		
                void SetWeaponComplex(WeaponComplex* weapon_complex) { this->weapon_complex = weapon_complex; };
                void SetDriveComplex(DriveComplex* drive_complex)    { this->drive_complex  = drive_complex; };
		void SetProtectionComplex(ProtectionComplex* protection_complex) { this->protection_complex = protection_complex; };
                                
                void SetKorpusData(VehicleKorpusData data_korpus) { this->data_korpus = data_korpus; };
                void SetGuiTextureOb(TextureOb* textureOb_gui) { this->textureOb_gui = textureOb_gui; };
        	void SetGuiRect(Rect rect) { kontur_rect = rect; };
        	
        	void SetColor(Color4f color) { this->color = color; }
        	void SetLand(BaseLand* land) { this->land = land; };
        	        		
        	BaseLand* GetLand() const { return land; };
        	        					
                void AddItemSlot(ItemSlot*, const Rect&); 
                bool AddItemToCargoSlot(BaseItem*);
                bool UnpackContainerItemToCargoSlot(Container*);
                
                int GetFreeSpace() const { return propetries.free_space; };
                float GetVisionRadius() const { return propetries.radius; };

                void BindOwnerNpc(Npc*);
		bool IsObjectWithinRadarRange(BaseGameEntity*) const;
		                              
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
       	        ItemSlot* GetEmptyCargoSlot();
       	        ItemSlot* GetCargoSlotWithGoods(int);
        	
        	const Rect& GetGuiRect() const { return kontur_rect; };
        	
        	GoodsPack* GetGoodsPack() const;
        	
        	AbilitiesStatus ableTo;
                VehiclePropetries propetries;
                VehicleKorpusData data_korpus;
                       	
        	void SelfRepairEvent();
        	bool ExternalRepairEvent();
        	       
        	void UpdateSpecialAction();         
        	virtual void UpdateInSpace(int, bool) = 0;
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

        	void HyperJumpEvent();
        	void DockingEvent();
        	void LaunchingEvent();
        	
		void UpdateSpecialEffect();
        	
        	void RenderInfoInSpace(const vec2f&);
        	void RenderInfo(const vec2f&);
        	        	
        	void RenderRadarRange();
        	void RenderGrappleRange();        
        	
        	void RecalculateCollisionRadius();

		bool IsArmorFull() const;
		int GetArmorMiss() const;
		void BuyArmorAsMuchAsPossible();
		
		bool IsFuelFull() const;
		int GetFuelMiss() const;
		void BuyFuelAsMuchAsPossible();

	protected:
		int special_action_id;
	
		virtual void UpdateInfo() = 0;
             	std::string returnProtectionStr();

        	WeaponComplex*     weapon_complex;
            	DriveComplex*      drive_complex;
        	ProtectionComplex* protection_complex;
                
		Npc* owner_npc;

        	ItemSlot* radar_slot;
        	ItemSlot* scaner_slot;
        	ItemSlot* energizer_slot;
        	ItemSlot* grapple_slot;
        	ItemSlot* droid_slot;
        	ItemSlot* freezer_slot;
        
                ItemSlot* gate_slot;
                
                std::vector<ItemSlot*> slot_total_vec;
        	std::vector<ItemSlot*> slot_cargo_vec;
		        	
        	// KONTUR RECT 
        	Rect kontur_rect; 
                TextureOb* textureOb_gui;
                //                
                
                   	     	
   	     	BaseLand* land;
   	     	
                Color4f color;
                                
                VehicleSlot* parent_vehicleslot;
                             		
                void RenderGrappleTrail() const;
		void RenderKorpus() const;
             	void RenderTurrels() const;
             	void RenderDriveEffect(float parent_d_alpha = 0.0) const;
          	void RenderShieldEffect(float parent_d_alpha = 0.0) const;
        	                
        	void UpdateGrappleMicroProgram();       
        	                                
                UnresolvedDataUniqueVehicle data_unresolved_Vehicle;
                
                void SaveDataUniqueVehicle(boost::property_tree::ptree&, const std::string&) const;		
		void LoadDataUniqueVehicle(const boost::property_tree::ptree&);
		void ResolveDataUniqueVehicle();

        private:
             	void DropRandomItemToSpace();   
             	bool AddItemToEmptyCargoSlot(BaseItem*);
                bool MergeIdenticalGoods(BaseItem*);
                
                bool UpdateFadeInEffect();
        	bool UpdateFadeOutEffect();
             	
        friend class GuiVehicle;
             	
};

#endif 
