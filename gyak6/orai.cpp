
#include <iostream>
#include <vector>
#include <string>
#include <stdexcept>
#include <set>

using namespace std;

class Allat
{

protected:
    string nev;

public:
    explicit Allat(const string &nev)
};

class Tehen : public Allat
{
    unsigned tomeg;

public:
    Tehen(const string &nev, unsigned tomeg)
        : nev(nev), tomeg(tomeg)
    {
        cout << "Tehen paraméteres konstruktor: " << this->nev << " " << this->tomeg << endl;
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

    bool operator<(const Tehen &other) const
    {
        return (nev < other.nev) || (nev == other.nev && tomeg < other.tomeg);
    }

    bool operator==(const Tehen &other) const
    {
        return nev == other.nev && tomeg == other.tomeg;
    }

    bool operator!=(const Tehen &other) const
    {
        return !operator==(other);
    }

    operator unsigned() const
    {
        return tomeg;
    }

    bool operator==(unsigned val) const
    {
        return tomeg == val;
    }
};

bool operator==(unsigned val, const Tehen &t)
{
    return t.getTomeg() == val;
}

/////////////

class Juhaszkutya : public Allat
{
    string nev = "Bodri";

public:
    Juhaszkutya() : Allat("Morzsa") {}

    const string &getNev() const
    {
        return nev;
    }

    void setNev(const std::string &n)
    {
        nev = n;
    }
};

////////////

/////////////
class Cseszealj
{
    vector<Tehen> tehenek;

public:
    const vector<Tehen> &getTehenek() const
    {
        return tehenek;
    }

public:
    void elrabol(const Tehen &t)
    {
        if (t.getTomeg() > 60)
        {
            tehenek.push_back(t);
        }
    }

    void elrabol(const Juhaszkutya &t) const
    {
        throw runtime_error(t.getNev());
    }

    Cseszealj &operator<<(const Tehen &t)
    {
        elrabol(t);
        return *this;
    }

    void operator<<(const Juhaszkutya &t) const
    {
        elrabol(t);
    }

    void operator+=(const Tehen &t)
    {
        elrabol(t);
    }

    void operator+=(const Juhaszkutya &t) const
    {
        elrabol(t);
    }

    void print() const
    {
        cout << "Elrabolva " << tehenek.size() << " db tehĂŠn" << endl;
        for (const auto &t : tehenek)
        {
            t.print();
        }
    }

    bool kisebb(const Cseszealj &other) const
    {
        return tehenek.size() < other.tehenek.size();
    }

    bool operator<(const Cseszealj &other) const
    {
        return tehenek.size() < other.tehenek.size();
    }
};

bool kisebb(const Cseszealj &a, const Cseszealj &b)
{
    return a.getTehenek().size() < b.getTehenek().size();
}

int main()
{
    Cseszealj csesze;
    Tehen tehen1("Riska", 70);
    Tehen tehen2("Boci", 50);
    Tehen tehen3("Mucika", 100);
    Tehen tehen4("Uff", 99);
    Tehen tehen5("Boo", 99);
    Tehen tehen6("Buendia", 909);
    Juhaszkutya kutya;

    return 0;
}
