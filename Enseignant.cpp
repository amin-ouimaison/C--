#include<iostream>
#include<string.h>
using namespace std ; 

class Enseignant  {

    protected:
    string nom ;
    string prenom ;
    int nbseances ;
    double *tabseances ;
    int charge_status ;
    
    public : 
    // constructeur usuel 
    Enseignant( string , string , int  , int  );
    // consructeur de recopie
    Enseignant(const Enseignant& );  
    // destructeur
    ~Enseignant();
    // surdéfinition <<
    friend ostream& operator << (ostream&  , const Enseignant&  ) ;
    // surdéfinition >>
    friend istream& operator >> (istream& , Enseignant& ) ;
    // surdéfinition =
    Enseignant& operator = (const Enseignant& ) ;
    // méthode Charge
    double Charge ()  const;
    // méthode HeuresSup
    bool HeuresSup () ;
    // méthode 
    double Honoraires(double );
    // surdéfinition ==
    bool operator == (const Enseignant& ) ;
    // surdéfinition !=
    bool operator != (const Enseignant& ) ;
    // surdéfinition <
    bool operator < (const Enseignant& ) ;
    // surdéfinition >
    bool operator > (const Enseignant& ) ;
} ;
///////////////////////////////////////////////////////////////////////////////////////   constructeur usuel
Enseignant::Enseignant( string nom , string prenom , int nbseances , int charge_status ){
    this->nom = nom ; 
    this->prenom = prenom ;
    this->nbseances = nbseances ;
    this->tabseances =new double[nbseances] ;
} 

///////////////////////////////////////////////////////////////////////////////////////   constructeur recopie
Enseignant::Enseignant(const Enseignant& tmp):
 nom(tmp.nom) , prenom(tmp.prenom) , nbseances(tmp.nbseances) , charge_status(tmp.charge_status) , tabseances(new double[nbseances]) {
    for(int i = 0 ; i < nbseances ; i++)tabseances[i] = tmp.tabseances[i] ;
 }

///////////////////////////////////////////////////////////////////////////////////////   destructeur
Enseignant::~Enseignant() {
    delete[] tabseances;
}

///////////////////////////////////////////////////////////////////////////////////////   surdéfinition <<
ostream& operator <<(ostream& output , const Enseignant& tmp ) {
    output<<"Enseignant "<<tmp.prenom<<" "<<tmp.nom<<" il a "<<tmp.nbseances<<" seances et un minimum de "<<tmp.charge_status<<" heures par semaine"<<endl ;
     for(int i = 0 ; i < tmp.nbseances; i++)output<<"seance "<<i+1<<" : "<<tmp.tabseances[i]<<endl ;
    return output ;
}

///////////////////////////////////////////////////////////////////////////////////////   surdéfinition >>
istream& operator >>(istream& input, Enseignant& tmp){
    cout<<"entrer le nom "<<endl ;
    input>>tmp.nom ;
    cout<<"entrer le prenom "<<endl ;
    input>>tmp.prenom ;
    do{
        cout<<"entrer le nombre des seances "<<endl ;
        input>>tmp.nbseances ;
    }while(tmp.nbseances < 0) ;
    do{
    cout<<"entre le nombre minimale des heures "<<endl ;
        input>>tmp.charge_status ;
    }while(tmp.charge_status < 0) ;
    for(int i = 0 ; i < tmp.nbseances ; i++){
        do{
            cout<<"entre la seance "<<i+1<<endl ;
            input>>tmp.tabseances[i] ;
            }while(tmp.tabseances[i] < 0) ;
            }
    return input ;
} 
///////////////////////////////////////////////////////////////////////////////////////   surdéfinition =
Enseignant& Enseignant:: operator =(const Enseignant& tmp) {
    if(this != &tmp){
        nom = tmp.nom ;
        prenom = tmp.prenom ;
        charge_status = tmp.charge_status ;
        nbseances = tmp.nbseances ;
        delete []tabseances ;
        tabseances = new double[nbseances] ;
        for(int i = 0 ; i < tmp.nbseances ; i++)
        tabseances[i] = tmp.tabseances[i] ;
        }
    return *this ;
}

///////////////////////////////////////////////////////////////////////////////////////   méthode Charge 
double Enseignant::Charge() const{
    int somme  = 0 ;
    for(int i = 0 ; i < nbseances ; i++){
        somme += tabseances[i] ;
    }
    return somme ;
}

///////////////////////////////////////////////////////////////////////////////////////   méthode HeuresSup
bool Enseignant::HeuresSup(){
    return (this->Charge() > charge_status) ;
}

///////////////////////////////////////////////////////////////////////////////////////   méthode Honoraires
double Enseignant::Honoraires(double tarif ){
    if(this->HeuresSup()) return (this->Charge()-charge_status)*tarif ;
    return 0 ;
}

///////////////////////////////////////////////////////////////////////////////////////   surdéfinition ==
bool Enseignant::operator ==( const Enseignant& tmp) {
    return (Charge() == tmp.Charge()) ;
}

///////////////////////////////////////////////////////////////////////////////////////   surdéfinition !=
bool Enseignant::operator !=(const Enseignant& tmp) {
    return !(*this == tmp) ;
}

///////////////////////////////////////////////////////////////////////////////////////   surdéfinition <
bool Enseignant::operator < (const Enseignant& tmp ) {
    return (this->Charge() < tmp.Charge()) ;
}

///////////////////////////////////////////////////////////////////////////////////////   surdéfinition >
 bool Enseignant::operator >(const Enseignant& tmp) {
     return !(*this < tmp) ;
 }
 
 class Responsable : public Enseignant {
    string nom_filier ;
    int nb_heure_responsable ;
    public:
    Responsable(string  , int  , string , string , int  , int) ;
    Responsable(const Responsable& ) ;
    double Charge () const ;
} ;

///////////////////////////////////////////////////////////////////////////////////////   constructeur usuel 
Responsable::Responsable(string nom_filie  , int nb_heure_responsabl , string no, string preno , int nbseance  , int charge_statu ) 
:Enseignant( no,  preno ,  nbseance  ,  charge_statu) , nom_filier(nom_filie) , nb_heure_responsable(nb_heure_responsable)
{}

///////////////////////////////////////////////////////////////////////////////////////   constructeur recopie
Responsable::Responsable(const Responsable& tmp) : nom_filier(tmp.nom_filier) , nb_heure_responsable(tmp.nb_heure_responsable) ,
Enseignant(tmp) {}

///////////////////////////////////////////////////////////////////////////////////////   méthode Charge
double Responsable::Charge() const {
    return nb_heure_responsable + Enseignant::Charge() ;
}
int main (){

    return 0 ;
}
