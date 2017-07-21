///*
//    Copyright (C) ColdStars, Aleksandr Pivovarov <<coldstars8@gmail.com>>
    
//    This program is free software; you can redistribute it and/or
//    modify it under the terms of the GNU General Public License
//    as published by the Free Software Foundation; either version 2
//    of the License, or (at your option) any later version.
    
//    This program is distributed in the hope that it will be useful,
//    but WITHOUT ANY WARRANTY; without even the implied warranty of
//    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//    GNU General Public License for more details.
    
//    You should have received a copy of the GNU General Public License
//    along with this program; if not, write to the Free Software
//    Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
//*/

//#include <render/VehicleDrawable.hpp>

//#include <client/effects/Shield.hpp>
//#include <jeti/particlesystem/DriveEffect.hpp>
//#include <jeti/particlesystem/ExplosionEffect.hpp>
//#include <client/text/VerticalFlowText.hpp>

//VehicleDrawable::VehicleDrawable(jeti::control::TextureOb* texture, jeti::Mesh* mesh)
//    :
//      BaseDrawable(texture, mesh)
//{}

///* virtual override */
//VehicleDrawable::~VehicleDrawable()
//{
//    #if CREATEDESTROY_LOG_ENABLED == 1
//    Logger::Instance().Log("___::~VehicleDrawable("+std::to_string(id())+")");
//    #endif
//}

//void VehicleDrawable::CreateDriveComplexTextureDependedStuff()
//{
////    points().addMidLeftPoint();
////    points().addMidFarLeftPoint();
        
//    //DriveEffect* drive_effect = GetNewDriveEffect(textureOb().GetData().size_id, points().GetpMidLeft(), points().GetpMidFarLeft());
//    //m_ComplexDrive.SetDriveEffect(drive_effect);
//}

//void VehicleDrawable::CreateProtectionComplexTextureDependedStuff()
//{
//    //m_ComplexProtector.GetShieldEffect()->setParent(this);
//}

///* virtual override final */
////void VehicleDrawable::RenderStuffWhenFocusedInSpace(const jeti::Renderer& render)
////{
//////    m_ComplexWeapon.RenderWeaponIcons();
    
//////    RenderRadarRange();
//////    m_ComplexWeapon.RenderWeaponsRange();
    
//////    m_ComplexDrive.DrawPath(render);
////}

///* virtual override final */
////void VehicleDrawable::RenderInfoInSpace(const jeti::Renderer& render, const glm::vec2& scroll_coords, float zoom)
////{
//////    UpdateInfo(); // virtual
//////    glm::vec2 pos(center().x - scroll_coords.x, center().y - scroll_coords.y);
//////    pos /= zoom;
//////    jeti::drawInfoIn2Column(GetInfo().title_list, GetInfo().value_list, pos);
//////    if (m_OwnerNpc != nullptr)
//////    {
//////        glm::vec2 pos2(pos.x + 300, pos.y);
//////        m_OwnerNpc->RenderInfo(pos2);
//////    }
////}

//void VehicleDrawable::RenderInfo(const glm::vec2& center, int offset_x, int offset_y)
//{
////    UpdateInfo(); // virtual
////    glm::vec2 pos(center.x - offset_x, center.y - offset_y);
////    jeti::drawInfoIn2Column(GetInfo().title_list, GetInfo().value_list, pos);

////    if (m_OwnerNpc != nullptr)
////    {
////        m_OwnerNpc->RenderInfo(glm::vec2(center.x + 190 - offset_x, center.y - offset_y));
////    }
//}

//void VehicleDrawable::RenderGrabTrail(const jeti::Renderer& render) const
//{
//    //m_SlotGrapple->GetGrappleEquipment()->RenderGrabTrail(render);
//}
        
//void VehicleDrawable::RenderKorpus(const jeti::Renderer& render)
//{
//    //render.DrawQuad(textureOb(), actualModelMatrix());
//    //alpitodorender render.DrawMeshLight(mesh(), textureOb(), actualModelMatrix());
//}

//void VehicleDrawable::RenderDriveEffect(float scale, float parent_d_alpha) const
//{
//    //m_ComplexDrive.GetDriveEffect()->Update();
//    //m_ComplexDrive.GetDriveEffect()->Render(scale, parent_d_alpha);
//}


//void VehicleDrawable::RenderShieldEffect(const jeti::Renderer& renderer, float parent_d_alpha) const
//{
//    //m_ComplexProtector.GetShieldEffect()->Render(renderer, parent_d_alpha);
//}

//void VehicleDrawable::RenderRadarRange()
//{
////    if (m_Properties.radar > VISIBLE_DISTANCE_WITHOUT_RADAR)
////    {
////        m_SlotRadar->UpdateRange(GuiTextureObCollector::Instance().dot_yellow);
////        m_SlotRadar->DrawRange(vec2(center()));
////    }
//}

//void VehicleDrawable::RenderGrappleRange()
//{
////    if (m_Properties.grab_radius > 0)
////    {
////        m_SlotGrapple->UpdateRange(GuiTextureObCollector::Instance().dot_blue);
////        m_SlotGrapple->DrawRange(vec2(center()));
////    }
//}