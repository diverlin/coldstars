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


RadarModuleBuilder& RadarModuleBuilder::Instance()
{
	static RadarModuleBuilder instance;
	return instance;
}

RadarModuleBuilder::~RadarModuleBuilder()
{}

void RadarModuleBuilder::CreateNewRadarModule(int id)
{
	if (id == NONE_ID)
	{
		id = g_ID_GENERATOR.getNextId();
	}
        radar_module = new RadarModule(id);
        EntityManager::Instance().RegisterEntity(radar_module);
} 
        	
void RadarModuleBuilder::CreateNewInternals()
{     
    	TextureOb* texOb = g_TEXTURE_MANAGER.GetRandomTextureOb(TEXTURE::MODULE_ID);   
    	int radius_add  = getRandInt(MODULE::RADAR::RADIUS_MIN, MODULE::RADAR::RADIUS_MAX);
    
        radar_module->SetTextureOb(texOb);
        radar_module->SetRadiusAdd(radius_add);
}


