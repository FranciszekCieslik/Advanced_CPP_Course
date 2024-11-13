#include "cpplab.h"

int main()
{
    cpplab::vector<std::string> vs = {"jeden", "dwa", "trzy"};
    std::vector<std::string> us = {"jeden", "dwa", "trzy"};

    cpplab::vector<char> vc = {'0', '2', '4'};
    std::vector<char> uc{'1', '2', '3'};
    
    // std::cout<< "\n" << vs * us << 
    // "\n" << vc * uc << "\n" <<  vs * uc << "\n\n";

    cpplab::vector<int> vi = {1,2,3};
    std::vector<int> ui = {1,2,3};

    cpplab::vector<double> vd = {0.25,0.5,0.75};
    std::vector<double> ud = {0.25,0.5,0.75};

    std::cout<< "\n" << vi * ui << 
    "\n" << vd * ud << "\n" <<  vd * ui << "\n\n";
}