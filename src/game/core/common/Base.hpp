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

#pragma once

#include <struct/IdData.hpp>

#include <ceti/NonCopyable.hpp>

#include <boost/property_tree/ptree.hpp>


class Base : private NonCopyable
{
    public:      
        Base();
        virtual ~Base();

        virtual void putChildrenToGarbage() const {}
        void setSubSubTypeId(type::ENTITY subsubtype_id) { m_data_id.subsubtype_id = subsubtype_id; }
        
        void setMeshId(int mesh_id) { m_mesh_id = mesh_id; }
        void setTextureId(int texture_id) { m_texture_id = texture_id; }

        id_type id() const { return m_data_id.id; }
        type::ENTITY typeId() const { return m_data_id.type_id; }
        type::ENTITY subTypeId() const { return m_data_id.subtype_id; }
        type::ENTITY subSubTypeId() const { return m_data_id.subsubtype_id; }
        int_type descriptorId() const { assert(m_descriptorId != -1); return m_descriptorId; }

        std::string dataTypeStr() const;

        virtual void Save(boost::property_tree::ptree&) const {}
        virtual void Load(const boost::property_tree::ptree&) {}
        virtual void Resolve() {}
        
    protected:
        void setId(id_type id)               { m_data_id.id = id; }
        void setTypeId(type::ENTITY type_id)       { m_data_id.type_id = type_id; }
        void setSubTypeId(type::ENTITY subtype_id) { m_data_id.subtype_id = subtype_id; }
        
        void SaveData(boost::property_tree::ptree&, const std::string&) const;
        void LoadData(const boost::property_tree::ptree&);
        void ResolveData();

    private:
        int_type m_descriptorId = -1;
        int m_mesh_id;
        int m_texture_id;

        IdData m_data_id;

        friend class EntityManager;
};
