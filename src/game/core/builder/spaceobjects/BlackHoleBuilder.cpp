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

#include "BlackHoleBuilder.hpp"
#include "../CommonBuilderHeaders.hpp"
#include "../../spaceobjects/BlackHole.hpp"

#include <types/MeshTypes.hpp>

#include <meti/RandUtils.hpp>


BlackHoleBuilder::BlackHoleBuilder()
{}

BlackHoleBuilder::~BlackHoleBuilder()
{}

BlackHole* BlackHoleBuilder::createTemplate(id_type id) const
{
    BlackHole* blackhole = new BlackHole(id);
    assert(blackhole);
    
    int size = 4;
    bool dynamic = false;
    //    blackhole->BindShockWaveEffect(getNewShockWave(size, dynamic));
    global::get().entityManager().reg(blackhole);
    
    return blackhole;
} 

BlackHole* BlackHoleBuilder::create() const
{
    BlackHole* blackhole = createTemplate();
    createInternals(blackhole);

    return blackhole;
} 

void BlackHoleBuilder::createInternals(BlackHole* blackhole) const
{           
    //jeti::Mesh* mesh = MeshCollector::Instance().getMesh(TYPE::MESH::SPHERE_ID);
    
    LifeData data_life;
    data_life.is_alive   = true;
    data_life.garbage_ready = false;
    data_life.armor      = 100000;
    data_life.life_time = meti::getRandInt(250, 500);
    data_life.dying_time = 2;

    //jeti::TextureOb* texOb = TextureCollector::Instance().getTextureByTypeId(TYPE::TEXTURE::BLACKHOLE_ID);

    blackhole->setLifeData(data_life);
    
    float scale_comp = 30;
    glm::vec3 scale(scale_comp, scale_comp, scale_comp);
    //alpitodorender blackhole->SetRenderData(mesh, texOb, scale);
    
    //float step = 10;
    //AnimationConstantRotationAxisZ* animation_program = new AnimationConstantRotationAxisZ(step);
    //blackhole->SetRenderAnimation(animation_program);
}





