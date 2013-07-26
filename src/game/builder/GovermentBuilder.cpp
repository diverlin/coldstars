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

#include "GovermentBuilder.hpp"

#include "../docking/Goverment.hpp"

#include "../common/IdGenerator.hpp"
#include "../common/Logger.hpp"
#include "../world/EntityManager.hpp"
#include "../resources/TextureManager.hpp"

GovermentBuilder& GovermentBuilder::Instance()
{
	static GovermentBuilder instance;
	return instance;
}

GovermentBuilder::~GovermentBuilder()
{}

Goverment* GovermentBuilder::GetNewGovermentTemplate(INTLONGEST id) const
{
	Goverment* goverment = nullptr;
	
	if (id == NONE_ID)
	{
		id = EntityIdGenerator::Instance().GetNextId();
	}

    try 
    { 
        goverment = new Goverment(id);
    }
    catch(std::bad_alloc)
    {
        Logger::Instance().Log("EXEPTION:bad_dynamic_memory_allocation\n");
    }
    EntityManager::Instance().RegisterEntity(goverment);
    
    return goverment;
} 

Goverment* GovermentBuilder::GetNewGoverment() const
{
	Goverment* goverment = GetNewGovermentTemplate();
	CreateNewInternals(goverment);
        
        return goverment;
} 
    	
void GovermentBuilder::CreateNewInternals(Goverment* goverment) const
{
	TextureOb* textureOb_face  = TextureManager::Instance().GetRandomTextureOb(TEXTURE::GOVERMENT_BACKGROUND_ID); 
	goverment->SetTextureObFace(textureOb_face);
		        
	TextureOb* textureOb_background  = TextureManager::Instance().GetRandomTextureOb(TEXTURE::GOVERMENT_BACKGROUND_ID); 
	goverment->SetTextureObBackground(textureOb_background);

}

