#include <string>
#include <iostream>

void plus1(int& y)
{
       ++y;
}

void plus2(int y)
{
       ++y;
}

int main(int argc,char **argv)
{
        int x = 5;
        std::cout<<"X = ";
        std::cout<<x<<std::endl;
        plus1(x);
        std::cout<<"А теперь X = ";
        std::cout<<x<<std::endl;
        plus2(x);
        std::cout<<"Если не указывать & то X = ";
        std::cout<<x<<std::endl;
        return 0;
}
