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



Mineral::Mineral(int id)
{        
	data_id.id         = id;
	data_id.type_id    = ENTITY::MINERAL_ID;
	data_id.subtype_id = NONE_ID;
        
    	mass = getRandInt(1, 4);
    	velocity = getRandInt(40, 42) / 100.0;
}
    
    
void Mineral::UpdateInfo()
{
	info.clear();

    	info.addTitleStr("MINERAL");

    	info.addNameStr("id/ss_id:");    info.addValueStr(int2str(data_id.id) + " / " + int2str(starsystem->GetId()));
    	info.addNameStr("armor:");       info.addValueStr(int2str(data_life.armor));
    	info.addNameStr("mass:");        info.addValueStr(int2str(mass));
}
            

void Mineral::RenderInfoInSpace(vec2f scroll_coords)
{
	UpdateInfo();
     	drawInfoIn2Column(&info.title_list, &info.value_list, points.getCenter().x, points.getCenter().y, scroll_coords.x, scroll_coords.y);    
}


/*virtual*/
void Mineral::SaveData(boost::property_tree::ptree&) const
{

}

/*virtual*/		
void Mineral::LoadData(boost::property_tree::ptree&)
{

}
	
/*virtual*/	
void Mineral::ResolveData()
{

}

Mineral* GetNewMineral()
{
        int id = g_ID_GENERATOR.getNextId();
    	        
        LifeData data_life;
        data_life.is_alive   = true;
        data_life.garbage_ready = false;
    	data_life.armor      = getRandInt(1,6);
        data_life.dying_time = 30;        
        
        vec3f d_angle;
        d_angle.z      = -getRandInt(10, 100)*0.01; 
        
	TextureOb* texOb = g_TEXTURE_MANAGER.GetRandomTextureOb(TEXTURE::MINERAL_ID); 
	
	Mineral* mineral = new Mineral(id);

	mineral->SetLifeData(data_life);
	mineral->SetTextureOb(texOb);
	mineral->SetDeltaAngle(d_angle);
		
	mineral->postCreateInit();
	
	return mineral;
}




