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


#ifndef BULLETDATA_HPP
#define BULLETDATA_HPP


class BulletData
{
    public:
        int damage; 
        int armor; 
        int live_time;
            
        float speed_init;
        float speed_max;
        float d_speed; 
        float angular_speed; 
        
        BulletData()
        :
        damage(0), 
        armor(0),
        live_time(0),            
        speed_init(0.0),
        speed_max(0.0),
        d_speed(0.0),
        angular_speed(0.0)
        {}
    
        void SaveData(boost::property_tree::ptree&, const std::string&) const;
        void LoadData(const boost::property_tree::ptree&);
        void ResolveData();
};

#endif 
