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

#include "DriveEquipmentBuilder.hpp"
#include <item/equipment/Drive.hpp>
#include <managers/EntityManager.hpp>

#include <common/IdGenerator.hpp>
#include <ceti/Logger.hpp>
#include <meti/RandUtils.hpp>
#include <common/constants.hpp>

#include <common/Global.hpp>
//#include <resources/TextureCollector.hpp>
//#include <resources/MeshCollector.hpp>

//#include <jeti/animations/AnimationConstantRotation.hpp>

#include <descriptors/RaceDescriptors.hpp>
//#include <jeti/Mesh.hpp>

#include <meti/RandUtils.hpp>

namespace item {
namespace equipment {

DriveBuilder::DriveBuilder()
{}

DriveBuilder::~DriveBuilder()
{}

Drive* DriveBuilder::createTemplate(id_type id) const
{
    Drive* drive = new Drive(id);
    assert(drive);

    global::get().entityManager().reg(drive);
    
    return drive;
} 
        
Drive* DriveBuilder::create(const descriptor::Base& descriptor) const
{
    Drive* drive = createTemplate();
    createInternals(drive, descriptor);
        
    return drive;
}        
            
void DriveBuilder::createInternals(Drive* drive, const descriptor::Base& descriptor) const
{     
    ItemCommonData data = extractCommonData(descriptor);
            
    drive->SetSpeedOrig(descriptor.speed());
    drive->SetHyperOrig(descriptor.hyper());
    drive->setParentSubTypeId(TYPE::ENTITY::DRIVE_SLOT_ID);
    drive->setItemCommonData(data);
    
    drive->updateProperties();
    drive->CountPrice();
}

} // namespace equipment
} // namespace item

