// Markus Buchholz
// g++ diff_first_second.cpp -o t -I/usr/include/python3.8 -lpython3.8

#include <iostream>
#include <vector>
#include <cmath>
#include <tuple>
#include "matplotlibcpp.h"

namespace plt = matplotlibcpp;

double function(float xx)
{

    return 10 + 105 * std::pow(xx,2) - 70 * std::pow(xx,3);
}
//-----------------------------------------------------------

std::tuple<std::vector<float>, std::vector<float>, std::vector<float>> diffFirst(float start, float stop)
{
    auto h = 0.01;
    auto factor = 1.0f;
    std::vector<float> f_value;
    std::vector<float> x_value;
    std::vector<float> func;

    for (auto ii = start; ii <= stop; ii += h)
    {

        auto f = (function(ii + h) - function(ii)) / h;
        f_value.push_back(f / factor);
        x_value.push_back(ii);
        func.push_back(function(ii));
    }

    return std::make_tuple(x_value, f_value, func);
}
//-----------------------------------------------------------

std::tuple<std::vector<float>, std::vector<float>, std::vector<float>> diffSecond(float start, float stop)
{

    auto h = 0.01;
    auto factor = 0.001f;
    std::vector<float> f_value;
    std::vector<float> x_value;
    std::vector<float> func;

    for (auto ii = start; ii <= stop; ii += h)
    {

        // auto f = (function(ii + 2 * h) - 2 * function(ii + h) + function(ii)) / h * h;
        auto f = (function(ii + 1 * h) - 2 * function(ii) + function(ii - 1 * h)) / h * h;
        f_value.push_back(f / factor);
        x_value.push_back(ii);
        func.push_back(function(ii));
    }

    return std::make_tuple(x_value, f_value, func);
}


//-----------------------------------------------------------

void plotDiff(std::vector<float> xX, std::vector<float> diff1, std::vector<float> diff2, std::vector<float> func)
{

    plt::title("Numerical Differentiation");
    plt::named_plot("velocity", xX, diff1);
    plt::named_plot("acceleration", xX, diff2);
    plt::named_plot("path", xX, func);
    plt::xlabel("X");
    plt::ylabel("Y");
    plt::legend();
    plt::show();
}

//-----------------------------------------------------------

int main()
{

    auto diff1 = diffFirst(0.0f, 1.0f);
    auto diff2 = diffSecond(0.0f, 1.0f);
    plotDiff(std::get<0>(diff1), std::get<1>(diff1), std::get<1>(diff2), std::get<2>(diff1));
}