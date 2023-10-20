# 1C-Contest

## Requirements

+ openSSL

## Usage

`cd build` - создать папку для сборочных файлов 

`mkdir build && cmake .. && make && cd ..` - сборка бинарника в корневой папке

`./compare_dirs dir_name1 dir_name2 border_percent` - запуск программы

+ dir_name1(2) - пути до папок с файлами
+ border_percent - опциональный аргумент, обозначающий процент сходства, определяющий идентичность файлов, дефолтное значение: 70
