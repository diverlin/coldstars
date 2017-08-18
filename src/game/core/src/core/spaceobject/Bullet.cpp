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

#include "Bullet.hpp"

#include <core/descriptor/spaceobject/Bullet.hpp>
#include <core/model/spaceobject/Bullet.hpp>
#include <common/common.hpp>

#include <core/world/starsystem.hpp>

namespace control {

Bullet::Bullet(descriptor::Bullet* descr, model::Bullet* model)
    :
      SpaceObject(descr, model)
    , m_descriptor_rocket(descr)
    , m_model_rocket(model)
{
    m_model_rocket->setSpeed(descr->speedMin());
}

Bullet::~Bullet()
{
}

int Bullet::damage() const { return descriptor()->damage(); }

void Bullet::update(int time)
{
    _checkDeath();
        
    if (time > 0) {           
        if (model()->speed() < descriptor()->speedMax()) {
            model()->increaseSpeed(descriptor()->deltaSpeed());
        } 
                
        if (m_target) {
            setDirection(glm::normalize(m_target->position()-position()));
            if (!__checkTarget()) {
                m_target = nullptr;
            }
        }

        setPosition(position()+model()->speed()*direction()/* + _externalForce()*/);

        model()->decreaseLiveTime(1);
    }
}

bool Bullet::__checkTarget() const
{
    if (m_target->isAlive()) {
        if (m_target->place() == place::Type::SPACE) {
            if (m_target->starsystem()->id() == starsystem()->id()) {
                return true;
            }
        }
    }
    
    return false;
}

void Bullet::collisionEvent()
{
    die();
}

///* virtual override final */
//void Bullet::UpdateInfo()
//{
//    GetInfo().clear();

//    GetInfo().addTitleStr("ROCKET");
//    GetInfo().addNameStr("id/ss_id:");          GetInfo().addValueStr( std::to_string(id()) + " / " + std::to_string(starsystem()->id()) );
//    GetInfo().addNameStr("armor:");             GetInfo().addValueStr( std::to_string(dataLife().armor) );
//    if (m_Target != nullptr)
//    {
//        GetInfo().addNameStr("target_id:");       GetInfo().addValueStr(std::to_string(m_Target->id()));
//    }
//}

void Bullet::hit(int damage, SpaceObject* agressor)
{
    SpaceObject::hit(damage);

    //if (show_effect == true)
    {
        // improove
//        VerticalFlowText* text = new VerticalFlowText(std::to_string(damage), 12, meti::vec2(center()), COLOR::COLOR4I_RED_LIGHT, collisionRadius());
//        starsystem()->Add(text);
    }
}

/* virtual override final */
void Bullet::_postDeathUniqueEvent(bool show_effect)
{
    if (show_effect == true)
    {
//        jeti::ExplosionEffect* explosion = jeti::getNewExplosionEffect(collisionRadius());
//        starsystem()->Add(explosion, center());
    }
}

//void Bullet::RenderInSpace(const Renderer& render, float scale)
//{
//    //alpitodorender render.DrawQuad(textureOb(), actualModelMatrix());

//    m_EffectDrive->Update();
//    m_EffectDrive->Render(scale, 0.0f);
//}

} // namespace control

