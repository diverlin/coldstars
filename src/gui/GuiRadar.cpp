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


GuiRadar::GuiRadar()
{		
	textureOb_background 	= g_GUI_TEXTUREOB_COLLECTOR.background_radar;
	textureOb_bar	 	= g_GUI_TEXTUREOB_COLLECTOR.bar_radar;
	textureOb_screenrect	= g_GUI_TEXTUREOB_COLLECTOR.screenrect;
		
	scale = RADAR_SCALE;
	int screen_w = Screen::Instance().GetWindow().GetWidth();
    	int screen_h = Screen::Instance().GetWindow().GetHeight();
    	Resize(screen_w, screen_h);
    	       	
	int angle = 0;
	int subtype_id = GUI::BUTTON::WEAPON1_ACTIVATOR_ID;
	for (int i=0; i<GAME::WEAPONS_NUM_MAX; i++)
	{
		vec2i pos = getVec2i(rect.GetWidth()/2.5, angle);
    		ButtonTrigger* button = new ButtonTrigger(	g_GUI_TEXTUREOB_COLLECTOR.dot_purple, 
        					subtype_id,
    						rect.GetCenter().x+pos.x-GUI::ICON_SIZE/2,
    						rect.GetCenter().y+pos.y-GUI::ICON_SIZE/2, 
    					     	GUI::ICON_SIZE*1.5,  
    					     	GUI::ICON_SIZE*1.5, 
    					     	"weapon_"+int2str(i+1));    					     
    		button_map.insert(std::make_pair(subtype_id, button));
    		
		angle += 20;
		subtype_id++;
    	}
}

GuiRadar::~GuiRadar()
{}

void GuiRadar::Resize(int screen_w, int screen_h)
{
	rect.Set(0, 0, 250, 250);
}
     	
void GuiRadar::Reset()
{
	vehicle_vec.clear();
}
    
void GuiRadar::ButtonsAction(Player* player) const
{
	for (std::map<int, BaseButton*>::const_iterator iterator = button_map.begin(); iterator!=button_map.end(); iterator++)
	{
		BaseButton* button = iterator->second;
       		switch(button->GetSubTypeId())
       		{	
        		case GUI::BUTTON::WEAPON1_ACTIVATOR_ID: { player->GetWeaponsSelector().SetSingle(1, button->GetPressed()); break; }
        		case GUI::BUTTON::WEAPON2_ACTIVATOR_ID: { player->GetWeaponsSelector().SetSingle(2, button->GetPressed()); break; }      		
        		case GUI::BUTTON::WEAPON3_ACTIVATOR_ID: { player->GetWeaponsSelector().SetSingle(3, button->GetPressed()); break; }     
          		case GUI::BUTTON::WEAPON4_ACTIVATOR_ID: { player->GetWeaponsSelector().SetSingle(4, button->GetPressed()); break; }     
        		case GUI::BUTTON::WEAPON5_ACTIVATOR_ID: { player->GetWeaponsSelector().SetSingle(5, button->GetPressed()); break; }         		           		   	      	
                	case GUI::BUTTON::WEAPON6_ACTIVATOR_ID: { player->GetWeaponsSelector().SetSingle(6, button->GetPressed()); break; }          		
        		case GUI::BUTTON::WEAPON7_ACTIVATOR_ID: { player->GetWeaponsSelector().SetSingle(7, button->GetPressed()); break; }          		
        		case GUI::BUTTON::WEAPON8_ACTIVATOR_ID: { player->GetWeaponsSelector().SetSingle(8, button->GetPressed()); break; }          		
        		case GUI::BUTTON::WEAPON9_ACTIVATOR_ID: { player->GetWeaponsSelector().SetSingle(9, button->GetPressed()); break; }     
		}
	}
	
	UpdateEquipmentIcons(player);
}
 	
void GuiRadar::UpdateEquipmentIcons(Player* player) const
{
       	WeaponComplex* weapon_complex = player->GetNpc()->GetVehicle()->GetWeaponComplex();
       	GetButton(GUI::BUTTON::WEAPON1_ACTIVATOR_ID)->SetAdditionalTextureOb(weapon_complex->GetItemTextureOb(1));
       	GetButton(GUI::BUTTON::WEAPON2_ACTIVATOR_ID)->SetAdditionalTextureOb(weapon_complex->GetItemTextureOb(2));
       	GetButton(GUI::BUTTON::WEAPON3_ACTIVATOR_ID)->SetAdditionalTextureOb(weapon_complex->GetItemTextureOb(3));
       	GetButton(GUI::BUTTON::WEAPON4_ACTIVATOR_ID)->SetAdditionalTextureOb(weapon_complex->GetItemTextureOb(4));
       	GetButton(GUI::BUTTON::WEAPON5_ACTIVATOR_ID)->SetAdditionalTextureOb(weapon_complex->GetItemTextureOb(5));
       	GetButton(GUI::BUTTON::WEAPON6_ACTIVATOR_ID)->SetAdditionalTextureOb(weapon_complex->GetItemTextureOb(6));
       	GetButton(GUI::BUTTON::WEAPON7_ACTIVATOR_ID)->SetAdditionalTextureOb(weapon_complex->GetItemTextureOb(7));       	       	       	
       	GetButton(GUI::BUTTON::WEAPON8_ACTIVATOR_ID)->SetAdditionalTextureOb(weapon_complex->GetItemTextureOb(8)); 
       	GetButton(GUI::BUTTON::WEAPON9_ACTIVATOR_ID)->SetAdditionalTextureOb(weapon_complex->GetItemTextureOb(9)); 
}

void GuiRadar::Update()
{
	screenrect.Set(rect.GetCenter() + Screen::Instance().GetBottomLeftGlobalCoord() * scale, (int)(Screen::Instance().GetWindow().GetWidth() * scale), (int)(Screen::Instance().GetWindow().GetWidth() * scale));
}

bool GuiRadar::UpdateMouseInteraction(const MouseData& data_mouse)
{		
       	if (rect.CheckInteraction(data_mouse.mx - offset.x, data_mouse.my - offset.y) == true)
        {
        	if (data_mouse.left_press == true)
           	{
           		vec2f new_global_coord( (data_mouse.mx - rect.GetCenter().x - screenrect.GetWidth()/2)/scale, (data_mouse.my - rect.GetCenter().y - screenrect.GetHeight()/2)/scale);
           		Screen::Instance().SetBottomLeftGlobalCoord(new_global_coord);
       			return true;
        	}
     	}
     	
     	return false;
}
     		
void GuiRadar::AddIfWithinRange(BaseGameEntity* instance)
{
	float dist = distBetweenPoints(player->GetNpc()->GetVehicle()->GetPoints().GetCenter(), instance->GetPoints().GetCenter());
	if (dist < 600)
	{
		vehicle_vec.push_back(instance);
	}
}
    		
void GuiRadar::Render() const
{
	drawTexturedRect(textureOb_background, rect, -1.5);
	drawTexturedRect(textureOb_bar, rect, -1.5);
	drawTexturedRect(textureOb_screenrect, screenrect, -1.5);
		
	enable_POINTSPRITE();       	
     		glBindTexture(GL_TEXTURE_2D,  g_GUI_TEXTUREOB_COLLECTOR.dot_red->texture);
		for (unsigned int i=0; i<vehicle_vec.size(); i++)
		{
			float size = 1.0f;
			drawParticle(size, vehicle_vec[i]->GetPoints().GetCenter());			
		}
	disable_POINTSPRITE(); 
	
	RenderButtons();
}
