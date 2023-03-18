#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "../function.c"

int main(int argc, char *argv[]) {
    if (argc != 3) {
        printf("Expected 2 arguments");
        return 0;
    }

    char buf[m_size];

    // Неименованный канал для передачи из первого во второй процесс.
    int fd_f_s[2];
    // Неименованный канал для передачи из второго в третий процесс.
    int fd_s_t[2];

    // Создаём первый неименованный канал, который записывает в массив fd_f_s два дескриптора открытых файлов.
    if (pipe(fd_f_s) < 0) {
        printf("Can\'t open pipe\n");
        exit(-1);
    }
    // Создаём второй неименованный канал, который записвает в массив fd_s_t два дескриптора открытых файлов.
    if (pipe(fd_s_t) < 0) {
        printf("Can\'t open pipe\n");
        exit(-1);
    }

    int size;
    // Создаём новый дочерний процесс, дублируя текущий.
    // Новый процесс - дочерний. Процесс, который вызвал fork - родительский.
    int process = fork();
    
    if (process == -1) {
        printf("Fork failed\n");
        // Завершаем программу с кодом -1.
        exit(-1);
    } else if (process == 0) {
        // Находимся в процессе-потомке (второй процесс).
        // Разделим второй процесс на на второй и третий.
        int process2 = fork();

        if (process2 == -1) {
            printf("Fork failed\n");
            exit(-1);
        } else if (process2 == 0) {
            // Находимся в процессе-потомке второго процесса (третий процесс).
            // Третий процесс должен вывести результат выполнения второго процесса в файл output.
            
            // Закрываем второй канал на запись.
            if (close(fd_s_t[1]) < 0) {
                printf("From child: error in closing pipe for writing\n");
                exit(-1);
            }

            // Читаем из второго канала в буфер m_size символов.
            size = read(fd_s_t[0], buf, m_size);
            // Если произошла ошибка при чтении.
            if (size < 0) {
                printf("Oops. Error during reading from pipe\n");
                exit(-1);
            }

            // Закрываем второй канал на чтение.
            if (close(fd_s_t[0]) < 0) {
                printf("From child: error in closing pipe for reading\n");
                exit(-1);
            }

            // Открываем файл для записи. Если его нет - создаём.
            // Устанавливаем права доступа ('0666') для чтения и записи всем пользователям в системе.
            int output_file =  open(argv[2], O_WRONLY | O_CREAT, 0666);

            if (output_file < 0) {
                printf("Can\'t open file\n");
                exit(-1);
            }

            // Записываем строку 'buf' в файл
            size = write(output_file, buf, strlen(buf));
            if (size != strlen(buf)) {
                printf("Can\'t write all string\n");
                exit(-1);
            }

            // Закрываем файл.
            if (close(output_file) < 0) {
                printf("Can\'t close file\n");
                exit(-1);
            }
        } else {
            // Находимся в процессе-родителе (во втором процессе).

            // Данный второй процесс должен обработать данные (то бишь вызвать функцию) и передать
            // результат обработки через pipe третьему процессу.

            // Закрываем первый канал на запись.
            if (close(fd_f_s[1] < 0)) {
                printf("From child: error in closing pipe for writing\n");
                exit(-1);
            }
            // Читаем из первого канала в буфер m_size символов.
            size = read(fd_f_s[0], buf, m_size);

            if (size < 0) {
                printf("Oops. Error during reading from pipe\n");
                exit(-1);
            }

            // Обработка данных (вызов функции count_integers).
            count_integers(buf);

            // Закрываем первый канал на чтение.
            if (close(fd_f_s[0]) < 0) {
                printf("From child: error in closing pipe for reading\n");
                exit(-1);
            }

            // Записываем во второй канал.
            size = write(fd_s_t[1], buf, m_size);

            if (size != m_size) {
                printf("Can\'t write all string to pipe\n");
                exit(-1);
            }

            // Закрываем второй канал на запись.
            if (close(fd_s_t[1]) < 0) {
                printf("From child: error in closing pipe for writing\n");
                exit(-1);
            }
        }       
    } else {
        // Находимся в процессе-родителе (первый процесс).
        if (close(fd_f_s[0]) < 0) {
            printf("From child: error in closing pipe for reading\n");
            exit(-1);
        }
        
        // Открываем файл для чтения.
        int input_file = open(argv[1], O_RDONLY, 0666);

        if (input_file < 0) {
            printf("Can\'t open file\n");
            exit(-1);
        }

        // Читаем содержимое файла в буфер.
        size = read(input_file, buf, m_size);

        if (close(input_file) < 0) {
            printf("Can\'t close file\n");
        }

        // Запись в первый канал
        size = write(fd_f_s[1], buf, m_size);

        if (size != m_size) {
            printf("Can\'t write all string to pipe");
            exit(-1);
        }

        // Закрываем первый канал для записи.
        if (close(fd_f_s[1]) < 0) {
            printf("From child: error in closing pipe for writing\n");
            exit(-1);
        }
    }
    return 0;
}
