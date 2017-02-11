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

#include <core/spaceobjects/Vehicle.hpp>
#include <core/parts/orbit.hpp>


namespace model {

class Satellite : public model::Vehicle
{
public:
    Satellite();
    virtual ~Satellite();
    Satellite(const std::string& data);
    std::string data() const;

private:
    // ..

private:
    friend class boost::serialization::access;
    template<class Archive>
    void serialize(Archive & ar, const unsigned int version)
    {
        ar & boost::serialization::base_object<Vehicle>(*this);
    }
};

} // namespace model


namespace control {

class Satellite : public Vehicle
{
public:
    Satellite(model::Satellite*);
    virtual ~Satellite();

    void BindParent(const SpaceObject* const);

    virtual void UpdateInSpace(int, bool) override final;

    //        void RenderInSpace(const jeti::Renderer&, float);
    //        void RenderAtPlanet(const jeti::Renderer&);

    model::Satellite* model() const { return m_model_satellite; }
private:
    model::Satellite* m_model_satellite = nullptr;

    Orbit m_Orbit;

    //        virtual void UpdateInfo() override final;
    //        void UpdateRenderStuff();
};

} // namespace control



//class Satellite : public Vehicle
//{
//    public:
//        Satellite(int);
//        virtual ~Satellite();

//        void BindParent(const SpaceObject* const);
            
//        virtual void UpdateInSpace(int, bool) override final;
        
////        void RenderInSpace(const jeti::Renderer&, float);
////        void RenderAtPlanet(const jeti::Renderer&);
                
//        virtual void Save(boost::property_tree::ptree&) const override final;
//        virtual void Load(const boost::property_tree::ptree&) override final;
//        virtual void Resolve() override final;
            
//    private:
//        Orbit m_Orbit;

////        virtual void UpdateInfo() override final;
////        void UpdateRenderStuff();
                        
//        void SaveData(boost::property_tree::ptree&, const std::string&) const;
//        void LoadData(const boost::property_tree::ptree&);
//        void ResolveData();
//};


