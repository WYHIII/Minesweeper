/****************************
 * Minesweeper by Wu Yuhang
 * Version 1.0.0 INSIDER
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

#define VERSION "1.0.0 (INSIDER)"

using std::cin;
using std::cout;
using std::endl;
using std::queue;
using std::putchar;
using std::setw;

void start();
void welcome();
void draw();
void play();
inline void gameover();

void win();
bool check(int, int);
void open(int, int);
void flag(int, int);
void del(int, int);

const int MAXN = 100 + 3;
const int dx[] = {-1, 0, 1, 1, 1, 0, -1, -1};
const int dy[] = {1, 1, 1, 0, -1, -1, -1, 0};

bool m[MAXN][MAXN], vis[MAXN][MAXN], f[MAXN][MAXN];
int num[MAXN][MAXN], level, n, size, flags;

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

    for (int i = 1; i <= size; i++) {
        for (int j = 1; j <= size; j++) {
            if (!m[i][j]) {
                for (int k = 0; k < 8; k++) {
                    int xx = i + dx[k];
                    int yy = j + dy[k];
                    num[i][j] += m[xx][yy] ? 1 : 0;
                }
            }
        }
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
            if (f[i][j]) cout << " ! ";
            else if (!vis[i][j]) cout << " * ";
            else cout << ' ' << num[i][j] << ' ';
        }
        cout << endl;
    }
    cout << "   |" << endl << "   Y" << endl << "If you want to open a cell, input like this:'o 5 9'" << endl << "if you want to flag a cell, input like this:'f 5 9'" << endl << "if you want to cancle what you've done, input like this:'d 5 9'" << endl << endl;
}

void welcome() {
    cout << "Welcome to Minesweeper " << VERSION << "." << endl << "Press any key to continue."; getch(); system("cls");
    cout << "Select difficult level." << endl << "Level 1: 20 mines , 10 * 10 (EASY)" << endl << "Level 2: 80 mines , 20 * 20 (MEDIUM)" << endl << "Level 3: 500 mines , 50 * 50 (DIFFICULT)" << endl;
    char c; cin >> c;
    while (c != '1' && c != '2' && c != '3') {
        cout << "Wrong number, please input again." << endl;
        cin >> c;
    }
    level = c - '0';
    system("cls");cout << "Press any key to start the Game"; getch(); system("cls");

    if (level == 1) {n = flags = 20; size = 10;}
    else if (level == 2) {n = flags = 80; size = 20;}
    else if (level == 3) {n = flags = 500; size = 50;}
    else exit(1);
}

inline void gameover() {
    system("cls"); cout << "Game Over :(" << endl;
    system("pause"); exit(0);
}

bool check(int x, int y) {
    if (x > 0 && x <= size && y > 0 && y <= size) return true;
    cout << "Illegal instruction." << endl << "Press any key to continue." << endl; getch();
    return false;
}

void win() {
    for (int i = 1; i <= size; i++)
        for (int j = 1; j <= size; j++)
            if (m[i][j] && !f[i][j]) return;

    cout << "You win :)" << endl << "Press any key to continue." << endl; getch(); exit(0);
}

void play() {
    char c; int x, y;

    while (cin >> c) {
        switch(c) {
            case 'o': case 'O': cin >> y >> x; if (check(x, y)) open(x, y); break;
            case 'f': case 'F': cin >> y >> x; if (check(x, y)) flag(x, y); break;
            case 'd': case 'D': cin >> y >> x; if (check(x, y)) del(x, y); break;
            default: cout << "Unrecognized instructions." << endl << "Press any key to continue." << endl; getch(); break;
        }

        draw();
    }
}

void open(int x, int y) {
    if (m[x][y]) gameover();
    if (f[x][y]) {cout << "Can't open this cell.Flags on." << endl << "Press any key to continue." << endl; getch(); return;}
    vis[x][y] = true;
}

void flag(int x, int y) {
    if (!flags) {cout << "You use out of flags.Try to remove some of them." << endl << "Press any key to continue." << endl; getch(); return;}
    if (vis[x][y]) {cout << "Can't use flag.You've visited this cell." << endl << "Press any key to continue." << endl; getch(); return;}
    f[x][y] = true; flags--;

    win();
}

void del(int x, int y) {
    if (!f[x][y]) {cout << "This cell doesn't have flag." << endl << "Press any key to continue." << endl; getch(); return;}
    f[x][y] = false; flags++;
}