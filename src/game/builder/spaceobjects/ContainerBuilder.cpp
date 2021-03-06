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


ContainerBuilder& ContainerBuilder::Instance()
{
    static ContainerBuilder instance;
    return instance;
}

ContainerBuilder::~ContainerBuilder()
{}

Container* ContainerBuilder::GetNewContainerTemplate(INTLONGEST id) const
{
    Container* container = nullptr;
    
    if (id == NONE_ID)
    {
        id = EntityIdGenerator::Instance().GetNextId();
    }
        
    try 
    { 
        container = new Container(id);
    }
    catch(std::bad_alloc)
    {
        Logger::Instance().Log("EXEPTION:bad_dynamic_memory_allocation\n");
    }
    EntityManager::Instance().RegisterEntity(container);
    
    return container;
} 

Container* ContainerBuilder::GetNewContainer(TextureOb* textureOb, BaseItem* item) const
{
    Container* container = GetNewContainerTemplate();
    CreateNewInternals(container, textureOb, item);
        
    return container;
} 

Container* ContainerBuilder::GetNewMineralContainer(int mineral_ammount) const
{
    TextureOb* textureOb = TextureManager::Instance().GetRandomTextureOb(TYPE::TEXTURE::MINERAL_ID);   
    GoodsPack* goods_pack = GetNewGoodsPack(TYPE::ENTITY::MINERALS_ID);
    goods_pack->Increase(mineral_ammount);

    Container* container = GetNewContainer(textureOb, goods_pack);
    
    return container;
} 
           
void ContainerBuilder::CreateNewInternals(Container* container, TextureOb* textureOb, BaseItem* item) const
{           
    LifeData data_life;
    data_life.armor = 1;
    data_life.dying_time = 30;
    
    container->SetLifeData(data_life);
    Mesh* mesh = MeshCollector::Instance().GetMeshByTypeId(TYPE::MESH::PLANE_ID);
    container->SetRenderData(mesh, textureOb, textureOb->GetSize());
 
    float delta_angle = 0.001*getRandInt(20, 60);
    AnimationConstantRotation* animation_rotation = new AnimationConstantRotation(delta_angle);
    container->SetAnimationRotation(animation_rotation);
    
    container->SetGivenExpirience(CONTAINER_GIVEN_EXPIRIENCE);
    
    ItemSlot* item_slot = GetNewItemSlot(TYPE::ENTITY::CARGO_SLOT_ID);
    
    container->BindItemSlot(item_slot);
    container->GetItemSlot()->InsertItem(item);
}





