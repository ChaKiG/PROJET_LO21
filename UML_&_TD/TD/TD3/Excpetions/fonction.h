#ifndef FONCTION_H_INCLUDED
#define FONCTION_H_INCLUDED

namespace MATH{
class FractionException{
    char info[256];


public:
    class FractionException(const char * msg){
        strcpy(info, msg);
    }
    const char * getinfo(){
        return info;
    }

}

#endif // FONCTION_H_INCLUDED
