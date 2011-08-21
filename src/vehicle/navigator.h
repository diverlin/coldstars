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

#ifndef NAVIGATOR_H
#define NAVIGATOR_H


class Navigator
{
   public:
      Ship* pTo_ship;
   
      Planet*     pTo_target_planet;
      Ship*       pTo_target_ship;
      StarSystem* pTo_target_starsystem;  
      
      float target_pos_x;
      float target_pos_y;

      float* pTo_target_pos_x;
      float* pTo_target_pos_y;
      int docking_radius;
      
      Navigator(Ship* _pTo_ship);
      ~Navigator();
      
      void setStaticTargetCoords(float _target_pos_x, float _target_pos_y);
      
      void setTargetPlanet(Planet* _pTo_planet); 
      void setTargetShip(Ship* _pTo_ship);    
      void setTargetStarSystem(StarSystem* _pTo_starsystem);
      
      void removeTargetPlanet();
      void removeTargetShip(); 
      void removeTargetStarSystem();  
      
      bool updateTargetCoords();
      
      bool checkDocking();
      bool getDockingPermission();

};


#endif
