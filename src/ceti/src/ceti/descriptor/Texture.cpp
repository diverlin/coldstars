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

#include "Texture.hpp"

#include <sstream>

namespace ceti {
namespace descriptor {

Texture::Texture(int type,
           const std::string& model,
           const std::string& texture,
           const glm::vec3& orientation)
    :
      Base(type)
    , m_model(model)
    , m_texture(texture)
    , m_orientation(orientation)
{
}

Texture::Texture(const std::string& data)
{
    std::stringstream ss;
    ss << data;
    boost::archive::text_iarchive ia(ss);
    ia >> *this;
}

Texture::~Texture()
{}

bool
Texture::operator==(const Texture& rhs) const
{
    return data() == rhs.data();
}

std::string
Texture::data() const
{
    std::stringstream ss;
    boost::archive::text_oarchive oa(ss);
    oa << *this;
    return ss.str();
}

} // namespace descriptor
} // namespace ceti
