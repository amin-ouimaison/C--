#include<iostream>
using namespace std ;

class Polynome{
    protected:
    int degre ;
    double *coefficients ; 

    public:
    // constructeur par défaut
    Polynome();  
    // constructeur usuel
    Polynome(int );
    // constructeur de recopie
    Polynome(const Polynome&) ;
    // destructeur
    ~Polynome() ;
    // surdéfinition =
    Polynome& operator = (const Polynome&) ;
    // surdéfinition +
    Polynome operator + (const Polynome&) ;
    // surdéfinition *
    Polynome& operator * (double ) ;
    // méthode multiplication par x
    void multiplex () ;
    // méthode calcule primitive
    Polynome primitive() ;
    // valeur du polynome pour une valeur  donné 
    double valeur(double) ;
    // surdéfinition <<
    friend ostream& operator << (ostream& , const Polynome&) ;
    // surdéfinition >>
    friend istream& operator >> (istream& , Polynome& ) ;
};
///////////////////////////////////////////////////////////////////////////////////////   consructeur pa défaut 
Polynome::Polynome() : degre(0) , coefficients(nullptr){}

///////////////////////////////////////////////////////////////////////////////////////   consructeur usuel
Polynome::Polynome(int deg) : degre(deg) , coefficients(new double[deg+1]){}

///////////////////////////////////////////////////////////////////////////////////////   consructeur de recopie
Polynome::Polynome(const Polynome& pol) {
    degre = pol.degre ;
     coefficients = new double[degre+1]();
     for(int i = 0 ; i <= degre ; i++)coefficients[i] = pol.coefficients[i] ;
}

///////////////////////////////////////////////////////////////////////////////////////   destructeur
Polynome::~Polynome(){
    delete []coefficients ;
}

///////////////////////////////////////////////////////////////////////////////////////   surdéfinition =
Polynome& Polynome:: operator = (const Polynome& pol) {
    if(this!=&pol){
        degre = pol.degre ;
        delete []coefficients ;
        coefficients = new double[degre+1]() ;
        for(int i = 0 ; i <= degre ; i++)coefficients[i] = pol.coefficients[i] ;
    }
    return *this ;
}

///////////////////////////////////////////////////////////////////////////////////////   suedéfinition +
Polynome Polynome:: operator + (const Polynome& pol){
    Polynome tmp ; 
    tmp.degre = (degre > pol.degre)? degre : pol.degre ; 
    tmp.coefficients = new double[tmp.degre]() ; 
    for(int i = 0 ; i <= tmp.degre ; i++){
        if( i <= degre )tmp.coefficients[i]+=coefficients[i] ;
        if( i <= pol.degre )tmp.coefficients[i]+=pol.coefficients[i] ;
    }
    return tmp ; 
} 

///////////////////////////////////////////////////////////////////////////////////////   surdéfinition *
Polynome& Polynome::operator * (double d){
    for(int i = 0 ; i <=degre ; i++ )coefficients[i]*=d ; 
    return *this ;
    }

///////////////////////////////////////////////////////////////////////////////////////   méthode multiplication par x
void Polynome::multiplex () {
    degre++ ;
    double *tmp = new double[degre]() ; //  () initialise tous les éléments avec 0 
    for(int i = 0 ; i <= degre-1  ; i++)tmp[i+1] = coefficients[i] ;
    delete []coefficients ;
    coefficients = tmp ; 
}

///////////////////////////////////////////////////////////////////////////////////////   méthode calcule primitive
Polynome Polynome::primitive() {
    Polynome tmp(degre + 1); 
    tmp.coefficients[0] = 0; // La constante d'intégration est 0
    for (int i = 1; i <= degre; i++) {
        tmp.coefficients[i] = coefficients[i - 1] / i; // On divise chaque coefficient par son indice
    }
    return tmp;
}

///////////////////////////////////////////////////////////////////////////////////////   valeur du polynome pour une valeur x
double Polynome:: valeur(double x ) {
    double s  = coefficients[0] + coefficients[1] * x ;
    double xPoweri ;
    for(int i = 2 ; i <= degre ; i++ ){
        xPoweri = 1 ;
        for(int j = 1 ; j <= i ; j++){
            xPoweri*=x ;
        }
        s+=xPoweri*coefficients[i] ;
    }
    return s ;
}

///////////////////////////////////////////////////////////////////////////////////////   surdéfinition <<
ostream& operator << (ostream& output ,const Polynome& tmp) {
    output<<"Deg(P) =  "<<tmp.degre<<endl<<"P(X) = " ;
    for(int i = tmp.degre ; i > 1 ; i--)output<<tmp.coefficients[i]<<"x^"<<i<<" + ";
    output<<tmp.coefficients[1]<<"X"<<" + "<<tmp.coefficients[0]<<endl ;
    return output ;
}

///////////////////////////////////////////////////////////////////////////////////////   surdéfinition >>
istream& operator >> (istream& input ,Polynome& tmp){
    for(int i = 0 ; i <= tmp.degre ; i++){
        cout<<"enter the coefficient of X^"<<i<<endl ;
        input>>tmp.coefficients[i] ;
    }
    return input ;
}

 int main(){
    Polynome a(3)  ;  
    cin>>a; 
    cout<<a;
    return 0 ;
 }




 /*
 #include<iostream>
using namespace std;

class Polynome {
protected:
    int degre;
    double* coefficients;

public:
    // constructeur par défaut
    Polynome();
    // constructeur usuel
    Polynome(int);
    // constructeur de recopie
    Polynome(const Polynome&);
    // destructeur
    ~Polynome();
    // surdéfinition =
    Polynome& operator = (const Polynome&);
    // surdéfinition +
    Polynome operator + (const Polynome&);
    // surdéfinition *
    Polynome& operator * (double);
    // méthode multiplication par x
    void multiplex();
    // méthode calcule primitive
    Polynome primitive();
    // valeur du polynome pour une valeur donnée
    double valeur(double);
    // surdéfinition <<
    friend ostream& operator << (ostream&, const Polynome&);
    // surdéfinition >>
    friend istream& operator >> (istream&, Polynome&);
};

// constructeur par défaut
Polynome::Polynome() : degre(0), coefficients(nullptr) {}

// constructeur usuel
Polynome::Polynome(int deg) : degre(deg), coefficients(new double[deg + 1]()) {}

// constructeur de recopie
Polynome::Polynome(const Polynome& pol) {
    degre = pol.degre;
    coefficients = new double[degre + 1]();
    for (int i = 0; i <= degre; i++) {
        coefficients[i] = pol.coefficients[i];
    }
}

// destructeur
Polynome::~Polynome() {
    delete[] coefficients;
}

// surdéfinition =
Polynome& Polynome::operator = (const Polynome& pol) {
    if (this != &pol) {
        degre = pol.degre;
        delete[] coefficients;
        coefficients = new double[degre + 1]();
        for (int i = 0; i <= degre; i++) {
            coefficients[i] = pol.coefficients[i];
        }
    }
    return *this;
}

// surdéfinition +
Polynome Polynome::operator + (const Polynome& pol) {
    Polynome tmp(max(degre, pol.degre)); // On prend le plus grand degré des deux polynômes
    for (int i = 0; i <= tmp.degre; i++) {
        if (i <= degre) tmp.coefficients[i] += coefficients[i];
        if (i <= pol.degre) tmp.coefficients[i] += pol.coefficients[i];
    }
    return tmp;
}

// surdéfinition *
Polynome& Polynome::operator * (double d) {
    for (int i = 0; i <= degre; i++) {
        coefficients[i] *= d;
    }
    return *this;
}

// méthode multiplication par x
void Polynome::multiplex() {
    degre++;
    double* tmp = new double[degre](); // Allocation d'un tableau plus grand
    for (int i = 0; i < degre - 1; i++) {
        tmp[i + 1] = coefficients[i]; // Décalage des coefficients
    }
    delete[] coefficients;
    coefficients = tmp;
}

// méthode calcule primitive
Polynome Polynome::primitive() {
    Polynome tmp(degre + 1); // Le degré de la primitive est +1
    tmp.coefficients[0] = 0; // La constante d'intégration est 0
    for (int i = 1; i <= degre; i++) {
        tmp.coefficients[i] = coefficients[i - 1] / i; // On divise chaque coefficient par son indice
    }
    return tmp;
}

// valeur du polynome pour une valeur x
double Polynome::valeur(double x) {
    double result = 0;
    double power = 1;
    for (int i = 0; i <= degre; i++) {
        result += coefficients[i] * power;
        power *= x; // On multiplie la puissance de x à chaque itération
    }
    return result;
}

// surdéfinition <<
ostream& operator << (ostream& output, const Polynome& tmp) {
    output << "Deg(P) = " << tmp.degre << endl << "P(X) = ";
    for (int i = tmp.degre; i > 1; i--) {
        output << tmp.coefficients[i] << "x^" << i << " + ";
    }
    output << tmp.coefficients[1] << "x + " << tmp.coefficients[0] << endl;
    return output;
}

// surdéfinition >>
istream& operator >> (istream& input, Polynome& tmp) {
    for (int i = 0; i <= tmp.degre; i++) {
        cout << "Entrer le coefficient de X^" << i << ": ";
        input >> tmp.coefficients[i];
    }
    return input;
}

int main() {
    Polynome a(3);  
    cin >> a; 
    cout << a;
    return 0;
}

 
  */