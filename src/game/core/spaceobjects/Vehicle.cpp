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
#include <common/Global.hpp>
#include <managers/EntityManager.hpp>

#include <ceti/Logger.hpp>

//#include <jeti/Render.hpp>

//#include <resources/GuiTextureObCollector.hpp>

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

//#include <effects/Shield.hpp>
//#include <jeti/particlesystem/DriveEffect.hpp>
//#include <jeti/particlesystem/ExplosionEffect.hpp>
//#include <text/VerticalFlowText.hpp>

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
      m_npc(nullptr),
      m_ParentVehicleSlot(nullptr),
      m_Land(nullptr),
      m_SlotRadar(nullptr),
      m_SlotScaner(nullptr),
      m_SlotEnergizer(nullptr),
      m_SlotGrapple(nullptr),
      m_SlotDroid(nullptr),
      m_SlotFreezer(nullptr),
      m_ComplexWeapon(this)
{
    m_ComplexDrive.SetOwnerVehicle(this);
    m_ComplexProtector.SetOwnerVehicle(this);
}

/* virtual */
Vehicle::~Vehicle()
{
    LOG("___::~Vehicle("+std::to_string(id())+")");
} 

/* virtual override */
void Vehicle::putChildrenToGarbage() const
{
    m_npc->SetAlive(false);
    global::get().entityManager().addToGarbage(m_npc);
    
    for(unsigned int i=0; i<m_SlotTotal_vec.size(); i++)
    {
        global::get().entityManager().addToGarbage(m_SlotTotal_vec[i]);
    }
}

void Vehicle::CreateDriveComplexTextureDependedStuff()
{
    points().addMidLeftPoint();
    points().addMidFarLeftPoint();

    //DriveEffect* drive_effect = GetNewDriveEffect(textureOb().GetData().size_id, points().GetpMidLeft(), points().GetpMidFarLeft());
    //m_ComplexDrive.SetDriveEffect(drive_effect);
}    

void Vehicle::CreateProtectionComplexTextureDependedStuff()
{
    //    m_ComplexProtector.GetShieldEffect()->setParent(this);
}

void Vehicle::SetKorpusData(const VehicleDescriptor& data_korpus)
{ 
    m_VehicleDescriptor = data_korpus;
    m_properties.protection = m_VehicleDescriptor.protection;
}

GoodsPack* Vehicle::GetGoodsPack() const
{
    for(unsigned int i=0; i<m_SlotCargo_vec.size(); i++)
    {
        if (m_SlotCargo_vec[i]->item() != nullptr)
        {
            if (m_SlotCargo_vec[i]->item()->typeId() == TYPE::ENTITY::GOODS_ID)
            {
                return m_SlotCargo_vec[i]->goodsPack();
            }
        }
    }
    
    return nullptr;
}

/* virtual override final */
int Vehicle::givenExpirience() const
{
    return m_npc->GetSkills().GetExpirience() * GIVEN_EXPIRIENCE_RATE_DEPENDING_ON_NPC_EXPIRIENCE;
}

bool Vehicle::CheckItemSlotPresenceBySubTypeId(TYPE::ENTITY slot_subtype_id) const
{
    for (unsigned int i=0; i<m_SlotTotal_vec.size(); i++)
    {
        if (m_SlotTotal_vec[i]->subTypeId() == slot_subtype_id)
        {
            return true;
        }
    }
    
    return false;
}

void Vehicle::AddItemSlot(ItemSlot* slot) 
{ 
    slot->SetOwner(this);

    switch(slot->subTypeId())
    {
        case TYPE::ENTITY::WEAPON_SLOT_ID:
        {
            float border_start = 0.2;
            float border_end   = 0.8;
            
            float pos_x = meti::getRandFloat(border_start, border_end) - 0.5;
            float pos_y = meti::getRandFloat(border_start, border_end) - 0.5;

            slot->turrel()->setParentCenter(pos_x, pos_y, DEFAULT_ENTITY_ZPOS);
            points().Add(slot->turrel()->pCenter(), slot->turrel()->pParentCenter());
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

    if ( (slot->subTypeId() != TYPE::ENTITY::ARTEFACT_SLOT_ID) and (slot->subTypeId() != TYPE::ENTITY::CARGO_SLOT_ID) )
    {
        m_SlotFunct_vec.push_back(slot);
    }
    
    if (slot->subTypeId() == TYPE::ENTITY::ARTEFACT_SLOT_ID)
    {
        m_SlotArtef_vec.push_back(slot);
    }
    
    if (slot->subTypeId() == TYPE::ENTITY::CARGO_SLOT_ID)
    {
        m_SlotCargo_vec.push_back(slot);
    }

}

bool Vehicle::GetAllItemsFromVehicle(Vehicle* vehicle)
{
    bool result = true;
    for(unsigned int i=0; i<vehicle->m_SlotTotal_vec.size(); i++) {
        if (vehicle->m_SlotTotal_vec[i]->item() != nullptr) {
            if (vehicle->m_SlotTotal_vec[i]->subTypeId() == TYPE::ENTITY::CARGO_SLOT_ID) {
                result = AddItemToCargoSlot(vehicle->m_SlotTotal_vec[i]->item());
            } else {
                result = AddAndManageItem(vehicle->m_SlotTotal_vec[i]->item());
            }
        }
    }
    
    return result;
}

bool Vehicle::ManageItem(BaseItem* item)
{
    switch(item->typeId())
    {
        case TYPE::ENTITY::EQUIPMENT_ID:    { return ManageFunctionEquipment(item); break; }
        case TYPE::ENTITY::MODULE_ID:       { return ManageFunctionModule(item); break; }
        case TYPE::ENTITY::ARTEFACT_ID:     { return ManageFunctionArtefact(item); break; }
        case TYPE::ENTITY::GOODS_ID:        { return ManageFunctionGoodsPack(item); break; }
    }
    
    return false;
} 

bool Vehicle::ManageFunctionGoodsPack(BaseItem* item)
{
    return MergeIdenticalGoods(item);
}    

bool Vehicle::ManageFunctionEquipment(BaseItem* item)
{
    if (item->parentSubTypeId() == TYPE::ENTITY::WEAPON_SLOT_ID)
    {
        ItemSlot* item_slot = m_ComplexWeapon.GetEmptyWeaponSlot();
        if (item_slot != nullptr)
        {
            return item_slot->swapItem(item->itemSlot());
        }
        else
        {
            ItemSlot* item_slot = m_ComplexWeapon.GetEquipedWeakestWeaponSlot();
            if (item_slot != nullptr)
            {
                if (item->price() > item_slot->item()->price())
                {
                    return item_slot->swapItem(item->itemSlot());
                }
            }
        }
    }
    else
    {
        ItemSlot* item_slot = GetFuctionalSlot(item->parentSubTypeId());
        if (item_slot->item() == nullptr)
        {
            return item_slot->swapItem(item->itemSlot());
        }
        else
        {
            if (item->price() > item_slot->item()->price())
            {
                return item_slot->swapItem(item->itemSlot());
            }
        }
    }
    
    return false;
}     

bool Vehicle::ManageFunctionModule(BaseItem* item)
{
    for (unsigned int i=0; i<m_SlotFunct_vec.size(); i++) {
        if (m_SlotFunct_vec[i]->item()) {
            if (m_SlotFunct_vec[i]->item()->subTypeId() == item->parentSubTypeId()) {
                return ((BaseEquipment*)m_SlotFunct_vec[i]->item())->InsertModule((BaseModule*)item);
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
        return artef_slot->swapItem(item->itemSlot());
    }

    return false;
}

ItemSlot* const Vehicle::GetFuctionalSlot(TYPE::ENTITY functional_slot_subtype_id) const
{
    for(unsigned int i=0; i<m_SlotFunct_vec.size(); i++)
    {
        if (m_SlotFunct_vec[i]->subTypeId() == functional_slot_subtype_id)
        {
            return m_SlotFunct_vec[i];
        }
    }
    
    return nullptr;
}

ItemSlot* const Vehicle::GetEmptyArtefactSlot() const
{
    for(unsigned int i=0; i<m_SlotArtef_vec.size(); i++) {
        if (!m_SlotArtef_vec[i]->item()) {
            return m_SlotArtef_vec[i];
        }
    }    
    return nullptr;
}

ItemSlot* const Vehicle::GetEmptyCargoSlot()
{
    for (unsigned int i=0; i<m_SlotCargo_vec.size(); i++) {
        if (!m_SlotCargo_vec[i]->item()) {
            return m_SlotCargo_vec[i];
        }
    }
    
    return nullptr;
}

ItemSlot* const Vehicle::GetCargoSlotWithGoods(TYPE::ENTITY requested_goods_subtype_id)
{
    for (unsigned int i=0; i<m_SlotCargo_vec.size(); i++) {
        if (m_SlotCargo_vec[i]->item()) {
            if (m_SlotCargo_vec[i]->item()->typeId() == TYPE::ENTITY::GOODS_ID) {
                if (m_SlotCargo_vec[i]->item()->subTypeId() == requested_goods_subtype_id) {
                    return m_SlotCargo_vec[i];
                }
            }
        }
    }    
    return nullptr;
}

bool Vehicle::UnpackContainerItemToCargoSlot(Container* container)
{    
    if (AddItemToCargoSlot(container->itemSlot()->item()) == true)
    {
        container->killSilently();

        return true;
    }
    
    return false;
} 

bool Vehicle::AddItemToCargoSlot(BaseItem* item)
{
    IncreaseMass(item->mass());
    if (item->typeId() == TYPE::ENTITY::GOODS_ID)
    {
        if (ManageFunctionGoodsPack(item) == true)
        {
            return true;
        }
    }
    
    ItemSlot* cargo_slot = GetEmptyCargoSlot();
    if (cargo_slot != nullptr)
    {
        return cargo_slot->insertItem(item);
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
    for (unsigned int i=0; i<m_SlotCargo_vec.size(); i++) {
        if (m_SlotCargo_vec[i]->item()) {
            ManageItem(m_SlotCargo_vec[i]->item());
        }
    }
}

void Vehicle::SellItemsInCargo()
{
    for (unsigned int i=0; i<m_SlotCargo_vec.size(); i++) {
        if (m_SlotCargo_vec[i]->item()) {
            SellItem(m_SlotCargo_vec[i]->item());
        }
    }
}

bool Vehicle::SellItem(BaseItem* item)
{
    //float skill_rate = 1.0f + sign*0.1*npc->GetSkill().GetTrader();
    //npc->IncreaseCredits(sign*amount*skill_rate*minerals_price);
    int earn_money = 0;
    int item_mass = item->mass();
    switch(item->typeId())
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
        m_npc->IncreaseCredits(earn_money);
        
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
        m_npc->IncreaseCredits(-item->price());

        return true;
    }

    return false;
}

bool Vehicle::MergeIdenticalGoods(BaseItem* item)
{
    ItemSlot* item_slot = GetCargoSlotWithGoods(item->subTypeId());
    if (item_slot != nullptr)
    {
        item_slot->goodsPack()->Increase(item->mass());
        // delete item; dangerrr
        return true;
    }
    
    return false;
} 

void Vehicle::BindOwnerNpc(Npc* owner_npc)                
{ 
    m_npc = owner_npc;
    m_npc->SetVehicle(this);
} 

bool Vehicle::IsObjectWithinRadarRange(SpaceObject* object) const
{
    float dist = meti::distance(center(), object->center());
    if (dist < m_properties.radar)
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
                HyperJumpEvent(m_ComplexDrive.GetTarget()->starsystem());
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
    //LOG("Vehicle("+std::to_string(id())+")::HyperJumpEvent");
    
    m_ComplexWeapon.DeactivateAllWeapons();
    
    m_SpecialActionId = VEHICLE_SPECIAL_ACTION_TYPE::INITIATE_JUMPOUT_ID;
    starsystem->hyperSpace().AddVehicle(this);
}


void Vehicle::DockingEvent()
{
    //LOG("Vehicle("+std::to_string(id())+")::DockingEvent");

    m_ComplexWeapon.DeactivateAllWeapons();

    switch(m_ComplexDrive.GetTarget()->typeId())
    {
        case TYPE::ENTITY::PLANET_ID:
        {
            Planet* planet = ((Planet*)m_ComplexDrive.GetTarget());
            planet->GetLand()->AddVehicle(this);

            break;
        }

        case TYPE::ENTITY::VEHICLE_ID:
        {
            switch(m_ComplexDrive.GetTarget()->subTypeId())
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
    //LOG("Vehicle("+std::to_string(id())+")::LaunchingEvent");
    
    if (m_ParentVehicleSlot != nullptr)
    {
        switch(m_ParentVehicleSlot->GetOwner()->typeId())
        {
            case TYPE::ENTITY::ANGAR_ID:
            {
                int angleInD = meti::getRandInt(0, 360);
                glm::vec2 offset_pos = meti::getRandVec2f(40, 100);
                glm::vec3 offset_pos3(offset_pos.x, offset_pos.y, DEFAULT_ENTITY_ZPOS);
                glm::vec3 angle(0,0,angleInD);
                starsystem()->add(this, ((SpaceObject*)m_Land->GetOwner())->center() + offset_pos3, angle, nullptr);
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
        starsystem()->add(this, ((SpaceObject*)m_Land->GetOwner())->center() + offset_pos3, angle, nullptr);
        m_Land->RemoveVehicle(this);
    }

    SetSpecialActionId(VEHICLE_SPECIAL_ACTION_TYPE::INITIATE_LAUNCHING_ID);
    // alpitodorender SetTransparency(0.1);
}
//// 

/* virtual */
void Vehicle::remeberAgressor(Vehicle* agressor)
{
    m_npc->remeberAgressor(agressor);
}

/* virtual */
void Vehicle::hit(int damage)
{
    //LOG("Vehicle("+std::to_string(id())+")::Hit");
    if (!m_GodMode) {
        if (m_properties.energy < damage) {
            m_properties.hibernate_mode_enabled = true;
            UpdatePropertiesProtection();
        }

        // adjust real damage value
        damage *= (1.0 - m_properties.protection*0.01f);
        if (m_npc) {
            damage *= m_npc->GetSkills().GetDefenceNormalized();
        }

        SpaceObject::hit(damage);

        //if (show_effect == true)
        {
            //if (m_ComplexProtector.GetProtectorSlot()->item() != nullptr)
            {
                //m_ComplexProtector.GetShieldEffect()->SetAlpha(1.0);
            }

            //VerticalFlowText* text = new VerticalFlowText(std::to_string(damage), 12, meti::vec2(center()), COLOR::COLOR4I_RED_LIGHT, collisionRadius());
            //starsystem()->Add(text);
        }

    }
}

/* virtual */
void Vehicle::postDeathUniqueEvent(bool show_effect)  
{
    int num_items = meti::getRandInt(0, 3);
    for (int i = 0; i<num_items; i++)
    {
        DropRandomItemToSpace();
    }
    
    if (show_effect == true)
    {
        //        jeti::ExplosionEffect* explosion = jeti::getNewExplosionEffect(collisionRadius());
        //        starsystem()->Add(explosion, center());
    }
}


void Vehicle::CheckNeedsInStatic()
{
    // check armor
    if (dataLife().armor < 0.5*m_VehicleDescriptor.armor)    { m_Needs.repair_korpus = true; }
    else                                                { m_Needs.repair_korpus = false; }

    //check item damages
    m_Needs.repair_equipment = false;
    for (unsigned int i=0; i<m_SlotFunct_vec.size(); i++) {
        if (m_SlotFunct_vec[i]->item()) {
            if (m_SlotFunct_vec[i]->item()->isDamaged()) {
                m_Needs.repair_equipment = true;
            }
        }
    }

    //check ammo
    m_Needs.get_ammo = false;
    for (unsigned int i=0; i<m_SlotFunct_vec.size(); i++) {
        if (m_SlotFunct_vec[i]->item()) {
            if (m_SlotFunct_vec[i]->item()->subTypeId() == TYPE::ENTITY::ROCKET_EQUIPMENT_ID) {
                if (m_SlotFunct_vec[i]->rocketEquipment()->GetAmmo() == 0) {
                    m_Needs.get_ammo = true;
                }
            }
        }
    }

    // check fuel
    m_Needs.get_fuel = false;
    if (m_ComplexDrive.GetBakSlot() != nullptr)
    {
        if (m_ComplexDrive.GetBakSlot()->item() != nullptr)
        {
            if (m_ComplexDrive.GetBakSlot()->bakEquipment()->GetFuel() < 0.8*m_ComplexDrive.GetBakSlot()->bakEquipment()->GetFuelMax())
            {
                m_Needs.get_fuel = true;
            }
        }
    }

    // check credits
    if (m_npc->GetCredits() < 1000)    { m_Needs.get_credits = true; }
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
    if ( (m_Needs.repair_equipment == true) && (result == true) ) {
        for (unsigned int i=0; i<m_SlotFunct_vec.size(); i++) {
            if (m_SlotFunct_vec[i]->item()) {
                if (m_SlotFunct_vec[i]->item()->isDamaged() == true) {
                    result = ((Angar*)m_ParentVehicleSlot->GetOwner())->RepairItem(m_npc, m_SlotFunct_vec[i]->item());
                }
            }
        }
    }
    
    // buy ammo
    if ( (m_Needs.get_ammo == true) && (result == true) ) {
        for (unsigned int i=0; i<m_SlotFunct_vec.size(); i++) {
            if (m_SlotFunct_vec[i]->item()) {
                if (m_SlotFunct_vec[i]->item()->subTypeId() == TYPE::ENTITY::ROCKET_EQUIPMENT_ID) {
                    result = ((Angar*)m_ParentVehicleSlot->GetOwner())->ChargeRocketEquipment(m_npc, m_SlotFunct_vec[i]->rocketEquipment());
                }
            }
        }
    }
    
    // tank up
    if ( (m_Needs.get_fuel == true) and (result == true) ) {
        result = ((Angar*)m_ParentVehicleSlot->GetOwner())->TankUpVehicle(this);
    }

    //// check credits
    //if (m_OwnerNpc->GetCredits() < 1000) { m_Needs.get_credits = true; }
    //else                                { m_Needs.get_credits = false; }
}

void Vehicle::UpdateAllFunctionalItemsInStatic()
{
    for (unsigned int i=0; i<m_SlotFunct_vec.size(); i++) {
        if (m_SlotFunct_vec[i]->item()) {
            m_SlotFunct_vec[i]->item()->updateInStatic();
        }
    }

    for (unsigned int i=0; i<m_SlotArtef_vec.size(); i++) {
        if (m_SlotArtef_vec[i]->item()) {
            m_SlotArtef_vec[i]->item()->updateInStatic();
        }
    }
}

void Vehicle::IncreaseMass(int d_mass)
{
    //LOG("Vehicle("+std::to_string(id())+")::IncreaseMass");
    
    addMass(d_mass);
    m_properties.free_space = m_VehicleDescriptor.space - mass();
    UpdatePropertiesSpeed(); // as the mass influence speed this action is necessary here
}

void Vehicle::DecreaseMass(int d_mass)
{
    //LOG("Vehicle("+std::to_string(id())+")::DecreaseMass");
    
    addMass(-d_mass);
    m_properties.free_space = m_VehicleDescriptor.space - mass();
    UpdatePropertiesSpeed(); // as the mass influence speed this action is necessary here
}

void Vehicle::UpdatePropertiesSpeed()
{
    //LOG("Vehicle("+std::to_string(id())+")::UpdatePropertiesSpeed");
    
    // speed calculation ////
    m_properties.speed = 0;

    if (m_ComplexDrive.GetDriveSlot() != nullptr)
    {
        if (m_ComplexDrive.GetDriveSlot()->item() != nullptr)
        {
            if (m_ComplexDrive.GetDriveSlot()->driveEquipment()->isFunctioning() == true)
            {
                float actual_speed = (m_ComplexDrive.GetDriveSlot()->driveEquipment()->GetSpeed() - mass()*MASS_DECREASE_SPEED_RATE);
                if (actual_speed > 0)
                {
                    if (m_properties.artefact_gravity > 0)
                    {
                        m_properties.speed = (1.0 + m_properties.artefact_gravity/100.0)*actual_speed;
                    }
                    else
                    {
                        m_properties.speed = actual_speed;
                    }
                    
                    if (m_ComplexDrive.GetDriveSlot()->GetSelected() == true)
                    {
                        m_properties.speed *= EQUIPMENT::DRIVE::OVERLOAD_RATE;
                        m_ComplexDrive.GetDriveSlot()->item()->useOverloadDeterioration();
                    }
                    else
                    {
                        m_ComplexDrive.GetDriveSlot()->item()->useNormalDeterioration();
                    }

                    m_ComplexDrive.UpdatePath();
                }
            }
        }
    }
}

void Vehicle::UpdatePropertiesFire()
{
    //LOG("Vehicle("+std::to_string(id())+")::UpdatePropertiesFire");
    
    m_ComplexWeapon.UpdateFireAbility();

    m_properties.total_damage = m_ComplexWeapon.GetTotalDamage();
    m_properties.total_radius = m_ComplexWeapon.GetTotalRadius();
}

void Vehicle::UpdatePropertiesRadar()
{
    //LOG("Vehicle("+std::to_string(id())+")::UpdatePropertiesRadar");
    
    m_properties.radar = VISIBLE_DISTANCE_WITHOUT_RADAR;
    m_properties.equipment_radar = false;
    
    if (m_SlotRadar->item() != nullptr)
    {
        if (m_SlotRadar->radarEquipment()->isFunctioning() == true)
        {
            m_properties.radar = m_SlotRadar->radarEquipment()->GetRadius();
            m_properties.equipment_radar = true;
        }
    }
}

void Vehicle::UpdatePropertiesJump()
{
    //LOG("Vehicle("+std::to_string(id())+")::UpdatePropertiesJump");

    m_properties.hyper = 0;

    if (m_ComplexDrive.GetDriveSlot() != nullptr)
    {
        if (m_ComplexDrive.GetDriveSlot()->item() != nullptr)
        {
            if (m_ComplexDrive.GetDriveSlot()->driveEquipment()->isFunctioning() == true)
            {
                if (m_ComplexDrive.GetBakSlot() != nullptr)
                {
                    if (m_ComplexDrive.GetBakSlot()->item() != nullptr)
                    {
                        if (m_ComplexDrive.GetBakSlot()->bakEquipment()->isFunctioning() == true)
                        {
                            if (m_ComplexDrive.GetDriveSlot()->driveEquipment()->GetHyper() > m_ComplexDrive.GetBakSlot()->bakEquipment()->GetFuel())
                            {
                                m_properties.hyper = m_ComplexDrive.GetDriveSlot()->driveEquipment()->GetHyper();
                            }
                            else
                            {
                                m_properties.hyper = m_ComplexDrive.GetBakSlot()->bakEquipment()->GetFuel();
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
    //LOG("Vehicle("+std::to_string(id())+")::UpdatePropertiesEnergy");
    
    m_properties.energy = 0;
    m_properties.hibernate_mode_enabled = true;

    if (m_SlotEnergizer->item() != nullptr)
    {
        if (m_SlotEnergizer->energizerEquipment()->isFunctioning() == true)
        {
            m_properties.energy = m_SlotEnergizer->energizerEquipment()->GetEnergy();
            m_properties.hibernate_mode_enabled = false;
        }
    }
    
    UpdatePropertiesProtection();
}

void Vehicle::UpdatePropertiesProtection()
{
    //LOG("Vehicle("+std::to_string(id())+")::UpdatePropertiesProtection");
    
    m_properties.protection = m_VehicleDescriptor.protection;
    m_properties.shield_effect_enabled = false;

    if (m_properties.hibernate_mode_enabled == false)
    {
        if (m_ComplexProtector.GetProtectorSlot()->item() != nullptr)
        {
            if (m_ComplexProtector.GetProtectorSlot()->protectorEquipment()->isFunctioning() == true)
            {
                m_properties.protection += m_ComplexProtector.GetProtectorSlot()->protectorEquipment()->GetProtection();
                m_properties.shield_effect_enabled = true;
            }
        }
    }

    if (m_properties.artefact_protection > 0)
    {
        m_properties.protection += m_properties.artefact_protection;
    }
}

void Vehicle::UpdatePropertiesRepair()
{
    //LOG("Vehicle("+std::to_string(id())+")::UpdatePropertiesRepair");
    
    m_properties.repair = 0;

    if (m_SlotDroid->item() != nullptr)
    {
        if (m_SlotDroid->droidEquipment()->isFunctioning() == true)
        {
            m_properties.repair = m_SlotDroid->droidEquipment()->GetRepair();
        }
    }
}


void Vehicle::IncreaseArmor(int repair)
{
    //LOG("Vehicle("+std::to_string(id())+")::IncreaseArmor");
    
    dataLife().armor += repair;
    
    if (dataLife().armor > m_VehicleDescriptor.armor)
    {
        dataLife().armor = m_VehicleDescriptor.armor;
    }
}

void Vehicle::UpdatePropertiesFreeze()
{
    //LOG("Vehicle("+std::to_string(id())+")::UpdatePropertiesFreeze");
    
    m_properties.freeze = 0;

    if (m_SlotFreezer->item() != nullptr)
    {
        if (m_SlotFreezer->freezerEquipment()->isFunctioning() == true)
        {
            m_properties.freeze = m_SlotFreezer->freezerEquipment()->GetFreeze();
        }
    }
}

void Vehicle::UpdatePropertiesScan()
{
    //LOG("Vehicle("+std::to_string(id())+")::UpdatePropertiesScan");
    
    m_properties.scan = 0;

    if (m_SlotScaner->item() != nullptr)
    {
        if (m_SlotScaner->scanerEquipment()->isFunctioning() == true)
        {
            m_properties.scan = m_SlotScaner->scanerEquipment()->GetScan();
        }
    }
}

void Vehicle::UpdatePropertiesGrab()
{
    //LOG("Vehicle("+std::to_string(id())+")::UpdatePropertiesGrab");

    m_properties.grab_strength = 0;
    m_properties.grab_radius = 0;

    if (m_VehicleDescriptor.slot_grapple_num != 0)
    {
        if (m_SlotGrapple->item() != nullptr)
        {
            if (m_SlotGrapple->grappleEquipment()->isFunctioning() == true)
            {
                m_properties.grab_strength = m_SlotGrapple->grappleEquipment()->GetStrength();
                m_properties.grab_radius = m_SlotGrapple->grappleEquipment()->GetRadius();
            }
        }
    }
}                  

void Vehicle::UpdateArtefactInfluence()
{
    //LOG("Vehicle("+std::to_string(id())+")::UpdateArtefactInfluence");
    
    m_properties.artefact_gravity = 0;
    m_properties.artefact_protection = 0;
    
    for (unsigned int i=0; i<m_SlotArtef_vec.size(); i++)
    {
        if (m_SlotArtef_vec[i]->item() != nullptr)
        {
            if (m_SlotArtef_vec[i]->item()->isFunctioning() == true)
            {
                switch(m_SlotArtef_vec[i]->item()->subTypeId())
                {
                    case TYPE::ENTITY::GRAVITY_ARTEFACT_ID:
                    {
                        m_properties.artefact_gravity += ((GravityArtefact*)m_SlotArtef_vec[i]->item())->GetGravity();
                        break;
                    }

                    case TYPE::ENTITY::PROTECTOR_ARTEFACT_ID:
                    {
                        m_properties.artefact_protection += ((ProtectorArtefact*)m_SlotArtef_vec[i]->item())->GetProtection();
                        break;
                    }
                }
            }
        }
    }
    
    if (m_properties.artefact_gravity > 0)
    {
        UpdatePropertiesSpeed();
    }
    
    if (m_properties.artefact_protection > 0)
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
//    glm::vec2 pos(center().x - scroll_coords.x, center().y - scroll_coords.y);
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
//    //render.DrawQuad(textureOb(), actualModelMatrix());
//    //alpitodorender render.DrawMeshLight(mesh(), textureOb(), actualModelMatrix());
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
//        m_SlotRadar->DrawRange(meti::vec2(center()));
//    }
//}

//void Vehicle::RenderGrappleRange()
//{
//    if (m_Properties.grab_radius > 0)
//    {
//        m_SlotGrapple->UpdateRange(GuiTextureObCollector::Instance().dot_blue);
//        m_SlotGrapple->DrawRange(meti::vec2(center()));
//    }
//}

bool Vehicle::IsAbleToJumpTo(StarSystem* target_starsystem) const
{
    float dist = meti::distance(starsystem()->center(), target_starsystem->center());
    if (dist < m_properties.hyper)
    {
        return true;
    }
    
    return false;
}

void Vehicle::RepairKorpusOnAmount(int amount)
{
    dataLife().armor += amount;
    if (dataLife().armor > m_VehicleDescriptor.armor)
    {
        dataLife().armor = m_VehicleDescriptor.armor;
    }
}

bool Vehicle::IsArmorFull() const
{
    if (dataLife().armor == m_VehicleDescriptor.armor)
    {
        return true;
    }
    
    return false;
}

int Vehicle::GetArmorMiss() const
{
    return (m_VehicleDescriptor.armor - dataLife().armor);
}

bool Vehicle::IsFuelFull() const
{
    if (m_ComplexDrive.GetBakSlot()->item() == nullptr)
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
    return m_ComplexDrive.GetBakSlot()->bakEquipment()->GetFuelMiss();
}

void Vehicle::LockRandomItem(int locked_turns)
{
    std::vector<ItemSlot*> _equiped_slot_vec;
    
    for (unsigned int i=0; i<m_SlotFunct_vec.size(); i++)
    {
        if (m_SlotFunct_vec[i]->item() != nullptr)
        {
            _equiped_slot_vec.push_back(m_SlotFunct_vec[i]);
        }
    }
    
    if (_equiped_slot_vec.size() > 0)
    {
        unsigned int _rand = meti::getRandInt(0, _equiped_slot_vec.size());
        _equiped_slot_vec[_rand]->item()->lockEvent(locked_turns);
    }
}

bool Vehicle::TryToConsumeEnergy(int energy)
{
    //LOG("Vehicle("+std::to_string(id())+")::TryToConsumeEnergy(energy="+std::to_string(energy)+")");
    
    if (m_properties.energy > energy)
    {
        m_properties.energy -= energy;
        m_SlotEnergizer->energizerEquipment()->DecreaseEnergy(energy);
        
        return true;
    }
    
    return false;
}

bool Vehicle::TryToGenerateEnergy(int energy)
{
    //LOG("Vehicle("+std::to_string(id())+")::TryToGenerateEnergy(energy="+std::to_string(energy)+")");
    
    int energy_max = m_SlotEnergizer->energizerEquipment()->GetEnergyMax();
    if (m_properties.energy < energy_max)
    {
        int diff_energy = energy_max - m_properties.energy;
        if ( diff_energy < energy)
        {
            energy = diff_energy;
        }
        
        m_properties.energy += energy;
        m_SlotEnergizer->energizerEquipment()->IncreaseEnergy(energy);
        
        if (m_properties.hibernate_mode_enabled == true)
        {
            if (m_properties.energy > HIBERNATION_ENERGY_THRESHOLD)
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
    
    if (m_SlotGrapple->item() != nullptr)
    {
        if (m_SlotGrapple->grappleEquipment()->isDamaged() == true)
        {
            status = STATUS::ITEM_DAMAGED;
        }
        
        if (m_SlotGrapple->grappleEquipment()->isLocked() != 0)
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
        if (m_SlotTotal_vec[i]->item() != nullptr)
        {
            _equiped_slot_vec.push_back(m_SlotTotal_vec[i]);
        }
    }
    
    if (_equiped_slot_vec.size() > 0)
    {
        _equiped_slot_vec[meti::getRandInt(0, _equiped_slot_vec.size()-1)]->dropItemToSpace();
    }
}

void Vehicle::UpdateGrappleMicroProgram_inDynamic()
{
    if (m_properties.grab_radius > 0)
    {
        m_SlotGrapple->grappleEquipment()->UpdateGrabScenarioProgram_inDynamic();
    }
}

void Vehicle::SaveData(boost::property_tree::ptree& save_ptree, const std::string& root) const
{
    //LOG(" Vehicle("+std::to_string(id())+")::SaveData");

    save_ptree.put(root+"m_DataKorpus.space", m_VehicleDescriptor.space);
    save_ptree.put(root+"m_DataKorpus.armor", m_VehicleDescriptor.armor);
    save_ptree.put(root+"m_DataKorpus.protection", m_VehicleDescriptor.protection);
    save_ptree.put(root+"m_DataKorpus.temperature", m_VehicleDescriptor.temperature);

    save_ptree.put(root+"m_DataKorpus.price", m_VehicleDescriptor.price);
    save_ptree.put(root+"m_DataKorpus.draw_turrels", m_VehicleDescriptor.draw_turrels);

    save_ptree.put(root+"m_DataKorpus.slot_grapple_num", m_VehicleDescriptor.slot_grapple_num);
    save_ptree.put(root+"m_DataKorpus.slot_drive_num", m_VehicleDescriptor.slot_drive_num);
    save_ptree.put(root+"m_DataKorpus.slot_protector_num", m_VehicleDescriptor.slot_protector_num);
    save_ptree.put(root+"m_DataKorpus.slot_radar_num", m_VehicleDescriptor.slot_radar_num);
    save_ptree.put(root+"m_DataKorpus.slot_scaner_num", m_VehicleDescriptor.slot_scaner_num);
    save_ptree.put(root+"m_DataKorpus.slot_freezer_num", m_VehicleDescriptor.slot_freezer_num);
    save_ptree.put(root+"m_DataKorpus.slot_weapon_num", m_VehicleDescriptor.slot_weapon_num);


    if (m_ComplexDrive.GetTarget() != nullptr)
    {
        save_ptree.put(root+"data_unresolved_Vehicle.drive_complex_target_id", m_ComplexDrive.GetTarget()->id());
        save_ptree.put(root+"data_unresolved_Vehicle.drive_complex_action_id", m_ComplexDrive.GetActionId());
    }
    else
    {
        save_ptree.put(root+"data_unresolved_Vehicle.drive_complex_target_id", NONE_ID);
        save_ptree.put(root+"data_unresolved_Vehicle.drive_complex_action_id", NONE_ID);
    }

    if (m_Land != nullptr)  { save_ptree.put(root+"data_unresolved_Vehicle.land_id", m_Land->id()); }
    else                     { save_ptree.put(root+"data_unresolved_Vehicle.land_id", NONE_ID); }
    
    if (m_ParentVehicleSlot != nullptr) { save_ptree.put(root+"data_unresolved_Vehicle.parent_vehicleslot_id", m_ParentVehicleSlot->id()); }
    else                                     { save_ptree.put(root+"data_unresolved_Vehicle.parent_vehicleslot_id", NONE_ID); }

    if (placeTypeId() == TYPE::PLACE::HYPER_SPACE_ID)
    {
        save_ptree.put(root+"data_unresolved_Vehicle.starsystem_hyper_id", m_ComplexDrive.GetTarget()->id());
    }
    else
    {
        save_ptree.put(root+"data_unresolved_Vehicle.starsystem_hyper_id", NONE_ID);
    }
}

void Vehicle::LoadData(const boost::property_tree::ptree& load_ptree)
{
    //LOG(" Vehicle("+std::to_string(id())+")::LoadData");
    
    m_VehicleDescriptor.space       = load_ptree.get<int>("m_DataKorpus.space");
    m_VehicleDescriptor.armor       = load_ptree.get<int>("m_DataKorpus.armor");
    m_VehicleDescriptor.protection  = load_ptree.get<int>("m_DataKorpus.protection");
    m_VehicleDescriptor.temperature = load_ptree.get<int>("m_DataKorpus.temperature");

    m_VehicleDescriptor.price        = load_ptree.get<int>("m_DataKorpus.price");
    m_VehicleDescriptor.draw_turrels = load_ptree.get<bool>("m_DataKorpus.draw_turrels");

    m_VehicleDescriptor.slot_grapple_num   = load_ptree.get<int>("m_DataKorpus.slot_grapple_num");
    m_VehicleDescriptor.slot_drive_num     = load_ptree.get<int>("m_DataKorpus.slot_drive_num");
    m_VehicleDescriptor.slot_protector_num = load_ptree.get<int>("m_DataKorpus.slot_protector_num");
    m_VehicleDescriptor.slot_radar_num     = load_ptree.get<int>("m_DataKorpus.slot_radar_num");
    m_VehicleDescriptor.slot_scaner_num    = load_ptree.get<int>("m_DataKorpus.slot_scaner_num");
    m_VehicleDescriptor.slot_freezer_num   = load_ptree.get<int>("m_DataKorpus.slot_freezer_num");
    m_VehicleDescriptor.slot_weapon_num    = load_ptree.get<int>("m_DataKorpus.slot_weapon_num");

    data_unresolved_Vehicle.drive_complex_target_id   = load_ptree.get<int>("data_unresolved_Vehicle.drive_complex_target_id");
    data_unresolved_Vehicle.drive_complex_action_id   = load_ptree.get<int>("data_unresolved_Vehicle.drive_complex_action_id");
    //data_unresolved_Vehicle.textureOb_gui_path = load_ptree.get<std::string>("data_unresolved_Vehicle.textureOb_gui_path");
    data_unresolved_Vehicle.parent_vehicleslot_id = load_ptree.get<int>("data_unresolved_Vehicle.parent_vehicleslot_id");
    data_unresolved_Vehicle.land_id = load_ptree.get<int>("data_unresolved_Vehicle.land_id");
    data_unresolved_Vehicle.starsystem_hyper_id = load_ptree.get<int>("data_unresolved_Vehicle.starsystem_hyper_id");

}

void Vehicle::ResolveData()
{
    //LOG(" Vehicle("+std::to_string(id())+")::ResolveData");
    
    CreateDriveComplexTextureDependedStuff();
    CreateProtectionComplexTextureDependedStuff();

    if (data_unresolved_Vehicle.drive_complex_target_id != NONE_ID)
    {
        m_ComplexDrive.SetTarget((SpaceObject*)global::get().entityManager().entity(data_unresolved_Vehicle.drive_complex_target_id),  data_unresolved_Vehicle.drive_complex_action_id);
    }

    if (data_unresolved_Vehicle.land_id != NONE_ID)
    {
        SetLand( (Land*)global::get().entityManager().entity(data_unresolved_Vehicle.land_id) );
    }

    switch(placeTypeId())
    {
        case TYPE::PLACE::SPACE_ID:
        {
            starsystem()->add(this, data_unresolved_Orientation.center, data_unresolved_Orientation.direction, parent());
            break;
        }

        case TYPE::PLACE::KOSMOPORT_ID:
        {
            ((VehicleSlot*)global::get().entityManager().entity(data_unresolved_Vehicle.parent_vehicleslot_id ))->InsertVehicle(this);
            break;
        }

        case TYPE::PLACE::HYPER_SPACE_ID:
        {
            //std::cout<<"xxx="<<data_unresolved_Vehicle.starsystem_hyper_id<<std::endl;
            ((StarSystem*)global::get().entityManager().entity(data_unresolved_Vehicle.starsystem_hyper_id))->hyperSpace().AddVehicle(this);
            //std::cout<<"yyy="<<data_unresolved_Vehicle.starsystem_hyper_id<<std::endl;
            
            break;
        }

        case TYPE::PLACE::NATURELAND_ID:
        {
            ((NatureLand*)global::get().entityManager().entity(data_unresolved_Vehicle.land_id))->AddVehicle(this);
            break;
        }
    }
    
    m_ComplexWeapon.PrepareWeapons();
}

void Vehicle::TEST_DamageAndLockRandItems()
{
    int rand_index1 = meti::getRandInt(0, m_SlotFunct_vec.size()-1);
    while (m_SlotFunct_vec[rand_index1]->item() == nullptr)
    {
        rand_index1 = meti::getRandInt(0, m_SlotFunct_vec.size()-1);
    }
    m_SlotFunct_vec[rand_index1]->item()->lockEvent(3);

    int rand_index2 = meti::getRandInt(0, m_SlotFunct_vec.size()-1);
    while (m_SlotFunct_vec[rand_index2]->item() == nullptr)
    {
        rand_index2 = meti::getRandInt(0, m_SlotFunct_vec.size()-1);
    }
    
    while (m_SlotFunct_vec[rand_index2]->item()->condition() > 0)
    {
        m_SlotFunct_vec[rand_index2]->item()->deteriorationEvent();
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
