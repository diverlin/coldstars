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

#include "PlanetBuilder.hpp"
#include "../CommonBuilderHeaders.hpp"
#include "../../spaceobjects/Planet.hpp"

#include <descriptors/Base.hpp>
#include <descriptors/DescriptorManager.hpp>

#include <common/constants.hpp>

//#include <effects/Atmosphere.hpp>
//#include <effects/Ring.hpp>

#include <types/MeshTypes.hpp>

#include <meti/RandUtils.hpp>


namespace builder {

model::Planet*
Planet::__createTemplate(int_t id)
{
    model::Planet* model = new model::Planet;
    model->setId(id);
    assert(model);

    global::get().entityManager().reg(model);
    
    return model;
}

model::Planet*
Planet::getNew()
{
    const auto& descr = global::get().descriptors().planet().random();
    return getNew(descr);
} 
     
model::Planet*
Planet::getNew(const descriptor::Planet& descr)
{
    model::Planet* model = __createTemplate();

    //jeti::Mesh* mesh = MeshCollector::Instance().getMesh(TYPE::MESH::SPHERE_ID);
    //jeti::TextureOb* textureOb      = TextureCollector::Instance().getTextureByTypeId(TYPE::TEXTURE::PLANET_ID);

    /// Planetoid
    model->setRadiusA(descr.radiusA());
    model->setRadiusB(descr.radiusB());
    model->setOrbitPhi(descr.orbitPhi());
    model->setSpeed(descr.speed());
    model->setClockwise(descr.clockwise());

    /// Orientation

    ///
    LifeData data_life;
    data_life.armor = descr.armor();
    model->setLifeData(data_life);

    //float scale_comp = meti::getRandInt(model::Planet::SCALE_MIN, model::Planet::SCALE_MAX);
    //glm::vec3 scale(scale_comp, scale_comp, scale_comp);
    //alpitodorender planet->SetRenderData(mesh, textureOb, scale);

    float delta_angle = 0.0001*meti::getRandInt(20, 60);
    //jeti::AnimationConstantRotation* animation_rotation = new jeti::AnimationConstantRotation(delta_angle);
    //alpitodorender planet->SetAnimationRotation(animation_rotation);

    //if (getRandBool())
    {
        //jeti::TextureOb* textureOb = TextureCollector::Instance().getTextureByTypeId(TYPE::TEXTURE::ATMOSPHERE_ID);
        //Atmosphere* atmosphere = new Atmosphere();
        //alpitodorender atmosphere->SetRenderData(mesh, textureOb, 1.04f*scale);
        //alpitodorender planet->AddDecoration(atmosphere);
    }

   /*
   {
        Mesh* mesh_plane = MeshCollector::Instance().getMesh(TYPE::MESH::PLANE_ID);

        TextureOb* textureOb = TextureCollector::Instance().getTextureByTypeId(TYPE::TEXTURE::RING_ID);
        Ring* ring = new Ring();
        ring->BindData3D(mesh_plane, textureOb, 1.5f*scale);
        //ring->setDirection(glm::normalize(glm::vec3(1.0f)));
        ring->setDirection(glm::normalize(glm::vec3(0.0f, 1.0f, 0.0f)));
        planet->AddDecoration(ring);
    }
    */
    return model;
}




//model::Planet*
//Planet::getNew(const descriptor::BaseOLD& descr)
//{
//    model::Planet* model = __createTemplate();

//    //jeti::Mesh* mesh = MeshCollector::Instance().getMesh(TYPE::MESH::SPHERE_ID);
//    //jeti::TextureOb* textureOb      = TextureCollector::Instance().getTextureByTypeId(TYPE::TEXTURE::PLANET_ID);

//    int orbit_radius = 1000; // hack
//    //model->setOrbitCenter(glm::vec3(0, 0, DEFAULT_ENTITY_ZPOS));
//    model->setRadiusA(orbit_radius);
//    model->setRadiusB(orbit_radius);
//    model->setOrbitPhi(0);
//    model->setSpeed(meti::getRandInt(model::Planet::SPEED_MIN, model::Planet::SPEED_MAX) / float(orbit_radius));
//    model->setClockwise(meti::getRandBool());

//    LifeData data_life;
//    data_life.armor = descr.armor();
//    model->setLifeData(data_life);

//    float scale_comp = meti::getRandInt(model::Planet::SCALE_MIN, model::Planet::SCALE_MAX);
//    glm::vec3 scale(scale_comp, scale_comp, scale_comp);
//    //alpitodorender planet->SetRenderData(mesh, textureOb, scale);

//    float delta_angle = 0.0001*meti::getRandInt(20, 60);
//    //jeti::AnimationConstantRotation* animation_rotation = new jeti::AnimationConstantRotation(delta_angle);
//    //alpitodorender planet->SetAnimationRotation(animation_rotation);

//    //if (getRandBool())
//    {
//        //jeti::TextureOb* textureOb = TextureCollector::Instance().getTextureByTypeId(TYPE::TEXTURE::ATMOSPHERE_ID);
//        //Atmosphere* atmosphere = new Atmosphere();
//        //alpitodorender atmosphere->SetRenderData(mesh, textureOb, 1.04f*scale);
//        //alpitodorender planet->AddDecoration(atmosphere);
//    }

//   /*
//   {
//        Mesh* mesh_plane = MeshCollector::Instance().getMesh(TYPE::MESH::PLANE_ID);

//        TextureOb* textureOb = TextureCollector::Instance().getTextureByTypeId(TYPE::TEXTURE::RING_ID);
//        Ring* ring = new Ring();
//        ring->BindData3D(mesh_plane, textureOb, 1.5f*scale);
//        //ring->setDirection(glm::normalize(glm::vec3(1.0f)));
//        ring->setDirection(glm::normalize(glm::vec3(0.0f, 1.0f, 0.0f)));
//        planet->AddDecoration(ring);
//    }
//    */
//    return model;
//}


} // namespace builder
