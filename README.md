# Huffman-Compression

Huffman-Compression - это программа, которая умеет сжимать и разжимать файлы, используя алгоритм сжатия Хаффмана. Основа взаимодействия с программой реализована с помощью [`Command Line Interface`](https://github.com/Tsygankov-Slava/cli)

# Оглавление

- [Технические требования](#технические-требования)
- [Установка](#установка)
- [Описание](#описание)
- [Пример использования](#пример-использования)
- [Лицензия](#лицензия)


# Технические требования

> - Версия CMake: 3.20
> - Версия Clang-Tidy: 13.0.0
> - Стандарт C++: 17

[🔝Оглавление](#оглавление)


# Установка

1. Зайти в Releases и выбрать подходящую версию Huffman-Compression (Рекомендовано использовать последнюю версию проекта)
2. После следует найти исполняемый файл `Huffman-Compression` и скачать его

[🔝Оглавление](#оглавление)


# Описание
Сначала откроем консоль и перейдём к исполняемому файлу. 
Затем у нас есть два варианта использования программы, сжать файл и наоборот разжать файл. 

1. Если мы хотим `сжать файл`, то надо использовать команду `encode` и передать в неё флаги:

| Название флага  |                       | Описание                                                                                                     |
|-----------------|-----------------------|--------------------------------------------------------------------------------------------------------------|
| `-i`, `--input` | `Обязательный флаг`   | Имя файла, подлежащий кодированию                                                                            |
| `-o`, `--output`| `Необязательный флаг` | Имя файла, в котором будет лежать закодированный текст. (По умолчанию \ `исходное имя` + `.enc`)             |
| `-s`, `--steps` | `Необязательный флаг` | Выведет информацию о кодирование (этапы выполнения)                                                          |

2. Если мы хотим `разжать файл`, то надо использовать команду `decode`:

| Название флага  |                       | Описание                                                                                                     |
|-----------------|-----------------------|--------------------------------------------------------------------------------------------------------------|
| `-i`, `--input` | `Обязательный флаг`   | Имя файла, подлежащий декодированию                                                                          |
| `-o`, `--output`| `Необязательный флаг` | Имя файла, в котором будет лежать раскодированный текст. (По умолчанию \ `исходное имя` + `.dec`)            |
| `-s`, `--steps` | `Необязательный флаг` | Выведет информацию о раскодирование (этапы выполнения)                                                       |

> Если хотите получить информацию по всем командам и флагам используйте команду `help`

❗ Для полного понимая того, как использовать Huffman-Compression, см. раздел ["Пример использования"](#пример-использования)

[🔝Оглавление](#оглавление)


# Пример использования
```

//Выведет справочную информацию
$ ./Huffman_Compression help
CLI version 0.1.0

Usage:
   command [flags] [arguments]

Commands:
  decode                           This is the command that starts decoding the encoded 
                                   file using the Huffman algorithm. 
    Flags:
      -i, --input=VALUE[REQUIRED]  Input file to be decoded
      -o, --output=VALUE           Output file to be decoded.  
                                   By default the compressed file will be written to 
                                   the input file with the prefix ".dec" at the end. 
      -s, --steps                  Print the information about decode (the execution steps) 
  encode                           This is the command that starts encoding the file with 
                                   the Huffman algorithm. 
    Flags:
      -i, --input=VALUE[REQUIRED]  Input file to be encoded.
      -o, --output=VALUE           Output file to be encoded.  
                                   By default the compressed file will be written to 
                                   the input file with the prefix ".enc" at the end. 
      -s, --steps                  Print the information about encode (the execution steps) 
  help                             Show help information.
  
  
// Закодирует файл ../1.txt, запишет новый, сжатый файл под именем 2.txt и будеи во время выполнения выводить информацию о кодирование 
$ ./Huffman_Compression encode -i ../1.txt -o ../2.txt -s
PROCESS...
Count of the symbols:
' -> 1
= -> 2
* -> 3
...
t -> 242060
e -> 342245
  -> 600320
-------

Code of the symbols:
 -> 101010
  -> 010010
! -> 111110
...
x -> 110001
y -> 100101
z -> 111100
-------

File encoding is completed! 


// Раскодирует файл ../2.txt, запишет новый, разжатый файл в файл decod и будет во время выполнения выводить информацию о раскодирование
$ ./Huffman_Compression decode -i ../2.txt -o ../decod -s
PROCESS...
Code of the symbols:
 -> 101010
  -> 010010
! -> 111110
...
x -> 110001
y -> 100101
z -> 111100

PROCESS...
File decoding is completed!
```

[🔝Оглавление](#оглавление)

# Лицензия

Huffman-Compression распространяется по [лицензии MIT](https://github.com/Tsygankov-Slava/Huffman-Compression/blob/main/LICENSE) от имени Tsygankov Viacheslav.

[🔝Оглавление](#оглавление)
