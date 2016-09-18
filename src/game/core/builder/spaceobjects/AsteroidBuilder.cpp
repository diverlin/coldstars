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
#include "../CommonBuilderHeaders.hpp"
#include "../../spaceobjects/Asteroid.hpp"

#include <common/constants.hpp>

#include <types/MeshTypes.hpp>

#include <meti/RandUtils.hpp>


AsteroidBuilder::AsteroidBuilder()
{}

AsteroidBuilder::~AsteroidBuilder()
{}

Asteroid* AsteroidBuilder::createTemplate(int_t id) const
{ 
    Asteroid* asteroid = new Asteroid(id);
    assert(asteroid);

    global::get().entityManager().reg(asteroid);
    
    return asteroid;
} 

Asteroid* AsteroidBuilder::create() const
{
    Asteroid* asteroid = createTemplate();
    createInternals(asteroid);
        
    return asteroid;
} 
           
void AsteroidBuilder::createInternals(Asteroid* asteroid) const
{           
    //jeti::Mesh* mesh = MeshCollector::Instance().getMesh(TYPE::MESH::SPHERE_DEFORMED_ID);
    
    LifeData data_life;   
    data_life.armor      = 10;
    data_life.dying_time = 50;
    
    PlanetDescriptor planet_data;

    planet_data.orbit_center  = glm::vec3(0, 0, DEFAULT_ENTITY_ZPOS); 
    planet_data.radius_A      = meti::getRandInt(300, 1200);
    planet_data.radius_B      = meti::getRandInt(300, 1200);
    planet_data.orbit_phi_inD = meti::getRandInt(360);
    planet_data.speed         = 0.1;
    planet_data.clockwise     = meti::getRandBool();
    
    asteroid->setPlanetDescriptor(planet_data);
    asteroid->setLifeData(data_life);

    float scale_comp = meti::getRandInt(ENTITY::ASTEROID::SCALE_MIN, ENTITY::ASTEROID::SCALE_MAX);
    glm::vec3 scale(scale_comp, scale_comp, scale_comp);
    //jeti::TextureOb* texOb = TextureCollector::Instance().getTextureByTypeId(TYPE::TEXTURE::ASTEROID_ID);
          
    //alpitodorender asteroid->SetRenderData(mesh, texOb, scale);

    float delta_angle = 0.0001*meti::getRandInt(20, 60);
    //jeti::AnimationConstantRotation* animation_rotation = new jeti::AnimationConstantRotation(delta_angle);
    //alpitodorender asteroid->SetAnimationRotation(animation_rotation);
                
    asteroid->setGivenExpirience(ENTITY::ASTEROID::GIVEN_EXPIRIENCE);
}





