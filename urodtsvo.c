#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <float.h>

// --------------------- Задание 1 ---------------------

int *find_min(int @club225751608 (*begin), int *end)
{
    int *min_ptr = begin;
    for (int *p = begin + 1; p < end; ++p)
    {
        if (*p < *min_ptr)
            min_ptr = p;
    }
    return min_ptr;
}

int *find_max(int @club225751608 (*begin), int *end)
{
    int *max_ptr = begin;
    for (int *p = begin + 1; p < end; ++p)
    {
        if (*p > *max_ptr)
            max_ptr = p;
    }
    return max_ptr;
}

long long sum_between(const int *first, const int *second)
{
    const int *left = first < second ? first : second;
    const int *right = first < second ? second : first;

    long long s = 0;
    for (const int *p = left + 1; p < right; ++p)
        s += *p;
    return s;
}

size_t find_longest_increasing(int @club225751608 (*begin), int *end, int **sequence_begin)
{
    if (begin >= end)
    {
        if (sequence_begin != NULL)
            *sequence_begin = begin;
        return 0;
    }

    int *best_start = begin;
    size_t best_len = 1;
    int *cur_start = begin;
    size_t cur_len = 1;

    for (int *p = begin + 1; p < end; ++p)
    {
        if (*p > *(p - 1))
        {
            ++cur_len;
        }
        else
        {
            if (cur_len > best_len)
            {
                best_len = cur_len;
                best_start = cur_start;
            }
            cur_start = p;
            cur_len = 1;
        }
    }

    if (cur_len > best_len)
    {
        best_len = cur_len;
        best_start = cur_start;
    }

    if (sequence_begin != NULL)
        *sequence_begin = best_start;

    return best_len;
}

void reverse_range(int @club225751608 (*begin), int *end)
{
    if (begin >= end)
        return;

    int *left = begin;
    int *right = end - 1;

    while (left < right)
    {
        int temp = *left;
        *left = *right;
        *right = temp;
        ++left;
        --right;
    }
}

void print_array(const int @club225751608 (*begin), const int *end)
{
    const int *p = begin;
    while (p < end)
    {
        printf("%d", *p);
        ++p;
        if (p < end)
            printf(" ");
    }
    printf("\n");
}

void task1(void)
{
    int n;
    printf("Введите количество элементов массива (2..1000): ");
    scanf("%d", &n);

    if (n < 2 || n > 1000)
    {
        printf("Некорректный размер массива.\n");
        return;
    }

    int a[1000];
    for (int i = 0; i < n; ++i)
        scanf("%d", &a[i]);

    int *min_ptr = find_min(a, a + n);
    int *max_ptr = find_max(a, a + n);

    ptrdiff_t pos_min = min_ptr - a;
    ptrdiff_t pos_max = max_ptr - a;
    ptrdiff_t distance = pos_max - pos_min;
    if (distance < 0)
        distance = -distance;

    long long sum = sum_between(min_ptr, max_ptr);

    int *seq_begin = NULL;
    size_t len = find_longest_increasing(a, a + n, &seq_begin);

    printf("\nИсходный массив:\n");
    print_array(a, a + n);
    printf("Минимум: %d\n", *min_ptr);
    printf("Позиция минимума: %td\n", pos_min);
    printf("Максимум: %d\n", *max_ptr);
    printf("Позиция максимума: %td\n", pos_max);
    printf("Расстояние между минимумом и максимумом: %td\n", distance);
    printf("Сумма элементов между минимумом и максимумом: %lld\n", sum);

    printf("\nСамый длинный возрастающий участок:\n");
    print_array(seq_begin, seq_begin + len);
    printf("Длина: %zu\n", len);

    reverse_range(seq_begin, seq_begin + len);

    printf("\nМассив после разворота выбранного участка:\n");
    print_array(a, a + n);
}

// --------------------- Задание 2 ---------------------

void print_matrix(size_t rows, size_t cols, const int matrix[rows][cols])
{
    for (size_t i = 0; i < rows; ++i)
    {
        const int *row = *(matrix + i);
        const int *p = row;
        for (size_t j = 0; j < cols; ++j, ++p)
        {
            printf("%d", *p);
            if (j + 1 < cols)
                printf(" ");
        }
        printf("\n");
    }
}

const int *find_matrix_max(size_t rows, size_t cols,
                           const int matrix[rows][cols],
                           size_t *max_row,


size_t *max_col)
{
    const int *best = NULL;
    size_t best_row = 0;
    size_t best_col = 0;

    for (size_t i = 0; i < rows; ++i)
    {
        const int *row = *(matrix + i);
        const int *p = row;
        for (size_t j = 0; j < cols; ++j, ++p)
        {
            if (best == NULL || *p > *best)
            {
                best = p;
                best_row = i;
                best_col = j;
            }
        }
    }

    if (max_row != NULL)
        *max_row = best_row;
    if (max_col != NULL)
        *max_col = best_col;

    return best;
}

double matrix_average(size_t rows, size_t cols, const int matrix[rows][cols])
{
    long long sum = 0;
    for (size_t i = 0; i < rows; ++i)
    {
        const int *row = *(matrix + i);
        const int *p = row;
        for (size_t j = 0; j < cols; ++j, ++p)
            sum += *p;
    }
    return (double)sum / (double)(rows * cols);
}

size_t count_above_average(size_t rows, size_t cols,
                           const int matrix[rows][cols],
                           double average)
{
    size_t count = 0;
    for (size_t i = 0; i < rows; ++i)
    {
        const int *row = *(matrix + i);
        const int *p = row;
        for (size_t j = 0; j < cols; ++j, ++p)
        {
            if (*p > average)
                ++count;
        }
    }
    return count;
}

size_t hottest_row(size_t rows, size_t cols, const int matrix[rows][cols])
{
    size_t best_index = 0;
    double best_value = -DBL_MAX;

    for (size_t i = 0; i < rows; ++i)
    {
        const int *row = *(matrix + i);
        double sum = 0.0;
        for (size_t j = 0; j < cols; ++j)
            sum += *(row + j);

        double avg = sum / (double)cols;
        if (avg > best_value)
        {
            best_value = avg;
            best_index = i;
        }
    }

    return best_index;
}

double row_average(size_t cols, const int *row)
{
    long long sum = 0;
    const int *p = row;
    for (size_t i = 0; i < cols; ++i, ++p)
        sum += *p;
    return (double)sum / (double)cols;
}

void fill_row_with_average(size_t cols, int *row)
{
    int *p = row;
    int value = (int)row_average(cols, row);
    for (size_t i = 0; i < cols; ++i, ++p)
        *p = value;
}

int max_neighbor_difference(size_t rows, size_t cols, const int matrix[rows][cols])
{
    int max_diff = 0;
    for (size_t i = 0; i < rows; ++i)
    {
        const int *row = *(matrix + i);
        const int *p = row;
        for (size_t j = 0; j + 1 < cols; ++j, ++p)
        {
            int diff = abs(*(p + 1) - *p);
            if (diff > max_diff)
                max_diff = diff;
        }
    }
    return max_diff;
}

void task2(void)
{
    size_t rows, cols;
    printf("Введите количество строк и столбцов (R C): ");
    scanf("%zu %zu", &rows, &cols);

    if (rows < 2 || cols < 2 || rows > 50 || cols > 50)
    {
        printf("Некорректный размер матрицы.\n");
        return;
    }

    int matrix[rows][cols];
    for (size_t i = 0; i < rows; ++i)
    {
        for (size_t j = 0; j < cols; ++j)
            scanf("%d", &matrix[i][j]);
    }

    const int (*read_only_matrix)[cols] = (const int (*)[cols])matrix;

    printf("\nИсходная карта:\n");
    print_matrix(rows, cols, read_only_matrix);

    size_t max_row = 0, max_col = 0;
    const int *max_ptr = find_matrix_max(rows, cols, read_only_matrix, &max_row, &max_col);
    double avg = matrix_average(rows, cols, read_only_matrix);
    size_t above = count_above_average(rows, cols, read_only_matrix, avg);
    size_t hot = hottest_row(rows, cols, read_only_matrix);
    double hot_avg = row_average(cols, *(matrix + hot));

    printf("Максимальная температура: %d\n", *max_ptr);
    printf("Строка: %zu\n", max_row);
    printf("Столбец: %zu\n", max_col);
    printf("Средняя температура карты: %.2f\n", avg);
    printf("Количество значений выше среднего: %zu\n", above);
    printf("Строка с максимальным средним: %zu\n", hot);
    printf("Среднее выбранной строки: %.2f\n", hot_avg);

    fill_row_with_average(cols, *(matrix + hot));

    printf("\nКарта после замены


выбранной строки:\n");
    print_matrix(rows, cols, read_only_matrix);
    printf("Максимальная разница соседних температур: %d\n", max_neighbor_difference(rows, cols, read_only_matrix));
}

int main(void)
{
    int choice;
    printf("Выберите задание:\n");
    printf("1 - Анализ массива\n");
    printf("2 - Анализ температурной карты\n");
    printf("Ваш выбор: ");
    scanf("%d", &choice);

    if (choice == 1)
        task1();
    else if (choice == 2)
        task2();
    else
        printf("Неверный выбор.\n");

    return 0;
}