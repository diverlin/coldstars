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
    Star();
    ~Star() = default;
    Star(const std::string& data);
    std::string data() const;

    void setTurnSinceLastSparkCounter(int turnSinceLastSparkCounter) { m_turnSinceLastSparkCounter = turnSinceLastSparkCounter; }

    int turnSinceLastSparkCounter() const { return m_turnSinceLastSparkCounter; }
    int turnSparkThreshold() const { return m_turnSparkThreshold; }

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


namespace control {

class Star : public Planetoid
{
public:
    Star(model::Star*, descriptor::Star*);
    virtual ~Star();

    void hit(int) {}
    void initiateSpark();

    //alpitodorender
    //        int colorId() const;
    //        float brightThreshold() const;
    //float deltaColor() const { return m_deltaColor; }

    // alpitodorender void CalcColor();
    void updateInSpaceInStatic();
    void updateInSpace(int, bool);

    model::Star* model() const { return m_model_star; }
    descriptor::Star* descriptor() const { return m_descriptor_star; }

private:
    model::Star* m_model_star = nullptr;
    descriptor::Star* m_descriptor_star = nullptr;

    float m_deltaColor = 0.0f;
    bool m_sparkActive = false;
    bool m_sparkGrows = false;

    //        virtual void UpdateInfo() override final;

    [[deprecated("ugly, remove")]]
    void _postDeathUniqueEvent(bool);
};

} // namespace control



//class Star : public Planetoid
//{
//public:
//    Star(int);
//    virtual ~Star();

//    //alpitodorender
//    //        int GetColorId() const;
//    //        float GetBrightThreshold() const;
//    float GetDeltaColor() const { return m_DeltaColor; }

//    void hit(int) {}
//    void InitiateSpark();


//    // alpitodorender void CalcColor();
//    void UpdateInSpaceInStatic();
//    void UpdateInSpace(int, bool);

//    virtual void Save(boost::property_tree::ptree&) const override final;
//    virtual void Load(const boost::property_tree::ptree&) override final;
//    virtual void Resolve() override final;

//private:
//    float m_DeltaColor;

//    bool m_SparkActive;
//    bool m_SparkGrows;

//    int m_TurnSinceLastSparkCounter;
//    int m_TurnSparkThreshold;

//    //        virtual void UpdateInfo() override final;
//    virtual void _postDeathUniqueEvent(bool) override final;

//    void SaveData(boost::property_tree::ptree&, const std::string&) const;
//    void LoadData(const boost::property_tree::ptree&);
//    void ResolveData();
//};







