#include <iostream>
#include <string>
#include <vector>

using namespace std;

// Tehen osztĂĄly definiĂĄlĂĄsa
class Tehen
{
    const string nev /*= addName()*/;
    unsigned tomeg;

public:
    Tehen(const string &nev, unsigned tomeg)
        : nev(nev), tomeg(tomeg)
    {
        cout << "Tehen paramĂŠteres konstruktor: " << this->nev << " " << this->tomeg << endl;
    }

    Tehen() : Tehen("Mooo", 125)
    {
        cout << "Tehen default konstruktor" << endl;
    }

    const string &getNev() const
    {
        return nev;
    }

    unsigned int getTomeg() const
    {
        return tomeg;
    }

    void setTomeg(unsigned int tomeg)
    {
        Tehen::tomeg = tomeg;
    }
    void print() const
    {
        cout << "nev: " << nev << ", tomeg: " << tomeg << endl;
    }
};

class Cseszealj
{

    vector<Tehen> tehenek = {};

public:
    void elrabol(Tehen tehen)
    {
        if (tehen.getTomeg() > 60)
            this->tehenek.push_back(tehen);
    }

    Cseszealj operator<<(const Tehen &tehen)
    {
        elrabol(tehen);
        return *this;
    }

    Cseszealj operator+=(const Tehen &tehen)
    {
        elrabol(tehen);
        return *this;
    }

    bool operator<(const Cseszealj &jobb) const
    {
        return this->tehenek.size() < jobb.tehenek.size();
    }

    bool operator>(const Cseszealj &jobb) const
    {
        return this->tehenek.size() > jobb.tehenek.size();
    }

    bool operator==(const unsigned szam) const
    {
        return tehenek.size() == szam;
    }

    bool operator!=(const unsigned szam) const
    {
        return tehenek.size() != szam;
    }

    void elrabol(Juhaszkutya kutya)
    {
        throw runtime_error(kutya.getNev());
    }
};

class Juhaszkutya
{
    string nev;

public:
    Juhaszkutya(const string &n) : nev(n) {}

    const string &getNev() const
    {
        return nev;
    }
};

int main()
{
    Tehen tehen1("Riska", 70);
    Tehen tehen2("Boci", 50);
    Tehen tehen3("Mucika", 100);
    Tehen tehen4("Uff", 99);
    Juhaszkutya kutya{"Bodri"};
    cout << kutya.getNev() << endl;

    Cseszealj ufo;
    ufo.elrabol(tehen1);
    ufo << tehen2 << tehen4;
    ufo += tehen3;
    return 0;
}
