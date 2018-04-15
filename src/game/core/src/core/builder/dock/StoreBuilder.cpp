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

#include <core/item/equipment/ALL>
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

#include <core/descriptor/dock/Store.hpp>
#include <core/model/dock/Store.hpp>
#include <core/dock/Store.hpp>

#include <core/spaceobject/Ship.hpp>

#include <common/constants.hpp>

#include <core/session/Shortcuts.hpp>
#include <core/manager/DescriptorManager.hpp>
#include <core/generator/DescriptorGenerator.hpp>

namespace builder {

core::control::Store*
StoreBuilder::gen()
{
    descriptor::Store* descr = nullptr;
    if (!core::shortcuts::descriptors()->hasType(descriptor::Type::STORE)) {
        descr = descriptor::genStore();
    } else {
        descr = core::shortcuts::descriptors()->randStore();
    }
    return gen(descr);
} 

core::control::Store*
StoreBuilder::gen(descriptor::Store* descr)
{
    core::control::Store* store = __createTemplate(descr);
    __createInternals(store);
    __putRandomEquipment(store);

    return store;
}

core::control::Store*
StoreBuilder::__createTemplate(descriptor::Store* descr)
{
    model::Store* model = new model::Store(descr->id());
    assert(model);

    core::control::Store* store = new core::control::Store(descr, model);
    assert(store);

    core::shortcuts::entities()->add(store);

    return store;
}

void
StoreBuilder::__createInternals(core::control::Store* store)
{

}

void
StoreBuilder::__putRandomEquipment(core::control::Store* store)
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
        store->add(builder::ShipBuilder::gen());
    }
    for (unsigned int i=0; i<lazer_num; i++) {
        store->add(builder::item::LazerItemBuilder::gen());
    }
    for (unsigned int i=0; i<rocket_num; i++) {
        store->add(builder::item::RocketItemBuilder::gen());
    }
    for (unsigned int i=0; i<radar_num; i++) {
        store->add(builder::item::RadarItemBuilder::gen());
    }
    for (unsigned int i=0; i<grapple_num; i++) {
        store->add(builder::item::GrappleItemBuilder::gen());
    }
    for (unsigned int i=0; i<drive_num; i++) {
        store->add(builder::item::DriveItemBuilder::gen());
    }
    for (unsigned int i=0; i<protector_num; i++) {
        store->add(builder::item::ProtectorItemBuilder::gen());
    }
    for (unsigned int i=0; i<bak_num; i++) {
        store->add(builder::item::BakItemBuilder::gen());
    }
    for (unsigned int i=0; i<droid_num; i++) {
        store->add(builder::item::DroidItemBuilder::gen());
    }
    for (unsigned int i=0; i<scaner_num; i++) {
        store->add(builder::item::ScanerItemBuilder::gen());
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

} // namespace builder
