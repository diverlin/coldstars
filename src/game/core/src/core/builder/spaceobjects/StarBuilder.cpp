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
#include <core/spaceobjects/Star.hpp>

#include <common/constants.hpp>

#include <descriptor/Base.hpp>
#include <descriptor/DescriptorManager.hpp>

#include <types/MeshTypes.hpp>
    
#include <meti/RandUtils.hpp>

namespace builder {

model::Star*
Star::__genTemplate(int_t id)
{ 
    model::Star* model = new model::Star;
    model->setId(id);

    assert(model);
    core::global::get().entityManager().reg(model);
    return model;
} 
 
model::Star*
Star::gen()
{
    const auto& descr = descriptor::Manager::get().star().random();
    return gen(descr);
} 

model::Star*
Star::gen(descriptor::Star* descr)
{
    model::Star* model = __genTemplate();

    // Planetoid
    //model->setOrbitCenter(meti::vec3(0, 0, DEFAULT_ENTITY_ZPOS));
    model->setRadiusA(descr->radiusA());
    model->setRadiusB(descr->radiusB());
    model->setOrbitPhi(descr->orbitPhi());
    model->setSpeed(descr->speed());

    // Orientation
    model->setSize(descr->size());
    model->setDirection(descr->direction());

    LifeData data_life;
    data_life.armor = descr->armor();
    model->setLifeData(data_life);

    return model;
}
          
} // namespace builder


