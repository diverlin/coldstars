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

#include <core/struct/IdData.hpp>

//#include <ceti/NonCopyable.hpp>
#include <ceti/Base.hpp>
//#include <ceti/IdGenerator.hpp>
#include <ceti/descriptor/BaseView.hpp>

#include <boost/property_tree/ptree.hpp>

#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>

class EntityManager;

//namespace descriptor {

//class Base
//{
//public:
//    Base(int_t type = -1, int_t id = -1);
//    ~Base();

////    std::string data() const;

//    int_t id() const { return m_id; }
//    int_t type() const { return m_type; }

//    //std::string info() const = 0;

//private:
//    friend class boost::serialization::access;
//    template<class Archive>
//    void serialize(Archive & ar, const unsigned int version) {
//        ar & m_id;
//        ar & m_type;
//    }

//    int_t m_id = -1;
//    int_t m_type = -1;
//    static IdGenerator m_idGenerator;
//};

//} // namespace descriptor


namespace descriptor {

class Base : public ceti::descriptor::BaseView
{
public:
    Base() = default;
    ~Base() = default;

    void setType(const type::entity& major)   { m_identity.type = major; }
    void setSubType(const type::entity& minor) { m_identity.subtype = minor; }
    void setSubSubType(const type::entity& patch) { m_identity.subsubtype = patch; }

    const core::Id& identity() const { return m_identity; }
    const type::entity& type() const { return m_identity.type; }
    const type::entity& subtype() const { return m_identity.subtype; }
    const type::entity& subsubtype() const { return m_identity.subsubtype; }

    std::string info() const {
        std::string result = "fill me";
        return result;
    }

private:
    core::Id m_identity;

private:
    friend class boost::serialization::access;
    template<class Archive>
    void serialize(Archive & ar, const unsigned int version) {
        ar & boost::serialization::base_object<ceti::descriptor::BaseView>(*this);
        ar & m_identity;
    }
};

}


namespace model {

class Base : public ceti::model::BaseView
{
public:
    Base() = default;
    ~Base() = default;
    Base(const std::string& data);
    std::string data() const;

    void setId(int_t id) { m_id = id; }
    void setType(const type::entity& major)   { m_identity.type = major; }
    void setSubType(const type::entity& minor) { m_identity.subtype = minor; }
    void setSubSubType(const type::entity& patch) { m_identity.subsubtype = patch; }

    void setDescriptor(int_t descriptor) { m_descriptor = descriptor; }

    const core::Id& identity() const { return m_identity; }
    int_t id() const { return m_id; }
    const type::entity& type() const { return m_identity.type; }
    const type::entity& subtype() const { return m_identity.subtype; }
    const type::entity& subsubtype() const { return m_identity.subsubtype; }
    int_t descriptor() const { assert(m_descriptor != -1); return m_descriptor; }

    std::string typeInfo() const;

private:
    core::Id m_identity;
    int_t m_descriptor = NONE;
    int_t m_id = NONE;

private:
    friend class boost::serialization::access;
    template<class Archive>
    void serialize(Archive & ar, const unsigned int version) {
        ar & boost::serialization::base_object<ceti::model::BaseView>(*this);
        ar & m_identity;
        ar & m_descriptor;
        ar & m_id;
    }
};

} // namespace model

namespace control {

class Base : private NonCopyable
{
public:
    [[depreacted("temprorary code refactor workaround")]]
    Base() = default;
    Base(model::Base*);
    virtual ~Base();

    virtual void putChildrenToGarbage() const {}

private:
    model::Base* m_model_base = nullptr;
    //model::Base* model() const { return m_model_base; }
};

} // namespace control



//namespace core {

//class Base : private NonCopyable
//{
//public:
//    Base();
//    virtual ~Base();

//    virtual void putChildrenToGarbage() const {}
//    void setSubSubTypeId(type::entity patch) { m_type.subsubtype = patch; }

//    void setMeshId(int mesh_id) { m_mesh_id = mesh_id; }
//    void setTextureId(int texture_id) { m_texture_id = texture_id; }

//    const core::Id& ident() const { return m_type; }
//    int_t id() const { return m_id; }
//    const type::entity& type() const { return m_type.type; }
//    const type::entity& subtype() const { return m_type.subtype; }
//    const type::entity& subsubtype() const { return m_type.subsubtype; }
//    int_t descriptorId() const { assert(m_descriptorId != -1); return m_descriptorId; }

//    std::string dataTypeStr() const;

//    virtual void Save(boost::property_tree::ptree&) const {}
//    virtual void Load(const boost::property_tree::ptree&) {}
//    virtual void Resolve() {}

//    void setId(int_t id) { m_id = id; /*assert(id != 0);*/ } // MAKE PROTECTED

//protected:
//    void setTypeId(const type::entity& major)   { m_type.type = major; }
//    void setSubTypeId(const type::entity& minor) { m_type.subtype = minor; }

//    void SaveData(boost::property_tree::ptree&, const std::string&) const;
//    void LoadData(const boost::property_tree::ptree&);
//    void ResolveData();

//private:
//    core::Id m_type;

//    int_t m_descriptorId = -1;
//    int_t m_id = -1;

//    int m_mesh_id = -1;
//    int m_texture_id = -1;

//    friend class EntityManager;
//};

//} // namespace core


