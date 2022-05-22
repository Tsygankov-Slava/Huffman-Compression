#include "CLI.h"

/**
 * The function adds flags to the flags map
 * @param name - flag name
 * @param isRequiredFlag - is the flag mandatory or not
 * @param isContainsValue - does the flag take a value or not
 * @return
 */
CLI &CLI::flag(const std::string &name, bool isRequiredFlag, bool isContainsValue) {
    flags.insert(std::make_pair(name, Flag(name, isRequiredFlag, isContainsValue)));
    return *this;
}

/**
 * A function that checks whether the user has called all the required flags or not
 * If the user has called all the required flags, the function will return OK, otherwise WRONG
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
 * The function processes all passed flags and checks them for validity
 * If everything is fine, the function will return OK
 * If the user calls informational flags (for example, --help), the function returns EXIT
 * If the user made any mistake while typing, the function will return WRONG
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
 * A function that checks that the user has not entered the same files in the --in and --out flags
 * If the user has entered the same files, the function will return WRONG, otherwise OK
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
 * A function that calls private methods of a class and processes their output
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
