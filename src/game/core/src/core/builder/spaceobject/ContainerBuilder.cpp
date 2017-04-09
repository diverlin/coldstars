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

#include <core/builder/spaceobject/ContainerBuilder.hpp>
#include <builder/CommonBuilderHeaders.hpp>

#include <core/spaceobject/Container.hpp>

#include <descriptor/Base.hpp>
#include <core/manager/DescriptorManager.hpp>
#include <core/descriptor/spaceobject/Container.hpp>
#include <core/model/spaceobject/Container.hpp>
#include <core/spaceobject/Container.hpp>

#include <core/generator/DescriptorGenerator.hpp>

#include <core/slot/ItemSlot.hpp>

#include <core/item/other/GoodsPack.hpp>

#include <meti/RandUtils.hpp>

namespace builder {

control::Container*
Container::gen()
{
    descriptor::Container* descr = nullptr;
    if (!descriptor::Manager::get().hasType(descriptor::Type::CONTAINER)) {
        descr = descriptor::genContainer();
    } else {
        descr = descriptor::Manager::get().randContainer();
    }
    assert(descr);
    return gen(descr);
}

control::Container*
Container::gen(descriptor::Container* descr)
{
    control::Container* container = __genTemplate(descr);
    __createInternals(container, descr);
    return container;
}

control::Container*
Container::__genTemplate(descriptor::Container* descr)
{
    model::Container* model = new model::Container(descr->id());
    assert(model);

    control::Container* container = new control::Container(descr, model);
    assert(container);

    EntityManager::get().add(container);
    return container;
}

//Container*
//ContainerBuilder::create(jeti::control::TextureOb* textureOb, BaseItem* item) const
//{
//    Container* container = createTemplate();
//    createInternals(container, textureOb, item);

//    return container;
//}

//Container* ContainerBuilder::create(item::Base* item) const
//{
//    Container* container = createTemplate();
//    createInternals(container, item);

//    return container;
//}

//Container* ContainerBuilder::create(int mineral_ammount) const
//{
//    //jeti::control::TextureOb* textureOb = TextureCollector::Instance().getTextureByTypeId(TYPE::TEXTURE::MINERAL);
//    GoodsPack* goods_pack = GetNewGoodsPack(entity::Type::MINERALS);
//    goods_pack->Increase(mineral_ammount);

//    //Container* container = GetNewContainer(textureOb, goods_pack);
//    Container* container = nullptr;
//    assert(container);
//    return container;
//}

//void ContainerBuilder::createInternals(Container* container, jeti::control::TextureOb* textureOb, BaseItem* item) const
//{
//    LifeData data_life;
//    data_life.armor = 1;
//    data_life.dying_time = 30;

//    container->setLifeData(data_life);
//    //jeti::Mesh* mesh = MeshCollector::Instance().getMesh(mesh::type::PLANE);
//    //alpitodorender container->SetRenderData(mesh, textureOb, textureOb->size());

//    float delta_angle = 0.001*meti::getRandInt(20, 60);
//    //jeti::AnimationConstantRotation* animation_rotation = new jeti::AnimationConstantRotation(delta_angle);
//    //alpitodorender container->SetAnimationRotation(animation_rotation);

//    container->setGivenExpirience(CONTAINER_GIVEN_EXPIRIENCE);

//    slot::ItemSlot* item_slot = GetNewItemSlot(entity::Type::CARGO_SLOT);

//    container->bindItemSlot(item_slot);
//    container->itemSlot()->insertItem(item);
//}

//void ContainerBuilder::createInternals(Container* container, BaseItem* item) const
//{
//    LifeData data_life;
//    data_life.armor = 1;
//    data_life.dying_time = 30;

//    container->setLifeData(data_life);
//    //jeti::Mesh* mesh = MeshCollector::Instance().getMesh(mesh::type::PLANE);
//    //alpitodorender container->SetRenderData(mesh, textureOb, textureOb->size());

//    float delta_angle = 0.001*meti::getRandInt(20, 60);
//    //jeti::AnimationConstantRotation* animation_rotation = new jeti::AnimationConstantRotation(delta_angle);
//    //alpitodorender container->SetAnimationRotation(animation_rotation);

//    container->setGivenExpirience(CONTAINER_GIVEN_EXPIRIENCE);

//    slot::ItemSlot* item_slot = GetNewItemSlot(entity::Type::CARGO_SLOT);

//    container->bindItemSlot(item_slot);
//    container->itemSlot()->insertItem(item);
//}

void
Container::__createInternals(control::Container* container, descriptor::Container* desr)
{
    LifeData data_life;
    data_life.armor = 1;
    data_life.dying_time = 30;

    container->model()->setLifeData(data_life);
}

} // namespace builder

