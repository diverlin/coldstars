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



Asteroid::Asteroid(int id)
{   
	data_id.id = id;
	data_id.type_id = ENTITY::ASTEROID_ID;
	
      	mass  = getRandInt(10, 30);
}
    
 
Asteroid::~Asteroid()
{}

void Asteroid::UpdateInSpace(int time, bool show_effect)
{    
	CheckDeath(show_effect);
	UpdateRotation();
	if (time > 0)
	{	
     		UpdatePosition();
     	}     	
}

void Asteroid::CollisionEvent(bool show_effect)
{
	data_life.is_alive = false;
	data_life.dying_time = -1;
}
    
void Asteroid::PostDeathUniqueEvent(bool show_effect)
{
       	for (int i = 0; i<3; i++)
	{      
                TextureOb* textureOb = g_TEXTURE_MANAGER.GetRandomTextureOb(TEXTURE::MINERAL_ID);   
                GoodsPack* goods_pack = GetNewGoodsPack(ENTITY::MINERAL_ID);
                goods_pack->Increase(4);
		Container* container = GetNewContainer(textureOb, goods_pack);
		starsystem->Add(container, points.GetCenter());
   	}
   	
   	if (show_effect == true)
     	{
        	createExplosion(starsystem, points.GetCenter(), data_planet.scale/2);        		
        }
        			
}    


void Asteroid::UpdateInfo()
{   
	info.clear();

    	info.addTitleStr("ASTEROID");
    	info.addNameStr("id/ss_id:");    info.addValueStr(int2str(data_id.id) + " / " + int2str(starsystem->GetId()));
    	info.addNameStr("armor:");       info.addValueStr(int2str(data_life.armor));
    	info.addNameStr("mass:");        info.addValueStr(int2str(mass));
	info.addNameStr("speed x 100:"); info.addValueStr(int2str(int(data_planet.speed*100)));
}     

void Asteroid::RenderInfoInSpace(vec2f scroll_coords) 
{  
	UpdateInfo();
     	drawInfoIn2Column(&info.title_list, &info.value_list, points.GetCenter().x, points.GetCenter().y, scroll_coords.x, scroll_coords.y);
}

void Asteroid::SaveDataUniqueAsteroid(boost::property_tree::ptree& save_ptree, const std::string& root) const
{}

void Asteroid::LoadDataUniqueAsteroid(const boost::property_tree::ptree& ptree)
{}

void Asteroid::ResolveDataUniqueAsteroid()
{
	((StarSystem*)EntityManager::Instance().GetEntityById(data_unresolved_BaseGameEntity.starsystem_id))->Add(this, parent, data_unresolved_BasePlanet.orbit_it); 
}
	
void Asteroid::SaveData(boost::property_tree::ptree& save_ptree) const		
{
	std::string root = "asteroid." + int2str(GetId())+".";
	SaveDataUniqueBase(save_ptree, root);
	SaveDataUniqueBaseGameEntity(save_ptree, root);
	SaveDataUniqueBasePlanet(save_ptree, root);
	SaveDataUniqueAsteroid(save_ptree, root);
}

void Asteroid::LoadData(const boost::property_tree::ptree& load_ptree)
{
	LoadDataUniqueBase(load_ptree);
	LoadDataUniqueBaseGameEntity(load_ptree);
	LoadDataUniqueBasePlanet(load_ptree);
	LoadDataUniqueAsteroid(load_ptree);
}

void Asteroid::ResolveData()
{
	ResolveDataUniqueBase();
	ResolveDataUniqueBaseGameEntity();
	ResolveDataUniqueBasePlanet();
	ResolveDataUniqueAsteroid();
}	
        




