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

#include <spaceobjects/Planetoid.hpp>

namespace model {

class Asteroid : public Planetoid {
public:
    static const int SCALE_MIN;
    static const int SCALE_MAX;
    static const int EXPIRIENCE_TO_GIVE;

public:
    Asteroid() = default;
    ~Asteroid() = default;
    Asteroid(const std::string& data);
    std::string data() const;

private:
    friend class boost::serialization::access;
    template<class Archive>
    void serialize(Archive & ar, const unsigned int version)
    {
        ar & boost::serialization::base_object<Planetoid>(*this);
    }
};

} // namespace model


namespace control {

class Asteroid : public Planetoid
{
    public:
        Asteroid(model::Asteroid*);
        virtual ~Asteroid();

        int damage() const { return mass()*10; };

        void updateInSpace(int, bool);
        void collisionEvent(bool);

        model::Asteroid* model() const { return m_model_asteroid; }

    private:
        void _postDeathUniqueEvent(bool);

        model::Asteroid* m_model_asteroid = nullptr;

//        virtual void UpdateInfo() override final;
};

} // namespace control

//class Asteroid : public Planetoid
//{
//    public:
//        Asteroid(int);
//        virtual ~Asteroid();

//        int damage() const { return mass()*10; };

//        void updateInSpace(int, bool);
//        void collisionEvent(bool);

//        virtual void Save(boost::property_tree::ptree&) const override final;
//        virtual void Load(const boost::property_tree::ptree&) override final;
//        virtual void Resolve() override final;
        
//    private:
//        void _postDeathUniqueEvent(bool);

////        virtual void UpdateInfo() override final;
        
//        void SaveData(boost::property_tree::ptree&, const std::string&) const;
//        void LoadData(const boost::property_tree::ptree&);
//        void ResolveData();
//};

