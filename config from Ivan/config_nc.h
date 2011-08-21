#ifndef CONFIG_H
#define CONFIG_H

#include <string>
#include <config.hpp>
#include <boost/utility.hpp>

class Config:private boost::noncopyable
{
  public:
  void setPort(int port);
  void setBind(std::string bind);
  unsigned int getPort() const;
  std::string getBind() const;
  std::string get_connect() const;
  std::string get_dir() const;
  std::string get_pid() const;
  std::string get_pass() const;
  void read(std::string config_file);
  static Config pConf();
  private:
  Config();
  ~Config();

  std::string bind;
  std::string connection;
  std::string directory;
  std::string pid_file;
  std::string password;
  int port;

  name_parser::parser config_parser;
};

#endif // CONFIG_G
