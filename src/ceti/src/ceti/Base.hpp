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

#include <ceti/type/IdType.hpp>
#include <ceti/NonCopyable.hpp>
#include <ceti/IdGenerator.hpp>

#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>

namespace ceti {

//namespace descriptor {

//class BaseView : private NonCopyable
//{
//public:
//    BaseView() = default;
//    ~BaseView() = default;

//    void setMesh(int mesh) { m_mesh = mesh; }
//    void setMaterial(int material) { m_material = material; }

//    int_t mesh() const { return m_mesh; }
//    int_t material() const { return m_material; }

//    std::string info() const {
//        std::string result = "fill me";
//        return result;
//    }

//private:
//    int_t m_mesh = NONE;
//    int_t m_material = NONE;

//private:
//    friend class boost::serialization::access;
//    template<class Archive>
//    void serialize(Archive & ar, const unsigned int version) {
//        ar & m_mesh;
//        ar & m_material;
//    }
//};

//} // namespace descriptor

//namespace model {

//class BaseView : private NonCopyable
//{
//public:
//    BaseView() = default;
//    ~BaseView() = default;
//    BaseView(const std::string& data);
//    std::string data() const;

//    void setMesh(int mesh) { m_mesh = mesh; }
//    void setMaterial(int material) { m_material = material; }

//    int_t mesh() const { return m_mesh; }
//    int_t material() const { return m_material; }

//private:
//    int_t m_mesh = NONE;
//    int_t m_material = NONE;

//private:
//    friend class boost::serialization::access;
//    template<class Archive>
//    void serialize(Archive & ar, const unsigned int version) {
//        ar & m_mesh;
//        ar & m_material;
//    }
//};

//} // namespace model

} // namespace ceti
