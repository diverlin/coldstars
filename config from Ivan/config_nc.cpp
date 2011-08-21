#include "config_nc.h"

Config::Config()
{
	bind = "0.0.0.0";
	port = 1777;
	directory = "/var/tcloud/";
	pid_file="/var/run/tcloud-nc.pid";
	password="pass";
	connection="127.0.0.1";
}

void Config::setPort(int port){this->port = port;}
void Config::setBind(std::string bind){this->bind = bind;}
unsigned int Config::getPort() const { return port;}
std::string Config::getBind() const {return bind;}
std::string Config::get_connect() const {return connection;}
std::string Config::get_dir() const {return directory + "/";}
std::string Config::get_pid() const {return pid_file;}
std::string Config::get_pass() const {return password;}

Config Config::pConf()
{
  static Config test_c;
  return test_c;
}


void Config::read(std::string config_file)
{
    config_parser.parse(config_file);

    config_parser.get<std::string>("allow-connection",connection);
    config_parser.get<std::string>("directory",directory);
    config_parser.get<std::string>("pid-file",pid_file);
    config_parser.get<std::string>("password",password);
    config_parser.get_ip("listen",bind,port);

    config_parser.end();
    config_parser.~parser();
}

