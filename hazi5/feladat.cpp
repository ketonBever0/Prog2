#include <iostream>
#include <string>
#include <cassert>
#include <utility>
#include <vector>

using namespace std;

/////////////////////////
//Ide dolgozz!!

class Kutya {
    string nev;
    unsigned kor;

public:
    virtual ~Kutya() = default;

    Kutya(string nev, unsigned kor) {
        this->nev = std::move(nev);
        this->kor = kor;
        cout << "Kutya letrehozva" << endl;
    };

    [[nodiscard]] string getNev() const {
        return this->nev;
    }

    [[nodiscard]] unsigned getKor() const {
        return this->kor;
    }

    [[nodiscard]] virtual string pedigre() const {
        return "nev:" + this->nev + ", kor:" + to_string(this->kor) + " ev";
    }

    [[nodiscard]] virtual vector<string> terel(const vector<string> &v) const {
        return v;
    }
};


class BorderCollie final : public Kutya {
    unsigned tereloKapacitas;

public:
    BorderCollie(const string &nev, const unsigned kor, unsigned tereloKapacitas) : Kutya(nev, kor),
        tereloKapacitas(tereloKapacitas) {
    }

    [[nodiscard]] unsigned getTereloKapacitas() const {
        return this->tereloKapacitas;
    }

    [[nodiscard]] string pedigre() const override {
        return "nev:" + this->getNev() + ", kor:" + to_string(this->getKor()) +
               " ev, faj:border collie, terelo kapacitas:" + to_string(this->getTereloKapacitas()) + " db birka";
    }

    [[nodiscard]] vector<string> terel(const vector<string> &v) const override {
        vector<string> nyaj;
        unsigned terelt = 0;
        unsigned uresek = 0;
        for (const auto & i : v) {
            if (!i.empty()) {
                nyaj.push_back(i);
                terelt++;
                if (terelt == this->getTereloKapacitas()) {
                    break;
                }
            }
            if (i.empty()) {
                uresek++;
            }
        }


        for (unsigned i = 0; i < uresek; i++) {
            nyaj.emplace_back("");
        }

        for (unsigned i = terelt + uresek; i < v.size(); i++) {
            nyaj.push_back(v[i]);
        }


        for (unsigned i = nyaj.size() - 1; i > 0; i--) {
            if (!nyaj[i].empty()) {
                break;
            }

            nyaj.pop_back();
        }

        return nyaj;
    }
};

void print(const Kutya &k) {
    cout << k.pedigre() << endl;
}


////////////////////////

//=== Teszteles bekapcsolasa kikommentezessel
// #define TEST_kutya
// #define TEST_pedigre
// #define TEST_terel
// #define TEST_border_collie
// #define TEST_pedigre_bc
#define TEST_terel_bc
//=== Teszteles bekapcsolas vege

/*
Készíts egy Kutya nevű osztályt!
Adattagok:
 - nev: a kutya neve
 - kor: a kutya életkora (unsigned)

Készítsd el a Kutya osztály konstruktorát is, amely két paramétert vár az adattagok inicializálására.
A konstruktorban az inicializálások után az alábbi szöveg kerüljön kiírásra a standard outputon:
"Kutya letrehozva"
A kiíratást sortörés kövesse.
*/
void test_kutya() {
#if defined TEST_kutya && !defined TEST_BIRO
        const Kutya k("Lassie", 3);
        assert(k.getNev() == "Lassie");
        assert(k.getKor() == 3);
#endif
}


/*
Készíts egy pedigre() publikus metódust a Kutya osztályban, mely sztring formában adja vissza a kutya adatait. A formátum a következő legyen:
nev:<nev>, kor:<kor> ev
A sztring végén ne legyen sortörés karakter, a kacsacsőrökkel jelzett értékek pedig helyettesítődjenek a megfelelő adattagok értékeivel (a vessző után illetve a <kor> és az ev között szóköz van).
*/
void test_pedigre() {
#if defined TEST_pedigre && !defined TEST_BIRO
        const Kutya k("Lassie", 3);
        string s = k.pedigre();
        assert(s == "nev:Lassie, kor:3 ev");
#endif
}


/*
Készíts egy publikus vector<string> terel() metódust, melynek egyetlen paramétere
egy std sztringeket tartalmazó vektor. A visszatérési érték egy sztringeket tartalmazó vektor.
A paraméterben kapott vektor egy birkanyájat reprezentál, a visszatérési érték pedig egy olyan vektor,
ami a kutya által összeterelt nyájat reprezentálja.
Az input nyájat nem kell módosítani. Egy kutya alapból nem tud nyájat terelni.
Legyen visszaadva egy olyan vektor, ami módosítás nélkül tartalmazza az erdeti vektor tartalmát.
*/
void test_terel() {
#if defined TEST_terel && !defined TEST_BIRO
        const Kutya k("Lassie", 3);

        vector<string> dinamikus_nyaj = k.terel({"Frici", "Julcsa", "Gyuri", "Margit"});
        assert(dinamikus_nyaj[3] == "Margit");
#endif
}

/*
Készíts egy BorderCollie osztályt, mely publikusan öröklődik a Kutya osztályból.
Új adattagok:
- tereloKapacitas: hány birkát tud terelni (unsigned)

A BorderCollie osztály rendelkezzen egy három paraméteres konstruktorral.
Az első kettő az ősosztály adattagjait beállító string és unsigned érték, a harmadik paraméter pedig szintén egy unsigned, amely a terelő kapacitást állítja be.
*/
void test_border_collie() {
#if defined TEST_border_collie && !defined TEST_BIRO
        const BorderCollie bc("Jess", 13, 5);
        assert(bc.getNev() == "Jess");
        assert(bc.getKor() == 13);
        assert(bc.getTereloKapacitas() == 5);
#endif
}

/*

Definiáld felül a BorderCollie osztályban a \texttt{pedigre} metódust. A létrehozott sztring így nézzen ki:
nev:<nev>, kor:<kor> ev, faj:border collie, terelo kapacitas:<tereloKapacitas> db birka
*/
void test_pedigre_bc() {
#if defined TEST_pedigre_bc && !defined TEST_BIRO
    const Kutya *bc = new BorderCollie("Jess", 13, 5);
    string s = bc->pedigre();
    cout << s << endl;
    assert(s == "nev:Jess, kor:13 ev, faj:border collie, terelo kapacitas:5 db birka");
    delete bc;
#endif
}


/*
Definiáld felül a BorderCollie osztályban a terel metódust. Ez a kutyafaj már képes nyájat terelni.
A terelés a következő módon történik. A paraméterben kapott vektorban minden 0 karakternél hosszabb sztring egy birka nevének felel meg, az üres sztringek pedig lyukaknak, ahol épp nincs birka.
Az ügyes terelőkutya úgy tereli össze a nyájat, hogy ne legyenek lyukak benne, de megtartja a birkák kezdeti sorrendjét.

Az output/összeterelt nyáj lesz a viszatérési érték. A vektor ott ér véget, ahol az utolsó birka van. A függvény által visszaadott vektor nem végződhet üres sztringgel/sztringekkel!
Olyan eset nem lehetséges, hogy a paraméterben kapott nyáj lyukkal, azaz üres sztringgel/sztringekkel végződik.

Még egy esetet le kell kezelni. A border collie-k nem tudnak tetszőleges méretű nyájat terelni, de azért megpróbálják a legtöbbet tenni, ami tőlük telik.
Abban az esetben, ha a tereloKapacitas értéküket meghaladó birkán haladtak már keresztül, leállnak a tereléssel és a nyáj végét úgy hagyják, ahogy volt.
(Példák a feladat.pdf-ben)
*/
void test_terel_bc() {
#if defined TEST_terel_bc && !defined TEST_BIRO
    const Kutya *bc = new BorderCollie("Jess", 13, 3);
    vector<string> nyaj = {"Frici", "", "Julcsa", "Gyuri", "", "Margit"};

    vector<string> dinamikus_nyaj = bc->terel(nyaj);
    assert(dinamikus_nyaj[0] == "Frici");
    assert(dinamikus_nyaj[1] == "Julcsa");
    assert(dinamikus_nyaj[2] == "Gyuri");
    assert(dinamikus_nyaj[3] == ""); //terelokapacitas!
    assert(dinamikus_nyaj[4] == "");
    assert(dinamikus_nyaj[5] == "Margit");
#endif
}

int main() {
    test_kutya();
    test_pedigre();
    test_terel();
    test_border_collie();
    test_pedigre_bc();
    test_terel_bc();

    return 0;
}
