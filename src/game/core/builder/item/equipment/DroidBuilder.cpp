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


#include "DroidBuilder.hpp"
#include <item/equipment/Droid.hpp>
#include <managers/EntityManager.hpp>

#include <common/IdGenerator.hpp>
#include <ceti/Logger.hpp>
#include <math/rand.hpp>
#include <common/constants.hpp>

#include <common/Global.hpp>

#include <descriptors/RaceDescriptors.hpp>

#include <meti/RandUtils.hpp>

namespace item {
namespace equipment {

using namespace item::equipment;

DroidBuilder::DroidBuilder()
{}

DroidBuilder::~DroidBuilder()
{}

Droid* DroidBuilder::createTemplate(id_type id) const
{
    Droid* droid = new Droid(id);
    assert(droid);

    global::get().entityManager().reg(droid);
    
    return droid;
} 

Droid* DroidBuilder::create(const descriptor::Base& descriptor) const
{
    Droid* droid = createTemplate();
    createInternals(droid, descriptor);
        
    return droid;
}  
            
void DroidBuilder::createInternals(Droid* droid, const descriptor::Base& descriptor) const
{     
    ItemCommonData common_data = extractCommonData(descriptor);
   
    droid->SetRepairOrig(descriptor.repair());
    droid->setParentSubTypeId(TYPE::ENTITY::DROID_SLOT_ID);
    droid->setItemCommonData(common_data);
            
    droid->updateProperties();
    droid->CountPrice();
}

} // namespace equipment
} // namespace item
