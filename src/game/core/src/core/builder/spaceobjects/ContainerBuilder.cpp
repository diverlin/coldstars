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

#include <builder/spaceobjects/ContainerBuilder.hpp>
#include <builder/slots/ItemSlotBuilder.hpp>
#include <builder/CommonBuilderHeaders.hpp>

#include <spaceobjects/Container.hpp>

#include <descriptor/Base.hpp>
#include <descriptor/DescriptorManager.hpp>
#include <descriptor/Container.hpp>

#include <slots/ItemSlot.hpp>

#include <item/others/GoodsPack.hpp>

#include <meti/RandUtils.hpp>

namespace builder {

Container::Container()
{}

Container::~Container()
{}

model::Container*
Container::getNew()
{
    const auto& descriptor = core::global::get().descriptors().getRand(descriptor::Type::CONTAINER);
    return getNew(descriptor);
}

model::Container*
Container::getNew(const std::string& data)
{
    return getNew(descriptor::Container(data));
}

model::Container*
Container::getNew(const descriptor::BaseOLD& descriptor)
{
    model::Container* container = __getNewTemplate();
    __createInternals(container, descriptor);
    return container;
}

model::Container*
Container::__getNewTemplate()
{
    model::Container* container = new model::Container;
    assert(container);
    core::global::get().entityManager().reg(container);
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
//    //jeti::control::TextureOb* textureOb = TextureCollector::Instance().getTextureByTypeId(TYPE::TEXTURE::MINERAL_ID);
//    GoodsPack* goods_pack = GetNewGoodsPack(entity::Type::MINERALS_ID);
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
//    //jeti::Mesh* mesh = MeshCollector::Instance().getMesh(mesh::type::PLANE_ID);
//    //alpitodorender container->SetRenderData(mesh, textureOb, textureOb->size());

//    float delta_angle = 0.001*meti::getRandInt(20, 60);
//    //jeti::AnimationConstantRotation* animation_rotation = new jeti::AnimationConstantRotation(delta_angle);
//    //alpitodorender container->SetAnimationRotation(animation_rotation);

//    container->setGivenExpirience(CONTAINER_GIVEN_EXPIRIENCE);

//    ItemSlot* item_slot = GetNewItemSlot(entity::Type::CARGO_SLOT_ID);

//    container->bindItemSlot(item_slot);
//    container->itemSlot()->insertItem(item);
//}

//void ContainerBuilder::createInternals(Container* container, BaseItem* item) const
//{
//    LifeData data_life;
//    data_life.armor = 1;
//    data_life.dying_time = 30;

//    container->setLifeData(data_life);
//    //jeti::Mesh* mesh = MeshCollector::Instance().getMesh(mesh::type::PLANE_ID);
//    //alpitodorender container->SetRenderData(mesh, textureOb, textureOb->size());

//    float delta_angle = 0.001*meti::getRandInt(20, 60);
//    //jeti::AnimationConstantRotation* animation_rotation = new jeti::AnimationConstantRotation(delta_angle);
//    //alpitodorender container->SetAnimationRotation(animation_rotation);

//    container->setGivenExpirience(CONTAINER_GIVEN_EXPIRIENCE);

//    ItemSlot* item_slot = GetNewItemSlot(entity::Type::CARGO_SLOT_ID);

//    container->bindItemSlot(item_slot);
//    container->itemSlot()->insertItem(item);
//}

void
Container::__createInternals(model::Container* container, const descriptor::BaseOLD& descriptor)
{
    LifeData data_life;
    data_life.armor = 1;
    data_life.dying_time = 30;

    assert(false);
//    container->setLifeData(data_life);

//    ItemSlot* item_slot = getNewItemSlot(entity::Type::CARGO_SLOT_ID);
//    container->bindItemSlot(item_slot);

    //    if (descriptor.child() >= 0) {
    //        item::Base* item = static_cast<item::Base*>(core::global::get().entityManager().get(descriptor.child()));
    //        item_slot->insertItem(item);
    //    }
}

} // namespace builder
