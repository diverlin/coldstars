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



Satellite :: Satellite(int id)
{        
	data_id.id = id;
	data_id.type_id = ENTITY::SATELLITE_ID;
	
    	mass = getRandInt(ENTITY::SATELLITE::MASS_MIN, ENTITY::SATELLITE::MASS_MAX);
    	orbit = new Orbit();
    	
    	d_angle.z = 1.0f;
}

Satellite :: ~Satellite() 
{
	delete orbit;
}
    
Orbit* Satellite :: getOrbit() const { return orbit; }
    				
void Satellite :: update_inSpace(int time, bool show_effect)
{
	CheckDeath(show_effect);
	if (time > 0)
	{
		orbit->UpdatePosition();

		//printf("sat orbit =%f,%f\n", orbit->getPosition().x, orbit->getPosition().y);
		//if (parent != NULL)
		//{		
			vec2f new_pos;
			new_pos.x = parent->GetPoints().GetCenter().x + orbit->GetPosition().x;
			new_pos.y = parent->GetPoints().GetCenter().y + orbit->GetPosition().y;
			points.SetCenter(new_pos);
			points.Update();
		//}
		//else
		//{
			//points.SetCenter(orbit->getPosition());
		//}
	}
}


void Satellite :: UpdateInfo()
{
	info.clear();

    	info.addTitleStr("SATELLITE");

    	//info.addNameStr("id/ss_id:");    info.addValueStr(int2str(data_id.id) + " / " + int2str(starsystem->GetId()));
    	info.addNameStr("id:");          info.addValueStr(int2str(data_id.id));
    	info.addNameStr("mass:");        info.addValueStr(int2str(mass));
}
            


void Satellite :: updateRenderStuff()
{
    	//points.update(); 
    	protection_complex->GetShieldEffect()->Update();
    	
    	this->UpdateRotation();
	points.SetAngle(angle.z);
    	//printf("3. angle = %f\n", angle.z);
    	points.Update();
    		
    	//if (ableTo.DRIVE == true)
    	//{
       		//drive_trail->update();
    	//}
}

void Satellite :: render_inSpace() const
{   
        //if (ableTo.GRAB == true)
        //{
                //renderGrappleTrail();
        //}
        
    	RenderKorpus();
    	
    	if (data_korpus.draw_turrels == true)
    	{
        	weapon_complex->RenderTurrels();
        }

    	//if (ableTo.DRIVE == true)
    	//{
		//renderDriveTrail();
    	//}
    	
    	if (ableTo.PROTECT == true)
    	{
        	RenderShield(); 
        }
}


void Satellite :: render_atPlanet() const
{
	RenderKorpus();
	
	if (data_korpus.draw_turrels == true)
    	{
        	weapon_complex->RenderTurrels();
        }
}		



/*virtual*/
void Satellite::SaveData(boost::property_tree::ptree& save_ptree) const
{
	//const std::string root = "rocket."+int2str(data_id.id)+".";
}

/*virtual*/
void Satellite::LoadData(const boost::property_tree::ptree& load_ptree)
{

}

/*virtual*/
void Satellite::ResolveData()
{

}


