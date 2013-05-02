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


#ifndef USERINPUT_H
#define USERINPUT_H

#include <GL/glew.h>
#include <SFML/Window.hpp>
#include "../pilots/Player.hpp"

class UserInput
{
    	public:
		static UserInput& Instance();
        	~UserInput();
		
		bool GetNextTurnReady() const { return next_turn_ready; };

		void UpdateInKosmoport(Player*, GuiManager&);
		void UpdateInSpace(Player*, GuiManager&);

	private:
		UserInput();
		UserInput(const UserInput&) = delete;
		UserInput& operator=(const UserInput&) = delete;
		
	        int moveCamera_axis_x;
        	int moveCamera_axis_y;
        
        	sf::Event event;
        	
        	Vec2<float> scroll_accel; 
        	        	
        	bool next_turn_ready;

        	void ResetFlags(Player*);
        	        	
        	void ManageInputsInSpace(Player*, GuiManager&);
        	void ManageInputsInKosmoport(Player*, GuiManager&);
        	
        	bool KeyPressedCommon(Player*, GuiManager&);
        	void KeyPressedInSpace(Player*, GuiManager&);
        	void KeyPressedInKosmoport(Player*, GuiManager&);
        	void MouseButtonPressed(Player*);
        	        	
        	void ManageRealTimeInputsInSpace(Player*);
        	void ScrollCamera(Player*);
};

#endif 
