#include <iostream>

using namespace std;





int main()
{


   //FONCTIONS



    try{
        fraction f(1,1);
        f.setFraction(1,0);
    }
    catch (const char * info){
        cout <<info <<std::endl;
    }
    catch(const FractionException & exception){
        cout <<exception.getinfo() <<endl;
    return 0;
}
