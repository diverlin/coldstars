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



GuiKosmoport::GuiKosmoport(Player* player)
{
	this->player = player;
	      	
	int screen_w = Config::Instance().SCREEN_WIDTH;
	int screen_h = Config::Instance().SCREEN_HEIGHT;
	
        TextureOb* texOb_button = g_GUI_TEXTUREOB_COLLECTOR.dot_green; // fake

    	Button* angar_screen_button     = new Button(texOb_button, 
    					     GUI::SCREEN::ANGAR_ID,
    					     screen_w - 1 * (GUI::ICON_SIZE + 5), 
    					     GUI::ICON_SIZE, 
    					     GUI::ICON_SIZE,  
    					     GUI::ICON_SIZE, 
    					     "angar");    					     
    	button_vec.push_back(angar_screen_button);
    	
    	Button* store_screen_button     = new Button(texOb_button, 
    					     GUI::SCREEN::STORE_ID,
    					     screen_w - 2 * (GUI::ICON_SIZE + 5),
    					     GUI::ICON_SIZE, 
    					     GUI::ICON_SIZE,  
    					     GUI::ICON_SIZE, 
    					     "store");
	button_vec.push_back(store_screen_button);
    					        	
    	Button* shop_screen_button      = new Button(texOb_button, 
    					     GUI::SCREEN::SHOP_ID,
    					     screen_w - 3 * (GUI::ICON_SIZE + 5), 
    					     GUI::ICON_SIZE, 
    					     GUI::ICON_SIZE,  
    					     GUI::ICON_SIZE, 
    					     "shop");
    	button_vec.push_back(shop_screen_button);
    					     
    	Button* galaxymap_screen_button = new Button(texOb_button, 
    					     GUI::SCREEN::GALAXYMAP_ID,
    					     screen_w - 4 * (GUI::ICON_SIZE + 5), 
    					     GUI::ICON_SIZE, 
    					     GUI::ICON_SIZE,  
    					     GUI::ICON_SIZE, 
    					     "galaxymap");
        button_vec.push_back(galaxymap_screen_button);
    					     
    	Button* goverment_screen_button = new Button(texOb_button, 
    					     GUI::SCREEN::GOVERMENT_ID,
    					     screen_w - 5 * (GUI::ICON_SIZE + 5), 
    					     GUI::ICON_SIZE,
    					     GUI::ICON_SIZE,  
    					     GUI::ICON_SIZE, 
    					     "goverment");
    	button_vec.push_back(goverment_screen_button);

	active_screen_id = GUI::SCREEN::ANGAR_ID;
}


GuiKosmoport::~GuiKosmoport()
{
	for (unsigned int i=0; i<button_vec.size(); i++)
	{
       		delete button_vec[i];
        }
}
		
bool GuiKosmoport::UpdateMouseInteraction(int mxvp, int myvp, int lmb, int rmb)
{
    	for (unsigned int i = 0; i< button_vec.size(); i++)
	{
       		if (button_vec[i]->CheckInteraction(mxvp, myvp) == true)
       		{
       			if (lmb == true)
       			{	
       			   	active_screen_id = button_vec[i]->GetSubTypeId();
       			   	return true;       			   	
       			}
       			break;
       		}
        }
        
        return false;
}

void GuiKosmoport::RenderButtons() const
{   
    	for (unsigned int i = 0; i< button_vec.size(); i++)
	{
       		button_vec[i]->Render();
        }    	
}

void GuiKosmoport::RenderFocusedButtonInfo(int mxvp, int myvp) const
{
	for (unsigned int i = 0; i<button_vec.size(); i++)
	{
       		if (button_vec[i]->CheckInteraction(mxvp, myvp) == true)
       		{
        		button_vec[i]->RenderInfo();
        		return; break;
        	}
        } 
}
                
