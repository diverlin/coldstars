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

#include "BaseEquipment.hpp"
#include "RocketEquipment.hpp"

#include "../../common/constants.hpp"
//#include <ceti/StringUtils.hpp>
#include "../../slots/ItemSlot.hpp"
#include <jeti/Render.hpp>
#include <jeti/Screen.hpp>
#include "../../resources/GuiTextureObCollector.hpp"
#include "../../common/Logger.hpp"
#include "../../garbage/EntityGarbage.hpp"

#include <jeti/AnimationEffect2D.hpp>

BaseEquipment::BaseEquipment()
{
    race_id = TYPE::RACE::R0_ID;
    animation_notfunctioning = new jeti::AnimationEffect2D(glm::vec3(0.8, 0.8, 1.0), glm::vec3(1.2, 1.2, 1.0), glm::vec3(0.02, 0.02, 0.0), 0, 0, 0);
}

/*virtual */
BaseEquipment::~BaseEquipment()
{
    #if CREATEDESTROY_LOG_ENABLED == 1
    Logger::Instance().Log("___::~BaseEquipment("+std::to_string(GetId())+")");
    #endif
        
    delete animation_notfunctioning;
}

/* virtual */
void BaseEquipment::PutChildsToGarbage() const
{
    for (unsigned int i=0; i<modules_vec.size(); i++)
    {
        EntityGarbage::Instance().Add(modules_vec[i]);
    }
}
        
/* virtual */
void BaseEquipment::AddCommonInfo()
{
    info.addNameStr("tech_level:");   info.addValueStr( getTechLevelStr(data_item.tech_level) );
    info.addNameStr("modules:");   info.addValueStr( std::to_string(data_item.modules_num_max) );
    info.addNameStr("race:");      info.addValueStr( getRaceStr(race_id) );
    info.addNameStr("deteriori:"); info.addValueStr( std::to_string(deterioration) );
    info.addNameStr("condition:"); info.addValueStr( std::to_string(condition) + "/" + std::to_string(data_item.condition_max) );
    info.addNameStr("mass:");      info.addValueStr( std::to_string(data_item.mass) );
    info.addNameStr("price:");     info.addValueStr( std::to_string(price) );

}

bool BaseEquipment::InsertModule(BaseModule* module)
{
    if (module->GetParentSubTypeId() == GetSubTypeId())
    {
        if (modules_vec.size() < data_item.modules_num_max)
            {
                if (module->GetItemSlot() != nullptr)
                {
                    module->GetItemSlot()->RemoveItem();
                }
                module->SetItemSlot(nullptr);
                module->SetEquipmentOwner(this);
                   modules_vec.push_back(module);                
                        
                UpdateProperties();
                item_slot->UpdateVehiclePropetries();

                return true;
            }
        }

           return false;   
} 

/* virtual */
void BaseEquipment::Render(const jeti::Renderer& render, const ceti::Box2D& box, const glm::vec2& gui_offset, bool draw_text)
{        
    RenderKorpus(render, box);

    for (unsigned int i=0; i<modules_vec.size(); i++)
    {
        //Rect module_rect(box.GetCenter().x + (1.1 * GUI::INSERTED_MODULE_SIZE) * (i), 
                     //box.GetCenter().y + (1.1 * GUI::INSERTED_MODULE_SIZE),
                 //GUI::INSERTED_MODULE_SIZE, 
                 //GUI::INSERTED_MODULE_SIZE);
        //drawTexturedRect(modules_vec[i]->GetTextureOb(), module_rect, -1.0f);
    }
        
    if (condition == 0)
    {
        render.DrawQuad(*GuiTextureObCollector::Instance().slot_mark_reject, box);
    }
    if (GetLocked() == true)
    {
        int font_size = 12;    
        render.DrawQuad(*GuiTextureObCollector::Instance().slot_mark_accept, box);

        glm::vec2 pos(box.GetCenter().x - font_size/2 + gui_offset.x, box.GetCenter().y - font_size + gui_offset.y);
        jeti::Screen::Instance().DrawText(std::to_string(locked_turns), font_size, pos);
    }

    if (draw_text == true)
    {
        if (GetSubTypeId() == TYPE::ENTITY::ROCKET_EQUIPMENT_ID)
        {
            glm::vec2 pos(box.GetCenter().x - box.GetSize().x/2 + gui_offset.x, box.GetCenter().y + gui_offset.y);
            jeti::Screen::Instance().DrawText(std::to_string(((RocketEquipment*)this)->GetAmmo()) + "/" + std::to_string(((RocketEquipment*)this)->GetAmmoMax()), 12, pos);
        }
    }
}


void BaseEquipment::SaveData(boost::property_tree::ptree& save_ptree, const std::string& root) const
{
    #if SAVELOAD_LOG_ENABLED == 1
    Logger::Instance().Log(" BaseEquipment::SaveData()  id=" + std::to_string(GetId()) + " START", SAVELOAD_LOG_DIP);
    #endif
}

void BaseEquipment::LoadData(const boost::property_tree::ptree& load_ptree)
{
    #if SAVELOAD_LOG_ENABLED == 1
    Logger::Instance().Log(" BaseEquipment::LoadData()  id=" + std::to_string(GetId()) + " START", SAVELOAD_LOG_DIP);
    #endif
}

void BaseEquipment::ResolveData()
{
    #if SAVELOAD_LOG_ENABLED == 1
    Logger::Instance().Log(" BaseEquipment::ResolveData()  id=" + std::to_string(GetId()) + " START", SAVELOAD_LOG_DIP);
    #endif
}
