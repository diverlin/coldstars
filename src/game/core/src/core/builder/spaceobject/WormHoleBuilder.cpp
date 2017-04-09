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

#include "WormHoleBuilder.hpp"
#include <core/builder/CommonBuilderHeaders.hpp>
#include <core/spaceobject/WormHole.hpp>
#include <core/manager/DescriptorManager.hpp>
#include <core/generator/DescriptorGenerator.hpp>

//#include <core/type/MeshType.hpp>

//#include <meti/RandUtils.hpp>

namespace builder {

control::WormHole*
WormHole::__genTemplate(descriptor::WormHole* descr)
{
    model::WormHole* model = new model::WormHole(descr->id());
    assert(model);

    control::WormHole* wormhole = new control::WormHole(descr, model);
    assert(wormhole);

    int size = 4;
    bool dynamic = false;
    //    blackhole->BindShockWaveEffect(getNewShockWave(size, dynamic));
    EntityManager::get().reg(wormhole);
    
    return wormhole;
} 

control::WormHole*
WormHole::gen()
{
    descriptor::WormHole* descr = nullptr;
    if (!descriptor::Manager::get().hasType(descriptor::Type::WORMHOLE)) {
        descr = descriptor::genWormHole();
    } else {
        descr = descriptor::Manager::get().randWormHole();
    }

    return gen(descr);
} 

control::WormHole*
WormHole::gen(descriptor::WormHole* descr)
{
    control::WormHole* wormhole = __genTemplate(descr);
    return wormhole;
}

void
WormHole::__createInternals(control::WormHole* wormhole)
{           
    //jeti::Mesh* mesh = MeshCollector::Instance().getMesh(mesh::type::SPHERE);
    
    LifeData data_life;
    data_life.garbage_ready = false;
    data_life.armor = 100000;
    data_life.life_time = meti::getRandInt(250, 500);
    data_life.dying_time = 2;

    //jeti::control::TextureOb* texOb = TextureCollector::Instance().getTextureByTypeId(TYPE::TEXTURE::BLACKHOLE);

    wormhole->model()->setLifeData(data_life);
    
    float scale_comp = 30;
    glm::vec3 scale(scale_comp, scale_comp, scale_comp);
    //alpitodorender blackhole->SetRenderData(mesh, texOb, scale);
    
    //float step = 10;
    //AnimationConstantRotationAxisZ* animation_program = new AnimationConstantRotationAxisZ(step);
    //blackhole->SetRenderAnimation(animation_program);
}

} // namespace builder



