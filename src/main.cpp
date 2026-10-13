#include <iostream>
#include <limits>
#include <new>

#include "lab01/str_ops.hpp"

int main() {
    constexpr int kBufferSize = 1025;
    char buffer[kBufferSize]{};
    char* text = nullptr;
    bool running = true;
    int exit_code{};

    std::cout << "Лабораторная работа 1. Вариант 10\n";

    try {
        while (running) {
            std::cout
                << "\n1. Ввести строку\n"
                << "2. Напечатать строку\n"
                << "3. Показать длину\n"
                << "4. Создать копию и напечатать\n"
                << "5. Подсчитать слова и найти подстроку\n"
                << "0. Выход\n"
                << "Ваш выбор: ";

            int choice{};
            if (!(std::cin >> choice)) {
                if (std::cin.eof() || std::cin.bad()) {
                    break;
                }

                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cout << "Введите целое число от 0 до 5.\n";
                continue;
            }

            bool extra_symbols = false;
            char symbol{};
            while (std::cin.get(symbol) && symbol != '\n') {
                if (symbol != ' ' && symbol != '\t' && symbol != '\r') {
                    extra_symbols = true;
                }
            }

            if (std::cin.bad()) {
                break;
            }

            if (extra_symbols) {
                std::cout << "Введите целое число без дополнительных символов\n";
                continue;
            }

            if (choice >= 2 && choice <= 5 && text == nullptr) {
                std::cout << "Сначала введите строку\n";
                continue;
            }

            switch (choice) {
                case 0: {
                    running = false;
                    break;
                }
                case 1: {
                    std::cout << "Введите строку (до " << kBufferSize - 1 << " байт): ";

                    if (!std::cin.getline(buffer, kBufferSize)) {
                        if (std::cin.eof() || std::cin.bad()) {
                            running = false;
                        } else {
                            std::cin.clear();
                            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                            std::cout << "Строка слишком длинная. Максимум: " << kBufferSize - 1 << " байта\n";
                        }
                        break;
                    }

                    char* new_text = str_alloc(buffer);
                    str_delete(text);
                    text = new_text;
                    std::cout << "Строка сохранена\n";
                    break;
                }
                case 2: {
                    std::cout << "Строка: ";
                    str_print(text);
                    std::cout << '\n';
                    break;
                }
                case 3: {
                    std::cout << "Длина: " << str_len(text) << '\n';
                    break;
                }
                case 4: {
                    char* copy = str_alloc(text);
                    std::cout << "Копия: ";
                    str_print(copy);
                    std::cout << '\n';
                    str_delete(copy);
                    break;
                }
                case 5: {
                    std::cout << "Количество слов: " << str_count_words(text) << '\n';
                    std::cout << "Введите подстроку: ";

                    if (!std::cin.getline(buffer, kBufferSize)) {
                        if (std::cin.eof() || std::cin.bad()) {
                            running = false;
                        } else {
                            std::cin.clear();
                            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                            std::cout << "Подстрока слишком длинная. Максимум: " << kBufferSize - 1 << " байта\n";
                        }
                        break;
                    }

                    int position{};
                    if (str_find_substr(text, buffer, position)) {
                        std::cout << "Подстрока найдена. Позиция: " << position << '\n';
                    } else {
                        std::cout << "Подстрока не найдена\n";
                    }
                    break;
                }
                default: {
                    std::cout << "Нет такого пункта меню. Выберите число от 0 до 5\n";
                    break;
                }
            }
        }
    } catch (const std::bad_alloc&) {
        std::cerr << "Недостаточно памяти\n";
        exit_code = 1;
    }

    str_delete(text);
    std::cout << "Завершение программы\n";
    return exit_code;
}
