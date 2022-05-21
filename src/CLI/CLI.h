#pragma once

#include <iostream>
#include <map>
#include <string>

/**
 * Класс Flag описывает флаг, который передаёт нам пользователь
 */
class Flag {
public:
    std::string name;      /** Переменная хранит название флага */
    bool isRequiredFlag;   /** Переменная, которая говорит, обязательно ли должен присутствовать данный флаг при запуске программы */
    bool isContainsValue;  /** Переменная, которая говорит, должен ли флаг содержать значение */
    std::string value;     /** Переменная хранит значение флага, которое добавлено после флага */
    bool isPassed = false; /** Переменная, которая говорит, был ли введён данный флаг */

    Flag(std::string name, bool isRequiredFlag, bool isContainsValue) : name(std::move(name)), isRequiredFlag(isRequiredFlag), isContainsValue(isContainsValue){};
};

/**
 * Класс CLI описывает интерфейс командной строки
 * Он занимается чтением флагов и проверкой на валидность переданной информации
 * Все ошибки связанные с переданной информацией обрабатываются в этом классе
 */
class CLI {
    int argc;
    char **argv;
    std::map<std::string, Flag> flags;

public:
    enum ParseState { WRONG,
                      EXIT,
                      OK };

private:
    ParseState parseFlags();
    CLI::ParseState checkRequiredFlags();
    CLI::ParseState checkFiles();

public:
    explicit CLI(int argc, char *argv[]) : argc(argc), argv(argv){};
    CLI &flag(const std::string &name, bool requiredField = false, bool containsValue = false);
    ParseState parse();
};
