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

#include <core/builder/dock/KosmoportBuilder.hpp>
#include <core/builder/dock/NatureLandBuilder.hpp>

#include <core/dock/Kosmoport.hpp>

#include <core/spaceobject/Planet.hpp>
#include <core/model/spaceobject/Planet.hpp>

#include <core/session/Shortcuts.hpp>
#include <core/manager/DescriptorManager.hpp>
#include <core/generator/DescriptorGenerator.hpp>

namespace core {

core::control::Planet*
PlanetBuilder::gen()
{
    descriptor::Planet* descr = nullptr;
    if (!core::shortcuts::descriptors()->hasType(descriptor::Type::PLANET)) {
        descr = descriptor::genPlanet();
    } else {
        descr = core::shortcuts::descriptors()->randPlanet();
    }
    assert(descr);
    return gen(descr);
} 

core::control::Planet*
PlanetBuilder::gen(int_t descriptor_id, int_t id)
{
    descriptor::Planet* descr = core::shortcuts::descriptors()->planet(descriptor_id);
    return gen(descr, id);
}

core::control::Planet*
PlanetBuilder::gen(descriptor::Planet* descr, int_t id)
{
    core::control::Planet* planet = __genTemplate(descr, id);
    __createInternals(planet, descr);
    return planet;
}

void
PlanetBuilder::__createInternals(core::control::Planet* planet, descriptor::Planet* descr)
{
    /// Orientation
    planet->setSize(descr->size());
    planet->model()->setDirection(descr->direction());

    /// SpaceObject
    planet->model()->setArmor(descr->armor());

    core::control::Kosmoport* kosmoport = core::KosmoportBuilder::gen();
    planet->bindLand(kosmoport);

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
        ring->setDirection(glm::normalize(meti::OY));
        planet->AddDecoration(ring);
    }
    */
}

core::control::Planet*
PlanetBuilder::__genTemplate(descriptor::Planet* descr, int_t id)
{
    model::Planet* model = new model::Planet(descr->id(), id);
    assert(model);

    core::control::Planet* planet = new core::control::Planet(descr, model);
    assert(planet);

    return planet;
}

} // namespace builder
