#include <iostream>
#include "interface.h"

using namespace std;

int main() {
    Interface inter;

    inter.add_window("Main Menu");
    inter.add_button("Main Menu", "Button 1", []() { cout << "Button 1 pressed!" << endl; });
    inter.add_button("Main Menu", "Button 2", []() { cout << "Button 2 pressed!" << endl; });
    inter.add_exit_button("Main Menu");

    inter.show_window("Main Menu");

    return 0;
}
