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


#include "droidModule.h"

DroidModule :: DroidModule(TextureOb* _pTo_texOb, int _repair_add)
{
     	CommonForModules_init(DROID_ID, _pTo_texOb);

     	repair_add = _repair_add;
}

DroidModule :: ~DroidModule()
{}

int DroidModule :: getRepairAdd() const { return repair_add; }
		
void DroidModule :: updateInfo()
{
	info.clear();

    	info.addTitleStr("droid module");
    	info.addNameStr("repair_add:");   info.addValueStr( int2str(repair_add) );
    	info.addNameStr("mass:");         info.addValueStr( int2str(mass) );
}

DroidModule* droidModuleGenerator()
{
    	TextureOb* pTo_texOb = g_TEXTURE_MANAGER.returnParticleTexObByColorId(RED_COLOR_ID); 
    	int _repair_add = randIntInRange(DROID_MODULE_REPAIR_MIN, DROID_MODULE_REPAIR_MAX);

    	DroidModule* pTo_droid_module = new DroidModule(pTo_texOb, _repair_add);

    	return pTo_droid_module;
}
