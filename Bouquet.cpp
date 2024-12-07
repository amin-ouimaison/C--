#include <iostream>
#include <cstring>
using namespace std;

class Fleur {
protected:
    float prix;
    char* espece;
    bool p;

public:
    Fleur() ;
    Fleur(float prix, bool p, const char* espece);
    Fleur(const Fleur&);
    ~Fleur() { delete[] espece; }
    char* getEspece();
    void Afficher();
    bool operator==(const Fleur&);
    bool operator!=(const Fleur&);
    Fleur& operator=(const Fleur&);
};

Fleur::Fleur() : prix(0) , p(false) {
         espece = new char[1]{'\0'}; // chaine vide
    }

Fleur::Fleur(float prix, bool p, const char* espece) {
    this->prix = prix;
    this->p = p;
    if (espece) {
        this->espece = new char[strlen(espece) + 1];
        strcpy(this->espece, espece);
    } else {
        this->espece = new char[1]{'\0'};  
    }
}

Fleur::Fleur(const Fleur& f) {
    prix = f.prix;
    p = f.p;
    if (f.espece) {
        espece = new char[strlen(f.espece) + 1];
        strcpy(espece, f.espece);
    } else { // si f.espece a une valeur null en affecte chaîne vide
        espece = new char[1]{'\0'};
    }
}

char* Fleur::getEspece() { return espece; }

void Fleur::Afficher() {
    cout << "La fleur est " << ((!espece || *espece == '\0') ? "inconnu" : espece) << " ayant le prix " << prix ;
    // verifiant qu'espece n'est pas pointeur null ni il est vide 
    cout << (p ? " .C'est une fleur parfumée" : "Ce n'est pas une fleur parfumée") <<endl;// p vrai <=> "fleur parfumé"
}

bool Fleur::operator==(const Fleur& f) {
    if (!espece && !f.espece) return true;  // si les deux sont nulles
    if (!espece || !f.espece) return false; // si un parmi est null
    return (strcmp(f.espece, espece) == 0 && (prix == f.prix) && (p == f.p));
}

bool Fleur::operator!=(const Fleur& f) {
    return !(*this == f);
}

Fleur& Fleur::operator=(const Fleur& f) {
    if (this != &f) { // évitant self affectation 
        delete[] espece;
        prix = f.prix;
        p = f.p;
        espece = new char[strlen(f.espece) + 1];
        strcpy(espece, f.espece);
    }
    return *this;
}

class Bouquet {
protected:
    int nbp ;
    Fleur* T ;

public:
    Bouquet() : T(nullptr), nbp(0) {}
    ~Bouquet() { delete[] T; } 
    void Afficher();
    friend bool coincide(const Bouquet& , const Bouquet&);
    Bouquet& operator +(const Fleur&) ;
};

void Bouquet::Afficher() {
    cout << "Le nombre de fleurs est " << nbp << " parmi :" << endl;
    for (int i = 0; i < nbp; i++) {
        int C = 0;
        for (int j = 0; j < i; j++)
            if (T[j] == T[i])
                C++;
        if (!C) { // vérifiant qu'on écrit chaque type du fleur une seule fois
            cout << T[i].getEspece() << " - ";
        }
    }
}

bool coincide(const Bouquet& B1, const Bouquet& B2) {
    if (B1.nbp != B2.nbp) return false;
    for (int i = 0; i < B2.nbp; i++)
        if (B1.T[i] != B2.T[i])
            return false;
    return true;
}

Bouquet& Bouquet::operator +(const Fleur& f){
    Bouquet tmp(*this) ;
    delete [] T ;
    T = new Fleur[++nbp] ;
    for(int i = 0 ; i < nbp -1 ; i++)T[i] = tmp.T[i] ;
    T[nbp-1] = f ;
    return *this;
}

class Fleur_col :public Fleur {
    char* couleur ;
    public:
    Fleur_col(float prix , bool p , char *espece , char *couleur):Fleur(prix , p , espece)  {
        if (couleur) {
        this->couleur = new char[strlen(couleur) + 1];
        strcpy(this->couleur, couleur);
    } else {
        this->couleur = new char[1]{'\0'};  
    }
    }
    Fleur_col(const Fleur_col& fcl) : Fleur(fcl) , couleur(fcl.couleur){}
    void Afficher(){
        cout<<"C est une fleur du couleur "<<couleur<<" ,";
        Fleur::Afficher() ;
    }
};

int main() {
    return 0;
}
