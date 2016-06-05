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


#pragma once

#include <spaceobjects/SpaceObject.hpp>

#include <parts/WeaponComplex.hpp>
#include <parts/DriveComplex.hpp>
#include <parts/ProtectionComplex.hpp>

#include <descriptors/VehicleDescriptor.hpp>
#include <struct/VehiclePropetries.hpp>
#include <struct/VehicleNeeds.hpp>

#include <types/StatusTypes.hpp>

class VehicleSlot;
class Land; 
class Npc;
class GoodsPack;
class Container;
namespace item {
class Base;
}
class BaseEquipment;
class BaseParticleSystem;
class ShockWaveEffect;

//namespace jeti {
//class Renderer;
//}

struct UnresolvedDataVehicle
{
    int drive_complex_target_id;
    int drive_complex_action_id;

    int starsystem_hyper_id;
    int parent_vehicleslot_id;
    int land_id;
};


enum class VEHICLE_SPECIAL_ACTION_TYPE
{
    NONE_ID=0, INITIATE_DOCKING_ID, INITIATE_LAUNCHING_ID, INITIATE_JUMPIN_ID, INITIATE_JUMPOUT_ID
};


class Vehicle : public SpaceObject
{   
public:
    Vehicle();
    virtual ~Vehicle();

    [[deprecated("move to gui")]]
    void CreateDriveComplexTextureDependedStuff();
    [[deprecated("move to gui")]]
    void CreateProtectionComplexTextureDependedStuff();

    void SetGodMode(bool god_mode) { m_GodMode = god_mode; }
    void SetSpecialActionId(VEHICLE_SPECIAL_ACTION_TYPE special_action_id) { m_SpecialActionId = special_action_id; }
    void SetParentVehicleSlot(VehicleSlot* parent_vehicleslot) { m_ParentVehicleSlot = parent_vehicleslot; }

    void SetLand(Land* land) { m_Land = land; }

    void SetKorpusData(const VehicleDescriptor&);

    bool GetGodMode() const { return m_GodMode; }
    Land* const GetLand() const { return m_Land; }
    VEHICLE_SPECIAL_ACTION_TYPE GetSpecialActionId() const { return m_SpecialActionId; }

    VehicleSlot* const parentVehicleSlot() const { return m_ParentVehicleSlot; }

    const VehiclePropetries& properties() const { return m_properties; }
    const VehicleNeeds& needs() const { return m_Needs; }
    const VehicleDescriptor& GetVehicleDescriptor() const { return m_VehicleDescriptor; }

    virtual int givenExpirience() const override final;
    bool isSlotExists(TYPE::ENTITY) const;

    void addItemSlot(ItemSlot*);

    [[deprecated("ship swap items in different logic")]]
    bool GetAllItemsFromVehicle(Vehicle*);

    bool addItemToCargoSlot(item::Base*);
    bool manage(item::Base*);

    void ManageItemsInCargo();
    [[deprecated("move to ext")]]
    void sellItemsInCargo();

    [[deprecated("move to ext")]]
    bool sellItem(item::Base*);
    [[deprecated("move to ext")]]
    bool buyItem(item::Base*);

    bool unpackContainerItemToCargoSlot(Container*);

    int freeSpace() const { return m_properties.free_space; }
    int space() const { return m_VehicleDescriptor.space; }

    void BindOwnerNpc(Npc*);

    bool IsObjectWithinRadarRange(SpaceObject*) const;

    WeaponComplex& GetComplexWeapon() { return m_ComplexWeapon; }   // !!!
    DriveComplex& GetComplexDrive()   { return m_ComplexDrive; }
    ProtectionComplex& GetComplexProtector() { return m_ComplexProtector; }

    const WeaponComplex& GetComplexWeapon() const { return m_ComplexWeapon; }

    ItemSlot* const slotRadar()     const { return m_SlotRadar; }
    ItemSlot* const slotScaner()    const { return m_SlotScaner; }
    ItemSlot* const slotEnergizer() const { return m_SlotEnergizer; }
    ItemSlot* const slotGrapple()   const { return m_SlotGrapple; }
    ItemSlot* const slotDroid()     const { return m_SlotDroid; }
    ItemSlot* const slotFreezer()   const { return m_SlotFreezer; }

    Npc* const npc() const { return m_npc; }

    ItemSlot* const GetEmptyCargoSlot();
    GoodsPack* GetGoodsPack() const;

    void UpdateSpecialAction();
    virtual void UpdateInSpace(int, bool) = 0;

    virtual void remeberAgressor(Vehicle*);
    void hit(int) override;

    virtual void postDeathUniqueEvent(bool);

    void CheckNeedsInStatic();
    void ResolveNeedsInKosmoportInStatic();
    void UpdateAllFunctionalItemsInStatic();
    void IncreaseMass(int);
    void DecreaseMass(int);
    void UpdatePropertiesEnergy();
    void UpdatePropertiesFreeze();
    void UpdatePropertiesSpeed();
    void UpdatePropertiesFire();
    void UpdatePropertiesRadar();
    void UpdatePropertiesJump();
    void UpdatePropertiesProtection();
    void UpdatePropertiesRepair();
    void UpdatePropertiesScan();
    void UpdatePropertiesGrab();
    void UpdateArtefactInfluence();

    void HyperJumpEvent(StarSystem*);
    void DockingEvent();
    void LaunchingEvent();

    void UpdateSpecialEffect();
    void UpdateLockedItems();

    //        virtual void RenderStuffWhenFocusedInSpace(const jeti::Renderer&) override final;
    //        virtual void RenderInfoInSpace(const jeti::Renderer&, const glm::vec2&, float) override final;
    //        void RenderInfo(const glm::vec2&, int, int);

    //        void RenderRadarRange();
    //        void RenderGrappleRange();

    bool IsAbleToJumpTo(StarSystem*) const;

    bool IsArmorFull() const;
    int GetArmorMiss() const;
    void IncreaseArmor(int);

    bool IsFuelFull() const;
    int GetFuelMiss() const;

    void RepairKorpusOnAmount(int);

    void LockRandomItem(int);

    bool TryToConsumeEnergy(int);
    bool TryToGenerateEnergy(int);

    STATUS CheckGrabStatus() const;

    void TEST_DamageAndLockRandItems();
    void TEST_DropRandomItemToSpace();

    float dissipateRate() const;
    int criticalDamage() const;

protected:
    std::vector<ItemSlot*> m_SlotTotal_vec;

    ItemSlot* const fuctionalSlot(TYPE::ENTITY) const;
    ItemSlot* const freeArtefactSlot() const;
    ItemSlot* const cargoSlotWithGoods(TYPE::ENTITY);

    bool manageItem(item::Base*);
    bool manageFunctionEquipment(item::Base*);
#ifdef USE_MODULES
    bool ManageFunctionModule(item::BaseItem*);
#endif
#ifdef USE_ARTEFACTS
    bool ManageFunctionArtefact(item::BaseItem*);
#endif
    bool ManageFunctionGoodsPack(item::Base*);

    //        virtual void UpdateInfo() = 0;

    //        void RenderGrabTrail(const jeti::Renderer&) const;
    //        void RenderKorpus(const jeti::Renderer&);
    //        void RenderTurrels() const;
    //        void RenderDriveEffect(float scale, float parent_d_alpha = 0.0) const;
    //        void RenderShieldEffect(const jeti::Renderer&, float parent_d_alpha = 0.0) const;

    void UpdateGrappleMicroProgram_inDynamic();

    virtual void putChildrenToGarbage() const override;

    UnresolvedDataVehicle data_unresolved_Vehicle;

    void SaveData(boost::property_tree::ptree&, const std::string&) const;
    void LoadData(const boost::property_tree::ptree&);
    void ResolveData();

private:
    bool m_GodMode;
    VEHICLE_SPECIAL_ACTION_TYPE m_SpecialActionId;

    Npc* m_npc = nullptr;

    VehicleSlot* m_ParentVehicleSlot = nullptr;

    Land* m_Land = nullptr;

    ItemSlot* m_SlotRadar = nullptr;
    ItemSlot* m_SlotScaner = nullptr;
    ItemSlot* m_SlotEnergizer = nullptr;
    ItemSlot* m_SlotGrapple = nullptr;
    ItemSlot* m_SlotDroid = nullptr;
    ItemSlot* m_SlotFreezer = nullptr;

    std::vector<ItemSlot*> m_equipmentSlots;
    std::vector<ItemSlot*> m_artefactSlots;
    std::vector<ItemSlot*> m_cargoSlots;

    WeaponComplex     m_ComplexWeapon;
    DriveComplex      m_ComplexDrive;
    ProtectionComplex m_ComplexProtector;

    VehiclePropetries m_properties;
    VehicleNeeds m_Needs;
    VehicleDescriptor m_VehicleDescriptor;

    void DropRandomItemToSpace();
    bool MergeIdenticalGoods(item::Base*);

    friend class GuiVehicle;
    friend class GuiVehicle2;
};

std::string getVehicleSpecialActionStr(VEHICLE_SPECIAL_ACTION_TYPE);


