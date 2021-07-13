#include <stdlib.h>
#include <vector>
#include <array>
#include <deque>
#include <windows.h>
#include <GL/glut.h>
#include <iostream>
#include <string>
#define _USE_MATH_DEFINES
#include <math.h>
using namespace std;

array<float, 3> monster1 = { 10.5, 8.5, 1.0 }; //coordinates and direction of first monster
array<float, 3> monster2 = { 13.5, 1.5, 2.0 }; //coordinates and direction of second monster
array<float, 3> monster3 = { 4.5, 6.5, 3.0 }; //coordinates and direction of third monster
array<float, 3> monster4 = { 2.5, 13.5, 4.0 }; //coordinates and direction of fourth monster

vector<array<float,3>> pinkys = { monster1 };
vector<array<float, 3>> blinkys = { monster2 };
vector<array<float, 3>> inkys = { monster3 };
vector<array<float, 3>> clydes = { monster4 };

vector<vector<array<float,3>>> all_ghosts = { pinkys, blinkys, inkys, clydes };

int main() {
    for (auto& l : all_ghosts) {
        for (auto& g : l) {
            for (auto& f : g) {
                cout << f << " " << endl;
            }
        }
    }
    return 0;
}