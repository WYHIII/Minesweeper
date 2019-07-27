/****************************
 * Minesweeper by Wu Yuhang
 * Version 0.1.0 (INSIDER)
****************************/

#include<iostream>
#include<cstdio>
#include<cstring>
#include<string>
#include<queue>
#include<ctime>
#include<iomanip>
#include<windows.h>
#include<conio.h>

#define VERSION "0.1.0 (INSIDER)"

using namespace std;

const int MAXN = 100 + 3;
const int dx[] = {-1, 0, 1, 1, 1, 0, -1, -1};
const int dy[] = {1, 1, 1, 0, -1, -1, -1, 0};

bool m[MAXN][MAXN], vis[MAXN][MAXN], f[MAXN][MAXN];
int num[MAXN][MAXN], level, n, size;

void start();
void welcome();
void draw();
void play();

//int scan(const string&);

int main() {
    start();
    play();
    return 0;
}

void start() {
    srand((unsigned)time(NULL));
    memset(m, false, sizeof(m));
    memset(f, false, sizeof(f));
    memset(vis, false, sizeof(vis));
    memset(num, 0, sizeof(num));

    welcome();

    int cnt = 0;
    while (cnt < n) {
        int x = rand() / (RAND_MAX / size);
        int y = rand() / (RAND_MAX / size);

        if (x < 1 || x > size || y < 1 || y > size) continue;
        m[x][y] = true;
        cnt++;
    }

    draw();
}

void draw() {
    system("cls");

    cout << "   "; for (int i = 1; i <= size; i++) cout << setw(3) << i;
    cout << endl << "    "; for (int i = 1; i <= size*3; i++) putchar('-');
    cout << "---> X" << endl;

    for (int i = 1; i <= size; i++) {
        cout << setw(3) << i; putchar('|');
        for (int j = 1; j <= size; j++) {
            if (!vis[i][j]) cout << " * ";
            else cout << ' ' << num[i][j] << ' ';
        }
        cout << endl;
    }
    cout << "   |" << endl << "   Y" << endl << "If you want to open a cell, input like this:'o 5 9'" << endl << "if you want to flag a cell, input like this:'f 5 9'" << endl << "if you want to cancle what you've done, input like this:'d 5 9'" << endl << endl;
}


void play() {
    char c;
    int x, y;

    cin >> c;
    switch(c) {
        case 'o': cin >> x >> y; if (m[x][y]) {system("cls"); cout << "Game Over :(";} else {vis[x][y] = true; draw();} break;
        case 'f': cin >> x >> y; f[x][y] = true; draw(); break;
        case 'd': cin >> x >> y; f[x][y] = false; draw(); break;
    }

}

void welcome() {
    cout << "Welcome to Minesweeper " << VERSION << "." << endl << "Press any key to continue."; getch(); system("cls");
    cout << "Select difficult level." << endl << "Level 1: 10 mines , 10 * 10 (EASY)" << endl << "Level 2: 40 mines , 20 * 20 (MEDIUM)" << endl << "Level 3: 100 mines , 50 * 50 (DIFFICULT)" << endl;
    char c; cin >> c;
    while (c != '1' && c != '2' && c != '3') {
        cout << "Wrong number, please input again." << endl;
        cin >> c;
    }
    level = c - '0';
    system("cls");cout << "Press any key to start the Game"; getch(); system("cls");

    if (level == 1) {n = 10; size = 10;}
    else if (level == 2) {n = 40; size = 20;}
    else if (level == 3) {n = 100; size = 50;}
    else abort();
}