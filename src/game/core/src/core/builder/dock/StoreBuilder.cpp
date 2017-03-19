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
#include <core/builder/slot/ItemSlotBuilder.hpp>
#include <core/builder/slot/VehicleSlotBuilder.hpp>

#include <core/builder/item/equipment/ALL>
#ifdef USE_MODULES
#include <core/builder/item/module/ALL>
#endif
#ifdef USE_ARTEFACTS
#include <core/builder/item/artefact/ALL>
#endif
#include <core/builder/item/other/ALL>

#include <core/builder/spaceobject/ShipBuilder.hpp>
#include <builder/CommonBuilderHeaders.hpp>

#include <dock/Store.hpp>

#include <core/spaceobject/Ship.hpp>

#include <common/constants.hpp>

#include <core/manager/DescriptorManager.hpp>

StoreBuilder::StoreBuilder()
{}

StoreBuilder::~StoreBuilder()
{}

Store* StoreBuilder::createTemplate(int_t id) const
{
    Store* store = new Store(id);
    assert(store);

    assert(false);
//    EntityManager::get().reg(store);
    
    return store;
} 

Store* StoreBuilder::create() const
{
    Store* store = createTemplate();
    createInternals(store);
    PutRandomEquipment(store);

    return store;
} 

void StoreBuilder::createInternals(Store* store) const
{
    for (unsigned int i=0; i<STORE_ITEM_SLOTS_NUM; i++)
    {
        control::ItemSlot* item_slot = getNewItemSlot(entity::Type::CARGO_SLOT);
        store->addItemSlot(item_slot);
    }

    for (unsigned int i=0; i<STORE_VEHICLE_SLOTS_NUM; i++)
    {
        control::VehicleSlot* vehicle_slot = getNewVehicleSlot(entity::Type::NONE);
        store->addVehicleSlot(vehicle_slot);
    }

    //store->SetTextureObBackground(TextureCollector::Instance().getTextureByTypeId(TYPE::TEXTURE::STORE_BACKGROUND));
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

    for (unsigned int i=0; i<vehicle_num; i++) {
        assert(false);
        //store->addVehicle(ShipBuilder::gen());
    }
    for (unsigned int i=0; i<lazer_num; i++) {
        assert(false);
//        store->addItem(core::global::get().lazerBuilder().gen());
    }
    for (unsigned int i=0; i<rocket_num; i++) {
        assert(false);
//        store->addItem(core::global::get().rocketBuilder().gen());
    }
    for (unsigned int i=0; i<radar_num; i++) {
        assert(false);
//        const auto& descr = descriptor::Manager::get().getRand(descriptor::Type::RADAR);
//        store->addItem(core::global::get().radarBuilder().gen(descr));
    }
    for (unsigned int i=0; i<grapple_num; i++) {
        assert(false);
//        const auto& descr = descriptor::Manager::get().getRand(descriptor::Type::GRAPPLE);
//        store->addItem(core::global::get().grappleBuilder().gen(descr));
    }
    for (unsigned int i=0; i<drive_num; i++) {
        assert(false);
//        const auto& descr = descriptor::Manager::get().getRand(descriptor::Type::DRIVE);
//        store->addItem(core::global::get().driveBuilder().gen(descr));
    }
    for (unsigned int i=0; i<protector_num; i++) {
        assert(false);
//        const auto& descr = descriptor::Manager::get().getRand(descriptor::Type::PROTECTOR);
//        store->addItem(core::global::get().protectorBuilder().gen(descr));
    }
    for (unsigned int i=0; i<bak_num; i++) {
        assert(false);
//        const auto& descr = descriptor::Manager::get().getRand(descriptor::Type::BAK);
//        store->addItem(core::global::get().bakBuilder().gen(descr));
    }
    for (unsigned int i=0; i<droid_num; i++) {
        assert(false);
//        const auto& descr = descriptor::Manager::get().getRand(descriptor::Type::DROID);
//        store->addItem(core::global::get().droidBuilder().gen(descr));
    }
    for (unsigned int i=0; i<scaner_num; i++) {
        assert(false);
//        const auto& descr = descriptor::Manager::get().getRand(descriptor::Type::SCANER);
//        store->addItem(core::global::get().scanerBuilder().gen(descr));
    }
#ifdef USE_EXTRA_EQUIPMENT
    for (unsigned int i=0; i<freezer_num; i++) {
        store->AddItem(core::global::get().freezerBuilder().create());
    }
    for (unsigned int i=0; i<energyBlock_num; i++) {
        store->AddItem(core::global::get().energizerBuilder().create());
    }
#endif
}
