#include <stdio.h>
#include <stdlib.h>

void print_line(const char *name, double x1, double y1, double x2, double y2)
{
    double a = y1 - y2;
    double b = x2 - x1;
    double c = x1 * y2 - x2 * y1;

    printf("%s: %+.2f*x %+.2f*y %+.2f = 0\n", name, a, b, c);
}

int main(void)
{
    int number;
    int d1, d2, d3, d4, d5, d6, d7, d8;
    int f1, f2, f3, f4, f5, f6, f7, f8;

    printf("1. Введите восьмизначное число: ");
    scanf("%d", &number);
    d1 = number / 10000000;
    d2 = number / 1000000 % 10;
    d3 = number / 100000 % 10;
    d4 = number / 10000 % 10;
    d5 = number / 1000 % 10;
    d6 = number / 100 % 10;
    d7 = number / 10 % 10;
    d8 = number % 10;

    printf("Для каждой цифры слева направо введите 0 (не брать) или 1 (брать): ");
    scanf("%d%d%d%d%d%d%d%d", &f1, &f2, &f3, &f4, &f5, &f6, &f7, &f8);
    printf("Сумма: %d\n\n",
           d1 * f1 + d2 * f2 + d3 * f3 + d4 * f4 +
           d5 * f5 + d6 * f6 + d7 * f7 + d8 * f8);

    printf("2. Введите шестизначное число: ");
    scanf("%d", &number);
    d1 = number / 100000;
    d2 = number / 10000 % 10;
    d3 = number / 1000 % 10;
    d4 = number / 100 % 10;
    d5 = number / 10 % 10;
    d6 = number % 10;
    printf("Результат: %d%d%d%d%d%d\n\n",
           d1 % 2, d2 % 2, d3 % 2, d4 % 2, d5 % 2, d6 % 2);

    {
        double x1, y1, x2, y2, x3, y3;

        printf("3. Введите координаты вершин треугольника "
               "(x1 y1 x2 y2 x3 y3): ");
        scanf("%lf%lf%lf%lf%lf%lf", &x1, &y1, &x2, &y2, &x3, &y3);
        print_line("Сторона AB", x1, y1, x2, y2);
        print_line("Сторона BC", x2, y2, x3, y3);
        print_line("Сторона CA", x3, y3, x1, y1);
        printf("\n");
    }

    {
        int a, b, c, not_a, not_b, not_b_and_c, left, result;

        printf("4. Таблица истинности функции "
               "(!A | (!B & C)) ~ A:\n");
        printf("A\tB\tC\t!A\t!B\t!B&C\t!A|(!B&C)\tРезультат\n");
        for (a = 0; a <= 1; a++) {
            for (b = 0; b <= 1; b++) {
                for (c = 0; c <= 1; c++) {
                    not_a = !a;
                    not_b = !b;
                    not_b_and_c = not_b && c;
                    left = not_a || not_b_and_c;
                    result = left == a;
                    printf("%d\t%d\t%d\t%d\t%d\t%d\t%d\t\t%d\n",
                           a, b, c, not_a, not_b, not_b_and_c, left, result);
                }
            }
        }
        printf("\n");
    }

    {
        int first, second;

        printf("5. Введите два трехзначных числа (abc и xyz): ");
        scanf("%d%d", &first, &second);
        printf("%d\n", first / 100 + second % 10);
        printf("%d\n", first / 10 % 10 + second / 100);
        printf("%d\n\n", first % 10 + second / 10 % 10);
    }

    printf("6. Введите четырехзначное число: ");
    scanf("%d", &number);
    printf("Сумма: %d\n\n", number / 100 + number % 100);

    {
        int x, y;
        long long difference, maximum;

        printf("7. Введите два целых числа: ");
        scanf("%d%d", &x, &y);
        difference = (long long)x - y;
        maximum = ((long long)x + y + llabs(difference)) / 2;
        printf("max(x, y) = %lld\n", maximum);
    }

    return 0;
}