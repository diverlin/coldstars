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

#include "GravityArtefact.hpp"
#include "../../common/constants.hpp"
#include "../../common/myStr.hpp"

GravityArtefact::GravityArtefact(int id)
{
	data_id.id = id;
        data_id.type_id = ENTITY::ARTEFACT_ID;
        data_id.subtype_id = ENTITY::GRAVITY_ARTEFACT_ID;
                        
        gravity = 0;
}

/* virtual */
GravityArtefact::~GravityArtefact ()
{}

/* virtual */
void GravityArtefact::AddUniqueInfo()
{
    	info.addTitleStr("gravity artefact");
    	info.addNameStr("gravity:");      info.addValueStr( int2str(gravity) );
}

/* virtual */
void GravityArtefact::AddCommonInfo()
{
    	info.addNameStr("mass:");      info.addValueStr( int2str(data_item.mass) );
}

/* virtual */
void GravityArtefact::SaveData(boost::property_tree::ptree& save_ptree) const
{
	std::string root = "gravity_artefact." + int2str(GetId()) + ".";
	SaveDataUniqueBase(save_ptree, root);
        SaveDataUniqueBaseItem(save_ptree, root);
	SaveDataUniqueGravityArtefact(save_ptree, root);
}

/* virtual */
void GravityArtefact::LoadData(const boost::property_tree::ptree& load_ptree)
{
	LoadDataUniqueBase(load_ptree);
        LoadDataUniqueBaseItem(load_ptree);
	LoadDataUniqueGravityArtefact(load_ptree);
}

/* virtual */
void GravityArtefact::ResolveData()
{
	ResolveDataUniqueBase();
        ResolveDataUniqueBaseItem();
	ResolveDataUniqueGravityArtefact();
}		
		
void GravityArtefact::SaveDataUniqueGravityArtefact(boost::property_tree::ptree& save_ptree, const std::string& root) const
{
        save_ptree.put(root+"gravity", gravity); 
}

void GravityArtefact::LoadDataUniqueGravityArtefact(const boost::property_tree::ptree& load_ptree)
{
	gravity = load_ptree.get<int>("gravity");
}

void GravityArtefact::ResolveDataUniqueGravityArtefact()
{}
