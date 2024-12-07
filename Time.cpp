 #include<iostream>
 using namespace std ; 
 ///////////////////////////////////////////////////////////////////////// 1) class Time
 class Time{
     protected:
     int h ;
     int m ;
     int s ;
     
     public : 
// constructeur par défaut 
     Time() : h(0) , m(0) , s(0){}

// constructeur usuel 
     Time(int , int , int) ;

// getters
     int getHeure() const { return h ; }
     int getMinute() const { return m ; }
     int getSeconde() const { return s ; }

// setters
     void setHeure(int ) ;
     void setMinute(int ) ;
     void setSeconde(int ) ;
     
// surdéfinition <
     bool operator < (const Time& ) const ; 

// calcul nombre des secondes (pour faciliter certain surdéfinition)
     int nombreSecondes() const { return (h*3600 + m*60 + s) ; }

// surdéfinition <= 
     bool operator >= (const Time& t) const { return !(*this < t ) ; }
     
// surdéfinition ==
     bool operator ==(const Time& t) const{ return (this->nombreSecondes() == t.nombreSecondes()) ; }
     
// surdéfinition !=
     bool operator !=(const Time& t) const{ return !(*this == t) ; }

// surdéfinition <<
      friend ostream& operator <<( ostream& , const Time&) ;
// surdéfinition >>
      friend istream& operator >>( istream& , Time& ) ;
      
// méthode Ajout1s
       void Ajout1s() ;
      
// méthode AjoutNs
       void AjoutNs(int ) ;

// méthode S_entre 
       static int S_entre(const Time& t1 ,const Time& t2){
          return (t1 >= t2) ? ( t1.nombreSecondes() - t2.nombreSecondes()) : ( t2.nombreSecondes() - t1.nombreSecondes()) ; 
      }
 } ;

///////////////////////////////////////////////////////////////////////// constructeur usuel
Time::Time(int heure , int minute , int seconde) {
        h = ( heure>=0 && heure<=23 )? heure : 0 ;
        m = ( minute>=0 && minute<=59 )? minute : 0 ;
        s = ( seconde>=0 && seconde<=59 )? seconde : 0 ;
        }

///////////////////////////////////////////////////////////////////////// setters
void Time::setHeure(int heure){
         if(heure <= 23) h = heure ;
         else cout<<"valeur invalide."<<endl ;
     }

void Time::setMinute(int minute){
        if(minute <= 59) m = minute ;
        else cout<<"valeur invalide."<<endl ; 

     }

void Time::setSeconde(int seconde){
         if(seconde <= 59) s = seconde ;
         else cout<<"valeur invalide."<<endl ; 
     }

///////////////////////////////////////////////////////////////////////// surdéfinition <
bool Time::operator < (const Time& t) const {
          return (this->nombreSecondes() < t.nombreSecondes()) ;
      }

///////////////////////////////////////////////////////////////////////// surdéfinition <<
ostream& operator <<( ostream& output , const Time& t){
          output<<t.h<<":"<<t.m<<":"<<t.s ;
          return output ;
      }

///////////////////////////////////////////////////////////////////////// surdéfinition >>
istream& operator >>( istream& input , Time& t){
    cout << "Entrez l'heure, la minute et les secondes : "<<endl;
    input >> t.h >> t.m >> t.s;
    if (t.h < 0 || t.h > 23 || t.m < 0 || t.m > 59 || t.s < 0 || t.s > 59)
    cout << "Valeur invalide détectée." << endl;
    return input;
}  

///////////////////////////////////////////////////////////////////////// méthode Ajout1s
void Time::Ajout1s(){
    s++ ; m += s/60 ;
    s %= 60 ;
    h += m/60 ;
    m %= 60 ;
    h %= 24 ;      
      }

///////////////////////////////////////////////////////////////////////// méthode AjoutNs
void Time::AjoutNs(int N ){
          for(int i = 0 ; i < N ; i++) this->Ajout1s() ;
      }

///////////////////////////////////////////////////////////////////////// 2) class tableau_Time 
  class tableau_Time{
    int nbelts ;
    Time *tab ;
    int taille ;  
    public :
// constructeur usuel 
    tableau_Time(int , int ) ;
// constructeur recopie
    tableau_Time(tableau_Time& ) ;
// destructeur 
    ~tableau_Time(){ delete [] tab ; }
// constructeur conversion 
    tableau_Time(int t ):taille(t) , tab(new Time[taille]){}
// surdéfinition =
    tableau_Time& operator = (const tableau_Time& ) ;
// méthode ajouTime
    void ajouTime(const Time& ) ;
 } ;
///////////////////////////////////////////////////////////////////////// constructeur usuel 
tableau_Time ::tableau_Time(int t , int n) : taille(t) , nbelts(n)  {
        tab = new Time[taille] ;

        }

///////////////////////////////////////////////////////////////////////// constructeur recopie
tableau_Time ::tableau_Time(tableau_Time& t){
        taille = t.taille ;
        nbelts = t.nbelts ;
        tab = new Time[taille] ;
        for(int i = 0 ; i < taille ; i++)tab[i] = t.tab[i];
    }

///////////////////////////////////////////////////////////////////////// surdéfinition =
tableau_Time& tableau_Time:: operator = (const tableau_Time& t){
    if(this != &t){
        taille = t.taille ;
        nbelts = t.nbelts ;
        if(tab) delete []tab ;
        tab = new Time[taille] ;
        for(int i = 0 ; i < taille ; i++)tab[i] = t.tab[i] ;
    }
    return *this ;
    }
///////////////////////////////////////////////////////////////////////// méthode ajouTime
void tableau_Time::ajouTime(const Time& t) {
    nbelts++ ;
    if( nbelts >= taille) taille++ ;
    Time* tmp = new Time[taille];
    for(int i = 0 ; i < nbelts -1 ; i++) tmp[i] = tab [i] ;
    delete [] tab ;
    tab = tmp ;
    tab[nbelts - 1] = t ;
   // Tri à bulles après l'insertion de t
    for (int i = 0; i < nbelts - 1; i++) {
        for (int j = 0; j < nbelts - i - 1; j++) {
            if ( tab[j + 1] < tab[j] ) {
                // Échange les éléments si l'ordre est incorrect
                Time temp = tab[j];
                tab[j] = tab[j + 1];
                tab[j + 1] = temp;
            }
        }
    }
          }

///////////////////////////////////////////////////////////////////////// 3) class Date
 class Date : public Time{
    int annee ;
    int mois ;
    int jour ;
    public:
    // constructeur usuel 
     Date(int a , int m ,int j ,int heure , int minute , int seconde ) : Time(heure , minute , seconde){
     annee = (a >= 0) ? a : 0;
     mois = (m >= 1 && m <= 12) ? m : 1;
     jour = (j >= 1 && j <= 31) ? j : 1;
     }
     // meéthode AfficheDate
     void AfficheDate(){
        cout<<annee<<"/"<<mois<<"/"<<jour<<" " ;
        cout<<*this<<endl ;
     }
     // méthode SaisiDate
     void SaisiDate() ;
 } ;

///////////////////////////////////////////////////////////////////////// méthode SaisiDate
void Date::SaisiDate() {
        int j , m , a ;
        cout<<"entrez le jour"<<endl ;
        cin>>j ;
        jour = ( j >=1 && j<=31)? j : 1 ; // si valeur invalide valeur par défaut sera 1 
        cout<<"entrez le mois"<<endl ;
        cin>>m ;
        mois = ( m >=1 && m<=12)? m : 1 ; // si valeur invalide valeur par défaut sera 1
        cout<<"entrez l annee"<<endl ;
        cin>>a ;
        annee = ( a >=0 )? a : 1 ; // si valeur invalide valeur par défaut sera 1
        cout<<"entrez l heure chronologique "<<endl ;
        cin>>static_cast<Time&>(*this);
        // static_cast garantit que l'objet courant sera traité comme un objet de type Time 
        // afin de pouvoir appeler l'opérateur >> défini pour la classe Time dans cette saisie (cin).

}
int main(){        
 return 0 ;
 }