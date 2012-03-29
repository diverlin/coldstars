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



#ifndef GUIKOSMOPORT_H
#define GUIKOSMOPORT_H


class GuiKosmoport
{
    	public:
       		GuiKosmoport(Player*);
       		~GuiKosmoport();

		int getActiveScreenId() const;
		
       		void update();
                void Render() const;
                
       	private:
       		int active_screen_id; 
       		
       		Player* player;
       		
       		std::vector<Button*> button_common_pList;
       		std::vector<Button*> button_angar_pList;
       		       		
       	        Button* angar_screen_button;
        	Button* store_screen_button;
        	Button* shop_screen_button;
        	Button* galaxymap_screen_button;
        	Button* goverment_screen_button;

        	Button* repair_button;
        	Button* fuel_button;  
        	Button* launch_button;       	
                
                void resetInfoFlags();
       		void mouseInteractionCheck();

       		void renderInternal() const;
       		void renderInfo() const;
};


#endif 
