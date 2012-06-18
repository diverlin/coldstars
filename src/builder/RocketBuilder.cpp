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


RocketBuilder& RocketBuilder::Instance()
{	
	static RocketBuilder instance;
	return instance;
}	


RocketBuilder::~RocketBuilder() {}


void RocketBuilder::CreateNewRocket(int id)
{
	if (id == NONE_ID)
	{
		id = g_ID_GENERATOR.getNextId();
	}
        rocket = new RocketBullet(id);
        EntityManager::Instance().RegisterEntity(rocket);
}

void RocketBuilder::CreateNewInternals(BulletData data_bullet, ItemSlot* slot, float offset, bool force_center_start) 
{
	LifeData data_life;	
	data_life.is_alive      = true;
        data_life.garbage_ready = false;
        data_life.armor = data_bullet.armor;        

         
        rocket->SetBulletData(data_bullet);
        rocket->SetOwner(slot->GetOwnerVehicle());
        rocket->SetTarget(slot->GetTurrel()->GetTarget());
        
        rocket->SetLifeData(data_life);
        rocket->SetTextureOb(data_bullet.texOb);
         
        CreateKorpusGeometry(rocket);
        //CreateShieldGeometry(rocket);
        //CreateGuiKontur(rocket);
        CreateDriveComplex(rocket);
        //CreateWeaponsComplex(rocket);
        //CreateProtectionComplex(rocket);
        //CreateEquipmentSlots(rocket);
}
