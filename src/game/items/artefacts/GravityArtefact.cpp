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
#include "../../common/Logger.hpp"

GravityArtefact::GravityArtefact(int id)
:
gravity(0)
{
	SetId(id);
    SetTypeId(TYPE::ENTITY::ARTEFACT_ID);
    SetSubTypeId(TYPE::ENTITY::GRAVITY_ARTEFACT_ID);
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
	#if SAVELOAD_LOG_ENABLED == 1
	Logger::Instance().Log(" SaveDataUniqueGravityArtefact()  id=" + int2str(GetId()) + " START", SAVELOAD_LOG_DIP);
	#endif
	
        save_ptree.put(root+"gravity", gravity); 
}

void GravityArtefact::LoadDataUniqueGravityArtefact(const boost::property_tree::ptree& load_ptree)
{
	#if SAVELOAD_LOG_ENABLED == 1
	Logger::Instance().Log(" LoadDataUniqueGravityArtefact()  id=" + int2str(GetId()) + " START", SAVELOAD_LOG_DIP);
	#endif
	
	gravity = load_ptree.get<int>("gravity");
}

void GravityArtefact::ResolveDataUniqueGravityArtefact()
{
	#if SAVELOAD_LOG_ENABLED == 1
	Logger::Instance().Log(" ResolveDataUniqueGravityArtefact()  id=" + int2str(GetId()) + " START", SAVELOAD_LOG_DIP);
	#endif
}
