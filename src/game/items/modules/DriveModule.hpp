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


#ifndef DRIVEMODULE_H
#define DRIVEMODULE_H

#include "BaseModule.hpp"

class DriveModule : public BaseModule
{
       public: 
              DriveModule(int);
              virtual ~DriveModule();

        void SetSpeedAdd(int speed_add) { this->speed_add = speed_add; };
        void SetHyperAdd(int hyper_add) { this->hyper_add = hyper_add; };
        
        int GetSpeedAdd() const { return speed_add; };
        int GetHyperAdd() const { return hyper_add; };

        virtual void Save(boost::property_tree::ptree&) const;
        virtual void Load(const boost::property_tree::ptree&);
        virtual void Resolve();
        
          private:
              int speed_add;
              int hyper_add;

              void virtual AddUniqueInfo();
              
              void SaveData(boost::property_tree::ptree&, const std::string&) const;
        void LoadData(const boost::property_tree::ptree&);
        void ResolveData();
};

#endif
