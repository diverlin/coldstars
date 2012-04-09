#ifndef SAVEMANAGER_HPP
#define SAVEMANAGER_HPP

#include <boost/property_tree/info_parser.hpp>
#include <boost/property_tree/ptree.hpp>

struct SaveManager
{
	public:
		static SaveManager& Instance();
		
		void SaveFile(const std::string&, boost::property_tree::ptree&) const;
		void LoadFile(const std::string&, boost::property_tree::ptree&) const;
					
	private:
		SaveManager();
		SaveManager(const SaveManager&);
		~SaveManager();
		SaveManager& operator=(const SaveManager&);
};

#endif //SAVEMANAGER_HPP
