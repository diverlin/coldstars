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

#include <core/spaceobject/Planetoid.hpp>

#include <core/descriptor/spaceobject/Star.hpp>

namespace model {

class Star : public Planetoid {

public:
    Star(int_t);
    ~Star() = default;
    Star(const std::string& data);
    std::string data() const;

    void setTurnSinceLastSparkCounter(int turnSinceLastSparkCounter) { m_turnSinceLastSparkCounter = turnSinceLastSparkCounter; }

    int turnSinceLastSparkCounter() const { return m_turnSinceLastSparkCounter; }
    int turnSparkThreshold() const { return m_turnSparkThreshold; }

    Info info() const override final {
        Info result = Planetoid::info();
        result.push_back(std::make_pair("model::Star", ""));
        result.push_back(std::make_pair("turnSinceLastSparkCounter", std::to_string(m_turnSinceLastSparkCounter)));
        result.push_back(std::make_pair("turnSparkThreshold", std::to_string(m_turnSparkThreshold)));
        return result;
    }

private:
    int m_turnSinceLastSparkCounter = 0;
    int m_turnSparkThreshold = 0;

private:
    friend class boost::serialization::access;
    template<class Archive>
    void serialize(Archive & ar, const unsigned int version) {
        ar & boost::serialization::base_object<Planetoid>(*this);
        ar & m_turnSinceLastSparkCounter;
        ar & m_turnSparkThreshold;
    }
};

} // namespace model

