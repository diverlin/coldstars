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


#ifndef ASTEROIDMANAGER_HPP
#define ASTEROIDMANAGER_HPP

class Starsystem;

class AsteroidManager 
{
    public:
        AsteroidManager():
        asteroid_num(0),
        asteroid_delay(0),
        asteroid_last_turn_created(0)
        {}
        ~AsteroidManager() {}
        
        void Parameterize(unsigned int asteroids_num, int asteroid_delay = 0) { this->asteroid_num = asteroid_num; this->asteroid_delay = asteroid_delay; }
            
        void Update(Starsystem*);

    private:                         
        unsigned int asteroid_num;
        int asteroid_delay;
        int asteroid_last_turn_created;            
};

#endif 




