#include "MdLoader.hpp"

#include <iostream>
#include <sstream>
#include <fstream>

namespace ceti {

MdLoader::MdLoader(const std::string& filepath)
{
    std::ifstream filestream;
    filestream.open(filepath.c_str());
     if (!filestream.is_open()) {
         std::cout<<"FAULT: Not abe to open file:"<<filepath;
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

} // namespace ceti
