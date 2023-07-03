#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

const int NUM_PLAYERS = 10;
const int FIELD_WIDTH = 20;
const int FIELD_HEIGHT = 10;

class Player {
    private:
        int x, y;
    public:
        Player(int px, int py) {
            x = px;
            y = py;
        }
        void move(int dx, int dy) {
            x += dx;
            y += dy;
            if (x < 0) x = 0;
            if (x >= FIELD_WIDTH) x = FIELD_WIDTH - 1;
            if (y < 0) y = 0;
            if (y >= FIELD_HEIGHT) y = FIELD_HEIGHT - 1;
        }
        int getX() { return x; }
        int getY() { return y; }
};

class Ball {
    private:
        int x, y, vx, vy;
    public:
        Ball(int px, int py, int pvx, int pvy) {
            x = px;
            y = py;
            vx = pvx;
            vy = pvy;
        }
        void move() {
            x += vx;
            y += vy;
            if (x < 0 || x >= FIELD_WIDTH) vx = -vx;
            if (y < 0 || y >= FIELD_HEIGHT) vy = -vy;
        }
        int getX() { return x; }
        int getY() { return y; }
};

int main() {
    srand(time(0));
    Player players[NUM_PLAYERS] = {Player(0, 0), Player(1, 0), Player(2, 0), Player(3, 0),
                                    Player(4, 0), Player(5, 0), Player(6, 0), Player(7, 0),
                                    Player(8, 0), Player(9, 0)};
    Ball ball(FIELD_WIDTH / 2, FIELD_HEIGHT / 2, rand() % 3 - 1, rand() % 3 - 1);
    while (true) {
        system("cls");
        for (int i = 0; i < FIELD_HEIGHT; i++) {
            for (int j = 0; j < FIELD_WIDTH; j++) {
                if (i == 0 || i == FIELD_HEIGHT - 1 || j == 0 || j == FIELD_WIDTH - 1)
                    cout << "#";
                else if (i == ball.getY() && j == ball.getX())
                    cout << "O";
                else {
                    bool player_here = false;
                    for (int k = 0; k < NUM_PLAYERS; k++) {
                        if (players[k].getX() == j && players[k].getY() == i) {
                            cout << "X";
                            player_here = true;
                            break;
                        }
                    }
                    if (!player_here) cout << " ";
                }
            }
            cout << endl;
        }
        for (int i = 0; i < NUM_PLAYERS; i++) {
            int dx = 0, dy = 0;
            if (rand() % 2) dx = rand() % 3 - 1;
            if (rand() % 2) dy = rand() % 3 - 1;
            players[i].move(dx, dy);
        }
        ball.move();
        if (ball.getY() == 0) {
            cout << "GOAL!" << endl;
            break;
        }
        if (ball.getY() == FIELD_HEIGHT - 1) {
            ball.move();
            ball.move();
            if (ball.getY() == FIELD_HEIGHT - 1) {
                cout << "GOALKEEPER SAVED!" << endl;
                break;
            }
        }
        if (rand() % 10 == 0) {
            int player_num = rand() % NUM_PLAYERS;
            int dx = (players[player_num].getX() < ball.getX()) ? -1 : 1;
            int dy = (players[player_num].getY() < ball.getY()) ? -1 : 1;
            players[player_num].move(dx, dy);
        }
    }
    return 0;
}