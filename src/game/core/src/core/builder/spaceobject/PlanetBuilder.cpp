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
#include <core/builder/CommonBuilderHeaders.hpp>
#include <core/spaceobject/Planet.hpp>
#include <core/model/spaceobject/Planet.hpp>
#include <core/descriptor/Base.hpp>
#include <core/manager/DescriptorManager.hpp>
#include <core/generator/DescriptorGenerator.hpp>

namespace builder {

model::Planet*
Planet::__genTemplate(int_t descriptor_id)
{
    model::Planet* model = new model::Planet(descriptor_id);
    assert(model);

    EntityManager::get().reg(model);
    
    return model;
}

model::Planet*
Planet::gen()
{
    descriptor::Planet* descr = nullptr;
    if (!descriptor::Manager::get().hasType(descriptor::Type::PLANET)) {
        descr = descriptor::genPlanet();
    } else {
        descr = descriptor::Manager::get().randPlanet();
    }
    assert(descr);
    return gen(descr);
} 

model::Planet*
Planet::gen(descriptor::Planet* descr)
{
    model::Planet* model = __genTemplate(descr->id());

    /// Base
    LifeData life_data;
    life_data.armor = descr->armor();
    model->setLifeData(life_data);

    /// Planetoid
    model->setRadiusA(descr->radiusA());
    model->setRadiusB(descr->radiusB());
    model->setOrbitPhi(descr->orbitPhi());
    model->setSpeed(descr->speed());
    model->setClockwise(descr->clockwise());

    /// Orientation
    model->setSize(descr->size());
    model->setDirection(descr->direction());

    //float scale_comp = meti::getRandInt(model::Planet::SCALE_MIN, model::Planet::SCALE_MAX);
    //glm::vec3 scale(scale_comp, scale_comp, scale_comp);
    //alpitodorender planet->SetRenderData(mesh, textureOb, scale);

    //float delta_angle = 0.0001*meti::getRandInt(20, 60);
    //jeti::AnimationConstantRotation* animation_rotation = new jeti::AnimationConstantRotation(delta_angle);
    //alpitodorender planet->SetAnimationRotation(animation_rotation);

    //if (getRandBool())
    {
        //jeti::control::TextureOb* textureOb = TextureCollector::Instance().getTextureByTypeId(TYPE::TEXTURE::ATMOSPHERE);
        //Atmosphere* atmosphere = new Atmosphere();
        //alpitodorender atmosphere->SetRenderData(mesh, textureOb, 1.04f*scale);
        //alpitodorender planet->AddDecoration(atmosphere);
    }

    /*
   {
        Mesh* mesh_plane = MeshCollector::Instance().getMesh(mesh::type::PLANE);

        TextureOb* textureOb = TextureCollector::Instance().getTextureByTypeId(TYPE::TEXTURE::RING);
        Ring* ring = new Ring();
        ring->BindData3D(mesh_plane, textureOb, 1.5f*scale);
        //ring->setDirection(glm::normalize(glm::vec3(1.0f)));
        ring->setDirection(glm::normalize(glm::vec3(0.0f, 1.0f, 0.0f)));
        planet->AddDecoration(ring);
    }
    */
    return model;
}

} // namespace builder
