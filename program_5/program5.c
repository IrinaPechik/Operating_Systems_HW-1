#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>
#include "../function.c"

const char *path1 = "pipe1.fifo";
const char *path2 = "pipe2.fifo";

int main(int argc, char *argv[]) {
    if (argc != 3) {
        printf("Expected 2 arguments");
        return 0;
    }

    // Создаём запись в файловой системе (именованный канал)
    // с именем path1, path2 + режим открытия.
    mknod(path1, S_IFIFO | 0666, 0);
    mknod(path2, S_IFIFO | 0666, 0);

    char buf[m_size];
    int fd_s_t = 0;
    int fd_f_s;
    int size;

    // Создаём первый и второй процесс.
    int process = fork();
    
    if (process == -1) {
        printf("Fork failed\n");
        // Завершаем программу с кодом -1.
        exit(-1);
    } else if (process == 0) {
        // Находимся во втором процессе.
        // Разделим второй процесс на на второй и третий.
        int process2 = fork();

        if (process2 == -1) {
            printf("Fork failed\n");
            exit(-1);
        } else if (process2 == 0) {
            // Находимся в третьем процессе.
            // Третий процесс должен вывести результат выполнения второго процесса в файл output.
            
            fd_s_t = open(path2, O_RDONLY);
            // Закрываем второй канал на запись.
            if (fd_s_t < 0) {
                printf("Oops. Error in closing FIFO for reading\n");
                exit(-1);
            }

            // Читаем из второго канала в буфер m_size символов.
            size = read(fd_s_t, buf, m_size);
            // Если произошла ошибка при чтении.
            if (size < 0) {
                printf("Oops. Error during reading from FIFO\n");
                exit(-1);
            }

            // Закрываем второй канал на чтение.
            if (close(fd_s_t) < 0) {
                printf("Oops. Error in closing FIFO\n");
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

            // Удаляем имена из файловой системы.
            unlink(path1);
            unlink(path2);
        } else {
            // Находимся во втором процессе.
            // Данный второй процесс должен обработать данные (то бишь вызвать функцию) и передать
            // результат обработки третьему процессу.

            // Открываем первый канал на чтение.
            if ((fd_f_s = open(path1, O_RDONLY)) < 0) {
                printf("Error in opening FIFO for reading\n");
                exit(-1);
            }
            // Читаем из первого канала в буфер m_size символов.
            size = read(fd_f_s, buf, m_size);

            if (size < 0) {
                printf("Oops. Error during reading from FIFO\n");
                exit(-1);
            }

            // Обработка данных (вызов функции count_integers).
            count_integers(buf);

            // Закрываем первый канал на чтение.
            if (close(fd_f_s) < 0) {
                printf("From child: error in closing FIFO\n");
                exit(-1);
            }

            if ((fd_s_t = open(path2, O_WRONLY)) < 0) {
                printf("Can\'t open FIFO for writing\n");
                exit(-1);
            }

            // Записываем во второй канал.
            size = write(fd_s_t, buf, m_size);

            if (size != m_size) {
                printf("Can\'t write all string to FIFO\n");
                exit(-1);
            }

            // Закрываем второй канал на запись.
            if (close(fd_s_t) < 0) {
                printf("From parent: error in closing FIFO \n");
                exit(-1);
            }
        }       
    } else {
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

        if ((fd_f_s = open(path1, O_WRONLY)) < 0) {
            printf("Can\'t open FIFO for writting\n");
            exit(-1);
        }


        // Запись в первый канал
        size = write(fd_f_s, buf, m_size);

        if (size != m_size) {
            printf("Can\'t write all string to FIFO");
            exit(-1);
        }

        // Закрываем первый канал для записи.
        if (close(fd_f_s) < 0) {
            printf("From parent: error in closing FIFO for writing\n");
            exit(-1);
        }
    }
    return 0;
}
