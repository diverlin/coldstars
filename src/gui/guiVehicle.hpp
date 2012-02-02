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


#ifndef GUIVEHICLE_H
#define GUIVEHICLE_H

class GuiVehicle
{
   	public:
      		GuiVehicle();
      		~GuiVehicle();

      		void bind(Vehicle*);
      		void createControlSkillButtons();

                void configure(Vehicle*, bool _in_store, bool _allow_full_control);
     		void update();
      		void render() const;

      	private:
                bool in_store;
                bool allow_full_control;
                
      	      	Vehicle* vehicle;
      		Skill* skill;
      		
      		std::vector<Button*> button_vec;
      	
      	      			Button* increment_attack_button;  
      				Button* decrement_attack_button;  
                
      				Button* increment_defence_button;  
      				Button* decrement_defence_button;  
        
      				Button* increment_leader_button;  
      				Button* decrement_leader_button; 
      
      				Button* increment_trader_button;  
      				Button* decrement_trader_button; 
    
      				Button* increment_technic_button;  
      				Button* decrement_technic_button; 
     
      				Button* increment_diplomat_button;  
     				Button* decrement_diplomat_button;    
     		
     		void manageSkill();
     		void mouseControl();
     		
     		void renderInternaly() const;
      		void renderSkill() const;	
};



#endif
