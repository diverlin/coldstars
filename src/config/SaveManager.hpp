#ifndef SAVEMANAGER_HPP
#define SAVEMANAGER_HPP

#include <boost/property_tree/info_parser.hpp>
#include <boost/property_tree/ptree.hpp>

struct SaveManager
{
	public:
		static SaveManager& Instance();
		
		template <typename T>
		void Put(std::string, T);
		void DumpToFile();
								
	private:
		SaveManager();
		SaveManager(const SaveManager&);
		~SaveManager();
		SaveManager& operator=(const SaveManager&);
		
		boost::property_tree::ptree ptree;
};

#endif //SAVEMANAGER_HPP
