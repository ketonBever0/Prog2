#include <string>
#include <iostream>
#include <set>

using namespace std;

class Feladat
{
    string nev;
    unsigned eroforrasigeny;
    unsigned prioritas;

public:
    Feladat(string nev, unsigned eroforrasigeny, unsigned prioritas = 5)
    {
        this->nev = nev;
        this->eroforrasigeny = eroforrasigeny;
        if (prioritas < 1)
            this->prioritas = 1;
        else if (prioritas > 10)
            this->prioritas = 10;
        else
            this->prioritas = prioritas;
    }

    unsigned getEroforrasIgeny() const
    {
        return this->eroforrasigeny;
    }

    bool operator<(const Feladat &masik) const
    {
        if (this->prioritas == masik.prioritas)
            return masik.eroforrasigeny > this->eroforrasigeny;
        else
            return masik.prioritas < this->prioritas;
    }

    operator string()
    {
        return this->nev + "=" + to_string(this->prioritas) + ":" + to_string(this->eroforrasigeny);
    }
};

class Szerver
{

    set<Feladat> feladatok;
    unsigned kapacitas;

public:
    Szerver()
    {
        kapacitas = 10;
    }

    Szerver &operator+=(const Feladat &uj)
    {
        feladatok.insert(uj);
        return *this;
    }

    string kiir()
    {
        string str = "";
        str += to_string(this->kapacitas) + "\n";
        for (Feladat feladat : feladatok)
        {
            str += string(feladat) + "\n";
        }
        return str;
    }

    void operator!()
    {
        set<Feladat>::iterator it = feladatok.begin();
        while (it != feladatok.end() && this->kapacitas > 0)
        {
            if (it->getEroforrasIgeny() <= this->kapacitas)
            {
                this->kapacitas -= it->getEroforrasIgeny();
                it = feladatok.erase(it);
            }
            else
            {
                break;
            }
            ++it;
        }
    }

    void operator++()
    {
        this->kapacitas++;
    }
};

int main()
{
    Feladat f1 = Feladat("Feladat5", 4, 11);
    Feladat f2 = Feladat("Feladat1", 18, 3);
    Feladat f3 = Feladat("Feladat1", 6, 3);
    Feladat f4 = Feladat("Feladat9", 2, 4);
    Feladat f5 = Feladat("5", 9, 2);

    Szerver sz1 = Szerver();
    for (unsigned i = 0; i < 7; i++)
    {
        ++sz1;
    }

    ((((sz1 += f1) += f2) += f3) += f4);

    cout << "Elotte:\n"
         << sz1.kiir() << endl;
    !sz1;
    cout << "Utana:\n"
         << sz1.kiir() << endl;

    return 0;
}