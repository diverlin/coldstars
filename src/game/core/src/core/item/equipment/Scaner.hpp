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

#include "Base.hpp"


namespace descriptor {
namespace item {

class Scaner : public BaseEquipment
{
public:

    static const int SCAN_MIN;
    static const int SCAN_MAX;
    static const float SCAN_TECH_RATE;

    static const int MODULES_NUM_MIN;
    static const int MODULES_NUM_MAX;

    static const int MASS_MIN;
    static const int MASS_MAX;
    static const int CONDITION_MIN;
    static const int CONDITION_MAX;

    static const float SCAN_WEIGHT;
    static const float MODULES_NUM_WEIGHT;


    Scaner();
    ~Scaner() = default;
    Scaner(const std::string& data);
    std::string data() const;

    void setScan(int scan) { m_scan = scan; }

    int scan() const { return m_scan; }

    std::string info() const {
        std::string result = "descriptor::item::Scaner:\n";
        result += std::string(" scan = ") + std::to_string(m_scan) + "\n";
        result += descriptor::item::BaseEquipment::info();
        return result;
    }

private:
    int m_scan = 0;

private:
    friend class boost::serialization::access;
    template<class Archive>
    void serialize(Archive & ar, const unsigned int version) {
        ar & boost::serialization::base_object<BaseEquipment>(*this);
        ar & m_scan;
    }
};

} // namespace item
} // namespace descriptor


namespace model {
namespace item {

class Scaner : public BaseEquipment
{
public:
    Scaner();
    ~Scaner() = default;
    Scaner(const std::string& data);
    std::string data() const;

    void setScan(int scan) { m_scan = scan; }

    int scan() const { return m_scan; }

private:
    int m_scan = 0;

private:
    friend class boost::serialization::access;
    template<class Archive>
    void serialize(Archive & ar, const unsigned int version) {
        ar & boost::serialization::base_object<BaseEquipment>(*this);
        ar & m_scan;
    }
};

} // namespace item
} // namespace model


namespace control {
namespace item {

class Scaner : public BaseEquipment
{
public:
    Scaner(model::item::Scaner*);
    virtual ~Scaner() = default;

    int scan() const { return m_scan; }

private:
    void setScanOrig(int scan_orig)  { m_scan_orig = scan_orig; }
    virtual void updateProperties();
    void countPrice();

protected:
    model::item::Scaner* model() const { return m_model_scaner; }
    descriptor::item::Scaner* descriptor() const { return m_descriptor_scaner; }

private:
    model::item::Scaner* m_model_scaner = nullptr;
    descriptor::item::Scaner* m_descriptor_scaner = nullptr;

    int m_scan_orig = 0;
    int m_scan_add = 0;
    int m_scan = 0;

    void virtual addUniqueInfo();

    std::string scanStr();
};

} // namespace item
} // namespace control
