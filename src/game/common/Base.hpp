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

#include <common/NonCopyable.hpp>
#include <boost/property_tree/ptree.hpp>
#include <struct/IdData.hpp>


class Base : private NonCopyable
{
	public:      
		Base();
		virtual ~Base();

		virtual void PutChildsToGarbage() const = 0;
		void SetSubSubTypeId(TYPE::ENTITY subsubtype_id) { m_Data_id.subsubtype_id = subsubtype_id; }
		
		INTLONGEST GetId() const { return m_Data_id.id; }   
		TYPE::ENTITY GetTypeId()   	const { return m_Data_id.type_id; }
		TYPE::ENTITY GetSubTypeId() const { return m_Data_id.subtype_id; }
		TYPE::ENTITY GetSubSubTypeId() const { return m_Data_id.subsubtype_id; }
					
        std::string GetDataTypeString() const;

		virtual void SaveData(boost::property_tree::ptree&) const = 0;
		virtual void LoadData(const boost::property_tree::ptree&) = 0;
		virtual void ResolveData() = 0;
		
	protected:
        void SetId(INTLONGEST id)                  { m_Data_id.id = id; }
        void SetTypeId(TYPE::ENTITY type_id)       { m_Data_id.type_id = type_id; }
		void SetSubTypeId(TYPE::ENTITY subtype_id) { m_Data_id.subtype_id = subtype_id; }
        
		void SaveDataUniqueBase(boost::property_tree::ptree&, const std::string&) const;
		void LoadDataUniqueBase(const boost::property_tree::ptree&);
		void ResolveDataUniqueBase();

    private:
		IdData m_Data_id;    
};

#endif 
