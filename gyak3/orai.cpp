#include <iostream>
#include <string>
#include <vector>
#include <set>

using namespace std;

// Tehen osztĂĄly definiĂĄlĂĄsa
class Tehen {
    const string nev /*= addName()*/;
    unsigned tomeg;
public:

    Tehen(const string& nev, unsigned tomeg)
            : nev(nev), tomeg(tomeg) {
        cout << "Tehen paramĂŠteres konstruktor: " << this->nev << " " << this->tomeg << endl;
    }

    Tehen() : Tehen("Mooo", 125) {
        cout << "Tehen default konstruktor" << endl;
    }


    const string &getNev() const {
        return nev;
    }

    unsigned int getTomeg() const {
        return tomeg;
    }

    void setTomeg(unsigned int tomeg) {
        Tehen::tomeg = tomeg;
    }
    void print() const {
        cout << "nev: " << nev << ", tomeg: " << tomeg << endl;
    }

};


int main() {
    Tehen t("Bocika", 34);
    Tehen t2;

    t.print();
    t2.print();

    unsigned n;
    cin >> n;
    vector<Tehen> tehenek;
    set<unsigned> tomegek;

    for (unsigned i = 0; i < n; i++)
    {
        string nev;
        unsigned tomeg;
        cin >> nev >> tomeg;
        Tehen tehen(nev, tomeg);
        bool van = false;
        for (unsigned i = 0; i < tehenek.size(); i++)
        {
            if (tehenek[i].getNev() == nev)
            {
                tehenek[i].setTomeg(tomeg);
                van = true;
                i--;
                break;
            }
            if (!van) tomegek.insert(tehen.getTomeg());
        }

    }

    // for(set<unsigned>::iterator it = tomegek.begin(); it != tomegek.end(); ++it) {
    //     cout << *it << endl;
    // }


    unsigned hatvanHetven = 0;

    for (unsigned i = 0; i < tehenek.size(); i++)
    {
        if(70 > tehenek[i].getTomeg() && tehenek[i].getTomeg() > 60) hatvanHetven++;
        tehenek[i].print();
    }

    cout << "60 és 70 közöttiek száma: " << hatvanHetven;


    cout << "Vege" << endl;
    for (unsigned i = 0; i < tehenek.size(); i++)
    {
        tehenek[i].print();
    }



    return 0;
}
