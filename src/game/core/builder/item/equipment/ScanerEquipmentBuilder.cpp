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


#include "ScanerEquipmentBuilder.hpp"
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

namespace item {
namespace equipment {

using namespace item::equipment;

ScanerBuilder::ScanerBuilder()
{}

ScanerBuilder::~ScanerBuilder()
{}

Scaner* ScanerBuilder::createTemplate(id_type id) const
{
    Scaner* scaner = new Scaner(id);
    assert(scaner);

    global::get().entityManager().reg(scaner);
    
    return scaner;
} 

Scaner* ScanerBuilder::create(const descriptor::Base& descriptor) const
{
    Scaner* scaner = createTemplate();
    createInternals(scaner, descriptor);
        
    return scaner;
} 
            
void ScanerBuilder::createInternals(Scaner* scaner, const descriptor::Base& descriptor) const
{
    ItemCommonData common_data = extractCommonData(descriptor);
    
    scaner->setScanOrig(descriptor.scan());
    scaner->setParentSubTypeId(TYPE::ENTITY::SCANER_SLOT_ID);
    scaner->setItemCommonData(common_data);

    scaner->updateProperties();
    scaner->countPrice();
}

} // namespace equipment
} // namespace item

