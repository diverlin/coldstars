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

#include "BulletDrawable.hpp"

BulletDrawable::BulletDrawable(jeti::TextureOb* texture, jeti::Mesh* mesh)
:
  BaseDrawable(texture, mesh),
  m_EffectDrive(nullptr)
{
}

/* virtual override final */
BulletDrawable::~BulletDrawable()
{
    #if CREATEDESTROY_LOG_ENABLED == 1
    Logger::Instance().Log("___::~BulletDrawable("+std::to_string(GetId())+")");
    #endif

    delete m_EffectDrive;
}

void BulletDrawable::CreateDriveComplexTextureDependedStuff()
{
//    GetPoints().addMidLeftPoint();
//    GetPoints().addMidFarLeftPoint();
        
    //alpitodorender m_EffectDrive = GetNewDriveEffect(GetTextureOb().GetData().size_id/2, GetPoints().GetpMidLeft(), GetPoints().GetpMidFarLeft());
}    

/* virtual override final */
//void RocketBullet::UpdateInfo()
//{
//    GetInfo().clear();

//    GetInfo().addTitleStr("ROCKET");
//    GetInfo().addNameStr("id/ss_id:");          GetInfo().addValueStr( std::to_string(GetId()) + " / " + std::to_string(GetStarSystem()->GetId()) );
//    GetInfo().addNameStr("armor:");             GetInfo().addValueStr( std::to_string(GetDataLife().armor) );
//    if (m_Target != nullptr)
//    {
//        GetInfo().addNameStr("target_id:");       GetInfo().addValueStr(std::to_string(m_Target->GetId()));
//    }
//}

//void RocketBullet::RenderInSpace(const Renderer& render, float scale)
//{
//    //alpitodorender render.DrawQuad(GetTextureOb(), GetActualModelMatrix());

//    m_EffectDrive->Update();
//    m_EffectDrive->Render(scale, 0.0f);
//}
