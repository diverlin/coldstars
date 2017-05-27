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
#include <core/type/DescriptorType.hpp>

#include <ceti/NonCopyable.hpp>
#include <ceti/Base.hpp>

//#include <boost/property_tree/ptree.hpp> // remove this

#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>

namespace descriptor {
class Base;
} // namespace descriptor

class EntityManager;

namespace model {

class Base : public NonCopyable
{
public:
    Base() = default;
    virtual ~Base() = default; // virtual method is needed for proper model base deletion
//    Base(const std::string& data);
//    std::string data() const;

    void setAlive(bool alive) { m_isAlive = alive; }
    void setId(int_t id) { m_id = id; }
    void setDescriptor(int_t descriptor) { m_descriptor = descriptor; }

    bool isAlive() const { return m_isAlive; }
    int_t id() const { return m_id; }
    int_t descriptor() const { return m_descriptor; }

    void setWritable(bool writable) { m_writable = writable; }

protected:
    bool _isWritable() const { return m_writable; }

private:
    bool m_writable = true;
    bool m_isAlive = true;
    int_t m_id = NONE;
    int_t m_descriptor = NONE;

private:
    friend class boost::serialization::access;
    template<class Archive>
    void serialize(Archive & ar, const unsigned int version) {
        ar & m_isAlive;
        ar & m_id;
        ar & m_descriptor;
    }
};

} // namespace model

namespace control {

class Base : private NonCopyable
{
public:
    Base(descriptor::Base*, model::Base*);
    virtual ~Base() = default;

    void setId(int_t id);

    int_t id();
    entity::Type type() const;
    entity::Type subType() const;

    bool isAlive() const;
    void die();

    descriptor::Base* descriptor() const { return m_descriptor_base; }
    model::Base* model() const { return m_model_base; }

private:
    descriptor::Base* m_descriptor_base = nullptr;
    model::Base* m_model_base = nullptr;

    virtual void __putChildrenToGarbage() const {}
};

} // namespace control


class Base : private NonCopyable
{
public:
    Base() = default;
    virtual ~Base() = default;

    void setId(int_t id) { m_id = id; }

    int_t id() { return m_id; }

private:
    int_t m_id = NONE;
};

//namespace core {

//class Base : private NonCopyable
//{
//public:
//    Base();
//    virtual ~Base();

//    virtual void putChildrenToGarbage() const {}
//    void setSubSubTypeId(entity::Type patch) { m_type.subsubtype = patch; }

//    void setMeshId(int mesh_id) { m_mesh_id = mesh_id; }
//    void setTextureId(int texture_id) { m_texture_id = texture_id; }

//    const core::Id& ident() const { return m_type; }
//    int_t id() const { return m_id; }
//    const entity::Type& type() const { return m_type.type; }
//    const entity::Type& subtype() const { return m_type.subtype; }
//    const entity::Type& subsubtype() const { return m_type.subsubtype; }
//    int_t descriptorId() const { assert(m_descriptorId != -1); return m_descriptorId; }

//    std::string dataTypeStr() const;

//    virtual void Save(boost::property_tree::ptree&) const {}
//    virtual void Load(const boost::property_tree::ptree&) {}
//    virtual void Resolve() {}

//    void setId(int_t id) { m_id = id; /*assert(id != 0);*/ } // MAKE PROTECTED

//protected:
//    void setTypeId(const entity::Type& major)   { m_type.type = major; }
//    void setSubTypeId(const entity::Type& minor) { m_type.subtype = minor; }

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


