#include <algorithm>
#include <iostream>
#include <set>
#include <vector>

using namespace std;

#ifndef MY_BADGE
/**
 * Badge osztály, ami egy elért teljesítményt jelent.
 * Van címe, mely a teljesítmény típusára utal és fokozata, mely 0 - 4 lehet.
 */
class Badge {
    string cim;
    unsigned fokozat;

public:
    /**
     * Konstruktor.
     * @param cim a badge címe
     */
    Badge(const string &cim, unsigned fokozat = 0) : cim(cim), fokozat(fokozat) {
    }

    /**
     * Default constructor a tárolókhoz.
     */
    Badge() = default;

    /**
     * Visszaadja a Badge címét.
     * @return a string-ként a badge címe
     */
    const string &getCim() const { return cim; }

    /**
     * Visszaadja a Badge fokozatát.
     * @return fokozat unsigned-ként.
     */
    unsigned getFokozat() const { return fokozat; }

    /**
     * Fokozat növelése maximum 4-ig.
     * @return Badge referencia az objektumra.
     */
    Badge &operator++() {
        if (fokozat <= 3) { ++fokozat; }
        return *this;
    }
};
#endif

class Pokemon {
    string _nev;
    unsigned _tamadas;
    unsigned _vedekezes;

public:
    Pokemon(const string &nev // poke neve
            , unsigned tamadas = 10 // poke tamadasi ereje
            , unsigned vedekezes = 10) // poke vedelmi ereje
        : _nev(nev)
          , _tamadas(tamadas)
          , _vedekezes(vedekezes) {
    }

    /**
     * Visszaadja a Pokemon nevét.
     * @return a Pokemon neve stringként.
    */
    operator string() const { return _nev; }

    /**
     * Getter a támadási erőre
     * @return A támadási erő értéke
     */
    unsigned getTamadas() const { return _tamadas; }

    /**
     * Getter a védekéezési erőre
     * @return A védekéezési erő értéke
     */
    unsigned getVedekezes() const { return _vedekezes; }

    /**
     * Eldönti, hogy a pokemont legyőzi-e az adott értékű támadás.
     * @param tamadasiEro a támadás ereje
     * @return true, ha a pokemonnál erősebb a támadás, egyébként false
     */
    virtual bool operator <(unsigned tamadasiEro) const { return _vedekezes < tamadasiEro; }
};

class PokeLabda {
    unsigned _tamadasiEro;

public:
    PokeLabda(unsigned tamadasiEro) : _tamadasiEro(tamadasiEro) {
    }

    [[nodiscard]] unsigned getEro() const {
        return this->_tamadasiEro;
    }

    /**
     * Megtámadja a pokemont. Ha a támadás ereje nagyobb, mint a pokemon védelme, akkor a pokemon legyőzésre kerül.
     * @param p a megtámadott pokemon
     * @return a legyőzött pokemon
     * @throws "Edzeni kell!", ha a pokemon túl erős
     */
    bool operator ()(const Pokemon p) const {
        if (p < _tamadasiEro) { return true; }

        throw string("Edzeni kell!");
    }

    /**
     * Visszaadja, hogy a pokelabda gyengébb-e egy másiknál.
     * @param labda a másik pokelabda
     * @return true, ha a pokelabda gyengébb, egyébként false
     */
    bool operator <(const PokeLabda &labda) const { return _tamadasiEro < labda._tamadasiEro; }
};

// IDE DOLGOZZ!!!

class FenyesPokemon : public Pokemon {
    unsigned fenyero;

public:
    FenyesPokemon(const string &nev, const unsigned &tamadas, const unsigned &vedekezes,
                  const unsigned &fenyero) : Pokemon(nev, tamadas, vedekezes), fenyero(fenyero) {
    }

    bool operator <(unsigned tamadasiEro) const override { return getVedekezes() < this->fenyero; }
};

class PokeTrainer {
public:
    set<PokeLabda> labdak;
    vector<Pokemon> elkapottak;
    vector<Badge> badgek;

    PokeTrainer() = default;

    PokeTrainer &operator+=(const PokeLabda &labda) {
        labdak.emplace(labda);
        return *this;
    }

    PokeTrainer operator>>(const Pokemon &pokemon) {
        for (const auto labda: labdak) {
            try  {
                if (labda(pokemon)) cout << "Elkapva: " << string(pokemon);
            } catch (...) {
                cout << "Edzeni kell!";
            }
        }
        return *this;
    }

    [[nodiscard]] unsigned veszit(const unsigned &tamadas) const {
        unsigned legyozne = 0;
        for (const auto &pokemon: elkapottak) {
            if (tamadas >= pokemon.getTamadas()) legyozne++;
        }
        return legyozne;
    }

    void badge(const vector<Badge> &badgek) {
        this->badgek.clear();
        transform(badgek.begin(), badgek.end(), back_inserter(this->badgek), [this](const Badge &badge) {
            return Badge(badge.getCim(), badge.getFokozat() + 1);
        });
    }

    void badgeLista() const {
        cout << "Badgek:" << endl;
        for (const auto &badge: this->badgek) {
            cout << badge.getCim() << " " << badge.getFokozat() << endl;
        }
    }

    void maxBadge() const {
        if (this->badgek.empty()) {
            cout << "Nincs badge!" << endl;
            return;
        }

        const auto max = max_element(this->badgek.begin(), this->badgek.end(),
                                     [](const Badge &badge1, const Badge &badge2) {
                                         return badge1.getFokozat() < badge2.getFokozat();
                                     });
        cout << max->getFokozat() << endl;
    }
};


int main() {
    return 0; // Ezt most tartsd meg!
}
