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


#include "scanerModule.hpp"


ScanerModule :: ScanerModule(TextureOb* _texOb, int _scan_add)
{
    	CommonForModules_init(SCANER_MODULE_ID, _texOb);

    	scan_add = _scan_add;
}


ScanerModule :: ~ScanerModule ()
{}


int ScanerModule :: getScanAdd() const { return scan_add; }
		
		
void ScanerModule :: addUniqueInfo()
{
    	info.addTitleStr("scaner module");
    	info.addNameStr("scan_add:");      info.addValueStr( int2str(scan_add) );
}


ScanerModule* scanerModuleGenerator()
{
    	TextureOb* texOb = g_TEXTURE_MANAGER.returnParticleTexObByColorId(RED_COLOR_ID); 
    	int scan_add = getRandInt(SCANER_MODULE_SCAN_MIN, SCANER_MODULE_SCAN_MAX);

    	ScanerModule* scaner_module = new ScanerModule(texOb, scan_add);    	
    	return scaner_module;
}
