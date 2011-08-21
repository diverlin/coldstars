#ifndef config_h
#define config_h
#include <string>
#include <fstream>
#include <map>
#include <stdlib.h>
#include <stdexcept>
#include <boost/lexical_cast.hpp>

namespace name_parser
{
	int line_number(std::fstream& in);
	typedef std::pair < std::string, std::string > config_line;
	typedef std::map < std::string, std::string > config_map;
	using std::string;
	using std::fstream;

	class parser
	{
		public:
			parser();
			void end();
			void parse(const string& file_name);

			template <typename return_type>
			bool get(const string& str,return_type& out_val);
			bool get_ip(const string& str,string& out,int& port);
		private:

			config_map config;
			fstream in;
			char ch;
			int include_;
			std::string prefix;

			void del_includes();
			void comment();

			void get_pair();

			void get_id(string& out_str);
			void get_val(string& out_str);
	};
} // end namespace parser
#endif // config_h
