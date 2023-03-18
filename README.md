# Индивидуальное домашние задание №1 по "Операционным системам" на тему "Использование каналов" (на оценку 8)
Печик Ирина Юрьевна, БПИ-217, Вариант-26

### Условие задачи:
Разработать программу, которая определяет количество целых
чисел в ASCII-строке. числа состоят из цифр от 0 до 9. Разделителями являются все другие символы
### Содержимое репозитория:
* [__funtionc.c__](https://github.com/IrinaPechik/Operating_Systems_HW-1/blob/main/function.c) - функция с решением задачи из условия
* [__tests__](https://github.com/IrinaPechik/Operating_Systems_HW-1/tree/main/input_files) - набор текстовых файлов, на которых проводилось тестирование программы
* __program [4, 5, 6, 7, 8]__ - программы на каждую из оценок. Для каждой такой программы приведены результаты выполнения тестов.

# Решение на 4 балла:
### Разработка программы, осуществляющей взаимодействие между тремя дочерними процессами с использованием неименованных каналов.
### 1. Приведено решение на С:
---
* __Главный файл__: [program4.c](https://github.com/IrinaPechik/Operating_Systems_HW-1/blob/main/program_4/program4.c)

* __Файл с функцией для нахождения количества чисел в ASCII-строке__: [function.c](https://github.com/IrinaPechik/Operating_Systems_HW-1/blob/main/function.c)  
---
### 2. Общая схема решения задачи:
* __Первый процесс__ читает текстовые данные из заданного файла и через __неименованный__ канал передает их __второму процессу__;
* __Второй процесс__ осуществляет обработку данных в соответствии с заданием и передает результат обработки через __неименованный__ канал __третьему процессу__;
* __Третий процесс__ осуществляет вывод данных в заданный файл.
### 3. Как запустить программу:
* __Компилируем__
     ```
     gcc program_4/program4.c -o program_4/program4.exe
     ```    
* __Запускаем__
     ```
     ./program_4/program4.exe ./input_files/input.txt program_4/output_files/output.txt
     ``` 
### 4. Для каждого из тестовых файлов представлен файл, полученный в результате работы программы:
* [output_files](https://github.com/IrinaPechik/Operating_Systems_HW-1/tree/main/program_4/output_files)

# Решение на 5 баллов:
### Разработка программы, в которой взаимодействие между тремя дочерними процессами осуществляется через именованные каналы.
### 1. Приведено решение на С:
---
* __Главный файл__: [program5.c](https://github.com/IrinaPechik/Operating_Systems_HW-1/blob/main/program_5/program5.c)

* __Файл с функцией для нахождения количества чисел в ASCII-строке__: [function.c](https://github.com/IrinaPechik/Operating_Systems_HW-1/blob/main/function.c)  
---
### 2. Общая схема решения задачи:
* __Первый процесс__ читает текстовые данные из заданного файла и через __именованный__ канал передает их __второму процессу__;
* __Второй процесс__ осуществляет обработку данных в соответствии с заданием и передает результат обработки через __именованный канал__ __третьему процессу__;
* __Третий процесс__ осуществляет вывод данных в заданный файл.
### 3. Как запустить программу:
* __Компилируем__
     ```
     gcc program_5/program5.c -o program_5/program5.exe
     ```    
* __Запускаем__
     ```
     ./program_5/program5.exe ./input_files/input.txt program_5/output_files/output.txt
     ``` 
### 4. Для каждого из тестовых файлов представлен файл, полученный в результате работы программы:
* [output_files](https://github.com/IrinaPechik/Operating_Systems_HW-1/tree/main/program_5/output_files)

# Решение на 6 баллов:
### Разработка программы, которая осуществляет взаимодействие между двумя дочерними процессами с использованием __неименованных__ каналов.
### 1. Приведено решение на С:
---
* __Главный файл__: [program6.c](https://github.com/IrinaPechik/Operating_Systems_HW-1/blob/main/program_6/program6.c)

* __Файл с функцией для нахождения количества чисел в ASCII-строке__: [function.c](https://github.com/IrinaPechik/Operating_Systems_HW-1/blob/main/function.c)  
---
### 2. Общая схема решения задачи:
* __Первый процесс__ читает текстовые данные из заданного файла и через __неименованный__ канал передает их __второму процессу__;
* __Второй процесс__ осуществляет обработку данных в соответствии с заданием и передает результат обработки через __неименованный канал__ обратно __первому процессу__;
* __Первый процесс__ осуществляет вывод данных в заданный файл.
### 3. Как запустить программу:
* __Компилируем__
     ```
     gcc program_6/program6.c -o program_6/program6.exe
     ```    
* __Запускаем__
     ```
     ./program_6/program6.exe ./input_files/input.txt program_6/output_files/output.txt
     ``` 
### 4. Для каждого из тестовых файлов представлен файл, полученный в результате работы программы:
* [output_files](https://github.com/IrinaPechik/Operating_Systems_HW-1/tree/main/program_6/output_files)

# Решение на 7 баллов:
### Разработка программы, которая осуществляет взаимодействие между двумя дочерними процессами с использованием __именованных__ каналов.
### 1. Приведено решение на С:
---
* __Главный файл__: [program7.c](https://github.com/IrinaPechik/Operating_Systems_HW-1/blob/main/program_7/program7.c)

* __Файл с функцией для нахождения количества чисел в ASCII-строке__: [function.c](https://github.com/IrinaPechik/Operating_Systems_HW-1/blob/main/function.c)  
---
### 2. Общая схема решения задачи:
* __Первый процесс__ читает текстовые данные из заданного файла и через __именованный__ канал передает их __второму процессу__;
* __Второй процесс__ осуществляет обработку данных в соответствии с заданием и передает результат обработки через __именованный канал__ обратно __первому процессу__;
* __Первый процесс__ осуществляет вывод данных в заданный файл.
### 3. Как запустить программу:
* __Компилируем__
     ```
     gcc program_7/program7.c -o program_7/program7.exe
     ```    
* __Запускаем__
     ```
     ./program_7/program7.exe ./input_files/input.txt program_7/output_files/output.txt
     ``` 
### 4. Для каждого из тестовых файлов представлен файл, полученный в результате работы программы:
* [output_files](https://github.com/IrinaPechik/Operating_Systems_HW-1/tree/main/program_7/output_files)

# Решение на 8 баллов:
### Разработка программы, которая осуществляет взаимодействие между двумя __независимыми (неродственными)__ процессами с использованием __именованных каналов__.
### 1. Приведено решение на С:
---
* __Главные файлы__: [program8_first.c](https://github.com/IrinaPechik/Operating_Systems_HW-1/blob/main/program_8/program8_first.c) [program8_second.c](https://github.com/IrinaPechik/Operating_Systems_HW-1/blob/main/program_8/program8_second.c)

* __Файл с функцией для нахождения количества чисел в ASCII-строке__: [function.c](https://github.com/IrinaPechik/Operating_Systems_HW-1/blob/main/function.c)  
---
### 2. Общая схема решения задачи:
* __Первый процесс__ читает текстовые данные из заданного файла и через __именованный__ канал передает их __второму процессу__;
* __Второй процесс__ осуществляет обработку данных в соответствии с заданием и передает результат обработки через __именованный канал__ обратно __первому процессу__;
* __Первый процесс__ осуществляет вывод данных в заданный файл.
### 3. Как запустить программу:
* __Компилируем__
     ```
     gcc program_8/program8_first.c -o program_8/program8_first.exe
     ``` 
     ```
     gcc program_8/program8_second.c -o program_8/program8_second.exe
     ```
* __Запускаем в разных терминалах в любом порядке__
     ```
     ./program_8/program8_first.exe ./input_files/input.txt program_8/output_files/output.txt
     ./program_8/program8_second.exe
     ``` 
     ![Untitled](https://user-images.githubusercontent.com/100044301/226130725-90b4f6e3-9bec-4b77-b1e5-fd4030bf86aa.png)

### 4. Для каждого из тестовых файлов представлен файл, полученный в результате работы программы:
* [output_files](https://github.com/IrinaPechik/Operating_Systems_HW-1/tree/main/program_8/output_tests)
