#include <iostream>
#include <stdexcept>
#include <cassert>

using namespace std;


/////////////////////////
//Ide dolgozz!!


int main() {

  

  return 0;
}


////////////////////////

//=== Teszteles bekapcsolasa kikommentezessel
//#define TEST_count_mM
//#define TEST_repeater
//#define TEST_multiplier
//#define TEST_strmin
//=== Teszteles bekapcsolas vege


/*
Készíts egy függvényt, amely beolvas egy tetszőleges hosszúságú sztringet a standard inputról, 
majd megszámolja hány darab m és M betű található benne.
A két betű darabszámának összege legyen a függvény visszatérési értéke. A függvény egész számmal térjen vissza.
A függvény semmit se írjon ki a standard outputra!
*/
void test_count_mM(){
  #if defined TEST_count_mM && !defined TEST_BIRO
  cout << "1-es feladat tesztelese" << endl;
  int m = count_mM();
  cout << "A beolvasott m és M karaketerk szama: " << m << endl;
  #endif 
}

/*
Készíts egy függvényt, amely beolvas előbb egy egész számot, utána pedig egy tetszőleges hosszúságú sztringet a standard inputról. 
A függvény visszatérési értéke egy sztring legyen, amelyben annyiszor van megismételve (szóköz vagy egyéb elválasztójelek nélkül) 
a beolvasott sztring, amennyi a beolvasott egész értéke.
Ha a beolvasott szám negatív a visszaadott sztring értéke "hiba" legyen. 
A függvény semmit se írjon ki a standard outputra!
*/
void test_repeater(){
  #if defined TEST_repeater && !defined TEST_BIRO
  cout << "2-es feladat tesztelese" << endl;
  string reps = repeater();
  cout << reps << endl;
  #endif
}

/*
Készíts egy függvényt, amelynek paramétere egy előjel nélküli egész szám. 
A függvény visszatérési értéke egy sztring legyen, amelyben a paraméterül kapott szám 3-szorosa van sztringgé konvertálva.
A függvény semmit se írjon ki a standard outputra!
*/
void test_multiplier(){
  #if defined TEST_multiplier && !defined TEST_BIRO
  cout << "3-as feladat tesztelese" << endl;
  string multi1 = multiplier(1);
  assert(multi1 == "3");
  #endif
}

/*
Készíts egy függvényt, amely két string-et vár paraméterül. A string-ek egy-egy egész számot tartalmaznak. 
A függvény visszatérési értéke az a szám lesz (sztringről egész számmá konvertálva), amelyiknek az értéke kisebb. 
Amennyiben az egyik sztring üres vagy a konverzió nem elvégezhető, akkor a másik sztring számértéke legyen visszaadva. 
Ha mindét sztring üres vagy nem konvertálható, akkor a visszatérési érték -999 legyen. 
A függvény semmit se írjon ki a standard outputra!
*/
void test_strmin(){
  #if defined TEST_strmin && !defined TEST_BIRO
  cout << "4-es feladat tesztelese" << endl;
  int min = strmin("3", "4");
  assert(min == 3);
  min = strmin("Harry", "Potter");
  assert(min == -999);
  min = strmin("-3", "szappanos bukta");
  assert(min == -3);
  #endif
  
}

int main(){

  test_count_mM();
  test_repeater();
  test_multiplier();
  test_strmin();

  return 0;
}
