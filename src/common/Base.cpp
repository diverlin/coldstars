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

#include "Base.hpp"

Base::Base()
{}

/*virtual*/
Base::~Base()
{}

void Base::SaveDataUniqueBase(boost::property_tree::ptree& save_ptree, const std::string& root) const
{
	save_ptree.put(root+"data_id.id",            data_id.id);
	save_ptree.put(root+"data_id.type_id",       data_id.type_id);
	save_ptree.put(root+"data_id.subtype_id",    data_id.subtype_id);
	save_ptree.put(root+"data_id.subsubtype_id", data_id.subsubtype_id);
}

void Base::LoadDataUniqueBase(const boost::property_tree::ptree& load_ptree)
{
	data_id.id              = load_ptree.get<int>("data_id.id");
	data_id.type_id         = load_ptree.get<int>("data_id.type_id");
	data_id.subtype_id      = load_ptree.get<int>("data_id.subtype_id");
	data_id.subsubtype_id   = load_ptree.get<int>("data_id.subsubtype_id");
}

void Base::ResolveDataUniqueBase()
{}
