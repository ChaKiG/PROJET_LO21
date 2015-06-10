#ifndef FRACTION_H_INCLUDED
#define FRACTION_H_INCLUDED
#include <iostream>


namespace MATH{

class Fraction{
    public:

    Fraction(int num=0, int den=1);
    inline int getNumerateur()const {return numerateur;};
    inline int getDenominateur()const {return denominateur;};
    void setFraction(int n, int d);
    void somme(Fraction f2);
    void afficher(std::ostream &f);
    ~Fraction(){std::cout <<"objet supprimme adresse : " <<this <<std::endl;}



    Fraction operator+(MATH::Fraction f);
    Fraction operator=(MATH::Fraction &f1);

    private:

    int numerateur;
    int denominateur;
    void simplification();

};



}
std::ostream& operator<<(std::ostream& f, const MATH::Fraction frac);


#endif // FRACTION_H_INCLUDED
