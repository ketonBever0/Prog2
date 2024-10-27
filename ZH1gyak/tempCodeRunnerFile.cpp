bool operator<(const Feladat &masik) const
    {
        if (this->prioritas == masik.prioritas)
            return masik.eroforrasigeny > this->eroforrasigeny;
        else
            return masik.prioritas < this->prioritas;
    }