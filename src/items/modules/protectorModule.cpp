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


ProtectorModule :: ProtectorModule(int protection_add)
{
     	this->protection_add = protection_add;
}

ProtectorModule :: ~ProtectorModule () /* virtual */
{}


int ProtectorModule :: getProtectionAdd() const { return protection_add; }
		
		
void ProtectorModule :: AddUniqueInfo()
{
    	info.addTitleStr("protector module");
    	info.addNameStr("protection_add:");  info.addValueStr( int2str(protection_add) );
}


ProtectorModule* getNewProtectorModule()
{
    	TextureOb* texOb = g_UNIQUE_TEXTURE_COLLECTOR.texOb_module; 
        
    	int protection_add = getRandInt(MODULE::PROTECTOR::PROTECTION_MIN, MODULE::PROTECTOR::PROTECTION_MAX);

        IdData data_id;
        data_id.type_id    = g_ID_GENERATOR.getNextId();
        data_id.type_id    = MODULE::MODULE_ID;
        data_id.subtype_id = MODULE::PROTECTOR_ID;  
        
    	ProtectorModule* protector_module = new ProtectorModule(protection_add);
        protector_module->SetTextureOb(texOb);
        protector_module->SetIdData(data_id);
        
    	return protector_module;
}
