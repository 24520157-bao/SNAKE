#include <iostream>
#include <windows.h>
#include <cstdlib>
#include <conio.h>
using namespace std;

void gotoxy(int column, int line);

struct Point {
    int x, y;
};

class CONRAN {
public:
    Point A[200];
    int DoDai;

    CONRAN() {
        DoDai = 3;
        A[0].x = 10; A[0].y = 10;
        A[1].x = 11; A[1].y = 10;
        A[2].x = 12; A[2].y = 10;
    }

    void Ve() {
        for (int i = 0; i < DoDai; i++) {
            gotoxy(A[i].x, A[i].y);
            cout << "O";
        }
    }

    void DiChuyen(int Huong) {
        for (int i = DoDai - 1; i > 0; i--)
            A[i] = A[i - 1];

        if (Huong == 0) A[0].x++;
        if (Huong == 1) A[0].y++;
        if (Huong == 2) A[0].x--;
        if (Huong == 3) A[0].y--;
    }
};

struct MOI {
    int x, y;
};

MOI CreateFood() {
    MOI m;
    m.x = rand() % 67 + 6;
    m.y = rand() % 17 + 4;
    return m;
}

void VeFood(MOI m) {
    gotoxy(m.x, m.y);
    cout << "@";
}

void VeKhung(int x0, int y0, int w, int h) {
    if (w < 2 or h < 2) return;
    for (int x = x0; x < x0 + w; ++x) {
        gotoxy(x, y0); cout << '#';
        gotoxy(x, y0 + h - 1); cout << '#';
    }
    for (int y = y0; y < y0 + h; ++y) {
        gotoxy(x0, y); cout << '#';
        gotoxy(x0 + w - 1, y); cout << '#';
    }
}

int main() {
    CONRAN r;
    int Huong = 0;
    char t;

    srand(time(NULL));
    MOI moi = CreateFood();

    while (1) {
        if (_kbhit()) {
            t = _getch();
            if (t == 'a') Huong = 2;
            if (t == 'w') Huong = 3;
            if (t == 'd') Huong = 0;
            if (t == 'x') Huong = 1;
        }

        system("cls");
        VeKhung(5, 3, 70, 20);
        VeFood(moi);
        r.Ve();

        r.DiChuyen(Huong);

        if (r.A[0].x == moi.x && r.A[0].y == moi.y) {
            r.DoDai++;
            moi = CreateFood();
        }

        Sleep(300);
    }

    return 0;
}

void gotoxy(int column, int line) {
    COORD coord;
    coord.X = column;
    coord.Y = line;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}
