#include<iostream>
using namespace std ; 
class Employe {
    protected:
    int mat ;
    int nbenf ; 
    int* tabages ;
    float sal ;

    public:
    // constructeur usuel 
    Employe(int , int , float) ;
    // constructeur recopie 
    Employe(const Employe& ) ;
    // méthode affiche
    void Affiche () ;
    // méthode AvgAge
    float AvgAge() ;
    // méthode salNet
    float SalNet (float tauxIGR){return sal - (sal*tauxIGR) ;}
    // surdéfinition =
    Employe& operator =(Employe& ) ;
    // surdéfinition ==
    bool operator ==(Employe& ) ;
    // surdéfinition !=
    bool operator !=(Employe& e){return !(e == *this) ;}
} ;
///////////////////////////////////////////////////////////////////////////////////////   constructeur usuel
Employe::Employe(int mat = 0 , int nbenf = 0, float sal = 0.0f){
    this->sal = sal ;
    this->nbenf = nbenf ;
    this->mat = mat ;
    tabages = new int[this->nbenf] ;
}

///////////////////////////////////////////////////////////////////////////////////////   constructeur recopie
Employe::Employe(const Employe& e){
    mat = e.mat ; 
    nbenf = e.nbenf ;
    sal = e.sal ;
    tabages = new int[this->nbenf] ;
    for(int i = 0 ; i < nbenf ; i++)tabages[i] = e.tabages[i] ;
}

///////////////////////////////////////////////////////////////////////////////////////   méthode Affiche
void Employe::Affiche (){
        cout<<"Affichant les infos employe"<<endl ;
        cout<<"Matricule : "<<mat<<endl<<"Nombre enfants : "<<nbenf<<endl<<"Salaire brute : "<<sal<<endl ;
        cout<<"Les enfants:"<<endl;
        for(int i = 0 ;i < nbenf ; i++ ){
            cout<<"Enfant : "<<i<<" age : "<<tabages[i]<<endl ;
        }
    }

///////////////////////////////////////////////////////////////////////////////////////   méthode AvgAge
float Employe::AvgAge(){
        float s = 0 ;
        for(int i = 0 ; i < nbenf ; i++ ) s = s + tabages[i] ;
        return s / nbenf ;
    }

///////////////////////////////////////////////////////////////////////////////////////   surdéfinition =
Employe& Employe::operator =(Employe& e){
    mat = e.mat ; 
    nbenf = e.nbenf ;
    tabages = new int [nbenf] ;
    for(int i = 0 ; i < nbenf ; i++){
        tabages[i] = e.tabages[i] ;
    }
    sal = e.sal ;
    return *this ;
    }

///////////////////////////////////////////////////////////////////////////////////////   surdéfinition ==
bool Employe::operator ==(Employe& e){
    bool comparaiSalaire = (sal == e.sal) ;
    bool compAvgAge = (AvgAge() == e.AvgAge()) ;
    return (comparaiSalaire && compAvgAge) ;
    }

///////////////////////////////////////////////////////////////////////////////////////   class dérivée Directeur
class Directeur : public Employe {
    public :
    float prime ;
    // consructeur par défaut
    Directeur() :Employe() , prime(0.0f){}
    // consructeur recopie
    Directeur(const Directeur& ) ;
    // méthode Affiche
    void Affiche() ;
    // méthode SalNet
    float SalNet(float tauxIGR){return (sal - (sal*tauxIGR)) + prime ;}
    } ;
///////////////////////////////////////////////////////////////////////////////////////   constructeur recopie
Directeur::Directeur(const Directeur& d ){
        mat = d.mat ;
        nbenf = d.nbenf ;
        delete []tabages ;
        tabages = new int[nbenf] ;
        for(int i = 0 ; i < nbenf ; i++ ){
            tabages[i] = d.tabages[i] ;
        }
        sal = d.sal ;
        prime = d.prime ;
    }

///////////////////////////////////////////////////////////////////////////////////////   méthode Affiche
void Directeur::Affiche(){
    cout<<"Matricule : "<<mat<<endl<<"Nombre enfants : "<<nbenf<<endl<<"Salaire brute : "<<sal<<endl<<"Prime : "<<prime<<endl ;
    cout<<"Les enfants:"<<endl;
    for(int i = 0 ; i <nbenf ; i++ ){
        cout<<"Enfant : "<<i<<" age : "<<tabages[i]<<endl ;
    } 
    }   
int main (){
    return 0 ;
}
