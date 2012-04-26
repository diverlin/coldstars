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


   
Star::Star(int id)
{ 
	data_id.id = id;
	data_id.type_id = ENTITY::STAR_ID;
	
   	texture_offset1 = 0.0;
    	texture_offset2 = 0.0;
}
    
Star::~Star()
{}
    
void Star::CalcColor()
{
        if (textureOb->color_id == COLOR::YELLOW_ID)
	{
		color.r = 255/255.0;
		color.g = 255/255.0;
		color.b = 255/220.0;
		color.a = 1.0;
	}
	
	if (textureOb->color_id == COLOR::BLUE_ID)
	{
		color.r = 220/255.0;
		color.g = 255/255.0;
		color.b = 255/255.0;
		color.a = 1.0;
	}
}
       
void Star::Update_inSpace(int time, bool show_effect)
{}
    
    
void Star::Render_NEW()
{
        texture_offset1 += 0.0002;
        texture_offset2 += 0.0003;

        glUseProgram(g_SHADERS.multitexturing);

        glActiveTexture(GL_TEXTURE0);                                
        glBindTexture(GL_TEXTURE_2D, textureOb->texture);
        glUniform1i(glGetUniformLocation(g_SHADERS.multitexturing, "Texture_0"), 0);

        glActiveTexture(GL_TEXTURE1);                                
        glBindTexture(GL_TEXTURE_2D, textureOb->texture);
        glUniform1i(glGetUniformLocation(g_SHADERS.multitexturing, "Texture_1"), 1);
        
	glUniform2f(glGetUniformLocation(g_SHADERS.multitexturing, "displ"), texture_offset1, texture_offset2);

	renderMesh(mesh->glList, points.getCenter3f(), angle, data_planet.scale);

        glUseProgram(0);
        glActiveTexture(GL_TEXTURE0);
}
        
void Star::Render_OLD()
{    
	UpdateRotation();
     	
     	glBindTexture(GL_TEXTURE_2D, textureOb->texture);      		
	renderMesh(mesh->glList, points.getCenter3f(), angle, data_planet.scale);
}

void Star::UpdateInfo()
{ 
	info.clear();
    	info.addTitleStr("STAR");
    	info.addNameStr("id/ss_id:");    info.addValueStr(int2str(data_id.id) + " / " + int2str(starsystem->GetId()));
}

void Star::RenderInfo_inSpace(vec2f scroll_coords)
{ 
	UpdateInfo();
     	drawInfoIn2Column(&info.title_list, &info.value_list, points.getCenter().x, points.getCenter().y, scroll_coords.x, scroll_coords.y);
}

void Star::PostDeathUniqueEvent(bool)
{}

   
void Star::SaveDataUniqueStar(boost::property_tree::ptree& save_ptree, const std::string& root) const
{}

void Star::LoadDataUniqueStar(const boost::property_tree::ptree& load_ptree)
{}

void Star::ResolveDataUniqueStar()
{
	((StarSystem*)EntityManager::Instance().GetEntityById(data_unresolved_BaseGameEntity.starsystem_id))->Add(this); 	
}


void Star::SaveData(boost::property_tree::ptree& save_ptree) const
{
	std::string root = "star." + int2str(GetId())+".";
	SaveDataUniqueBase(save_ptree, root);
	SaveDataUniqueBaseGameEntity(save_ptree, root);
	SaveDataUniqueBasePlanet(save_ptree, root);
	SaveDataUniqueStar(save_ptree, root);
}

void Star::LoadData(boost::property_tree::ptree& load_ptree)
{
	LoadDataUniqueBase(load_ptree);
	LoadDataUniqueBaseGameEntity(load_ptree);
	LoadDataUniqueBasePlanet(load_ptree);
	LoadDataUniqueStar(load_ptree);
}

void Star::ResolveData()
{
	ResolveDataUniqueBase();
	ResolveDataUniqueBaseGameEntity();
	ResolveDataUniqueBasePlanet();
	ResolveDataUniqueStar();
}
