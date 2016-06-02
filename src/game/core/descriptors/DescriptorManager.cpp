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

namespace {
const std::string fname = "data.txt";
} // namespace

DescriptorManager::DescriptorManager()
{}

DescriptorManager::~DescriptorManager()
{}

void
DescriptorManager::init()
{
    //generate();
    load();
}

void
DescriptorManager::add(const descriptor::Base& descriptor)
{
    const id_type id = descriptor.id();
    int type = descriptor.type();
    const auto it = m_descriptors.find(id);
    if (it != m_descriptors.end()) {
        throw std::runtime_error("descriptor with that id already exist");
    }
    m_descriptors.insert(std::make_pair(id, descriptor));

    const auto it2 = m_descriptorsTypes.find(type);
    if (it2 != m_descriptorsTypes.end()) {
        it2->second.push_back(descriptor);
    } else {
        std::vector<descriptor::Base> vector;
        vector.push_back(descriptor);
        m_descriptorsTypes[type] = vector;
    }
}

descriptor::Base
DescriptorManager::getRandom(const descriptor::Type& type)
{
    const auto it = m_descriptorsTypes.find(int(type));
    if (it != m_descriptorsTypes.end()) {
        const std::vector<descriptor::Base> descriptors = it->second;
        return meti::getRand(descriptors);
    }
    throw std::runtime_error("descriptor type doesn't contain any descriptors");
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
    filestream.open(fname);
    if(filestream.is_open()) {
        for(const auto& lists: m_descriptorsTypes) {
            const auto& list = lists.second;
            for(const descriptor::Base& descr: list) {
                filestream<<descr.data()<<std::endl;
            }
        }
    } else {
        throw std::runtime_error("not able to open file="+fname);
    }
    filestream.close();
}

void
DescriptorManager::load()
{
    clear();

    std::fstream filestream;
    std::string line;
    filestream.open(fname);
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

    clear();

    for(int i=0; i<num; ++i) {
        add(DescriptorGenerator::getNewBakDescriptor());
        add(DescriptorGenerator::getNewDriveDescriptor());
        add(DescriptorGenerator::getNewDroidDescriptor());
        add(DescriptorGenerator::getNewGrappleDescriptor());
        add(DescriptorGenerator::getNewScanerDescriptor());
        add(DescriptorGenerator::getNewRadarDescriptor());
        add(DescriptorGenerator::getNewProtectorDescriptor());
    }

    save();
}
