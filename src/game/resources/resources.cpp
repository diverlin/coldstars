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

#include "resources.hpp"
#include "../render/ShaderLoader.hpp"
#include "../render/Screen.hpp"
#include "MeshCollector.hpp"
#include "../render/Mesh.hpp"
#include "TextureManager.hpp"
#include "GuiTextureObCollector.hpp"

#include <types/MyInt.hpp>
#include <types/MeshTypes.hpp>

#include <common/constants.hpp>


void loadGameData()
{        
    load3DModels();
    loadImages();
    loadShaders();
}

void load3DModels()
{        
    MeshCollector::Instance().RegisterMesh(new Mesh(TYPE::MESH::PLANE_ID,           DATA_PATH+"obj/plane/plane.obj",   glm::vec3(0.0f, 0.0f, 1.0f), nullptr));
    MeshCollector::Instance().RegisterMesh(new Mesh(TYPE::MESH::SPHERE_ID,          DATA_PATH+"obj/sphere/sphere.obj", glm::vec3(1.0f, 0.0f, 0.0f), nullptr));
    MeshCollector::Instance().RegisterMesh(new Mesh(TYPE::MESH::SPHERE_DEFORMED_ID, DATA_PATH+"obj/sphere_deformed/sphere_deformed.obj", glm::vec3(1.0f, 0.0f, 0.0f), nullptr));
}



void loadImages()
{
//################################# TYPE::TEXTURE::STAR_ID ###############################
{
    MaterialDrawData material_data;
    material_data.texture_path = DATA_PATH+"star/s_000.jpg";
    material_data.brightThreshold = 1.9f;
    material_data.color_id = COLOR::YELLOW_ID;
    TextureOb* textureOb = new TextureOb(material_data);

    MaterialAssociationData association_data;
    association_data.type_id    = TYPE::TEXTURE::STAR_ID; 
    textureOb->SetAssociation(association_data);

    TextureManager::Instance().Add(textureOb);
}

{
    MaterialDrawData material_data;
    material_data.texture_path = DATA_PATH+"star/s_001.png";
    material_data.brightThreshold = 1.825f;
    material_data.color_id = COLOR::YELLOW_ID;
    TextureOb* textureOb = new TextureOb(material_data);

    MaterialAssociationData association_data;
    association_data.type_id    = TYPE::TEXTURE::STAR_ID; 
    textureOb->SetAssociation(association_data);

    TextureManager::Instance().Add(textureOb);
}

{
    MaterialDrawData material_data;
    material_data.texture_path = DATA_PATH+"star/s_100.jpg";
    material_data.brightThreshold = 2.525f;
    material_data.color_id = COLOR::BLUE_ID;
    TextureOb* textureOb = new TextureOb(material_data);

    MaterialAssociationData association_data;
    association_data.type_id    = TYPE::TEXTURE::STAR_ID; 
    textureOb->SetAssociation(association_data);

    TextureManager::Instance().Add(textureOb);
}

{
    MaterialDrawData material_data;
    material_data.texture_path = DATA_PATH+"star/s_101.png";
    material_data.brightThreshold = 1.925f;
    material_data.color_id = COLOR::BLUE_ID;
    TextureOb* textureOb = new TextureOb(material_data);

    MaterialAssociationData association_data;
    association_data.type_id    = TYPE::TEXTURE::STAR_ID; 
    textureOb->SetAssociation(association_data);

    TextureManager::Instance().Add(textureOb);
}



}



void loadShaders()
{
    Shaders shaders;
    shaders.base            = compileProgram(SHADERS_PATH+"base.vert",              SHADERS_PATH+"base.frag");
    shaders.black2alpha     = compileProgram(SHADERS_PATH+"black2alpha.vert",       SHADERS_PATH+"black2alpha.frag");
    shaders.shockwave       = compileProgram(SHADERS_PATH+"shockwave.vert",         SHADERS_PATH+"shockwave.frag");
    shaders.volumetriclight = compileProgram(SHADERS_PATH+"volumetricLight.vert",   SHADERS_PATH+"volumetricLight.frag");
    shaders.light           = compileProgram(SHADERS_PATH+"light.vert",             SHADERS_PATH+"light.frag");
    shaders.light_normalmap = compileProgram(SHADERS_PATH+"light_normalmap.vert",   SHADERS_PATH+"light_normalmap.frag");
    shaders.blur            = compileProgram(SHADERS_PATH+"blur.vert",              SHADERS_PATH+"blur.frag");
    shaders.extractbright   = compileProgram(SHADERS_PATH+"extractBright.vert",     SHADERS_PATH+"extractBright.frag");
    shaders.combine         = compileProgram(SHADERS_PATH+"combine.vert",           SHADERS_PATH+"combine.frag");
    shaders.multitexturing  = compileProgram(SHADERS_PATH+"multitex.vert",          SHADERS_PATH+"multitex.frag");
    shaders.blank           = compileProgram(SHADERS_PATH+"blank.vert",             SHADERS_PATH+"blank.frag");
    shaders.fogwarspark     = compileProgram(SHADERS_PATH+"fogwarspark.vert",       SHADERS_PATH+"fogwarspark.frag");   
    shaders.flash           = compileProgram(SHADERS_PATH+"flash.vert",             SHADERS_PATH+"flash.frag");
    shaders.mask            = compileProgram(SHADERS_PATH+"mask.vert",              SHADERS_PATH+"mask.frag");
    shaders.particle        = compileProgram(SHADERS_PATH+"particle.vert",          SHADERS_PATH+"particle.frag");
    shaders.starfield       = compileProgram(SHADERS_PATH+"starfield.vert",         SHADERS_PATH+"starfield.frag");
    
    Screen::Instance().GetRender().SetShaders(shaders);
}
