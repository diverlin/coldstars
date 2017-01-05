
#pragma once

#include <string>
#include <map>

namespace ceti {

namespace descriptor {
class Mesh;
class Material;
}

class MdLoader
{ 
    public:        
        MdLoader(const std::string&);
        ~MdLoader() {}
    
        const std::map<std::string, std::string>& data() const { return m_data; }
        const std::string& value(const std::string& key);

    private:
        std::map<std::string, std::string> m_data;
};

class InfoLoader
{
public:
    InfoLoader()=default;
    ~InfoLoader()=default;

    static void read(const std::string&, ceti::descriptor::Mesh*);
    static void read(const std::string&, ceti::descriptor::Material*);
};

} // namespace ceti
