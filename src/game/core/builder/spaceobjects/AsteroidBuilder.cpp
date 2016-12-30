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

#include "AsteroidBuilder.hpp"
#include <builder/CommonBuilderHeaders.hpp>
#include <spaceobjects/Asteroid.hpp>

#include <common/constants.hpp>

//#include <types/MeshTypes.hpp>

#include <meti/RandUtils.hpp>

namespace builder {

model::Asteroid* Asteroid::__createTemplate(int_t id)
{ 
    model::Asteroid* model = new model::Asteroid;
    model->setId(id);
    assert(model);

   core::global::get().entityManager().reg(model);
    
    return model;
} 

model::Asteroid* Asteroid::getNew()
{
    model::Asteroid* model = __createTemplate();

    //model->setOrbitCenter(meti::vec3(0, 0, DEFAULT_ENTITY_ZPOS));
    model->setRadiusA(meti::getRandInt(300, 1200));
    model->setRadiusB(meti::getRandInt(300, 1200));
    model->setOrbitPhi(meti::getRandInt(360));
    model->setSpeed(0.1f);
    model->setClockwise(meti::getRandBool());

    LifeData data_life;
    data_life.armor      = 10;
    data_life.dying_time = 50;
    model->setLifeData(data_life);

    float scale_comp = meti::getRandInt(model::Asteroid::SCALE_MIN, model::Asteroid::SCALE_MAX);
    glm::vec3 scale(scale_comp, scale_comp, scale_comp);

    //jeti::Mesh* mesh = MeshCollector::Instance().getMesh(TYPE::MESH::SPHERE_DEFORMED_ID);
    //jeti::control::TextureOb* texOb = TextureCollector::Instance().getTextureByTypeId(TYPE::TEXTURE::ASTEROID_ID);

    //alpitodorender asteroid->SetRenderData(mesh, texOb, scale);

    float delta_angle = 0.0001*meti::getRandInt(20, 60);
    //jeti::AnimationConstantRotation* animation_rotation = new jeti::AnimationConstantRotation(delta_angle);
    //alpitodorender asteroid->SetAnimationRotation(animation_rotation);

    // todo
    //model->setGivenExpirience(ENTITY::ASTEROID::GIVEN_EXPIRIENCE);
        
    return model;
} 
           
} // namespace builder



