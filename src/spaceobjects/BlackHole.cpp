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



BlackHole::BlackHole(int id)
{        
	data_id.id = id;
	data_id.type_id = ENTITY::BLACKHOLE_ID;
	
    	mass = getRandInt(1000, 4000);
    	
    	int size = 4;
    	bool dynamic = false;
       	shock_wave = GetNewShockWave(size, dynamic); 
}

/* virtual */
BlackHole::~BlackHole() 
{
	//delete shock_wave; delete from outside, starsystem of shockwaves effects vec in destructor
} 
 
void BlackHole::UpdateInSpace(int time, bool show_effect)
{
	UpdateRotation();
	if (time > 0)
	{
		points.SetCenter(points.GetCenter()+vec2f(0.1, 0.1)); // hack
		shock_wave->SetCenter(points.GetCenter());
	}
}

void BlackHole::UpdateInfo()
{
	info.clear();

    	info.addTitleStr("BLACKHOLE");

    	//info.addNameStr("id/ss_id:");    info.addValueStr(int2str(data_id.id) + " / " + int2str(starsystem->GetId()));
    	info.addNameStr("id:");          info.addValueStr(int2str(data_id.id));
    	info.addNameStr("mass:");        info.addValueStr(int2str(mass));
}
            
/*virtual*/
void BlackHole::SaveData(boost::property_tree::ptree&) const
{

}

/*virtual*/		
void BlackHole::LoadData(const boost::property_tree::ptree&)
{

}
	
/*virtual*/	
void BlackHole::ResolveData()
{

}

BlackHole* GetNewBlackHole()
{
        int id = SimpleIdGenerator::Instance().GetNextId();
        
        LifeData data_life;
        data_life.is_alive   = true;
        data_life.garbage_ready = false;
    	data_life.armor      = 100000;
        data_life.dying_time = 30;        
        
	TextureOb* texOb = TextureManager::Instance().GetRandomTextureOb(TEXTURE::BLACKHOLE_ID); 
	vec3f d_angle(0.0, 0.0, 10.0); 		
       
	BlackHole* blackhole = new BlackHole(id);
                
	blackhole->SetLifeData(data_life);
	blackhole->SetTextureOb(texOb);
	blackhole->SetMesh(MeshCollector.SPHERE_MESH);	
	
	blackhole->SetDeltaAngle(d_angle);
	blackhole->SetScale(30);
	
	blackhole->CalcCollisionrRadius();
	
	return blackhole;
}




