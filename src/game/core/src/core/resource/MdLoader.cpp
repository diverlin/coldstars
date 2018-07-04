#include "MdLoader.hpp"

#include <core/descriptor/Mesh.hpp>
#include <core/descriptor/Texture.hpp>

#include <ceti/StringUtils.hpp>
#include <ceti/FsUtils.hpp>
#include <ceti/Logger.hpp>

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>

#include <iostream>
#include <sstream>
#include <fstream>
#include <cassert>


MdLoader::MdLoader(const std::string& filepath)
{
    std::ifstream filestream;
    filestream.open(filepath.c_str());
     if (!filestream.is_open()) {
         std::cout<<"FAULT: Not abe to open file:"<<filepath<<std::endl;
         exit(EXIT_FAILURE);
     }
 
    std::string line;   
    unsigned int line_counter = 0;
    while(std::getline(filestream, line))
    {
        line_counter++;
        //LOG(filename+": line num="+std::to_string(line_counter)+" "+line);
        
        std::stringstream line_stream(line);
        std::string title;
        line_stream >> title;
        {
            if (title == "//" || title == "") {
                continue;
            } else {
                std::string val;
                line_stream >> val;
                m_data[title] = val;
            }
        }
    }

    filestream.close();
}

const std::string&
MdLoader::value(const std::string& key)
{
    auto it = m_data.find(key);
    assert(it != m_data.end());
    return m_data[key];
}


void
InfoLoader::read(const std::string& path, core::MeshDescr* mesh)
{
    LOG_DATA("managing "+path);
    boost::property_tree::ptree root;
    boost::property_tree::read_json(path, root);

    boost::optional<std::string> name = root.get_optional<std::string>("association.name");
    boost::optional<std::string> race = root.get_optional<std::string>("association.race");
    boost::optional<std::string> type = root.get_optional<std::string>("association.type");
    boost::optional<std::string> subtype = root.get_optional<std::string>("association.subtype");
    boost::optional<std::string> color = root.get_optional<std::string>("association.color");

    if (name) {
        mesh->setNameStr(name.get());
    }
    if (race) {
        mesh->setRaceStr(race.get());
    }
    if (type) {
        mesh->setTypeStr("mesh::" + type.get());
    }
    if (subtype) {
        mesh->setSubTypeStr(subtype.get());
    }
    if (color) {
        mesh->setColorStr(color.get());
    }

    std::string mesh_path = ceti::replace(path, ".od", ".obj");
    std::string material_path = ceti::replace(path, ".od", ".png");

    mesh->setModelPath(mesh_path);
    if (false) {
        mesh->setMaterialPath(material_path);
    }

    //assert(mesh->type() != NONE);
}

void
InfoLoader::read(const std::string& path, core::MaterialDescr* material)
{
    LOG_DATA("managing "+path);
    boost::property_tree::ptree root;
    boost::property_tree::read_json(path, root);

    boost::optional<std::string> name = root.get_optional<std::string>("association.name");
    boost::optional<std::string> race = root.get_optional<std::string>("association.race");
    boost::optional<std::string> type = root.get_optional<std::string>("association.type");
    boost::optional<std::string> subtype = root.get_optional<std::string>("association.subtype");
    boost::optional<std::string> color = root.get_optional<std::string>("association.color");

    if (name) {
        material->setNameStr(name.get());
    }
    if (race) {
        material->setRaceStr(race.get());
    }
    if (type) {
        material->setTypeStr("texture::" + type.get());
    }
    if (subtype) {
        material->setSubTypeStr(subtype.get());
    }
    if (color) {
        material->setColorStr(color.get());
    }

    boost::optional<float> brightThreshold = root.get_optional<float>("material.brightThreshold");
    boost::optional<int> row = root.get_optional<int>("material.row");
    boost::optional<int> col = root.get_optional<int>("material.col");
    boost::optional<float> fps = root.get_optional<float>("material.fps");
    boost::optional<bool> alpha = root.get_optional<bool>("material.alpha");
    boost::optional<bool> auto_rotated = root.get_optional<bool>("material.auto_rotated");

    if (brightThreshold) {
        material->setBrightThreshold(brightThreshold.get());
    }
    if (row) {
        if (row.get() > 0) {
            material->setRow(row.get());
        }
    }
    if (col) {
        if (col.get() > 0) {
            material->setCol(col.get());
        }
    }
    if (fps) {
        material->setFps(fps.get());
    }
    if (alpha) {
        material->setAlpha(alpha.get());
    }
    if (auto_rotated) {
        material->setAutoRotated(auto_rotated.get());
    }

    std::string img_base_path = ceti::replace(path, ".md", "");

    std::string img_texture_path = img_base_path + ".png";
    std::string img_normalmap_path = img_base_path + "_nm.png";

    assert(ceti::filesystem::is_file_exists(img_texture_path));
    material->setTexturePath(img_texture_path);

    if (ceti::filesystem::is_file_exists(img_normalmap_path)) {
        material->setNormalmapPath(img_normalmap_path);
    }

    // test
    //if (material->typeStr() == "texture::ship") {
        //material->setTexturePath("data/test1.png");
        //material->setNormalmapPath("data/test1_nm.png");
    //}

    assert(material->row() != 0);
    assert(material->col() != 0);

    //assert(material->type() != NONE);
}

