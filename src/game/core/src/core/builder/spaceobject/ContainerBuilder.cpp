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
#include <core/descriptor/spaceobject/Container.hpp>
#include <core/model/spaceobject/Container.hpp>
#include <core/spaceobject/Container.hpp>

#include <core/session/Shortcuts.hpp>
#include <core/manager/DescriptorManager.hpp>
#include <core/generator/DescriptorGenerator.hpp>

#include <core/slot/ItemSlot.hpp>

#include <core/item/other/Goods.hpp>

#include <meti/RandUtils.hpp>

namespace builder {

core::control::Container*
ContainerBuilder::gen()
{
    descriptor::Container* descr = nullptr;
    if (!core::shortcuts::descriptors()->hasType(descriptor::Type::CONTAINER)) {
        descr = descriptor::genContainer();
    } else {
        descr = core::shortcuts::descriptors()->randContainer();
    }
    assert(descr);
    return gen(descr);
}

core::control::Container*
ContainerBuilder::gen(descriptor::Container* descr)
{
    core::control::Container* container = __genTemplate(descr);
    __createInternals(container, descr);
    return container;
}

core::control::Container*
ContainerBuilder::gen(int_t descriptor_id, int_t object_id)
{
    descriptor::Container* descriptor = core::shortcuts::descriptors()->container(descriptor_id);
    core::control::Container* container = __genTemplate(descriptor, object_id);
    __createInternals(container, descriptor);
    return container;
}

core::control::Container*
ContainerBuilder::gen(int_t descriptor_id, int_t object_id, int_t item_id)
{
    descriptor::Container* descriptor = core::shortcuts::descriptors()->container(descriptor_id);
    core::control::Container* container = __genTemplate(descriptor, object_id);
    __createInternals(container, descriptor);

    core::control::Item* item = core::shortcuts::entities()->item(item_id);
    container->insert(item);

    return container;
}

core::control::Container*
ContainerBuilder::__genTemplate(descriptor::Container* descriptor, int_t object_id)
{
    model::Container* model = new model::Container(descriptor->id(), object_id);
    assert(model);

    core::control::Container* container = new core::control::Container(descriptor, model);
    assert(container);

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

//    ItemSlot* item_slot = GetNewItemSlot(entity::Type::CARGO_SLOT);

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

//    ItemSlot* item_slot = GetNewItemSlot(entity::Type::CARGO_SLOT);

//    container->bindItemSlot(item_slot);
//    container->itemSlot()->insertItem(item);
//}

void
ContainerBuilder::__createInternals(core::control::Container* container, descriptor::Container* desr)
{
    container->model()->setArmor(1);
}

} // namespace builder

