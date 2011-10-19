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


#include "freezerModule.hpp"

FreezerModule :: FreezerModule(TextureOb* _texOb, int _freeze_add)
{
     	CommonForModules_init(FREEZER_ID, _texOb);

     	freeze_add = _freeze_add;
}


int FreezerModule :: getFreezeAdd() const { return freeze_add; }
		
		
void FreezerModule :: addUniqueInfo()
{
    	info.addTitleStr("freezer module");
    	info.addNameStr("freeze_add:");     info.addValueStr( int2str(freeze_add) );
}


FreezerModule* freezerModuleGenerator()
{
    TextureOb* texOb = g_TEXTURE_MANAGER.returnParticleTexObByColorId(RED_COLOR_ID); 
    int freeze_add = getRandInt(FREEZER_MODULE_FREEZE_MIN, FREEZER_MODULE_FREEZE_MAX);

    FreezerModule* freezer_module = new FreezerModule(texOb, freeze_add);
    return freezer_module;
}
