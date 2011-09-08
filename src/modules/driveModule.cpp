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


#include "driveModule.h"

DriveModule :: DriveModule(TextureOb* _texOb, int _speed_add, int _hyper_add)
{
     	CommonForModules_init(DRIVE_ID, _texOb);

     	speed_add = _speed_add;
     	hyper_add = _hyper_add;
}

DriveModule :: ~DriveModule()
{}

int DriveModule :: getSpeedAdd() const { return speed_add; }
int DriveModule :: getHyperAdd() const { return hyper_add; }
		
		
void DriveModule :: addUniqueInfo()
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


DriveModule* driveModuleGenerator()
{
    	TextureOb* texOb = g_TEXTURE_MANAGER.returnParticleTexObByColorId(RED_COLOR_ID);     	
    	int speed_add = randIntInRange(DRIVE_MODULE_SPEED_MIN, DRIVE_MODULE_SPEED_MAX);
    	int hyper_add = randIntInRange(DRIVE_MODULE_HYPER_MIN, DRIVE_MODULE_HYPER_MAX);

    	DriveModule* drive_module = new DriveModule(texOb, speed_add, hyper_add);
    	return drive_module;
}


