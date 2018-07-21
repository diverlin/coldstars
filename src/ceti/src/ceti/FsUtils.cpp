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

#include "FsUtils.hpp"
#include "StringUtils.hpp"

#include <boost/filesystem.hpp>

#include <fstream>

namespace ceti {
namespace filesystem {

std::vector<std::string>
getFilesList(const std::string& root, const std::string& ext) {
    using namespace boost::filesystem;
    std::vector<std::string> result;
    auto files = recursive_directory_iterator(root);
    for(const auto& p: files) {
        if (is_regular_file(p)) {
            if ((p.path().extension() == ext) || (ext == ".*")) {
                result.push_back(p.path().string());
            }
        }
    }

    return result;
}


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
    return true;
}

void touch_file(const std::string& fname)
{
    if (!is_file_exists(fname)) {
        create_file(fname);
    }
}

std::string add_suffix(const std::string& path, const std::string& suffix)
{
    std::string result(path);
    std::string extension(get_extension(result));
    result = ceti::replace(result, extension, "");
    result += suffix;
    result += extension;
    return result;
}

std::string get_extension(const std::string& path)
{
    unsigned long begin = path.find_last_of('.');
    unsigned long end = path.length();
    unsigned long size = end - begin;
    return path.substr(begin, size);
}


} // namespace filesystem
} // namespace ceti
