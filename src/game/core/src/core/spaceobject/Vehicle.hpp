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

#include <core/spaceobject/SpaceObject.hpp>

#include <core/part/WeaponComplex.hpp>
#include <core/part/DriveComplex.hpp>
#include <core/part/ProtectionComplex.hpp>
#include <core/part/GrappleComplex.hpp>

#include <core/struct/VehicleNeeds.hpp>

#include <core/type/StatusType.hpp>

#include <core/common/unittest.hpp>

class GoodsPack;

namespace descriptor {
class VehicleDescr;
} // namespace descriptor

namespace model {
class Vehicle;
class Container;
class StarSystem;
class Item;
} // namespace model

namespace core {

class VehicleSlot;

} // namespace core

class Equipment;
class BaseParticleSystem;
class ShockWaveEffect;

//struct UnresolvedDataVehicle
//{
//    int drive_complex_target_id;
//    int drive_complex_action_id;

//    int starsystem_hyper_id;
//    int parent_vehicleslot_id;
//    int land_id;
//};


enum class VEHICLE_SPECIAL_ACTION_TYPE {
    NONE=0, INITIATE_DOCKING, INITIATE_LAUNCHING, INITIATE_JUMPIN, INITIATE_JUMPOUT
};

const int VISIBLE_DISTANCE_WITHOUT_RADAR = 200;

namespace core {

class ItemSlot;

namespace control {

class Container;
class Npc;
class Item;
class Land;

class Vehicle : public SpaceObject
{
public:
    struct Propetries
    {
        int free_space = 0;

        int protection = 0;
        int radar = VISIBLE_DISTANCE_WITHOUT_RADAR;
        float speed = 0;  // depends on mass and drive

        int energy = 0;
        int hyper = 0;  // depends on drive and bak
        //int fuel = 0;   // depends on bak
        int repair = 0; // depends on droid
        int freeze = 0; // depends on freezer
        int scan = 0;   // depends on scaner

        int grab_strength = 0;
        int grab_radius = 0;

        int temperature = 0;

        int artefact_gravity = 0;
        int artefact_protection = 0;

        // simplification
        int total_damage = 0;
        int fire_radius_min = 0;
        int fire_radius_max = 0;

        bool equipment_radar = false;
        bool shield_effect_enabled = false;
        bool hibernate_mode_enabled = false;
        bool draw_decors = true;
    };

public:
    Vehicle(descriptor::VehicleDescr*, model::Vehicle*);
    ~Vehicle() override;

    bool canRadarObject(SpaceObject* ob) const;

    // good
    void dock(SpaceObject*);
    void grab(SpaceObject*);
    void navigate(SpaceObject*);
    void navigate(const meti::vec3&);

    bool mount(Item*);
    bool load(Item*);
    bool manage(Item*);
    bool remove(Item*);

    core::complex::Weapon& weapons() { return m_weapon_complex; }
    const core::complex::Drive& navigator() const { return m_drive_complex; }
    core::complex::Drive& navigator() { return m_drive_complex; }
    //

    void resetTargets();

    [[deprecated("move to gui")]]
    void CreateDriveComplexTextureDependedStuff();
    [[deprecated("move to gui")]]
    void CreateProtectionComplexTextureDependedStuff();

    void setGodMode(bool god_mode) { m_godMode = god_mode; }
    void SetSpecialActionId(VEHICLE_SPECIAL_ACTION_TYPE special_action_id) { m_specialActionId = special_action_id; }
    void setParentVehicleSlot(VehicleSlot* parent_vehicleslot) { m_parentVehicleSlot = parent_vehicleslot; }

    void setLand(Land* land);

    void setKorpusData(descriptor::VehicleDescr*);

    bool godMode() const { return m_godMode; }
    Land* land() const { return m_Land; }
    VEHICLE_SPECIAL_ACTION_TYPE GetSpecialActionId() const { return m_specialActionId; }

    VehicleSlot* parentVehicleSlot() const { return m_parentVehicleSlot; }

    const Propetries& properties() const { return m_properties; }
    VehicleNeeds& needs() { return m_needs; }

    descriptor::VehicleDescr* descriptor() const { return m_descriptor_vehicle; }
    model::Vehicle* model() const { return m_model_vehicle; }

    virtual int givenExpirience() const override final;
    bool isSlotTypePresent(const entity::Type&) const;

    void addItemSlot(ItemSlot*);

    [[deprecated("ship swap items in different logic")]]
    bool grabItemsFromVehicle(Vehicle*);

    bool isSlotFree(const place::Type&) const;
    bool checkManage(const core::Id&);

    void manageItemsInCargo();
    [[deprecated("move to ext")]]
    void sellItemsInCargo();

    [[deprecated("move to ext")]]
    bool sellItem(Item*);
    [[deprecated("move to ext")]]
    bool buyItem(Item*);

    bool unpackContainerItemToCargoSlot(Container*);

    int freeSpace() const;
    int space() const;

    void bindNpc(control::Npc*);

    bool isObjectVisible(SpaceObject*) const;

public:
    [[warning("used only for tests")]]
    std::vector<ItemSlot*> bakSlots() const { return m_drive_complex.bakSlots(); }
    std::vector<ItemSlot*> driveSlots() const { return m_drive_complex.driveSlots(); }
    std::vector<ItemSlot*> radarSlots() const { return m_radarSlots; }
    std::vector<ItemSlot*> scanerSlots() const { return m_scanerSlots; }
#ifdef USE_EXTRA_EQUIPMENT
    //    ItemSlot* energizerSlot() const { return m_energizerSlot; }
    //    ItemSlot* freezerSlot()   const { return m_freezerSlot; }
#endif // USE_EXTRA_EQUIPMENT
    std::vector<ItemSlot*> grappleSlots() const { return m_grapple_complex.grappleSlots(); }
    std::vector<ItemSlot*> droidSlots() const { return m_droidSlots; }
    std::vector<ItemSlot*> protectorSlots() const { return m_protector_complex.protectorSlots(); }

    std::vector<ItemSlot*> weaponSlots() const { return m_weapon_complex.weaponSlots(); }
    std::vector<ItemSlot*> cargoSlots() const { return m_cargoSlots; }

private:
    void __updateSpecialAction();

public:
    control::Npc* npc() const { return m_npc; }

    GoodsPack* goodsPack() const;

    virtual void update(int) = 0;

    void hit(int, SpaceObject* agressor = nullptr) override;

    virtual void _postDeathUniqueEvent(bool);

    void checkNeedsInStatic();
    void resolveNeedsInKosmoportInStatic();
    void updateAllFunctionalItemsInStatic();

private:
    void __increaseMass(int);
public:
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

protected:
    //    void _dockingEvent();

public:
    //    void process();

    void HyperJumpEvent(model::StarSystem*);
    //    void LaunchingEvent();

    void UpdateSpecialEffect();
    void UpdateLockedItems();

    //        virtual void RenderStuffWhenFocusedInSpace(const jeti::Renderer&) override final;
    //        virtual void RenderInfoInSpace(const jeti::Renderer&, const glm::vec2&, float) override final;
    //        void RenderInfo(const glm::vec2&, int, int);

    //        void RenderRadarRange();
    //        void RenderGrappleRange();

    bool isAbleToJumpTo(model::StarSystem*) const;

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

    float adjustDissipateFilter() const;

    std::vector<ItemSlot*> slots() const
    {
        std::vector<ItemSlot*> slots;
        for (auto it: m_slots) {
            slots.push_back(it.second);
        }
        return slots;
    }

private:
    void __updateFreeSpace();
    //    bool __addItemToCargo(Item*);
    ceti::pack<control::Item*> __items() const;

protected:
    descriptor::VehicleDescr* m_descriptor_vehicle = nullptr;
    model::Vehicle* m_model_vehicle = nullptr;

    ItemSlot* _freeArtefactSlot() const;
    ItemSlot* _cargoSlotWithGoods(place::Type);

#ifdef USE_MODULES
    bool installModule(Item*);
#endif // USE_MODULES
#ifdef USE_ARTEFACTS
    bool installArtefact(Item*);
#endif // USE_ARTEFACTS
    bool _installGoodsPack(Item*);

    //        virtual void UpdateInfo() = 0;

    //        void RenderGrabTrail(const jeti::Renderer&) const;
    //        void RenderKorpus(const jeti::Renderer&);
    //        void RenderTurrels() const;
    //        void RenderDriveEffect(float scale, float parent_d_alpha = 0.0) const;
    //        void RenderShieldEffect(const jeti::Renderer&, float parent_d_alpha = 0.0) const;

    void UpdateGrappleMicroProgram_inDynamic();

protected:
    void _putNpcToGarbage() const;
    void _putItemsToGarbage() const;

private:
    bool m_godMode = false;
    VEHICLE_SPECIAL_ACTION_TYPE m_specialActionId = VEHICLE_SPECIAL_ACTION_TYPE::NONE;

    control::Npc* m_npc = nullptr;

    VehicleSlot* m_parentVehicleSlot = nullptr;

    Land* m_Land = nullptr;

    std::vector<ItemSlot*> m_radarSlots;
    std::vector<ItemSlot*> m_scanerSlots;
#ifdef USE_EXTRA_EQUIPMENT
    ItemSlot* m_energizerSlot = nullptr;
    ItemSlot* m_freezerSlot = nullptr;
#endif // USE_EXTRA_EQUIPMENT
    std::vector<ItemSlot*> m_droidSlots;

    std::vector<ItemSlot*> m_equipmentSlots;
    std::vector<ItemSlot*> m_artefactSlots;
    std::vector<ItemSlot*> m_cargoSlots;

    Propetries m_properties;
    VehicleNeeds m_needs;
    core::complex::Weapon m_weapon_complex;
    core::complex::Drive m_drive_complex;
    core::complex::Protector m_protector_complex;
    core::complex::Grapple m_grapple_complex;

    std::map<int, ItemSlot*> m_slots;

    [[deprecated("use predetermentistic way")]]
    //    void __dropRandomItemToSpace();
    bool __mergeIdenticalGoods(Item*);

    Container* __wrapItemToContainer(Item*);
    bool _checkInstallEquipment(const core::Id&);

    std::vector<ItemSlot*> __equipedAndFunctionalSlots(const std::vector<ItemSlot*>&);
    void __createSlots(descriptor::VehicleDescr*);

    bool __manage(Item*);
    bool __insertItem(ItemSlot*, Item*);
    ItemSlot* __itemSlot(int) const;
    ItemSlot* __freeCargoSlot();

    bool __installItem(Item*);
    bool __installEquipment(Item*);
    ItemSlot* __freeFunctionalSlot(const SlotType&) const;

    std::vector<ItemSlot*> __equipedSlotsByType(const SlotType&);

    void __loadModel();
    void __loadItemsFromModel();

    void __putChildrenToGarbage() const override;
};


} // namespace control
} // namespace core























//class Vehicle : public SpaceObject
//{
//public:
//    Vehicle();
//    virtual ~Vehicle();

//    // wepon complex interface
//    void fire(int, float);
//    void setWeaponTarget(SpaceObject* object, ItemSlot* slot = nullptr);
//    void prepareWeapons();
//    int guessDamage(int dist);
//    //\ weapon complex interface

//    [[deprecated("move to gui")]]
//    void CreateDriveComplexTextureDependedStuff();
//    [[deprecated("move to gui")]]
//    void CreateProtectionComplexTextureDependedStuff();

//    void setGodMode(bool god_mode) { m_godMode = god_mode; }
//    void SetSpecialActionId(VEHICLE_SPECIAL_ACTION_TYPE special_action_id) { m_specialActionId = special_action_id; }
//    void SetParentVehicleSlot(VehicleSlot* parent_vehicleslot) { m_parentVehicleSlot = parent_vehicleslot; }

//    void setLand(Land* land) { m_Land = land; }

//    void setKorpusData(descriptor::Vehicle*);

//    bool godMode() const { return m_godMode; }
//    Land* const land() const { return m_Land; }
//    VEHICLE_SPECIAL_ACTION_TYPE GetSpecialActionId() const { return m_specialActionId; }

//    VehicleSlot* const parentVehicleSlot() const { return m_parentVehicleSlot; }

//    const VehiclePropetries& properties() const { return m_properties; }
//    const VehicleNeeds& needs() const { return m_needs; }
//    descriptor::Vehicle* vehicleDescriptor() const { return m_vehicleDescriptor; }

//    virtual int givenExpirience() const override final;
//    bool isSlotTypePresent(const entity::Type&) const;

//    void addItemSlot(ItemSlot*);

//    [[deprecated("ship swap items in different logic")]]
//    bool grabItemsFromVehicle(Vehicle*);

//    bool addItemToCargoSlot(Base*);
//    bool manage(Base*);

//    bool isSlotFree(const entity::Type&) const;
//    bool checkManage(const core::Id&);

//    void manageItemsInCargo();
//    [[deprecated("move to ext")]]
//    void sellItemsInCargo();

//    [[deprecated("move to ext")]]
//    bool sellItem(Base*);
//    [[deprecated("move to ext")]]
//    bool buyItem(Base*);

//    bool unpackContainerItemToCargoSlot(Container*);

//    int freeSpace() const { return m_properties.free_space; }
//    int space() const { return m_vehicleDescriptor.space; }

//    void bindNpc(Npc*);

//    bool isObjectVisible(SpaceObject*) const;

//    WeaponComplex& weaponComplex() { return m_weaponComplex; }   // !!!
//    const WeaponComplex& weaponComplex() const { return m_weaponComplex; }
//    DriveComplex& driveComplex()   { return m_driveComplex; }
//    ProtectionComplex& protectorComplex() { return m_protectorComplex; }

//    ItemSlot* const radarSlot()     const { return m_radarSlot; }
//    ItemSlot* const scanerSlot()    const { return m_scanerSlot; }
//#ifdef USE_EXTRA_EQUIPMENT
//    ItemSlot* const energizerSlot() const { return m_energizerSlot; }
//    ItemSlot* const freezerSlot()   const { return m_freezerSlot; }
//#endif // USE_EXTRA_EQUIPMENT
//    ItemSlot* const grappleSlot()   const { return m_grappleSlot; }
//    ItemSlot* const droidSlot()     const { return m_droidSlot; }

//    Npc* const npc() const { return m_npc; }

//    ItemSlot* const freeCargoSlot();
//    GoodsPack* goodsPack() const;

//    void UpdateSpecialAction();
//    virtual void UpdateInSpace(int, bool) = 0;

//    virtual void remeberAgressor(Vehicle*);
//    void hit(int) override;

//    virtual void _postDeathUniqueEvent(bool);

//    void CheckNeedsInStatic();
//    void ResolveNeedsInKosmoportInStatic();
//    void UpdateAllFunctionalItemsInStatic();

//    bool dropItemToSpace(const entity::Type&);

//protected:
//    void _increaseMass(int);
//    void _decreaseMass(int);
//    void _updatePropEnergy();
//    void _updatePropFreeze();
//    void _updatePropSpeed();
//    void _updatePropFire();
//    void _updatePropRadar();
//    void _updatePropJump();
//    void _updatePropProtection();
//    void _updatePropRepair();
//    void _updatePropScan();
//    void _updatePropGrab();
//    void _updateArtefactInfluence();
//    friend class ItemSlot;
//public:

//    void HyperJumpEvent(Starsystem*);
//    void DockingEvent();
//    void LaunchingEvent();

//    void UpdateSpecialEffect();
//    void UpdateLockedItems();

//    //        virtual void RenderStuffWhenFocusedInSpace(const jeti::Renderer&) override final;
//    //        virtual void RenderInfoInSpace(const jeti::Renderer&, const glm::vec2&, float) override final;
//    //        void RenderInfo(const glm::vec2&, int, int);

//    //        void RenderRadarRange();
//    //        void RenderGrappleRange();

//    bool isAbleToJumpTo(Starsystem*) const;

//    bool isArmorFull() const;
//    int armorMiss() const;
//    void increaseArmor(int);
//    void repairKorpus(int);

//    bool isFuelFull() const;
//    int fuelMiss() const;

//    void lockRandomItem(int);

//    bool tryConsumeEnergy(int);
//    bool tryGenerateEnergy(int);

//    STATUS CheckGrabStatus() const;

//    float adjustDissipateFilter() const;

//protected:
//    std::vector<ItemSlot*> m_slots;

//    ItemSlot* const _functionalSlot(const entity::Type&) const;
//    ItemSlot* const _freeArtefactSlot() const;
//    ItemSlot* const _cargoSlotWithGoods(entity::Type);

//    bool _installItem(Base*);
//    bool _installEquipment(Base*);
//#ifdef USE_MODULES
//    bool installModule(Base*);
//#endif // USE_MODULES
//#ifdef USE_ARTEFACTS
//    bool installArtefact(Base*);
//#endif // USE_ARTEFACTS
//    bool _installGoodsPack(Base*);

//    //        virtual void UpdateInfo() = 0;

//    //        void RenderGrabTrail(const jeti::Renderer&) const;
//    //        void RenderKorpus(const jeti::Renderer&);
//    //        void RenderTurrels() const;
//    //        void RenderDriveEffect(float scale, float parent_d_alpha = 0.0) const;
//    //        void RenderShieldEffect(const jeti::Renderer&, float parent_d_alpha = 0.0) const;

//    void UpdateGrappleMicroProgram_inDynamic();

//    virtual void putChildrenToGarbage() const override;

//    UnresolvedDataVehicle data_unresolved_Vehicle;

//    void SaveData(boost::property_tree::ptree&, const std::string&) const;
//    void LoadData(const boost::property_tree::ptree&);
//    void ResolveData();

//private:
//    bool m_godMode;
//    VEHICLE_SPECIAL_ACTION_TYPE m_specialActionId;

//    Npc* m_npc = nullptr;

//    VehicleSlot* m_parentVehicleSlot = nullptr;

//    Land* m_Land = nullptr;

//    ItemSlot* m_radarSlot = nullptr;
//    ItemSlot* m_scanerSlot = nullptr;
//#ifdef USE_EXTRA_EQUIPMENT
//    ItemSlot* m_energizerSlot = nullptr;
//    ItemSlot* m_freezerSlot = nullptr;
//#endif // USE_EXTRA_EQUIPMENT
//    ItemSlot* m_grappleSlot = nullptr;
//    ItemSlot* m_droidSlot = nullptr;


//    std::vector<ItemSlot*> m_equipmentSlots;
//    std::vector<ItemSlot*> m_artefactSlots;
//    std::vector<ItemSlot*> m_cargoSlots;

//    WeaponComplex     m_weaponComplex;
//    DriveComplex      m_driveComplex;
//    ProtectionComplex m_protectorComplex;

//    VehiclePropetries m_properties;
//    VehicleNeeds m_needs;
//    descriptor::Vehicle m_vehicleDescriptor;

//    [[deprecated("use predetermentistic way")]]
////    void __dropRandomItemToSpace();
//    bool __mergeIdenticalGoods(Base*);

//    Container* __wrapItemToContainer(Base*);
//    bool _checkInstallEquipment(const core::Id&);
//    ItemSlot* const _freeFunctionalSlot(const core::Id&) const;

//    friend class GuiVehicle;
//    friend class GuiVehicle2;
//};

std::string getVehicleSpecialActionStr(VEHICLE_SPECIAL_ACTION_TYPE);


