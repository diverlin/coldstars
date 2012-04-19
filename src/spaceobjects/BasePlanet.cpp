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


BasePlanet::BasePlanet()
{}

/* virtual */
BasePlanet::~BasePlanet()
{
	delete orbit;
}

void BasePlanet::PostCreateInit()
{
        this->CalcCollisionrRadius();           
        
        orbit = new Orbit();
}

void BasePlanet::CreateOrbit()
{
	orbit->CalcPath(data_planet.radius_A, data_planet.radius_B, data_planet.speed, data_planet.orbit_phi_inD);
}
    		
void BasePlanet::CalcCollisionrRadius()
{
        float scale_factor = 5.4;                                            
        int w = scale_factor * data_planet.scale;
        int h = scale_factor * data_planet.scale;
        collision_radius = (w + h)/4; 
        
        points.setWidthHeight(scale_factor*data_planet.scale, scale_factor*data_planet.scale);  // needs for finding visible corners
}

void BasePlanet::PostDeathUniqueEvent(bool)  /* virtual */
{}		
		 		
void BasePlanet::Render_NEW(vec2f scroll_coords)
{     	
     	glUseProgram(g_SHADERS.light);
     	//printProgramInfoLog(g_LIGHT_PROGRAM);

     	//if (glGetUniformLocation(g_LIGHT_PROGRAM, "lightPos") == -1)
         	//printf("shader lightPos fail\n"); 
     	//if (glGetUniformLocation(g_LIGHT_PROGRAM, "eyePos") == -1)
         	//printf("shader eyePos fail\n"); 
     	//if (glGetUniformLocation(g_LIGHT_PROGRAM, "Texture_0") == -1)
         	//printf("shader Texture_0 fail\n"); 

     	glUniform4f(glGetUniformLocation(g_SHADERS.light, "lightPos"), -scroll_coords.x, -scroll_coords.y, -200.0, 0.0);
     	glUniform4f(glGetUniformLocation(g_SHADERS.light, "eyePos"), -scroll_coords.x, -scroll_coords.y, -200.0, 0.0);

     	glActiveTexture(GL_TEXTURE0);
     	glBindTexture(GL_TEXTURE_2D, textureOb->texture);
     	glUniform1i(glGetUniformLocation(g_SHADERS.light, "Texture_0"), 0);
      
	renderMesh(mesh->glList, points.getCenter3f(), angle, data_planet.scale);

     	//// render atmosphere
     	//glEnable(GL_BLEND);
     	//glActiveTexture(GL_TEXTURE0);                                
     	//glBindTexture(GL_TEXTURE_2D, pTo_atmosphereTexOb->texture);
     	//glUniform1i(glGetUniformLocation(g_LIGHT_PROGRAM, "Texture_0"), 0);

	//renderMesh(mesh->glList, center_pos, angle, planet_data.scale*1.05);
	
     	//glDisable(GL_BLEND);
     	//// render atmosphere

     	glUseProgram(0);
     	glActiveTexture(GL_TEXTURE0);
}

void BasePlanet::Render_OLD()
{   	
	glBindTexture(GL_TEXTURE_2D, textureOb->texture);
	renderMesh(mesh->glList, points.getCenter3f(), angle, data_planet.scale);
}


void BasePlanet::SaveDataUniqueBasePlanet(boost::property_tree::ptree& save_ptree, const std::string& root) const
{
	save_ptree.put(root+"orbit.it", orbit->GetIt());
	
	save_ptree.put(root+"data.scale", data_planet.scale);
	save_ptree.put(root+"data.orbit_center.x", data_planet.orbit_center.x);	
	save_ptree.put(root+"data.orbit_center.y", data_planet.orbit_center.y);	
	save_ptree.put(root+"data.radius_A", data_planet.radius_A);	
	save_ptree.put(root+"data.radius_B", data_planet.radius_B);
	save_ptree.put(root+"data.orbit_phi_inD", data_planet.orbit_phi_inD);		
	save_ptree.put(root+"data.speed", data_planet.speed);
}

void BasePlanet::LoadDataUniqueBasePlanet(const boost::property_tree::ptree& load_ptree)
{
	data_planet.scale = load_ptree.get<int>("data.scale");
	data_planet.orbit_center.x = load_ptree.get<float>("data.orbit_center.x");	
	data_planet.orbit_center.y = load_ptree.get<float>("data.orbit_center.y");	
	data_planet.radius_A = load_ptree.get<float>("data.radius_A");	
	data_planet.radius_B = load_ptree.get<float>("data.radius_B");
	data_planet.orbit_phi_inD = load_ptree.get<float>("data.orbit_phi_inD");		
	data_planet.speed = load_ptree.get<float>("data.speed");
}

void BasePlanet::ResolveDataUniqueBasePlanet()
{}


