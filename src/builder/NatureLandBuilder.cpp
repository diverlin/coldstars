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

#include "NatureLandBuilder.hpp"
#include "../docking/NatureLand.hpp"

#include "../common/id.hpp"
#include "../common/Logger.hpp"
#include "../common/EntityManager.hpp"

#include "../resources/TextureManager.hpp"

NatureLandBuilder& NatureLandBuilder::Instance()
{
	static NatureLandBuilder instance;
	return instance;
}

NatureLandBuilder::~NatureLandBuilder()
{}

NatureLand* NatureLandBuilder::GetNewNatureLandTemplate(int id) const
{
	NatureLand* natureland = NULL;
	
	if (id == NONE_ID)
	{
		id = SimpleIdGenerator::Instance().GetNextId();
	}

        try 
        { 
        	natureland = new NatureLand(id);
        }
        catch(std::bad_alloc)
        {
        	Logger::Instance().Log("EXEPTION:bad_dynamic_memory_allocation\n");
        }
        
        EntityManager::Instance().RegisterEntity(natureland);
        
        return natureland;
} 

NatureLand* NatureLandBuilder::GetNewNatureLand() const
{
	NatureLand* natureland = GetNewNatureLandTemplate();
	CreateNewInternals(natureland);
        
        return natureland;
} 
       	
void NatureLandBuilder::CreateNewInternals(NatureLand* natureland) const
{
	natureland->SetTextureObBackground(TextureManager::Instance().GetRandomTextureOb(TEXTURE::NATURELAND_BACKGROUND_ID));
}

  	
