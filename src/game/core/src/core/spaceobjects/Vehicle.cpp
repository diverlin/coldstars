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

//#include <client/resources/GuiTextureObCollector.hpp>

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
#include <item/artefacts/GravityArtefact.hpp>
#include <item/artefacts/ProtectorArtefact.hpp>
#endif

//#include <client/effects/Shield.hpp>
//#include <jeti/particlesystem/DriveEffect.hpp>
//#include <jeti/particlesystem/ExplosionEffect.hpp>
//#include <client/text/VerticalFlowText.hpp>

#include <parts/Turrel.hpp>

#include <pilots/Npc.hpp>

#include <core/descriptor/item/Item.hpp>

#include <dock/Kosmoport.hpp>
#include <dock/Angar.hpp>
#include <dock/Shop.hpp>
#include <dock/Store.hpp>
#include <dock/NatureLand.hpp>

//#include <jeti/Render.hpp>

#include <math/rand.hpp>
#include <meti/RandUtils.hpp>


namespace model {

Vehicle::Vehicle(const std::string& data)
{
    //MACRO_READ_SERIALIZED_DATA
}

std::string
Vehicle::data() const
{
    //MACRO_SAVE_SERIALIZED_DATA
}

} // namespace model





namespace control {


Vehicle::Vehicle(model::Vehicle* model)
    :
      SpaceObject(model)
    , m_model_vehicle(model)
{
    assert(false);
    //    model()->weaponComplex()->SetOwnerVehicle(this);
    //    model()->driveComplex().SetOwnerVehicle(this);
    //    model()->protectorComplex().SetOwnerVehicle(this);
}

/* virtual */
Vehicle::~Vehicle()
{
    //LOG("___::~Vehicle("+std::to_string(model()->id())+")");
}

/* virtual override */
void Vehicle::putChildrenToGarbage() const
{
    assert(false);
//    m_npc->setAlive(false);
//    core::global::get().entityManager().addToGarbage(m_npc);

//    for(ItemSlot* slot: m_slots) {
//        core::global::get().entityManager().addToGarbage(slot);
//    }
}

// weapon complex interface
void Vehicle::fire(int timer, float attack_rate)
{
    weaponComplex().fire(timer, attack_rate, false);
}

void Vehicle::setWeaponTarget(model::SpaceObject* object, ItemSlot* slot)
{
    assert(false);
    //model()->weaponComplex().setTarget(object, slot);
}

void Vehicle::prepareWeapons()
{
    model()->weaponComplex().prepareWeapons();
}

int Vehicle::guessDamage(int dist)
{
    return model()->weaponComplex().guessDamage(dist);
}

//\ weapon complex interface

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

void Vehicle::setKorpusData(descriptor::Vehicle* korpus_data)
{
    m_descriptor_vehicle = korpus_data;
    model()->properties().protection = m_descriptor_vehicle->protection();
}

GoodsPack* Vehicle::goodsPack() const
{
    assert(false);
//    for(ItemSlot* slot: m_cargoSlots) {
//        if (slot->item()) {
//            if (slot->item()->type() == entity::Type::GOODS) {
//                return slot->goodsPack();
//            }
//        }
//    }
    return nullptr;
}

/* virtual override final */
int Vehicle::givenExpirience() const
{
    assert(false);
    //return m_npc->skills().expirience() * GIVEN_EXPIRIENCE_RATE_DEPENDING_ON_NPC_EXPIRIENCE;
}

bool Vehicle::isSlotTypePresent(const entity::type& slot_subtype_id) const
{
    assert(false);
//    for (ItemSlot* slot: m_slots) {
//        if (slot->subtype() == slot_subtype_id) {
//            return true;
//        }
//    }
    return false;
}

void Vehicle::addItemSlot(ItemSlot* slot)
{
    assert(false);
//    slot->setOwner(this);

//    switch(slot->subtype())
//    {
//    case entity::Type::WEAPON_SLOT:
//    {
//        float border_start = 0.2;
//        float border_end   = 0.8;

//        float pos_x = meti::getRandFloat(border_start, border_end) - 0.5;
//        float pos_y = meti::getRandFloat(border_start, border_end) - 0.5;

//        slot->turrel()->setParentPosition(pos_x, pos_y, DEFAULT_ENTITY_ZPOS);
//        //points().add(slot->turrel()->pPosition(), slot->turrel()->pParentPosition());
//        model()->weaponComplex().addSlot(slot);

//        break;
//    }
//    case entity::Type::DRIVE_SLOT:     { model()->driveComplex().SetDriveSlot(slot); break; }
//    case entity::Type::BAK_SLOT:       { model()->driveComplex().SetBakSlot(slot); break; }
//    case entity::Type::PROTECTOR_SLOT: { model()->protectorComplex().SetProtectorSlot(slot); break; }
//    case entity::Type::RADAR_SLOT:     { m_radarSlot  = slot; break; }
//    case entity::Type::SCANER_SLOT:    { m_scanerSlot = slot; break; }
//#ifdef USE_EXTRA_EQUIPMENT
//    case entity::Type::ENERGIZER_SLOT: { m_energizerSlot = slot; break; }
//    case entity::Type::FREEZER_SLOT:   { m_freezerSlot   = slot; break; }
//#endif // USE_EXTRA_EQUIPMENT
//    case entity::Type::GRAPPLE_SLOT:   { m_grappleSlot   = slot; break; }
//    case entity::Type::DROID_SLOT:     { m_droidSlot     = slot; break; }
//    }

//    m_slots.push_back(slot);

//    if ( (slot->subtype() != entity::Type::ARTEFACT_SLOT) and (slot->subtype() != entity::Type::CARGO_SLOT) ) {
//        m_equipmentSlots.push_back(slot);
//    }

//    if (slot->subtype() == entity::Type::ARTEFACT_SLOT) {
//        m_artefactSlots.push_back(slot);
//    }

//    if (slot->subtype() == entity::Type::CARGO_SLOT) {
//        m_cargoSlots.push_back(slot);
//    }
}

bool Vehicle::grabItemsFromVehicle(Vehicle* vehicle)
{
    bool result = true;
    assert(false);
//    for(ItemSlot* slot: vehicle->m_slots) {
//        if (slot->item()) {
//            if (slot->subtype() == entity::Type::CARGO_SLOT) {
//                result = addItemToCargoSlot(slot->item());
//            } else {
//                result = manage(slot->item());
//            }
//        }
//    }
    return result;
}

bool Vehicle::_installItem(control::Item* item)
{
    assert(false);
//    switch(item->type()) {
//    case entity::Type::EQUIPMENT:    { return _installEquipment(item); break; }
//#ifdef USE_MODULES
//    case entity::Type::MODULE:       { return _installModule(item); break; }
//#endif
//#ifdef USE_ARTEFACTS
//    case entity::Type::ARTEFACT:     { return _installArtefact(item); break; }
//#endif
//    case entity::Type::GOODS:        { return _installGoodsPack(item); break; } // what??
//    }
//    return false;
}

bool Vehicle::isSlotFree(const place::type& subtype) const
{
    assert(false);
//    for (ItemSlot* slot: m_slots) {
//        if (slot->subtype() == subtype) {
//            if (slot->isEmpty()) {
//                return true;
//            }
//        }
//    }
//    return false;
}

bool Vehicle::checkManage(const core::Id& ident)
{
    if (!isSlotTypePresent(ident.subtype)) {
        return false;
    }

    switch(ident.type) {
    case entity::type::EQUIPMENT:    { return _checkInstallEquipment(ident); break; }
        //#ifdef USE_MODULES
        //    case entity::Type::MODULE:       { return _checkInstallModule(type); break; }
        //#endif
        //#ifdef USE_ARTEFACTS
        //    case entity::Type::ARTEFACT:     { return _checkInstallArtefact(type); break; }
        //#endif
        //    case entity::Type::GOODS:        { return _checkInstallGoodsPack(type); break; }
    }
    return false;
}

bool Vehicle::_installGoodsPack(Item* item)
{
    return __mergeIdenticalGoods(item);
}

bool Vehicle::_installEquipment(Item* item)
{
    if (item->descriptor()->slotType() == entity::type::WEAPON_SLOT) {
        ItemSlot* slot = model()->weaponComplex().freeSlot();
        if (slot) {
            return slot->swapItem(item->slot());
        } else {
            ItemSlot* slot = model()->weaponComplex().equipedWeakestSlot();
            if (slot) {
                if (item->descriptor()->price() > slot->item()->descriptor()->price()) {
                    return slot->swapItem(item->slot());
                }
            }
        }
    } else {
        ItemSlot* slot = _functionalSlot(item->descriptor()->slotType());
        if (slot->item()) {
            if (item->descriptor()->price() > slot->item()->descriptor()->price()) {
                return slot->swapItem(item->slot());
            }
        } else {
            return slot->swapItem(item->slot());
        }
    }

    return false;
}

bool Vehicle::_checkInstallEquipment(const core::Id& ident)
{
    if (ident.type == entity::type::WEAPON_SLOT) {
        if (model()->weaponComplex().freeSlot()) {
            return true;
        }
    } else {
        if (_freeFunctionalSlot(ident)) {
            return true;
        }
    }

    if (freeCargoSlot()) {
        return true;
    }

    return false;
}

#ifdef USE_MODULES
bool Vehicle::installModule(item::Base* item)
{
    for (unsigned int i=0; i<m_SlotFunct_vec.size(); i++) {
        if (m_SlotFunct_vec[i]->item()) {
            if (m_SlotFunct_vec[i]->item()->subTypeId() == item->parentSubTypeId()) {
                return ((Equipment*)m_SlotFunct_vec[i]->item())->InsertModule((BaseModule*)item);
            }
        }
    }
    return false;
}
#endif

#ifdef EANBLE_ARTEFACTS
bool Vehicle::installArtefact(item::Base* item)
{
    ItemSlot* artef_slot = GetEmptyArtefactSlot();
    if (artef_slot) {
        return artef_slot->swapItem(item->itemSlot());
    }

    return false;
}
#endif

ItemSlot* const
Vehicle::_functionalSlot(const entity::type& functional_slot_subtype_id) const
{
    assert(false);
//    for(ItemSlot* slot: m_equipmentSlots) {
//        if (slot->subtype() == functional_slot_subtype_id) {
//            return slot;
//        }
//    }
    return nullptr;
}

ItemSlot* const
Vehicle::_freeFunctionalSlot(const core::Id& ident) const
{
    assert(false);
//    for(ItemSlot* slot: m_equipmentSlots) {
//        if (slot->subtype() == ident.subtype) {
//            if (slot->isEmpty()) {
//                return slot;
//            }
//        }
//    }
    return nullptr;
}

ItemSlot* const
Vehicle::_freeArtefactSlot() const
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

ItemSlot* const Vehicle::_cargoSlotWithGoods(place::type requested_goods_subtype_id)
{
    assert(false);
//    for (ItemSlot* slot: m_cargoSlots) {
//        if (slot->item()) {
//            if (slot->item()->type() == entity::Type::GOODS) {
//                if (slot->item()->subtype() == requested_goods_subtype_id) {
//                    return slot;
//                }
//            }
//        }
//    }
    return nullptr;
}

bool
Vehicle::unpackContainerItemToCargoSlot(control::Container* container)
{
    if (addItemToCargoSlot(container->itemSlot()->item()) == true)
    {
        container->killSilently();

        return true;
    }

    return false;
}

bool Vehicle::addItemToCargoSlot(Item* item)
{
    assert(false);
//    _increaseMass(item->mass());
//    if (item->type() == entity::Type::GOODS) {
//        if (_installGoodsPack(item)) {
//            return true;
//        }
//    }

//    ItemSlot* slot = freeCargoSlot();
//    if (slot) {
//        return slot->insert(item);
//    }

    return false;
}

bool
Vehicle::manage(Item* item)
{
    if (addItemToCargoSlot(item)) {
        _installItem(item);
        return true;
    }
    return false;
}

void Vehicle::manageItemsInCargo()
{
    for (unsigned int i=0; i<m_cargoSlots.size(); i++) {
        if (m_cargoSlots[i]->item()) {
            _installItem(m_cargoSlots[i]->item());
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

bool Vehicle::sellItem(Item* item)
{
    //float skill_rate = 1.0f + sign*0.1*npc->GetSkill().GetTrader();
    //npc->IncreaseCredits(sign*amount*skill_rate*minerals_price);
    int earn_money = 0;
    int item_mass = item->descriptor()->mass();
    assert(false);
//    switch(item->type()) {
//        case entity::Type::GOODS: {
//            earn_money = ((Kosmoport*)m_Land)->GetShop()->BuyGoods((GoodsPack*)item);
//            break;
//        }

//        case entity::Type::EQUIPMENT: {
//            earn_money = ((Kosmoport*)m_Land)->GetStore()->buyItem(item);
//            break;
//        }
//    }

//    if (earn_money > 0) {
//        _decreaseMass(item_mass);
//        m_npc->increaseCredits(earn_money);

//        return true;
//    } else {
//        return false;
//    }
}

bool Vehicle::buyItem(Item* item)
{
    if (addItemToCargoSlot(item) == true)
    {
        m_npc->increaseCredits(-item->descriptor()->price());

        return true;
    }

    return false;
}

bool Vehicle::__mergeIdenticalGoods(Item* item)
{
    assert(false);
//    ItemSlot* item_slot = _cargoSlotWithGoods(item->subtype());
//    if (item_slot != nullptr)
//    {
//        item_slot->goodsPack()->Increase(item->mass());
//        // delete item; dangerrr
//        return true;
//    }

    return false;
}

void Vehicle::bindNpc(control::Npc* owner_npc)
{
    m_npc = owner_npc;
    assert(false);
    //    m_npc->setVehicle(this);
}

bool Vehicle::isObjectVisible(SpaceObject* object) const
{
    float dist = meti::distance(position(), object->position());
    if (dist < model()->properties().radar) {
        return true;
    }

    return false;
}

void Vehicle::UpdateSpecialAction()
{
    switch(m_specialActionId)
    {
    case VEHICLE_SPECIAL_ACTION_TYPE::NONE: { break; }

    case VEHICLE_SPECIAL_ACTION_TYPE::INITIATE_DOCKING:
    {
        // alpitodorender if (UpdateFadeInEffect() == true)
        {
            DockingEvent();
            m_specialActionId = VEHICLE_SPECIAL_ACTION_TYPE::NONE;
        }

        break;
    }

    case VEHICLE_SPECIAL_ACTION_TYPE::INITIATE_LAUNCHING:
    {
        // alpitodorender if (UpdateFadeOutEffect() == true)
        {
            m_specialActionId = VEHICLE_SPECIAL_ACTION_TYPE::NONE;
        }

        break;
    }

    case VEHICLE_SPECIAL_ACTION_TYPE::INITIATE_JUMPIN:
    {
        // alpitodorender if (UpdateFadeInEffect() == true)
        {
            assert(false);
            //HyperJumpEvent(model()->driveComplex().target()->starsystem());
        }

        break;
    }

    case VEHICLE_SPECIAL_ACTION_TYPE::INITIATE_JUMPOUT:
    {
        // alpitodorender if (UpdateFadeOutEffect() == true)
        {
            m_specialActionId = VEHICLE_SPECIAL_ACTION_TYPE::NONE;
        }

        break;
    }
    }
}

//// ******** dock/LAUNCHING ********
void Vehicle::HyperJumpEvent(model::Starsystem* starsystem)
{
    //LOG("Vehicle("+std::to_string(id())+")::HyperJumpEvent");

    model()->weaponComplex().deactivateWeapons();

    m_specialActionId = VEHICLE_SPECIAL_ACTION_TYPE::INITIATE_JUMPOUT;
    assert(false);
    //starsystem->hyperSpace().AddVehicle(this);
}


void Vehicle::DockingEvent()
{
    //LOG("Vehicle("+std::to_string(id())+")::DockingEvent");

    model()->weaponComplex().deactivateWeapons();

    assert(false);
//    switch(model()->driveComplex().target()->type())
//    {
//    case entity::type::PLANET:
//    {
//        //        Planet* planet = ((Planet*)model()->driveComplex().target());
//        //        planet->GetLand()->AddVehicle(this);

//        break;
//    }

//    case entity::type::VEHICLE:
//    {
//        switch(model()->driveComplex().target()->subtype())
//        {
//        case entity::type::SPACESTATION:
//        {
//            SpaceStation* spacestation = ((SpaceStation*)model()->driveComplex().target());
//            assert(false);
//            //spacestation->land()->AddVehicle(this);

//            break;
//        }

//        case entity::type::SHIP:
//        {
//            //..
//            break;
//        }
//        }

//        break;
//    }
//    }

    model()->driveComplex().ResetTarget();
}

void Vehicle::LaunchingEvent()
{
    //LOG("Vehicle("+std::to_string(id())+")::LaunchingEvent");

    /* if (m_parentVehicleSlot != nullptr)
    {
        switch(m_parentVehicleSlot->owner()->typeId())
        {
        case entity::Type::ANGAR:
        {
            int angleInD = meti::getRandInt(360);
            glm::vec2 offset_pos = meti::getRandVec2f(40, 100);
            glm::vec3 offset_pos3(offset_pos.x, offset_pos.y, DEFAULT_ENTITY_ZPOS);
            glm::vec3 angle(0,0,angleInD);
            starsystem()->add(this, ((SpaceObject*)m_Land->GetOwner())->center() + offset_pos3, angle, nullptr);
            m_Land->RemoveVehicle(this);

            break;
        }

        case entity::Type::VEHICLE:
        {
            //..
            break;
        }
        }
    }
    else
    {
        int angleInD = meti::getRandInt(360);
        glm::vec2 offset_pos = meti::getRandVec2f(40, 100);
        glm::vec3 offset_pos3(offset_pos.x, offset_pos.y, DEFAULT_ENTITY_ZPOS);
        glm::vec3 angle(0,0,angleInD);
        starsystem()->add(this, ((SpaceObject*)m_Land->GetOwner())->center() + offset_pos3, angle, nullptr);
        m_Land->RemoveVehicle(this);
    }

    SetSpecialActionId(VEHICLE_SPECIAL_ACTION_TYPE::INITIATE_LAUNCHING);
    // alpitodorender SetTransparency(0.1);*/
}

/* virtual */
void Vehicle::remeberAgressor(Vehicle* agressor)
{
    assert(false);
    //m_npc->remeberAgressor(agressor);
}


float Vehicle::adjustDissipateFilter() const
{
    float rate = 1.0f - model()->properties().protection*0.01f;
    //    if (m_npc) {
    //        rate *= m_npc->GetSkills().GetDefenceNormalized();
    //    }
    //std::cout<<"---rate="<<rate<<std::endl;
    assert(rate > 0 && rate <= 1.0f);
    return rate;
}

int Vehicle::criticalDamage() const {
    return 2*model()->armor();
}

/* virtual */
void Vehicle::hit(int damage)
{
    LOG(std::string("Vehicle::hit id=") << std::to_string(model()->id()) << " damage=" << std::to_string(damage));
    if (m_godMode)
        return;

#ifdef USE_EXTRA_EQUIPMENT
    if (model()->properties().energy < damage) {
        model()->properties().hibernate_mode_enabled = true;
        _updatePropProtection();
    }
#endif

    SpaceObject::hit(damage * adjustDissipateFilter());

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

/* virtual */
void Vehicle::_postDeathUniqueEvent(bool show_effect)
{
    int num_items = meti::getRandInt(3);
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
    if (model()->armor() < 0.5*descriptor()->armor()) {
        model()->needs().repair_korpus = true;
    } else {
        model()->needs().repair_korpus = false;
    }

    //check item damages
    model()->needs().repair_equipment = false;
    for (ItemSlot* slot: m_equipmentSlots) {
        if (slot->item()) {
            if (slot->item()->isDamaged()) {
                model()->needs().repair_equipment = true;
            }
        }
    }

    //check ammo
    model()->needs().get_ammo = false;
    assert(false);
//    for (ItemSlot* slot: m_equipmentSlots) {
//        if (slot->item()) {
//            if (slot->item()->subtype() == entity::Type::ROCKET_EQUIPMENT) {
//                if (slot->rocketEquipment()->GetAmmo() == 0) {
//                    model()->needs().get_ammo = true;
//                }
//            }
//        }
//   }

    // check fuel
assert(false);
//    model()->needs().get_fuel = false;
//    if (model()->driveComplex().bakSlot()) {
//        if (model()->driveComplex().bakSlot()->item()) {
//            if (model()->driveComplex().bakSlot()->bakEquipment()->fuel() < 0.8*model()->driveComplex().bakSlot()->bakEquipment()->fuelMax()) {
//                model()->needs().get_fuel = true;
//            }
//        }
//    }

    // check credits
//    if (m_npc->credits() < 1000)    { model()->needs().get_credits = true; }
//    else                            { model()->needs().get_credits = false; }
}


void Vehicle::ResolveNeedsInKosmoportInStatic()
{
    bool result = true;

    // buy repair korpus
    if ( (model()->needs().repair_korpus == true) and (result == true) )
    {
        assert(false);
        //result = ((Angar*)m_parentVehicleSlot->owner())->RepairVehicle(this);
    }

    // repair equipment
    if ( (model()->needs().repair_equipment == true) && (result == true) ) {
        for (unsigned int i=0; i<m_equipmentSlots.size(); i++) {
            if (m_equipmentSlots[i]->item()) {
                if (m_equipmentSlots[i]->item()->isDamaged()) {
                    assert(false);
                    //result = ((Angar*)m_parentVehicleSlot->owner())->RepairItem(m_npc, m_equipmentSlots[i]->item());
                }
            }
        }
    }

    // buy ammo
    if ( (model()->needs().get_ammo == true) && (result == true) ) {
        for (ItemSlot* slot: m_equipmentSlots) {
            if (slot->item()) {
                assert(false);
//                if (slot->item()->subtype() == entity::Type::ROCKET_EQUIPMENT) {
//                    result = ((Angar*)m_parentVehicleSlot->owner())->chargeRocketEquipment(m_npc, slot->rocketEquipment());
//                }
            }
        }
    }

    // tank up
    if ( (model()->needs().get_fuel == true) and (result == true) ) {
        assert(false);
        //result = ((Angar*)m_parentVehicleSlot->owner())->TankUpVehicle(this);
    }

    //// check credits
    //if (m_OwnerNpc->GetCredits() < 1000) { model()->needs().get_credits = true; }
    //else                                { model()->needs().get_credits = false; }
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
    model()->properties().free_space = descriptor()->space() - model()->mass();
    _updatePropSpeed(); // as the mass influence speed this action is necessary here
}

void Vehicle::_decreaseMass(int d_mass)
{
    //LOG("Vehicle("+std::to_string(id())+")::DecreaseMass");

    _addMass(-d_mass);
    model()->properties().free_space = descriptor()->space() - model()->mass();
    _updatePropSpeed(); // as the mass influence speed this action is necessary here
}

void Vehicle::_updatePropSpeed()
{
    //LOG("Vehicle("+std::to_string(id())+")::UpdatePropertiesSpeed");
    assert(false);
//    model()->properties().speed = 0;
//    if (!model()->driveComplex().driveSlot())
//        return;
//    if (!model()->driveComplex().driveSlot()->item())
//        return;
//    if (!model()->driveComplex().driveSlot()->driveEquipment()->isFunctioning())
//        return;

//    float actual_speed = (model()->driveComplex().driveSlot()->driveEquipment()->speed() - model()->mass()*MASS_DECREASE_SPEED_RATE);
//    if (actual_speed > 0) {
//        if (model()->properties().artefact_gravity > 0) {
//            model()->properties().speed = (1.0 + model()->properties().artefact_gravity/100.0)*actual_speed;
//        } else {
//            model()->properties().speed = actual_speed;
//        }

//        if (model()->driveComplex().driveSlot()->isSelected() == true) {
//            model()->properties().speed *= EQUIPMENT::DRIVE::OVERLOAD_RATE;
//            model()->driveComplex().driveSlot()->item()->useOverloadDeterioration();
//        } else {
//            model()->driveComplex().driveSlot()->item()->useNormalDeterioration();
//        }
//        model()->driveComplex().UpdatePath();
//    }
}

void Vehicle::_updatePropFire()
{
    //LOG("Vehicle("+std::to_string(id())+")::UpdatePropertiesFire");

    model()->weaponComplex().updateFireAbility();

    model()->properties().total_damage = model()->weaponComplex().damage();
    model()->properties().fire_radius_min = model()->weaponComplex().radiusMin();
    model()->properties().fire_radius_max = model()->weaponComplex().radiusMax();
}

void Vehicle::_updatePropRadar()
{
    //LOG("Vehicle("+std::to_string(id())+")::UpdatePropertiesRadar");

    model()->properties().radar = VISIBLE_DISTANCE_WITHOUT_RADAR;
    model()->properties().equipment_radar = false;

    if (!m_radarSlot->item())
        return;

    assert(false);
//    if (!m_radarSlot->radarEquipment()->isFunctioning())
//        return;

//    model()->properties().radar = m_radarSlot->radarEquipment()->radius();
//    model()->properties().equipment_radar = true;
}

void Vehicle::_updatePropJump()
{
    //LOG("Vehicle("+std::to_string(id())+")::UpdatePropertiesJump");

    model()->properties().hyper = 0;
    assert(false);

//    if (!model()->driveComplex().driveSlot())
//        return;
//    if (!model()->driveComplex().driveSlot()->item())
//        return;
//    if (!model()->driveComplex().driveSlot()->driveEquipment()->isFunctioning())
//        return;
//    if (!model()->driveComplex().bakSlot())
//        return;
//    if (!model()->driveComplex().bakSlot()->item())
//        return;
//    if (!model()->driveComplex().bakSlot()->bakEquipment()->isFunctioning())
//        return;

//    model()->properties().hyper = std::min(model()->driveComplex().driveSlot()->driveEquipment()->hyper(), model()->driveComplex().bakSlot()->bakEquipment()->fuel());
}

void Vehicle::_updatePropProtection()
{
    //LOG("Vehicle("+std::to_string(id())+")::UpdatePropertiesProtection");

    model()->properties().protection = descriptor()->protection();
    model()->properties().shield_effect_enabled = false;

    assert(false);
//    if (!model()->properties().hibernate_mode_enabled) {
//        if (model()->protectorComplex().protectorSlot()->item()) {
//            if (model()->protectorComplex().protectorSlot()->protectorEquipment()->isFunctioning()) {
//                model()->properties().protection += model()->protectorComplex().protectorSlot()->protectorEquipment()->protection();
//                model()->properties().shield_effect_enabled = true;
//            }
//        }
//    }

    if (model()->properties().artefact_protection > 0) {
        model()->properties().protection += model()->properties().artefact_protection;
    }
}

void Vehicle::_updatePropRepair()
{
    //LOG("Vehicle("+std::to_string(id())+")::UpdatePropertiesRepair");

    model()->properties().repair = 0;

    if (m_droidSlot->item() != nullptr)
    {
        assert(false);
//        if (m_droidSlot->droidEquipment()->isFunctioning() == true) {
//            model()->properties().repair = m_droidSlot->droidEquipment()->model()->repair();
//        }
    }
}


void Vehicle::increaseArmor(int repair)
{
    //LOG("Vehicle("+std::to_string(id())+")::IncreaseArmor");

    model()->addArmor(repair);

    if (model()->armor() > descriptor()->armor()) {
        model()->setArmor(descriptor()->armor());
    }
}

void Vehicle::_updatePropFreeze()
{
#ifdef USE_EXTRA_EQUIPMENT
    //LOG("Vehicle("+std::to_string(id())+")::UpdatePropertiesFreeze");

    model()->properties().freeze = 0;

    if (m_SlotFreezer->item() != nullptr)
    {
        if (m_SlotFreezer->freezerEquipment()->isFunctioning() == true)
        {
            model()->properties().freeze = m_SlotFreezer->freezerEquipment()->GetFreeze();
        }
    }
#endif
}

void Vehicle::_updatePropEnergy()
{
#ifdef USE_EXTRA_EQUIPMENT
    //LOG("Vehicle("+std::to_string(id())+")::UpdatePropertiesEnergy");

    model()->properties().energy = 0;
    model()->properties().hibernate_mode_enabled = true;

    if (m_SlotEnergizer->item() != nullptr)
    {
        if (m_SlotEnergizer->energizerEquipment()->isFunctioning() == true)
        {
            model()->properties().energy = m_SlotEnergizer->energizerEquipment()->GetEnergy();
            model()->properties().hibernate_mode_enabled = false;
        }
    }

    UpdatePropertiesProtection();
#endif
}



void Vehicle::_updatePropScan()
{
    //LOG("Vehicle("+std::to_string(id())+")::UpdatePropertiesScan");

    model()->properties().scan = 0;

    if (m_scanerSlot->item() != nullptr)
    {
        assert(false);
//        if (m_scanerSlot->scanerEquipment()->isFunctioning() == true)
//        {
//            model()->properties().scan = m_scanerSlot->scanerEquipment()->scan();
//        }
    }
}

void Vehicle::_updatePropGrab()
{
    //LOG("Vehicle("+std::to_string(id())+")::UpdatePropertiesGrab");

    model()->properties().grab_strength = 0;
    model()->properties().grab_radius = 0;

    if (descriptor()->grappleSlotNum() != 0)
    {
        if (m_grappleSlot->item() != nullptr)
        {
            assert(false);
//            if (m_grappleSlot->grappleEquipment()->isFunctioning() == true)
//            {
//                model()->properties().grab_strength = m_grappleSlot->grappleEquipment()->strength();
//                model()->properties().grab_radius = m_grappleSlot->grappleEquipment()->radius();
//            }
        }
    }
}

void Vehicle::_updateArtefactInfluence()
{
#ifdef USE_ARTEFACTS
    //LOG("Vehicle("+std::to_string(id())+")::UpdateArtefactInfluence");

    model()->properties().artefact_gravity = 0;
    model()->properties().artefact_protection = 0;

    for (unsigned int i=0; i<m_SlotArtef_vec.size(); i++)
    {
        if (m_SlotArtef_vec[i]->item() != nullptr)
        {
            if (m_SlotArtef_vec[i]->item()->isFunctioning() == true)
            {
                switch(m_SlotArtef_vec[i]->item()->subTypeId())
                {
                case entity::Type::GRAVITY_ARTEFACT:
                {
                    model()->properties().artefact_gravity += ((GravityArtefact*)m_SlotArtef_vec[i]->item())->GetGravity();
                    break;
                }

                case entity::Type::PROTECTOR_ARTEFACT:
                {
                    model()->properties().artefact_protection += ((ProtectorArtefact*)m_SlotArtef_vec[i]->item())->GetProtection();
                    break;
                }
                }
            }
        }
    }

    if (model()->properties().artefact_gravity > 0)
    {
        UpdatePropertiesSpeed();
    }

    if (model()->properties().artefact_protection > 0)
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
//    if (model()->properties().radar > VISIBLE_DISTANCE_WITHOUT_RADAR)
//    {
//        m_SlotRadar->UpdateRange(GuiTextureObCollector::Instance().dot_yellow);
//        m_SlotRadar->DrawRange(meti::vec2(center()));
//    }
//}

//void Vehicle::RenderGrappleRange()
//{
//    if (model()->properties().grab_radius > 0)
//    {
//        m_SlotGrapple->UpdateRange(GuiTextureObCollector::Instance().dot_blue);
//        m_SlotGrapple->DrawRange(meti::vec2(center()));
//    }
//}

bool Vehicle::isAbleToJumpTo(model::Starsystem* target_starsystem) const
{
    assert(false);
//    float dist = meti::distance(starsystem()->position(), target_starsystem->position());
//    if (dist < model()->properties().hyper) {
//        return true;
//    }

    return false;
}

void Vehicle::repairKorpus(int amount)
{
    model()->addArmor(amount);
    if (model()->armor() > descriptor()->armor()) {
        model()->setArmor(descriptor()->armor());
    }
}

bool Vehicle::isArmorFull() const
{
    if (model()->armor() == descriptor()->armor()) {
        return true;
    }

    return false;
}

int Vehicle::armorMiss() const
{
    return (descriptor()->armor() - model()->armor());
}

bool Vehicle::isFuelFull() const
{
    assert(false);
//    if (!model()->driveComplex().bakSlot()->item()) {
//        return true;
//    }

    if (fuelMiss() == 0) {
        return true;
    }


    return false;
}

int Vehicle::fuelMiss() const
{
    assert(false);
//    return model()->driveComplex().bakSlot()->bakEquipment()->fuelMiss();
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
        unsigned int _rand = meti::getRandInt(_equiped_slot_vec.size());
        _equiped_slot_vec[_rand]->item()->doLock(locked_turns);
    }
}

bool Vehicle::tryConsumeEnergy(int energy)
{
#ifdef USE_EXTRA_EQUIPMENT
    //LOG("Vehicle("+std::to_string(id())+")::TryToConsumeEnergy(energy="+std::to_string(energy)+")");

    if (model()->properties().energy > energy)
    {
        model()->properties().energy -= energy;
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
    if (model()->properties().energy < energy_max)
    {
        int diff_energy = energy_max - model()->properties().energy;
        if ( diff_energy < energy)
        {
            energy = diff_energy;
        }

        model()->properties().energy += energy;
        m_SlotEnergizer->energizerEquipment()->IncreaseEnergy(energy);

        if (model()->properties().hibernate_mode_enabled == true)
        {
            if (model()->properties().energy > HIBERNATION_ENERGY_THRESHOLD)
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
        assert(false);
//        if (m_grappleSlot->grappleEquipment()->isDamaged() == true)
//        {
//            status = STATUS::ITEM_DAMAGED;
//        }

//        if (m_grappleSlot->grappleEquipment()->isLocked() != 0)
//        {
//            status = STATUS::ITEM_LOCKED;
//        }
    }
    else
    {
        status = STATUS::ITEMSLOT_EMPTY;
    }

    return status;
}

bool Vehicle::dropItemToSpace(const entity::type& type)
{
    if (model()->place() != place::type::KOSMOS)
        return false;

    assert(false);
//    for (ItemSlot* slot: m_slots) {
//        if (slot->subtype() == type && slot->item()) {
//            item::Base* item = slot->takeItem();
//            Container* container = __wrapItemToContainer(item);
//            //    float impulse_strength = 0.5;
//            //    glm::vec3 impulse_dir(meti::getRandXYVec3Unit());
//            //    container->addImpulse(impulse_dir, impulse_strength);

//            starsystem()->add(container, position());
//            return true;
//        }
//    }

    return false;
}

model::Container*
Vehicle::__wrapItemToContainer(Item* item)
{
    model::Container* container = builder::Container::getNew();
    assert(false);
    //container->insertItem(item);

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
//        _equiped_slot_vec[meti::getRandInt(_equiped_slot_vec.size()-1)]->dropItemToSpace();
//    }
//}

void Vehicle::UpdateGrappleMicroProgram_inDynamic()
{
    assert(false);
//    if (model()->properties().grab_radius > 0) {
//        m_grappleSlot->grappleEquipment()->UpdateGrabScenarioProgram_inDynamic();
//    }
}

//void Vehicle::SaveData(boost::property_tree::ptree& save_ptree, const std::string& root) const
//{
//    //LOG(" Vehicle("+std::to_string(id())+")::SaveData");

//    save_ptree.put(root+"m_DataKorpus.space", m_vehicleDescriptor.space);
//    save_ptree.put(root+"m_DataKorpus.armor", m_vehicleDescriptor.armor);
//    save_ptree.put(root+"m_DataKorpus.protection", m_vehicleDescriptor.protection);
//    save_ptree.put(root+"m_DataKorpus.temperature", m_vehicleDescriptor.temperature);

//    save_ptree.put(root+"m_DataKorpus.price", m_vehicleDescriptor.price);
//    save_ptree.put(root+"m_DataKorpus.draw_turrels", m_vehicleDescriptor.draw_turrels);

//    save_ptree.put(root+"m_DataKorpus.slot_grapple_num", m_vehicleDescriptor.slot_grapple_num);
//    save_ptree.put(root+"m_DataKorpus.slot_drive_num", m_vehicleDescriptor.slot_drive_num);
//    save_ptree.put(root+"m_DataKorpus.slot_protector_num", m_vehicleDescriptor.slot_protector_num);
//    save_ptree.put(root+"m_DataKorpus.slot_radar_num", m_vehicleDescriptor.slot_radar_num);
//    save_ptree.put(root+"m_DataKorpus.slot_scaner_num", m_vehicleDescriptor.slot_scaner_num);
//    save_ptree.put(root+"m_DataKorpus.slot_freezer_num", m_vehicleDescriptor.slot_freezer_num);
//    save_ptree.put(root+"m_DataKorpus.slot_weapon_num", m_vehicleDescriptor.slot_weapon_num);


//    if (m_driveComplex.target() != nullptr)
//    {
//        save_ptree.put(root+"data_unresolved_Vehicle.drive_complex_target_id", m_driveComplex.target()->id());
//        save_ptree.put(root+"data_unresolved_Vehicle.drive_complex_action_id", m_driveComplex.GetActionId());
//    }
//    else
//    {
//        save_ptree.put(root+"data_unresolved_Vehicle.drive_complex_target_id", NONE);
//        save_ptree.put(root+"data_unresolved_Vehicle.drive_complex_action_id", NONE);
//    }

//    if (m_Land != nullptr)  { save_ptree.put(root+"data_unresolved_Vehicle.land_id", m_Land->id()); }
//    else                     { save_ptree.put(root+"data_unresolved_Vehicle.land_id", NONE); }

//    if (m_parentVehicleSlot != nullptr) { save_ptree.put(root+"data_unresolved_Vehicle.parent_vehicleslot_id", m_parentVehicleSlot->id()); }
//    else                                     { save_ptree.put(root+"data_unresolved_Vehicle.parent_vehicleslot_id", NONE); }

//    if (place() == type::place::HYPER)
//    {
//        save_ptree.put(root+"data_unresolved_Vehicle.starsystem_hyper_id", m_driveComplex.target()->id());
//    }
//    else
//    {
//        save_ptree.put(root+"data_unresolved_Vehicle.starsystem_hyper_id", NONE);
//    }
//}

//void Vehicle::LoadData(const boost::property_tree::ptree& load_ptree)
//{
//    //LOG(" Vehicle("+std::to_string(id())+")::LoadData");

//    m_vehicleDescriptor.space       = load_ptree.get<int>("m_DataKorpus.space");
//    m_vehicleDescriptor.armor       = load_ptree.get<int>("m_DataKorpus.armor");
//    m_vehicleDescriptor.protection  = load_ptree.get<int>("m_DataKorpus.protection");
//    m_vehicleDescriptor.temperature = load_ptree.get<int>("m_DataKorpus.temperature");

//    m_vehicleDescriptor.price        = load_ptree.get<int>("m_DataKorpus.price");
//    m_vehicleDescriptor.draw_turrels = load_ptree.get<bool>("m_DataKorpus.draw_turrels");

//    m_vehicleDescriptor.slot_grapple_num   = load_ptree.get<int>("m_DataKorpus.slot_grapple_num");
//    m_vehicleDescriptor.slot_drive_num     = load_ptree.get<int>("m_DataKorpus.slot_drive_num");
//    m_vehicleDescriptor.slot_protector_num = load_ptree.get<int>("m_DataKorpus.slot_protector_num");
//    m_vehicleDescriptor.slot_radar_num     = load_ptree.get<int>("m_DataKorpus.slot_radar_num");
//    m_vehicleDescriptor.slot_scaner_num    = load_ptree.get<int>("m_DataKorpus.slot_scaner_num");
//    m_vehicleDescriptor.slot_freezer_num   = load_ptree.get<int>("m_DataKorpus.slot_freezer_num");
//    m_vehicleDescriptor.slot_weapon_num    = load_ptree.get<int>("m_DataKorpus.slot_weapon_num");

//    data_unresolved_Vehicle.drive_complex_target_id   = load_ptree.get<int>("data_unresolved_Vehicle.drive_complex_target_id");
//    data_unresolved_Vehicle.drive_complex_action_id   = load_ptree.get<int>("data_unresolved_Vehicle.drive_complex_action_id");
//    //data_unresolved_Vehicle.textureOb_gui_path = load_ptree.get<std::string>("data_unresolved_Vehicle.textureOb_gui_path");
//    data_unresolved_Vehicle.parent_vehicleslot_id = load_ptree.get<int>("data_unresolved_Vehicle.parent_vehicleslot_id");
//    data_unresolved_Vehicle.land_id = load_ptree.get<int>("data_unresolved_Vehicle.land_id");
//    data_unresolved_Vehicle.starsystem_hyper_id = load_ptree.get<int>("data_unresolved_Vehicle.starsystem_hyper_id");

//}

//void Vehicle::ResolveData()
//{
//    //LOG(" Vehicle("+std::to_string(id())+")::ResolveData");

//    CreateDriveComplexTextureDependedStuff();
//    CreateProtectionComplexTextureDependedStuff();

//    if (data_unresolved_Vehicle.drive_complex_target_id != NONE)
//    {
//        m_driveComplex.SetTarget((SpaceObject*)core::global::get().entityManager().getEntity(data_unresolved_Vehicle.drive_complex_target_id),  data_unresolved_Vehicle.drive_complex_action_id);
//    }

//    if (data_unresolved_Vehicle.land_id != NONE)
//    {
//        setLand( (Land*)core::global::get().entityManager().getEntity(data_unresolved_Vehicle.land_id) );
//    }

//    switch(place())
//    {
//    case type::place::KOSMOS:
//    {
//        //starsystem()->add(this, data_unresolved_Orientation.center, data_unresolved_Orientation.direction, parent());
//        break;
//    }

//    case type::place::KOSMOPORT:
//    {
//        ((VehicleSlot*)core::global::get().entityManager().getEntity(data_unresolved_Vehicle.parent_vehicleslot_id ))->InsertVehicle(this);
//        break;
//    }

//    case type::place::HYPER:
//    {
//        //std::cout<<"xxx="<<data_unresolved_Vehicle.starsystem_hyper_id<<std::endl;
//        ((Starsystem*)core::global::get().entityManager().getEntity(data_unresolved_Vehicle.starsystem_hyper_id))->hyperSpace().AddVehicle(this);
//        //std::cout<<"yyy="<<data_unresolved_Vehicle.starsystem_hyper_id<<std::endl;

//        break;
//    }

//    case type::place::LAND:
//    {
//        ((NatureLand*)core::global::get().entityManager().getEntity(data_unresolved_Vehicle.land_id))->AddVehicle(this);
//        break;
//    }
//    }

//    m_weaponComplex.prepareWeapons();
//}

//void Vehicle::TEST_DamageAndLockRandItems()
//{
//    int rand_index1 = meti::getRandInt(m_equipmentSlots.size()-1);
//    while (m_equipmentSlots[rand_index1]->item() == nullptr)
//    {
//        rand_index1 = meti::getRandInt(m_equipmentSlots.size()-1);
//    }
//    m_equipmentSlots[rand_index1]->item()->doLock(3);

//    int rand_index2 = meti::getRandInt(m_equipmentSlots.size()-1);
//    while (m_equipmentSlots[rand_index2]->item() == nullptr)
//    {
//        rand_index2 = meti::getRandInt(m_equipmentSlots.size()-1);
//    }

//    while (m_equipmentSlots[rand_index2]->item()->condition() > 0)
//    {
//        m_equipmentSlots[rand_index2]->item()->deteriorationEvent();
//    }
//}

} // namespace control


























//Vehicle::Vehicle()
//    :
//      m_godMode(false),
//      m_specialActionId(VEHICLE_SPECIAL_ACTION_TYPE::NONE),
//      m_npc(nullptr),
//      m_parentVehicleSlot(nullptr),
//      m_Land(nullptr),
//      m_radarSlot(nullptr),
//      m_scanerSlot(nullptr),
//      #ifdef USE_EXTRA_EQUIPMENT
//      m_energizerSlot(nullptr),
//      m_freezerSlot(nullptr),
//      #endif // USE_EXTRA_EQUIPMENT
//      m_grappleSlot(nullptr),
//      m_droidSlot(nullptr),
//      m_weaponComplex(this)
//{
//    m_driveComplex.SetOwnerVehicle(this);
//    m_protectorComplex.SetOwnerVehicle(this);
//}

///* virtual */
//Vehicle::~Vehicle()
//{
//    LOG("___::~Vehicle("+std::to_string(id())+")");
//}

///* virtual override */
//void Vehicle::putChildrenToGarbage() const
//{
//    m_npc->setAlive(false);
//   core::global::get().entityManager().addToGarbage(m_npc);

//    for(ItemSlot* slot: m_slots) {
//       core::global::get().entityManager().addToGarbage(slot);
//    }
//}

//// weapon complex interface
//void Vehicle::fire(int timer, float attack_rate)
//{
//    weaponComplex().fire(timer, attack_rate, false);
//}

//void Vehicle::setWeaponTarget(SpaceObject* object, ItemSlot* slot)
//{
//    weaponComplex().setTarget(object, slot);
//}

//void Vehicle::prepareWeapons()
//{
//    weaponComplex().prepareWeapons();
//}

//int Vehicle::guessDamage(int dist)
//{
//    return weaponComplex().guessDamage(dist);
//}

////\ weapon complex interface

//void Vehicle::CreateDriveComplexTextureDependedStuff()
//{
//    points().addMidLeftPoint();
//    points().addMidFarLeftPoint();

//    //DriveEffect* drive_effect = GetNewDriveEffect(textureOb().GetData().size_id, points().GetpMidLeft(), points().GetpMidFarLeft());
//    //m_ComplexDrive.SetDriveEffect(drive_effect);
//}

//void Vehicle::CreateProtectionComplexTextureDependedStuff()
//{
//    //    m_ComplexProtector.GetShieldEffect()->setParent(this);
//}

//void Vehicle::setKorpusData(descriptor::Vehicle* korpus_data)
//{
//    m_vehicleDescriptor = korpus_data;
//    m_properties.protection = m_vehicleDescriptor.protection;
//}

//GoodsPack* Vehicle::goodsPack() const
//{
//    for(ItemSlot* slot: m_cargoSlots) {
//        if (slot->item()) {
//            if (slot->item()->type() == entity::Type::GOODS) {
//                return slot->goodsPack();
//            }
//        }
//    }
//    return nullptr;
//}

///* virtual override final */
//int Vehicle::givenExpirience() const
//{
//    return m_npc->skills().expirience() * GIVEN_EXPIRIENCE_RATE_DEPENDING_ON_NPC_EXPIRIENCE;
//}

//bool Vehicle::isSlotTypePresent(const entity::Type& slot_subtype_id) const
//{
//    for (ItemSlot* slot: m_slots) {
//        if (slot->subtype() == slot_subtype_id) {
//            return true;
//        }
//    }
//    return false;
//}

//void Vehicle::addItemSlot(ItemSlot* slot)
//{
//    slot->setOwner(this);

//    switch(slot->subtype())
//    {
//    case entity::Type::WEAPON_SLOT:
//    {
//        float border_start = 0.2;
//        float border_end   = 0.8;

//        float pos_x = meti::getRandFloat(border_start, border_end) - 0.5;
//        float pos_y = meti::getRandFloat(border_start, border_end) - 0.5;

//        slot->turrel()->setParentPosition(pos_x, pos_y, DEFAULT_ENTITY_ZPOS);
//        //points().add(slot->turrel()->pPosition(), slot->turrel()->pParentPosition());
//        m_weaponComplex.addSlot(slot);

//        break;
//    }
//    case entity::Type::DRIVE_SLOT:     { m_driveComplex.SetDriveSlot(slot); break; }
//    case entity::Type::BAK_SLOT:       { m_driveComplex.SetBakSlot(slot); break; }
//    case entity::Type::PROTECTOR_SLOT: { m_protectorComplex.SetProtectorSlot(slot); break; }
//    case entity::Type::RADAR_SLOT:     { m_radarSlot  = slot; break; }
//    case entity::Type::SCANER_SLOT:    { m_scanerSlot = slot; break; }
//#ifdef USE_EXTRA_EQUIPMENT
//    case entity::Type::ENERGIZER_SLOT: { m_energizerSlot = slot; break; }
//    case entity::Type::FREEZER_SLOT:   { m_freezerSlot   = slot; break; }
//#endif // USE_EXTRA_EQUIPMENT
//    case entity::Type::GRAPPLE_SLOT:   { m_grappleSlot   = slot; break; }
//    case entity::Type::DROID_SLOT:     { m_droidSlot     = slot; break; }
//    }

//    m_slots.push_back(slot);

//    if ( (slot->subtype() != entity::Type::ARTEFACT_SLOT) and (slot->subtype() != entity::Type::CARGO_SLOT) ) {
//        m_equipmentSlots.push_back(slot);
//    }

//    if (slot->subtype() == entity::Type::ARTEFACT_SLOT) {
//        m_artefactSlots.push_back(slot);
//    }

//    if (slot->subtype() == entity::Type::CARGO_SLOT) {
//        m_cargoSlots.push_back(slot);
//    }
//}

//bool Vehicle::grabItemsFromVehicle(Vehicle* vehicle)
//{
//    bool result = true;
//    for(ItemSlot* slot: vehicle->m_slots) {
//        if (slot->item()) {
//            if (slot->subtype() == entity::Type::CARGO_SLOT) {
//                result = addItemToCargoSlot(slot->item());
//            } else {
//                result = manage(slot->item());
//            }
//        }
//    }
//    return result;
//}

//bool Vehicle::_installItem(item::Base* item)
//{
//    switch(item->type()) {
//    case entity::Type::EQUIPMENT:    { return _installEquipment(item); break; }
//#ifdef USE_MODULES
//    case entity::Type::MODULE:       { return _installModule(item); break; }
//#endif
//#ifdef USE_ARTEFACTS
//    case entity::Type::ARTEFACT:     { return _installArtefact(item); break; }
//#endif
//    case entity::Type::GOODS:        { return _installGoodsPack(item); break; } // what??
//    }
//    return false;
//}

//bool Vehicle::isSlotFree(const entity::Type& subtype) const
//{
//    for (ItemSlot* slot: m_slots) {
//        if (slot->subtype() == subtype) {
//            if (slot->isEmpty()) {
//                return true;
//            }
//        }
//    }
//    return false;
//}

//bool Vehicle::checkManage(const core::Id& ident)
//{
//    if (!isSlotTypePresent(ident.subtype)) {
//        return false;
//    }

//    switch(ident.type) {
//    case entity::Type::EQUIPMENT:    { return _checkInstallEquipment(ident); break; }
////#ifdef USE_MODULES
////    case entity::Type::MODULE:       { return _checkInstallModule(type); break; }
////#endif
////#ifdef USE_ARTEFACTS
////    case entity::Type::ARTEFACT:     { return _checkInstallArtefact(type); break; }
////#endif
////    case entity::Type::GOODS:        { return _checkInstallGoodsPack(type); break; }
//    }
//    return false;
//}

//bool Vehicle::_installGoodsPack(item::Base* item)
//{
//    return __mergeIdenticalGoods(item);
//}

//bool Vehicle::_installEquipment(item::Base* item)
//{
//    if (item->parentSubtype() == entity::Type::WEAPON_SLOT) {
//        ItemSlot* slot = m_weaponComplex.freeSlot();
//        if (slot) {
//            return slot->swapItem(item->slot());
//        } else {
//            ItemSlot* slot = m_weaponComplex.equipedWeakestSlot();
//            if (slot) {
//                if (item->price() > slot->item()->price()) {
//                    return slot->swapItem(item->slot());
//                }
//            }
//        }
//    } else {
//        ItemSlot* slot = _functionalSlot(item->parentSubtype());
//        if (slot->item()) {
//            if (item->price() > slot->item()->price()) {
//                return slot->swapItem(item->slot());
//            }
//        } else {
//            return slot->swapItem(item->slot());
//        }
//    }

//    return false;
//}

//bool Vehicle::_checkInstallEquipment(const core::Id& ident)
//{
//    if (ident.type == entity::Type::WEAPON_SLOT) {
//        if (m_weaponComplex.freeSlot()) {
//            return true;
//        }
//    } else {
//        if (_freeFunctionalSlot(ident)) {
//            return true;
//        }
//    }

//    if (freeCargoSlot()) {
//        return true;
//    }

//    return false;
//}

//#ifdef USE_MODULES
//bool Vehicle::installModule(item::Base* item)
//{
//    for (unsigned int i=0; i<m_SlotFunct_vec.size(); i++) {
//        if (m_SlotFunct_vec[i]->item()) {
//            if (m_SlotFunct_vec[i]->item()->subTypeId() == item->parentSubTypeId()) {
//                return ((Equipment*)m_SlotFunct_vec[i]->item())->InsertModule((BaseModule*)item);
//            }
//        }
//    }
//    return false;
//}
//#endif

//#ifdef EANBLE_ARTEFACTS
//bool Vehicle::installArtefact(item::Base* item)
//{
//    ItemSlot* artef_slot = GetEmptyArtefactSlot();
//    if (artef_slot) {
//        return artef_slot->swapItem(item->itemSlot());
//    }

//    return false;
//}
//#endif

//ItemSlot* const
//Vehicle::_functionalSlot(const entity::Type& functional_slot_subtype_id) const
//{
//    for(ItemSlot* slot: m_equipmentSlots) {
//        if (slot->subtype() == functional_slot_subtype_id) {
//            return slot;
//        }
//    }
//    return nullptr;
//}

//ItemSlot* const
//Vehicle::_freeFunctionalSlot(const core::Id& ident) const
//{
//    for(ItemSlot* slot: m_equipmentSlots) {
//        if (slot->subtype() == ident.subtype) {
//            if (slot->isEmpty()) {
//                return slot;
//            }
//        }
//    }
//    return nullptr;
//}

//ItemSlot* const
//Vehicle::_freeArtefactSlot() const
//{
//    for(ItemSlot* slot: m_artefactSlots) {
//        if (!slot->item()) {
//            return slot;
//        }
//    }
//    return nullptr;
//}

//ItemSlot* const Vehicle::freeCargoSlot()
//{
//    for (ItemSlot* slot: m_cargoSlots) {
//        if (!slot->item()) {
//            return slot;
//        }
//    }
//    return nullptr;
//}

//ItemSlot* const Vehicle::_cargoSlotWithGoods(entity::Type requested_goods_subtype_id)
//{
//    for (ItemSlot* slot: m_cargoSlots) {
//        if (slot->item()) {
//            if (slot->item()->type() == entity::Type::GOODS) {
//                if (slot->item()->subtype() == requested_goods_subtype_id) {
//                    return slot;
//                }
//            }
//        }
//    }
//    return nullptr;
//}

//bool Vehicle::unpackContainerItemToCargoSlot(Container* container)
//{
//    if (addItemToCargoSlot(container->itemSlot()->item()) == true)
//    {
//        container->killSilently();

//        return true;
//    }

//    return false;
//}

//bool Vehicle::addItemToCargoSlot(item::Base* item)
//{
//    _increaseMass(item->mass());
//    if (item->type() == entity::Type::GOODS) {
//        if (_installGoodsPack(item)) {
//            return true;
//        }
//    }

//    ItemSlot* slot = freeCargoSlot();
//    if (slot) {
//        return slot->insert(item);
//    }

//    return false;
//}

//bool
//Vehicle::manage(item::Base* item)
//{
//    if (addItemToCargoSlot(item)) {
//        _installItem(item);
//        return true;
//    }
//    return false;
//}

//void Vehicle::manageItemsInCargo()
//{
//    for (unsigned int i=0; i<m_cargoSlots.size(); i++) {
//        if (m_cargoSlots[i]->item()) {
//            _installItem(m_cargoSlots[i]->item());
//        }
//    }
//}

//void Vehicle::sellItemsInCargo()
//{
//    for (unsigned int i=0; i<m_cargoSlots.size(); i++) {
//        if (m_cargoSlots[i]->item()) {
//            sellItem(m_cargoSlots[i]->item());
//        }
//    }
//}

//bool Vehicle::sellItem(item::Base* item)
//{
//    //float skill_rate = 1.0f + sign*0.1*npc->GetSkill().GetTrader();
//    //npc->IncreaseCredits(sign*amount*skill_rate*minerals_price);
//    int earn_money = 0;
//    int item_mass = item->mass();
//    switch(item->type())
//    {
//    case entity::Type::GOODS:
//    {
//        earn_money = ((Kosmoport*)m_Land)->GetShop()->BuyGoods((GoodsPack*)item);
//        break;
//    }

//    case entity::Type::EQUIPMENT:
//    {
//        earn_money = ((Kosmoport*)m_Land)->GetStore()->buyItem(item);
//        break;
//    }
//    }

//    if (earn_money > 0)
//    {
//        _decreaseMass(item_mass);
//        m_npc->increaseCredits(earn_money);

//        return true;
//    }
//    else
//    {
//        return false;
//    }
//}

//bool Vehicle::buyItem(item::Base* item)
//{
//    if (addItemToCargoSlot(item) == true)
//    {
//        m_npc->increaseCredits(-item->price());

//        return true;
//    }

//    return false;
//}

//bool Vehicle::__mergeIdenticalGoods(item::Base* item)
//{
//    ItemSlot* item_slot = _cargoSlotWithGoods(item->subtype());
//    if (item_slot != nullptr)
//    {
//        item_slot->goodsPack()->Increase(item->mass());
//        // delete item; dangerrr
//        return true;
//    }

//    return false;
//}

//void Vehicle::bindNpc(Npc* owner_npc)
//{
//    m_npc = owner_npc;
//    m_npc->setVehicle(this);
//}

//bool Vehicle::isObjectVisible(SpaceObject* object) const
//{
////    float dist = meti::distance(position(), object->position());
////    if (dist < model()->properties().radar)
////    {
////        return true;
////    }

////    return false;
//}

//void Vehicle::UpdateSpecialAction()
//{
//    switch(m_specialActionId)
//    {
//    case VEHICLE_SPECIAL_ACTION_TYPE::NONE: { break; }

//    case VEHICLE_SPECIAL_ACTION_TYPE::INITIATE_DOCKING:
//    {
//        // alpitodorender if (UpdateFadeInEffect() == true)
//        {
//            DockingEvent();
//            m_specialActionId = VEHICLE_SPECIAL_ACTION_TYPE::NONE;
//        }

//        break;
//    }

//    case VEHICLE_SPECIAL_ACTION_TYPE::INITIATE_LAUNCHING:
//    {
//        // alpitodorender if (UpdateFadeOutEffect() == true)
//        {
//            m_specialActionId = VEHICLE_SPECIAL_ACTION_TYPE::NONE;
//        }

//        break;
//    }

//    case VEHICLE_SPECIAL_ACTION_TYPE::INITIATE_JUMPIN:
//    {
//        // alpitodorender if (UpdateFadeInEffect() == true)
//        {
//            HyperJumpEvent(m_driveComplex.target()->starsystem());
//        }

//        break;
//    }

//    case VEHICLE_SPECIAL_ACTION_TYPE::INITIATE_JUMPOUT:
//    {
//        // alpitodorender if (UpdateFadeOutEffect() == true)
//        {
//            m_specialActionId = VEHICLE_SPECIAL_ACTION_TYPE::NONE;
//        }

//        break;
//    }
//    }
//}

////// ******** dock/LAUNCHING ********
//void Vehicle::HyperJumpEvent(Starsystem* starsystem)
//{
//    //LOG("Vehicle("+std::to_string(id())+")::HyperJumpEvent");

//    m_weaponComplex.deactivateWeapons();

//    m_specialActionId = VEHICLE_SPECIAL_ACTION_TYPE::INITIATE_JUMPOUT;
//    starsystem->hyperSpace().AddVehicle(this);
//}


//void Vehicle::DockingEvent()
//{
//    //LOG("Vehicle("+std::to_string(id())+")::DockingEvent");

//    m_weaponComplex.deactivateWeapons();

//    switch(m_driveComplex.target()->type())
//    {
//    case entity::Type::PLANET:
//    {
////        Planet* planet = ((Planet*)m_driveComplex.target());
////        planet->GetLand()->AddVehicle(this);

//        break;
//    }

//    case entity::Type::VEHICLE:
//    {
//        switch(m_driveComplex.target()->subtype())
//        {
//        case entity::Type::SPACESTATION:
//        {
//            assert(false);
//            //SpaceStation* spacestation = ((SpaceStation*)m_driveComplex.target());
//            //spacestation->land()->AddVehicle(this);

//            break;
//        }

//        case entity::Type::SHIP:
//        {
//            //..
//            break;
//        }
//        }

//        break;
//    }
//    }

//    m_driveComplex.ResetTarget();
//}

//void Vehicle::LaunchingEvent()
//{
//    //LOG("Vehicle("+std::to_string(id())+")::LaunchingEvent");

//   /* if (m_parentVehicleSlot != nullptr)
//    {
//        switch(m_parentVehicleSlot->owner()->typeId())
//        {
//        case entity::Type::ANGAR:
//        {
//            int angleInD = meti::getRandInt(360);
//            glm::vec2 offset_pos = meti::getRandVec2f(40, 100);
//            glm::vec3 offset_pos3(offset_pos.x, offset_pos.y, DEFAULT_ENTITY_ZPOS);
//            glm::vec3 angle(0,0,angleInD);
//            starsystem()->add(this, ((SpaceObject*)m_Land->GetOwner())->center() + offset_pos3, angle, nullptr);
//            m_Land->RemoveVehicle(this);

//            break;
//        }

//        case entity::Type::VEHICLE:
//        {
//            //..
//            break;
//        }
//        }
//    }
//    else
//    {
//        int angleInD = meti::getRandInt(360);
//        glm::vec2 offset_pos = meti::getRandVec2f(40, 100);
//        glm::vec3 offset_pos3(offset_pos.x, offset_pos.y, DEFAULT_ENTITY_ZPOS);
//        glm::vec3 angle(0,0,angleInD);
//        starsystem()->add(this, ((SpaceObject*)m_Land->GetOwner())->center() + offset_pos3, angle, nullptr);
//        m_Land->RemoveVehicle(this);
//    }

//    SetSpecialActionId(VEHICLE_SPECIAL_ACTION_TYPE::INITIATE_LAUNCHING);
//    // alpitodorender SetTransparency(0.1);*/
//}

///* virtual */
//void Vehicle::remeberAgressor(Vehicle* agressor)
//{
////    m_npc->remeberAgressor(agressor);
//}


//float Vehicle::adjustDissipateFilter() const
//{
////    float rate = 1.0f - model()->properties().protection*0.01f;
////    //    if (m_npc) {
////    //        rate *= m_npc->GetSkills().GetDefenceNormalized();
////    //    }
////    //std::cout<<"---rate="<<rate<<std::endl;
////    assert(rate > 0 && rate <= 1.0f);
////    return rate;
//}

//int Vehicle::criticalDamage() const {
//    return 2*armor();
//}

///* virtual */
//void Vehicle::hit(int damage)
//{
////    LOG(std::string("Vehicle::hit id=") << std::to_string(id()) << " damage=" << std::to_string(damage));
////    if (m_godMode)
////        return;

////#ifdef USE_EXTRA_EQUIPMENT
////    if (model()->properties().energy < damage) {
////        model()->properties().hibernate_mode_enabled = true;
////        _updatePropProtection();
////    }
////#endif

////    SpaceObject::hit(damage * adjustDissipateFilter());

////    //if (show_effect == true)
////    {
////        //if (m_ComplexProtector.GetProtectorSlot()->item() != nullptr)
////        {
////            //m_ComplexProtector.GetShieldEffect()->SetAlpha(1.0);
////        }

////        //VerticalFlowText* text = new VerticalFlowText(std::to_string(damage), 12, meti::vec2(center()), COLOR::COLOR4I_RED_LIGHT, collisionRadius());
////        //starsystem()->Add(text);
////    }
//}

///* virtual */
//void Vehicle::_postDeathUniqueEvent(bool show_effect)
//{
////    int num_items = meti::getRandInt(3);
////    for (int i = 0; i<num_items; i++)
////    {
////        //__dropRandomItemToSpace();
////    }

////    if (show_effect == true)
////    {
////        //        jeti::ExplosionEffect* explosion = jeti::getNewExplosionEffect(collisionRadius());
////        //        starsystem()->Add(explosion, center());
////    }
//}


//void Vehicle::CheckNeedsInStatic()
//{
////    // check armor
////    if (_dataLife().armor < 0.5*m_vehicleDescriptor.armor)    { m_needs.repair_korpus = true; }
////    else                                                { m_needs.repair_korpus = false; }

////    //check item damages
////    m_needs.repair_equipment = false;
////    for (ItemSlot* slot: m_equipmentSlots) {
////        if (slot->item()) {
////            if (slot->item()->isDamaged()) {
////                m_needs.repair_equipment = true;
////            }
////        }
////    }

////    //check ammo
////    m_needs.get_ammo = false;
////    for (ItemSlot* slot: m_equipmentSlots) {
////        if (slot->item()) {
////            if (slot->item()->subtype() == entity::Type::ROCKET_EQUIPMENT) {
////                if (slot->rocketEquipment()->GetAmmo() == 0) {
////                    m_needs.get_ammo = true;
////                }
////            }
////        }
////    }

////    // check fuel
////    m_needs.get_fuel = false;
////    if (m_driveComplex.bakSlot()) {
////        if (m_driveComplex.bakSlot()->item()) {
////            if (m_driveComplex.bakSlot()->bakEquipment()->fuel() < 0.8*m_driveComplex.bakSlot()->bakEquipment()->fuelMax()) {
////                m_needs.get_fuel = true;
////            }
////        }
////    }

////    // check credits
////    if (m_npc->credits() < 1000)    { m_needs.get_credits = true; }
////    else                                    { m_needs.get_credits = false; }
//}


//void Vehicle::ResolveNeedsInKosmoportInStatic()
//{
////    bool result = true;

////    // buy repair korpus
////    if ( (m_needs.repair_korpus == true) and (result == true) )
////    {
////        result = ((Angar*)m_parentVehicleSlot->owner())->RepairVehicle(this);
////    }

////    // repair equipment
////    if ( (m_needs.repair_equipment == true) && (result == true) ) {
////        for (unsigned int i=0; i<m_equipmentSlots.size(); i++) {
////            if (m_equipmentSlots[i]->item()) {
////                if (m_equipmentSlots[i]->item()->isDamaged() == true) {
////                    result = ((Angar*)m_parentVehicleSlot->owner())->RepairItem(m_npc, m_equipmentSlots[i]->item());
////                }
////            }
////        }
////    }

////    // buy ammo
////    if ( (m_needs.get_ammo == true) && (result == true) ) {
////        for (ItemSlot* slot: m_equipmentSlots) {
////            if (slot->item()) {
////                if (slot->item()->subtype() == entity::Type::ROCKET_EQUIPMENT) {
////                    result = ((Angar*)m_parentVehicleSlot->owner())->chargeRocketEquipment(m_npc, slot->rocketEquipment());
////                }
////            }
////        }
////    }

////    // tank up
////    if ( (m_needs.get_fuel == true) and (result == true) ) {
////        result = ((Angar*)m_parentVehicleSlot->owner())->TankUpVehicle(this);
////    }

////    //// check credits
////    //if (m_OwnerNpc->GetCredits() < 1000) { m_Needs.get_credits = true; }
////    //else                                { m_Needs.get_credits = false; }
//}

//void Vehicle::UpdateAllFunctionalItemsInStatic()
//{
////    for (unsigned int i=0; i<m_equipmentSlots.size(); i++) {
////        if (m_equipmentSlots[i]->item()) {
////            m_equipmentSlots[i]->item()->updateInStatic();
////        }
////    }

////    for (unsigned int i=0; i<m_artefactSlots.size(); i++) {
////        if (m_artefactSlots[i]->item()) {
////            m_artefactSlots[i]->item()->updateInStatic();
////        }
////    }
//}

//void Vehicle::_increaseMass(int d_mass)
//{
//    //LOG("Vehicle("+std::to_string(id())+")::IncreaseMass");

////    _addMass(d_mass);
////    model()->properties().free_space = m_vehicleDescriptor.space - mass();
////    _updatePropSpeed(); // as the mass influence speed this action is necessary here
//}

//void Vehicle::_decreaseMass(int d_mass)
//{
//    //LOG("Vehicle("+std::to_string(id())+")::DecreaseMass");

////    _addMass(-d_mass);
////    model()->properties().free_space = m_vehicleDescriptor.space - mass();
////    _updatePropSpeed(); // as the mass influence speed this action is necessary here
//}

//void Vehicle::_updatePropSpeed()
//{
////    //LOG("Vehicle("+std::to_string(id())+")::UpdatePropertiesSpeed");
////    model()->properties().speed = 0;
////    if (!m_driveComplex.driveSlot())
////        return;
////    if (!m_driveComplex.driveSlot()->item())
////        return;
////    if (!m_driveComplex.driveSlot()->driveEquipment()->isFunctioning())
////        return;

////    float actual_speed = (m_driveComplex.driveSlot()->driveEquipment()->speed() - mass()*MASS_DECREASE_SPEED_RATE);
////    if (actual_speed > 0) {
////        if (model()->properties().artefact_gravity > 0) {
////            model()->properties().speed = (1.0 + model()->properties().artefact_gravity/100.0)*actual_speed;
////        } else {
////            model()->properties().speed = actual_speed;
////        }

////        if (m_driveComplex.driveSlot()->isSelected() == true) {
////            model()->properties().speed *= EQUIPMENT::DRIVE::OVERLOAD_RATE;
////            m_driveComplex.driveSlot()->item()->useOverloadDeterioration();
////        } else {
////            m_driveComplex.driveSlot()->item()->useNormalDeterioration();
////        }
////        m_driveComplex.UpdatePath();
////    }
//}

//void Vehicle::_updatePropFire()
//{
////    //LOG("Vehicle("+std::to_string(id())+")::UpdatePropertiesFire");

////    m_weaponComplex.updateFireAbility();

////    model()->properties().total_damage = m_weaponComplex.damage();
////    model()->properties().fire_radius_min = m_weaponComplex.radiusMin();
////    model()->properties().fire_radius_max = m_weaponComplex.radiusMax();
//}

//void Vehicle::_updatePropRadar()
//{
//    //LOG("Vehicle("+std::to_string(id())+")::UpdatePropertiesRadar");

////    model()->properties().radar = VISIBLE_DISTANCE_WITHOUT_RADAR;
////    model()->properties().equipment_radar = false;

////    if (!m_radarSlot->item())
////        return;

////    if (!m_radarSlot->radarEquipment()->isFunctioning())
////        return;

////    model()->properties().radar = m_radarSlot->radarEquipment()->radius();
////    model()->properties().equipment_radar = true;
//}

//void Vehicle::_updatePropJump()
//{
////    //LOG("Vehicle("+std::to_string(id())+")::UpdatePropertiesJump");

////    model()->properties().hyper = 0;

////    if (!m_driveComplex.driveSlot())
////        return;
////    if (!m_driveComplex.driveSlot()->item())
////        return;
////    if (!m_driveComplex.driveSlot()->driveEquipment()->isFunctioning())
////        return;
////    if (!m_driveComplex.bakSlot())
////        return;
////    if (!m_driveComplex.bakSlot()->item())
////        return;
////    if (!m_driveComplex.bakSlot()->bakEquipment()->isFunctioning())
////        return;

////    model()->properties().hyper = std::min(m_driveComplex.driveSlot()->driveEquipment()->hyper(), m_driveComplex.bakSlot()->bakEquipment()->fuel());
//}

//void Vehicle::_updatePropProtection()
//{
//    //LOG("Vehicle("+std::to_string(id())+")::UpdatePropertiesProtection");

////    model()->properties().protection = m_vehicleDescriptor.protection;
////    model()->properties().shield_effect_enabled = false;

////    if (model()->properties().hibernate_mode_enabled == false)
////    {
////        if (m_protectorComplex.protectorSlot()->item() != nullptr)
////        {
////            if (m_protectorComplex.protectorSlot()->protectorEquipment()->isFunctioning() == true)
////            {
////                model()->properties().protection += m_protectorComplex.protectorSlot()->protectorEquipment()->protection();
////                model()->properties().shield_effect_enabled = true;
////            }
////        }
////    }

////    if (model()->properties().artefact_protection > 0)
////    {
////        model()->properties().protection += model()->properties().artefact_protection;
////    }
//}

//void Vehicle::_updatePropRepair()
//{
//    //LOG("Vehicle("+std::to_string(id())+")::UpdatePropertiesRepair");

////    model()->properties().repair = 0;

////    if (m_droidSlot->item() != nullptr)
////    {
////        if (m_droidSlot->droidEquipment()->isFunctioning() == true) {
////            model()->properties().repair = m_droidSlot->droidEquipment()->repair();
////        }
////    }
//}


//void Vehicle::increaseArmor(int repair)
//{
////    //LOG("Vehicle("+std::to_string(id())+")::IncreaseArmor");

////    _dataLife().armor += repair;

////    if (_dataLife().armor > m_vehicleDescriptor.armor)
////    {
////        _dataLife().armor = m_vehicleDescriptor.armor;
////    }
//}

//void Vehicle::_updatePropFreeze()
//{
////#ifdef USE_EXTRA_EQUIPMENT
////    //LOG("Vehicle("+std::to_string(id())+")::UpdatePropertiesFreeze");

////    model()->properties().freeze = 0;

////    if (m_SlotFreezer->item() != nullptr)
////    {
////        if (m_SlotFreezer->freezerEquipment()->isFunctioning() == true)
////        {
////            model()->properties().freeze = m_SlotFreezer->freezerEquipment()->GetFreeze();
////        }
////    }
////#endif
//}

//void Vehicle::_updatePropEnergy()
//{
////#ifdef USE_EXTRA_EQUIPMENT
////    //LOG("Vehicle("+std::to_string(id())+")::UpdatePropertiesEnergy");

////    model()->properties().energy = 0;
////    model()->properties().hibernate_mode_enabled = true;

////    if (m_SlotEnergizer->item() != nullptr)
////    {
////        if (m_SlotEnergizer->energizerEquipment()->isFunctioning() == true)
////        {
////            model()->properties().energy = m_SlotEnergizer->energizerEquipment()->GetEnergy();
////            model()->properties().hibernate_mode_enabled = false;
////        }
////    }

////    UpdatePropertiesProtection();
////#endif
//}



//void Vehicle::_updatePropScan()
//{
//    //LOG("Vehicle("+std::to_string(id())+")::UpdatePropertiesScan");

////    model()->properties().scan = 0;

////    if (m_scanerSlot->item() != nullptr)
////    {
////        if (m_scanerSlot->scanerEquipment()->isFunctioning() == true)
////        {
////            model()->properties().scan = m_scanerSlot->scanerEquipment()->scan();
////        }
////    }
//}

//void Vehicle::_updatePropGrab()
//{
//    //LOG("Vehicle("+std::to_string(id())+")::UpdatePropertiesGrab");

////    model()->properties().grab_strength = 0;
////    model()->properties().grab_radius = 0;

////    if (m_vehicleDescriptor.slot_grapple_num != 0)
////    {
////        if (m_grappleSlot->item() != nullptr)
////        {
////            if (m_grappleSlot->grappleEquipment()->isFunctioning() == true)
////            {
////                model()->properties().grab_strength = m_grappleSlot->grappleEquipment()->strength();
////                model()->properties().grab_radius = m_grappleSlot->grappleEquipment()->radius();
////            }
////        }
////    }
//}

//void Vehicle::_updateArtefactInfluence()
//{
////#ifdef USE_ARTEFACTS
////    //LOG("Vehicle("+std::to_string(id())+")::UpdateArtefactInfluence");

////    model()->properties().artefact_gravity = 0;
////    model()->properties().artefact_protection = 0;

////    for (unsigned int i=0; i<m_SlotArtef_vec.size(); i++)
////    {
////        if (m_SlotArtef_vec[i]->item() != nullptr)
////        {
////            if (m_SlotArtef_vec[i]->item()->isFunctioning() == true)
////            {
////                switch(m_SlotArtef_vec[i]->item()->subTypeId())
////                {
////                case entity::Type::GRAVITY_ARTEFACT:
////                {
////                    model()->properties().artefact_gravity += ((GravityArtefact*)m_SlotArtef_vec[i]->item())->GetGravity();
////                    break;
////                }

////                case entity::Type::PROTECTOR_ARTEFACT:
////                {
////                    model()->properties().artefact_protection += ((ProtectorArtefact*)m_SlotArtef_vec[i]->item())->GetProtection();
////                    break;
////                }
////                }
////            }
////        }
////    }

////    if (model()->properties().artefact_gravity > 0)
////    {
////        UpdatePropertiesSpeed();
////    }

////    if (model()->properties().artefact_protection > 0)
////    {
////        UpdatePropertiesProtection();
////    }
////#endif
//}

/////* virtual override final */
////void Vehicle::RenderStuffWhenFocusedInSpace(const jeti::Renderer& render)
////{
////    m_ComplexWeapon.RenderWeaponIcons();

////    RenderRadarRange();
////    m_ComplexWeapon.RenderWeaponsRange();

////    m_ComplexDrive.DrawPath(render);
////}

/////* virtual override final */
////void Vehicle::RenderInfoInSpace(const jeti::Renderer& render, const glm::vec2& scroll_coords, float zoom)
////{
////    UpdateInfo(); // virtual
////    glm::vec2 pos(center().x - scroll_coords.x, center().y - scroll_coords.y);
////    pos /= zoom;
////    jeti::drawInfoIn2Column(GetInfo().title_list, GetInfo().value_list, pos);
////    if (m_OwnerNpc != nullptr)
////    {
////        glm::vec2 pos2(pos.x + 300, pos.y);
////        m_OwnerNpc->RenderInfo(pos2);
////    }
////}

////void Vehicle::RenderInfo(const glm::vec2& center, int offset_x, int offset_y)
////{
////    UpdateInfo(); // virtual
////    glm::vec2 pos(center.x - offset_x, center.y - offset_y);
////    jeti::drawInfoIn2Column(GetInfo().title_list, GetInfo().value_list, pos);

////    if (m_OwnerNpc != nullptr)
////    {
////        m_OwnerNpc->RenderInfo(glm::vec2(center.x + 190 - offset_x, center.y - offset_y));
////    }
////}

////void Vehicle::RenderGrabTrail(const jeti::Renderer& render) const
////{
////    //m_SlotGrapple->GetGrappleEquipment()->RenderGrabTrail(render);
////}

////void Vehicle::RenderKorpus(const jeti::Renderer& render)
////{
////    //render.DrawQuad(textureOb(), actualModelMatrix());
////    //alpitodorender render.DrawMeshLight(mesh(), textureOb(), actualModelMatrix());
////}

////void Vehicle::RenderDriveEffect(float scale, float parent_d_alpha) const
////{
////    m_ComplexDrive.GetDriveEffect()->Update();
////    //m_ComplexDrive.GetDriveEffect()->Render(scale, parent_d_alpha);
////}


////void Vehicle::RenderShieldEffect(const jeti::Renderer& renderer, float parent_d_alpha) const
////{
////    m_ComplexProtector.GetShieldEffect()->Render(renderer, parent_d_alpha);
////}

////void Vehicle::RenderRadarRange()
////{
////    if (model()->properties().radar > VISIBLE_DISTANCE_WITHOUT_RADAR)
////    {
////        m_SlotRadar->UpdateRange(GuiTextureObCollector::Instance().dot_yellow);
////        m_SlotRadar->DrawRange(meti::vec2(center()));
////    }
////}

////void Vehicle::RenderGrappleRange()
////{
////    if (model()->properties().grab_radius > 0)
////    {
////        m_SlotGrapple->UpdateRange(GuiTextureObCollector::Instance().dot_blue);
////        m_SlotGrapple->DrawRange(meti::vec2(center()));
////    }
////}

//bool Vehicle::isAbleToJumpTo(Starsystem* target_starsystem) const
//{
////    float dist = meti::distance(starsystem()->position(), target_starsystem->position());
////    if (dist < model()->properties().hyper)
////    {
////        return true;
////    }

////    return false;
//}

//void Vehicle::repairKorpus(int amount)
//{
////    _dataLife().armor += amount;
////    if (_dataLife().armor > m_vehicleDescriptor.armor)
////    {
////        _dataLife().armor = m_vehicleDescriptor.armor;
////    }
//}

//bool Vehicle::isArmorFull() const
//{
////    if (_dataLife().armor == m_vehicleDescriptor.armor)
////    {
////        return true;
////    }

////    return false;
//}

//int Vehicle::armorMiss() const
//{
////    return (m_vehicleDescriptor.armor - _dataLife().armor);
//}

//bool Vehicle::isFuelFull() const
//{
////    if (m_driveComplex.bakSlot()->item() == nullptr)
////    {
////        return true;
////    }

////    if (fuelMiss() == 0)
////    {
////        return true;
////    }


////    return false;
//}

//int Vehicle::fuelMiss() const
//{
////    return m_driveComplex.bakSlot()->bakEquipment()->fuelMiss();
//}

//void Vehicle::lockRandomItem(int locked_turns)
//{
////    std::vector<ItemSlot*> _equiped_slot_vec;

////    for (unsigned int i=0; i<m_equipmentSlots.size(); i++)
////    {
////        if (m_equipmentSlots[i]->item() != nullptr)
////        {
////            _equiped_slot_vec.push_back(m_equipmentSlots[i]);
////        }
////    }

////    if (_equiped_slot_vec.size() > 0)
////    {
////        unsigned int _rand = meti::getRandInt(_equiped_slot_vec.size());
////        _equiped_slot_vec[_rand]->item()->doLock(locked_turns);
////    }
//}

//bool Vehicle::tryConsumeEnergy(int energy)
//{
////#ifdef USE_EXTRA_EQUIPMENT
////    //LOG("Vehicle("+std::to_string(id())+")::TryToConsumeEnergy(energy="+std::to_string(energy)+")");

////    if (model()->properties().energy > energy)
////    {
////        model()->properties().energy -= energy;
////        m_SlotEnergizer->energizerEquipment()->DecreaseEnergy(energy);

////        return true;
////    }

////    return false;
////#else
////    return true;
////#endif
//}

//bool Vehicle::tryGenerateEnergy(int energy)
//{
////#ifdef USE_EXTRA_EQUIPMENT
////    //LOG("Vehicle("+std::to_string(id())+")::TryToGenerateEnergy(energy="+std::to_string(energy)+")");

////    int energy_max = m_SlotEnergizer->energizerEquipment()->GetEnergyMax();
////    if (model()->properties().energy < energy_max)
////    {
////        int diff_energy = energy_max - model()->properties().energy;
////        if ( diff_energy < energy)
////        {
////            energy = diff_energy;
////        }

////        model()->properties().energy += energy;
////        m_SlotEnergizer->energizerEquipment()->IncreaseEnergy(energy);

////        if (model()->properties().hibernate_mode_enabled == true)
////        {
////            if (model()->properties().energy > HIBERNATION_ENERGY_THRESHOLD)
////            {
////                UpdatePropertiesProtection();
////            }
////        }

////        return true;
////    }

////    return false;
////#else
////    return true;
////#endif
//}


//STATUS Vehicle::CheckGrabStatus() const
//{
////    STATUS status = STATUS::ITEM_OK;

////    if (m_grappleSlot->item() != nullptr)
////    {
////        if (m_grappleSlot->grappleEquipment()->isDamaged() == true)
////        {
////            status = STATUS::ITEM_DAMAGED;
////        }

////        if (m_grappleSlot->grappleEquipment()->isLocked() != 0)
////        {
////            status = STATUS::ITEM_LOCKED;
////        }
////    }
////    else
////    {
////        status = STATUS::ITEMSLOT_EMPTY;
////    }

////    return status;
//}

//bool Vehicle::dropItemToSpace(const entity::Type& type)
//{
////    if (place() != type::place::KOSMOS)
////        return false;

////    for (ItemSlot* slot: m_slots) {
////        if (slot->subtype() == type && slot->item()) {
////            item::Base* item = slot->takeItem();
////            Container* container = __wrapItemToContainer(item);
////            //    float impulse_strength = 0.5;
////            //    glm::vec3 impulse_dir(meti::getRandXYVec3Unit());
////            //    container->addImpulse(impulse_dir, impulse_strength);

////            starsystem()->add(container, position());
////            return true;
////        }
////    }

////    return false;
//}

//Container*
//Vehicle::__wrapItemToContainer(item::Base* item)
//{
////    Container* container = ContainerBuilder::getNew();
////    container->insertItem(item);

////    return container;
//}

////void Vehicle::__dropRandomItemToSpace()
////{
////    std::vector<ItemSlot*> _equiped_slot_vec;
////    for (ItemSlot* slot: m_slots) {
////        if (slot->item()) {
////            _equiped_slot_vec.push_back(slot);
////        }
////    }
////    if (_equiped_slot_vec.size() > 0) {
////        _equiped_slot_vec[meti::getRandInt(_equiped_slot_vec.size()-1)]->dropItemToSpace();
////    }
////}

//void Vehicle::UpdateGrappleMicroProgram_inDynamic()
//{
////    if (model()->properties().grab_radius > 0)
////    {
////        m_grappleSlot->grappleEquipment()->UpdateGrabScenarioProgram_inDynamic();
////    }
//}

//void Vehicle::SaveData(boost::property_tree::ptree& save_ptree, const std::string& root) const
//{
////    //LOG(" Vehicle("+std::to_string(id())+")::SaveData");

////    save_ptree.put(root+"m_DataKorpus.space", m_vehicleDescriptor.space);
////    save_ptree.put(root+"m_DataKorpus.armor", m_vehicleDescriptor.armor);
////    save_ptree.put(root+"m_DataKorpus.protection", m_vehicleDescriptor.protection);
////    save_ptree.put(root+"m_DataKorpus.temperature", m_vehicleDescriptor.temperature);

////    save_ptree.put(root+"m_DataKorpus.price", m_vehicleDescriptor.price);
////    save_ptree.put(root+"m_DataKorpus.draw_turrels", m_vehicleDescriptor.draw_turrels);

////    save_ptree.put(root+"m_DataKorpus.slot_grapple_num", m_vehicleDescriptor.slot_grapple_num);
////    save_ptree.put(root+"m_DataKorpus.slot_drive_num", m_vehicleDescriptor.slot_drive_num);
////    save_ptree.put(root+"m_DataKorpus.slot_protector_num", m_vehicleDescriptor.slot_protector_num);
////    save_ptree.put(root+"m_DataKorpus.slot_radar_num", m_vehicleDescriptor.slot_radar_num);
////    save_ptree.put(root+"m_DataKorpus.slot_scaner_num", m_vehicleDescriptor.slot_scaner_num);
////    save_ptree.put(root+"m_DataKorpus.slot_freezer_num", m_vehicleDescriptor.slot_freezer_num);
////    save_ptree.put(root+"m_DataKorpus.slot_weapon_num", m_vehicleDescriptor.slot_weapon_num);


////    if (m_driveComplex.target() != nullptr)
////    {
////        save_ptree.put(root+"data_unresolved_Vehicle.drive_complex_target_id", m_driveComplex.target()->id());
////        save_ptree.put(root+"data_unresolved_Vehicle.drive_complex_action_id", m_driveComplex.GetActionId());
////    }
////    else
////    {
////        save_ptree.put(root+"data_unresolved_Vehicle.drive_complex_target_id", NONE);
////        save_ptree.put(root+"data_unresolved_Vehicle.drive_complex_action_id", NONE);
////    }

////    if (m_Land != nullptr)  { save_ptree.put(root+"data_unresolved_Vehicle.land_id", m_Land->id()); }
////    else                     { save_ptree.put(root+"data_unresolved_Vehicle.land_id", NONE); }

////    if (m_parentVehicleSlot != nullptr) { save_ptree.put(root+"data_unresolved_Vehicle.parent_vehicleslot_id", m_parentVehicleSlot->id()); }
////    else                                     { save_ptree.put(root+"data_unresolved_Vehicle.parent_vehicleslot_id", NONE); }

////    if (place() == type::place::HYPER)
////    {
////        save_ptree.put(root+"data_unresolved_Vehicle.starsystem_hyper_id", m_driveComplex.target()->id());
////    }
////    else
////    {
////        save_ptree.put(root+"data_unresolved_Vehicle.starsystem_hyper_id", NONE);
////    }
//}

//void Vehicle::LoadData(const boost::property_tree::ptree& load_ptree)
//{
////    //LOG(" Vehicle("+std::to_string(id())+")::LoadData");

////    m_vehicleDescriptor.space       = load_ptree.get<int>("m_DataKorpus.space");
////    m_vehicleDescriptor.armor       = load_ptree.get<int>("m_DataKorpus.armor");
////    m_vehicleDescriptor.protection  = load_ptree.get<int>("m_DataKorpus.protection");
////    m_vehicleDescriptor.temperature = load_ptree.get<int>("m_DataKorpus.temperature");

////    m_vehicleDescriptor.price        = load_ptree.get<int>("m_DataKorpus.price");
////    m_vehicleDescriptor.draw_turrels = load_ptree.get<bool>("m_DataKorpus.draw_turrels");

////    m_vehicleDescriptor.slot_grapple_num   = load_ptree.get<int>("m_DataKorpus.slot_grapple_num");
////    m_vehicleDescriptor.slot_drive_num     = load_ptree.get<int>("m_DataKorpus.slot_drive_num");
////    m_vehicleDescriptor.slot_protector_num = load_ptree.get<int>("m_DataKorpus.slot_protector_num");
////    m_vehicleDescriptor.slot_radar_num     = load_ptree.get<int>("m_DataKorpus.slot_radar_num");
////    m_vehicleDescriptor.slot_scaner_num    = load_ptree.get<int>("m_DataKorpus.slot_scaner_num");
////    m_vehicleDescriptor.slot_freezer_num   = load_ptree.get<int>("m_DataKorpus.slot_freezer_num");
////    m_vehicleDescriptor.slot_weapon_num    = load_ptree.get<int>("m_DataKorpus.slot_weapon_num");

////    data_unresolved_Vehicle.drive_complex_target_id   = load_ptree.get<int>("data_unresolved_Vehicle.drive_complex_target_id");
////    data_unresolved_Vehicle.drive_complex_action_id   = load_ptree.get<int>("data_unresolved_Vehicle.drive_complex_action_id");
////    //data_unresolved_Vehicle.textureOb_gui_path = load_ptree.get<std::string>("data_unresolved_Vehicle.textureOb_gui_path");
////    data_unresolved_Vehicle.parent_vehicleslot_id = load_ptree.get<int>("data_unresolved_Vehicle.parent_vehicleslot_id");
////    data_unresolved_Vehicle.land_id = load_ptree.get<int>("data_unresolved_Vehicle.land_id");
////    data_unresolved_Vehicle.starsystem_hyper_id = load_ptree.get<int>("data_unresolved_Vehicle.starsystem_hyper_id");

//}

//void Vehicle::ResolveData()
//{
////    //LOG(" Vehicle("+std::to_string(id())+")::ResolveData");

////    CreateDriveComplexTextureDependedStuff();
////    CreateProtectionComplexTextureDependedStuff();

////    if (data_unresolved_Vehicle.drive_complex_target_id != NONE)
////    {
////        m_driveComplex.SetTarget((SpaceObject*)core::global::get().entityManager().getEntity(data_unresolved_Vehicle.drive_complex_target_id),  data_unresolved_Vehicle.drive_complex_action_id);
////    }

////    if (data_unresolved_Vehicle.land_id != NONE)
////    {
////        setLand( (Land*)core::global::get().entityManager().getEntity(data_unresolved_Vehicle.land_id) );
////    }

////    switch(place())
////    {
////    case type::place::KOSMOS:
////    {
////        //starsystem()->add(this, data_unresolved_Orientation.center, data_unresolved_Orientation.direction, parent());
////        break;
////    }

////    case type::place::KOSMOPORT:
////    {
////        ((VehicleSlot*)core::global::get().entityManager().getEntity(data_unresolved_Vehicle.parent_vehicleslot_id ))->InsertVehicle(this);
////        break;
////    }

////    case type::place::HYPER:
////    {
////        //std::cout<<"xxx="<<data_unresolved_Vehicle.starsystem_hyper_id<<std::endl;
////        ((Starsystem*)core::global::get().entityManager().getEntity(data_unresolved_Vehicle.starsystem_hyper_id))->hyperSpace().AddVehicle(this);
////        //std::cout<<"yyy="<<data_unresolved_Vehicle.starsystem_hyper_id<<std::endl;

////        break;
////    }

////    case type::place::LAND:
////    {
////        ((NatureLand*)core::global::get().entityManager().getEntity(data_unresolved_Vehicle.land_id))->AddVehicle(this);
////        break;
////    }
////    }

////    m_weaponComplex.prepareWeapons();
//}

////void Vehicle::TEST_DamageAndLockRandItems()
////{
////    int rand_index1 = meti::getRandInt(m_equipmentSlots.size()-1);
////    while (m_equipmentSlots[rand_index1]->item() == nullptr)
////    {
////        rand_index1 = meti::getRandInt(m_equipmentSlots.size()-1);
////    }
////    m_equipmentSlots[rand_index1]->item()->doLock(3);

////    int rand_index2 = meti::getRandInt(m_equipmentSlots.size()-1);
////    while (m_equipmentSlots[rand_index2]->item() == nullptr)
////    {
////        rand_index2 = meti::getRandInt(m_equipmentSlots.size()-1);
////    }

////    while (m_equipmentSlots[rand_index2]->item()->condition() > 0)
////    {
////        m_equipmentSlots[rand_index2]->item()->deteriorationEvent();
////    }
////}

//std::string getVehicleSpecialActionStr(VEHICLE_SPECIAL_ACTION_TYPE type_id)
//{
////    switch(type_id)
////    {
////    case VEHICLE_SPECIAL_ACTION_TYPE::INITIATE_DOCKING:     { return "INITIATE_DOCKING"; break; }
////    case VEHICLE_SPECIAL_ACTION_TYPE::INITIATE_LAUNCHING:    { return "INITIATE_LAUNCHING"; break; }
////    case VEHICLE_SPECIAL_ACTION_TYPE::INITIATE_JUMPIN:        { return "INITIATE_JUMPIN"; break; }
////    case VEHICLE_SPECIAL_ACTION_TYPE::INITIATE_JUMPOUT:        { return "INITIATE_JUMPOUT"; break; }
////    case VEHICLE_SPECIAL_ACTION_TYPE::NONE:                    { return "NONE"; break; }

////    default: { return "UKNOWN id_type"; break; }
////    }
//}
