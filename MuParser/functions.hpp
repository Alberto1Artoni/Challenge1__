#include<functional>
#include<vector>
#include<cmath>
#include "muparser_fun.hpp"

// creation of a namespace for my methods and struct 
namespace myfunctions{

// definition of the struct, with the function, its gradient and all the parameters
struct mystruct{
    MuparserFun f;
    std::vector<double> initial_point{0.0,0.0};
    double tolerance_step=0.1;
    double tolerance_grad=0.1;
    double initial_step=1;
    unsigned int maxiter=100;
    double sigma=0.4;
    double h=1e-4;
};

// declaration of all the methods I'll need
std::vector<double> armijo(mystruct);

bool cond(mystruct,double,std::vector<double>);

double norm(std::vector<double>);

std::vector<double> FD_gradient(mystruct, std::vector<double>);

}

// to make the code easier to read, I define these 2 operators for making the difference between two vectors and the muliplication between a scalar and a vector
std::vector<double> operator-(std::vector<double>,std::vector<double>);

std::vector<double> operator*(double,std::vector<double>);