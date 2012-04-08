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
		template <typename T>
		T Get(std::string);
		
		void SaveFile(const std::string&);
		void LoadFile(const std::string&);
							
		void SaveDebug(const std::string&, const boost::property_tree::ptree&) const;
					
	private:
		SaveManager();
		SaveManager(const SaveManager&);
		~SaveManager();
		SaveManager& operator=(const SaveManager&);
		
		boost::property_tree::ptree ptree;
		std::vector<boost::property_tree::ptree> starsystem_subptree_vec;
		std::vector<boost::property_tree::ptree> star_subptree_vec;
		std::vector<boost::property_tree::ptree> planet_subptree_vec;
		
		friend class EntityManager;
};

#endif //SAVEMANAGER_HPP
