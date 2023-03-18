#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "../function.c"
#include <sys/wait.h>

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
        // Здесь нам нужно обработать данные в соответствии с заданием (вызвать функцию)
        // и передать результат обработки через неименованный канал обратно первому процессу.  

        // Закрываем первый канал на запись.
        if (close(fd_f_s[1]) < 0) {
            printf("From child: error in closing pipe for writing\n");
            exit(-1);
        } 

        // Читаем данные из первого канла.
        size = read(fd_f_s[0], buf, m_size);
        if (size < 0) {
            printf("Oops. Error during reading from pipe\n");
            exit(-1);
        }
        // Вызываем функцию. Результат будет в буфуре (buf).
        count_integers(buf);

        // Закрываем первый канал на чтение.
        if (close(fd_f_s[0]) < 0) {
            printf("From child: error in closing pipe for reading\n");
            exit(-1);
        }

        // Передаём данные второму каналу.
        size = write(fd_s_t[1], buf, m_size);
        if (size != m_size) {
            printf("Can\'t write all string to pipe\n");
            exit(-1);
        }

        // Закрываем второй поток на запись.
        if (close(fd_s_t[1]) < 0) {
            printf("From child: error in closing pipe for writing\n");
            exit(-1);
        }
        exit(0);
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

    // Теперь первый процесс осуществляет вывод данных в заданный файл.
    // Ждем, пока завершится дочерний процесс.
    while (wait(NULL) > 0) {}

    // Закрываем второй канал на запись.
    if (close(fd_s_t[1]) < 0) {
        printf("From child: error in closing pipe for writing\n");
        exit(-1);
    }

    // Читаем данные второго канала.
    size = read(fd_s_t[0], buf, m_size);

    if (size < 0) {
        printf("Oops. Error during reading from pipe\n");
        exit(-1);
    }

    // Закрываем второй канал на чтение.
    if (close(fd_s_t[0]) < 0) {
        printf("Error in closing pipe for reading\n");
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
    return 0;
}
