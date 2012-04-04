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


NpcBuilder& NpcBuilder::Instance()
{
	static NpcBuilder instance;
	return instance;
}

NpcBuilder::~NpcBuilder()
{}

void NpcBuilder::CreateNewNpc(int race_id, int subtype_id)
{
        IdData data_id;
    	data_id.id         = g_ID_GENERATOR.getNextId(); 
    	data_id.type_id    = ENTITY::NPC_ID;
    	data_id.subtype_id = subtype_id;
    	
    	LifeData data_life;
    	
       	TextureOb* texOb_face  = g_TEXTURE_MANAGER.getRandomFaceTexObWithFolloingAttributes(race_id);
	npc = new Npc(race_id);
        npc->SetTextureOb(texOb_face);
        npc->SetIdData(data_id);
        npc->SetLifeData(data_life);        
	
	GetEntityManager().RegisterEntity(npc);
} 
        	
void NpcBuilder::CreateNewInternals()
{    

}
