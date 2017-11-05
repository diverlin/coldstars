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
#ifdef USE_ARTEFACTS
#include <builder/item/artefacts/GravityArtefactBuilder.hpp>
#include <builder/item/artefacts/ProtectorArtefactBuilder.hpp>
#endif // USE_ARTEFACTS
#include <builder/CommonBuilderHeaders.hpp>

#ifdef USE_ARTEFACTS
#include <core/item/artefacts/GravityArtefact.hpp>
#include <core/item/artefacts/ProtectorArtefact.hpp>
#endif // USE_ARTEFACTS

#include <core/descriptor/dock/NatureLand.hpp>
#include <core/model/dock/NatureLand.hpp>
#include <core/dock/NatureLand.hpp>

#include <core/slot/ItemSlot.hpp>

#include <core/session/Shortcuts.hpp>
#include <core/manager/DescriptorManager.hpp>
#include <core/generator/DescriptorGenerator.hpp>

#include <common/constants.hpp>

//#include <meti/RandUtils.hpp>

namespace builder {

control::NatureLand*
NatureLand::gen()
{
    descriptor::NatureLand* descr = nullptr;
    if (!core::shortcuts::descriptors()->hasType(descriptor::Type::NATURELAND)) {
        descr = descriptor::genNatureLand();
    } else {
        descr = core::shortcuts::descriptors()->randNatureLand();
    }
    assert(descr);
    return gen(descr);
} 

control::NatureLand*
NatureLand::gen(descriptor::NatureLand* descr)
{
    control::NatureLand* natureland = __createTemplate(descr);
    __createInternals(natureland);

    return natureland;
}

control::NatureLand*
NatureLand::__createTemplate(descriptor::NatureLand* descr)
{
    model::NatureLand* model = new model::NatureLand(descr->id());
    assert(model);

    control::NatureLand* natureland = new control::NatureLand(descr, model);
    assert(natureland);

    core::shortcuts::entities()->add(natureland);

    return natureland;
}

void
NatureLand::__createInternals(control::NatureLand* natureland)
{
    //natureland->SetTextureObBackground(TextureCollector::Instance().getTextureByTypeId(TYPE::TEXTURE::NATURELAND_BACKGROUND));

    unsigned int item_slot_num = meti::rand::gen_int(NATURELAND_ITEM_SLOT_MIN, NATURELAND_ITEM_SLOT_MAX);
    assert(item_slot_num<=SLOT_CARGO_TYPES.size());
    for (unsigned int i=0; i<item_slot_num; i++) {
        slot::Item* item_slot = new slot::Item(entity::Group::CARGO_SLOT, SLOT_CARGO_TYPES[i]);
        natureland->add(item_slot);
    }
    
    for (unsigned int i=0; i<item_slot_num; i++)
    {
        if (natureland->canAcceptNewItem() == true)
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

} // namespace builder

