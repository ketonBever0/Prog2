#include <string>
#include <iostream>
#include <set>
#include <vector>
#include <map>
#include <algorithm>

using namespace std;

class Telepes
{

  string nev = "";
  string szulBolygo = "";
  string bolygo = "";
  unsigned ero = 1;
  bool vegan = false;

public:
  Telepes()
  {
    nev = "";
    szulBolygo = "";
    bolygo = "";
    ero = 1;
    this->vegan = false;
  }

  Telepes(string nev, string bolygo, unsigned ero = 1)
  {
    this->nev = nev;
    this->bolygo = bolygo;
    this->szulBolygo = bolygo;
    this->ero = ero;
  }

  Telepes(string nev, string szulBolygo, string bolygo, unsigned ero)
  {
    this->nev = nev;
    this->bolygo = bolygo;
    this->szulBolygo = szulBolygo;
    this->ero = ero;
  }

  const string &getNev() const
  {
    return this->nev;
  }

  const string &getSzulBolygo() const
  {
    return this->szulBolygo;
  }

  const string &getBolygo() const
  {
    return this->bolygo;
  }

  unsigned getEro() const
  {
    return this->ero;
  }

  const bool isVegan()
      const
  {
    return this->vegan;
  }

  void setNev(string nev)
  {
    this->nev = nev;
  }

  void setSzulBolygo(string szulBolygo)
  {
    this->szulBolygo = szulBolygo;
  }

  void setBolygo(string bolygo)
  {
    this->bolygo = bolygo;
  }

  void setEro(unsigned ero)
  {
    this->ero = ero;
  }

  void setVegan(bool vegan)
  {
    this->vegan = vegan;
  }
};

class Kolonia
{

  const static unsigned max = 25;
  vector<Telepes> telepesek;
  string nev;
  string bolygo;

public:
  string getNev() const { return nev; }
  string getBolygo() const { return bolygo; }
  const unsigned getLetszam() const { return telepesek.size(); }
  const vector<Telepes> &getTelepesek() const
  {
    return telepesek;
  }

  Kolonia(string nev, string bolygo)
  {
    this->nev = nev;
    this->bolygo = bolygo;
  }

  Kolonia()
  {
    this->nev = "";
    this->bolygo = "";
  }

  friend bool veganE(const Kolonia &melyik);
  void letelepszik(Telepes ki)
  {
    if (getLetszam() >= max)
    {
      cout << "A kolonia megtelt" << endl;
    }
    else
    {
      if (veganE(*this) && !ki.isVegan())
      {
        cout << "A kolonia vegan" << endl;
        return;
      }
      ki.setBolygo(bolygo);
      telepesek.push_back(ki);
    }
  }

  void nevsor()
  {
    set<string> nevek;
    for (unsigned i = 0; i < getLetszam(); i++)
    {
      nevek.insert(telepesek[i].getNev());
    }
    for (string nev : nevek)
    {
      cout << nev << endl;
    }
  }

  const unsigned legerosebb() const
  {
    if (telepesek.size() == 0)
      return 0;
    unsigned legerosebb = 0;
    for (Telepes telepes : telepesek)
    {
      if (telepes.getEro() > legerosebb)
        legerosebb = telepes.getEro();
    }
    return legerosebb;
  }

  const int szamol(string melyik) const
  {
    int mennyi = 0;
    for (Telepes telepes : telepesek)
    {
      string szulo = telepes.getSzulBolygo();

      transform(melyik.begin(), melyik.end(), melyik.begin(), ::tolower);
      transform(szulo.begin(), szulo.end(), szulo.begin(), ::tolower);

      if (szulo == melyik)
        mennyi++;
    }
    return mennyi;
  }

  map<unsigned, unsigned> eroHisztogram() const
  {
    map<unsigned, unsigned> erok;
    for (Telepes telepes : telepesek)
    {
      unsigned ero = telepes.getEro();
      if (erok.find(ero) == erok.end())
        erok[ero] = 1;
      else
        erok[ero]++;
    }
    return erok;
  }
};

bool veganE(const Kolonia &melyik)
{
  if (melyik.getLetszam() == 0)
    return false;

  unsigned veganok = 0;
  const vector<Telepes> &telepesek = melyik.getTelepesek();
  for (const Telepes &telepes : telepesek)
  {
    if (telepes.isVegan())
      veganok++;
  }
  return (veganok > (melyik.getLetszam() / 2));
}
