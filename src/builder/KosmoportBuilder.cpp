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


KosmoportBuilder& KosmoportBuilder::Instance()
{
	static KosmoportBuilder instance;
	return instance;
}

KosmoportBuilder::~KosmoportBuilder()
{}

void KosmoportBuilder::CreateNewKosmoport(int id)
{
	if (id == NONE_ID)
	{
		id = g_ID_GENERATOR.getNextId();
	}
        kosmoport = new Kosmoport(id);
        EntityManager::Instance().RegisterEntity(kosmoport);
} 
        	
void KosmoportBuilder::CreateNewInternals()
{
	AngarBuilder::Instance().CreateNewAngar();
	AngarBuilder::Instance().CreateNewInternals();	
	kosmoport->BindAngar(AngarBuilder::Instance().GetAngar());

	StoreBuilder::Instance().CreateNewStore();
	StoreBuilder::Instance().CreateNewInternals();	
	StoreBuilder::Instance().PutRandomEquipment();	
	kosmoport->BindStore(StoreBuilder::Instance().GetStore());

	ShopBuilder::Instance().CreateNewShop();
	ShopBuilder::Instance().CreateNewInternals();	
	kosmoport->BindShop(ShopBuilder::Instance().GetShop());
		        	
	GovermentBuilder::Instance().CreateNewGoverment();
	GovermentBuilder::Instance().CreateNewInternals();	
	kosmoport->BindGoverment(GovermentBuilder::Instance().GetGoverment());
}

  	
