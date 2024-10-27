#include <string>
#include <vector>
#include <map>
#include <cassert>
#include <algorithm>
#include <iostream>

using namespace std;

class Telepes
{

  string nev, szul_bolygo, bolygo;
  unsigned oxigen;

public:
  Telepes(string _nev, string _szul_bolygo, string _bolygo, unsigned _oxigen) : nev(_nev),
                                                                                szul_bolygo(_szul_bolygo),
                                                                                bolygo(_bolygo),
                                                                                oxigen(_oxigen)
  {
  }

  Telepes() : Telepes("", "", "", 100)
  {
  }

  Telepes(string _nev, string _bolygo, unsigned _oxigen = 100) : Telepes(_nev, _bolygo, _bolygo, _oxigen)
  {
  }

  string getNev() const
  {
    return nev;
  }

  string getSzulBolygo() const
  {
    return szul_bolygo;
  }

  string getBolygo() const
  {
    return bolygo;
  }

  unsigned getOxigen() const
  {
    return oxigen;
  }

  void setNev(const string &_nev)
  {
    nev = _nev;
  }

  void setSzulBolygo(const string &_szul_bolygo)
  {
    szul_bolygo = _szul_bolygo;
  }

  void setBolygo(const string &_bolygo)
  {
    bolygo = _bolygo;
  }

  void setOxigen(unsigned _oxigen)
  {
    oxigen = _oxigen;
  }

  Telepes &operator-=(unsigned ox)
  {
    if (ox < oxigen)
    {
      oxigen -= ox;
    }
    else
    {
      oxigen = 0;
    }
    return *this;
  }

  operator string() const
  {
    return nev + " (" + bolygo + ", " + to_string(oxigen) + ")";
  }

  Telepes &operator++()
  {
    if (oxigen < 100)
      oxigen++;
    return *this;
  }

  Telepes operator++(int)
  {
    if (oxigen < 100)
      oxigen++;
    return *this;
  }

  int operator+(const Telepes &masik) const
  {
    return oxigen + masik.getOxigen();
  }
};

bool operator==(const Telepes &t1, const Telepes &t2)
{
  return t1.getNev() == t2.getNev() && t1.getOxigen() == t2.getOxigen() && t1.getBolygo() == t2.getBolygo() && t1.getSzulBolygo() == t2.getSzulBolygo();
}

class Korhaz
{
  string hely;
  map<string, vector<Telepes>> betegek;

public:
  unsigned getLetszam()
  {
    unsigned mennyi = 0;
    for (map<string, vector<Telepes>>::iterator it = betegek.begin(); it != betegek.end(); it++)
    {
      mennyi += it->second.size();
    }
    return mennyi;
  }

  unsigned getLetszam(string hol)
  {
    return betegek[hol].size();
  }

  unsigned getBolygokSzama() const
  {
    return betegek.size();
  }

  Korhaz &operator<<(const Telepes &kit)
  {
    betegek[kit.getBolygo()].push_back(kit);
    return *this;
  }

  Korhaz &operator>>(Telepes &kit)
  {
    for (map<string, vector<Telepes>>::iterator it = betegek.begin(); it != betegek.end(); it++)
    {
      vector<Telepes> &lista = it->second;
      for (vector<Telepes>::iterator beteg_it = lista.begin(); beteg_it != lista.end();)
      {
        if (*beteg_it == kit)
        {
          beteg_it = lista.erase(beteg_it);
        }
        else
        {
          ++beteg_it;
        }
      }
    }
    return *this;
  }

  bool operator<(const Korhaz &masik) const
  {
    return (getBolygokSzama() < masik.getBolygokSzama());
  }

  Korhaz operator+(const Korhaz masik) const
  {
    Korhaz uj;

    for (const auto &par : betegek)
    {
      for (const Telepes &beteg : par.second)
      {
        uj << beteg;
      }
    }

    for (const auto &par : masik.betegek)
    {
      for (const Telepes &beteg : par.second)
      {
        uj << beteg;
      }
    }

    return uj;
  }

  operator string()
  {
    string str = "";
    for (map<string, vector<Telepes>>::iterator it = betegek.begin(); it != betegek.end(); it++)
    {
      str += it->first + "\n";
      for (Telepes beteg : it->second)
      {
        str += string(beteg) + "\n";
      }
    }
    return str;
  }
};

void test_telepes()
{
  Telepes t1;
  assert(t1.getNev() == "");
  assert(t1.getSzulBolygo() == "");
  assert(t1.getBolygo() == "");
  assert(t1.getOxigen() == 100);

  t1.setSzulBolygo("Mars");
  t1.setBolygo("Venus");
  t1.setNev("Jevgenyij Anyegin");
  t1.setOxigen(70);
  assert(t1.getNev() == "Jevgenyij Anyegin");
  assert(t1.getSzulBolygo() == "Mars");
  assert(t1.getBolygo() == "Venus");
  assert(t1.getOxigen() == 70);

  Telepes t2("Jevgenyij Anyegin", "Mars", "Venus", 70);
  Telepes t3("Alekszej Vronszkij", "Mars", "Mars", 99);
  assert(t1 == t2);
  assert(!(t1 == t3)); // t1 es t3 nem egyenloek

  t1 -= 30;
  assert(t1.getOxigen() == 40);
  t1 -= 45;
  assert(t1.getOxigen() == 0); // max 0-ig csokkenhet az oxigenszint

  ((t2 -= 5) -= 30) -= 35;
  assert(t2.getOxigen() == 0); // 0-ra kell csokkennie az oxigenszintnek
  // cout << string(t2) << endl;
  assert(std::string(t2) == "Jevgenyij Anyegin (Venus, 0)");

  /* t2++;
   assert(t2.getOxigen() == 1);
   ++t2;
   assert(t2.getOxigen() == 2);*/
}

void test_korhaz()
{
  Korhaz k;
  Telepes t1("T1", "SzuletesiBolygo", "LakoBolygo1", 70);
  Telepes t2("T2", "SzuletesiBolygo", "LakoBolygo2", 70);
  Telepes t3("T3", "SzuletesiBolygo", "LakoBolygo1", 33);

  k << t1 << t2 << t3;

  assert(k.getLetszam() == 3);
  assert(k.getLetszam("LakoBolygo1") == 2);
  assert(k.getLetszam("LakoBolygo2") == 1);

  std::string expected = "LakoBolygo1\nT1 (LakoBolygo1, 70)\nT3 (LakoBolygo1, 33)\nLakoBolygo2\nT2 (LakoBolygo2, 70)\n";
  assert(std::string(k) == expected);

  k >> t1;
  assert(k.getLetszam() == 2);
  assert(k.getLetszam("LakoBolygo1") == 1);
  expected = "LakoBolygo1\nT3 (LakoBolygo1, 33)\nLakoBolygo2\nT2 (LakoBolygo2, 70)\n";
  assert(std::string(k) == expected);

  Korhaz k2;
  k2 << t1;
  assert(k2.getLetszam() == 1);
  assert(k2.getLetszam("LakoBolygo1") == 1);

  Korhaz k3 = k + k2;
  assert(k3.getLetszam() == 3);

  assert(k2 < k);
}

int main()
{
  test_telepes();
  test_korhaz();

  return 0;
}
