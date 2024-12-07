#include<iostream>
using namespace std ; 
class Tableau_tri{
    protected :
    float* tab ;
    int taille ;
    int nbelts ;

    public:
    // constructeur par défaut 
    Tableau_tri(); 

    // constructeur usuel
    Tableau_tri(int ); 

    // constructeur de recopie
    Tableau_tri(const Tableau_tri & ) ;

    // destructeur
    ~Tableau_tri() ;

    // surdéfinition =
    Tableau_tri& operator = (const Tableau_tri &) ; 

    // méthode frequence
    int frequence(float ) ;

    //methode supprime 
    void supprime(float) ;

    // surdéfinition >
    int operator > (float ) ;

    // surdéfinition +  float
    Tableau_tri& operator + (float ) ;

    // surdéfinition + Tableau_tri
    Tableau_tri operator + (const Tableau_tri &  ) ;

    // surdéfinition postdécrémentation--
    void operator -- (int ) ;

    // surdéfinition *
    void operator * (float ) ;

    // surdéfinition <<
     friend ostream& operator << (ostream& , Tableau_tri& ); 

    // surdéfinition >>
     friend istream& operator >> (istream& , Tableau_tri& ); 
} ;
///////////////////////////////////////////////////////////////////////////////////////   2) constructeur par défaut
Tableau_tri::Tableau_tri() :tab(nullptr) , taille(0) , nbelts(0){}

///////////////////////////////////////////////////////////////////////////////////////   2) constructer usuel 
Tableau_tri::Tableau_tri(int t ){
    taille = t ;
    tab = new float[taille] ;
    nbelts = 0;
    }

///////////////////////////////////////////////////////////////////////////////////////  2)  constructeur recopie
Tableau_tri::Tableau_tri(const Tableau_tri &t ) {
        taille = t.taille ;
        nbelts = t.nbelts ;
        tab = new float[taille] ; 
        for(int i = 0 ; i < nbelts ; i++) tab[i] = t.tab[i] ;
}

///////////////////////////////////////////////////////////////////////////////////////   2) destructeur
Tableau_tri::~Tableau_tri(){delete []tab ;} 

///////////////////////////////////////////////////////////////////////////////////////   3) surdéfinition = 
Tableau_tri& Tableau_tri::operator =(const Tableau_tri& t){
    if( this != &t){
        taille = t.taille ;
        nbelts = t.nbelts ;
        if(!tab) delete [] tab ; // pour éviter supression du pointeur null
        tab = new float[taille] ;
        for(int i = 0 ; i < nbelts ; i++) tab[i] = t.tab[i] ;
    }
        return *this ;
}

///////////////////////////////////////////////////////////////////////////////////////   4) méthode Frequence
int Tableau_tri::frequence(float f ){
    int C = 0 ;
    int i = 0 ;
    while(f >= tab[i] && i < nbelts){
        if(f==tab[i]) C++ ; 
        i++ ;
    }
    return C ;
}

///////////////////////////////////////////////////////////////////////////////////////   5) méthode supprime 
void Tableau_tri::supprime(float f ){
    int C = 0 ;
    float* tmp = new float[taille] ;
    for(int i = 0 ; i < nbelts ; i++){
        if(tab[i]!=f){
            tmp[i] = tab[i] ; // tmp va recevoir tous les éléments != f puis on peut tab = tmp 
            C++ ;
        }
    }
    nbelts = C ;
    delete []tab ;
    tab = tmp ;
}

///////////////////////////////////////////////////////////////////////////////////////   6) surdéfinition > 
int Tableau_tri::operator > (float f){
    int i = 0 ;
    while(tab[i] <= f){
        if(tab[i]==f) return i ;
        i++ ;
    }
    return -1 ;
} 

///////////////////////////////////////////////////////////////////////////////////////   7) surdéfinition + pour ajouter élément 
Tableau_tri& Tableau_tri::operator + (float f){
    if(nbelts == taille) taille++ ;
    Tableau_tri tmp(*this) ;// copie temporaire
    tab = new float[taille] ;
    // Si f est inférieur ou égal au premier élément, on insère f au début
    if(f <= tmp.tab[0]) {
        tab[0] = f ;  
        for(int i = 1 ; i < nbelts ; i++) tab[i] = tmp.tab[i-1] ;
    }
    // Si f est supérieur ou égal au dernier élément, on l'insère à la fin.
    else if(tmp.tab[nbelts-1] <= f) {
        for(int i = 0 ; i < nbelts ; i++) tab[i] = tmp.tab[i] ;
        tab[nbelts] = f ;  
    }
    // Sinon, on insère f entre deux éléments
    else {
        for(int i = 0 ; i < nbelts - 1 ; i++) {
            tab[i] = tmp.tab[i] ;  // copie les éléments existants jusqu'à la position d'insertion
            if(f >= tmp.tab[i] && f < tmp.tab[i+1]) {
                tab[++i] = f ;  // On insère f 
                for(int j = i + 1 ; j < nbelts ; j++) tab[j] = tmp.tab[j-1] ;  
                break ;
                }
            }
        }
    nbelts++ ;
    return *this ;
}

///////////////////////////////////////////////////////////////////////////////////////   8) surdéfinition -- 
void Tableau_tri::operator -- (int ){
    for(int i = 0 ; i < nbelts ; i++)tab[i]-- ;
};

///////////////////////////////////////////////////////////////////////////////////////   9) surdéfinition * 
void Tableau_tri:: operator * (float f ){
    if(f >= 0){
        for(int i =0 ; i < nbelts ; i++){
            tab[i]*=f ;
        }
    }
    else {
        float *tmp = new float[taille] ;
        for(int i = 0 ; i < nbelts ; i++){
         tmp[i] = tab[nbelts - 1 - i] ;
        }
        delete []tab ;
        tab  = tmp ;
    }
}

///////////////////////////////////////////////////////////////////////////////////////   10) surdéfinition << 
ostream&  operator << (ostream& output, Tableau_tri& t){
    output<<"le nombre des elements est "<<t.nbelts<<endl;
    output<<"la taille du tableau est "<<t.taille<<endl ;
    for(int i = 0 ; i < t.nbelts ; i++)output<<"tab["<<i<<"]="<<t.tab[i]<<endl ;
    return output ;
}

///////////////////////////////////////////////////////////////////////////////////////   10) surdéfinition >>
istream& operator >> (istream& input , Tableau_tri& t){
    do{
        cout<<"entrez le nombre des elements "<<endl ;
        input>>t.nbelts ;
        }while(t.nbelts <= 0) ;
        if(t.nbelts > t.taille){
        delete []t.tab ;
        t.tab = new float[t.nbelts] ;
        }
        for( int i = 0 ; i < t.nbelts ; i++){
            cout<<"entrez l'element n°"<<i+1<<endl ;
            input>>t.tab[i] ;
        } 
        t.taille = t.nbelts ;
        // tri de bulles pour ordonner le tableau
        for(int i = 0 ; i < t.nbelts ; i++){
            for(int j = 0 ; j < i ; j++){
                float tmp ;
                if(t.tab[j] > t.tab[j+1]){
                    tmp = t.tab[j] ; 
                    t.tab[j] = t.tab[j+1] ;
                    t.tab[j+1] = tmp ; 
                }
            }
        }
        return input ;
     }

class Tableau_tri_rep :public Tableau_tri{
    int nbrepete ;
    int nbnonrepete ;
    public :
    // methode recalcule nombre d'éléments répétées et le retourne  
    int getRepetition(){
        int s = 0 ;
        for(int i = 0 ; i < nbelts - 1 ; i++){
            if(tab[i] < tab[i+1] ) s+=this->frequence(tab[i]) ;
        }
        nbrepete = s ;
        return nbrepete ;
    }
    // methode recalcule nombre d'éléments non répétées et le retourne  
    int getnonRepetition(){
        nbnonrepete = nbelts - nbrepete ;
        return nbnonrepete;
        }
    // B-1) constructeur usuelle 
    Tableau_tri_rep(int n):Tableau_tri(n){}
    // B-2) constructeur de recopie 
    Tableau_tri_rep(const Tableau_tri_rep& tpr):Tableau_tri(tpr) {
        nbrepete = tpr.nbrepete ;
        nbnonrepete = tpr.nbnonrepete ;
    } 
    // B-3) surcharge >> 
    friend istream& operator >> (istream& ,Tableau_tri_rep& ) ;
    // B-3) surcharge <<
    friend ostream& operator << (ostream& ,Tableau_tri_rep& ) ;

} ;
///////////////////////////////////////////////////////////////////////////////////////   B-3 surdéfinition >>
istream& operator >> (istream& input,Tableau_tri_rep& tpr){
    input>>static_cast<Tableau_tri&>(tpr);
    return input ;
}
///////////////////////////////////////////////////////////////////////////////////////   B-3 surdéfinition <<
ostream& operator << (ostream& output,Tableau_tri_rep& tpr){
    output<<static_cast<Tableau_tri&>(tpr);
    output<<"le nombre des elements repete est "<<tpr.getRepetition()<<endl;
    output<<"le nombre des elements non repete est "<<tpr.getnonRepetition()<<endl;
    return output ;
}
int main(){
    Tableau_tri_rep e(5) ;
    e+7+7+7+7+8+9 ;
    cout<<e<<endl;
    cin>>e ;
    cout<<e<<endl;
    return 0 ;
}
