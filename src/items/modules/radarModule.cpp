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


RadarModule :: RadarModule(int radius_add)
{
     	this->radius_add = radius_add;
}

RadarModule :: ~RadarModule() /* virtual */
{}


int RadarModule :: getRadiusAdd() const { return radius_add; }


void RadarModule :: addUniqueInfo()
{
    	info.addTitleStr("radar module");
    	info.addNameStr("radius_add:");   info.addValueStr(int2str(radius_add));
}


RadarModule* getNewRadarModule()
{
    	TextureOb* texOb = g_UNIQUE_TEXTURE_COLLECTOR.texOb_module; 
    	int radius_add  = getRandInt(RADAR_MODULE_RADIUS_MIN, RADAR_MODULE_RADIUS_MAX);
    
        IdData data_id;
        data_id.type_id    = g_ID_GENERATOR.getNextId();
        data_id.type_id    = MODULE::MODULE;
        data_id.subtype_id = MODULE::RADAR; 
        
    	RadarModule* radar_module = new RadarModule(radius_add);    
        radar_module->setTextureOb(texOb);
        radar_module->setIdData(data_id);
                
    	return radar_module;
}














