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

#include <slots/ItemSlot.hpp>

#include <items/others/GoodsPack.hpp>

#include <meti/RandUtils.hpp>


ContainerBuilder::ContainerBuilder()
{}

ContainerBuilder::~ContainerBuilder()
{}

Container* ContainerBuilder::createTemplate(INTLONGEST id) const
{       
    Container* container = new Container(id);
    assert(container);

    global::get().entitiesManager().RegisterEntity(container);
    
    return container;
} 

Container* ContainerBuilder::create(jeti::TextureOb* textureOb, BaseItem* item) const
{
    Container* container = createTemplate();
    createInternals(container, textureOb, item);
        
    return container;
} 

Container* ContainerBuilder::create(int mineral_ammount) const
{
    //jeti::TextureOb* textureOb = TextureCollector::Instance().getTextureByTypeId(TYPE::TEXTURE::MINERAL_ID);
    GoodsPack* goods_pack = GetNewGoodsPack(TYPE::ENTITY::MINERALS_ID);
    goods_pack->Increase(mineral_ammount);

    //Container* container = GetNewContainer(textureOb, goods_pack);
    Container* container = nullptr;
    assert(container);
    return container;
} 
           
void ContainerBuilder::createInternals(Container* container, jeti::TextureOb* textureOb, BaseItem* item) const
{           
    LifeData data_life;
    data_life.armor = 1;
    data_life.dying_time = 30;
    
    container->setLifeData(data_life);
    //jeti::Mesh* mesh = MeshCollector::Instance().getMesh(TYPE::MESH::PLANE_ID);
    //alpitodorender container->SetRenderData(mesh, textureOb, textureOb->size());
 
    float delta_angle = 0.001*meti::getRandInt(20, 60);
    //jeti::AnimationConstantRotation* animation_rotation = new jeti::AnimationConstantRotation(delta_angle);
    //alpitodorender container->SetAnimationRotation(animation_rotation);
    
    container->setGivenExpirience(CONTAINER_GIVEN_EXPIRIENCE);
    
    ItemSlot* item_slot = GetNewItemSlot(TYPE::ENTITY::CARGO_SLOT_ID);
    
    container->BindItemSlot(item_slot);
    container->GetItemSlot()->InsertItem(item);
}





