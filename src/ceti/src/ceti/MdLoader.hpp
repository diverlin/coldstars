
#pragma once

#include <string>
#include <map>

namespace ceti {

class MdLoader
{ 
    public:        
        MdLoader(const std::string&);
        ~MdLoader() {}
    
        std::map<std::string, std::string> data() const { return m_data; }

    private:
        std::map<std::string, std::string> m_data;
};

} // namespace ceti
