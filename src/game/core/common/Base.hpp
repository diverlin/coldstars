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

#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>

class EntityManager;


namespace core {

class Base : private NonCopyable
{
public:
    Base();
    virtual ~Base();

    virtual void putChildrenToGarbage() const {}
    void setSubSubTypeId(type::entity patch) { m_type.subsubtype = patch; }

    void setMeshId(int mesh_id) { m_mesh_id = mesh_id; }
    void setTextureId(int texture_id) { m_texture_id = texture_id; }

    const core::Id& ident() const { return m_type; }
    const int_t& id() const { return m_id; }
    const type::entity& type() const { return m_type.type; }
    const type::entity& subtype() const { return m_type.subtype; }
    const type::entity& subsubtype() const { return m_type.subsubtype; }
    const int_t& descriptorId() const { assert(m_descriptorId != -1); return m_descriptorId; }

    std::string dataTypeStr() const;

    virtual void Save(boost::property_tree::ptree&) const {}
    virtual void Load(const boost::property_tree::ptree&) {}
    virtual void Resolve() {}

    void setId(const int_t& id) { m_id = id; /*assert(id != 0);*/ } // MAKE PROTECTED

protected:
    void setTypeId(const type::entity& major)   { m_type.type = major; }
    void setSubTypeId(const type::entity& minor) { m_type.subtype = minor; }

    void SaveData(boost::property_tree::ptree&, const std::string&) const;
    void LoadData(const boost::property_tree::ptree&);
    void ResolveData();

private:
    core::Id m_type;

    int_t m_descriptorId = -1;
    int_t m_id = -1;

    int m_mesh_id = -1;
    int m_texture_id = -1;

    friend class EntityManager;
};


namespace model {

class Base : private NonCopyable
{
public:
    Base() = default;
    ~Base() = default;
    Base(const std::string& data);
    std::string data() const;

    core::Id type;

    int_t descriptor = NONE;
    int_t id = NONE;

    int_t mesh = NONE;
    int_t material = NONE;

private:
    friend class boost::serialization::access;
    template<class Archive>
    void serialize(Archive & ar, const unsigned int version)
    {
        ar & type;
        ar & descriptor;
        ar & id;
        ar & mesh;
        ar & material;
    }
};

} // namespace model

namespace control {

class Base : private NonCopyable
{
public:
    Base(model::Base*);
    virtual ~Base();

    virtual void putChildrenToGarbage() const {}
    void setSubSubTypeId(type::entity patch) { model()->type.subsubtype = patch; }

    void setMeshId(int mesh_id) { model()->mesh = mesh_id; }
    void setTextureId(int texture_id) { model()->material = texture_id; }

    const core::Id& ident() const { return model()->type; }
    const int_t& id() const { return model()->id; }
    const type::entity& type() const { return model()->type.type; }
    const type::entity& subtype() const { return model()->type.subtype; }
    const type::entity& subsubtype() const { return model()->type.subsubtype; }
    const int_t& descriptorId() const { assert(model()->descriptor != -1); return model()->descriptor; }

    std::string dataTypeStr() const;

    virtual void Save(boost::property_tree::ptree&) const {}
    virtual void Load(const boost::property_tree::ptree&) {}
    virtual void Resolve() {}

    void setId(const int_t& id) { model()->id = id; /*assert(id != 0);*/ } // MAKE PROTECTED

protected:
    void setTypeId(const type::entity& major)   { model()->type.type = major; }
    void setSubTypeId(const type::entity& minor) { model()->type.subtype = minor; }

//    void SaveData(boost::property_tree::ptree&, const std::string&) const;
//    void LoadData(const boost::property_tree::ptree&);
//    void ResolveData();

private:
    model::Base* m_model_base = nullptr;
    model::Base* model() const { return m_model_base; }
    friend class EntityManager;
};

} // namespace control

} // namespace core
