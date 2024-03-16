#include "functions.hpp"
#include<cmath>
#include<iostream>

namespace myfunctions{
    // definition of the armijo function
    std::vector<double> armijo(mystruct & data){
        unsigned int k=0;
        // x will be the x_k point, and will be updated, while x_old will be the x_(k-1) point 
        
        std::vector<double> x_old;
        double alpha=data.initial_step;
        // grad is the gradient in x_k
        std::vector<double> grad;
        grad=FD_gradient(data);
        // while loop for the update of the x, with all the needed conditions for stoppage of the loop
        double error_step=data.tolerance_step+1;
        while(k<data.maxiter && error_step>data.tolerance_step && norm(grad)>data.tolerance_grad){
            // update of x_old
            x_old=data.current_point;
            // computation of alpha_k with armijo rule
            alpha=data.initial_step;
            while(cond(data,alpha))
                {alpha=alpha/2;}
            // update of x
            grad=FD_gradient(data);
            data.current_point=data.current_point-alpha*grad;
            // increase the number of iterations done
            error_step=norm(data.current_point-x_old);
            ++k;
        }
        return data.current_point;
    }

    // cond is the function needed for the armijo condition on alpha
    bool cond(mystruct & data,double alpha){
        // computation of gradient
        std::vector<double> grad;
        grad=FD_gradient(data);
        // computation of left and right parts of inequality
        std::vector<double> x_grad;
        double value_left=data.f.Eval(); //-data.f.Eval(x - alpha * grad);
        data.current_point=data.current_point-alpha*grad;
        value_left-=data.f.Eval();
        data.current_point=data.current_point+alpha*grad;
        double norm_grad=std::pow(norm(grad),2);
        double value_right=(data.sigma*alpha)*norm_grad;
        // return the opposite condition because if this return false (i.e. the condition holds) then the loop stops
        return value_left<value_right;
    }

    // function for the computation of the norm of a vector, loop over the element, summing the squares then computing the square root
    double norm(std::vector<double> vec){
        double norm=0;
        for(std::size_t i=0;i<vec.size();++i){
            norm+=std::pow(vec[i],2);
        }
        return std::sqrt(norm);
    }

    std::vector<double> FD_gradient(mystruct & data){
        std::vector<double> x_old,grad;
        double f1,f2;
        x_old=data.current_point;
        // pointwisely computation of the gradient
        for(std::size_t i=0;i<data.current_point.size();++i){
            data.current_point[i]=x_old[i]-data.h;
            f1=data.f.Eval();
            data.current_point[i]=x_old[i]+data.h;
            f2=data.f.Eval();
            grad.emplace_back((f2-f1)/(2*data.h));
            data.current_point=x_old;
        }
        return grad;
    }
}

// operator for the difference of two vectors
std::vector<double> operator-(std::vector<double> v1,std::vector<double> v2){
    // if the size is different, then the smaller vector will be expanded with zeros
    std::size_t max=std::max(v1.size(),v2.size());
    v1.resize(max,0.0);
    v2.resize(max,0.0);
    std::vector<double> result;
    // difference element by element
    for(std::size_t i=0;i<max;++i){
        result.emplace_back(v1[i]-v2[i]);
    }
    return result;
}

std::vector<double> operator+(std::vector<double> v1,std::vector<double> v2){
    // if the size is different, then the smaller vector will be expanded with zeros
    std::size_t max=std::max(v1.size(),v2.size());
    v1.resize(max,0.0);
    v2.resize(max,0.0);
    std::vector<double> result;
    // difference element by element
    for(std::size_t i=0;i<max;++i){
        result.emplace_back(v1[i]+v2[i]);
    }
    return result;
}

// operator for the scalar - vector multiplication, loop over the vector elements, each one multiplied by the scalar
std::vector<double> operator*(double num,std::vector<double> vec){
    std::vector<double> result=vec;
    for(std::size_t i=0;i<vec.size();++i)
        result[i]=num*vec[i];
    return result;
}