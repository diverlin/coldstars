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

#include "KosmoportBuilder.hpp"
#include "../docking/Kosmoport.hpp"

#include "AngarBuilder.hpp"
#include "StoreBuilder.hpp"
#include "ShopBuilder.hpp"
#include "GovermentBuilder.hpp"

#include "../common/id.hpp"
#include "../common/Logger.hpp"
#include "../managers/EntityManager.hpp"

KosmoportBuilder& KosmoportBuilder::Instance()
{
	static KosmoportBuilder instance;
	return instance;
}

KosmoportBuilder::~KosmoportBuilder()
{}

Kosmoport* KosmoportBuilder::GetNewKosmoportTemplate(int id) const
{
	Kosmoport* kosmoport = NULL;
	
	if (id == NONE_ID)
	{
		id = SimpleIdGenerator::Instance().GetNextId();
	}

        try 
        { 
        	kosmoport = new Kosmoport(id);
        }
        catch(std::bad_alloc)
        {
        	Logger::Instance().Log("EXEPTION:bad_dynamic_memory_allocation\n");
        }
        
        EntityManager::Instance().RegisterEntity(kosmoport);
        
        return kosmoport;
} 

Kosmoport* KosmoportBuilder::GetNewKosmoport() const
{
	Kosmoport* kosmoport = GetNewKosmoportTemplate();
	CreateNewInternals(kosmoport);
        
        return kosmoport;
} 
       	
void KosmoportBuilder::CreateNewInternals(Kosmoport* kosmoport) const
{
	kosmoport->BindAngar(AngarBuilder::Instance().GetNewAngar());
	kosmoport->BindStore(StoreBuilder::Instance().GetNewStore());
	kosmoport->BindShop(ShopBuilder::Instance().GetNewShop());
	kosmoport->BindGoverment(GovermentBuilder::Instance().GetNewGoverment());
}

  	
