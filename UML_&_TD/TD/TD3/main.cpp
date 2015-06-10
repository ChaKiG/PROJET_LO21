#include <iostream>
#include "fraction.h"

using namespace std;
using namespace MATH;

int main()
{
    MATH::Fraction f(12,5);
    MATH::Fraction f2(5,2);
    MATH::Fraction S;
    MATH::Fraction &ref=f;

    std::cout <<" num : " <<f.getNumerateur() <<std::endl;
    std::cout <<" den : " <<f.getDenominateur() <<std::endl;


    cout<<ref;
    f+f2;


    //f.somme(f2);

    std::cout <<"Somme de 12/5 et 5/2\n";
    std::cout <<" num : " <<f.getNumerateur() <<std::endl;
    std::cout <<" den : " <<f.getDenominateur() <<std::endl;

}


