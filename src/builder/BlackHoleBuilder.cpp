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

#include "BlackHoleBuilder.hpp"
#include "../spaceobjects/BlackHole.hpp"
#include "../common/id.hpp"
#include "../common/Logger.hpp"
#include "../world/EntityManager.hpp"
#include "../common/rand.hpp"
#include "../resources/TextureManager.hpp"
#include "../resources/MeshCollector.hpp"

BlackHoleBuilder& BlackHoleBuilder::Instance()
{
	static BlackHoleBuilder instance;
	return instance;
}

BlackHoleBuilder::~BlackHoleBuilder()
{}

BlackHole* BlackHoleBuilder::GetNewBlackHoleTemplate(int id) const
{
	BlackHole* blackhole = NULL;
	
	if (id == NONE_ID)
	{
		id = SimpleIdGenerator::Instance().GetNextId();
	}

        try 
        { 
        	blackhole = new BlackHole(id); 
        }
        catch(std::bad_alloc)
        {
        	Logger::Instance().Log("EXEPTION:bad_dynamic_memory_allocation\n");
        }

	int size = 4;
    	bool dynamic = false;
       	blackhole->BindShockWaveEffect(GetNewShockWave(size, dynamic)); 
        EntityManager::Instance().RegisterEntity(blackhole);
        
        return blackhole;
} 

BlackHole* BlackHoleBuilder::GetNewBlackHole() const
{
	BlackHole* blackhole = GetNewBlackHoleTemplate();
	CreateNewInternals(blackhole);
        
        return blackhole;
} 
       	
void BlackHoleBuilder::CreateNewInternals(BlackHole* blackhole) const
{           
        LifeData data_life;
        data_life.is_alive   = true;
        data_life.garbage_ready = false;
    	data_life.armor      = 100000;
        data_life.life_time = getRandInt(250, 500);     
        data_life.dying_time = 2;        
        
	TextureOb* texOb = TextureManager::Instance().GetRandomTextureOb(TEXTURE::BLACKHOLE_ID); 
	vec3f d_angle(0.0, 0.0, 10.0); 		
                
	blackhole->SetLifeData(data_life);
	blackhole->SetTextureOb(texOb);
	blackhole->SetMesh(MeshCollector::Instance().GetMeshByTypeId(MESH::SPHERE_NORMAL_ID));	
	
	blackhole->SetDeltaAngle(d_angle);
	blackhole->SetScale(30);
	
	blackhole->CalcCollisionrRadius();
}





