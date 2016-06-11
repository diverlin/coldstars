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

#include <builder/spaceobjects/ContainerBuilder.hpp>

#include <world/starsystem.hpp>
#include <common/Global.hpp>
#include <managers/EntityManager.hpp>

#include <ceti/Logger.hpp>

//#include <jeti/Render.hpp>

//#include <resources/GuiTextureObCollector.hpp>

#include <slots/VehicleSlot.hpp> 
#include <slots/ItemSlot.hpp>

#include <item/equipment/Rocket.hpp>
#ifdef USE_EXTRA_EQUIPMENT
#include <item/equipment/EnergizerEquipment.hpp>
#include <item/equipment/FreezerEquipment.hpp>
#endif
#include <item/equipment/Radar.hpp>
#include <item/equipment/Bak.hpp>
#include <item/equipment/Protector.hpp>
#include <item/equipment/Droid.hpp>
#include <item/equipment/Drive.hpp>
#include <item/equipment/Scaner.hpp>
#include <item/equipment/Grapple.hpp>
#include <item/others/GoodsPack.hpp>
#ifdef USE_ARTEFACTS
#include <items/artefacts/GravityArtefact.hpp>
#include <items/artefacts/ProtectorArtefact.hpp>
#endif

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
      m_godMode(false),
      m_specialActionId(VEHICLE_SPECIAL_ACTION_TYPE::NONE_ID),
      m_npc(nullptr),
      m_parentVehicleSlot(nullptr),
      m_Land(nullptr),
      m_radarSlot(nullptr),
      m_scanerSlot(nullptr),
      #ifdef USE_EXTRA_EQUIPMENT
      m_energizerSlot(nullptr),
      m_freezerSlot(nullptr),
      #endif // USE_EXTRA_EQUIPMENT
      m_grappleSlot(nullptr),
      m_droidSlot(nullptr),
      m_weaponComplex(this)
{
    m_driveComplex.SetOwnerVehicle(this);
    m_protectorComplex.SetOwnerVehicle(this);
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
    
    for(unsigned int i=0; i<m_slots.size(); i++)
    {
        global::get().entityManager().addToGarbage(m_slots[i]);
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

void Vehicle::setKorpusData(const VehicleDescriptor& korpus_data)
{ 
    m_vehicleDescriptor = korpus_data;
    m_properties.protection = m_vehicleDescriptor.protection;
}

GoodsPack* Vehicle::goodsPack() const
{
    for(ItemSlot* slot: m_cargoSlots) {
        if (slot->item()) {
            if (slot->item()->type() == type::entity::GOODS_ID) {
                return slot->goodsPack();
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

bool Vehicle::isSlotExists(type::entity slot_subtype_id) const
{
    for (ItemSlot* slot: m_slots) {
        if (slot->subtype() == slot_subtype_id) {
            return true;
        }
    }
    return false;
}

void Vehicle::addItemSlot(ItemSlot* slot) 
{ 
    slot->setOwner(this);

    switch(slot->subtype())
    {
    case type::entity::WEAPON_SLOT_ID:
    {
        float border_start = 0.2;
        float border_end   = 0.8;

        float pos_x = meti::getRandFloat(border_start, border_end) - 0.5;
        float pos_y = meti::getRandFloat(border_start, border_end) - 0.5;

        slot->turrel()->setParentPosition(pos_x, pos_y, DEFAULT_ENTITY_ZPOS);
        points().Add(slot->turrel()->pPosition(), slot->turrel()->pParentPosition());
        m_weaponComplex.addSlot(slot);

        break;
    }
    case type::entity::DRIVE_SLOT_ID:     { m_driveComplex.SetDriveSlot(slot); break; }
    case type::entity::BAK_SLOT_ID:       { m_driveComplex.SetBakSlot(slot); break; }
    case type::entity::PROTECTOR_SLOT_ID: { m_protectorComplex.SetProtectorSlot(slot); break; }
    case type::entity::RADAR_SLOT_ID:     { m_radarSlot  = slot; break; }
    case type::entity::SCANER_SLOT_ID:    { m_scanerSlot = slot; break; }
#ifdef USE_EXTRA_EQUIPMENT
    case TYPE::ENTITY::ENERGIZER_SLOT_ID: { m_energizerSlot = slot; break; }
    case TYPE::ENTITY::FREEZER_SLOT_ID:   { m_freezerSlot   = slot; break; }
#endif // USE_EXTRA_EQUIPMENT
    case type::entity::GRAPPLE_SLOT_ID:   { m_grappleSlot   = slot; break; }
    case type::entity::DROID_SLOT_ID:     { m_droidSlot     = slot; break; }
    }

    m_slots.push_back(slot);

    if ( (slot->subtype() != type::entity::ARTEFACT_SLOT_ID) and (slot->subtype() != type::entity::CARGO_SLOT_ID) ) {
        m_equipmentSlots.push_back(slot);
    }
    
    if (slot->subtype() == type::entity::ARTEFACT_SLOT_ID) {
        m_artefactSlots.push_back(slot);
    }
    
    if (slot->subtype() == type::entity::CARGO_SLOT_ID) {
        m_cargoSlots.push_back(slot);
    }
}

bool Vehicle::grabItemsFromVehicle(Vehicle* vehicle)
{
    bool result = true;
    for(ItemSlot* slot: vehicle->m_slots) {
        if (slot->item()) {
            if (slot->subtype() == type::entity::CARGO_SLOT_ID) {
                result = addItemToCargoSlot(slot->item());
            } else {
                result = install(slot->item());
            }
        }
    }    
    return result;
}

bool Vehicle::_manageItem(item::Base* item)
{
    switch(item->type())
    {
    case type::entity::EQUIPMENT_ID:    { return _manageFunctionEquipment(item); break; }
#ifdef USE_MODULES
    case TYPE::ENTITY::MODULE_ID:       { return ManageFunctionModule(item); break; }
#endif
#ifdef USE_ARTEFACTS
    case TYPE::ENTITY::ARTEFACT_ID:     { return ManageFunctionArtefact(item); break; }
#endif
    case type::entity::GOODS_ID:        { return _manageFunctionGoodsPack(item); break; }
    }
    
    return false;
} 

bool Vehicle::_manageFunctionGoodsPack(item::Base* item)
{
    return __mergeIdenticalGoods(item);
}    

bool Vehicle::_manageFunctionEquipment(item::Base* item)
{
    if (item->parentSubTypeId() == type::entity::WEAPON_SLOT_ID)
    {
        ItemSlot* item_slot = m_weaponComplex.freeSlot();
        if (item_slot != nullptr) {
            return item_slot->swapItem(item->itemSlot());
        } else {
            ItemSlot* item_slot = m_weaponComplex.equipedWeakestSlot();
            if (item_slot != nullptr) {
                if (item->price() > item_slot->item()->price()) {
                    return item_slot->swapItem(item->itemSlot());
                }
            }
        }
    } else {
        ItemSlot* item_slot = _fuctionalSlot(item->parentSubTypeId());
        if (item_slot->item() == nullptr) {
            return item_slot->swapItem(item->itemSlot());
        } else {
            if (item->price() > item_slot->item()->price()) {
                return item_slot->swapItem(item->itemSlot());
            }
        }
    }
    
    return false;
}     

#ifdef USE_MODULES
bool Vehicle::ManageFunctionModule(item::BaseItem* item)
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
#endif

#ifdef EANBLE_ARTEFACTS
bool Vehicle::ManageFunctionArtefact(item::BaseItem* item)
{
    ItemSlot* artef_slot = GetEmptyArtefactSlot();
    if (artef_slot != nullptr)
    {
        return artef_slot->swapItem(item->itemSlot());
    }

    return false;
}
#endif

ItemSlot* const Vehicle::_fuctionalSlot(type::entity functional_slot_subtype_id) const
{
    for(ItemSlot* slot: m_equipmentSlots) {
        if (slot->subtype() == functional_slot_subtype_id) {
            return slot;
        }
    }    
    return nullptr;
}

ItemSlot* const Vehicle::_freeArtefactSlot() const
{
    for(ItemSlot* slot: m_artefactSlots) {
        if (!slot->item()) {
            return slot;
        }
    }
    return nullptr;
}

ItemSlot* const Vehicle::freeCargoSlot()
{
    for (ItemSlot* slot: m_cargoSlots) {
        if (!slot->item()) {
            return slot;
        }
    }    
    return nullptr;
}

ItemSlot* const Vehicle::_cargoSlotWithGoods(type::entity requested_goods_subtype_id)
{
    for (ItemSlot* slot: m_cargoSlots) {
        if (slot->item()) {
            if (slot->item()->type() == type::entity::GOODS_ID) {
                if (slot->item()->subtype() == requested_goods_subtype_id) {
                    return slot;
                }
            }
        }
    }
    return nullptr;
}

bool Vehicle::unpackContainerItemToCargoSlot(Container* container)
{    
    if (addItemToCargoSlot(container->itemSlot()->item()) == true)
    {
        container->killSilently();

        return true;
    }
    
    return false;
} 

bool Vehicle::addItemToCargoSlot(item::Base* item)
{
    _increaseMass(item->mass());
    if (item->type() == type::entity::GOODS_ID)
    {
        if (_manageFunctionGoodsPack(item) == true)
        {
            return true;
        }
    }
    
    ItemSlot* cargo_slot = freeCargoSlot();
    if (cargo_slot != nullptr)
    {
        return cargo_slot->insertItem(item);
    }
    
    return false;
} 

bool Vehicle::install(item::Base* item)
{
    if (addItemToCargoSlot(item)) {
        _manageItem(item);
        return true;
    }
    return false;
}

void Vehicle::manageItemsInCargo()
{
    for (unsigned int i=0; i<m_cargoSlots.size(); i++) {
        if (m_cargoSlots[i]->item()) {
            _manageItem(m_cargoSlots[i]->item());
        }
    }
}

void Vehicle::sellItemsInCargo()
{
    for (unsigned int i=0; i<m_cargoSlots.size(); i++) {
        if (m_cargoSlots[i]->item()) {
            sellItem(m_cargoSlots[i]->item());
        }
    }
}

bool Vehicle::sellItem(item::Base* item)
{
    //float skill_rate = 1.0f + sign*0.1*npc->GetSkill().GetTrader();
    //npc->IncreaseCredits(sign*amount*skill_rate*minerals_price);
    int earn_money = 0;
    int item_mass = item->mass();
    switch(item->type())
    {
    case type::entity::GOODS_ID:
    {
        earn_money = ((Kosmoport*)m_Land)->GetShop()->BuyGoods((GoodsPack*)item);
        break;
    }

    case type::entity::EQUIPMENT_ID:
    {
        earn_money = ((Kosmoport*)m_Land)->GetStore()->buyItem(item);
        break;
    }
    }
    
    if (earn_money > 0)
    {
        _decreaseMass(item_mass);
        m_npc->IncreaseCredits(earn_money);
        
        return true;
    }
    else
    {
        return false;
    }
}

bool Vehicle::buyItem(item::Base* item)
{
    if (addItemToCargoSlot(item) == true)
    {
        m_npc->IncreaseCredits(-item->price());

        return true;
    }

    return false;
}

bool Vehicle::__mergeIdenticalGoods(item::Base* item)
{
    ItemSlot* item_slot = _cargoSlotWithGoods(item->subtype());
    if (item_slot != nullptr)
    {
        item_slot->goodsPack()->Increase(item->mass());
        // delete item; dangerrr
        return true;
    }
    
    return false;
} 

void Vehicle::bindNpc(Npc* owner_npc)
{ 
    m_npc = owner_npc;
    m_npc->SetVehicle(this);
} 

bool Vehicle::isObjectVisible(SpaceObject* object) const
{
    float dist = meti::distance(position(), object->position());
    if (dist < m_properties.radar)
    {
        return true;
    }
    
    return false;
}    

void Vehicle::UpdateSpecialAction()
{
    switch(m_specialActionId)
    {
    case VEHICLE_SPECIAL_ACTION_TYPE::NONE_ID: { break; }

    case VEHICLE_SPECIAL_ACTION_TYPE::INITIATE_DOCKING_ID:
    {
        // alpitodorender if (UpdateFadeInEffect() == true)
        {
            DockingEvent();
            m_specialActionId = VEHICLE_SPECIAL_ACTION_TYPE::NONE_ID;
        }

        break;
    }

    case VEHICLE_SPECIAL_ACTION_TYPE::INITIATE_LAUNCHING_ID:
    {
        // alpitodorender if (UpdateFadeOutEffect() == true)
        {
            m_specialActionId = VEHICLE_SPECIAL_ACTION_TYPE::NONE_ID;
        }

        break;
    }

    case VEHICLE_SPECIAL_ACTION_TYPE::INITIATE_JUMPIN_ID:
    {
        // alpitodorender if (UpdateFadeInEffect() == true)
        {
            HyperJumpEvent(m_driveComplex.GetTarget()->starsystem());
        }

        break;
    }

    case VEHICLE_SPECIAL_ACTION_TYPE::INITIATE_JUMPOUT_ID:
    {
        // alpitodorender if (UpdateFadeOutEffect() == true)
        {
            m_specialActionId = VEHICLE_SPECIAL_ACTION_TYPE::NONE_ID;
        }

        break;
    }
    }
}

//// ******** dock/LAUNCHING ******** 
void Vehicle::HyperJumpEvent(Starsystem* starsystem)
{
    //LOG("Vehicle("+std::to_string(id())+")::HyperJumpEvent");
    
    m_weaponComplex.deactivateWeapons();
    
    m_specialActionId = VEHICLE_SPECIAL_ACTION_TYPE::INITIATE_JUMPOUT_ID;
    starsystem->hyperSpace().AddVehicle(this);
}


void Vehicle::DockingEvent()
{
    //LOG("Vehicle("+std::to_string(id())+")::DockingEvent");

    m_weaponComplex.deactivateWeapons();

    switch(m_driveComplex.GetTarget()->type())
    {
    case type::entity::PLANET_ID:
    {
        Planet* planet = ((Planet*)m_driveComplex.GetTarget());
        planet->GetLand()->AddVehicle(this);

        break;
    }

    case type::entity::VEHICLE_ID:
    {
        switch(m_driveComplex.GetTarget()->subtype())
        {
        case type::entity::SPACESTATION_ID:
        {
            SpaceStation* spacestation = ((SpaceStation*)m_driveComplex.GetTarget());
            spacestation->land()->AddVehicle(this);

            break;
        }

        case type::entity::SHIP_ID:
        {
            //..
            break;
        }
        }

        break;
    }
    }

    m_driveComplex.ResetTarget();
}

void Vehicle::LaunchingEvent()
{
    //LOG("Vehicle("+std::to_string(id())+")::LaunchingEvent");
    
   /* if (m_parentVehicleSlot != nullptr)
    {
        switch(m_parentVehicleSlot->owner()->typeId())
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
    // alpitodorender SetTransparency(0.1);*/
}

/* virtual */
void Vehicle::remeberAgressor(Vehicle* agressor)
{
    m_npc->remeberAgressor(agressor);
}


float Vehicle::dissipateRate() const
{
    float rate = m_properties.protection*0.01f;
    //    if (m_npc) {
    //        rate *= m_npc->GetSkills().GetDefenceNormalized();
    //    }
    return rate;
}

int Vehicle::criticalDamage() const {
    return armor() * (1.0 + dissipateRate()) + 2;
}

/* virtual */
void Vehicle::hit(int damage)
{
    LOG(std::string("Vehicle::hit id=") << std::to_string(id()) << " damage=" << std::to_string(damage));
    if (!m_godMode) {
        if (m_properties.energy < damage) {
            m_properties.hibernate_mode_enabled = true;
            _updatePropProtection();
        }

        SpaceObject::hit(damage * (1.0 - dissipateRate()));

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
void Vehicle::_postDeathUniqueEvent(bool show_effect)  
{
    int num_items = meti::getRandInt(0, 3);
    for (int i = 0; i<num_items; i++)
    {
        //__dropRandomItemToSpace();
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
    if (_dataLife().armor < 0.5*m_vehicleDescriptor.armor)    { m_needs.repair_korpus = true; }
    else                                                { m_needs.repair_korpus = false; }

    //check item damages
    m_needs.repair_equipment = false;
    for (ItemSlot* slot: m_equipmentSlots) {
        if (slot->item()) {
            if (slot->item()->isDamaged()) {
                m_needs.repair_equipment = true;
            }
        }
    }

    //check ammo
    m_needs.get_ammo = false;
    for (ItemSlot* slot: m_equipmentSlots) {
        if (slot->item()) {
            if (slot->item()->subtype() == type::entity::ROCKET_EQUIPMENT_ID) {
                if (slot->rocketEquipment()->GetAmmo() == 0) {
                    m_needs.get_ammo = true;
                }
            }
        }
    }

    // check fuel
    m_needs.get_fuel = false;
    if (m_driveComplex.bakSlot()) {
        if (m_driveComplex.bakSlot()->item()) {
            if (m_driveComplex.bakSlot()->bakEquipment()->fuel() < 0.8*m_driveComplex.bakSlot()->bakEquipment()->fuelMax()) {
                m_needs.get_fuel = true;
            }
        }
    }

    // check credits
    if (m_npc->GetCredits() < 1000)    { m_needs.get_credits = true; }
    else                                    { m_needs.get_credits = false; }
}


void Vehicle::ResolveNeedsInKosmoportInStatic()
{
    bool result = true;
    
    // buy repair korpus
    if ( (m_needs.repair_korpus == true) and (result == true) )
    {
        result = ((Angar*)m_parentVehicleSlot->owner())->RepairVehicle(this);
    }

    // repair equipment
    if ( (m_needs.repair_equipment == true) && (result == true) ) {
        for (unsigned int i=0; i<m_equipmentSlots.size(); i++) {
            if (m_equipmentSlots[i]->item()) {
                if (m_equipmentSlots[i]->item()->isDamaged() == true) {
                    result = ((Angar*)m_parentVehicleSlot->owner())->RepairItem(m_npc, m_equipmentSlots[i]->item());
                }
            }
        }
    }
    
    // buy ammo
    if ( (m_needs.get_ammo == true) && (result == true) ) {
        for (ItemSlot* slot: m_equipmentSlots) {
            if (slot->item()) {
                if (slot->item()->subtype() == type::entity::ROCKET_EQUIPMENT_ID) {
                    result = ((Angar*)m_parentVehicleSlot->owner())->chargeRocketEquipment(m_npc, slot->rocketEquipment());
                }
            }
        }
    }
    
    // tank up
    if ( (m_needs.get_fuel == true) and (result == true) ) {
        result = ((Angar*)m_parentVehicleSlot->owner())->TankUpVehicle(this);
    }

    //// check credits
    //if (m_OwnerNpc->GetCredits() < 1000) { m_Needs.get_credits = true; }
    //else                                { m_Needs.get_credits = false; }
}

void Vehicle::UpdateAllFunctionalItemsInStatic()
{
    for (unsigned int i=0; i<m_equipmentSlots.size(); i++) {
        if (m_equipmentSlots[i]->item()) {
            m_equipmentSlots[i]->item()->updateInStatic();
        }
    }

    for (unsigned int i=0; i<m_artefactSlots.size(); i++) {
        if (m_artefactSlots[i]->item()) {
            m_artefactSlots[i]->item()->updateInStatic();
        }
    }
}

void Vehicle::_increaseMass(int d_mass)
{
    //LOG("Vehicle("+std::to_string(id())+")::IncreaseMass");
    
    _addMass(d_mass);
    m_properties.free_space = m_vehicleDescriptor.space - mass();
    _updatePropSpeed(); // as the mass influence speed this action is necessary here
}

void Vehicle::_decreaseMass(int d_mass)
{
    //LOG("Vehicle("+std::to_string(id())+")::DecreaseMass");
    
    _addMass(-d_mass);
    m_properties.free_space = m_vehicleDescriptor.space - mass();
    _updatePropSpeed(); // as the mass influence speed this action is necessary here
}

void Vehicle::_updatePropSpeed()
{
    //LOG("Vehicle("+std::to_string(id())+")::UpdatePropertiesSpeed");
    m_properties.speed = 0;
    if (!m_driveComplex.driveSlot())
        return;
    if (!m_driveComplex.driveSlot()->item())
        return;
    if (!m_driveComplex.driveSlot()->driveEquipment()->isFunctioning())
        return;

    float actual_speed = (m_driveComplex.driveSlot()->driveEquipment()->speed() - mass()*MASS_DECREASE_SPEED_RATE);
    if (actual_speed > 0) {
        if (m_properties.artefact_gravity > 0) {
            m_properties.speed = (1.0 + m_properties.artefact_gravity/100.0)*actual_speed;
        } else {
            m_properties.speed = actual_speed;
        }

        if (m_driveComplex.driveSlot()->isSelected() == true) {
            m_properties.speed *= EQUIPMENT::DRIVE::OVERLOAD_RATE;
            m_driveComplex.driveSlot()->item()->useOverloadDeterioration();
        } else {
            m_driveComplex.driveSlot()->item()->useNormalDeterioration();
        }
        m_driveComplex.UpdatePath();
    }
}

void Vehicle::_updatePropFire()
{
    //LOG("Vehicle("+std::to_string(id())+")::UpdatePropertiesFire");
    
    m_weaponComplex.updateFireAbility();

    m_properties.total_damage = m_weaponComplex.damage();
}

void Vehicle::_updatePropRadar()
{
    //LOG("Vehicle("+std::to_string(id())+")::UpdatePropertiesRadar");
    
    m_properties.radar = VISIBLE_DISTANCE_WITHOUT_RADAR;
    m_properties.equipment_radar = false;
    
    if (!m_radarSlot->item())
        return;

    if (!m_radarSlot->radarEquipment()->isFunctioning())
        return;

    m_properties.radar = m_radarSlot->radarEquipment()->radius();
    m_properties.equipment_radar = true;
}

void Vehicle::_updatePropJump()
{
    //LOG("Vehicle("+std::to_string(id())+")::UpdatePropertiesJump");

    m_properties.hyper = 0;

    if (!m_driveComplex.driveSlot())
        return;
    if (!m_driveComplex.driveSlot()->item())
        return;
    if (!m_driveComplex.driveSlot()->driveEquipment()->isFunctioning())
        return;
    if (!m_driveComplex.bakSlot())
        return;
    if (!m_driveComplex.bakSlot()->item())
        return;
    if (!m_driveComplex.bakSlot()->bakEquipment()->isFunctioning())
        return;

    m_properties.hyper = std::min(m_driveComplex.driveSlot()->driveEquipment()->hyper(), m_driveComplex.bakSlot()->bakEquipment()->fuel());
}

void Vehicle::_updatePropProtection()
{
    //LOG("Vehicle("+std::to_string(id())+")::UpdatePropertiesProtection");
    
    m_properties.protection = m_vehicleDescriptor.protection;
    m_properties.shield_effect_enabled = false;

    if (m_properties.hibernate_mode_enabled == false)
    {
        if (m_protectorComplex.protectorSlot()->item() != nullptr)
        {
            if (m_protectorComplex.protectorSlot()->protectorEquipment()->isFunctioning() == true)
            {
                m_properties.protection += m_protectorComplex.protectorSlot()->protectorEquipment()->protection();
                m_properties.shield_effect_enabled = true;
            }
        }
    }

    if (m_properties.artefact_protection > 0)
    {
        m_properties.protection += m_properties.artefact_protection;
    }
}

void Vehicle::_updatePropRepair()
{
    //LOG("Vehicle("+std::to_string(id())+")::UpdatePropertiesRepair");
    
    m_properties.repair = 0;

    if (m_droidSlot->item() != nullptr)
    {
        if (m_droidSlot->droidEquipment()->isFunctioning() == true) {
            m_properties.repair = m_droidSlot->droidEquipment()->repair();
        }
    }
}


void Vehicle::increaseArmor(int repair)
{
    //LOG("Vehicle("+std::to_string(id())+")::IncreaseArmor");
    
    _dataLife().armor += repair;
    
    if (_dataLife().armor > m_vehicleDescriptor.armor)
    {
        _dataLife().armor = m_vehicleDescriptor.armor;
    }
}

void Vehicle::_updatePropFreeze()
{
#ifdef USE_EXTRA_EQUIPMENT
    //LOG("Vehicle("+std::to_string(id())+")::UpdatePropertiesFreeze");
    
    m_properties.freeze = 0;

    if (m_SlotFreezer->item() != nullptr)
    {
        if (m_SlotFreezer->freezerEquipment()->isFunctioning() == true)
        {
            m_properties.freeze = m_SlotFreezer->freezerEquipment()->GetFreeze();
        }
    }
#endif
}

void Vehicle::_updatePropEnergy()
{
#ifdef USE_EXTRA_EQUIPMENT
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
#endif
}



void Vehicle::_updatePropScan()
{
    //LOG("Vehicle("+std::to_string(id())+")::UpdatePropertiesScan");
    
    m_properties.scan = 0;

    if (m_scanerSlot->item() != nullptr)
    {
        if (m_scanerSlot->scanerEquipment()->isFunctioning() == true)
        {
            m_properties.scan = m_scanerSlot->scanerEquipment()->scan();
        }
    }
}

void Vehicle::_updatePropGrab()
{
    //LOG("Vehicle("+std::to_string(id())+")::UpdatePropertiesGrab");

    m_properties.grab_strength = 0;
    m_properties.grab_radius = 0;

    if (m_vehicleDescriptor.slot_grapple_num != 0)
    {
        if (m_grappleSlot->item() != nullptr)
        {
            if (m_grappleSlot->grappleEquipment()->isFunctioning() == true)
            {
                m_properties.grab_strength = m_grappleSlot->grappleEquipment()->strength();
                m_properties.grab_radius = m_grappleSlot->grappleEquipment()->radius();
            }
        }
    }
}                  

void Vehicle::_updateArtefactInfluence()
{
#ifdef USE_ARTEFACTS
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
#endif
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

bool Vehicle::isAbleToJumpTo(Starsystem* target_starsystem) const
{
    float dist = meti::distance(starsystem()->position(), target_starsystem->position());
    if (dist < m_properties.hyper)
    {
        return true;
    }
    
    return false;
}

void Vehicle::repairKorpus(int amount)
{
    _dataLife().armor += amount;
    if (_dataLife().armor > m_vehicleDescriptor.armor)
    {
        _dataLife().armor = m_vehicleDescriptor.armor;
    }
}

bool Vehicle::isArmorFull() const
{
    if (_dataLife().armor == m_vehicleDescriptor.armor)
    {
        return true;
    }
    
    return false;
}

int Vehicle::armorMiss() const
{
    return (m_vehicleDescriptor.armor - _dataLife().armor);
}

bool Vehicle::isFuelFull() const
{
    if (m_driveComplex.bakSlot()->item() == nullptr)
    {
        return true;
    }
    
    if (fuelMiss() == 0)
    {
        return true;
    }
    
    
    return false;
}

int Vehicle::fuelMiss() const
{
    return m_driveComplex.bakSlot()->bakEquipment()->fuelMiss();
}

void Vehicle::lockRandomItem(int locked_turns)
{
    std::vector<ItemSlot*> _equiped_slot_vec;
    
    for (unsigned int i=0; i<m_equipmentSlots.size(); i++)
    {
        if (m_equipmentSlots[i]->item() != nullptr)
        {
            _equiped_slot_vec.push_back(m_equipmentSlots[i]);
        }
    }
    
    if (_equiped_slot_vec.size() > 0)
    {
        unsigned int _rand = meti::getRandInt(0, _equiped_slot_vec.size());
        _equiped_slot_vec[_rand]->item()->doLock(locked_turns);
    }
}

bool Vehicle::tryConsumeEnergy(int energy)
{
#ifdef USE_EXTRA_EQUIPMENT
    //LOG("Vehicle("+std::to_string(id())+")::TryToConsumeEnergy(energy="+std::to_string(energy)+")");
    
    if (m_properties.energy > energy)
    {
        m_properties.energy -= energy;
        m_SlotEnergizer->energizerEquipment()->DecreaseEnergy(energy);
        
        return true;
    }
    
    return false;
#else
    return true;
#endif
}

bool Vehicle::tryGenerateEnergy(int energy)
{
#ifdef USE_EXTRA_EQUIPMENT
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
#else
    return true;
#endif
}


STATUS Vehicle::CheckGrabStatus() const
{
    STATUS status = STATUS::ITEM_OK;
    
    if (m_grappleSlot->item() != nullptr)
    {
        if (m_grappleSlot->grappleEquipment()->isDamaged() == true)
        {
            status = STATUS::ITEM_DAMAGED;
        }
        
        if (m_grappleSlot->grappleEquipment()->isLocked() != 0)
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

bool Vehicle::dropItemToSpace(const type::entity& type)
{
    if (place() != type::place::KOSMOS)
        return false;

    for (ItemSlot* slot: m_slots) {
        if (slot->subtype() == type && slot->item()) {
            item::Base* item = slot->takeItem();
            Container* container = __wrapItemToContainer(item);
            //    float impulse_strength = 0.5;
            //    glm::vec3 impulse_dir(meti::getRandXYVec3Unit());
            //    container->addImpulse(impulse_dir, impulse_strength);

            starsystem()->add(container, position());
            return true;
        }
    }

    return false;
}

Container*
Vehicle::__wrapItemToContainer(item::Base* item)
{
    Container* container = ContainerBuilder::getNew();
    container->insertItem(item);

    return container;
}

//void Vehicle::__dropRandomItemToSpace()
//{
//    std::vector<ItemSlot*> _equiped_slot_vec;
//    for (ItemSlot* slot: m_slots) {
//        if (slot->item()) {
//            _equiped_slot_vec.push_back(slot);
//        }
//    }
//    if (_equiped_slot_vec.size() > 0) {
//        _equiped_slot_vec[meti::getRandInt(0, _equiped_slot_vec.size()-1)]->dropItemToSpace();
//    }
//}

void Vehicle::UpdateGrappleMicroProgram_inDynamic()
{
    if (m_properties.grab_radius > 0)
    {
        m_grappleSlot->grappleEquipment()->UpdateGrabScenarioProgram_inDynamic();
    }
}

void Vehicle::SaveData(boost::property_tree::ptree& save_ptree, const std::string& root) const
{
    //LOG(" Vehicle("+std::to_string(id())+")::SaveData");

    save_ptree.put(root+"m_DataKorpus.space", m_vehicleDescriptor.space);
    save_ptree.put(root+"m_DataKorpus.armor", m_vehicleDescriptor.armor);
    save_ptree.put(root+"m_DataKorpus.protection", m_vehicleDescriptor.protection);
    save_ptree.put(root+"m_DataKorpus.temperature", m_vehicleDescriptor.temperature);

    save_ptree.put(root+"m_DataKorpus.price", m_vehicleDescriptor.price);
    save_ptree.put(root+"m_DataKorpus.draw_turrels", m_vehicleDescriptor.draw_turrels);

    save_ptree.put(root+"m_DataKorpus.slot_grapple_num", m_vehicleDescriptor.slot_grapple_num);
    save_ptree.put(root+"m_DataKorpus.slot_drive_num", m_vehicleDescriptor.slot_drive_num);
    save_ptree.put(root+"m_DataKorpus.slot_protector_num", m_vehicleDescriptor.slot_protector_num);
    save_ptree.put(root+"m_DataKorpus.slot_radar_num", m_vehicleDescriptor.slot_radar_num);
    save_ptree.put(root+"m_DataKorpus.slot_scaner_num", m_vehicleDescriptor.slot_scaner_num);
    save_ptree.put(root+"m_DataKorpus.slot_freezer_num", m_vehicleDescriptor.slot_freezer_num);
    save_ptree.put(root+"m_DataKorpus.slot_weapon_num", m_vehicleDescriptor.slot_weapon_num);


    if (m_driveComplex.GetTarget() != nullptr)
    {
        save_ptree.put(root+"data_unresolved_Vehicle.drive_complex_target_id", m_driveComplex.GetTarget()->id());
        save_ptree.put(root+"data_unresolved_Vehicle.drive_complex_action_id", m_driveComplex.GetActionId());
    }
    else
    {
        save_ptree.put(root+"data_unresolved_Vehicle.drive_complex_target_id", NONE_ID);
        save_ptree.put(root+"data_unresolved_Vehicle.drive_complex_action_id", NONE_ID);
    }

    if (m_Land != nullptr)  { save_ptree.put(root+"data_unresolved_Vehicle.land_id", m_Land->id()); }
    else                     { save_ptree.put(root+"data_unresolved_Vehicle.land_id", NONE_ID); }
    
    if (m_parentVehicleSlot != nullptr) { save_ptree.put(root+"data_unresolved_Vehicle.parent_vehicleslot_id", m_parentVehicleSlot->id()); }
    else                                     { save_ptree.put(root+"data_unresolved_Vehicle.parent_vehicleslot_id", NONE_ID); }

    if (place() == type::place::HYPER)
    {
        save_ptree.put(root+"data_unresolved_Vehicle.starsystem_hyper_id", m_driveComplex.GetTarget()->id());
    }
    else
    {
        save_ptree.put(root+"data_unresolved_Vehicle.starsystem_hyper_id", NONE_ID);
    }
}

void Vehicle::LoadData(const boost::property_tree::ptree& load_ptree)
{
    //LOG(" Vehicle("+std::to_string(id())+")::LoadData");
    
    m_vehicleDescriptor.space       = load_ptree.get<int>("m_DataKorpus.space");
    m_vehicleDescriptor.armor       = load_ptree.get<int>("m_DataKorpus.armor");
    m_vehicleDescriptor.protection  = load_ptree.get<int>("m_DataKorpus.protection");
    m_vehicleDescriptor.temperature = load_ptree.get<int>("m_DataKorpus.temperature");

    m_vehicleDescriptor.price        = load_ptree.get<int>("m_DataKorpus.price");
    m_vehicleDescriptor.draw_turrels = load_ptree.get<bool>("m_DataKorpus.draw_turrels");

    m_vehicleDescriptor.slot_grapple_num   = load_ptree.get<int>("m_DataKorpus.slot_grapple_num");
    m_vehicleDescriptor.slot_drive_num     = load_ptree.get<int>("m_DataKorpus.slot_drive_num");
    m_vehicleDescriptor.slot_protector_num = load_ptree.get<int>("m_DataKorpus.slot_protector_num");
    m_vehicleDescriptor.slot_radar_num     = load_ptree.get<int>("m_DataKorpus.slot_radar_num");
    m_vehicleDescriptor.slot_scaner_num    = load_ptree.get<int>("m_DataKorpus.slot_scaner_num");
    m_vehicleDescriptor.slot_freezer_num   = load_ptree.get<int>("m_DataKorpus.slot_freezer_num");
    m_vehicleDescriptor.slot_weapon_num    = load_ptree.get<int>("m_DataKorpus.slot_weapon_num");

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
        m_driveComplex.SetTarget((SpaceObject*)global::get().entityManager().get(data_unresolved_Vehicle.drive_complex_target_id),  data_unresolved_Vehicle.drive_complex_action_id);
    }

    if (data_unresolved_Vehicle.land_id != NONE_ID)
    {
        setLand( (Land*)global::get().entityManager().get(data_unresolved_Vehicle.land_id) );
    }

    switch(place())
    {
    case type::place::KOSMOS:
    {
        //starsystem()->add(this, data_unresolved_Orientation.center, data_unresolved_Orientation.direction, parent());
        break;
    }

    case type::place::KOSMOPORT:
    {
        ((VehicleSlot*)global::get().entityManager().get(data_unresolved_Vehicle.parent_vehicleslot_id ))->InsertVehicle(this);
        break;
    }

    case type::place::HYPER:
    {
        //std::cout<<"xxx="<<data_unresolved_Vehicle.starsystem_hyper_id<<std::endl;
        ((Starsystem*)global::get().entityManager().get(data_unresolved_Vehicle.starsystem_hyper_id))->hyperSpace().AddVehicle(this);
        //std::cout<<"yyy="<<data_unresolved_Vehicle.starsystem_hyper_id<<std::endl;

        break;
    }

    case type::place::LAND:
    {
        ((NatureLand*)global::get().entityManager().get(data_unresolved_Vehicle.land_id))->AddVehicle(this);
        break;
    }
    }
    
    m_weaponComplex.prepareWeapons();
}

//void Vehicle::TEST_DamageAndLockRandItems()
//{
//    int rand_index1 = meti::getRandInt(0, m_equipmentSlots.size()-1);
//    while (m_equipmentSlots[rand_index1]->item() == nullptr)
//    {
//        rand_index1 = meti::getRandInt(0, m_equipmentSlots.size()-1);
//    }
//    m_equipmentSlots[rand_index1]->item()->doLock(3);

//    int rand_index2 = meti::getRandInt(0, m_equipmentSlots.size()-1);
//    while (m_equipmentSlots[rand_index2]->item() == nullptr)
//    {
//        rand_index2 = meti::getRandInt(0, m_equipmentSlots.size()-1);
//    }
    
//    while (m_equipmentSlots[rand_index2]->item()->condition() > 0)
//    {
//        m_equipmentSlots[rand_index2]->item()->deteriorationEvent();
//    }
//}

std::string getVehicleSpecialActionStr(VEHICLE_SPECIAL_ACTION_TYPE type_id)
{
    switch(type_id)
    {
    case VEHICLE_SPECIAL_ACTION_TYPE::INITIATE_DOCKING_ID:     { return "INITIATE_DOCKING_ID"; break; }
    case VEHICLE_SPECIAL_ACTION_TYPE::INITIATE_LAUNCHING_ID:    { return "INITIATE_LAUNCHING_ID"; break; }
    case VEHICLE_SPECIAL_ACTION_TYPE::INITIATE_JUMPIN_ID:        { return "INITIATE_JUMPIN_ID"; break; }
    case VEHICLE_SPECIAL_ACTION_TYPE::INITIATE_JUMPOUT_ID:        { return "INITIATE_JUMPOUT_ID"; break; }
    case VEHICLE_SPECIAL_ACTION_TYPE::NONE_ID:                    { return "NONE_ID"; break; }

    default: { return "UKNOWN id_type"; break; }
    }
}
