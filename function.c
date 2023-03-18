#include <stdio.h>
#include <string.h>

const int m_size = 5000;

void count_integers(char *str) {
    // Количество чисел в строке.
    int count = 0;
    // Является ли текущий символ цифрой.
    int is_number = 0;

    for (int i = 0; str[i] != '\0'; i++) {
        // Если текущий символ - цифра.
        if (str[i] >= '0' && str[i] <= '9') {
            is_number = 1;
        } else if (is_number == 1) {
            // Если число закончилось, прибавляем 1 к общему количеству чисел.
            count++;
            // Теперь текущий символ - не цифра.
            is_number = 0;
        }
    }
    // Проверка последнего символа.
    if (is_number == 1) {
        count++;
    }

    // Пустая строчка для вывода количества чисел.
    char output[m_size];
    // Записываем число в строку output.
    sprintf(output, "%d", count);

    memset(str, 0, m_size);
    // Копируем обратно во входную строчку - строчку вывода.
    strcpy(str, output);
}