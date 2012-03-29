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


BakModule :: BakModule(int fuel_max_add)
{
    	this->fuel_max_add = fuel_max_add;
}

BakModule :: ~BakModule() /* virtual */
{}

int BakModule :: getFuelMaxAdd() const { return fuel_max_add; }
 	

void BakModule :: AddUniqueInfo()
{
    	info.addTitleStr("bak module");
    	info.addNameStr("fuel_max_add:"); info.addValueStr( int2str(fuel_max_add) );
}



BakModule* getNewBakModule()
{
    	TextureOb* texOb = g_UNIQUE_TEXTURE_COLLECTOR.texOb_module; 
          	
    	int fuel_max_add = getRandInt(MODULE::BAK::FUEL_MIN, MODULE::BAK::FUEL_MAX);

        IdData data_id;
        data_id.type_id    = g_ID_GENERATOR.getNextId();
        data_id.type_id    = MODULE::MODULE_ID;
        data_id.subtype_id = MODULE::BAK_ID;  
        
    	BakModule* bak_module = new BakModule(fuel_max_add);
        bak_module->SetTextureOb(texOb);
        bak_module->SetIdData(data_id);
        
    	return bak_module;
}
