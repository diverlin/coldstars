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

#ifndef GRAVITYARTEFACT_H
#define GRAVITYARTEFACT_H

#include "../BaseItem.hpp"

class GravityArtefact : public BaseItem
{
        public:
              GravityArtefact(int);
              virtual ~GravityArtefact();
        
        void SetGravity(int gravity) { this->gravity = gravity; };
        
        int GetGravity() const { return gravity; };
        
             virtual void Save(boost::property_tree::ptree&) const;
        virtual void Load(const boost::property_tree::ptree&);
        virtual void Resolve();
        
    private:  
        int gravity;
           
             virtual void AddUniqueInfo();  
             virtual void AddCommonInfo();   
             
             void SaveData(boost::property_tree::ptree&, const std::string&) const;
        void LoadData(const boost::property_tree::ptree&);
        void ResolveData();                
};

#endif
