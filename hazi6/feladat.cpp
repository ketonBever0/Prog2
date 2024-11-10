#include <iostream>
#include <utility>
#include <vector>
#include <functional>
#include <algorithm>
#include <cmath>

using namespace std;

class Etel {
    string nev;
    string leiras;
    unsigned ar;

public:
    Etel() {
        this->nev = "amint kesz megtudod";
        this->leiras = "ami sikerul";
        this->ar = 0;
    }

    Etel(const string &nev, const string &leiras, const unsigned ar) {
        this->nev = nev;
        this->leiras = leiras;
        this->ar = ar;
    }

    virtual string get_nev() {
        return nev;
    }

    string get_leiras() {
        return leiras;
    }

    explicit virtual operator unsigned() const {
        return ar;
    }

    [[nodiscard]] virtual unsigned get_type() const {
        return 0;
    }

    [[nodiscard]] unsigned get_ar() const {
        return ar;
    }
};


class Menu : public Etel {
    string nev;
    string leiras;
    unsigned ar;
    vector<Etel> etelek;

public:
    Menu() : Etel() {
    }

    Menu(string nev, string leiras) : Etel() {
        this->nev = std::move(nev);
        this->leiras = std::move(leiras);
        this->ar = 0;
    }

    Menu(string nev, string leiras, const Etel &egy, const Etel &ketto, const Etel &harom) : Etel() {
        this->nev = std::move(nev);
        this->leiras = std::move(leiras);
        this->ar = 0;
        etelek.push_back(egy);
        etelek.push_back(ketto);
        etelek.push_back(harom);
    }

    string get_nev() override {
        string str = "Menu:\n";
        for (auto &i: etelek) {
            str += i.get_nev();
            str += "\n";
        }
        return str;
    }

    explicit operator unsigned() const override {
        unsigned vegar = 0;
        for (auto &i: etelek) {
            vegar += i.get_ar();
        }
        return vegar - round(vegar * 0.1);
    }

    Etel &operator[](const int i) {
        if (i < 0 || i >= etelek.size()) {
            throw exception();
        }
        return this->etelek[i];
    }

    [[nodiscard]] unsigned get_type() const override {
        return 1;
    }
};

class Vendeglo {
    vector<reference_wrapper<Etel> > etelek;

public:
    Vendeglo() = default;

    Vendeglo &operator<<(Etel &mit) {
        etelek.emplace_back(mit);
        return *this;
    }

    Etel &operator[](const int i) const {
        if (i < 0 || i >= static_cast<int>(etelek.size())) {
            throw exception();
        }
        return etelek[i];
    }

    explicit operator Etel &() const {
        if (etelek.empty()) throw std::exception();

        const auto min_it = std::min_element(etelek.begin(), etelek.end(), [](const Etel &a, const Etel &b) {
            return a.get_ar() < b.get_ar();
        });

        return *min_it;
    }
};


int main() {
    // 1. feladat: Etel osztály tesztelése
    Etel etel1; // Default konstruktor
    Etel etel2("Pizza", "Sonkás-sajtos pizza", 1200); // Paraméteres konstruktor

    std::cout << "Etel1 neve: " << etel1.get_nev() << ", leírása: " << etel1.get_leiras() << ", ára: " << (unsigned int)
            etel1 << "\n";
    std::cout << "Etel2 neve: " << etel2.get_nev() << ", leírása: " << etel2.get_leiras() << ", ára: " << (unsigned int)
            etel2 << "\n";

    // 2. feladat: Menu osztály tesztelése
    Etel etel3("Leves", "Zöldségleves", 600);
    Etel etel4("Tészta", "Spagetti bolognese", 1500);
    Menu menu1("Ebédmenü", "3 fogásos ebéd", etel2, etel3, etel4);

    std::cout << "Menu neve: " << menu1.get_nev() << "\n";
    std::cout << "Menu ára: " << (unsigned int) menu1 << "\n"; // 10% kedvezmény

    // 3. feladat: Vendeglo osztály tesztelése
    Vendeglo vendeglo;
    vendeglo << etel3 << etel2 << etel4 << menu1;

    try {
        std::cout << "A vendéglő legolcsóbb étele: " << vendeglo.operator Etel().get_nev() << "\n";
    } catch (const std::exception &e) {
        std::cout << "Hiba: " << e.what() << "\n";
    }

    return 0;
}
