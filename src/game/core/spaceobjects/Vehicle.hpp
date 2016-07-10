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


enum class VEHICLE_SPECIAL_ACTION_TYPE {
    NONE_ID=0, INITIATE_DOCKING_ID, INITIATE_LAUNCHING_ID, INITIATE_JUMPIN_ID, INITIATE_JUMPOUT_ID
};


class Vehicle : public SpaceObject
{   
public:
    Vehicle();
    virtual ~Vehicle();

    // wepon complex interface
    void fire(int, float);
    void setWeaponTarget(SpaceObject* object, ItemSlot* slot = nullptr);
    void prepareWeapons();
    int guessDamage(int dist);
    //\ weapon complex interface

    [[deprecated("move to gui")]]
    void CreateDriveComplexTextureDependedStuff();
    [[deprecated("move to gui")]]
    void CreateProtectionComplexTextureDependedStuff();

    void setGodMode(bool god_mode) { m_godMode = god_mode; }
    void SetSpecialActionId(VEHICLE_SPECIAL_ACTION_TYPE special_action_id) { m_specialActionId = special_action_id; }
    void SetParentVehicleSlot(VehicleSlot* parent_vehicleslot) { m_parentVehicleSlot = parent_vehicleslot; }

    void setLand(Land* land) { m_Land = land; }

    void setKorpusData(const VehicleDescriptor&);

    bool godMode() const { return m_godMode; }
    Land* const land() const { return m_Land; }
    VEHICLE_SPECIAL_ACTION_TYPE GetSpecialActionId() const { return m_specialActionId; }

    VehicleSlot* const parentVehicleSlot() const { return m_parentVehicleSlot; }

    const VehiclePropetries& properties() const { return m_properties; }
    const VehicleNeeds& needs() const { return m_needs; }
    const VehicleDescriptor& vehicleDescriptor() const { return m_vehicleDescriptor; }

    virtual int givenExpirience() const override final;
    bool isSlotTypePresent(type::entity) const;

    void addItemSlot(ItemSlot*);

    [[deprecated("ship swap items in different logic")]]
    bool grabItemsFromVehicle(Vehicle*);

    bool addItemToCargoSlot(item::Base*);
    bool manage(item::Base*);
    bool checkManage(const type::entity&);

    void manageItemsInCargo();
    [[deprecated("move to ext")]]
    void sellItemsInCargo();

    [[deprecated("move to ext")]]
    bool sellItem(item::Base*);
    [[deprecated("move to ext")]]
    bool buyItem(item::Base*);

    bool unpackContainerItemToCargoSlot(Container*);

    int freeSpace() const { return m_properties.free_space; }
    int space() const { return m_vehicleDescriptor.space; }

    void bindNpc(Npc*);

    bool isObjectVisible(SpaceObject*) const;

    WeaponComplex& weaponComplex() { return m_weaponComplex; }   // !!!
    const WeaponComplex& weaponComplex() const { return m_weaponComplex; }
    DriveComplex& driveComplex()   { return m_driveComplex; }
    ProtectionComplex& protectorComplex() { return m_protectorComplex; }

    ItemSlot* const radarSlot()     const { return m_radarSlot; }
    ItemSlot* const scanerSlot()    const { return m_scanerSlot; }
#ifdef USE_EXTRA_EQUIPMENT
    ItemSlot* const energizerSlot() const { return m_energizerSlot; }
    ItemSlot* const freezerSlot()   const { return m_freezerSlot; }
#endif // USE_EXTRA_EQUIPMENT
    ItemSlot* const grappleSlot()   const { return m_grappleSlot; }
    ItemSlot* const droidSlot()     const { return m_droidSlot; }

    Npc* const npc() const { return m_npc; }

    ItemSlot* const freeCargoSlot();
    GoodsPack* goodsPack() const;

    void UpdateSpecialAction();
    virtual void UpdateInSpace(int, bool) = 0;

    virtual void remeberAgressor(Vehicle*);
    void hit(int) override;

    virtual void _postDeathUniqueEvent(bool);

    void CheckNeedsInStatic();
    void ResolveNeedsInKosmoportInStatic();
    void UpdateAllFunctionalItemsInStatic();

    bool dropItemToSpace(const type::entity&);

protected:
    void _increaseMass(int);
    void _decreaseMass(int);
    void _updatePropEnergy();
    void _updatePropFreeze();
    void _updatePropSpeed();
    void _updatePropFire();
    void _updatePropRadar();
    void _updatePropJump();
    void _updatePropProtection();
    void _updatePropRepair();
    void _updatePropScan();
    void _updatePropGrab();
    void _updateArtefactInfluence();
    friend class ItemSlot;
public:

    void HyperJumpEvent(Starsystem*);
    void DockingEvent();
    void LaunchingEvent();

    void UpdateSpecialEffect();
    void UpdateLockedItems();

    //        virtual void RenderStuffWhenFocusedInSpace(const jeti::Renderer&) override final;
    //        virtual void RenderInfoInSpace(const jeti::Renderer&, const glm::vec2&, float) override final;
    //        void RenderInfo(const glm::vec2&, int, int);

    //        void RenderRadarRange();
    //        void RenderGrappleRange();

    bool isAbleToJumpTo(Starsystem*) const;

    bool isArmorFull() const;
    int armorMiss() const;
    void increaseArmor(int);
    void repairKorpus(int);

    bool isFuelFull() const;
    int fuelMiss() const;

    void lockRandomItem(int);

    bool tryConsumeEnergy(int);
    bool tryGenerateEnergy(int);

    STATUS CheckGrabStatus() const;

    float dissipateRate() const;
    int criticalDamage() const;

protected:
    std::vector<ItemSlot*> m_slots;

    ItemSlot* const _functionalSlot(const type::entity&) const;
    ItemSlot* const _freeArtefactSlot() const;
    ItemSlot* const _cargoSlotWithGoods(type::entity);

    bool _installItem(item::Base*);
    bool _installEquipment(item::Base*);
#ifdef USE_MODULES
    bool installModule(item::BaseItem*);
#endif // USE_MODULES
#ifdef USE_ARTEFACTS
    bool installArtefact(item::BaseItem*);
#endif // USE_ARTEFACTS
    bool _installGoodsPack(item::Base*);

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
    bool m_godMode;
    VEHICLE_SPECIAL_ACTION_TYPE m_specialActionId;

    Npc* m_npc = nullptr;

    VehicleSlot* m_parentVehicleSlot = nullptr;

    Land* m_Land = nullptr;

    ItemSlot* m_radarSlot = nullptr;
    ItemSlot* m_scanerSlot = nullptr;
#ifdef USE_EXTRA_EQUIPMENT
    ItemSlot* m_energizerSlot = nullptr;
    ItemSlot* m_freezerSlot = nullptr;
#endif // USE_EXTRA_EQUIPMENT
    ItemSlot* m_grappleSlot = nullptr;
    ItemSlot* m_droidSlot = nullptr;


    std::vector<ItemSlot*> m_equipmentSlots;
    std::vector<ItemSlot*> m_artefactSlots;
    std::vector<ItemSlot*> m_cargoSlots;

    WeaponComplex     m_weaponComplex;
    DriveComplex      m_driveComplex;
    ProtectionComplex m_protectorComplex;

    VehiclePropetries m_properties;
    VehicleNeeds m_needs;
    VehicleDescriptor m_vehicleDescriptor;

    [[deprecated("use predetermentistic way")]]
//    void __dropRandomItemToSpace();
    bool __mergeIdenticalGoods(item::Base*);

    Container* __wrapItemToContainer(item::Base*);
    bool _checkInstallEquipment(const type::entity&);
    ItemSlot* const _freeFunctionalSlot(const type::entity&) const;

    friend class GuiVehicle;
    friend class GuiVehicle2;
};

std::string getVehicleSpecialActionStr(VEHICLE_SPECIAL_ACTION_TYPE);


