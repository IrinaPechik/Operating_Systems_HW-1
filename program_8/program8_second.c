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

    // Создаём запись в файловой системе (именованный канал)
    // с именем path1, path2 + режим открытия.
    mknod(path1, S_IFIFO | 0666, 0);
    mknod(path2, S_IFIFO | 0666, 0);

    char buf[m_size];
    int fd_f_s;
    int fd_s_t;
    int size;

    fd_f_s = open(path1, O_RDONLY);
    // Закрываем второй канал на запись.
    if (fd_f_s < 0) {
        printf("Oops. Error in closing FIFO for reading\n");
        exit(-1);
    }

    // Читаем данные из первого канла.
    size = read(fd_f_s, buf, m_size);
    if (size < 0) {
        printf("Oops. Error during reading from FIFO\n");
        exit(-1);
    }
    // Вызываем функцию. Результат будет в буфуре (buf).
    count_integers(buf);

    // Закрываем первый канал на чтение.
    if (close(fd_f_s) < 0) {
        printf("From child: error in closing FIFO for reading\n");
        exit(-1);
    }

    // Открываем первый канал на запись.
    if ((fd_s_t = open(path2, O_WRONLY)) < 0) {
        printf("Error in opening FIFO for writting\n");
        exit(-1);
    }

    // Передаём данные второму каналу.
    size = write(fd_s_t, buf, m_size);
    if (size != m_size) {
        printf("Can\'t write all string to FIFO\n");
        exit(-1);
    }

    // Закрываем второй поток на запись.
    if (close(fd_s_t) < 0) {
        printf("From parent: error in closing FIFO\n");
        exit(-1);
    }
    return 0;
}
