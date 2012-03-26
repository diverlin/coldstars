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


FreezerModule :: FreezerModule(int freeze_add)
{
     	this->freeze_add = freeze_add;
}

FreezerModule :: ~FreezerModule() /* virtual */
{}

int FreezerModule :: getFreezeAdd() const { return freeze_add; }


void FreezerModule :: addUniqueInfo()
{
    	info.addTitleStr("freezer module");
    	info.addNameStr("freeze_add:");     info.addValueStr( int2str(freeze_add) );
}


FreezerModule* getNewFreezerModule()
{
    	TextureOb* texOb = g_UNIQUE_TEXTURE_COLLECTOR.texOb_module; 
        int freeze_add = getRandInt(FREEZER_MODULE_FREEZE_MIN, FREEZER_MODULE_FREEZE_MAX);

        IdData data_id;
        data_id.type_id    = g_ID_GENERATOR.getNextId();
        data_id.type_id    = MODULE::MODULE;
        data_id.subtype_id = MODULE::FREEZER; 
        
        FreezerModule* freezer_module = new FreezerModule(freeze_add);
        freezer_module->setTextureOb(texOb);
        freezer_module->setIdData(data_id);
        
        return freezer_module;
}
