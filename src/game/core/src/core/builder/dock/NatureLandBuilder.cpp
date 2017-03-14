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


#include <builder/dock/NatureLandBuilder.hpp>
#include <core/builder/slot/ItemSlotBuilder.hpp>
#ifdef USE_ARTEFACTS
#include <builder/item/artefacts/GravityArtefactBuilder.hpp>
#include <builder/item/artefacts/ProtectorArtefactBuilder.hpp>
#endif // USE_ARTEFACTS
#include <builder/CommonBuilderHeaders.hpp>

#ifdef USE_ARTEFACTS
#include <core/item/artefacts/GravityArtefact.hpp>
#include <core/item/artefacts/ProtectorArtefact.hpp>
#endif // USE_ARTEFACTS

#include <dock/NatureLand.hpp>

#include <common/constants.hpp>

#include <meti/RandUtils.hpp>


NatureLandBuilder::NatureLandBuilder()
{}

NatureLandBuilder::~NatureLandBuilder()
{}

NatureLand* NatureLandBuilder::createTemplate(int_t id) const
{
    NatureLand* natureland = new NatureLand(id);
    assert(natureland);

    assert(false);
//    core::global::get().entityManager().reg(natureland);
    
    return natureland;
} 

NatureLand* NatureLandBuilder::create() const
{
    NatureLand* natureland = createTemplate();
    createInternals(natureland);

    return natureland;
} 

void NatureLandBuilder::createInternals(NatureLand* natureland) const
{
    //natureland->SetTextureObBackground(TextureCollector::Instance().getTextureByTypeId(TYPE::TEXTURE::NATURELAND_BACKGROUND));
    
    unsigned int item_slot_num = meti::getRandInt(NATURELAND_ITEM_SLOT_MIN, NATURELAND_ITEM_SLOT_MAX);
    for (unsigned int i=0; i<item_slot_num; i++) {
        control::ItemSlot* item_slot = getNewItemSlot(entity::Type::CARGO_SLOT);
        natureland->AddItemSlot(item_slot);
    }
    
    for (unsigned int i=0; i<item_slot_num; i++)
    {
        if (natureland->CanAcceptNewItem() == true)
        {
            //int type_id = getRandInt(ENTITY::GRAVITY_ARTEFACT, ENTITY::PROTECTOR_ARTEFACT);
            //switch (type_id)
            //{
            //case ENTITY::GRAVITY_ARTEFACT:
            //{
            //natureland->AddItem(GravityArtefactBuilder::Instance().GetNewGravityArtefact());
            //break;
            //}

            //case ENTITY::PROTECTOR_ARTEFACT:
            //{
            //natureland->AddItem(ProtectorArtefactBuilder::Instance().GetNewProtectorArtefact());
            //break;
            //}
            //}
        }
    }
}


