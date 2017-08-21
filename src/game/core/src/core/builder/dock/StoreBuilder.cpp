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

#include <core/manager/DescriptorManager.hpp>
#include <core/generator/DescriptorGenerator.hpp>

namespace builder {

control::Store*
Store::gen()
{
    descriptor::Store* descr = nullptr;
    if (!descriptor::Manager::get().hasType(descriptor::Type::STORE)) {
        descr = descriptor::genStore();
    } else {
        descr = descriptor::Manager::get().randStore();
    }
    return gen(descr);
} 

control::Store*
Store::gen(descriptor::Store* descr)
{
    control::Store* store = __createTemplate(descr);
    __createInternals(store);
    __putRandomEquipment(store);

    return store;
}

control::Store*
Store::__createTemplate(descriptor::Store* descr)
{
    model::Store* model = new model::Store(descr->id());
    assert(model);

    control::Store* store = new control::Store(descr, model);
    assert(store);

    core::manager::Entity::get().add(store);

    return store;
}

void
Store::__createInternals(control::Store* store)
{

}

void
Store::__putRandomEquipment(control::Store* store)
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
        store->add(builder::Ship::gen());
    }
    for (unsigned int i=0; i<lazer_num; i++) {
        store->add(builder::item::Lazer::gen());
    }
    for (unsigned int i=0; i<rocket_num; i++) {
        store->add(builder::item::Rocket::gen());
    }
    for (unsigned int i=0; i<radar_num; i++) {
        store->add(builder::item::Radar::gen());
    }
    for (unsigned int i=0; i<grapple_num; i++) {
        store->add(builder::item::Grapple::gen());
    }
    for (unsigned int i=0; i<drive_num; i++) {
        store->add(builder::item::Drive::gen());
    }
    for (unsigned int i=0; i<protector_num; i++) {
        store->add(builder::item::Protector::gen());
    }
    for (unsigned int i=0; i<bak_num; i++) {
        store->add(builder::item::Bak::gen());
    }
    for (unsigned int i=0; i<droid_num; i++) {
        store->add(builder::item::Droid::gen());
    }
    for (unsigned int i=0; i<scaner_num; i++) {
        store->add(builder::item::Scaner::gen());
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
