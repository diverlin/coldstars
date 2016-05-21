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


#include <builder/items/equipment/ScanerEquipmentBuilder.hpp>
#include <item/equipment/Scaner.hpp>
#include <managers/EntityManager.hpp>

#include <common/IdGenerator.hpp>
#include <ceti/Logger.hpp>
#include <math/rand.hpp>
#include <common/constants.hpp>

#include <common/Global.hpp>

//#include <resources/TextureCollector.hpp>
//#include <resources/MeshCollector.hpp>
//#include <jeti/TextureOb.hpp>

#include <descriptors/RaceDescriptors.hpp>

#include <meti/RandUtils.hpp>

using namespace item::equipment;

ScanerBuilder::ScanerBuilder()
{}

ScanerBuilder::~ScanerBuilder()
{}

Scaner* ScanerBuilder::createTemplate(id_type id) const
{
    Scaner* scaner_equipment = new Scaner(id);
    assert(scaner_equipment);

    global::get().entityManager().reg(scaner_equipment);
    
    return scaner_equipment;
} 

Scaner* ScanerBuilder::create(const descriptor::Base& descriptor) const
{
    Scaner* scaner_equipment = createTemplate();
    createInternals(scaner_equipment, descriptor);
        
    return scaner_equipment;
} 
            
void ScanerBuilder::createInternals(Scaner* scaner_equipment, const descriptor::Base& descriptor) const
{
    ItemCommonData common_data = extractCommonData(descriptor);
    
    scaner_equipment->SetScanOrig(descriptor.scan());
    scaner_equipment->setParentSubTypeId(TYPE::ENTITY::SCANER_SLOT_ID);
    scaner_equipment->setItemCommonData(common_data);

    scaner_equipment->updateProperties();
    scaner_equipment->CountPrice();
}
