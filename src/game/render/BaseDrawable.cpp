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


#include <render/BaseDrawable.hpp>
#include <render/Render.hpp>

#include <render/textureOb.hpp>
#include <render/Mesh.hpp>
#include <common/Orientation.hpp>

#include <resources/GuiTextureObCollector.hpp>

#include <render/animations/BaseAnimationRotation.hpp>

#include <glm/gtx/transform.hpp>
#include <math/QuaternionUtils.hpp>

#ifdef LOG_DRAW_ENABLED
#include "<common/Logger.hpp>
#endif

namespace jeti {

BaseDrawable::BaseDrawable(Orientation* orientation, TextureOb* textureOb, Mesh* mesh)
    :
      m_TextureOb(textureOb),
      m_Mesh(mesh),
      m_Orientation(orientation),
      m_AnimationRotation(nullptr)
{}

/* virtual */
BaseDrawable::~BaseDrawable() {
#if CREATEDESTROY_LOG_ENABLED == 1
    Logger::Instance().Log("___::~Drawable("+int2str(GetId())+")");
#endif
    
    delete m_AnimationRotation;
}

void BaseDrawable::ValidateResources() const
{
    assert(m_TextureOb);
    if (!m_TextureOb->GetIsLoaded()) {
        m_TextureOb->Load();
    }
    // todo the same for mesh
}

//void BaseDrawable::BindData2D(TextureOb* textureOb)
//{
//m_TextureOb = textureOb;
//SetSize(textureOb->GetFrameWidth(), textureOb->GetFrameHeight(), 1.0);
//SetCollisionRadius((textureOb->GetFrameWidth() + textureOb->GetFrameHeight()) / 4.0);
//} 


void BaseDrawable::RenderCollisionRadius(const Renderer& render) const
{
    TextureOb* texOb_collision_radius =  GuiTextureObCollector::Instance().radar_range;
    glm::vec3 zero;
    glm::mat4 Mm = getModelMatrix(m_Orientation->GetCenter(), glm::vec3(2*m_Orientation->GetCollisionRadius()), zero);
    render.DrawQuad(*texOb_collision_radius, Mm);
}

void BaseDrawable::RenderAxis(const Renderer& render) const
{
    glm::mat4 Mm = getModelMatrix(m_Orientation->GetCenter(), glm::vec3(2*m_Orientation->GetCollisionRadius()), glm::vec3(0.0f));    // angle
    render.DrawAxis(Mm, /*width*/4);
    //render.DrawVector(GetDir(), GetCenter(), GetSize().x, /*width*/6);
    render.DrawVector(m_Orientation->GetDirection(), Mm, /*width*/6);
}

void BaseDrawable::UpdateRenderAnimation()
{
    if (m_AnimationRotation != nullptr) {
        //m_AnimationRotation->Update(GetAngle());
    }
}

bool BaseDrawable::UpdateFadeInEffect()
{
    if (m_Color.a > 0.01) {
        m_Color.a -= 0.02;
        return false;
    } else {
        m_Color.a = 0.0;
        return true;
    }
}

bool BaseDrawable::UpdateFadeOutEffect()
{
    if (m_Color.a < 1.0) {
        m_Color.a += 0.02;
        return false;
    } else {
        m_Color.a = 1.0;
        return true;
    }
}

const glm::mat4& BaseDrawable::GetActualModelMatrix()
{    
    RotationBetweenVectors(m_QuatDirection, m_Mesh->GetOriginDirection(), m_Orientation->GetDirection());
    if (m_AnimationRotation != nullptr) {
        m_AnimationRotation->Update(m_QuatAnimation, m_Mesh->GetOriginDirection());
    }
    
    m_MatrixTranslate = glm::translate(m_Orientation->GetCenter());
    m_MatrixRotate    = glm::toMat4(m_QuatDirection * m_QuatAnimation);
    m_MatrixScale     = glm::scale(m_Orientation->GetSize());

    m_MatrixModel = m_MatrixTranslate * m_MatrixScale * m_MatrixRotate;
    
    return m_MatrixModel;
}

glm::mat4 getModelMatrix(const glm::vec3& center, const glm::vec3& size, const glm::vec3& angle)
{
    glm::mat4 Tm = glm::translate(center);

    glm::quat Qx, Qy, Qz;

    //QuatFromAngleAndAxis(Qx, angle.x, AXIS_X);
    //QuatFromAngleAndAxis(Qy, angle.y, AXIS_Y);
    //QuatFromAngleAndAxis(Qz, angle.z, AXIS_Z);

    glm::mat4 Rm = glm::toMat4(Qx*Qy*Qz);
    glm::mat4 Sm = glm::scale(size);

    glm::mat4 Mm = Tm * Rm * Sm;

    return Mm;
}

}
