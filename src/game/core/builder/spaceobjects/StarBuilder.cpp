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

#include "StarBuilder.hpp"
#include <builder/CommonBuilderHeaders.hpp>
#include "../../spaceobjects/Star.hpp"

#include <common/constants.hpp>

#include <descriptors/Base.hpp>
#include <descriptors/DescriptorManager.hpp>

#include <types/MeshTypes.hpp>
    
#include <meti/RandUtils.hpp>

namespace builder {

model::Star*
Star::__getNewTemplate(int_t id)
{ 
    model::Star* model = new model::Star;
    model->setId(id);

    assert(model);
    global::get().entityManager().reg(model);
    return model;
} 
 
model::Star*
Star::getNew()
{
    const auto& descr = global::get().descriptors().star().random();
    return getNew(descr);
} 

model::Star*
Star::getNew(const descriptor::Star& descr)
{
    model::Star* model = __getNewTemplate();
    //jeti::Mesh* mesh = MeshCollector::Instance().getMesh(TYPE::MESH::SPHERE_ID);
    //jeti::TextureOb* texOb = TextureCollector::Instance().getTextureByTypeId(TYPE::TEXTURE::STAR_ID);

    // Planetoid
    //model->setOrbitCenter(meti::vec3(0, 0, DEFAULT_ENTITY_ZPOS));
    model->setRadiusA(descr.radiusA());
    model->setRadiusB(descr.radiusB());
    model->setOrbitPhi(descr.orbitPhi());
    model->setSpeed(descr.speed());

    // Orientation
    model->setSize(descr.size());

    LifeData data_life;
    data_life.armor = descr.armor();
    model->setLifeData(data_life);

    //float scale_comp = 1.0; //meti::getRandInt(ENTITY::STAR::SCALE_MIN, ENTITY::STAR::SCALE_MAX);
    //glm::vec3 scale(scale_comp, scale_comp, scale_comp);
    //alpitodorender star->SetRenderData(mesh, texOb, scale);

    // alpitodorender star->CalcColor();
    return model;
}
          
} // namespace builder


