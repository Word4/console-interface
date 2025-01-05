#pragma once
#ifndef INTERFACE_H
#define INTERFACE_H

#include <iostream>
#include <vector>
#include <string>
#include <functional>
#include <windows.h>

using namespace std;

class Button {
public:
    int id;
    string name;
    function<void()> func;

    void press();

    Button(const string& _name, int _id);
    Button(const string& _name, int _id, function<void()> func_);
};

class Object {
public:
    string name;
    int id;

    Object(const string& _name, int _id);
};

class Window {
public:
    string name;
    int cur_cursor_position = 0;
    vector<string> cursor_position;
    vector<Button*> buttons;
    vector<Object*> objects;
    int key;
    int max_word_length = 6;
    int line_size;

    int max_widget_size = 0;
    int max_title_size = 0;
    const int min_line_size = 4; // -()-
    const int min_arrow_size = 4; // " -> "
    int additional_symbol_count = 0;


    int red_theme = 04;
    int green_theme = 02;
    int blue_theme = 03;
    int purple_theme = 05;
    int yellow_theme = 06;
    int default_theme = 07;

    int main_text_theme = default_theme;
    int other_text_theme = 07;

    Window(const string& _name);

    void add_button(const string& name, function<void()> func);
    void show_window();
    void handle_click();
    void change_cur_cursor_position();

    void set_main_text_theme(int main_text_theme_);
    void set_other_text_theme(int other_text_theme_);
    void set_line_size(int size);
};

class Interface {
public:
    void add_window(string name);
    void add_button(string window_name, string button_name, function<void()> func);
    void show_window(string window_name);
    void add_exit_button(string window_name, string button_name = "exit");
    void set_main_text_theme(string name);
    void set_other_text_theme(string name);
    void set_main_text_theme_and_update_window(string name, string window_name);
    void set_other_text_theme_and_update_window(string name, string window_name);
    void help();

private:
    int max_widget_size = 0;
    int max_title_size = 0;
    const int min_line_size = 4; // -()-
    const int min_arrow_size = 4; // " -> "
    int additional_symbol_count = 0;
    int line_size = min_line_size;

    int red_theme = 04;
    int green_theme = 02;
    int blue_theme = 03;
    int purple_theme = 05;
    int yellow_theme = 06;
    int default_theme = 07;

    int main_text_theme = default_theme;
    int other_text_theme = 07;

    vector<Window*> windows;

    void position_logic();
};

#endif // INTERFACE_H
