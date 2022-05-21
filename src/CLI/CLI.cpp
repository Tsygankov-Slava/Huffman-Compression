#include "CLI.h"

/**
 * Функция добавляет флаги в мапу flags
 * @param name - имя флага
 * @param isRequiredFlag - переменная обозначающая обязательный ли флаг или нет
 * @param isContainsValue - переменная обозначающая принимает ли флаг значение или нет
 * @return
 */
CLI &CLI::flag(const std::string &name, bool isRequiredFlag, bool isContainsValue) {
    flags.insert(std::make_pair(name, Flag(name, isRequiredFlag, isContainsValue)));
    return *this;
}

/**
 * Функция проверяющая вызвал ли пользователь все обязательные флаги или нет
 * Если пользователь вызвал все обязательные флаги, функция вернёт OK, иначе WRONG
 * @return
 */
CLI::ParseState CLI::checkRequiredFlags() {
    for (const auto &[name, flag] : flags) {
        if (flag.isRequiredFlag && !flag.isPassed) {
            std::cout << "Недопустимый ввод. Флаг " << name << " обязательный при вызове данной программы. Посмотрите справочную информация (обратитесь с флагом --help).\n";
            return WRONG;
        }
    }
    return OK;
}

/**
 * Функция обрабатывает все переданные флаги и проверяет их на валидность
 * Если всё хорошо, функция вернёт OK
 * Если пользователь вызывает информационные флаги (например, --help), то функция вернёт EXIT
 * Если пользователь допустил какую-либо ошибку при вводе, то функция вернёт WRONG
 * @return
 */
CLI::ParseState CLI::parseFlags() {
    for (int i = 1; i < argc; ++i) {
        if (argv[i][0] == '-') {
            if (flags.count(argv[i])) {
                auto flag = &flags.at(std::string(argv[i]));
                if (flag->name == "--help") {
                    std::cout << "Описание флагов:\n"
                                 "\t--help        : Вывод справки.\n"
                                 "\t--description : Описание программы.\n"
                                 "\t--in          : Флаг через который нужно передавать файл, который надо сжать. [!обязательный флаг, требующий аргумент после себя]\n"
                                 "\t--out         : Флаг через который нужно передать предпочтительное название сжатого файла. [!обязательный флаг, требующий аргумент после себя]\n"
                                 "\n"
                                 "Пример:\n"
                                 ">>> ./Huffman_Compression --in input.txt --out output.txt\n"
                                 "В примере выше мы передаём в нашу программу для сжатия файл input.txt, а на выходе получаем сжатый файл output.txt\n"
                                 ">>> ./Huffman_Compression --in C:/Test/input.txt --out D:/Test/output.txt\n"
                                 "В примере выше мы передаём в нашу программу для сжатия файл input.txt, который находится на диске C:/ в директории Test/, а на выходе получаем сжатый файл output.txt, который будет находится на диске D:/ в директории Test/\n";
                    return EXIT;
                }
                if (flag->name == "--description") {
                    std::cout << "Программа \"Сжатие файлов алгоритмом Хаффмана\"\n"
                                 "Суть данной программы состоит в том, чтобы уменьшать размер переданного ей файла.\n"
                                 "На вход программа принимает файл какого-то размера, затем создаёт новый уменьшенный файл с именем (путём), указанными через флаг --out (читать справку, вызвав флаг --help()).\n";
                    return EXIT;
                }
                flag->isPassed = true;
                if (flag->isContainsValue) {
                    if (i == argc - 1) {
                        std::cout << "Недопустимый ввод. Флаг " << flag->name << " был передан без аргументов. Посмотрите справочную информация (обратитесь с флагом --help).\n";
                        return WRONG;
                    }
                    ++i;
                    if (argv[i][0] == '-') {
                        std::cout << "Недопустимый ввод. Вы пытаетесь в аргумент флага " << flag->name << " передать флаг " << argv[i] << ". Посмотрите справочную информация (обратитесь с флагом --help).\n";
                        return WRONG;
                    }
                    flag->value = argv[i];
                }
            } else {
                std::cout << "Недопустимый ввод. Неизвестный флаг " << argv[i] << ". Посмотрите справочную информация (обратитесь с флагом --help).\n";
                return WRONG;
            }
        } else {
            std::cout << "Недопустимый ввод. Неизвестный аргумент " << argv[i] << ". Посмотрите справочную информация (обратитесь с флагом --help).\n";
            return WRONG;
        }
    }
    return OK;
}

/**
 * Функция проверяющая, что пользователь не ввёл одинаковые файлы в флаги --in и --out
 * Если пользователь ввёл одинаковые файлы, то функция вернёт WRONG, иначе OK
 * @return
 */
CLI::ParseState CLI::checkFiles() {
    if (!flags.at("--in").value.empty() && flags.at("--in").value == flags.at("--out").value) {
        std::cout << "Недопустимый ввод. Файлы переданные c флагами --in и --out совпадают. Посмотрите справочную информация (обратитесь с флагом --help).\n";
        return WRONG;
    }
    return OK;
}

/**
 * Функция вызывающая приватные функции класса и обрабатывающая их вывод
 * @return
 */
CLI::ParseState CLI::parse() {
    ParseState parseFlagsState = parseFlags();
    if (parseFlagsState != OK) {
        return parseFlagsState;
    }
    ParseState checkRequiredFlagsState = checkRequiredFlags();
    if (checkRequiredFlagsState != OK) {
        return checkRequiredFlagsState;
    }
    ParseState checkFilesState = checkFiles();
    if (checkFilesState != OK) {
        return checkFilesState;
    }
    return OK;
}