#include <iostream>
using namespace std;

int main()
{
    cout << "Szam: ";
    unsigned int n;
    cin >> n;

    string elrabolva = "";

    for (unsigned int i = 0; i < n; i++)
    {
        string nev;
        int tomeg;
        
        cin >> nev >> tomeg;

        cout << "Nev: " << nev << " Tomeg: " << tomeg;
        cout << endl;
        
        if (tomeg < 50 || nev.length() < 3)
        {
            cout << "Nincs elrabolva." << endl;
        } else {
            cout << "Elrabolva!" << endl;
            elrabolva += nev + " " + to_string(tomeg);
        }
        
        cout << elrabolva << endl;
    }
    
    

    return 0;
}