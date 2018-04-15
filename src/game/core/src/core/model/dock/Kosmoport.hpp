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

#include "Land.hpp"

#include <core/type/RaceType.hpp>

namespace model {

class KosmoportModel : public LandModel
{
public:
    KosmoportModel(int_t);
    ~KosmoportModel() = default;
    KosmoportModel(const std::string& data);
    std::string data() const;

    int_t angar() const { return m_angar; }
    int_t store() const { return m_store; }
    int_t shop() const { return m_shop; }
    int_t goverment() const { return m_goverment; }

    void setAngar(int_t angar) { m_angar = angar; }
    void setStore(int_t store) { m_store = store; }
    void setShop(int_t shop) { m_shop = shop; }
    void setGoverment(int_t goverment) { m_goverment = goverment; }

private:
    friend class boost::serialization::access;
    template<class Archive>
    void serialize(Archive & ar, const unsigned int version) {
        ar & boost::serialization::base_object<LandModel>(*this);
        ar & m_angar;
        ar & m_store;
        ar & m_shop;
        ar & m_goverment;
    }

private:
    int_t m_angar = NONE;
    int_t m_store = NONE;
    int_t m_shop = NONE;
    int_t m_goverment = NONE;
};

} // namespace model

