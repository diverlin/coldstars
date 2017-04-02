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


#include <builder/dock/GovermentBuilder.hpp>
#include <builder/CommonBuilderHeaders.hpp>

#include <core/descriptor/dock/Goverment.hpp>
#include <core/model/dock/Goverment.hpp>
#include <core/dock/Goverment.hpp>

#include <core/manager/DescriptorManager.hpp>
#include <core/generator/DescriptorGenerator.hpp>

namespace builder {

control::Goverment*
Goverment::gen()
{
    descriptor::Goverment* descr = nullptr;
    if (!descriptor::Manager::get().hasType(descriptor::Type::GOVERMENT)) {
        descr = descriptor::genGoverment();
    } else {
        descr = descriptor::Manager::get().randGoverment();
    }
    return gen(descr);
}

control::Goverment*
Goverment::gen(descriptor::Goverment* descr)
{
    control::Goverment* goverment = __createTemplate(descr);
    __createInternals(goverment);

    return goverment;
} 

control::Goverment*
Goverment::__createTemplate(descriptor::Goverment* descr)
{
    model::Goverment* model = new model::Goverment(descr->id());
    assert(model);

    control::Goverment* goverment = new control::Goverment(descr, model);
    assert(goverment);

    EntityManager::get().reg(goverment);

    return goverment;
}

void
Goverment::__createInternals(control::Goverment* goverment)
{
    //jeti::control::TextureOb* textureOb_face  = TextureCollector::Instance().getTextureByTypeId(TYPE::TEXTURE::GOVERMENT_BACKGROUND);
    //goverment->SetTextureObFace(textureOb_face);

    //jeti::control::TextureOb* textureOb_background  = TextureCollector::Instance().getTextureByTypeId(TYPE::TEXTURE::GOVERMENT_BACKGROUND);
    //goverment->SetTextureObBackground(textureOb_background);

}

} // namespace builder
