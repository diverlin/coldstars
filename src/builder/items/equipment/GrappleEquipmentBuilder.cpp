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


GrappleEquipmentBuilder& GrappleEquipmentBuilder::Instance()
{
	static GrappleEquipmentBuilder instance;
	return instance;
}

GrappleEquipmentBuilder::~GrappleEquipmentBuilder()
{}

void GrappleEquipmentBuilder::CreateNewGrappleEquipment(int id)
{
	if (id == NONE_ID)
	{
		id = g_ID_GENERATOR.getNextId();
	}
        grapple_equipment = new GrappleEquipment(id);
        EntityManager::Instance().RegisterEntity(grapple_equipment);
} 
        	
void GrappleEquipmentBuilder::CreateNewInternals(int race_id, int revision_id)
{     
    	if (race_id == -1)
       		race_id = RACE::R0_ID; //RACES_GOOD_LIST[randint(0, len(RACES_GOOD_LIST) - 1)]

    	if (revision_id == -1)
       		revision_id = TECHLEVEL::L0_ID; 

    	int tech_rate = 1; //int tech_rate = returnRaceTechRate(race_id);  

    	TextureOb* texOb_item = g_TEXTURE_MANAGER.GetRandomTextureOb(TEXTURE::GRAPPLE_EQUIPMENT_ID);   
    	//item_texOb = TEXTURE_MANAGER.returnItemTexOb(TEXTURE::GRAPPLE_EQUIPMENT_ID, revision_id) 

    	int strength_orig   = getRandInt(EQUIPMENT::GRAPPLE::STRENGTH_MIN,   EQUIPMENT::GRAPPLE::STRENGTH_MAX);
    	int radius_orig     = getRandInt(EQUIPMENT::GRAPPLE::RADIUS_MIN,     EQUIPMENT::GRAPPLE::RADIUS_MAX);
    	int speed_orig      = getRandInt(EQUIPMENT::GRAPPLE::SPEED_MIN,      EQUIPMENT::GRAPPLE::SPEED_MAX);
    	int maxNumItem_orig = getRandInt(EQUIPMENT::GRAPPLE::MAXNUMITEM_MIN, EQUIPMENT::GRAPPLE::MAXNUMITEM_MAX);
    	
    	ItemCommonData common_data;
    	common_data.modules_num_max = getRandInt(EQUIPMENT::GRAPPLE::MODULES_NUM_MIN, EQUIPMENT::GRAPPLE::MODULES_NUM_MAX);
    	common_data.mass            = getRandInt(EQUIPMENT::GRAPPLE::MASS_MIN,        EQUIPMENT::GRAPPLE::MASS_MAX);
    	common_data.condition_max   = getRandInt(EQUIPMENT::GRAPPLE::CONDITION_MIN,   EQUIPMENT::GRAPPLE::CONDITION_MAX) * tech_rate;
    	common_data.deterioration_rate = 1;
                                                                 
        grapple_equipment->SetStrengthOrig(strength_orig);
        grapple_equipment->SetRadiusOrig(radius_orig);
        grapple_equipment->SetSpeedOrig(speed_orig);
        grapple_equipment->SetMaxNumItemOrig(maxNumItem_orig);

        grapple_equipment->SetTextureOb(texOb_item);    
        grapple_equipment->SetFunctionalSlotSubTypeId(SLOT::GRAPPLE_ID);
        grapple_equipment->SetItemCommonData(common_data);        

    	grapple_equipment->UpdatePropetries();
    	grapple_equipment->CountPrice();
}


