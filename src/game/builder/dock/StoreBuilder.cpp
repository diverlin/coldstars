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


#include <builder/dock/StoreBuilder.hpp>
#include <builder/slots/ItemSlotBuilder.hpp>
#include <builder/slots/VehicleSlotBuilder.hpp>
#include <builder/items/IncludeItemBuilders.hpp>
#include <builder/spaceobjects/ShipBuilder.hpp>
#include <builder/CommonBuilderHeaders.hpp>

#include <dock/Store.hpp>

#include <spaceobjects/Ship.hpp>

#include <items/equipment/BakEquipment.hpp>
#include <items/equipment/DriveEquipment.hpp>
#include <items/equipment/DroidEquipment.hpp>
#include <items/equipment/GrappleEquipment.hpp>
#include <items/equipment/LazerEquipment.hpp>
#include <items/equipment/ProtectorEquipment.hpp>
#include <items/equipment/RadarEquipment.hpp>
#include <items/equipment/RocketEquipment.hpp>
#include <items/equipment/ScanerEquipment.hpp>
#include <items/equipment/EnergizerEquipment.hpp>
#include <items/equipment/FreezerEquipment.hpp>

#include <common/constants.hpp>
                     
                     
StoreBuilder& StoreBuilder::Instance()
{
    static StoreBuilder instance;
    return instance;
}

StoreBuilder::~StoreBuilder()
{}

Store* StoreBuilder::GetNewStoreTemplate(INTLONGEST id) const
{
    Store* store = nullptr;
    
    if (id == NONE_ID)
    {
        id = EntityIdGenerator::Instance().GetNextId();
    }

    try 
    { 
        store = new Store(id);
    }
    catch(std::bad_alloc)
    {
        Logger::Instance().Log("EXEPTION:bad_dynamic_memory_allocation\n");
    }
    
    EntityManager::Instance().RegisterEntity(store);
    
    return store;
} 

Store* StoreBuilder::GetNewStore() const
{
    Store* store = GetNewStoreTemplate();
    CreateNewInternals(store);
    PutRandomEquipment(store);
            
        return store;
} 
            
void StoreBuilder::CreateNewInternals(Store* store) const
{
    for (unsigned int i=0; i<STORE_ITEM_SLOTS_NUM; i++)
    {
        ItemSlot* item_slot = GetNewItemSlot(TYPE::ENTITY::CARGO_SLOT_ID);
        store->AddItemSlot(item_slot);
    }

    for (unsigned int i=0; i<STORE_VEHICLE_SLOTS_NUM; i++)
    {
        VehicleSlot* vehicle_slot = GetNewVehicleSlot(TYPE::ENTITY::NONE_ID);
        store->AddVehicleSlot(vehicle_slot);
    }
        
    store->SetTextureObBackground(TextureManager::Instance().GetRandomTextureOb(TYPE::TEXTURE::STORE_BACKGROUND_ID));
}


void StoreBuilder::PutRandomEquipment(Store* store) const
{
        //int race_id = RACES_GOOD_LIST[getRandInt(0, RACES_GOOD_LIST.size() - 1)];
        //int revision_id = 0;

        unsigned int vehicle_num     = 3;
        
        unsigned int lazer_num       = 3;
        unsigned int rocket_num      = 2;
        //unsigned int torped_num      = 2;
        unsigned int radar_num       = 1;
        unsigned int grapple_num     = 1;
        unsigned int drive_num       = 1;
        unsigned int protector_num   = 1;
        unsigned int bak_num         = 1;
        unsigned int droid_num       = 1;
        unsigned int scaner_num      = 1;
        unsigned int freezer_num     = 1;
        unsigned int energyBlock_num = 1;

        for (unsigned int i=0; i<vehicle_num; i++)
        { 
               store->AddVehicle(ShipBuilder::Instance().GetNewShip()); 
        }
                
        for (unsigned int i=0; i<lazer_num; i++)
        { 
               store->AddItem(LazerEquipmentBuilder::Instance().GetNewLazerEquipment()); 
        }

        for (unsigned int i=0; i<rocket_num; i++)
        { 
               store->AddItem(RocketEquipmentBuilder::Instance().GetNewRocketEquipment());
        }

        for (unsigned int i=0; i<radar_num; i++)
        { 
            store->AddItem(RadarEquipmentBuilder::Instance().GetNewRadarEquipment()); 
        }

        for (unsigned int i=0; i<grapple_num; i++)
        { 
              store->AddItem(GrappleEquipmentBuilder::Instance().GetNewGrappleEquipment()); 
        }

        for (unsigned int i=0; i<drive_num; i++)
        {        
                store->AddItem(DriveEquipmentBuilder::Instance().GetNewDriveEquipment());
        }

        for (unsigned int i=0; i<protector_num; i++)
        { 
           store->AddItem(ProtectorEquipmentBuilder::Instance().GetNewProtectorEquipment()); 
        }

        for (unsigned int i=0; i<bak_num; i++)
        { 
                store->AddItem(BakEquipmentBuilder::Instance().GetNewBakEquipment());
        }

        for (unsigned int i=0; i<droid_num; i++)
        { 
           store->AddItem(DroidEquipmentBuilder::Instance().GetNewDroidEquipment()); 
        }

        for (unsigned int i=0; i<scaner_num; i++)
        { 
           store->AddItem(ScanerEquipmentBuilder::Instance().GetNewScanerEquipment()); 
        }

        for (unsigned int i=0; i<freezer_num; i++)
        { 
           store->AddItem(FreezerEquipmentBuilder::Instance().GetNewFreezerEquipment()); 
        }

        for (unsigned int i=0; i<energyBlock_num; i++) 
        { 
            store->AddItem(EnergizerEquipmentBuilder::Instance().GetNewEnergizerEquipment());  
        }
}



      
