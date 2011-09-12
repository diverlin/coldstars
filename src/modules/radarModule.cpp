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


#include "radarModule.hpp"

RadarModule :: RadarModule(TextureOb* _texOb, int _radius_add)
{
     	CommonForModules_init(RADAR_ID, _texOb);

     	radius_add = _radius_add;
}

RadarModule :: ~RadarModule()
{}


int RadarModule :: getRadiusAdd() const { return radius_add; }


void RadarModule :: addUniqueInfo()
{
    	info.addTitleStr("radar module");
    	info.addNameStr("radius_add:");   info.addValueStr(int2str(radius_add));
}


RadarModule* radarModuleGenerator()
{
    	TextureOb* texOb = g_TEXTURE_MANAGER.returnParticleTexObByColorId(RED_COLOR_ID); 
    	int radius_add  = randIntInRange(RADAR_MODULE_RADIUS_MIN, RADAR_MODULE_RADIUS_MAX);
    
    	RadarModule* radar_module = new RadarModule(texOb, radius_add);    	
    	return radar_module;
}














