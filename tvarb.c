#include <limits.h>
#include <stdio.h>

static unsigned long long magnitude(long long value)
{
    if (value < 0) {
        return (unsigned long long)(-(value + 1)) + 1;
    }
    return (unsigned long long)value;
}

/*
 * Пояснения к заданиям:
 * 1. Число переводится в систему счисления с основанием 6:
 *    делим его на 6, записываем остатки и выводим их в обратном порядке.
 * 2. При m0 = 0 последовательность имеет вид mi = mi-1 + i.
 *    Увеличиваем i и mi, пока mi не станет больше N.
 * 3. Цифры сравниваются слева направо. Если каждая следующая цифра
 *    не меньше предыдущей, порядок возрастающий; если не больше — убывающий.
 * 4. Считаем номера членов с 1. Добавляем член к сумме, если его номер
 *    не делится на 3, а само значение делится на 3.
 * 5. Перебираем числа от 100 до 999 и оставляем те, у которых все цифры
 *    попарно различны.
 * 6. НОД находим алгоритмом Евклида; НОК вычисляем по формуле
 *    (a / НОД(a, b)) * b.
 * 7. Используем равенство n^3 = (n^2 - n + 1) + ... + (n^2 + n - 1):
 *    куб равен сумме n последовательных нечетных чисел.
 * 8. Перебираем первый натуральный корень, а второй проверяем как
 *    целый квадратный корень остатка. Чтобы не повторять пары,
 *    рассматриваем только случаи, когда первый корень не больше второго.
 */

/* Задание 1: перевод целого числа в систему счисления с основанием 6. */
static void task1(void)
{
    long long number;
    unsigned long long value;
    char digits[70];
    int length = 0;

    printf("Введите целое число: ");
    if (scanf("%lld", &number) != 1) {
        printf("Ошибка ввода.\n");
        return;
    }

    value = magnitude(number);
    if (value == 0) {
        digits[length++] = '0';
    } else {
        while (value > 0) {
            digits[length++] = (char)('0' + value % 6);
            value /= 6;
        }
    }

    printf("В шестиричной системе: ");
    if (number < 0) {
        putchar('-');
    }
    while (length > 0) {
        putchar(digits[--length]);
    }
    putchar('\n');
}

/* Задание 2: поиск первого элемента последовательности, превышающего N. */
static void task2(void)
{
    long long limit;
    long long value = 0;
    long long index = 0;

    printf("Введите N: ");
    if (scanf("%lld", &limit) != 1) {
        printf("Ошибка ввода.\n");
        return;
    }

    while (value <= limit) {
        ++index;
        if (value > LLONG_MAX - index) {
            printf("Результат слишком велик для типа long long.\n");
            return;
        }
        value += index;
    }

    printf("Первое подходящее число: %lld, его номер: %lld\n",
           value, index);
}

/* Задание 3: проверка, упорядочены ли цифры числа по возрастанию или убыванию. */
static void task3(void)
{
    long long number;
    unsigned long long value;
    int digits[32];
    int length = 0;
    int increasing = 1;
    int decreasing = 1;

    printf("Введите целое число: ");
    if (scanf("%lld", &number) != 1) {
        printf("Ошибка ввода.\n");
        return;
    }

    value = magnitude(number);
    do {
        digits[length++] = (int)(value % 10);
        value /= 10;
    } while (value > 0);

    for (int i = length - 1; i > 0; --i) {
        if (digits[i] > digits[i - 1]) {
            increasing = 0;
        }
        if (digits[i] < digits[i - 1]) {
            decreasing = 0;
        }
    }

    if (increasing && decreasing) {
        printf("Все цифры одинаковы: число упорядочено в обе стороны.\n");
    } else if (increasing) {
        printf("Цифры расположены по возрастанию.\n");
    } else if (decreasing) {
        printf("Цифры расположены по убыванию.\n");
    } else {
        printf("Цифры не упорядочены.\n");
    }
}

/* Задание 4: сумма подходящих членов последовательности до ввода нуля. */
static void task4(void)
{
    long long number;
    long long sum = 0;
    unsigned long long index = 0;

    printf("Вводите натуральные числа; для окончания введите 0.\n");
    for (;;) {
        if (scanf("%lld", &number) != 1) {
            printf("Ошибка ввода.\n");
            return;
        }
        if (number == 0) {


break;
        }
        if (number < 0) {
            printf("Члены последовательности должны быть натуральными.\n");
            return;
        }

        ++index;
        if (index % 3 != 0 && number % 3 == 0) {
            if (sum > LLONG_MAX - number) {
                printf("Сумма слишком велика для типа long long.\n");
                return;
            }
            sum += number;
        }
    }

    printf("Искомая сумма: %lld\n", sum);
}

/* Задание 5: вывод трехзначных чисел, в которых цифры не повторяются. */
static void task5(void)
{
    int printed = 0;
    int count = 0;

    printf("Трехзначные числа с уникальными цифрами:\n");
    for (int number = 100; number <= 999; ++number) {
        int hundreds = number / 100;
        int tens = number / 10 % 10;
        int units = number % 10;

        if (hundreds != tens && hundreds != units && tens != units) {
            printf("%d ", number);
            ++printed;
            ++count;
            if (printed == 12) {
                putchar('\n');
                printed = 0;
            }
        }
    }
    if (printed != 0) {
        putchar('\n');
    }
    printf("Всего: %d\n", count);
}

/* Задание 6: вычисление НОД алгоритмом Евклида и НОК по формуле. */
static void task6(void)
{
    long long first;
    long long second;
    long long a;
    long long b;

    printf("Введите два натуральных числа: ");
    if (scanf("%lld%lld", &first, &second) != 2 ||
        first <= 0 || second <= 0) {
        printf("Ошибка: нужны два положительных целых числа.\n");
        return;
    }

    a = first;
    b = second;
    while (b != 0) {
        long long remainder = a % b;
        a = b;
        b = remainder;
    }

    printf("НОД: %lld\n", a);
    if (first / a > LLONG_MAX / second) {
        printf("НОК слишком велик для типа long long.\n");
    } else {
        printf("НОК: %lld\n", (first / a) * second);
    }
}

/* Задание 7: вычисление куба как суммы последовательных нечетных чисел. */
static void task7(void)
{
    long long number;
    long long first_odd;
    long long sum = 0;

    printf("Введите натуральное число: ");
    if (scanf("%lld", &number) != 1 || number <= 0) {
        printf("Ошибка: число должно быть положительным.\n");
        return;
    }
    if (number > 2097151) {
        printf("Число слишком велико для вычисления в типе long long.\n");
        return;
    }

    first_odd = number * number - number + 1;
    for (long long i = 0; i < number; ++i) {
        sum += first_odd + 2 * i;
    }

    printf("%lld в третьей степени = %lld\n", number, sum);
}

static long long integer_sqrt(long long number)
{
    long long low = 1;
    long long high = number;
    long long result = 0;

    while (low <= high) {
        long long middle = low + (high - low) / 2;
        if (middle <= number / middle) {
            result = middle;
            low = middle + 1;
        } else {
            high = middle - 1;
        }
    }
    return result;
}

/* Задание 8: поиск всех представлений числа суммой квадратов натуральных чисел. */
static void task8(void)
{
    long long number;
    int found = 0;

    printf("Введите натуральное число: ");
    if (scanf("%lld", &number) != 1 || number <= 1) {
        printf("Ошибка: число должно быть больше 1.\n");
        return;
    }

    printf("Представления в виде суммы квадратов натуральных чисел:\n");
    for (long long first = 1; first <= (number - 1) / first; ++first) {
        long long remainder = number - first * first;
        long long second = integer_sqrt(remainder);

        if (second >= first && second * second == remainder) {
            printf("%lld = %lld^2 + %lld^2\n",
                   number, first, second);
            found = 1;
        }
    }

    if (!found) {
        printf("Представить число таким образом нельзя.\n");
    }
}

int main(void)
{
    int choice;

    do {
        printf("\nВыберите задание (1-8), 0 - выход:\n");
        printf("1. Перевод в систему счисления с основанием 6\n");
        printf("2. Первое число последовательности больше N\n");


printf("3. Проверка порядка цифр\n");
        printf("4. Сумма членов последовательности по условию\n");
        printf("5. Трехзначные числа с уникальными цифрами\n");
        printf("6. НОД и НОК алгоритмом Евклида\n");
        printf("7. Куб числа как сумма последовательных нечетных\n");
        printf("8. Представление числа суммой двух квадратов\n");
        printf("Ваш выбор: ");

        if (scanf("%d", &choice) != 1) {
            printf("Ошибка ввода.\n");
            return 1;
        }

        switch (choice) {
        case 0:
            break;
        case 1:
            task1();
            break;
        case 2:
            task2();
            break;
        case 3:
            task3();
            break;
        case 4:
            task4();
            break;
        case 5:
            task5();
            break;
        case 6:
            task6();
            break;
        case 7:
            task7();
            break;
        case 8:
            task8();
            break;
        default:
            printf("Нет задания с таким номером.\n");
            break;
        }
    } while (choice != 0);

    return 0;
}