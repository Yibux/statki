#include <iostream>
#include <vector>
#include <random>
#include <chrono>

using namespace std;

class Player {
public:
    static const int BOARD_SIZE = 30;

    char plansza[BOARD_SIZE][BOARD_SIZE];

    Player() {
        for (int i = 0; i < BOARD_SIZE; ++i) {
            for (int j = 0; j < BOARD_SIZE; ++j) {
                plansza[i][j] = '*';
            }
        }
    }

    void wyswietlPlansze() {
        for (int i = 0; i < BOARD_SIZE; ++i) {
            for (int j = 0; j < BOARD_SIZE; ++j) {
                cout << plansza[i][j] << " ";
            }
            cout << endl;
        }
    }

    bool czyKoordynatyPoprawne(int x, int y) {
        return (x >= 0 && x < BOARD_SIZE && y >= 0 && y < BOARD_SIZE);
    }

    bool czyPolePuste(int x, int y) {
        return (plansza[x][y] == '*');
    }

    bool czyMoznaPostawicStatek(int x, int y, int orientacja, int dlugoscStatku) {
        if (!czyKoordynatyPoprawne(x, y))
            return false;

        if (orientacja == 1 && y + dlugoscStatku >= BOARD_SIZE)
            return false;

        if (orientacja == 0 && x + dlugoscStatku >= BOARD_SIZE)
            return false;

        for (int i = 0; i < dlugoscStatku; ++i) {
            if (orientacja == 0 && !czyPolePuste(x, y + i))
                return false;

            if (orientacja == 1 && !czyPolePuste(x + i, y))
                return false;
        }

        return true;
    }

    bool postawStatek(int x, int y, int orientacja, int dlugoscStatku) {
        if (!czyKoordynatyPoprawne(x, y) || !czyMoznaPostawicStatek(x, y, orientacja, dlugoscStatku)) {
            cout << "Nie można postawić statku na tych koordynatach." << endl;
            return false;
        }

        for (int i = 0; i < dlugoscStatku; ++i) {
            if (orientacja == 1)
                plansza[x][y + i] = dlugoscStatku + '0';
            else
                plansza[x + i][y] = dlugoscStatku + '0';
        }
        return true;
    }

    void automatyczneRozstawienieStatkow(const vector<int>& dlugosciStatkow) {
        //srand(time(nullptr));
        srand(std::chrono::system_clock::now().time_since_epoch().count());

        for (int dlugosc : dlugosciStatkow) {
            int orientacja;
            int x, y;
            while(true) {
                orientacja = rand() % 2;
                if(orientacja == 0) {
                    x = rand() % BOARD_SIZE;
                    y = rand() % BOARD_SIZE - dlugosc;
                } else {
                    x = rand() % BOARD_SIZE-dlugosc;
                    y = rand() % BOARD_SIZE;
                }
                if(czyMoznaPostawicStatek(x, y, orientacja, dlugosc))
                    break;
            }

            postawStatek(x, y, orientacja, dlugosc);
        }
    }
};

class Statki {
private:
    Player players[2];
    vector<int> dlugosciStatkow;

public:
    Statki(const vector<int>& dlugosciStatkow) : dlugosciStatkow(dlugosciStatkow) {}

    void rozstawStatkiRecznie(int gracz) {
        cout << "Gracz " << gracz << ", reczne rozstawienie statkow." << endl;

        for (int dlugosc : dlugosciStatkow) {
            bool poprawneKoordynaty = false;
            int x, y, orientacja;

            while (!poprawneKoordynaty) {
                cout << "Podaj koordynaty dla statku o dlugosci " << dlugosc << ":" << endl;
                cout << "Wprowadz x: ";
                cin >> x;

                cout << "Wprowadz y: ";
                cin >> y;

                cout << "Wprowadz orientacje (0 - pionowo, 1 - poziomo): ";
                cin >> orientacja;

                if (players[gracz].czyKoordynatyPoprawne(x, y)) {
                    poprawneKoordynaty = true;
                } else {
                    cout << "Niepoprawne koordynaty. Wprowadz je ponownie." << endl;
                }
            }

            players[gracz].postawStatek(x, y, orientacja, dlugosc);
            players[gracz].wyswietlPlansze();
        }

    }

    void rozstawStatkiAutomatycznie() {
        for (int i = 0; i < 2; ++i) {
            players[i].automatyczneRozstawienieStatkow(dlugosciStatkow);
        }
    }

    void rozpocznijGre() {
        int aktualnyGracz = 0;

        while (true) {
            cout << "Gracz " << aktualnyGracz << ", twoj ruch." << endl;
            cout << "Wprowadz koordynaty strzalu (x, y): ";
            int x, y;
            cin >> y >> x;

            if (!players[1 - aktualnyGracz].czyKoordynatyPoprawne(x, y)) {
                cout << "Nieprawidlowe koordynaty strzalu." << endl;
                continue;
            }

            char pole = players[1 - aktualnyGracz].plansza[x][y];
            if (pole == 'X' || pole == 'O') {
                cout << "To pole zostalo juz trafione." << endl;
                continue;
            }

            if (pole == '*') {
                cout << "Pudlo!" << endl;
                players[1 - aktualnyGracz].plansza[x][y] = 'O';
            }
            else {
                int dlugoscStatku = pole - '0';
                players[1 - aktualnyGracz].plansza[x][y] = 'X';

                bool zatopiony = true;
                for (int i = 0; i < Player::BOARD_SIZE; ++i) {
                    for (int j = 0; j < Player::BOARD_SIZE; ++j) {
                        if (players[1 - aktualnyGracz].plansza[i][j] == dlugoscStatku + '0') {
                            zatopiony = false;
                            break;
                        }
                    }
                }

                if (zatopiony) {
                    cout << "Trafiony zatopiony!" << endl;
                }
                else {
                    cout << "Trafiony!" << endl;
                }
            }

            players[1 - aktualnyGracz].wyswietlPlansze();

            bool czyKoniecGry = true;
            for (int i = 0; i < Player::BOARD_SIZE; ++i) {
                for (int j = 0; j < Player::BOARD_SIZE; ++j) {
                    if (players[1 - aktualnyGracz].plansza[i][j] >= '2' && players[1 - aktualnyGracz].plansza[i][j] <= '5') {
                        czyKoniecGry = false;
                        break;
                    }
                }
            }

            if (czyKoniecGry) {
                cout << "Gracz " << aktualnyGracz << " wygral!" << endl;
                break;
            }

            aktualnyGracz = 1 - aktualnyGracz;
        }
    }
};

int main() {
    vector<int> dlugosciStatkow;
    int iloscRodzajowStatkow;

    cout << "Podaj ilosc rodzajow statkow (2-5): ";
    cin >> iloscRodzajowStatkow;
    while (getchar()!='\n');
    if (iloscRodzajowStatkow < 2 || iloscRodzajowStatkow > 5) {
        cout << "Nieprawidlowa ilosc rodzajów statkow." << endl;
        return 0;
    }

    cout << "Podaj dlugosci statkow (oddzielone spacja): ";
    for (int i = 0; i < iloscRodzajowStatkow; ++i) {
        int dlugosc;
        cin >> dlugosc;
        dlugosciStatkow.push_back(dlugosc);
    }
    while (getchar()!='\n');

    Statki statki(dlugosciStatkow);

    int opcja;
    cout<<"Wybierz jakie ma byc rozstawienie statkow (0 - recznie, 1 - automatyczne): ";
    cin>>opcja;
    while (getchar()!='\n');
    switch (opcja) {
        case 0:
            cout << "Rozstawienie statkow: " << endl;
            statki.rozstawStatkiRecznie(0);
            statki.rozstawStatkiRecznie(1);
            break;
        case 1:
            cout << "Automatyczne rozstawienie statkow: " << endl;
            statki.rozstawStatkiAutomatycznie();
            break;
        default:
            cout<<"Wybrano zla wartosc. Koniec programu.";
            return 1;
    }

    cout << "Rozpocznij gre!" << endl;
    statki.rozpocznijGre();

    return 0;
}
