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

class UserInput
{
    	public:
		static UserInput& Instance();
        	~UserInput();

		bool GetSaveCommand() const { return save; };
		bool GetLoadCommand() const { return load; };
		
		bool GetNextTurnReady() const { return next_turn_ready; };

		void UpdateInKosmoport(Player*);
		void UpdateInSpace(Player*, GuiSpace*);

	private:
		UserInput();
		UserInput(const UserInput&) = delete;
		UserInput& operator=(const UserInput&) = delete;
		
		bool save, load;
	        bool keyboardLeftPressed;
        	bool keyboardRightPressed;    
        	bool keyboardUpPressed;    
        	bool keyboardDownPressed;  
        
        	sf::Event event;
        	
        	int scroll_accel_x; 
        	int scroll_accel_y; 
        	
        	bool next_turn_ready;

        	void ResetFlags(Player*);
        	        	
        	void GetSimpleInputsInSpace(Player*, GuiSpace*);
        	void GetSimpleInputsInKosmoport(Player*);
        	void KeyPressedInSpace(Player*, GuiSpace*);
        	void KeyPressedInKosmoport(Player*);
        	void MouseButtonPressed(Player*);
        	        	
        	void GetRealTimeInputs();
        	void ScrollCamera(Player*);
};

#endif 
