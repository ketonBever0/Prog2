#include <iostream>
using namespace std;

class Tehen
{
    string nev;
    unsigned tomeg;

public:
    Tehen()
    {
        cout << "Tehén default konstruktor";
        this->nev = "Moo";
        this->tomeg = 125;
    }

    Tehen(string nev, unsigned tomeg)
    {
        this->nev = nev;
        this->tomeg = tomeg;
    }

    string getNev()
    {
        return this->nev;
    }
};

string addName()
{
    cout << "Név beállítva" << endl;
    return "Riska";
}

int main(int argc, char const *argv[])
{
    Tehen tehen = Tehen("Riska", 140);
    cout << tehen.getNev() << endl;

    Tehen t2;

    return 0;
}
