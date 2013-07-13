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


#ifndef BASE_HPP
#define BASE_HPP

#include <boost/property_tree/ptree.hpp>
#include <struct/IdData.hpp>

class Base
{
	public:      
		Base();
		virtual ~Base();

		virtual void PutChildsToGarbage() const = 0;

		void SetSubTypeId(ENTITY::eTYPE subtype_id)       { data_id.subtype_id = subtype_id; }
		void SetSubSubTypeId(ENTITY::eTYPE subsubtype_id) { data_id.subsubtype_id = subsubtype_id; }
		
		unsigned long int GetId()        	const { return data_id.id; }   
		ENTITY::eTYPE GetTypeId()   	const { return data_id.type_id; }
		ENTITY::eTYPE GetSubTypeId() 	const { return data_id.subtype_id; }
		ENTITY::eTYPE GetSubSubTypeId() 	const { return data_id.subsubtype_id; }
					
        std::string GetDataTypeString() const;

		virtual void SaveData(boost::property_tree::ptree&) const = 0;
		virtual void LoadData(const boost::property_tree::ptree&) = 0;
		virtual void ResolveData() = 0;
		
	protected:
		IdData data_id;
		
		void SaveDataUniqueBase(boost::property_tree::ptree&, const std::string&) const;
		void LoadDataUniqueBase(const boost::property_tree::ptree&);
		void ResolveDataUniqueBase();
};

#endif 
