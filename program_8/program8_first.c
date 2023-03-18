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
    umask(0);
    if (argc != 3) {
        printf("Expected 2 arguments");
        return 0;
    }

    // Создаём запись в файловой системе (именованный канал)
    // с именем path1, path2 + режим открытия.
    mknod(path1, S_IFIFO | 0666, 0);
    mknod(path2, S_IFIFO | 0666, 0);
    char buf[m_size];
    int fd_f_s;
    int fd_s_t;
    int size;

    // Здесь наш первый процесс,
    // который должен считать данные из входного файла и отправить их во второй процесс.
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

    fd_f_s = open(path1, O_WRONLY);
    if (fd_f_s  < 0) {
        printf("Error in opening FIFO for writing\n");
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

    fd_s_t = open(path2, O_RDONLY);
    if (fd_s_t  < 0) {
        printf("Error in opening FIFO for reading\n");
        exit(-1);
    }

    // Читаем данные второго канала.
    size = read(fd_s_t, buf, m_size);

    if (size < 0) {
        printf("Oops. Error during reading from FIFO\n");
        exit(-1);
    }

    if (close(fd_s_t) < 0) {
        printf("Error in closing FIFO.\n");
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
    }

    // Удаляем имена из файловой системы.
    unlink(path1);
    unlink(path2);
    return 0;
}
