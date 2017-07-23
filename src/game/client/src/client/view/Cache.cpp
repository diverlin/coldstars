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

#include "Cache.hpp"

#include <core/manager/DescriptorManager.hpp>

#include <client/view/BaseView.hpp>

#include <jeti/Mesh.hpp>
#include <jeti/Material.hpp>


namespace view {

Cache::Cache()
{}

Cache::~Cache()
{}                                    

void
Cache::add(Base* view)
{
    __loadResourcesFor(view);
    m_cache.insert(std::make_pair(view->id(), view));
}

Base*
Cache::get(int_t id) const
{
    std::map<int_t, Base*>::const_iterator it = m_cache.find(id);
    if (it != m_cache.end()) {
        return it->second;
    }
    return nullptr;
}

void
Cache::__loadResourcesFor(Base* view)
{
    {
    jeti::control::Material* material = nullptr;

    int_t descritprorId = view->texture();
    auto it = m_materialCollector.find(descritprorId);
    if (it != m_materialCollector.end()) {
        material = it->second;
    } else {
        ceti::descriptor::Material* descriptor = descriptor::Manager::get().materials()->get(descritprorId);
        if (descriptor) {
            jeti::model::Material* model = new jeti::model::Material(descriptor);
            material = new jeti::control::Material(model);
        }
        assert(material);
        m_materialCollector.insert(std::make_pair(descritprorId, material));
    }
    view->setMaterial(material);
    }

    {
    jeti::Mesh* mesh = nullptr;

    int_t descritprorId = view->mesh();
    auto it = m_meshCollector.find(descritprorId);
    if (it != m_meshCollector.end()) {
        mesh = it->second;
    } else {
        ceti::descriptor::Mesh* descriptor = descriptor::Manager::get().meshes()->get(descritprorId);
        if (descriptor) {
            mesh = new jeti::Mesh(descriptor);
        }
        assert(mesh);
        m_meshCollector.insert(std::make_pair(descritprorId, mesh));
    }

    view->bindMesh(mesh);
    }
}

} // namespace view