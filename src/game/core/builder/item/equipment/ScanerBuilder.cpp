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


#include "ScanerBuilder.hpp"
#include <item/equipment/Scaner.hpp>
#include <managers/EntityManager.hpp>

#include <ceti/Logger.hpp>

#include <common/Global.hpp>

#include <descriptors/Base.hpp>
#include <descriptors/DescriptorManager.hpp>

namespace item {
namespace equipment {

using namespace item::equipment;

ScanerBuilder::ScanerBuilder()
{}

ScanerBuilder::~ScanerBuilder()
{}

Scaner* ScanerBuilder::createTemplate(int_t id) const
{
    Scaner* scaner = new Scaner(id);
    assert(scaner);

    global::get().entityManager().reg(scaner);
    
    return scaner;
} 

Scaner* ScanerBuilder::getNew() const
{
    const descriptor::BaseOLD& descriptor = global::get().descriptors().getRand(descriptor::Type::SCANER);
    Scaner* scaner = createTemplate();
    createInternals(scaner, descriptor);

    return scaner;
}

Scaner* ScanerBuilder::getNew(const descriptor::BaseOLD& descriptor) const
{
    Scaner* scaner = createTemplate();
    createInternals(scaner, descriptor);
        
    return scaner;
} 
            
void ScanerBuilder::createInternals(Scaner* scaner, const descriptor::BaseOLD& descriptor) const
{
    ItemCommonData common_data = extractCommonData(descriptor);
    
    scaner->setScanOrig(descriptor.scan());
    scaner->setParentSubTypeId(type::entity::SCANER_SLOT_ID);
    scaner->setItemCommonData(common_data);

    scaner->updateProperties();
    scaner->countPrice();
}

} // namespace equipment
} // namespace item

