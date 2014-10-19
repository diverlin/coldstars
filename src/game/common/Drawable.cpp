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


#include <common/Drawable.hpp>

#include <resources/MeshCollector.hpp>
#include <resources/TextureManager.hpp>
#include <resources/GuiTextureObCollector.hpp>

#include <common/constants.hpp>
#include <math/rand.hpp>
#include <common/common.hpp>
#include <common/Logger.hpp>

#include <world/EntityManager.hpp>

#include <render/Render.hpp>
#include <types/MeshTypes.hpp>

#include <animations/BaseAnimationRotation.hpp>

#include <render/Mesh.hpp>
#include <common/Orientation.hpp>

#include <glm/gtx/transform.hpp>
#include <math/QuaternionUtils.hpp>


Drawable::Drawable(Orientation* orientation)
    :
      m_TextureOb(nullptr),
      m_Mesh(nullptr),
      m_AnimationRotation(nullptr),
      m_Orientation(orientation)
{}

/* virtual */
Drawable::~Drawable() {
#if CREATEDESTROY_LOG_ENABLED == 1
    Logger::Instance().Log("___::~Drawable("+int2str(GetId())+")");
#endif
    
    delete m_AnimationRotation;
}

void Drawable::SetRenderData(Mesh* mesh, TextureOb* textureOb, const glm::vec3& size) {
    m_Mesh = mesh;
    m_TextureOb = textureOb;
    if (m_Mesh->GetTypeId() == TYPE::MESH::PLANE_ID) {
        m_Orientation->SetSize(textureOb->GetSize());
    } else {
        m_Orientation->SetSize(size);
    }
    m_Orientation->SetCollisionRadius((size.x + size.y) / 4.0);
    m_Orientation->SetDirection(mesh->GetOriginDirection());
}

void Drawable::ValidateResources() const
{
    assert(m_TextureOb);
    if (!m_TextureOb->GetIsLoaded()) {
        m_TextureOb->Load();
    }
    // todo the same for mesh
}

//void Drawable::BindData2D(TextureOb* textureOb)
//{
//m_TextureOb = textureOb;
//SetSize(textureOb->GetFrameWidth(), textureOb->GetFrameHeight(), 1.0);
//SetCollisionRadius((textureOb->GetFrameWidth() + textureOb->GetFrameHeight()) / 4.0);
//} 


void Drawable::RenderCollisionRadius(const Renderer& render) const
{
    TextureOb* texOb_collision_radius =  GuiTextureObCollector::Instance().radar_range;
    glm::vec3 zero;
    glm::mat4 Mm = getModelMatrix(m_Orientation->GetCenter(), glm::vec3(2*m_Orientation->GetCollisionRadius()), zero);
    render.DrawQuad(*texOb_collision_radius, Mm);
}

void Drawable::RenderAxis(const Renderer& render) const
{
    glm::mat4 Mm = getModelMatrix(m_Orientation->GetCenter(), glm::vec3(2*m_Orientation->GetCollisionRadius()), glm::vec3(0.0f));    // angle
    render.DrawAxis(Mm, /*width*/4);
    //render.DrawVector(GetDir(), GetCenter(), GetSize().x, /*width*/6);
    render.DrawVector(m_Orientation->GetDirection(), Mm, /*width*/6);
}

void Drawable::UpdateRenderAnimation()
{
    if (m_AnimationRotation != nullptr)
    {
        //m_AnimationRotation->Update(GetAngle());
    }
}

bool Drawable::UpdateFadeInEffect()
{
    if (m_Color.a > 0.01) {
        m_Color.a -= 0.02;
        return false;
    } else {
        m_Color.a = 0.0;
        return true;
    }
}

bool Drawable::UpdateFadeOutEffect()
{
    if (m_Color.a < 1.0) {
        m_Color.a += 0.02;
        return false;
    } else {
        m_Color.a = 1.0;
        return true;
    }
}

const glm::mat4& Drawable::GetActualModelMatrix()
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

//void Drawable::SaveData(boost::property_tree::ptree& save_ptree, const std::string& root) const
//{
//#if SAVELOAD_LOG_ENABLED == 1
//    Logger::Instance().Log(" BaseDrawable("+int2str(GetId())+")::SaveData", SAVELOAD_LOG_DIP);
//#endif

//    if (m_Mesh) save_ptree.put(root+"data_unresolved_BaseDrawable.mesh_type_id", (int)m_Mesh->GetTypeId());
//    else        save_ptree.put(root+"data_unresolved_BaseDrawable.mesh_type_id", (int)TYPE::MESH::NONE_ID);
    
//    if (m_TextureOb)    save_ptree.put(root+"data_unresolved_BaseDrawable.textureOb_path", m_TextureOb->GetData().texture_path);
//    else                save_ptree.put(root+"data_unresolved_BaseDrawable.textureOb_path", "none");
//}

//void Drawable::LoadData(const boost::property_tree::ptree& load_ptree)
//{
//#if SAVELOAD_LOG_ENABLED == 1
//    Logger::Instance().Log(" BaseDrawable("+int2str(GetId())+")::LoadData", SAVELOAD_LOG_DIP);
//#endif

//    data_unresolved_BaseDrawable.mesh_type_id = (TYPE::MESH)load_ptree.get<int>("data_unresolved_BaseDrawable.mesh_type_id");
//    data_unresolved_BaseDrawable.textureOb_path = load_ptree.get<std::string>("data_unresolved_BaseDrawable.textureOb_path");
//}

//void Drawable::ResolveData()
//{
//#if SAVELOAD_LOG_ENABLED == 1
//    Logger::Instance().Log(" BaseDrawable("+int2str(GetId())+")::ResolveData", SAVELOAD_LOG_DIP);
//#endif
    
//    if (data_unresolved_BaseDrawable.mesh_type_id != TYPE::MESH::NONE_ID) {
//        m_Mesh = MeshCollector::Instance().GetMeshByTypeId(data_unresolved_BaseDrawable.mesh_type_id);
//    }
    
//    m_TextureOb = TextureManager::Instance().GetTextureObByPath(data_unresolved_BaseDrawable.textureOb_path);
//}


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

