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


DroidModule :: DroidModule(int repair_add)
{
     	this->repair_add = repair_add;
}

DroidModule :: ~DroidModule() /* virtual */
{}

int DroidModule :: getRepairAdd() const { return repair_add; }
		
		
void DroidModule :: AddUniqueInfo()
{
    	info.addTitleStr("droid module");
    	info.addNameStr("repair_add:");   info.addValueStr( int2str(repair_add) );
}

DroidModule* getNewDroidModule()
{
    	TextureOb* texOb = g_UNIQUE_TEXTURE_COLLECTOR.texOb_module; 
         
    	int repair_add = getRandInt(MODULE::DROID::REPAIR_MIN, MODULE::DROID::REPAIR_MAX);

        IdData data_id;
        data_id.type_id    = g_ID_GENERATOR.getNextId();
        data_id.type_id    = MODULE::MODULE_ID;
        data_id.subtype_id = MODULE::DROID_ID; 
        
    	DroidModule* droid_module = new DroidModule(repair_add);
        droid_module->SetTextureOb(texOb);
        droid_module->SetIdData(data_id);
        
    	return droid_module;
}
