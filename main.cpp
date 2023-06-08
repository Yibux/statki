#include <iostream>

using namespace std;

class Player {
public:
    char plansza[30][30];
    //orientacja 0 pionowo, 1 poziomo
    //orientacja 0 lewo, gora, 1 prawo, dol
    bool czyKordySaPoprawne(int x, int y, int orientacja, int strona, int dlugoscStatku) {
        if(x < 0 || y < 0 || x >= 30 || y >= 30 ||
        (strona != 1 && strona != 0) ||
        (orientacja == 1 && x + dlugoscStatku >= 30) ||
        (orientacja == 0 && y + dlugoscStatku >= 30))
            return false;

        for (int i = 0; i < dlugoscStatku; ++i) {
            if (orientacja == 1 && plansza[x + i][y] != '*') {
                return false;
            }
            if (orientacja == 0 && plansza[x][y + i] != '*') {
                return false;
            }
        }

        return true;
    }
    //0 powodzenie, 1 zajete miejsce, 2 niepoprawne kordy
    int postawStatek(int x, int y, int strona, int orientacja, int dlugoscStatku) {
        if(!czyKordySaPoprawne(x,y,orientacja,strona,dlugoscStatku))
            return 2;
        for (int i = 0; i < dlugoscStatku; ++i) {
            if (orientacja == 1) {
                plansza[x + i][y] = 'S';
            }
            else {
                plansza[x][y + i] = 'S';
            }
        }
        return 0;
    }
};

class Statki {
private:
    Player players[2];
public:
    Statki() {
        for (int i = 0; i < 30; ++i) {
            for (int j = 0; j < 30; ++j) {
                players[0].plansza[i][j] = '*';
                players[1].plansza[i][j] = '*';
            }
        }
    }
    void wstawStatek(int gracz, int x, int y, int strona, int orientacja, int dlugoscStatku) {
        int wynik = players[gracz].postawStatek(x, y, strona, orientacja, dlugoscStatku);
        if (wynik == 0) {
            cout << "Statek zostal postawiony pomyslnie dla gracza " << gracz << endl;
        }
        else if (wynik == 1) {
            cout << "Miejsce jest juz zajete dla gracza " << gracz << endl;
        }
        else if (wynik == 2) {
            cout << "Niepoprawne koordynaty dla gracza " << gracz << endl;
        }
    }
};



int main() {
    Statki statki;

    int gracz = 0;
    while (gracz < 2) {
        cout << "Gracz " << gracz << ", podaj koordynaty statku (x, y): ";
        int x, y;
        cin >> x >> y;

        cout << "Podaj orientację statku (0 - pionowo, 1 - poziomo): ";
        int orientacja;
        cin >> orientacja;

        cout << "Podaj stronę statku (0 - lewo/góra, 1 - prawo/dół): ";
        int strona;
        cin >> strona;

        cout << "Podaj długość statku: ";
        int dlugoscStatku;
        cin >> dlugoscStatku;

        statki.wstawStatek(gracz, x, y, strona, orientacja, dlugoscStatku);
        gracz++;
    }
    return 0;
}
