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

#ifndef GOVERMENT_H
#define GOVERMENT_H

#include "Room.hpp"

class Goverment : public Room
{
        public: 
                Goverment(int);
                ~Goverment();
                
                void SetTextureObFace(TextureOb* textureOb_face) { this->textureOb_face = textureOb_face; };
           
                void SaveData(boost::property_tree::ptree&) const;        
        void LoadData(const boost::property_tree::ptree&);
        void ResolveData();
        
        private:
                TextureOb* textureOb_face;
                
                void SaveDataUniqueGoverment(boost::property_tree::ptree&, const std::string&) const;        
        void LoadDataUniqueGoverment(const boost::property_tree::ptree&);
        void ResolveDataUniqueGoverment();
};

#endif
