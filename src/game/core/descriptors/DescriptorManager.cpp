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

#include "DescriptorManager.hpp"
#include <descriptors/DescriptorGenerator.hpp>
#include <meti/RandUtils.hpp>

#include <fstream>

#include <boost/filesystem.hpp>
using namespace boost::filesystem;

namespace {
const std::string descriptors_fname = "descriptors.txt";

bool is_file_exists(const std::string& fname)
{
    boost::filesystem::path p(fname);
    if (!boost::filesystem::exists(p)) {
        return false;
    }
    if (!boost::filesystem::is_regular_file(p)) {
        return false;
    }

    return true;
}

bool create_file(const std::string& fname)
{
    std::fstream file(fname, std::ios::out | std::ios::app);
    file.close();
}

} // namespace

DescriptorManager::DescriptorManager()
{
    if (is_file_exists(descriptors_fname)) {
        load();
    } else {
        generate();
    }
}

DescriptorManager::~DescriptorManager()
{}

void
DescriptorManager::add(const descriptor::Base& descriptor)
{
    //std::cout<<"add descriptor with type"<<descriptor::typeStr((descriptor::Type)descriptor.type())<<std::endl;
    const id_type id = descriptor.id();
    int type = descriptor.type();

    {
        const auto it = m_descriptors.find(id);
        if (it != m_descriptors.end()) {
            throw std::runtime_error("descriptor with that id already exist");
        }
        m_descriptors.insert(std::make_pair(id, descriptor));
    }

    {
        const auto it = m_descriptorsTypes.find(type);
        if (it != m_descriptorsTypes.end()) {
            it->second.push_back(descriptor);
        } else {
            std::vector<descriptor::Base> vector;
            vector.push_back(descriptor);
            m_descriptorsTypes[type] = vector;
        }
    }
}

descriptor::Base
DescriptorManager::getRand(const descriptor::Type& type)
{
    const auto it = m_descriptorsTypes.find(int(type));
    if (it != m_descriptorsTypes.end()) {
        const std::vector<descriptor::Base> descriptors = it->second;
        return meti::getRand(descriptors);
    }
    throw std::runtime_error("descriptor type doesn't contain any descriptors, " + descriptor::typeStr(type));
}

descriptor::Base
DescriptorManager::get(const id_type& id)
{
    const auto it = m_descriptors.find(id);
    if (it != m_descriptors.end()) {
        return it->second;
    }
    throw std::runtime_error("descriptor id doesn't exist");
}

void
DescriptorManager::save()
{
    std::fstream filestream;
    filestream.open(descriptors_fname);
    if(filestream.is_open()) {
        for(const auto& lists: m_descriptorsTypes) {
            const auto& list = lists.second;
            for(const descriptor::Base& descr: list) {
                filestream<<descr.data()<<std::endl;
            }
        }
    } else {
        throw std::runtime_error("not able to open file="+descriptors_fname);
    }
    filestream.close();
}

void
DescriptorManager::load()
{
    clear();

    std::fstream filestream;
    std::string line;
    filestream.open(descriptors_fname);
    if(filestream.is_open()) {
        while(std::getline(filestream, line)) {
            if (!line.empty()) {
                const descriptor::Base& descr = descriptor::Base(line);
                add(descr);
            }
        }
    }
    filestream.close();
}

void
DescriptorManager::clear()
{
    m_descriptors.clear();
    m_descriptorsTypes.clear();
}

void DescriptorManager::generate()
{
    int num = 20;

    create_file(descriptors_fname);

    clear();

    for(int i=0; i<num; ++i) {
        // items
        add(DescriptorGenerator::getNewBakDescriptor());
        add(DescriptorGenerator::getNewDriveDescriptor());
        add(DescriptorGenerator::getNewDroidDescriptor());
        add(DescriptorGenerator::getNewGrappleDescriptor());
        add(DescriptorGenerator::getNewScanerDescriptor());
        add(DescriptorGenerator::getNewRadarDescriptor());
        add(DescriptorGenerator::getNewProtectorDescriptor());
        add(DescriptorGenerator::getNewBombDescriptor());

        // spaceobjects
        add(DescriptorGenerator::getNewStarsystemDescriptor());
        add(DescriptorGenerator::getNewVehicleDescriptor());
        add(DescriptorGenerator::getNewStarDescriptor());
        add(DescriptorGenerator::getNewPlanetDescriptor());
        add(DescriptorGenerator::getNewContainerDescriptor());
        //add(DescriptorGenerator::getNewAsteroidDescriptor());

        // world
        add(DescriptorGenerator::getNewStarsystemDescriptor());
    }

    save();
}
