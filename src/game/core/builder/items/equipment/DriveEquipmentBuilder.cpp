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

#include <builder/items/equipment/DriveEquipmentBuilder.hpp>
#include <items/equipment/DriveEquipment.hpp>
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

DriveEquipmentBuilder::DriveEquipmentBuilder()
{}

DriveEquipmentBuilder::~DriveEquipmentBuilder()
{}

DriveEquipment* DriveEquipmentBuilder::createTemplate(id_type id) const
{
    DriveEquipment* drive_equipment = new DriveEquipment(id);
    assert(drive_equipment);

    global::get().entityManager().reg(drive_equipment);
    
    return drive_equipment;
} 
        
DriveEquipment* DriveEquipmentBuilder::create(const Descriptor& descriptor) const
{
    DriveEquipment* drive_equipment = createTemplate();
    createInternals(drive_equipment, descriptor);
        
    return drive_equipment;
}        
            
void DriveEquipmentBuilder::createInternals(DriveEquipment* drive_equipment, const Descriptor& descriptor) const
{     
    ItemCommonData common_data;
    common_data.race            = (TYPE::RACE)descriptor.race();
    common_data.tech         = (TYPE::TECH)descriptor.tech();
    common_data.modules_num    = descriptor.modules();
    common_data.mass               = descriptor.mass();
    common_data.condition      = descriptor.condition();
    common_data.deterioration = 1;
    common_data.deterioration_overload_rate = EQUIPMENT::DRIVE::OVERLOAD_DETERIORATION_RATE;

    // alpitodorender drive_equipment->SetRenderData(mesh, texOb, size);
    
    //float step = getRandInt(10, 40)*0.01;
    //AnimationConstantRotationAxisX* animation_program = new AnimationConstantRotationAxisX(step);
    //drive_equipment->SetRenderAnimation(animation_program);
            
    drive_equipment->SetSpeedOrig(descriptor.speed());
    drive_equipment->SetHyperOrig(descriptor.hyper());
    drive_equipment->setParentSubTypeId(TYPE::ENTITY::DRIVE_SLOT_ID);
    drive_equipment->setItemCommonData(common_data);
    drive_equipment->setCondition(common_data.condition);
    
    drive_equipment->updateProperties();
    drive_equipment->CountPrice();
}


