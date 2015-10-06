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

#include <common/RaceDescriptors.hpp>
//#include <jeti/Mesh.hpp>

#include <meti/RandUtils.hpp>

DriveEquipmentBuilder::DriveEquipmentBuilder()
{}

DriveEquipmentBuilder::~DriveEquipmentBuilder()
{}

DriveEquipment* DriveEquipmentBuilder::createTemplate(ID id) const
{
    DriveEquipment* drive_equipment = new DriveEquipment(id);
    assert(drive_equipment);

    global::get().entitiesManager().reg(drive_equipment);
    
    return drive_equipment;
} 
        
DriveEquipment* DriveEquipmentBuilder::create(TYPE::TECHLEVEL tech_level, TYPE::RACE race_id, int speed_orig, int hyper_orig) const
{
    DriveEquipment* drive_equipment = createTemplate();
    createInternals(drive_equipment, tech_level, race_id, speed_orig, hyper_orig);
        
    return drive_equipment;
}        
            
void DriveEquipmentBuilder::createInternals(DriveEquipment* drive_equipment, TYPE::TECHLEVEL tech_level, TYPE::RACE race_id, int speed_orig, int hyper_orig) const
{     
    if (race_id == TYPE::RACE::NONE_ID) {
        race_id = meti::getRand(global::get().raceDescriptors().getRaces(TYPE::KIND::GOOD));
    }
    
    if (tech_level == TYPE::TECHLEVEL::NONE_ID) {
        tech_level = TYPE::TECHLEVEL::L0_ID; 
    }

    //Mesh* mesh = MeshCollector::Instance().getMesh(TYPE::MESH::PLANE_ID);
    //TextureOb* texOb = TextureCollector::Instance().getTextureByTypeId(TYPE::TEXTURE::DRIVE_EQUIPMENT_ID);
    //glm::vec3 size = texOb->size();
    
//    jeti::Mesh* mesh = MeshCollector::Instance().getMesh(TYPE::MESH::SPACESTATION_ID);
//    jeti::TextureOb* texOb = mesh->textureOb();
    glm::vec3 size = glm::vec3(50);

    //texOb = TEXTURE_MANAGER.returnItemTexOb(TYPE::TEXTURE::DRIVE_EQUIPMENT_ID, revision_id) 

    speed_orig      = meti::getRandInt(EQUIPMENT::DRIVE::SPEED_MIN, EQUIPMENT::DRIVE::SPEED_MAX) * (1 + EQUIPMENT::DRIVE::SPEED_TECHLEVEL_RATE * (int)tech_level);
    hyper_orig      = meti::getRandInt(EQUIPMENT::DRIVE::HYPER_MIN, EQUIPMENT::DRIVE::HYPER_MAX) * (1 + EQUIPMENT::DRIVE::HYPER_TECHLEVEL_RATE * (int)tech_level);

    ItemCommonData common_data;
    common_data.tech_level         = tech_level;
    common_data.modules_num_max     = meti::getRandInt(EQUIPMENT::DRIVE::MODULES_NUM_MIN, EQUIPMENT::DRIVE::MODULES_NUM_MAX);
    common_data.mass                = meti::getRandInt(EQUIPMENT::DRIVE::MASS_MIN,        EQUIPMENT::DRIVE::MASS_MAX);
    common_data.condition_max       = meti::getRandInt(EQUIPMENT::DRIVE::CONDITION_MIN,   EQUIPMENT::DRIVE::CONDITION_MAX);
    common_data.deterioration_normal = 1;
    common_data.deterioration_overload_rate = EQUIPMENT::DRIVE::OVERLOAD_DETERIORATION_RATE;

    // alpitodorender drive_equipment->SetRenderData(mesh, texOb, size);
    
    //float step = getRandInt(10, 40)*0.01;
    //AnimationConstantRotationAxisX* animation_program = new AnimationConstantRotationAxisX(step);
    //drive_equipment->SetRenderAnimation(animation_program);
            
    drive_equipment->SetSpeedOrig(speed_orig);  
    drive_equipment->SetHyperOrig(hyper_orig);
    drive_equipment->setParentSubTypeId(TYPE::ENTITY::DRIVE_SLOT_ID);
    drive_equipment->setItemCommonData(common_data);
    drive_equipment->setCondition(common_data.condition_max);
    
    drive_equipment->updateProperties();
    drive_equipment->CountPrice();
}


