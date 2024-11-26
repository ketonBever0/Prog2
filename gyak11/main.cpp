#include <iostream>
#include <string>
#include <vector>
#include <numeric>

using namespace std;

struct Kolomp{

  explicit Kolomp(unsigned h):hanyszor(h){
    cout << "Kolomp (" << hanyszor << ") letrejott" << endl;
  }

  ~Kolomp(){
    cout << "Kolomp (" << hanyszor << ") megsemmisul" << endl;
  }

  string hangotAd() const{
    std::string result;
    for (unsigned i = 0; i < hanyszor; ++i) {
      result += " kolompol";
    }
    return result;
  }

private:
  unsigned hanyszor;
};

class Allat{
  string nev;

public:
  Allat(const string& nev):nev(nev){
    cout << nev << " letrejott" << endl;
  }

  ~Allat(){
    cout << "Allat megsemmisul (" << nev << ")" << endl;
  }

  virtual string hangotAd() const {
    return "Hangot ad:";
  }

  const string& getNev() const {
    return nev;
  }
};



class Tehen: public Allat{
  Kolomp * kolomp;
public:
  Tehen(const string& str, unsigned kolompolasSzam):Allat(str), kolomp(kolompolasSzam > 0 ? new Kolomp(kolompolasSzam) : nullptr){
  }

  ~Tehen(){
    cout << "Tehen megsemmisul (" << getNev() << ")" << endl;
    delete kolomp;
  }

  Tehen(const Tehen& t):Allat(t), kolomp(t.kolomp == nullptr ? nullptr : new Kolomp(*t.kolomp)){

  }

  Tehen& operator=(const Tehen& t){
    if(&t == this)
      return *this;
    Allat::operator=(t);
    delete kolomp;
    kolomp = t.kolomp == nullptr ? nullptr : new Kolomp(*t.kolomp);

    return *this;
  }

  string hangotAd() const override{
    string result = Allat::hangotAd() + "muuu";
    if(kolomp){
      result += kolomp->hangotAd();
    }
    return result;
  }
};

class Ponty: public Allat{
public:
  Ponty():Allat("Nemo"){ }

  string hangotAd() const override{
    return Allat::hangotAd() + "blub-blub";
  }
};

class Cseszealj{
  vector<Allat*> allatok;

public:
  void elrabol(Allat* a){
    allatok.push_back(a);
  }

  void meghallgat()const{
    string result = accumulate(allatok.begin(), allatok.end(), string(), [](string res, const Allat* a){
      res += a->hangotAd();
      res += '\n';
      return res;
    });
    cout << result << endl;
  }
};


int main() {
  Cseszealj cs;
  Ponty p;
  Allat* a = new Tehen("Maris", 5);

  cs.elrabol(a);
  cs.elrabol(&p);

  delete a;

  return 0;
}
