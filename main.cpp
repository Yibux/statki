#include <iostream>

using namespace std;

class Player {
public:
    char plansza[30][30];
    //orientacja 0 pionowo, 1 poziomo
    //orientacja 0 lewo, gora, 1 prawo, dol
    bool czyKordySaPoprawne(int x, int y, int orientacja, int strona, int dlugoscStatku) {
        if(x < 0 || y < 0 || x >= 30 || y >= 30 || (strona != 1 && strona != 0) || (orientacja == 1 && x + dlugoscStatku >= 30) || (orientacja == 0 && y + dlugoscStatku >= 30))
            return false;
        return true;
    }
    //0 powodzenie, 1 zajete miejsce, 2 niepoprawne kordy
    int postawStatek(int x, int y, int strona, int orientacja, int dlugoscStatku) {
        if(!czyKordySaPoprawne(x,y,orientacja,strona,dlugoscStatku))
            return 2;

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
};



int main() {
    Statki statki;
    return 0;
}
