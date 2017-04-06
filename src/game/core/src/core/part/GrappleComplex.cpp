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

#include "GrappleComplex.hpp"

#include <core/type/EntityType.hpp>
#include <core/type/StatusType.hpp>

#include <core/spaceobject/Vehicle.hpp>
#include <core/spaceobject/SpaceObject.hpp>

namespace complex {

Grapple::Grapple(control::Vehicle* vehicle)
    :
      Base(vehicle)
{}

bool
Grapple::isObjectIsTarget(control::SpaceObject* object) const
{
    for (control::SpaceObject* target: m_targets) {
        if (object->id() == target->id()) {
            return true;
        }
    }

    return false;
}

bool
Grapple::addTarget(control::SpaceObject* target)
{
    m_targets.add(target);
    m_free_strength -= target->mass();
    return true;
}

bool
Grapple::removeTarget(control::SpaceObject* target)
{
    if (!isObjectIsTarget(target)) {
        return false;
    }

    m_targets.remove(target);
    m_free_strength += target->mass();
}

void
Grapple::resetTargets()
{
    m_targets.clear();
    m_free_strength = m_strength;
}

bool
Grapple::canBeManaged(control::SpaceObject* object) const
{
    // avoiding dublicated items in the vector
    // maybe better to inherit ceti::pack from std::set?
    if (isObjectIsTarget(object)) {
        return false;
    }

    if (m_free_strength < object->mass()) {
        return false;
    }
}

void
Grapple::UpdateGrabScenarioProgram_inDynamic()
{
    ceti::pack<control::SpaceObject*> targetsToForget;

    for (control::SpaceObject* target: m_targets) {
        if (_validateTarget(target, m_radius) != STATUS::TARGET_OK) {
            targetsToForget.add(target);
        } else {
            glm::vec3 impulse_dir = glm::normalize(_vehicle()->position() - target->position());

            target->addImpulse(impulse_dir, 0.001* m_strength);

            float dist = meti::distance(_vehicle()->position(), target->position());
            if (dist < 0.5*_vehicle()->collisionRadius()) {
                switch(target->descriptor()->obType()) {
                case entity::Type::CONTAINER: {
                    control::Container* container = reinterpret_cast<control::Container*>(target);
                    if (_vehicle()->unpackContainerItemToCargoSlot(container)) {
                        targetsToForget.add(target);
                    }
                    break;
                }

                    //case ENTITY::VEHICLE:
                    //{
                    //ItemSlot* _slot = GetEmptyOtsecSlot();
                    //Vehicle* _vehicle = (Vehicle*)grapple_slot->GetGrappleEquipment()->target_vec[i];
                    //if (_slot != nullptr)
                    //{
                    ////_slot->InsertItem(_vehicle);
                    //starsystem->AddToRemoveFromOuterSpaceQueue(_vehicle);
                    //}
                    //grapple_slot->GetGrappleEquipment()->AddToRemoveQueue(_vehicle);
                    //break;
                    //}
                }
            }
        }
    }
}


////void GrappleEquipment::RenderGrabTrail(const jeti::Renderer& render)
////{
////    //for (unsigned int i=0; i<target_vec.size(); i++)
////    //{
////    //float xl = target_vec[i]->position().x - item_slot->GetOwnerVehicle()->center().x;
////    //float yl = target_vec[i]->position().y - item_slot->GetOwnerVehicle()->center().y;

////    //float len = sqrt((xl*xl) + (yl*yl));

////    //float angle_inR = atan2(yl, xl);

////    //float angle_inD = angle_inR * RADIAN_TO_DEGREE_RATE;

////    //drawLine(GuiTextureObCollector::Instance().grapple_trail,
////    //item_slot->GetOwnerVehicle()->center(),
////    //len,
////    //angle_inD,
////    //8);
////    //}
////}


} // namespace complex
