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


DriveModule :: DriveModule(int speed_add, 
                           int hyper_add)
{
     	this->speed_add = speed_add;
     	this->hyper_add = hyper_add;
}

DriveModule :: ~DriveModule() /* virtual */
{}

int DriveModule :: getSpeedAdd() const { return speed_add; }
int DriveModule :: getHyperAdd() const { return hyper_add; }
		
		
void DriveModule :: AddUniqueInfo()
{ 
    	info.addTitleStr("drive module"); 
    	if (speed_add != 0)
    	{ 
    		info.addNameStr("speed_add:");       info.addValueStr( int2str(speed_add) );
    	} 
    	
    	if (hyper_add != 0)
    	{ 
    		info.addNameStr("hyper_add:");       info.addValueStr( int2str(hyper_add) );
    	}
}


DriveModule* getNewDriveModule()
{
    	TextureOb* texOb = g_UNIQUE_TEXTURE_COLLECTOR.texOb_module; 
           	
    	int speed_add = getRandInt(MODULE::DRIVE::SPEED_MIN, MODULE::DRIVE::SPEED_MAX);
    	int hyper_add = getRandInt(MODULE::DRIVE::HYPER_MIN, MODULE::DRIVE::HYPER_MAX);

        IdData data_id;
        data_id.type_id    = g_ID_GENERATOR.getNextId();
        data_id.type_id    = MODULE::MODULE_ID;
        data_id.subtype_id = MODULE::DRIVE_ID;  
        
    	DriveModule* drive_module = new DriveModule(speed_add, hyper_add);
        drive_module->SetTextureOb(texOb);
        drive_module->SetIdData(data_id);
        
    	return drive_module;
}


