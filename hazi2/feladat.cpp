#include <iostream>
#include <string>
#include <cassert>
#include <cctype>
#include <algorithm>

using namespace std;

/////////////////////////
//Ide dolgozz!!

class Telepes {

  string nev;
  string szulBolygo;
  string bolygo;
  unsigned ero;


  public:

  Telepes() {
    nev = "";
    szulBolygo = "";
    bolygo = "";
    ero = 1;
  }

  Telepes(string nev, string bolygo, unsigned ero = 1) {
    this->nev = nev;
    this->bolygo = bolygo;
    this->szulBolygo = bolygo;
    this->ero = ero;
  }

  Telepes(string nev, string szulBolygo, string bolygo, unsigned ero) {
    this->nev = nev;
    this->bolygo = bolygo;
    this->szulBolygo = szulBolygo;
    this->ero = ero;
  }

  bool kivandorlo() const {

    string szulBolygoLower = szulBolygo;
    string bolygoLower = bolygo;

    transform(szulBolygoLower.begin(), szulBolygoLower.end(), szulBolygoLower.begin(), ::tolower);
    transform(bolygoLower.begin(), bolygoLower.end(), bolygoLower.begin(), ::tolower);

    return szulBolygoLower != bolygoLower;
  }

  void dolgozik(string& munkak) const {
    unsigned stamina = ero;
    unsigned cut = 0;

    for (unsigned i = 0; i < munkak.length(); i++) {
        if (munkak[i] == ';') {
            stamina--;
            if (stamina == 0) {
                cut = i + 1;
                break;
            }
        }
    }
    munkak = munkak.substr(cut);
}



    string getNev() {
      return this->nev;
    }

    string getSzulBolygo() {
      return this->szulBolygo;
    }

    string getBolygo() {
      return this->bolygo;
    }

    unsigned getEro() {
      return this->ero;
    }

    void setNev(string nev) {
      this->nev = nev;
    }

    void setSzulBolygo(string szulBolygo) {
        this->szulBolygo = szulBolygo;
    }

    void setBolygo(string bolygo) {
      this->bolygo = bolygo;
    }

    void setEro(unsigned ero) {
      this->ero = ero;
    }

};


////////////////////////

//=== Teszteles bekapcsolasa kikommentezessel
//#define TEST_default_konstruktor
//#define TEST_param_konstruktor
//#define TEST_param_konstruktor2
// #define TEST_kivandorlo
// #define TEST_munkavegzes
//=== Teszteles bekapcsolas vege

/*
Készíts egy Telepes nevű osztályt, mely a különféle bolygókon letelepedett emberek adatait tárolja.
Négy adattagja van, ezek mindegyikéhez tartozik getter és setter. 
- szul_bolygo: születési bolygó
- bolygo: jelenlegi bolygó
- nev: a telepes neve
- ero: munkavégző képesség (unsigned int)
Rendelkezzen egy default konstruktorral, amely a nev, szul_bolygo és bolygo adattagokat üres sztringre inicializálja, az ero-t pedig 1-re.
*/
void test_default_konstruktor(){
  #if defined TEST_default_konstruktor && !defined TEST_BIRO
  Telepes t1;
  assert(t1.getNev() == "");
  assert(t1.getSzulBolygo() == "");
  assert(t1.getBolygo() == "");
  assert(t1.getEro() == 1);

  t1.setSzulBolygo("Mars");
  t1.setBolygo("Venus");
  t1.setNev("Jevgenyij Anyegin");
  t1.setEro(10);
  assert(t1.getNev() == "Jevgenyij Anyegin");
  assert(t1.getSzulBolygo() == "Mars");
  assert(t1.getBolygo() == "Venus");
  assert(t1.getEro() == 10);
  #endif
}

/*
Legyen egy konstruktora, mely négy paraméterrel rendelkezik és mind a négy adattagot a paramétereknek megfelelően állítja be. 
Paraméterek sorrendje: nev, szul_bolygo, bolygo, ero
*/
void test_param_konstruktor(){
  #if defined TEST_param_konstruktor && !defined TEST_BIRO
  const Telepes t1("Franz Kafka", "Mars", "Venus", 50);
  assert(t1.getNev() == "Franz Kafka");
  assert(t1.getSzulBolygo() == "Mars");
  assert(t1.getBolygo() == "Venus");
  assert(t1.getEro() == 50);
  #endif
}

/*
Legyen egy konstruktora, amely két sztringet és egy unsigned paramétert vár. Az első sztring paraméter alapján a telepes neve legyen inicializálva, 
míg a második sztring paraméter a telepes jelenlegi bolygójának a neve. 
Ez alapján legyen inicializálva a bolygo és a szul_bolygo adattag is.
Lehessen úgy is használni, hogy meghívásakor nem adunk meg unsigned értéket, csak a két sztringet. Ilyenkor az ero érték legyen 1-re állítva. 
*/
void test_param_konstruktor2(){
  #if defined TEST_param_konstruktor2 && !defined TEST_BIRO
  const Telepes t1("Kurt Vonnegut", "Venus", 4);
  assert(t1.getNev() == "Kurt Vonnegut");
  assert(t1.getSzulBolygo() == "Venus");
  assert(t1.getBolygo() == "Venus");
  assert(t1.getEro() == 4);

  const Telepes t2("Kurt Vonnegut", "Venus");
  assert(t2.getNev() == "Kurt Vonnegut");
  assert(t2.getSzulBolygo() == "Venus");
  assert(t2.getBolygo() == "Venus");
  assert(t2.getEro() == 1);
  #endif
}

/*
Készíts egy kivandorlo() metódust a Telepes osztályba, mely segít eldönteni, hogy a telepes kivandorlónak minősül-e. 
A visszatérési értéke akkor legyen igaz, ha a szul\_bolygo és bolygo adattagok értéke nem egyenlő egymással. 
Két bolygó neve egyenlőnek számít, ha csak kisbetű/nagybetű eltérés van a nevükben (pl. ``Mars'' és ``mars'' egyenlőek). 
A bolygók nevei ascii karakterek (tehát nem tartalmaznak pl. ékezetes betűket). Ha mindkét adattag értéke üres sztring egyenlőnek tekinthetőek. 
*/
void test_kivandorlo(){
  #if defined TEST_kivandorlo && !defined TEST_BIRO
  const Telepes t1("Franz Kafka", "Mars", "Px-2312", 50); //Kafka kivandorlo
  assert(t1.kivandorlo());
  #endif
}

/*
Készíts egy dolgozik() metódust, amely naplózza a telepes munkavégézését.
A paraméterként kapott sztring reprezentálja az egymás után következő feladatokat pontosvesszővel elválasztva. 
A feladatok alfanumerikus kódokkal vannak reprezentálva, pl.: b1 - kapálás, b22 - ültetés stb. 
A telepesek minden feladatot el tudnak végezni, azonban csak annyi darabot, 
amennyi az ero értékük, utána kifáradnak. A metódus célja, hogy levágja azokat a munkákat a sztring elejéről, amiket a telepes elvégzett.
*/
void test_munkavegzes(){
  #if defined TEST_munkavegzes && !defined TEST_BIRO
  const Telepes t1("Kovacs Geza", "Uranus", "Px-2312", 2);
  string munkak = "b1;b22;c3;x823";
  t1.dolgozik(munkak);
  assert(munkak == "c3;x823");
  #endif
}

int main(){

  test_default_konstruktor();
  test_param_konstruktor();
  test_param_konstruktor2();
  test_kivandorlo();
  test_munkavegzes();

  return 0;
}
