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


#include "BaseItem.hpp"
#include <common/constants.hpp>
#include <ceti/Logger.hpp>
//#include <ceti/StringUtils.hpp>

#include <common/Global.hpp>
#include <managers/EntityManager.hpp>

#include <slots/ItemSlot.hpp>

namespace item {

Base::Base()
{}

/* virtual */
Base::~Base()
{
    LOG("___::~BaseItem("+std::to_string(id())+")");
}

void Base::lockEvent(int locked_turns)
{
    LOG("BaseItem::LockEvent");
    
    bool was_working = false;
    if (m_locked_turns == 0) {
        was_working = true;
    }
    
    m_locked_turns += locked_turns;
    if (was_working == true) {
        m_item_slot->updateVehiclePropetries();
    }
}
                
void Base::useNormalDeterioration()
{
    m_deterioration = m_data_item.deterioration;
}
                                
void Base::useOverloadDeterioration()
{
    m_deterioration = m_data_item.deterioration * m_data_item.deterioration_overload_rate;
}
 
void Base::damageEvent()
{
    LOG("BaseItem::DamageEvent");

    m_item_slot->updateVehiclePropetries();
}
                
void Base::deteriorationEvent()
{
    m_condition -= m_deterioration;
    if (m_condition <= 0) {
        m_condition = 0;
        damageEvent();
    }
}         
                
bool Base::repairEvent()
{
    m_condition = m_data_item.condition_max;
    m_item_slot->updateVehiclePropetries();
    
    return true;
}

void Base::updateLock()
{
    if (m_locked_turns > 0) {
        m_locked_turns--;
        if (m_locked_turns == 0) {
            m_item_slot->updateVehiclePropetries();
        }
    }
}     

//void BaseItem::UpdateInfo()
//{
////    info.clear();

//    addUniqueInfo();
//    AddCommonInfo();
//}

//void BaseItem::RenderInfo(const jeti::Renderer& render, const glm::vec2& pos)
//{
//    UpdateInfo();
    
//    //render.enable_BLEND();
//    jeti::drawInfoIn2Column(info.title_list, info.value_list, pos);
//    //render.disable_BLEND();
//}

///* virtual */
//void BaseItem::Render(const jeti::Renderer& render, const ceti::Box2D& box, const glm::vec2& gui_offset, bool draw_text)
//{
//    RenderKorpus(render, box);
//}

//void BaseItem::RenderKorpus(const jeti::Renderer& render, const ceti::Box2D& box)
//{
//    glm::vec2 v(0.0);
//    glm::vec4 c(1.0, 1.0, 1.0, 1.0);
//    glm::vec3 center(box.center().x, box.center().y, GUI::POS_Z);
//    setCenter(center);
//    //SetAngle(box.GetAngle());
//    //SetScale(box.size());
//    //RenderMeshLight(v, c);
//}

void Base::SaveData(boost::property_tree::ptree& save_ptree, const std::string& root) const
{
    LOG(" BaseItem::SaveData()  id=" + std::to_string(id()) + " START");
    
    save_ptree.put(root+"price", m_price);
    save_ptree.put(root+"condition", m_condition);
    save_ptree.put(root+"locked_turns", m_locked_turns);
    save_ptree.put(root+"race_id", (int)m_race_id);
    save_ptree.put(root+"parent_subtype_id", (int)m_parent_subtype_id);

    save_ptree.put(root+"data_item.tech_level",                     (int)m_data_item.tech);
    //save_ptree.put(root+"data_item.modules_num_max",                m_data_item.modules_num);
    save_ptree.put(root+"data_item.condition_max",                  m_data_item.condition_max);
    save_ptree.put(root+"data_item.deterioration_normal",           m_data_item.deterioration);
    save_ptree.put(root+"data_item.deterioration_overload_rate",    m_data_item.deterioration_overload_rate);
    save_ptree.put(root+"data_item.mass",                           m_data_item.mass);

    //alpitodorender
//    if (HasTextureOb())     { save_ptree.put(root+"unresolved.textureOb_path", textureOb().GetData().texture_path); }
//    else                    { save_ptree.put(root+"unresolved.textureOb_path", "none"); }
        
    if (m_item_slot)   { save_ptree.put(root+"unresolved.item_slot_id", m_item_slot->id()); }
    else               { save_ptree.put(root+"unresolved.item_slot_id", NONE_ID); }
}

void Base::LoadData(const boost::property_tree::ptree& load_ptree)
{
    LOG(" BaseItem::LoadData()  id=" + std::to_string(id()) + " START");
    
    m_price             = load_ptree.get<int>("price");
    m_condition         = load_ptree.get<int>("condition");
    m_locked_turns      = load_ptree.get<int>("locked_turns");
    m_race_id           = (TYPE::RACE)load_ptree.get<int>("race_id");
    m_parent_subtype_id = (TYPE::ENTITY)load_ptree.get<int>("parent_subtype_id");

    m_data_item.tech           = (TYPE::TECH)load_ptree.get<int>("data_item.tech_level");
    //m_data_item.modules_num      = load_ptree.get<int>("data_item.modules_num_max");
    m_data_item.condition_max        = load_ptree.get<int>("data_item.condition_max");
    m_data_item.deterioration = load_ptree.get<int>("data_item.deterioration_normal");
    m_data_item.deterioration_overload_rate = load_ptree.get<float>("data_item.deterioration_overload_rate");
    m_data_item.mass                 = load_ptree.get<int>("data_item.mass");
                    
    m_data_unresolved_BaseItem.textureOb_path = load_ptree.get<std::string>("unresolved.textureOb_path");
    m_data_unresolved_BaseItem.item_slot_id   = load_ptree.get<int>("unresolved.item_slot_id");
}
                
void Base::ResolveData()
{
    LOG(" BaseItem::ResolveData()  id=" + std::to_string(id()) + " START");
    
    //BindData2D(TextureCollector::Instance().GetTextureObByPath(data_unresolved_BaseItem.textureOb_path));
    
    useNormalDeterioration();
    updateProperties(); // this function must be performed before inserting to slot!!!
        
    if(m_data_unresolved_BaseItem.item_slot_id != NONE_ID) // item_slot can be nullptr in case of inserted module
    {
        ((ItemSlot*)global::get().entityManager().get(m_data_unresolved_BaseItem.item_slot_id))->insertItem(this);
    }
}

} // namespace item