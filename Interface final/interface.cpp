#include "interface.h"
#include <conio.h>

void Button::press() {
    func();
}

Button::Button(const string& _name, int _id) : name(_name), id(_id) {}

Button::Button(const string& _name, int _id, function<void()> func_) : func(func_), name(_name), id(_id) {}

Object::Object(const string& _name, int _id) : name(_name), id(_id) {}

Window::Window(const string& _name) : name(_name) {
    if (_name.size() > max_word_length)
        max_word_length = _name.size();
}

void Window::set_main_text_theme(int main_text_theme_) {
    main_text_theme = main_text_theme_;
}

void Window::set_other_text_theme(int other_text_theme_) {
    other_text_theme = other_text_theme_;
}

void Window::set_line_size(int size) {
    line_size = size;
}

void Window::add_button(const string& name, function<void()> func) {
    Button* button_new = new Button(name, objects.size(), func);
    Object* object_new = new Object("button", buttons.size());
    buttons.push_back(button_new);
    objects.push_back(object_new);
    cursor_position.push_back("    ");

    int buffer_word_length = name.size();
    if (buffer_word_length > max_word_length)
        max_word_length = buffer_word_length;
}

void Window::show_window() {
    system("cls");
    change_cur_cursor_position();

    HANDLE h;
    h = GetStdHandle(STD_OUTPUT_HANDLE);

    SetConsoleTextAttribute(h, other_text_theme);

    int additional_symbol_count = line_size - name.size() - 4;
    for (int i = 0; i < additional_symbol_count / 2; i++)
        cout << '-';
    cout << "-(";

    SetConsoleTextAttribute(h, main_text_theme);
    cout << name;
    SetConsoleTextAttribute(h, other_text_theme);

    cout << ")-";
    for (int i = 0; i < additional_symbol_count / 2; i++)
        cout << '-';
    cout << endl;

    int button_id = 0;
    for (int i = 0; i < objects.size(); i++) {
        if (objects[i]->name == "button") {
            SetConsoleTextAttribute(h, main_text_theme);
            cout << cursor_position[i];
            SetConsoleTextAttribute(h, other_text_theme);
            cout << buttons[button_id]->name << endl;
            button_id++;
        }
    }

    for (int i = 0; i < line_size; i++)
        cout << '-';
    cout << endl;

    handle_click();
}

void Window::handle_click() {
    key = _getch();
    if (key == 224) {
        key = _getch();
        if (key == 80) { // Down arrow
            cur_cursor_position++;
            if (cur_cursor_position > cursor_position.size() - 1) cur_cursor_position = 0;
        }
        if (key == 72) { // Up arrow
            cur_cursor_position--;
            if (cur_cursor_position < 0) cur_cursor_position = cursor_position.size() - 1;
        }
        show_window();
    }
    if (key == 13) { // Enter key
        if (objects[cur_cursor_position]->name == "button") {
            buttons[objects[cur_cursor_position]->id]->press();
            system("pause");
        }
        show_window();
    }
}

void Window::change_cur_cursor_position() {
    for (int i = 0; i < cursor_position.size(); i++) {
        cursor_position[i] = "    ";
    }
    cursor_position[cur_cursor_position] = " -> ";
}

void Interface::add_window(string name) {
    int title_size = name.size();
    if (title_size > max_title_size)
        max_title_size = title_size;

    Window* window_new = new Window(name);
    windows.push_back(window_new);
}

void Interface::add_button(string window_name, string button_name, function<void()> func) {
    for (int i = 0; i < windows.size(); i++) {
        int button_size = button_name.size();
        if (button_size > max_widget_size)
            max_widget_size = button_size;

        if (windows[i]->name == window_name)
            windows[i]->add_button(button_name, func);
    }
}

void Interface::show_window(string window_name) {
    for (int i = 0; i < windows.size(); i++) {
        if (windows[i]->name == window_name) {
            position_logic();
            windows[i]->set_line_size(line_size);
            windows[i]->set_main_text_theme(main_text_theme);
            windows[i]->set_other_text_theme(other_text_theme);
            windows[i]->show_window();
        }
    }
}

void Interface::add_exit_button(string window_name, string button_name) {
    add_button(window_name, button_name, []() { exit(0); });
}

void Interface::set_main_text_theme(string name) {
    if (name == "default")
        main_text_theme = default_theme;
    else if (name == "red")
        main_text_theme = red_theme;
    else if (name == "green")
        main_text_theme = green_theme;
    else if (name == "blue")
        main_text_theme = blue_theme;
    else if (name == "purple")
        main_text_theme = purple_theme;
    else if (name == "yellow")
        main_text_theme = yellow_theme;

    for (int i = 0; i < windows.size(); i++)
        windows[i]->set_main_text_theme(main_text_theme);
}

void Interface::set_other_text_theme(string name) {
    if (name == "default")
        other_text_theme = default_theme;
    else if (name == "red")
        other_text_theme = red_theme;
    else if (name == "green")
        other_text_theme = green_theme;
    else if (name == "blue")
        other_text_theme = blue_theme;
    else if (name == "purple")
        other_text_theme = purple_theme;
    else if (name == "yellow")
        other_text_theme = yellow_theme;

    for (int i = 0; i < windows.size(); i++)
        windows[i]->set_other_text_theme(main_text_theme);
}

void Interface::set_main_text_theme_and_update_window(string name, string window_name) {
    set_main_text_theme(name);
    show_window(window_name);
}

void Interface::set_other_text_theme_and_update_window(string name, string window_name) {
    set_other_text_theme(name);
    show_window(window_name);
}

void Interface::help() {
    system("cls");
    cout << "add_window(\"название окна\") - создает окно, в котором будут создаваться кнопки и тд\n" << endl;
    cout << "add_button(\"название окна в котором будет кнопка\", \"название кнопки\",функция например []() {exit(0); }); \nПри нажатии ENTER пока стрелка напротив кнопки, функция будет вызвана\n" << endl;
    cout << "add_exit_button(\"название окна в котором будет кнопка\",\"имя кнопки (по дефолту это exit)\");\nЭта кнопка завершает программу\n" << endl;
    cout << "inter.show_window(\"название окна\"); выводит окно\n" << endl;
    cout << "set_main_text_theme(\"название цвета\")\nЗадает цвет части текста\n" << endl;
    cout << "set_other_text_theme(\"название цвета\")\nЗадает цвет части текста" << endl;
    cout << "Цвета: red, green, yellow, blue, purple\ndefault - белый\n" << endl;
    cout << "set_other_text_theme_and_update_window(\"цвет\",\"название окна\") - меняет цвет и обновляет окно" << endl;
    cout << "set_main_text_theme_and_update_window(\"цвет\",\"название окна\")\n" << endl;
}

void Interface::position_logic() {
    additional_symbol_count = (max_widget_size + min_arrow_size) - (max_title_size + min_line_size);
    if (additional_symbol_count % 2 != 0)
        additional_symbol_count++;
    line_size = max_title_size + min_line_size + additional_symbol_count;
}
