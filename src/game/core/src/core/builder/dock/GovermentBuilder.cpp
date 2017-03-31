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

#include <dock/Goverment.hpp>

namespace builder {

control::Goverment*
GovermentBuilder::gen()
{
    control::Goverment* goverment = __createTemplate();
    __createInternals(goverment);

    return goverment;
} 

control::Goverment*
GovermentBuilder::__createTemplate(int_t id)
{
    control::Goverment* goverment = new control::Goverment(id);
    assert(goverment);

    EntityManager::get().reg(goverment);

    return goverment;
}

void
GovermentBuilder::__createInternals(control::Goverment* goverment)
{
    //jeti::control::TextureOb* textureOb_face  = TextureCollector::Instance().getTextureByTypeId(TYPE::TEXTURE::GOVERMENT_BACKGROUND);
    //goverment->SetTextureObFace(textureOb_face);

    //jeti::control::TextureOb* textureOb_background  = TextureCollector::Instance().getTextureByTypeId(TYPE::TEXTURE::GOVERMENT_BACKGROUND);
    //goverment->SetTextureObBackground(textureOb_background);

}

} // namespace builder
