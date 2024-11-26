#include <algorithm>
#include <iostream>
#include <functional>
#include <string>
#include <utility>
#include <vector>
using namespace std;

class Komponens {
protected:
    string nev;

    explicit Komponens(string n) : nev(std::move(n)) {
    }

public:
    virtual explicit operator string() noexcept {
        return nev;
    }

    enum KomponensTipus { tAlaplap, tProcesszor, tMemoria, tKomponensMAX };

    [[nodiscard]] virtual KomponensTipus getTipus() const noexcept = 0;

    virtual ~Komponens() = default; // ez helyes
};


class Alaplap : public Komponens {
public:
    explicit Alaplap(const string &nev) : Komponens(nev) {
    }

    [[nodiscard]] KomponensTipus getTipus() const noexcept override {
        return tAlaplap;
    }

    explicit operator string() noexcept override {
        return this->nev;
    }
};


class Processzor : public Komponens {
    unsigned MHz;

public:
    Processzor(const string &nev, const unsigned &MHz) : Komponens(nev), MHz(MHz) {
    }

    explicit operator string() noexcept override {
        return Komponens::operator string() + " (" + to_string(MHz) + "MHz)";
    }

    [[nodiscard]] KomponensTipus getTipus() const noexcept override {
        return tProcesszor;
    }

    explicit operator unsigned() const {
        return MHz;
    }
};


class Memoria final : public Komponens {
    unsigned GB;

public:
    Memoria(const string &nev, const unsigned gb) : Komponens(nev), GB(gb) {
    }

    explicit operator string() noexcept override {
        return Komponens::operator string() + " (" + to_string(GB) + "GB RAM)";
    }

    [[nodiscard]] KomponensTipus getTipus() const noexcept override {
        return tMemoria;
    }

    explicit operator unsigned() const {
        return GB;
    }
};


class Raktar {
    vector<reference_wrapper<Komponens> > komponensek;

public:
    Raktar() = default;

    Raktar &operator<<(Komponens &komponens) {
        komponensek.emplace_back(komponens);
        return *this;
    }

    Komponens &operator[](const unsigned i) {
        try {
            return komponensek.at(i);
        } catch (const out_of_range &) {
            throw out_of_range("rossz index " + to_string(i));
        }
    }

    const Komponens &operator[](const unsigned i) const {
        if (i <= komponensek.size())
            return komponensek[i];
        throw out_of_range("rossz index " + to_string(i));
    }

    [[nodiscard]] unsigned getProcesszorDarab() const {
        return count_if(komponensek.cbegin(), komponensek.cend(), [](auto k) {
            return k.get().getTipus() == Komponens::tProcesszor;
        });
    }

    [[nodiscard]] unsigned getOsszMemoria() const {
        unsigned ossz = 0;
        for_each(komponensek.begin(), komponensek.end(), [&ossz](auto k) {
            if (k.get().getTipus() == Komponens::tMemoria)
                ossz =+ static_cast<unsigned>(*dynamic_cast<Memoria *>(&k.get()));
        });
        return ossz;
    }

    [[nodiscard]] bool vanTeljesGep() const {
        unsigned komp = 0;
        for_each(komponensek.begin(), komponensek.end(), [&komp](auto k) {
            komp |= 1 << k.get().getTipus();
        });
        for (unsigned i = 0; i <= Komponens::tKomponensMAX; i++) {
            if ((komp & 1 << i) == 0)
                return false;
        }
        return true;
    }


    void selejtez(const unsigned &minMHz, const unsigned &minGB) {
        vector<reference_wrapper<Komponens> > uj;
        copy_if(komponensek.rbegin(), komponensek.rend(), back_inserter(uj), [=](auto k) {
            switch (k.get().getTipus()) {
                case Komponens::tMemoria: {
                    const auto *memoria = dynamic_cast<Memoria *>(&k.get());
                    return memoria && minGB <= static_cast<unsigned>(*memoria);
                }
                case Komponens::tProcesszor: {
                    const auto *processzor = dynamic_cast<Processzor *>(&k.get());
                    return processzor && minMHz <= static_cast<unsigned>(*processzor);
                }
                default:
                    return true;
            }
        });
        komponensek = uj;
    }
};

ostream &operator<<(ostream &os, const Raktar &r) {
    try {
        for (unsigned i = 0; i < r.; ++i)
            os << string(const_cast<Komponens &>(r[i])) << endl;
    } catch (...) {
    }
    return os;
}

// int main() {
//     return 0;
// }
