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


#include "GravityArtefactBuilder.hpp"
#include <items/artefacts/GravityArtefact.hpp>
#include <managers/EntityManager.hpp>

#include <common/IdGenerator.hpp>
#include <ceti/Logger.hpp>
#include <meti/RandUtils.hpp>
#include <common/constants.hpp>

#include <common/Global.hpp>

//#include <resources/TextureCollector.hpp>
//#include <resources/MeshCollector.hpp>
//#include <jeti/TextureOb.hpp>

#include <common/RaceDescriptors.hpp>


GravityArtefactBuilder::GravityArtefactBuilder()
{}

GravityArtefactBuilder::~GravityArtefactBuilder()
{}

GravityArtefact* GravityArtefactBuilder::createTemplate(ID id) const
{
    GravityArtefact* gravity_artefact = new GravityArtefact(id);
    assert(gravity_artefact);

    global::get().entitiesManager().registerEntity(gravity_artefact);
    
    return gravity_artefact;
} 
    
GravityArtefact* GravityArtefactBuilder::create(int gravity) const
{
    GravityArtefact* gravity_artefact = createTemplate();
    createInternals(gravity_artefact, gravity);
        
    return gravity_artefact;
} 
        
void GravityArtefactBuilder::createInternals(GravityArtefact* gravity_artefact, int gravity) const
{
//    jeti::Mesh* mesh = MeshCollector::Instance().getMesh(TYPE::MESH::PLANE_ID);
//    jeti::TextureOb* texOb_item = TextureCollector::Instance().getTextureByTypeId(TYPE::TEXTURE::BAK_EQUIPMENT_ID);
    //item_texOb = TEXTURE_MANAGER.returnItemTexOb(TYPE::TEXTURE::RADAR_EQUIPMENT_ID, revision_id) 
    gravity = meti::getRandInt(ARTEFACT::GRAVITY::GRAVITYRATE_MIN, ARTEFACT::GRAVITY::GRAVITYRATE_MAX);

    ItemCommonData common_data;
    common_data.deterioration_normal = 1;

    gravity_artefact->SetGravity(gravity);
    // alpitodorender gravity_artefact->SetRenderData(mesh, texOb_item, texOb_item->size());
    gravity_artefact->setParentSubTypeId(TYPE::ENTITY::ARTEFACT_SLOT_ID);
    gravity_artefact->setItemCommonData(common_data);
    gravity_artefact->setCondition(common_data.condition_max);
}


