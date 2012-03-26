#include "config.cpp"
#include "iostream"
int main(int argc,char** argv)
{
  std::cout<<Config::instance().USE_MODERN_HW<<std::endl;
  return 0;
}
