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

#include "Cursor.hpp"
#include "../render/Screen.hpp"
#include "../builder/ItemSlotBuilder.hpp"

#include "../spaceobjects/RocketBullet.hpp"
#include "../spaceobjects/Satellite.hpp"
#include "../spaceobjects/Ship.hpp"
#include "../spaceobjects/SpaceStation.hpp"
#include "../spaceobjects/Asteroid.hpp"
#include "../spaceobjects/Planet.hpp"
#include "../spaceobjects/Star.hpp"
#include "../spaceobjects/BlackHole.hpp"
#include "../spaceobjects/Container.hpp"

#include "../parts/WeaponComplex.hpp"

Cursor::Cursor():focused_space_ob(NULL)
{
     	item_slot = GetNewItemSlot(ENTITY::CARGO_SLOT_ID);
     	rect.Set(0, 0, GUI::ITEMSLOT::WIDTH_FOR_CURSOR, GUI::ITEMSLOT::HEIGHT_FOR_CURSOR);
}

Cursor::~Cursor()
{}

void Cursor::UpdateMouseStuff()
{
   	data_mouse.left_click = false;
   	data_mouse.right_click = false;
   	
        const sf::Input& Input = Screen::Instance().GetWindow().GetInput();
        data_mouse.left_press  = Input.IsMouseButtonDown(sf::Mouse::Left);
        data_mouse.right_press = Input.IsMouseButtonDown(sf::Mouse::Right);        

        data_mouse.mx = Input.GetMouseX();
        data_mouse.my = Screen::Instance().GetWindow().GetHeight() - Input.GetMouseY();
                
        data_mouse.mxvp = data_mouse.mx + Screen::Instance().GetBottomLeftGlobalCoord().x;
    	data_mouse.myvp = data_mouse.my + Screen::Instance().GetBottomLeftGlobalCoord().y;
}

void Cursor::Update(const MouseData& data_mouse)
{
     	rect.SetCenter(data_mouse.mx, data_mouse.my);
}

void Cursor::RenderFocusedSpaceObjectStuff()
{
	if (focused_space_ob != NULL)
	{
		switch(focused_space_ob->GetTypeId())
		{
			case ENTITY::VEHICLE_ID:
			{
				switch(focused_space_ob->GetSubTypeId())
				{
					case ENTITY::ROCKETBULLET_ID:
					{
						((RocketBullet*)focused_space_ob)->RenderInfoInSpace(Screen::Instance().GetBottomLeftGlobalCoord());
						
						break;
					}

					case ENTITY::SATELLITE_ID:
					{
						Satellite* satellite = (Satellite*)focused_space_ob;
						
			                	satellite->GetWeaponComplex().RenderWeaponIcons();

                				satellite->RenderRadarRange(); 
                				satellite->GetWeaponComplex().RenderWeaponsRange(); 
                		                                
                        			satellite->GetDriveComplex().DrawPath(); 

						satellite->RenderInfoInSpace(Screen::Instance().GetBottomLeftGlobalCoord());
						                        
						break;
					}

					case ENTITY::SHIP_ID:
					{
						Ship* ship = (Ship*)focused_space_ob;
						
			                	ship->GetWeaponComplex().RenderWeaponIcons();

                				ship->RenderRadarRange(); 
                				ship->GetWeaponComplex().RenderWeaponsRange(); 
                		                                
                        			ship->GetDriveComplex().DrawPath(); 

						ship->RenderInfoInSpace(Screen::Instance().GetBottomLeftGlobalCoord());
						                        
						break;
					}

					case ENTITY::SPACESTATION_ID:
					{
						SpaceStation* spacestation = (SpaceStation*)focused_space_ob;
	
			                	spacestation->GetWeaponComplex().RenderWeaponIcons();

                				spacestation->RenderRadarRange(); 
                				spacestation->GetWeaponComplex().RenderWeaponsRange(); 
                		                                
                        			spacestation->GetDriveComplex().DrawPath(); 
        
        					spacestation->RenderInfoInSpace(Screen::Instance().GetBottomLeftGlobalCoord());
        					                
						break;
					}
				}

				
				break;
			}

			case ENTITY::CONTAINER_ID:
			{
				((Container*)focused_space_ob)->RenderInfoInSpace(Screen::Instance().GetBottomLeftGlobalCoord());
				
				break;
			}

			case ENTITY::ASTEROID_ID:
			{
				((Asteroid*)focused_space_ob)->GetOrbit()->Draw();

				((Asteroid*)focused_space_ob)->RenderInfoInSpace(Screen::Instance().GetBottomLeftGlobalCoord());
								
				break;
			}

			case ENTITY::BLACKHOLE_ID:
			{
				((BlackHole*)focused_space_ob)->RenderInfoInSpace(Screen::Instance().GetBottomLeftGlobalCoord());
				
				break;
			}
									
			case ENTITY::PLANET_ID:
			{
				((Planet*)focused_space_ob)->GetOrbit()->Draw();

				((Planet*)focused_space_ob)->RenderInfoInSpace(Screen::Instance().GetBottomLeftGlobalCoord());
								
				break;
			}
			
			case ENTITY::STAR_ID:
			{
				((Star*)focused_space_ob)->RenderInfoInSpace(Screen::Instance().GetBottomLeftGlobalCoord());

				break;
			}		
		}
	
	}
	
	focused_space_ob = NULL;
}
