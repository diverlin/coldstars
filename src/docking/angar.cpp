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


Angar :: Angar(TextureOb* _texOb_background, TextureOb* _texOb_landingArea)
{
        texOb_background = _texOb_background;

	Platform* platform;
	
	int screen_w = Config::Instance().SCREEN_WIDTH;
	int screen_h = Config::Instance().SCREEN_HEIGHT;	
	
        platform = new Platform(_texOb_landingArea, screen_w/2,       screen_h/2,       GUI::SLOT::WIDTH_FOR_ANGAR, GUI::SLOT::HEIGHT_FOR_ANGAR);
        platform_vec.push_back(platform);

        platform = new Platform(_texOb_landingArea, screen_w/2 + 150, screen_h/2,       GUI::SLOT::WIDTH_FOR_ANGAR, GUI::SLOT::HEIGHT_FOR_ANGAR);
        platform_vec.push_back(platform);
    
        platform = new Platform(_texOb_landingArea, screen_w/2 - 150, screen_h/2,       GUI::SLOT::WIDTH_FOR_ANGAR, GUI::SLOT::HEIGHT_FOR_ANGAR);
        platform_vec.push_back(platform);

        platform = new Platform(_texOb_landingArea, screen_w/2,       screen_h/2 + 150, GUI::SLOT::WIDTH_FOR_ANGAR, GUI::SLOT::HEIGHT_FOR_ANGAR);
        platform_vec.push_back(platform);

        platform = new Platform(_texOb_landingArea, screen_w/2,       screen_h/2 - 150, GUI::SLOT::WIDTH_FOR_ANGAR, GUI::SLOT::HEIGHT_FOR_ANGAR);
        platform_vec.push_back(platform);
}


int Angar :: getFreePlatformTotalNum()
{
        int sum_free = 0;
        for (unsigned int i = 0; i < platform_vec.size(); i++)
        {
                if (platform_vec[i]->getVehicle() == NULL)
                {
                        sum_free++;
                }
        }
        return sum_free; 
}

bool Angar :: add(Vehicle* vehicle)
{
        for (unsigned int i = 0; i < platform_vec.size(); i++)
        {
                if (platform_vec[i]->getVehicle() == NULL)
                {
                        platform_vec[i]->insert(vehicle);
                        return true;
                }
        }
        
        return false;        
}


bool Angar :: remove(Vehicle* vehicle)
{
        for (unsigned int i = 0; i < platform_vec.size(); i++)
        {
                if (platform_vec[i]->getVehicle() != NULL)
                {
                        if (platform_vec[i]->getVehicle() == vehicle)
                        {
                                platform_vec[i]->free();
                                return true;
                        }
                }
        }
    
        return false;       
}



void Angar :: mouseControl(Player* player)
{
        //bool lmb = player->getCursor()->getMouseLeftButton(); 
        bool rmb = player->getCursor()->getMouseRightButton(); 

        for (unsigned int i = 0; i < platform_vec.size(); i++)
        { 
                float dist = distBetweenPoints(player->getCursor()->getMousePos().x, 
                                               player->getScreen()->getHeight() - player->getCursor()->getMousePos().y, 
                                               platform_vec[i]->GetRect().getCenter().x, 
                                               platform_vec[i]->GetRect().getCenter().y);
        				
                if (dist < platform_vec[i]->GetRect().getWidth()/2)
                {
                        if (rmb == true)
                        {
                                if (platform_vec[i]->getVehicle() != NULL)
                                {
                                        player->getNpc()->setScanTarget(platform_vec[i]->getVehicle());
                                }
                        }
                }
        }
}



void Angar :: Render(Player* player) const
{
        clearScreen();
        resetRenderTransformation();
                        
        renderBackground(player);
                
	enable_BLEND();
        
        renderInternals();
        //RenderItemInfo();
        
}

void Angar :: renderBackground(Player* player) const
{
     	Rect screen_rect = Rect(0, 0, player->getScreen()->getWidth(), player->getScreen()->getHeight());
     	drawTexturedRect(texOb_background, screen_rect, -2);  
}

void Angar :: renderInternals() const
{
        for (unsigned int i = 0; i < platform_vec.size(); i++)
        {
                platform_vec[i]->Render();
        }
}

void Angar :: RenderItemInfo(Player* player) const
{
        for (unsigned int i = 0; i < platform_vec.size(); i++)
        { 
		if (platform_vec[i]->getVehicle() != NULL)
                {

                	float dist = distBetweenPoints(player->getCursor()->getMousePos().x, 
                        	                       player->getScreen()->getHeight() - player->getCursor()->getMousePos().y, 
                                	               platform_vec[i]->GetRect().getCenter().x, 
                                        	       platform_vec[i]->GetRect().getCenter().y);
        				
                	if (dist < platform_vec[i]->GetRect().getWidth()/2)
                	{
		                platform_vec[i]->renderInfo();
                	}
                }
        }
}
            

