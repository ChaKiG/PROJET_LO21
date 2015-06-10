#include <iostream>




/*////////////////////////      EXERCICE 17   ///////////////////////////
using namespace std;

struct personne {
    char nom[30];
    unsigned int age;
};

void raz(struct personne *per);
void affiche_struct(const struct personne *per);
void affiche_tab(const struct personne per[], int nb);
void init_struct(struct personne *per, char nom[30], int age);
void copy_struct(const struct personne per1, struct personne per2);
void copy_tab(const struct personne per1[], struct personne per2[], int nb);


void raz(struct personne *per){
    per->nom[0]='\0';
    per->age=0;
}

void affiche_struct(const struct personne *per){
    cout <<"nom : " <<per->nom;
    cout <<endl <<"age : " <<per->age <<endl;
}

void affiche_tab(const struct personne per[], int nb){
    for(int i(0); i<nb; i++)
        affiche_struct(per+i);
}

void init_struct(struct personne *per, char nom[30], int age){
    per->age=age;
    for(int i(0); i<30; i++)
        per->nom[i]=nom[i];
}

void copy_struct(const struct personne per1, struct personne per2){
    per2.age=per1.age;
    for(int i(0); i<30; i++)
        per2.nom[i]=per1.nom[i];
}

void copy_tab(const struct personne per1[], struct personne per2[], int nb){
    for(int i(0); i<nb; i++)
        copy_struct(per1[i], per2[i]);
}






int main()
{
    struct personne per;
    struct personne *p_per=&per;
    struct personne *pper = new struct personne[10];
    struct personne *pper2 = new struct personne[10];

    raz(p_per);
    affiche_struct(p_per);

    cout <<endl <<endl;
    init_struct(pper, "toto", 20);
    init_struct(pper+1, "jojo", 15);
    init_struct(pper+2, "momo", 5);
    affiche_tab(pper, 3);


    cout <<endl <<endl;
    copy_tab(pper,pper2,3);
    affiche_tab(pper, 3);


    delete pper[];
    delete pper2[];
    return 0;
}
*/



using namespace std;

struct compte {
    char id[20];
    int solde;
};

int& operation(compte t[], char nom[]){
    for(int i(0); i<sizeof(t); i++)
        if(strcmp(t[i].id,nom)==0){
            int& ref=t[i].solde;
            return ref;
        }
    //return null;
}



void essai_comptes(){
    compte tab[4]={ {"courant", 0},{"codevi", 1500 },{"epargne", 200 }, { "cel", 300 } };
    operation(tab,"courant")=100;
    operation(tab,"codevi")+=100;
    operation(tab,"cel")-=50;
    for(int i=0; i<4; i++)
        cout<<tab[i].id<<" : "<<tab[i].solde<<"\n";
}

int main(){
    essai_comptes();
    return 0;
}
