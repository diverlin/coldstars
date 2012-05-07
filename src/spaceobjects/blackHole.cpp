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
}

BlackHole::~BlackHole() {}
   
void BlackHole::SetEffect(BlackHoleEffect* effect) { this->effect = effect; } 
		
void BlackHole::UpdateInSpace(int time, bool show_effect)
{
	//updateRotation();
	//effect->update();
	if (time > 0)
	{}
}

void BlackHole::UpdateInfo()
{
	info.clear();

    	info.addTitleStr("BLACKHOLE");

    	//info.addNameStr("id/ss_id:");    info.addValueStr(int2str(data_id.id) + " / " + int2str(starsystem->GetId()));
    	info.addNameStr("id:");          info.addValueStr(int2str(data_id.id));
    	info.addNameStr("mass:");        info.addValueStr(int2str(mass));
}
            
void BlackHole::RenderInfoInSpace(vec2f scroll_coords)
{
	UpdateInfo();
     	drawInfoIn2Column(&info.title_list, &info.value_list, points.GetCenter().x, points.GetCenter().y, scroll_coords.x, scroll_coords.y);    
}

void BlackHole::Render2D() const
{
	//effect->Render();
}

/*virtual*/
void BlackHole::SaveData(boost::property_tree::ptree&) const
{

}

/*virtual*/		
void BlackHole::LoadData(boost::property_tree::ptree&)
{

}
	
/*virtual*/	
void BlackHole::ResolveData()
{

}

BlackHole* GetNewBlackHole()
{
        int id         = g_ID_GENERATOR.getNextId();
        
        LifeData data_life;
        data_life.is_alive   = true;
        data_life.garbage_ready = false;
    	data_life.armor      = 100000;
        data_life.dying_time = 30;        
        
	TextureOb* texOb = g_TEXTURE_MANAGER.GetRandomTextureOb(TEXTURE::BLACKHOLE_ID); 
	
	BlackHole* blackhole = new BlackHole(id);

	blackhole->SetLifeData(data_life);
	blackhole->SetTextureOb(texOb);
	
   	//blackhole->CalcCollisionrRadius();
	
	return blackhole;
}




