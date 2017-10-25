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

#include "Data.hpp"
#include <common/constants.hpp>
#include <common/Config.hpp>
#include <common/Global.hpp>
#include <client/common/global.hpp>

#include <core/session/Shortcuts.hpp>
#include <core/manager/DescriptorManager.hpp>
#include <core/generator/DescriptorGenerator.hpp>

//#include <jeti/ShaderLoader.hpp>
#include <jeti/Mesh.hpp>
//#include <jeti/Screen.hpp>
//#include <ceti/descriptor/Collector.hpp>
#include <ceti/FsUtils.hpp>
//#include <ceti/MdLoader.hpp>
#include <ceti/StringUtils.hpp>

#include "TextureCollector.hpp"
#include "GuiTextureObCollector.hpp"

#include <core/session/Shortcuts.hpp>

#include <ceti/type/IdType.hpp>
#include <core/type/RaceType.hpp>
#include <core/type/MeshType.hpp>
#include <core/type/TechLevelType.hpp>
#include <core/type/TextureType.hpp>

#include <string>


Data::Data()
{
    __generate();
}

Data::~Data()
{
}

void Data::__generate()
{
    __generateMeshDescriptors();
    __generateMaterialDescriptors();
    __generateGameObjectDescriptors();
}

void Data::__generateMeshDescriptors()
{        
    auto dmm = core::shortcuts::descriptors()->meshes();
    if (!dmm->loaded()) {
        auto result = ceti::filesystem::getFilesList("data", ".od");
        const auto& types = core::shortcuts::types();
        dmm->generate(result, types);
    }
}

void Data::__generateGameObjectDescriptors()
{
    core::shortcuts::descriptors()->generate();
}

void Data::__generateMaterialDescriptors()
{
    auto dmm = core::shortcuts::descriptors()->materials();
    if (!dmm->loaded()) {
        auto result = ceti::filesystem::getFilesList("data", ".md");
        const auto& types = core::shortcuts::types();
        dmm->generate(result, types);
    }
}


