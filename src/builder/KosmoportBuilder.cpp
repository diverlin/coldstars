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
        TextureOb* _texOb_slot = g_TEXTURE_MANAGER.GetRandomTextureOb(TEXTURE::SLOT_ID);
        TextureOb* _texOb_landingArea = g_TEXTURE_MANAGER.GetRandomTextureOb(TEXTURE::LANDINGAREA_ID);
        
        TextureOb* _texOb_angarBackground  = g_TEXTURE_MANAGER.GetRandomTextureOb(TEXTURE::ANGAR_BACKGROUND_ID);   
        TextureOb* _texOb_storeBackground  = g_TEXTURE_MANAGER.GetRandomTextureOb(TEXTURE::STORE_BACKGROUND_ID);    
        TextureOb* _texOb_shopBackground   = g_TEXTURE_MANAGER.GetRandomTextureOb(TEXTURE::SHOP_BACKGROUND_ID);    
        TextureOb* _texOb_govermentBackground = g_TEXTURE_MANAGER.GetRandomTextureOb(TEXTURE::GOVERMENT_BACKGROUND_ID);    

        Angar* angar         = new Angar(_texOb_angarBackground, _texOb_landingArea);
        Store* store         = new Store(_texOb_storeBackground, _texOb_slot);
        Shop* shop           = new Shop(_texOb_shopBackground);
        Goverment* goverment = new Goverment(_texOb_govermentBackground, _texOb_slot);
        
        equipStore(store);
        
        kosmoport->SetAngar(angar);
        kosmoport->SetStore(store);
        kosmoport->SetShop(shop);
        kosmoport->SetGoverment(goverment);
}

  	
