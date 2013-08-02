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
#include <builder/slots/ItemSlotBuilder.hpp>

#include "../items/BaseItem.hpp"

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
#include "ButtonTrigger.hpp"
#include "../resources/GuiTextureObCollector.hpp"
#include "../pilots/Player.hpp"
#include "../pilots/Npc.hpp"

#include "../render/Render.hpp"

#include <slots/ItemSlot.hpp>


Cursor::Cursor()
: 
BaseGuiElement(),
focused_ob(nullptr)
{
    item_slot = GetNewItemSlotWithoutSaveAbility(TYPE::ENTITY::CARGO_SLOT_ID);
    
    GetBox().SetSize(GUI::ITEMSLOT::WIDTH_FOR_CURSOR, GUI::ITEMSLOT::HEIGHT_FOR_CURSOR);
    
    //ButtonTrigger* button; // EXPERIMENTAL GUI
    //button = new ButtonTrigger(GuiTextureObCollector::Instance().dot_red, GUI::BUTTON::ACTION_ATTACK_ID, "attack");  
    //button_map.insert(std::make_pair(button->GetSubTypeId(), button));
    
    //button = new ButtonTrigger(GuiTextureObCollector::Instance().dot_purple, GUI::BUTTON::ACTION_PRECISEATTACK_ID, "presize_attack");  
    //button_map.insert(std::make_pair(button->GetSubTypeId(), button));
    
    //button = new ButtonTrigger(GuiTextureObCollector::Instance().dot_green, GUI::BUTTON::ACTION_SCAN_ID, "scan");  
    //button_map.insert(std::make_pair(button->GetSubTypeId(), button));
    
    //button = new ButtonTrigger(GuiTextureObCollector::Instance().dot_blue, GUI::BUTTON::ACTION_GRAB_ID, "grab");  
    //button_map.insert(std::make_pair(button->GetSubTypeId(), button)); 	   		
    
    //button = new ButtonTrigger(GuiTextureObCollector::Instance().dot_yellow, GUI::BUTTON::ACTION_FOLLOW_ID, "follow");  
    //button_map.insert(std::make_pair(button->GetSubTypeId(), button));
        
    //int angle = 0;
    //for (std::map<int, BaseButton*>::const_iterator iterator = button_map.begin(); iterator!=button_map.end(); iterator++)
    //{
    //float scale = 0.4;
        //Vec2<float> pos = getVec2f(100*scale, angle);	
    //rect.SetCenter(pos);
    //rect.SetSize(GUI::ITEMSLOT::WIDTH_FOR_SHIP, GUI::ITEMSLOT::HEIGHT_FOR_SHIP);		    			   
        //rect.Scale(scale);	
        //iterator->second->SetRect(rect);   
    
    //angle += 360/button_map.size();
    //}
}

Cursor::~Cursor()
{}

void Cursor::UpdateMouseStuff()
{
   	data_mouse.left_click = false;
   	data_mouse.right_click = false;
   	
	sf::Vector2i mouse_pos = sf::Mouse::getPosition(Screen::Instance().GetWindow());
	
	data_mouse.left_press  = sf::Mouse::isButtonPressed(sf::Mouse::Left);
	data_mouse.right_press = sf::Mouse::isButtonPressed(sf::Mouse::Right);       
	
	data_mouse.pos_screencoord.Set(mouse_pos.x, Screen::Instance().GetHeight() - mouse_pos.y);
	data_mouse.pos_worldcoord = data_mouse.pos_screencoord*Screen::Instance().GetScale() + Screen::Instance().GetBottomLeftScreenWC();
}

void Cursor::Update()
{
    GetBox().SetCenter(data_mouse.pos_screencoord.x, data_mouse.pos_screencoord.y);     	
}

void Cursor::RenderFocusedObjectStuff() const
{
	if (focused_ob != nullptr)
	{
		enable_BLEND();
	    {
        	focused_ob->RenderStuffWhenFocusedInSpace();

			Box2D box(focused_ob->GetCenter(), focused_ob->GetSize());
			box.SetScale(1.1, 1.1);
			box.SetAngle(focused_ob->GetAngle().z);
			drawQuad(GuiTextureObCollector::Instance().mark_target, box);
        }
        disable_BLEND();   	
	}
}

void Cursor::RenderFocusedObjectInfo()
{
	if (focused_ob != nullptr)
	{
		enable_BLEND();
	    {
        	focused_ob->RenderInfoInSpace(Screen::Instance().GetBottomLeftScreenWC(), Screen::Instance().GetScale());
        }
        disable_BLEND();   	
	}
	
	focused_ob = nullptr;
}

/* virtual override final */
void Cursor::RenderUnique(Player* player) const
{
    item_slot->RenderItem(GetBox(), Vec3<float>(0,0,0));   
}
