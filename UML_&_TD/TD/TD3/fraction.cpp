#include <iostream>
#include "fraction.h"


using namespace MATH;
using namespace std;

/*    Initialisation par affectation
Fraction::Fraction(int n, int d):numerateur(n),denominateur(d){};
*/
Fraction::Fraction(int num, int den){
    numerateur=num;
    if(den!=0){
        denominateur=den;
    }else{
        denominateur=1;
        std::cout <<"Denominateur non valide, initialise a 1\n";
    }
    std::cout <<"objet cree adresse : " <<this <<std::endl;
    simplification();
}

void Fraction::setFraction(int n, int d){
    numerateur=n;
    if(d!=0)
        denominateur=d;
    else
        denominateur=1;
    simplification();
}

void Fraction::simplification(){
        if (numerateur==0){
            denominateur=1;
            return;
        }if (denominateur==0)
            return;
        int a=numerateur, b=denominateur;
        if (a<0)
            a=-a;
        if (b<0)
            b=-b;
        while(a!=b){
            if (a>b) a=a-b;
            else b=b-a;
        }
        numerateur/=a; denominateur/=a;
        if (denominateur<0) {
            denominateur=-denominateur;
            numerateur=-numerateur;
        }
}

void Fraction::somme(Fraction f1){
    int num, den;
    num=f1.getNumerateur()*getDenominateur()+f1.getDenominateur()*getNumerateur();
    den=f1.getDenominateur()*getDenominateur();
    setFraction(num,den);
}

/*
Fraction& Fraction::operator=(Fraction &f1){
    Fraction f;
    f.setFraction(f1.getNumerateur(), f1.getDenominateur());
}*/

Fraction Fraction::operator+(Fraction f){
    int num, den;
    num=f.getNumerateur()*denominateur+f.getDenominateur()*numerateur;
    den=f.getDenominateur()*denominateur;
    setFraction(num,den);
    return *this;
}

std::ostream& operator<<(std::ostream& f, const Fraction frac){
    f<<frac.getNumerateur () <<"/" <<frac.getDenominateur();
    return f;
}



