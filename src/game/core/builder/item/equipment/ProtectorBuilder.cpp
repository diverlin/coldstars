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


#include <builder/item/equipment/ProtectorBuilder.hpp>
#include <item/equipment/Protector.hpp>
#include <managers/EntityManager.hpp>

#include <ceti/Logger.hpp>

#include <common/Global.hpp>

#include <descriptors/Base.hpp>
#include <descriptors/DescriptorManager.hpp>

namespace item {
namespace equipment {

ProtectorBuilder::ProtectorBuilder()
{}

ProtectorBuilder::~ProtectorBuilder()
{}

Protector*
ProtectorBuilder::createTemplate(id_type id) const
{
    Protector* protector = new Protector(id);
    assert(protector);

    global::get().entityManager().reg(protector);
    
    return protector;
} 
   
std::vector<Protector*>
ProtectorBuilder::getNew(int num) const
{
    std::vector<Protector*> result;
    for (int i=0; i<num; ++i) {
        result.push_back(getNew());
    }
    return result;
}

Protector*
ProtectorBuilder::getNew() const
{
    const descriptor::BaseOLD& descriptor = global::get().descriptors().getRand(descriptor::Type::PROTECTOR);
    Protector* protector = createTemplate();
    createInternals(protector, descriptor);
        
    return protector;
} 

Protector*
ProtectorBuilder::getNew(const descriptor::BaseOLD& descriptor) const
{
    Protector* protector = createTemplate();
    createInternals(protector, descriptor);

    return protector;
}
         
void
ProtectorBuilder::createInternals(Protector* protector, const descriptor::BaseOLD& descriptor) const
{     
    ItemCommonData common_data = extractCommonData(descriptor);

    protector->SetProtectionOrig(descriptor.protection());
    protector->setParentSubTypeId(type::entity::PROTECTOR_SLOT_ID);
    protector->setItemCommonData(common_data);
            
    protector->updateProperties();
    protector->CountPrice();
}

} // namespace equipment
} // namespace item

