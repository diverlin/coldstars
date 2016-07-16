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

namespace descriptor {

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

Manager::Manager()
{
    bool force_generate = true;
    if (is_file_exists(descriptors_fname) && !force_generate) {
        load();
    } else {
        __generate();
    }
}

Manager::~Manager()
{}

void
Manager::add(const Base& descriptor)
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
            std::vector<Base> vector;
            vector.push_back(descriptor);
            m_descriptorsTypes[type] = vector;
        }
    }
}

Base
Manager::getRand(const Type& type)
{
    const auto it = m_descriptorsTypes.find(int(type));
    if (it != m_descriptorsTypes.end()) {
        const std::vector<Base> descriptors = it->second;
        return meti::getRand(descriptors);
    }
    throw std::runtime_error("descriptor type doesn't contain any descriptors, " + typeStr(type));
}

Base
Manager::get(const id_type& id)
{
    const auto it = m_descriptors.find(id);
    if (it != m_descriptors.end()) {
        return it->second;
    }
    throw std::runtime_error("descriptor id doesn't exist");
}

void
Manager::save()
{
    std::fstream filestream;
    filestream.open(descriptors_fname);
    if(filestream.is_open()) {
        for(const auto& lists: m_descriptorsTypes) {
            const auto& list = lists.second;
            for(const Base& descr: list) {
                filestream<<descr.data()<<std::endl;
            }
        }
    } else {
        throw std::runtime_error("not able to open file="+descriptors_fname);
    }
    filestream.close();
}

void
Manager::load()
{
    __clear();

    std::fstream filestream;
    std::string line;
    filestream.open(descriptors_fname);
    if(filestream.is_open()) {
        while(std::getline(filestream, line)) {
            if (!line.empty()) {
                const Base& descr = Base(line);
                add(descr);
            }
        }
    }
    filestream.close();
}

void
Manager::__clear()
{
    m_descriptors.clear();
    m_descriptorsTypes.clear();
}

void
Manager::__generate()
{
    create_file(descriptors_fname);

    __clear();

    int base = 1;
    int num = base * 20;
    for(int i=0; i<num; ++i) {
        // items
        add(Generator::getNewBakDescriptor());
        add(Generator::getNewDriveDescriptor());
        add(Generator::getNewDroidDescriptor());
        add(Generator::getNewGrappleDescriptor());
        add(Generator::getNewScanerDescriptor());
        add(Generator::getNewRadarDescriptor());
        add(Generator::getNewProtectorDescriptor());
        add(Generator::getNewBombDescriptor());
    }

    num = base * 10;
    for(int i=0; i<num; ++i) {
        // spaceobjects
        add(Generator::getNewVehicleDescriptor());
        add(Generator::getNewStarDescriptor());
        add(Generator::getNewPlanetDescriptor());
        add(Generator::getNewContainerDescriptor());
        //add(generator::getNewAsteroidDescriptor());
    }

    // world
    num = base * 10;
    for(int i=0; i<num; ++i) {
        add(Generator::getNewStarsystemDescriptor());
    }

    num = base * 4;
    for(int i=0; i<num; ++i) {
        add(Generator::getNewSectorDescriptor(m_starsystem.idList()));
    }

    num = base * 1;
    for(int i=0; i<num; ++i) {
        add(Generator::getNewGalaxyDescriptor(m_sector.idList()));
    }

    save();
}

} // namespace descriptor
