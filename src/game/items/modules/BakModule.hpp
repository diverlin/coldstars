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


#ifndef BAKMODULE_H
#define BAKMODULE_H

#include "BaseModule.hpp"

class BakModule : public BaseModule
{
       public:
             BakModule(int);
              virtual ~BakModule();
 
         void SetFuelMaxAdd(int fuel_max_add) { this->fuel_max_add = fuel_max_add; };
         int GetFuelMaxAdd() const { return fuel_max_add; };

        virtual void Save(boost::property_tree::ptree&) const;
        virtual void Load(const boost::property_tree::ptree&);
        virtual void Load();
        
         private:
              int fuel_max_add;
              
              void virtual AddUniqueInfo();

        void SaveDataUniqueBakModule(boost::property_tree::ptree&, const std::string&) const;
        void LoadDataUniqueBakModule(const boost::property_tree::ptree&);
        void ResolveDataUniqueBakModule();
};

#endif
