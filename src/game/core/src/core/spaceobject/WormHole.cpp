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

#include "WormHole.hpp"
#include "../common/constants.hpp"
#include <core/manager/DescriptorManager.hpp>

#include <meti/RandUtils.hpp>
#include <ceti/Logger.hpp>
#include "../world/starsystem.hpp"

namespace {
descriptor::WormHole* getDescriptor(model::WormHole* model) {
    return descriptor::Manager::get().wormHole(model->descriptor());
}
} // namespace

namespace control {

WormHole::WormHole(model::WormHole* model)
    :
      Planetoid(model, getDescriptor(model))
    , m_model_wormhole(model)
    , m_descriptor_wormhole(getDescriptor(model))
{
//    setId(id);
//    setTypeId(entity::Type::BLACKHOLE);

//    setMass(meti::getRandInt(1000, 4000));
}

WormHole::~WormHole()
{
    //delete shockwave;
}

void WormHole::setPosition(const glm::vec3& center) { setPosition(center); /*shockwave->setCenter(meti::vec2(center));*/ }

void WormHole::updateInSpace(int time, bool show_effect)
{
    _checkDeath(show_effect);

    if (time > 0) {
        setPosition(position()+meti::getRandXYVec3f(1, 2, 0));
        //        shockwave->setCenter(meti::vec2(center()));

        assert(false);
//        model()->dataLife().life_time--;
//        if (model()->dataLife().life_time < 0) {
//            //scale -= 0.1;
//            //if (scale < 1.0) {
//            model()->dataLife().is_alive = false;
//            //}
//        }
    }

    //    shockwave->Update();
}

//void BlackHole::UpdateInfo()
//{
//    GetInfo().clear();

//    GetInfo().addTitleStr("BLACKHOLE");

//    GetInfo().addNameStr("id:");         GetInfo().addValueStr(std::to_string(id()));
//    GetInfo().addNameStr("mass:");       GetInfo().addValueStr(std::to_string(mass()));
//    GetInfo().addNameStr("pos:");        GetInfo().addValueStr( meti::str(center()) );
//}

} // namespace control



//BlackHole::BlackHole(int id)
//{
//    setId(id);
//    setTypeId(entity::Type::BLACKHOLE);
    
//    setMass(meti::getRandInt(1000, 4000));
//}

//BlackHole::~BlackHole()
//{
//    //delete shockwave;
//}
 
//void BlackHole::setPosition(const glm::vec3& center) { setPosition(center); /*shockwave->setCenter(meti::vec2(center));*/ }
         
//void BlackHole::updateInSpace(int time, bool show_effect)
//{
//    _checkDeath(show_effect);

//    if (time > 0) {
//        setPosition(position()+meti::getRandXYVec3f(1, 2, 0));
////        shockwave->setCenter(meti::vec2(center()));
    
//        _dataLife().life_time--;
//        if (_dataLife().life_time < 0) {
//            //scale -= 0.1;
//            //if (scale < 1.0) {
//                _dataLife().is_alive = false;
//            //}
//        }
//    }

////    shockwave->Update();
//}

////void BlackHole::UpdateInfo()
////{
////    GetInfo().clear();

////    GetInfo().addTitleStr("BLACKHOLE");

////    GetInfo().addNameStr("id:");         GetInfo().addValueStr(std::to_string(id()));
////    GetInfo().addNameStr("mass:");       GetInfo().addValueStr(std::to_string(mass()));
////    GetInfo().addNameStr("pos:");        GetInfo().addValueStr( meti::str(center()) );
////}
          
//void BlackHole::SaveData(boost::property_tree::ptree& save_ptree, const std::string& root) const
//{
//    //LOG(" BlackHole("+std::to_string(id())+")::SaveData");
//}

//void BlackHole::LoadData(const boost::property_tree::ptree& load_ptree)
//{
//    //LOG(" BlackHole("+std::to_string(id())+")::LoadData");
//}

//void BlackHole::ResolveData()
//{
//    //LOG(" BlackHole("+std::to_string(id())+")::ResolveData");
    
//    //starsystem()->add(this, data_unresolved_Orientation.center);
//}
 
///*virtual*/
//void BlackHole::Save(boost::property_tree::ptree& save_ptree) const
//{
//    std::string root = "blackhole." + std::to_string(id())+".";

//    Base::SaveData(save_ptree, root);
//    //Orientation::SaveData(save_ptree, root);
////    BaseDrawable::SaveData(save_ptree, root);
//    SpaceObject::SaveData(save_ptree, root);
//    Planetoid::SaveData(save_ptree, root);
//    BlackHole::SaveData(save_ptree, root);
//}

///*virtual*/
//void BlackHole::Load(const boost::property_tree::ptree& load_ptree)
//{
//    Base::LoadData(load_ptree);
// //   Orientation::LoadData(load_ptree);
////    BaseDrawable::LoadData(load_ptree);
//    SpaceObject::LoadData(load_ptree);
//    Planetoid::LoadData(load_ptree);
//    BlackHole::LoadData(load_ptree);
//}
    
///*virtual*/
//void BlackHole::Resolve()
//{
//    Base::ResolveData();
//   // Orientation::ResolveData();
////    BaseDrawable::ResolveData();
//    SpaceObject::ResolveData();
//    Planetoid::ResolveData();
//    BlackHole::ResolveData();
//}
