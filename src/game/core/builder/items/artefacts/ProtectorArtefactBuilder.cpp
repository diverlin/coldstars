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


#include "ProtectorArtefactBuilder.hpp"
#include <items/artefacts/ProtectorArtefact.hpp>
#include <managers/EntitiesManager.hpp>

#include <common/IdGenerator.hpp>
#include <ceti/Logger.hpp>
#include <meti/RandUtils.hpp>
#include <common/constants.hpp>

#include <common/Global.hpp>

//#include <resources/TextureCollector.hpp>
//#include <resources/MeshCollector.hpp>
//#include <jeti/TextureOb.hpp>

#include <common/RaceDescriptors.hpp>

ProtectorArtefactBuilder::ProtectorArtefactBuilder()
{}

ProtectorArtefactBuilder::~ProtectorArtefactBuilder()
{}

ProtectorArtefact* ProtectorArtefactBuilder::createTemplate(INTLONGEST id) const
{
    ProtectorArtefact* protector_artefact = nullptr;    
    if (id == NONE_ID) {
        id = EntityIdGenerator::Instance().GetNextId();
    }

    try {
        protector_artefact = new ProtectorArtefact(id);
    } catch(std::bad_alloc) {
        Logger::Instance().Log("EXEPTION:bad_dynamic_memory_allocation\n");
    }
    global::get().entitiesManager().RegisterEntity(protector_artefact);
    
    return protector_artefact;
} 
   
ProtectorArtefact* ProtectorArtefactBuilder::create(int protection) const
{
    ProtectorArtefact* protector_artefact = createTemplate();
    CreateNewInternals(protector_artefact, protection);    
        
    return protector_artefact;
} 
         
void ProtectorArtefactBuilder::CreateNewInternals(ProtectorArtefact* protector_artefact, int protection) const
{ 
//    jeti::Mesh* mesh = MeshCollector::Instance().getMesh(TYPE::MESH::PLANE_ID);
//    jeti::TextureOb* texOb_item = TextureCollector::Instance().getTextureByTypeId(TYPE::TEXTURE::BAK_EQUIPMENT_ID);
    //item_texOb = TEXTURE_MANAGER.returnItemTexOb(TYPE::TEXTURE::RADAR_EQUIPMENT_ID, revision_id) 
    protection = meti::getRandInt(ARTEFACT::PROTECTOR::PROTECTION_MIN, ARTEFACT::PROTECTOR::PROTECTION_MAX);

    ItemCommonData common_data;
    common_data.deterioration_normal = 1;

    protector_artefact->SetProtection(protection);
    // alpitodorender protector_artefact->SetRenderData(mesh, texOb_item, texOb_item->size());
    protector_artefact->SetParentSubTypeId(TYPE::ENTITY::ARTEFACT_SLOT_ID);
    protector_artefact->SetItemCommonData(common_data);
    protector_artefact->SetCondition(common_data.condition_max);
}


