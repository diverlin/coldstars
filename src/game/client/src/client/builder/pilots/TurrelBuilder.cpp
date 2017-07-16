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
#include <core/builder/CommonBuilderHeaders.hpp>
#include <core/model/spaceobject/Asteroid.hpp>
#include <core/spaceobject/Asteroid.hpp>
#include <core/descriptor/spaceobject/Asteroid.hpp>
#include <core/manager/DescriptorManager.hpp>
#include <core/generator/DescriptorGenerator.hpp>

namespace builder {

control::Turrel*
Turrel::gen()
{
    descriptor::Turrel* descr = nullptr;
    if (!descriptor::Manager::get().hasType(descriptor::Type::TURREL)) {
        descr = descriptor::genTurrel();
    } else {
        descr = descriptor::Manager::get().randTurrel();
    }
    assert(descr);
    return gen(descr);
}

control::Turrel*
Turrel::gen(descriptor::Turrel* descr)
{
    control::Turrel* turrel = __genTemplate(descr);

    /// Base
    LifeData life_data;
    life_data.armor = descr->armor();
    turrel->model()->setLifeData(life_data);

    /// Orientation
    turrel->model()->setSize(descr->size());
    turrel->model()->setDirection(descr->direction());

    return turrel;
} 

control::Turrel*
Turrel::__genTemplate(descriptor::Turrel* descr)
{
    model::Turrel* model = new model::Turrel(descr->id());
    assert(model);

    control::Turrel* turrel = new control::Turrel(descr, model);
    assert(turrel);

    //manager::Entities::get().add(turrel);

    return turrel;
}

} // namespace builder



