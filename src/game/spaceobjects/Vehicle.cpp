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

#include <spaceobjects/Vehicle.hpp>
#include <spaceobjects/Planet.hpp>
#include <spaceobjects/SpaceStation.hpp>
#include <spaceobjects/Container.hpp>

#include <world/starsystem.hpp>
#include <world/EntityManager.hpp>
#include <garbage/EntityGarbage.hpp>

//#include <ceti/StringUtils.hpp>
#include <common/Logger.hpp>

//#include <jeti/Render.hpp>

#include <resources/GuiTextureObCollector.hpp>

#include <slots/VehicleSlot.hpp> 
#include <slots/ItemSlot.hpp>

#include <items/equipment/RocketEquipment.hpp>
#include <items/equipment/EnergizerEquipment.hpp>
#include <items/equipment/FreezerEquipment.hpp>
#include <items/equipment/RadarEquipment.hpp>
#include <items/equipment/BakEquipment.hpp>
#include <items/equipment/ProtectorEquipment.hpp>
#include <items/equipment/DroidEquipment.hpp>
#include <items/equipment/DriveEquipment.hpp>
#include <items/equipment/ScanerEquipment.hpp>
#include <items/equipment/GrappleEquipment.hpp>
#include <items/others/GoodsPack.hpp>
#include <items/artefacts/GravityArtefact.hpp>
#include <items/artefacts/ProtectorArtefact.hpp>

#include <effects/Shield.hpp>
#include <jeti/particlesystem/DriveEffect.hpp>
#include <jeti/particlesystem/ExplosionEffect.hpp>
#include <text/VerticalFlowText.hpp> 

#include <parts/Turrel.hpp>

#include <pilots/Npc.hpp>

#include <dock/Kosmoport.hpp>
#include <dock/Angar.hpp>
#include <dock/Shop.hpp>
#include <dock/Store.hpp>
#include <dock/NatureLand.hpp>

//#include <jeti/Render.hpp>

#include <math/rand.hpp>
#include <meti/RandUtils.hpp>

Vehicle::Vehicle()
:
m_GodMode(false),
m_SpecialActionId(VEHICLE_SPECIAL_ACTION_TYPE::NONE_ID),
m_OwnerNpc(nullptr),
m_ParentVehicleSlot(nullptr),
m_Land(nullptr),
m_SlotRadar(nullptr),
m_SlotScaner(nullptr),
m_SlotEnergizer(nullptr),
m_SlotGrapple(nullptr),
m_SlotDroid(nullptr),
m_SlotFreezer(nullptr)
{
    m_ComplexWeapon.SetOwnerVehicle(this);
    m_ComplexDrive.SetOwnerVehicle(this);
    m_ComplexProtector.SetOwnerVehicle(this);
}

/* virtual */
Vehicle::~Vehicle()
{
    #if CREATEDESTROY_LOG_ENABLED == 1
    Logger::Instance().Log("___::~Vehicle("+std::to_string(GetId())+")");
    #endif
} 

/* virtual override */
void Vehicle::PutChildsToGarbage() const
{
    m_OwnerNpc->SetAlive(false);
    EntityGarbage::Instance().Add(m_OwnerNpc);
    
    for(unsigned int i=0; i<m_SlotTotal_vec.size(); i++)
    {
        EntityGarbage::Instance().Add(m_SlotTotal_vec[i]);    
    }
}

void Vehicle::CreateDriveComplexTextureDependedStuff()
{
    GetPoints().addMidLeftPoint();
    GetPoints().addMidFarLeftPoint();
        
    //DriveEffect* drive_effect = GetNewDriveEffect(GetTextureOb().GetData().size_id, GetPoints().GetpMidLeft(), GetPoints().GetpMidFarLeft());
    //m_ComplexDrive.SetDriveEffect(drive_effect);
}    

void Vehicle::CreateProtectionComplexTextureDependedStuff()
{
    m_ComplexProtector.GetShieldEffect()->SetParent(this);
}

void Vehicle::SetKorpusData(const VehicleKorpusData& data_korpus) 
{ 
    m_DataKorpus = data_korpus; 
    m_Properties.protection = m_DataKorpus.protection;
}
                
GoodsPack* Vehicle::GetGoodsPack() const
{
    for(unsigned int i=0; i<m_SlotCargo_vec.size(); i++)
    {
        if (m_SlotCargo_vec[i]->GetItem() != nullptr)
        {
            if (m_SlotCargo_vec[i]->GetItem()->GetTypeId() == TYPE::ENTITY::GOODS_ID)
            {
                return m_SlotCargo_vec[i]->GetGoodsPack();
            }
        }
    }    
    
    return nullptr;
}
        
/* virtual override final */
int Vehicle::GetGivenExpirience() const
{
    return m_OwnerNpc->GetSkills().GetExpirience() * GIVEN_EXPIRIENCE_RATE_DEPENDING_ON_NPC_EXPIRIENCE;
}
    
bool Vehicle::CheckItemSlotPresenceBySubTypeId(TYPE::ENTITY slot_subtype_id) const
{
    for (unsigned int i=0; i<m_SlotTotal_vec.size(); i++)
    {
        if (m_SlotTotal_vec[i]->GetSubTypeId() == slot_subtype_id)
        {
            return true;
        }
    }
    
    return false;
}
                    
void Vehicle::AddItemSlot(ItemSlot* slot) 
{ 
    slot->SetOwner(this); 
                
    switch(slot->GetSubTypeId())
    {
        case TYPE::ENTITY::WEAPON_SLOT_ID:    
        {
            float border_start = 0.2;
            float border_end   = 0.8;
            
            float pos_x = meti::getRandFloat(border_start, border_end) - 0.5;
            float pos_y = meti::getRandFloat(border_start, border_end) - 0.5;
                            
            slot->GetTurrel()->SetParentCenter(pos_x, pos_y, DEFAULT_ENTITY_ZPOS);
            GetPoints().Add(slot->GetTurrel()->GetpCenter(), slot->GetTurrel()->GetpParentCenter()); 
            m_ComplexWeapon.AddSlot(slot); 
            
            break; 
        }
        case TYPE::ENTITY::DRIVE_SLOT_ID:     { m_ComplexDrive.SetDriveSlot(slot); break; }
        case TYPE::ENTITY::BAK_SLOT_ID:       { m_ComplexDrive.SetBakSlot(slot); break; }
        case TYPE::ENTITY::PROTECTOR_SLOT_ID: { m_ComplexProtector.SetProtectorSlot(slot); break; }
        case TYPE::ENTITY::RADAR_SLOT_ID:     { m_SlotRadar  = slot; break; }
        case TYPE::ENTITY::SCANER_SLOT_ID:    { m_SlotScaner = slot; break; }        
        case TYPE::ENTITY::ENERGIZER_SLOT_ID: { m_SlotEnergizer = slot; break; }
        case TYPE::ENTITY::GRAPPLE_SLOT_ID:   { m_SlotGrapple   = slot; break; }
        case TYPE::ENTITY::DROID_SLOT_ID:     { m_SlotDroid     = slot; break; }
        case TYPE::ENTITY::FREEZER_SLOT_ID:   { m_SlotFreezer   = slot; break; }
    }
        
    m_SlotTotal_vec.push_back(slot); 

    if ( (slot->GetSubTypeId() != TYPE::ENTITY::ARTEFACT_SLOT_ID) and (slot->GetSubTypeId() != TYPE::ENTITY::CARGO_SLOT_ID) )
    {
        m_SlotFunct_vec.push_back(slot);
    }
    
    if (slot->GetSubTypeId() == TYPE::ENTITY::ARTEFACT_SLOT_ID)
    {
        m_SlotArtef_vec.push_back(slot);
    }
    
    if (slot->GetSubTypeId() == TYPE::ENTITY::CARGO_SLOT_ID)
    {
        m_SlotCargo_vec.push_back(slot); 
    }
        
}

bool Vehicle::GetAllItemsFromVehicle(Vehicle* vehicle)
{
    bool result = true;
    for(unsigned int i=0; i<vehicle->m_SlotTotal_vec.size(); i++)
    { 
        if (vehicle->m_SlotTotal_vec[i]->GetItem() != nullptr)
        {
            if (vehicle->m_SlotTotal_vec[i]->GetSubTypeId() == TYPE::ENTITY::CARGO_SLOT_ID)
            {
                result = AddItemToCargoSlot(vehicle->m_SlotTotal_vec[i]->GetItem());
            }
            else
            {
                result = AddAndManageItem(vehicle->m_SlotTotal_vec[i]->GetItem());
            }
        }
    }
    
    return result;
}
                
bool Vehicle::ManageItem(BaseItem* item)
{
    switch(item->GetTypeId())
    {
        case TYPE::ENTITY::EQUIPMENT_ID:     { return ManageFunctionEquipment(item); break; }
        case TYPE::ENTITY::MODULE_ID:         { return ManageFunctionModule(item); break; }
        case TYPE::ENTITY::ARTEFACT_ID:     { return ManageFunctionArtefact(item); break; }    
        case TYPE::ENTITY::GOODS_ID:         { return ManageFunctionGoodsPack(item); break; }
    }
    
    return false;
} 
                
bool Vehicle::ManageFunctionGoodsPack(BaseItem* item)
{
    return MergeIdenticalGoods(item);
}    

bool Vehicle::ManageFunctionEquipment(BaseItem* item)
{
    if (item->GetParentSubTypeId() == TYPE::ENTITY::WEAPON_SLOT_ID)
    {
        ItemSlot* item_slot = m_ComplexWeapon.GetEmptyWeaponSlot();
        if (item_slot != nullptr)
        {
            return item_slot->SwapItem(item->GetItemSlot());
        }
        else
        {
            ItemSlot* item_slot = m_ComplexWeapon.GetEquipedWeakestWeaponSlot();
            if (item_slot != nullptr)
            {
                if (item->GetPrice() > item_slot->GetItem()->GetPrice())
                {
                    return item_slot->SwapItem(item->GetItemSlot());
                }
            }
        }
    }
    else
    {
        ItemSlot* item_slot = GetFuctionalSlot(item->GetParentSubTypeId());
        if (item_slot->GetItem() == nullptr)
        {
            return item_slot->SwapItem(item->GetItemSlot());
        }
        else
        {
            if (item->GetPrice() > item_slot->GetItem()->GetPrice())
            {
                return item_slot->SwapItem(item->GetItemSlot());
            }
        }        
    }
    
    return false;        
}     

bool Vehicle::ManageFunctionModule(BaseItem* item)
{
    for (unsigned int i=0; i<m_SlotFunct_vec.size(); i++)
    {
        if (m_SlotFunct_vec[i]->GetItem() != nullptr)
        {
            if (m_SlotFunct_vec[i]->GetItem()->GetSubTypeId() == item->GetParentSubTypeId())
            {
                return ((BaseEquipment*)m_SlotFunct_vec[i]->GetItem())->InsertModule((BaseModule*)item);                
            }
        }
    }
    
    return false;
}

bool Vehicle::ManageFunctionArtefact(BaseItem* item)
{
    ItemSlot* artef_slot = GetEmptyArtefactSlot();
    if (artef_slot != nullptr)
    {
        return artef_slot->SwapItem(item->GetItemSlot());
    }

    return false;
}

ItemSlot* const Vehicle::GetFuctionalSlot(TYPE::ENTITY functional_slot_subtype_id) const
{
    for(unsigned int i=0; i<m_SlotFunct_vec.size(); i++)
    {
        if (m_SlotFunct_vec[i]->GetSubTypeId() == functional_slot_subtype_id)
        {
            return m_SlotFunct_vec[i];
        }
    }
    
    return nullptr;
}

ItemSlot* const Vehicle::GetEmptyArtefactSlot() const
{
    for(unsigned int i=0; i<m_SlotArtef_vec.size(); i++)
    {
        if (m_SlotArtef_vec[i]->GetItem() == nullptr)
        {
            return m_SlotArtef_vec[i];
        }
    }
    
    return nullptr;
}
                    
ItemSlot* const Vehicle::GetEmptyCargoSlot()
{
    for (unsigned int i=0; i<m_SlotCargo_vec.size(); i++)
    {                  
        if (m_SlotCargo_vec[i]->GetItem() == nullptr)
        {
            return m_SlotCargo_vec[i];
        }
    }
    
    return nullptr;
}

ItemSlot* const Vehicle::GetCargoSlotWithGoods(TYPE::ENTITY requested_goods_subtype_id)
{
    for (unsigned int i=0; i<m_SlotCargo_vec.size(); i++)
    {
        if (m_SlotCargo_vec[i]->GetItem() != nullptr)
        {
            if (m_SlotCargo_vec[i]->GetItem()->GetTypeId() == TYPE::ENTITY::GOODS_ID)
            {
                if (m_SlotCargo_vec[i]->GetItem()->GetSubTypeId() == requested_goods_subtype_id)
                {
                    return m_SlotCargo_vec[i];
                }
            }
        }                     
    }
    
    return nullptr;
}

bool Vehicle::UnpackContainerItemToCargoSlot(Container* container)
{    
     if (AddItemToCargoSlot(container->GetItemSlot()->GetItem()) == true)
    {      
        container->SilentKill();
                                
        return true;
    }
    
    return false;
} 

bool Vehicle::AddItemToCargoSlot(BaseItem* item)
{
    IncreaseMass(item->GetMass());
    if (item->GetTypeId() == TYPE::ENTITY::GOODS_ID)
    {
        if (ManageFunctionGoodsPack(item) == true)
        {
            return true;
        }
    }
    
    ItemSlot* cargo_slot = GetEmptyCargoSlot();
    if (cargo_slot != nullptr)
    {
        return cargo_slot->InsertItem(item);
    }
    
    return false;
} 

bool Vehicle::AddAndManageItem(BaseItem* item)
{
    bool result = AddItemToCargoSlot(item);
                            
    if (result == true)
    {
        ManageItem(item);
    }

    return result;
}
     
void Vehicle::ManageItemsInCargo()
{
    for (unsigned int i=0; i<m_SlotCargo_vec.size(); i++)
    {
        if (m_SlotCargo_vec[i]->GetItem() != nullptr)
        {
            ManageItem(m_SlotCargo_vec[i]->GetItem());
        }
    }
}
    
void Vehicle::SellItemsInCargo()
{
    for (unsigned int i=0; i<m_SlotCargo_vec.size(); i++)
    {
        if (m_SlotCargo_vec[i]->GetItem() != nullptr)
        {
            SellItem(m_SlotCargo_vec[i]->GetItem());
        }
    }
}

bool Vehicle::SellItem(BaseItem* item)
{
    //float skill_rate = 1.0f + sign*0.1*npc->GetSkill().GetTrader();
    //npc->IncreaseCredits(sign*amount*skill_rate*minerals_price);
    int earn_money = 0;
    int item_mass = item->GetMass();
    switch(item->GetTypeId())
    {
        case TYPE::ENTITY::GOODS_ID:        
        { 
            earn_money = ((Kosmoport*)m_Land)->GetShop()->BuyGoods((GoodsPack*)item);    
            break; 
        }
        
        case TYPE::ENTITY::EQUIPMENT_ID: 
        { 
            earn_money = ((Kosmoport*)m_Land)->GetStore()->BuyItem(item);
            break; 
        }        
    }
    
    if (earn_money > 0)
    {
        DecreaseMass(item_mass);
        m_OwnerNpc->IncreaseCredits(earn_money);
        
        return true;
    }
    else
    {
        return false;
    }
}
 
bool Vehicle::BuyItem(BaseItem* item)
{
        if (AddItemToCargoSlot(item) == true)
        {
            m_OwnerNpc->IncreaseCredits(-item->GetPrice());
            
            return true; 
        }
        
        return false;
}
                
bool Vehicle::MergeIdenticalGoods(BaseItem* item)
{
    ItemSlot* item_slot = GetCargoSlotWithGoods(item->GetSubTypeId());
    if (item_slot != nullptr)
    {
        item_slot->GetGoodsPack()->Increase(item->GetMass());
        // delete item; dangerrr
        return true;
    }
    
    return false;                
} 

void Vehicle::BindOwnerNpc(Npc* owner_npc)                
{ 
    m_OwnerNpc = owner_npc; 
    m_OwnerNpc->SetVehicle(this); 
} 

bool Vehicle::IsObjectWithinRadarRange(BaseSpaceEntity* object) const
{
    float dist = meti::distance(GetCenter(), object->GetCenter());
    if (dist < m_Properties.radar)
    {
            return true;
    }
    
    return false;
}    

void Vehicle::UpdateSpecialAction()
{
    switch(m_SpecialActionId)
    {
        case VEHICLE_SPECIAL_ACTION_TYPE::NONE_ID: { break; }
        
        case VEHICLE_SPECIAL_ACTION_TYPE::INITIATE_DOCKING_ID:
        {
            // alpitodorender if (UpdateFadeInEffect() == true)
            {
                DockingEvent();
                m_SpecialActionId = VEHICLE_SPECIAL_ACTION_TYPE::NONE_ID;
            }
            
            break;            
        }
                    
        case VEHICLE_SPECIAL_ACTION_TYPE::INITIATE_LAUNCHING_ID:
        {
            // alpitodorender if (UpdateFadeOutEffect() == true)
            {
                m_SpecialActionId = VEHICLE_SPECIAL_ACTION_TYPE::NONE_ID;
            }
            
            break;
        }

        case VEHICLE_SPECIAL_ACTION_TYPE::INITIATE_JUMPIN_ID:
        {
            // alpitodorender if (UpdateFadeInEffect() == true)
            {
                HyperJumpEvent(m_ComplexDrive.GetTarget()->GetStarSystem());
            }
        
            break;
        }
        
        case VEHICLE_SPECIAL_ACTION_TYPE::INITIATE_JUMPOUT_ID:
        {
            // alpitodorender if (UpdateFadeOutEffect() == true)
            {
                m_SpecialActionId = VEHICLE_SPECIAL_ACTION_TYPE::NONE_ID;
            }
        
            break;
        }
    }
}
 
//// ******** dock/LAUNCHING ******** 
void Vehicle::HyperJumpEvent(StarSystem* starsystem)
{
    #if ENTITY_TRANSACTION_LOG_ENABLED == 1 
    Logger::Instance().Log("Vehicle("+std::to_string(GetId())+")::HyperJumpEvent", ENTITY_TRANSACTION_LOG_DIP);
    #endif   
    
    m_ComplexWeapon.DeactivateAllWeapons();
    
    m_SpecialActionId = VEHICLE_SPECIAL_ACTION_TYPE::INITIATE_JUMPOUT_ID;
    starsystem->GetHyperSpace().AddVehicle(this);
}
                
                
void Vehicle::DockingEvent()
{
    #if ENTITY_TRANSACTION_LOG_ENABLED == 1 
    Logger::Instance().Log("Vehicle("+std::to_string(GetId())+")::DockingEvent", ENTITY_TRANSACTION_LOG_DIP);
    #endif
              
    m_ComplexWeapon.DeactivateAllWeapons();
                   
    switch(m_ComplexDrive.GetTarget()->GetTypeId())                               
    {
        case TYPE::ENTITY::PLANET_ID:
        {
            Planet* planet = ((Planet*)m_ComplexDrive.GetTarget());                
            planet->GetLand()->AddVehicle(this);
                    
            break;
        }

        case TYPE::ENTITY::VEHICLE_ID:
        {     
            switch(m_ComplexDrive.GetTarget()->GetSubTypeId())
            {
                case TYPE::ENTITY::SPACESTATION_ID:
                {
                            SpaceStation* spacestation = ((SpaceStation*)m_ComplexDrive.GetTarget());
                                spacestation->GetLand()->AddVehicle(this);
                        
                    break;
                }
                
                case TYPE::ENTITY::SHIP_ID:
                {
                    //..
                    break;
                }
            }
        
            break;
        }
    }
        
    m_ComplexDrive.ResetTarget();
}

void Vehicle::LaunchingEvent()
{
    #if ENTITY_TRANSACTION_LOG_ENABLED == 1 
    Logger::Instance().Log("Vehicle("+std::to_string(GetId())+")::LaunchingEvent", ENTITY_TRANSACTION_LOG_DIP);
    #endif
    
    if (m_ParentVehicleSlot != nullptr)
    {
        switch(m_ParentVehicleSlot->GetOwner()->GetTypeId())
        {
            case TYPE::ENTITY::ANGAR_ID:
            {
                int angleInD = meti::getRandInt(0, 360);
                glm::vec2 offset_pos = meti::getRandVec2f(40, 100);
                glm::vec3 offset_pos3(offset_pos.x, offset_pos.y, DEFAULT_ENTITY_ZPOS);
                glm::vec3 angle(0,0,angleInD);
                GetStarSystem()->AddVehicle(this, ((BaseSpaceEntity*)m_Land->GetOwner())->GetCenter() + offset_pos3, angle, nullptr);
                m_Land->RemoveVehicle(this);
    
                break;
            }
                
            case TYPE::ENTITY::VEHICLE_ID:
            {
                //..
                break;
            }
        }
    }
    else
    {
        int angleInD = meti::getRandInt(0, 360);
        glm::vec2 offset_pos = meti::getRandVec2f(40, 100);
        glm::vec3 offset_pos3(offset_pos.x, offset_pos.y, DEFAULT_ENTITY_ZPOS);
        glm::vec3 angle(0,0,angleInD);
        GetStarSystem()->AddVehicle(this, ((BaseSpaceEntity*)m_Land->GetOwner())->GetCenter() + offset_pos3, angle, nullptr);
        m_Land->RemoveVehicle(this); 
    }

    SetSpecialActionId(VEHICLE_SPECIAL_ACTION_TYPE::INITIATE_LAUNCHING_ID);
    // alpitodorender SetTransparency(0.1);
}
//// 

/* virtual */
void Vehicle::TakeIntoAccountAgressor(Vehicle* agressor)
{
    m_OwnerNpc->TakeIntoAccountAgressor(agressor);
}

/* virtual */
void Vehicle::Hit(int damage, bool show_effect)
{
    #if WEAPONSTARGET_LOG_ENABLED == 1
    Logger::Instance().Log("Vehicle("+std::to_string(GetId())+")::Hit", WEAPONSTARGET_LOG_DIP);
    #endif
    
    if (m_GodMode == false)
    {
    
    if (m_Properties.energy < damage)
    {
        m_Properties.hibernate_mode_enabled = true;
        UpdatePropertiesProtection();
    }
    
    damage *= (1.0 - m_Properties.protection*0.01f);
    damage *= m_OwnerNpc->GetSkills().GetDefenceNormalized();
    
    GetDataLife().armor -= damage;
    
    if (GetDataLife().armor < 0)
    {
        GetDataLife().is_alive = false;
    }

    if (show_effect == true)
    {
        if (m_ComplexProtector.GetProtectorSlot()->GetItem() != nullptr)
        {
            m_ComplexProtector.GetShieldEffect()->SetAlpha(1.0);
        }           
               
               VerticalFlowText* text = new VerticalFlowText(std::to_string(damage), 12, meti::vec2(GetCenter()), COLOR::COLOR4I_RED_LIGHT, GetCollisionRadius());
               GetStarSystem()->Add(text); 
           }
           
    }
}

/* virtual */
void Vehicle::PostDeathUniqueEvent(bool show_effect)  
{
    int num_items = meti::getRandInt(0, 3);
    for (int i = 0; i<num_items; i++)
    {
        DropRandomItemToSpace();
    }
    
    if (show_effect == true)
    {
//        jeti::ExplosionEffect* explosion = jeti::getNewExplosionEffect(GetCollisionRadius());
//        GetStarSystem()->Add(explosion, GetCenter());
    }
}


void Vehicle::CheckNeedsInStatic()
{
        // check armor
        if (GetDataLife().armor < 0.5*m_DataKorpus.armor)    { m_Needs.repair_korpus = true; }
        else                                                { m_Needs.repair_korpus = false; }

        //check item damages
        m_Needs.repair_equipment = false;
        for (unsigned int i=0; i<m_SlotFunct_vec.size(); i++)
        {
                if (m_SlotFunct_vec[i]->GetItem() != nullptr)
                {
                        if (m_SlotFunct_vec[i]->GetItem()->GetDamaged() == true)
                        {
                                m_Needs.repair_equipment = true;                                
                        }
                }
        }
        
        //check ammo
        m_Needs.get_ammo = false;
        for (unsigned int i=0; i<m_SlotFunct_vec.size(); i++)
        {
                if (m_SlotFunct_vec[i]->GetItem() != nullptr)
                {
                        if (m_SlotFunct_vec[i]->GetItem()->GetSubTypeId() == TYPE::ENTITY::ROCKET_EQUIPMENT_ID) 
                        {
                                if (m_SlotFunct_vec[i]->GetRocketEquipment()->GetAmmo() == 0)
                                {
                                        m_Needs.get_ammo = true; 
                                }
                        }
                }
        }
        
        // check fuel
        m_Needs.get_fuel = false;
        if (m_ComplexDrive.GetBakSlot() != nullptr)
        {
                if (m_ComplexDrive.GetBakSlot()->GetItem() != nullptr)
                {
                        if (m_ComplexDrive.GetBakSlot()->GetBakEquipment()->GetFuel() < 0.8*m_ComplexDrive.GetBakSlot()->GetBakEquipment()->GetFuelMax())
                        {
                                m_Needs.get_fuel = true;
                        } 
                }   
        }
        
        // check credits
        if (m_OwnerNpc->GetCredits() < 1000)    { m_Needs.get_credits = true; }
        else                                    { m_Needs.get_credits = false; }
}


void Vehicle::ResolveNeedsInKosmoportInStatic()
{
    bool result = true;
    
    // buy repair korpus
    if ( (m_Needs.repair_korpus == true) and (result == true) )
    {
        result = ((Angar*)m_ParentVehicleSlot->GetOwner())->RepairVehicle(this);
    }        
  
    // repair equipment
    if ( (m_Needs.repair_equipment == true) and (result == true) )
    {
        for (unsigned int i=0; i<m_SlotFunct_vec.size(); i++)
        {
            if (m_SlotFunct_vec[i]->GetItem() != nullptr)
            {
                if (m_SlotFunct_vec[i]->GetItem()->GetDamaged() == true)
                {
                    result = ((Angar*)m_ParentVehicleSlot->GetOwner())->RepairItem(m_OwnerNpc, m_SlotFunct_vec[i]->GetItem());
                }
            }
        }
    }        
    
    // buy ammo
    if ( (m_Needs.get_ammo == true) and (result == true) )
    {
        for (unsigned int i=0; i<m_SlotFunct_vec.size(); i++)
        {
            if (m_SlotFunct_vec[i]->GetItem() != nullptr)
            {
                if (m_SlotFunct_vec[i]->GetItem()->GetSubTypeId() == TYPE::ENTITY::ROCKET_EQUIPMENT_ID)
                {
                    result = ((Angar*)m_ParentVehicleSlot->GetOwner())->ChargeRocketEquipment(m_OwnerNpc, m_SlotFunct_vec[i]->GetRocketEquipment());
                }
            }
        }
    }
    
    // tank up
    if ( (m_Needs.get_fuel == true) and (result == true) )
    {
        result = ((Angar*)m_ParentVehicleSlot->GetOwner())->TankUpVehicle(this);
    }
   
    //// check credits
    //if (m_OwnerNpc->GetCredits() < 1000) { m_Needs.get_credits = true; }
    //else                                { m_Needs.get_credits = false; }
}

void Vehicle::UpdateAllFunctionalItemsInStatic()
{
    for (unsigned int i=0; i<m_SlotFunct_vec.size(); i++)
    {
        if (m_SlotFunct_vec[i]->GetItem() != nullptr)
        {
            m_SlotFunct_vec[i]->GetItem()->UpdateInStatic();
        }
    }

    for (unsigned int i=0; i<m_SlotArtef_vec.size(); i++)
    {
        if (m_SlotArtef_vec[i]->GetItem() != nullptr)
        {
            m_SlotArtef_vec[i]->GetItem()->UpdateInStatic();
        }
    }
}

void Vehicle::IncreaseMass(int d_mass)
{
    #if ITEMINFLUENCE_LOG_ENABLED == 1
    Logger::Instance().Log("Vehicle("+std::to_string(GetId())+")::IncreaseMass", ITEMINFLUENCE_LOG_DIP);
    #endif
    
    ChangeMass(d_mass);
    m_Properties.free_space = m_DataKorpus.space - GetMass();
    UpdatePropertiesSpeed(); // as the mass influence speed this action is necessary here
}

void Vehicle::DecreaseMass(int d_mass)
{
    #if ITEMINFLUENCE_LOG_ENABLED == 1
    Logger::Instance().Log("Vehicle("+std::to_string(GetId())+")::DecreaseMass", ITEMINFLUENCE_LOG_DIP);
    #endif
    
    ChangeMass(-d_mass);
    m_Properties.free_space = m_DataKorpus.space - GetMass();
    UpdatePropertiesSpeed(); // as the mass influence speed this action is necessary here
}

void Vehicle::UpdatePropertiesSpeed()
{
    #if ITEMINFLUENCE_LOG_ENABLED == 1
    Logger::Instance().Log("Vehicle("+std::to_string(GetId())+")::UpdatePropertiesSpeed", ITEMINFLUENCE_LOG_DIP);
    #endif
    
    // speed calculation ////
    m_Properties.speed = 0;

    if (m_ComplexDrive.GetDriveSlot() != nullptr) 
    {
        if (m_ComplexDrive.GetDriveSlot()->GetItem() != nullptr) 
        {
            if (m_ComplexDrive.GetDriveSlot()->GetDriveEquipment()->GetFunctioning() == true)  
            {
                float actual_speed = (m_ComplexDrive.GetDriveSlot()->GetDriveEquipment()->GetSpeed() - GetMass()*MASS_DECREASE_SPEED_RATE); 
                if (actual_speed > 0)
                { 
                    if (m_Properties.artefact_gravity > 0)
                    {
                        m_Properties.speed = (1.0 + m_Properties.artefact_gravity/100.0)*actual_speed;         
                    }
                    else
                    {
                        m_Properties.speed = actual_speed; 
                    }
                    
                    if (m_ComplexDrive.GetDriveSlot()->GetSelected() == true)
                    {
                        m_Properties.speed *= EQUIPMENT::DRIVE::OVERLOAD_RATE;
                        m_ComplexDrive.GetDriveSlot()->GetItem()->UseOverloadDeterioration();
                    }
                    else
                    {
                        m_ComplexDrive.GetDriveSlot()->GetItem()->UseNormalDeterioration();
                    }
                                           
                    m_ComplexDrive.UpdatePath();
                }
            }
        }
    }
}

void Vehicle::UpdatePropertiesFire()
{
    #if ITEMINFLUENCE_LOG_ENABLED == 1
    Logger::Instance().Log("Vehicle("+std::to_string(GetId())+")::UpdatePropertiesFire", ITEMINFLUENCE_LOG_DIP);
    #endif
    
    m_ComplexWeapon.UpdateFireAbility();
         
    m_Properties.total_damage = m_ComplexWeapon.GetTotalDamage();
    m_Properties.total_radius = m_ComplexWeapon.GetTotalRadius();
}

void Vehicle::UpdatePropertiesRadar()
{
    #if ITEMINFLUENCE_LOG_ENABLED == 1
    Logger::Instance().Log("Vehicle("+std::to_string(GetId())+")::UpdatePropertiesRadar", ITEMINFLUENCE_LOG_DIP);
    #endif
    
    m_Properties.radar = VISIBLE_DISTANCE_WITHOUT_RADAR;
    m_Properties.equipment_radar = false;
    
       if (m_SlotRadar->GetItem() != nullptr) 
       {
        if (m_SlotRadar->GetRadarEquipment()->GetFunctioning() == true)  
        {
            m_Properties.radar = m_SlotRadar->GetRadarEquipment()->GetRadius();
            m_Properties.equipment_radar = true;
        }
    }
}

void Vehicle::UpdatePropertiesJump()
{
    #if ITEMINFLUENCE_LOG_ENABLED == 1
    Logger::Instance().Log("Vehicle("+std::to_string(GetId())+")::UpdatePropertiesJump", ITEMINFLUENCE_LOG_DIP);
    #endif
        
    m_Properties.hyper = 0;

    if (m_ComplexDrive.GetDriveSlot() != nullptr)
    {
        if (m_ComplexDrive.GetDriveSlot()->GetItem() != nullptr)
        {
            if (m_ComplexDrive.GetDriveSlot()->GetDriveEquipment()->GetFunctioning() == true)
            {
                if (m_ComplexDrive.GetBakSlot() != nullptr)
                {
                    if (m_ComplexDrive.GetBakSlot()->GetItem() != nullptr)
                    {
                        if (m_ComplexDrive.GetBakSlot()->GetBakEquipment()->GetFunctioning() == true)
                        {
                            if (m_ComplexDrive.GetDriveSlot()->GetDriveEquipment()->GetHyper() > m_ComplexDrive.GetBakSlot()->GetBakEquipment()->GetFuel())
                            {
                                m_Properties.hyper = m_ComplexDrive.GetDriveSlot()->GetDriveEquipment()->GetHyper();
                            }
                            else
                            {
                                m_Properties.hyper = m_ComplexDrive.GetBakSlot()->GetBakEquipment()->GetFuel();
                            }
                        }
                    } 
                }
            }
        }
    }
}

void Vehicle::UpdatePropertiesEnergy()
{
    #if ITEMINFLUENCE_LOG_ENABLED == 1
    Logger::Instance().Log("Vehicle("+std::to_string(GetId())+")::UpdatePropertiesEnergy", ITEMINFLUENCE_LOG_DIP);
    #endif
    
    m_Properties.energy = 0;
    m_Properties.hibernate_mode_enabled = true;

    if (m_SlotEnergizer->GetItem() != nullptr)
    {
        if (m_SlotEnergizer->GetEnergizerEquipment()->GetFunctioning() == true)
        {
            m_Properties.energy = m_SlotEnergizer->GetEnergizerEquipment()->GetEnergy();
            m_Properties.hibernate_mode_enabled = false;
        }
    }
    
    UpdatePropertiesProtection();
}

void Vehicle::UpdatePropertiesProtection()
{
    #if ITEMINFLUENCE_LOG_ENABLED == 1
    Logger::Instance().Log("Vehicle("+std::to_string(GetId())+")::UpdatePropertiesProtection", ITEMINFLUENCE_LOG_DIP);
    #endif
    
    m_Properties.protection = m_DataKorpus.protection;
    m_Properties.shield_effect_enabled = false;

    if (m_Properties.hibernate_mode_enabled == false)
    {
        if (m_ComplexProtector.GetProtectorSlot()->GetItem() != nullptr)
        {
            if (m_ComplexProtector.GetProtectorSlot()->GetProtectorEquipment()->GetFunctioning() == true)
            {
                m_Properties.protection += m_ComplexProtector.GetProtectorSlot()->GetProtectorEquipment()->GetProtection();
                m_Properties.shield_effect_enabled = true;
            }
        }
    }

    if (m_Properties.artefact_protection > 0)
    {
        m_Properties.protection += m_Properties.artefact_protection;
    }
}

void Vehicle::UpdatePropertiesRepair()
{
    #if ITEMINFLUENCE_LOG_ENABLED == 1
    Logger::Instance().Log("Vehicle("+std::to_string(GetId())+")::UpdatePropertiesRepair", ITEMINFLUENCE_LOG_DIP);
    #endif
    
    m_Properties.repair = 0;

    if (m_SlotDroid->GetItem() != nullptr)
    {
        if (m_SlotDroid->GetDroidEquipment()->GetFunctioning() == true)
        {
            m_Properties.repair = m_SlotDroid->GetDroidEquipment()->GetRepair();
        }
    }
}


void Vehicle::IncreaseArmor(int repair)
{
    #if ITEMINFLUENCE_LOG_ENABLED == 1
    Logger::Instance().Log("Vehicle("+std::to_string(GetId())+")::IncreaseArmor", ITEMINFLUENCE_LOG_DIP);
    #endif
    
    GetDataLife().armor += repair;
    
    if (GetDataLife().armor > m_DataKorpus.armor)
    {
        GetDataLife().armor = m_DataKorpus.armor;
    }
}

void Vehicle::UpdatePropertiesFreeze()
{
    #if ITEMINFLUENCE_LOG_ENABLED == 1
    Logger::Instance().Log("Vehicle("+std::to_string(GetId())+")::UpdatePropertiesFreeze", ITEMINFLUENCE_LOG_DIP);
    #endif
    
    m_Properties.freeze = 0;

    if (m_SlotFreezer->GetItem() != nullptr)
    {
        if (m_SlotFreezer->GetFreezerEquipment()->GetFunctioning() == true)
        {
            m_Properties.freeze = m_SlotFreezer->GetFreezerEquipment()->GetFreeze();
        }
    }
}

void Vehicle::UpdatePropertiesScan()
{
    #if ITEMINFLUENCE_LOG_ENABLED == 1
    Logger::Instance().Log("Vehicle("+std::to_string(GetId())+")::UpdatePropertiesScan", ITEMINFLUENCE_LOG_DIP);
    #endif
    
    m_Properties.scan = 0;

    if (m_SlotScaner->GetItem() != nullptr)
    {
        if (m_SlotScaner->GetScanerEquipment()->GetFunctioning() == true)
        {
            m_Properties.scan = m_SlotScaner->GetScanerEquipment()->GetScan();
        }
    }
}

void Vehicle::UpdatePropertiesGrab()
{
    #if ITEMINFLUENCE_LOG_ENABLED == 1
    Logger::Instance().Log("Vehicle("+std::to_string(GetId())+")::UpdatePropertiesGrab", ITEMINFLUENCE_LOG_DIP);
    #endif

    m_Properties.grab_strength = 0;
    m_Properties.grab_radius = 0;
                                            
    if (m_DataKorpus.slot_grapple_num != 0)
    {
        if (m_SlotGrapple->GetItem() != nullptr)
        {
            if (m_SlotGrapple->GetGrappleEquipment()->GetFunctioning() == true)
            {
                m_Properties.grab_strength = m_SlotGrapple->GetGrappleEquipment()->GetStrength();
                m_Properties.grab_radius = m_SlotGrapple->GetGrappleEquipment()->GetRadius();
            }
        }
    }
}                  
        
void Vehicle::UpdateArtefactInfluence()
{
    #if ITEMINFLUENCE_LOG_ENABLED == 1
    Logger::Instance().Log("Vehicle("+std::to_string(GetId())+")::UpdateArtefactInfluence", ITEMINFLUENCE_LOG_DIP);
    #endif
    
    m_Properties.artefact_gravity = 0;
    m_Properties.artefact_protection = 0;
    
    for (unsigned int i=0; i<m_SlotArtef_vec.size(); i++)
    {
        if (m_SlotArtef_vec[i]->GetItem() != nullptr)
        {
            if (m_SlotArtef_vec[i]->GetItem()->GetFunctioning() == true)
            {
                switch(m_SlotArtef_vec[i]->GetItem()->GetSubTypeId())
                {
                    case TYPE::ENTITY::GRAVITY_ARTEFACT_ID:
                    {
                        m_Properties.artefact_gravity += ((GravityArtefact*)m_SlotArtef_vec[i]->GetItem())->GetGravity();
                        break;
                    }
    
                    case TYPE::ENTITY::PROTECTOR_ARTEFACT_ID:
                    {
                        m_Properties.artefact_protection += ((ProtectorArtefact*)m_SlotArtef_vec[i]->GetItem())->GetProtection();
                        break;
                    }
                }                      
            }
        }
    }
    
    if (m_Properties.artefact_gravity > 0)
    {
        UpdatePropertiesSpeed();
    }
    
    if (m_Properties.artefact_protection > 0)
    {
        UpdatePropertiesProtection();
    }
}

///* virtual override final */
//void Vehicle::RenderStuffWhenFocusedInSpace(const jeti::Renderer& render)
//{
//    m_ComplexWeapon.RenderWeaponIcons();
    
//    RenderRadarRange();
//    m_ComplexWeapon.RenderWeaponsRange();
    
//    m_ComplexDrive.DrawPath(render);
//}

///* virtual override final */
//void Vehicle::RenderInfoInSpace(const jeti::Renderer& render, const glm::vec2& scroll_coords, float zoom)
//{
//    UpdateInfo(); // virtual
//    glm::vec2 pos(GetCenter().x - scroll_coords.x, GetCenter().y - scroll_coords.y);
//    pos /= zoom;
//    jeti::drawInfoIn2Column(GetInfo().title_list, GetInfo().value_list, pos);
//    if (m_OwnerNpc != nullptr)
//    {
//        glm::vec2 pos2(pos.x + 300, pos.y);
//        m_OwnerNpc->RenderInfo(pos2);
//    }
//}

//void Vehicle::RenderInfo(const glm::vec2& center, int offset_x, int offset_y)
//{
//    UpdateInfo(); // virtual
//    glm::vec2 pos(center.x - offset_x, center.y - offset_y);
//    jeti::drawInfoIn2Column(GetInfo().title_list, GetInfo().value_list, pos);

//    if (m_OwnerNpc != nullptr)
//    {
//        m_OwnerNpc->RenderInfo(glm::vec2(center.x + 190 - offset_x, center.y - offset_y));
//    }
//}

//void Vehicle::RenderGrabTrail(const jeti::Renderer& render) const
//{
//    //m_SlotGrapple->GetGrappleEquipment()->RenderGrabTrail(render);
//}
        
//void Vehicle::RenderKorpus(const jeti::Renderer& render)
//{
//    //render.DrawQuad(GetTextureOb(), GetActualModelMatrix());
//    //alpitodorender render.DrawMeshLight(GetMesh(), GetTextureOb(), GetActualModelMatrix());
//}

//void Vehicle::RenderDriveEffect(float scale, float parent_d_alpha) const
//{
//    m_ComplexDrive.GetDriveEffect()->Update();
//    //m_ComplexDrive.GetDriveEffect()->Render(scale, parent_d_alpha);
//}


//void Vehicle::RenderShieldEffect(const jeti::Renderer& renderer, float parent_d_alpha) const
//{
//    m_ComplexProtector.GetShieldEffect()->Render(renderer, parent_d_alpha);
//}

//void Vehicle::RenderRadarRange()
//{
//    if (m_Properties.radar > VISIBLE_DISTANCE_WITHOUT_RADAR)
//    {
//        m_SlotRadar->UpdateRange(GuiTextureObCollector::Instance().dot_yellow);
//        m_SlotRadar->DrawRange(meti::vec2(GetCenter()));
//    }
//}

//void Vehicle::RenderGrappleRange()
//{
//    if (m_Properties.grab_radius > 0)
//    {
//        m_SlotGrapple->UpdateRange(GuiTextureObCollector::Instance().dot_blue);
//        m_SlotGrapple->DrawRange(meti::vec2(GetCenter()));
//    }
//}

bool Vehicle::IsAbleToJumpTo(StarSystem* target_starsystem) const
{
     float dist = meti::distance(GetStarSystem()->GetCenter(), target_starsystem->GetCenter());
    if (dist < m_Properties.hyper)
    {
        return true;
    }
    
    return false;
}
        
void Vehicle::RepairKorpusOnAmount(int amount)
{
    GetDataLife().armor += amount;
    if (GetDataLife().armor > m_DataKorpus.armor)
    {
        GetDataLife().armor = m_DataKorpus.armor;
    }
}

bool Vehicle::IsArmorFull() const
{
    if (GetDataLife().armor == m_DataKorpus.armor)
    {
        return true;
    }
    
    return false;
}

int Vehicle::GetArmorMiss() const
{
    return (m_DataKorpus.armor - GetDataLife().armor);
}

bool Vehicle::IsFuelFull() const
{
    if (m_ComplexDrive.GetBakSlot()->GetItem() == nullptr)
    {
        return true;
    }
    
    if (GetFuelMiss() == 0)
    {
        return true;
    }
    
    
    return false;
}

int Vehicle::GetFuelMiss() const
{
    return m_ComplexDrive.GetBakSlot()->GetBakEquipment()->GetFuelMiss();
}

void Vehicle::LockRandomItem(int locked_turns)
{
    std::vector<ItemSlot*> _equiped_slot_vec;
    
    for (unsigned int i=0; i<m_SlotFunct_vec.size(); i++)
    {
        if (m_SlotFunct_vec[i]->GetItem() != nullptr)
        {
            _equiped_slot_vec.push_back(m_SlotFunct_vec[i]);
        }
    }
    
    if (_equiped_slot_vec.size() > 0)
    {
        unsigned int _rand = meti::getRandInt(0, _equiped_slot_vec.size());
        _equiped_slot_vec[_rand]->GetItem()->LockEvent(locked_turns);
    }    
}

bool Vehicle::TryToConsumeEnergy(int energy)
{
    #if ITEMINFLUENCE_LOG_ENABLED == 1
    Logger::Instance().Log("Vehicle("+std::to_string(GetId())+")::TryToConsumeEnergy(energy="+std::to_string(energy)+")", ITEMINFLUENCE_LOG_DIP);
    #endif
    
    if (m_Properties.energy > energy)
    {
        m_Properties.energy -= energy;
        m_SlotEnergizer->GetEnergizerEquipment()->DecreaseEnergy(energy); 
        
        return true;        
    }
    
    return false;
}

bool Vehicle::TryToGenerateEnergy(int energy)
{
    #if ITEMINFLUENCE_LOG_ENABLED == 1
    Logger::Instance().Log("Vehicle("+std::to_string(GetId())+")::TryToGenerateEnergy(energy="+std::to_string(energy)+")", ITEMINFLUENCE_LOG_DIP);
    #endif
    
    int energy_max = m_SlotEnergizer->GetEnergizerEquipment()->GetEnergyMax();
    if (m_Properties.energy < energy_max)
    {
        int diff_energy = energy_max - m_Properties.energy;
        if ( diff_energy < energy)
        {
            energy = diff_energy;
        }
        
        m_Properties.energy += energy;
        m_SlotEnergizer->GetEnergizerEquipment()->IncreaseEnergy(energy); 
        
        if (m_Properties.hibernate_mode_enabled == true)
        {
            if (m_Properties.energy > HIBERNATION_ENERGY_THRESHOLD)
            {
                UpdatePropertiesProtection();
            }
        }
        
        return true;
    }
    
    return false;
}

STATUS Vehicle::CheckGrabStatus() const
{
    STATUS status = STATUS::ITEM_OK;
    
    if (m_SlotGrapple->GetItem() != nullptr)
    {
        if (m_SlotGrapple->GetGrappleEquipment()->GetDamaged() == true)
        {  
            status = STATUS::ITEM_DAMAGED;
        }
        
        if (m_SlotGrapple->GetGrappleEquipment()->GetLocked() != 0)
        {  
            status = STATUS::ITEM_LOCKED;
        }        
    }
    else
    {
        status = STATUS::ITEMSLOT_EMPTY;
    }    

    return status;    
}
        
void Vehicle::DropRandomItemToSpace()
{
    std::vector<ItemSlot*> _equiped_slot_vec;
    
    for (unsigned int i=0; i<m_SlotTotal_vec.size(); i++)
    {
        if (m_SlotTotal_vec[i]->GetItem() != nullptr)
        {
            _equiped_slot_vec.push_back(m_SlotTotal_vec[i]);
        }
    }
    
    if (_equiped_slot_vec.size() > 0)
    {
        _equiped_slot_vec[meti::getRandInt(0, _equiped_slot_vec.size()-1)]->DropItemToSpace();
    }        
}

void Vehicle::UpdateGrappleMicroProgram_inDynamic()
{
    if (m_Properties.grab_radius > 0)
    {
        m_SlotGrapple->GetGrappleEquipment()->UpdateGrabScenarioProgram_inDynamic();
    }     
}
                
void Vehicle::SaveData(boost::property_tree::ptree& save_ptree, const std::string& root) const
{
    #if SAVELOAD_LOG_ENABLED == 1
    Logger::Instance().Log(" Vehicle("+std::to_string(GetId())+")::SaveData", SAVELOAD_LOG_DIP);
    #endif

    save_ptree.put(root+"m_DataKorpus.space", m_DataKorpus.space);           
    save_ptree.put(root+"m_DataKorpus.armor", m_DataKorpus.armor);  
    save_ptree.put(root+"m_DataKorpus.protection", m_DataKorpus.protection); 
    save_ptree.put(root+"m_DataKorpus.temperature", m_DataKorpus.temperature); 

    save_ptree.put(root+"m_DataKorpus.price", m_DataKorpus.price); 
    save_ptree.put(root+"m_DataKorpus.draw_turrels", m_DataKorpus.draw_turrels);            

    save_ptree.put(root+"m_DataKorpus.slot_grapple_num", m_DataKorpus.slot_grapple_num);  
    save_ptree.put(root+"m_DataKorpus.slot_drive_num", m_DataKorpus.slot_drive_num);
    save_ptree.put(root+"m_DataKorpus.slot_protector_num", m_DataKorpus.slot_protector_num);           
    save_ptree.put(root+"m_DataKorpus.slot_radar_num", m_DataKorpus.slot_radar_num);
    save_ptree.put(root+"m_DataKorpus.slot_scaner_num", m_DataKorpus.slot_scaner_num);
    save_ptree.put(root+"m_DataKorpus.slot_freezer_num", m_DataKorpus.slot_freezer_num);
    save_ptree.put(root+"m_DataKorpus.slot_weapon_num", m_DataKorpus.slot_weapon_num);           
           

    if (m_ComplexDrive.GetTarget() != nullptr) 
    {
        save_ptree.put(root+"data_unresolved_Vehicle.drive_complex_target_id", m_ComplexDrive.GetTarget()->GetId());
        save_ptree.put(root+"data_unresolved_Vehicle.drive_complex_action_id", m_ComplexDrive.GetActionId());
    }
    else 
    {
        save_ptree.put(root+"data_unresolved_Vehicle.drive_complex_target_id", NONE_ID);
        save_ptree.put(root+"data_unresolved_Vehicle.drive_complex_action_id", NONE_ID);
    }
               
    if (m_Land != nullptr)  { save_ptree.put(root+"data_unresolved_Vehicle.land_id", m_Land->GetId()); }
    else                     { save_ptree.put(root+"data_unresolved_Vehicle.land_id", NONE_ID); }
    
    if (m_ParentVehicleSlot != nullptr) { save_ptree.put(root+"data_unresolved_Vehicle.parent_vehicleslot_id", m_ParentVehicleSlot->GetId()); }
    else                                     { save_ptree.put(root+"data_unresolved_Vehicle.parent_vehicleslot_id", NONE_ID); }
  
    if (GetPlaceTypeId() == TYPE::PLACE::HYPER_SPACE_ID) 
    { 
        save_ptree.put(root+"data_unresolved_Vehicle.starsystem_hyper_id", m_ComplexDrive.GetTarget()->GetId()); 
    }
    else 
    { 
        save_ptree.put(root+"data_unresolved_Vehicle.starsystem_hyper_id", NONE_ID); 
    }  
}

void Vehicle::LoadData(const boost::property_tree::ptree& load_ptree)
{
    #if SAVELOAD_LOG_ENABLED == 1
    Logger::Instance().Log(" Vehicle("+std::to_string(GetId())+")::LoadData", SAVELOAD_LOG_DIP);
    #endif
    
       m_DataKorpus.space       = load_ptree.get<int>("m_DataKorpus.space");     
       m_DataKorpus.armor       = load_ptree.get<int>("m_DataKorpus.armor");   
       m_DataKorpus.protection  = load_ptree.get<int>("m_DataKorpus.protection"); 
       m_DataKorpus.temperature = load_ptree.get<int>("m_DataKorpus.temperature"); 

       m_DataKorpus.price        = load_ptree.get<int>("m_DataKorpus.price"); 
       m_DataKorpus.draw_turrels = load_ptree.get<bool>("m_DataKorpus.draw_turrels"); 

       m_DataKorpus.slot_grapple_num   = load_ptree.get<int>("m_DataKorpus.slot_grapple_num"); 
       m_DataKorpus.slot_drive_num     = load_ptree.get<int>("m_DataKorpus.slot_drive_num"); 
       m_DataKorpus.slot_protector_num = load_ptree.get<int>("m_DataKorpus.slot_protector_num"); 
       m_DataKorpus.slot_radar_num     = load_ptree.get<int>("m_DataKorpus.slot_radar_num"); 
       m_DataKorpus.slot_scaner_num    = load_ptree.get<int>("m_DataKorpus.slot_scaner_num"); 
       m_DataKorpus.slot_freezer_num   = load_ptree.get<int>("m_DataKorpus.slot_freezer_num"); 
       m_DataKorpus.slot_weapon_num    = load_ptree.get<int>("m_DataKorpus.slot_weapon_num"); 

       data_unresolved_Vehicle.drive_complex_target_id   = load_ptree.get<int>("data_unresolved_Vehicle.drive_complex_target_id"); 
       data_unresolved_Vehicle.drive_complex_action_id   = load_ptree.get<int>("data_unresolved_Vehicle.drive_complex_action_id");        
       //data_unresolved_Vehicle.textureOb_gui_path = load_ptree.get<std::string>("data_unresolved_Vehicle.textureOb_gui_path"); 
       data_unresolved_Vehicle.parent_vehicleslot_id = load_ptree.get<int>("data_unresolved_Vehicle.parent_vehicleslot_id"); 
       data_unresolved_Vehicle.land_id = load_ptree.get<int>("data_unresolved_Vehicle.land_id");
       data_unresolved_Vehicle.starsystem_hyper_id = load_ptree.get<int>("data_unresolved_Vehicle.starsystem_hyper_id"); 
       
}

void Vehicle::ResolveData()
{
    #if SAVELOAD_LOG_ENABLED == 1
    Logger::Instance().Log(" Vehicle("+std::to_string(GetId())+")::ResolveData", SAVELOAD_LOG_DIP);
    #endif
    
    CreateDriveComplexTextureDependedStuff();
    CreateProtectionComplexTextureDependedStuff();

    if (data_unresolved_Vehicle.drive_complex_target_id != NONE_ID) 
    { 
        m_ComplexDrive.SetTarget((BaseSpaceEntity*)EntityManager::Instance().GetEntityById(data_unresolved_Vehicle.drive_complex_target_id),  data_unresolved_Vehicle.drive_complex_action_id); 
    }        
             
    if (data_unresolved_Vehicle.land_id != NONE_ID) 
    { 
        SetLand( (BaseLand*)EntityManager::Instance().GetEntityById(data_unresolved_Vehicle.land_id) ); 
    }              

    switch(GetPlaceTypeId())
    {
        case TYPE::PLACE::SPACE_ID: 
        {
            GetStarSystem()->AddVehicle(this, data_unresolved_Orientation.center, data_unresolved_Orientation.direction, GetParent()); 
            break;
        }
        
        case TYPE::PLACE::KOSMOPORT_ID:
        {    
            ((VehicleSlot*)EntityManager::Instance().GetEntityById(data_unresolved_Vehicle.parent_vehicleslot_id ))->InsertVehicle(this); 
            break;
        }
        
        case TYPE::PLACE::HYPER_SPACE_ID:
        {
            //std::cout<<"xxx="<<data_unresolved_Vehicle.starsystem_hyper_id<<std::endl;
            ((StarSystem*)EntityManager::Instance().GetEntityById(data_unresolved_Vehicle.starsystem_hyper_id))->GetHyperSpace().AddVehicle(this);
            //std::cout<<"yyy="<<data_unresolved_Vehicle.starsystem_hyper_id<<std::endl;
            
            break;
        }
        
        case TYPE::PLACE::NATURELAND_ID:
        {
            ((NatureLand*)EntityManager::Instance().GetEntityById(data_unresolved_Vehicle.land_id))->AddVehicle(this); 
            break;
        }
    }
    
    m_ComplexWeapon.PrepareWeapons();
}
                
void Vehicle::TEST_DamageAndLockRandItems()
{
    int rand_index1 = meti::getRandInt(0, m_SlotFunct_vec.size()-1);
    while (m_SlotFunct_vec[rand_index1]->GetItem() == nullptr)
    {
        rand_index1 = meti::getRandInt(0, m_SlotFunct_vec.size()-1);
    }
    m_SlotFunct_vec[rand_index1]->GetItem()->LockEvent(3);

    int rand_index2 = meti::getRandInt(0, m_SlotFunct_vec.size()-1);
    while (m_SlotFunct_vec[rand_index2]->GetItem() == nullptr)
    {
        rand_index2 = meti::getRandInt(0, m_SlotFunct_vec.size()-1);
    }
    
    while (m_SlotFunct_vec[rand_index2]->GetItem()->GetCondition() > 0)
    {
        m_SlotFunct_vec[rand_index2]->GetItem()->DeteriorationEvent();
    }
}

void Vehicle::TEST_DropRandomItemToSpace()
{
    DropRandomItemToSpace();    
}






std::string getVehicleSpecialActionStr(VEHICLE_SPECIAL_ACTION_TYPE type_id)
{
    switch(type_id)
    {
        case VEHICLE_SPECIAL_ACTION_TYPE::INITIATE_DOCKING_ID:     { return "INITIATE_DOCKING_ID"; break; }
        case VEHICLE_SPECIAL_ACTION_TYPE::INITIATE_LAUNCHING_ID:    { return "INITIATE_LAUNCHING_ID"; break; }
        case VEHICLE_SPECIAL_ACTION_TYPE::INITIATE_JUMPIN_ID:        { return "INITIATE_JUMPIN_ID"; break; }
        case VEHICLE_SPECIAL_ACTION_TYPE::INITIATE_JUMPOUT_ID:        { return "INITIATE_JUMPOUT_ID"; break; }
        case VEHICLE_SPECIAL_ACTION_TYPE::NONE_ID:                    { return "NONE_ID"; break; }
                        
        default: { return "UKNOWN ID"; break; }        
    }
}
