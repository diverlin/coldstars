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

#include "BaseVehicleBuilder.hpp"
#include "../../spaceobjects/Vehicle.hpp"

#include "../../parts/WeaponComplex.hpp"

#include <descriptors/DescriptorManager.hpp>

#include <item/equipment/ALL>

#ifdef USE_MODULES
#include <item/modules/ALL>
#endif

#include <item/others/Bomb.hpp>

#ifdef USE_ARTEFACTS
#include <item/artefacts/ALL>
#endif

#include <builder/item/equipment/ALL>
#include <builder/item/modules/ALL>
#include <builder/item/artefacts//ALL>
#include <builder/item/other/ALL>

#include <common/Global.hpp>
#include <managers/EntityManager.hpp>

#include <builder/slots/ItemSlotBuilder.hpp>

#include <math/rand.hpp>
#include <meti/RandUtils.hpp>

//#include <jeti/particlesystem/DriveEffect.hpp>

#include <slots/ItemSlot.hpp>

#include <types/TechLevelTypes.hpp>

#include <descriptors/DescriptorGenerator.hpp>

BaseVehicleBuilder::BaseVehicleBuilder()
{}
     
void BaseVehicleBuilder::_createSlots(Vehicle* vehicle)
{     
    // WEAPON SLOTS
    unsigned int slot_weapon_num = vehicle->vehicleDescriptor().slot_weapon_num;
    for (unsigned int i=0; i<slot_weapon_num; i++) {
        ItemSlot* weapon_slot = getNewItemSlot(type::entity::WEAPON_SLOT_ID);
        weapon_slot->setSubSubTypeId(SLOT_WEAPON_TYPES[i]);   
        vehicle->addItemSlot(weapon_slot);
    }
        
    if (vehicle->vehicleDescriptor().slot_radar_num) {
        ItemSlot* radar_slot = getNewItemSlot(type::entity::RADAR_SLOT_ID);
        vehicle->addItemSlot(radar_slot);
    }
            
    if (vehicle->vehicleDescriptor().slot_scaner_num) {
        ItemSlot* scaner_slot = getNewItemSlot(type::entity::SCANER_SLOT_ID);
        vehicle->addItemSlot(scaner_slot);
    }

    if (vehicle->vehicleDescriptor().slot_energizer_num) {
        ItemSlot* energizer_slot = getNewItemSlot(type::entity::ENERGIZER_SLOT_ID);
        vehicle->addItemSlot(energizer_slot);
    }
    
    if (vehicle->vehicleDescriptor().slot_grapple_num) {
        ItemSlot* grapple_slot = getNewItemSlot(type::entity::GRAPPLE_SLOT_ID);
        vehicle->addItemSlot(grapple_slot); 
    }
    
    if (vehicle->vehicleDescriptor().slot_droid_num) {
        ItemSlot* droid_slot = getNewItemSlot(type::entity::DROID_SLOT_ID);
        vehicle->addItemSlot(droid_slot); 
    }
    
    if (vehicle->vehicleDescriptor().slot_freezer_num) {
        //ItemSlot* freezer_slot = GetNewItemSlot(type::entity::FREEZER_SLOT_ID);
        //vehicle->AddItemSlot(freezer_slot);           
    }
    
    if (vehicle->vehicleDescriptor().slot_protector_num) {
        ItemSlot* protector_slot = getNewItemSlot(type::entity::PROTECTOR_SLOT_ID);
        vehicle->addItemSlot(protector_slot);         
    }
    
    if (vehicle->vehicleDescriptor().slot_drive_num) {
        ItemSlot* drive_slot = getNewItemSlot(type::entity::DRIVE_SLOT_ID);
        vehicle->addItemSlot(drive_slot);
    }
    
    if (vehicle->vehicleDescriptor().slot_bak_num) {
        ItemSlot* bak_slot = getNewItemSlot(type::entity::BAK_SLOT_ID);
        vehicle->addItemSlot(bak_slot);
    }
    
    //////////// ARTEFACT SLOT /////////////////////////
    int artefact_num = vehicle->vehicleDescriptor().slot_artefact_num;
    for (int i=0; i<artefact_num; i++) {
        ItemSlot* artefact_slot = getNewItemSlot(type::entity::ARTEFACT_SLOT_ID);
        artefact_slot->setSubSubTypeId(SLOT_ARTEFACT_TYPES[i]);  
        vehicle->addItemSlot(artefact_slot);         
    } 

    //////// OTSEC SLOT ////////////////////////////////
    int otsec_num = vehicle->vehicleDescriptor().slot_otsec_num;
    for (int i=0; i<otsec_num; i++) {
        ItemSlot* otsec_slot = getNewItemSlot(type::entity::CARGO_SLOT_ID);
        otsec_slot->setSubSubTypeId(SLOT_CARGO_TYPES[i]);   
        vehicle->addItemSlot(otsec_slot);         
    }

    // GATE SLOT
    {
        ItemSlot* gate_slot = getNewItemSlot(type::entity::GATE_SLOT_ID);
        vehicle->addItemSlot(gate_slot);
    }
}

void BaseVehicleBuilder::equip(Vehicle* vehicle, const descriptor::BaseOLD& descriptor)
{
//    type::entity type = (type::entity)descriptor.type();
//    switch(type) {
//    case type::entity::BAK_EQUIPMENT_ID:
//    {
//        BakEquipment* bak_equipment = core::global::get().bakBuilder().create(descriptor);
//        if (vehicle->AddAndManageItem(bak_equipment) == false) {
//           core::global::get().entityManager().addToGarbage(bak_equipment);
//        }
//        break;
//    }
//    case type::entity::DRIVE_EQUIPMENT_ID:
//    {
//        DriveEquipment* bak_equipment = core::global::get().driveBuilder().create(descriptor);
//        if (vehicle->AddAndManageItem(drive_equipment) == false) {
//           core::global::get().entityManager().addToGarbage(drive_equipment);
//        }
//        break;
//    }
//    case type::entity::DROID_EQUIPMENT_ID:
//    {
//        DriveEquipment* bak_equipment = core::global::get().driveBuilder().create(descriptor);
//        if (vehicle->AddAndManageItem(drive_equipment) == false) {
//           core::global::get().entityManager().addToGarbage(drive_equipment);
//        }
//        break;
//    }
//    }
}

void BaseVehicleBuilder::equip(Vehicle* vehicle, type::tech tech_level)
{
    unsigned int weapons_num = meti::getRandInt(vehicle->vehicleDescriptor().slot_weapon_num/2, vehicle->vehicleDescriptor().slot_weapon_num);
    for (unsigned int i=0; i<weapons_num; i++) {
        if (vehicle->isSlotFree(type::entity::WEAPON_SLOT_ID)) {
            bool rand = 0; //getRandBool();
            if (rand) {
                vehicle->manage(core::global::get().rocketBuilder().getNew(tech_level) );
            } else {
                vehicle->manage(core::global::get().lazerBuilder().getNew(tech_level) );
            }
        }
    }   
    
    if (vehicle->isSlotFree(type::entity::RADAR_SLOT_ID)) {
        vehicle->manage(core::global::get().radarBuilder().getNew());
    }
    
    if (vehicle->isSlotFree(type::entity::DRIVE_SLOT_ID)) {
        vehicle->manage(core::global::get().driveBuilder().getNew());
    }
    
    if (vehicle->isSlotFree(type::entity::BAK_SLOT_ID)) {
        vehicle->manage(core::global::get().bakBuilder().getNew());
    }

#ifdef USE_EXTRA_EQUIPMENT
    if (vehicle->isSlotFree(type::entity::ENERGIZER_SLOT_ID)) {
        vehicle->manage(core::global::get().energizerBuilder().getNew());
    }
    
    if (vehicle->isSlotFree(type::entity::FREEZER_SLOT_ID)) {
        vehicle->manage(core::global::get().freezerBuilder().getNew());
    }
#endif

    if (vehicle->isSlotFree(type::entity::PROTECTOR_SLOT_ID)) {
        vehicle->manage(core::global::get().protectorBuilder().getNew());
    }
        
    if (vehicle->isSlotFree(type::entity::DROID_SLOT_ID)) {
        vehicle->manage(core::global::get().droidBuilder().getNew());
    }
    
    if (vehicle->isSlotFree(type::entity::SCANER_SLOT_ID)) {
        vehicle->manage(core::global::get().scanerBuilder().getNew());
    }
    
    if (vehicle->isSlotFree(type::entity::GRAPPLE_SLOT_ID)) {
        vehicle->manage(core::global::get().grappleBuilder().getNew());
    }
}

#ifdef USE_MODULES
void BaseVehicleBuilder::EquipModules(Vehicle* vehicle, TYPE::TECH tech_level)
{
    for (unsigned int i=0; i<4; i++) 
    {     
        if (vehicle->GetEmptyCargoSlot() == nullptr) {
            return;
        }
            
        type::entity module_subtype_id = meti::getRand(MODULE_TYPES);
        switch(module_subtype_id) {
            case type::entity::LAZER_MODULE_ID:       { vehicle->AddItemToCargoSlot(core::global::get().lazerModuleBuilder().create()); break; }
            case type::entity::ROCKET_MODULE_ID:      { vehicle->AddItemToCargoSlot(core::global::get().rocketModuleBuilder().create()); break; }
            case type::entity::DRIVE_MODULE_ID:       { vehicle->AddItemToCargoSlot(core::global::get().driveModuleBuilder().create()); break; }
            case type::entity::RADAR_MODULE_ID:       { vehicle->AddItemToCargoSlot(core::global::get().radarModuleBuilder().create()); break; }
            case type::entity::BAK_MODULE_ID:         { vehicle->AddItemToCargoSlot(core::global::get().bakModuleBuilder().create()); break; }
            //case type::entity::ENERGIZER_MODULE_ID: { vehicle->AddItemToCargoSlot(core::global::get().energizerModuleBuilder().create()); break; }
            case type::entity::PROTECTOR_MODULE_ID:   { vehicle->AddItemToCargoSlot(core::global::get().protectorModuleBuilder().create()); break; }
            case type::entity::DROID_MODULE_ID:       { vehicle->AddItemToCargoSlot(core::global::get().droidModuleBuilder().create()); break; }
            //case type::entity::FREEZER_MODULE_ID:   { vehicle->AddItemToCargoSlot(core::global::get().freezerModuleBuilder().create()); break; }
            case type::entity::GRAPPLE_MODULE_ID:     { vehicle->AddItemToCargoSlot(core::global::get().grappleModuleBuilder().create()); break; }
            case type::entity::SCANER_MODULE_ID:      { vehicle->AddItemToCargoSlot(core::global::get().scanerModuleBuilder().create()); break; }
        }
    }
}
#endif // USE_MODULES

#ifdef USE_ARTEFACTS
void BaseVehicleBuilder::EquipArtefacts(Vehicle* vehicle, TYPE::TECH tech_level)
{
    for (unsigned int i=0; i<2; i++) {
        if (vehicle->GetEmptyCargoSlot() == nullptr) {
            return;
        }                    
        vehicle->manage(core::global::get().gravityArtefactBuilder().create());
    }   

    for (unsigned int i=0; i<2; i++) {
        if (vehicle->GetEmptyCargoSlot() == nullptr) {
            return;
        }            
        vehicle->manage(core::global::get().protectorArtefactBuilder().create());
    }  
}
#endif // USE_ARTEFACTS

void BaseVehicleBuilder::equipBomb(Vehicle* vehicle, type::tech tech_level)
{
    for (unsigned int i=0; i<2; i++) {
        //vehicle->AddItemToCargoSlot(core::global::get().bombBuilder().create());
    }    
}




