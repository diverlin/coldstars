#include "config.hpp"
namespace name_parser
{
	int line_number(std::fstream& in)
	{
		// line of error
		int line = 1;
		char ch;
		int position = in.tellg();
		in.seekg (0, std::ios::beg);
		for(int i=0;i<position;++i,in.get(ch))
			if(ch=='\n')++line;
		return line;
	}
	parser::parser()
	{
		include_=0;
	}
	void parser::end()
	{
		if(!config.empty())
		{
			std::string error_list;
			for(config_map::iterator it=config.begin();it!=config.end();it++)
				error_list+=it->first + ' ' + it->second + '\n';
			throw std::runtime_error("Wrong parameters :\n" + error_list);
		}
	}
	void parser::parse(const string& file_name)
	{
		in.open(file_name.c_str());
		get_pair();
		in.close();
		if(include_!=0)
			throw std::runtime_error("Not found '}'. Bad end file ");
	}

	template <typename return_type>
	bool parser::get(const string& str,return_type& out_val)
	{
    try
    {
      config_map::iterator it = config.find(str);
      if(it==config.end())
        return false;
      std::string out = it->second;
      config.erase(it);
      out_val = boost::lexical_cast<return_type>(out);
      return true;
    }
    catch(boost::bad_lexical_cast&)
    {
      throw std::runtime_error("Wrong value on parametr " + str);
    }
	}

	bool parser::get_ip(const string& str,string& out,int& port)
	{
		string temp;
    if(! get<std::string>(str,temp) )
      return false;
		out=temp.substr(0,temp.find_last_of(':'));
		port = atoi(temp.substr(temp.find_last_of(':')+1).c_str());
    return true;
	}

	void parser::del_includes()
	{
		while(ch=='}'&&in)
		{
			prefix=prefix.substr(0,prefix.find_last_of('.'));
			prefix=prefix.substr(0,prefix.find_last_of('.')+1);
			--include_;
			comment();
		}
	}
	void parser::comment()
	{
		for(in>>ch; ch =='/'&&in;in>>ch)
		{
			char temp;
			in.get(temp);
			switch (temp)
			{
				case '/':
					while(temp!='\n'&&in)
						in.get(temp);
					break;
				case '*':
					while(in)
					{
						while(ch!='*'&&in)
							in>>ch;
						in.get(temp);
						if(temp=='/')
							break;
					}
					if(!in)
						throw std::runtime_error("Bad end file. Close comment");
					break;
				default:
					in.putback(temp);
					return ;
			}
		}
	}

	void parser::get_pair()
	{
		comment();
		while(in)
		{
			std::string first,second;

			get_id(first);
			in>>ch;
			if(ch=='{')
			{
				++include_;
				prefix+=first+'.';
				comment();
			}
			else
			{
				if(!(isalpha(ch)||isdigit(ch)||ch=='\"'))
					throw std::runtime_error("Bad value. On line " + boost::lexical_cast<std::string>(line_number(in)) + " Use \" \"? ");
				get_val(second);

				std::string add_id(prefix+first);
				config_line add(add_id,second);
				config_map::iterator it = config.find(add_id);
				if(it!=config.end())
					throw std::runtime_error("conflicts with previous declaration "+add_id+" in config file");
				config.insert(add);

				comment();
				del_includes();
			}
		}
	}

	void parser::get_id(string& out_str)
	{
		int i = 0;
		while(in&&(isalpha(ch)||isdigit(ch)||ch=='_'||ch=='-'))
		{
			++i;
			out_str+=ch;
			in.get(ch);
		}
		if(!in||!isspace(ch)||i==0)
		{
			in.putback(ch);
			std::string error_str;
			in>>error_str;
			throw std::runtime_error("Wrong synbols "+error_str + " On line " + boost::lexical_cast<std::string>(line_number(in)));
		}
	}

	void parser::get_val(string& out_str)
	{
		if(ch=='\"')
		{
			in.get(ch);
			while(in)
			{
				if(ch=='\"')
					break;
				out_str+=ch;
				in.get(ch);
				if(ch=='\\')
				{
					in.get(ch);
					if(ch=='\n')
					{
						while(isspace(ch))
							in>>ch;
					}
					else
						out_str+=ch;
				}
				if(ch=='\n')
					throw std::runtime_error("Bad value \'" + out_str + "\'. On line " + boost::lexical_cast<std::string>(line_number(in)));
			}
			if(!in)
				throw std::runtime_error("Not found \'\"\'. Bad end file");
			in>>ch;
		}
		else
			while(in&&ch!=';'&&!isspace(ch))
			{
				out_str+=ch;
				in.get(ch);
			}
		if(isspace(ch))
			in>>ch;
		if(ch!=';')
    {
			if(in)
				throw std::runtime_error("Not found ';' On line " + boost::lexical_cast<std::string>(line_number(in)));
			else
				throw std::runtime_error("Not found ';'. Bad end file");
    }
	}
} // end namespace parser
