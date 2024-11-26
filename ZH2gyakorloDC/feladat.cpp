#include <algorithm>
#include <iostream>
#include <set>
#include <string>
#include <utility>
#include <vector>

using namespace std;

class Allat {
private:
    std::string nev;
    unsigned kor;

public:
    Allat(std::string nev, unsigned kor) : nev(nev), kor(kor) {
    }

    virtual ~Allat() = default;

    virtual void hangotAd() const = 0;

    unsigned getKor() const {
        return kor;
    }

    const std::string &getNev() const {
        return nev;
    }

    virtual std::string getFajta() const = 0;

    virtual bool isNovenyevo() const {
        return false;
    }

    virtual unsigned getTaplalekSzukseglet() const {
        return 0;
    }
};

class Ragadozo : public Allat {
private:
    unsigned vadaszatiUgyesseg;

public:
    Ragadozo(const std::string &nev, unsigned kor, unsigned vadaszatiUgyesseg)
        : Allat(nev, kor), vadaszatiUgyesseg(vadaszatiUgyesseg) {
    }

    unsigned getVadaszatiUgyesseg() const {
        return vadaszatiUgyesseg;
    }


};

class Novenyevo : public Allat {
private:
    unsigned taplalekSzukseglet;

public:
    Novenyevo(const std::string &nev, unsigned kor, unsigned taplalekSzukseglet)
        : Allat(nev, kor), taplalekSzukseglet(taplalekSzukseglet) {
    }

    unsigned getTaplalekSzukseglet() const override {
        return taplalekSzukseglet;
    }

    bool isNovenyevo() const override {
        return true;
    }
};


class Tigris : public Ragadozo {
public:
    Tigris(const std::string &nev, const unsigned &kor, const unsigned &vadaszatiUgyesseg) : Ragadozo(
        nev, kor, vadaszatiUgyesseg) {
    }

    void hangotAd() const override {
        cout << "Rawr!" << endl;
    }

    [[nodiscard]] string getFajta() const override {
        return "Tigris";
    }
};

class Zsiraf : public Novenyevo {
public:
    Zsiraf(const string &nev, const unsigned &kor, const unsigned &taplalekSzukseglet) : Novenyevo(
        nev, kor, taplalekSzukseglet) {
    }

    void hangotAd() const override {
        cout << "Nyuuu!" << endl;
    }

    [[nodiscard]] string getFajta() const override {
        return "Zsiraf";
    }
};


class Allatkert {
    vector<Allat> allatok;
    set<Allat> elhelyezettek;

public:
    Allatkert() = default;

    bool is_elhelyezve(const Allat &allat) const {
        return elhelyezettek.find(allat) != elhelyezettek.end();
    }

    Allatkert &operator+=(const Allat &allat) {
        allatok.push_back(allat);
        return *this;
    }

    Allatkert &operator>>(const unsigned &index) {
        if (index >= allatok.size() || !is_elhelyezve(allatok[index])) throw out_of_range("HIBA");
        elhelyezettek.emplace(allatok[index]);
        return *this;
    }

    void listaz() const {
        for (const auto& allat : allatok) {
            cout << allat.getNev() << " - " << (is_elhelyezve(allat) ? "elhelyezve" : "nincs elhelyezve") << endl;
        }
    }

    [[nodiscard]] unsigned szabadHelyek() const {
        unsigned num = 0;
        for (const auto &allat : allatok) {
            if (!is_elhelyezve(allat)) num++;
        }
        return num;
    }

    void hangParade() const {
        for (const auto &allat : allatok) {
            if (is_elhelyezve(allat)) {
                elhelyezettek.find(allat)->hangotAd();
            }
        }
    }

    unsigned taplalekIgeny() {
        unsigned num = 0;
        for_each(allatok.begin(), allatok.end(), [&num](const Allat &allat) {
            if (allat.isNovenyevo()) {
                if (allat.isNovenyevo() && allat.getTaplalekSzukseglet() > 0) num += allat.getTaplalekSzukseglet();
            }
        });
        return num;
    }

    unsigned kulonboKor() const {
        set<unsigned> korok;
        for_each(allatok.begin(), allatok.end(), [&korok](const Allat &allat) {
            korok.emplace(allat.getKor());
        });
        return korok.size();
    }


};


#ifndef TEST_BIRO
int main() {

    Zsiraf zs("Nyakas",11,100);
    std::cout << zs.getFajta() << ": " << zs.getKor() << " - "  << zs.getNev() << std::endl;
    zs.hangotAd();

    Tigris t("Cica",12,123);
    std::cout << t.getFajta() << ": " << t.getKor() << " - "  << t.getNev() << std::endl;
    t.hangotAd();

    Allatkert a;
    a+=zs;
    a+=t;
    a >> 1;
    a.listaz();

    std::cout << a.taplalekIgeny() << std::endl;
    std::cout << a.szabadHelyek() << std::endl;
    a.hangParade();
    std::cout << a.kulonboKor() << std::endl;


    return 0;
}
#endif
