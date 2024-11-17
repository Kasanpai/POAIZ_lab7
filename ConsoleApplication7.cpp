#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>

void generateAdjacencyMatrix(int** matrix, int N) {
    // Инициализация генератора случайных чисел
    srand(time(NULL));

    // Генерация матрицы смежности
    for (int i = 0; i < N; i++) {
        for (int j = i + 1; j < N; j++) {
            // С вероятностью 0.5 устанавливаем ребро между вершинами
            int edge = rand() % 2;
            matrix[i][j] = edge;
            matrix[j][i] = edge;  // Для неориентированного графа симметрично
        }
    }

    // Диагональные элементы должны быть равны 0 (нет петель)
    for (int i = 0; i < N; i++) {
        matrix[i][i] = 0;
    }
}

void printAdjacencyMatrix(int** matrix, int N) {
    printf("Матрица смежности:\n");
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            printf("%d ", matrix[i][j]);
        }
        printf("\n");
    }
}

void DFS(int** matrix, int N, int* NUM, int v) {
    // Помечаем вершину как посещенную
    NUM[v] = 1;
    // Выводим номер вершины
    printf("%d ", v+1);

    // Обходим все вершины, смежные с v
    for (int i = 0; i < N; i++) {
        // Если есть ребро и вершина не посещена
        if (matrix[v][i] == 1 && NUM[i] == 0) {
            DFS(matrix, N, NUM, i);
        }
    }
}

void DFS_All(int** matrix, int N) {
    // Массив для хранения состояния посещения вершин
    int* NUM = (int*)malloc(N * sizeof(int));

    // Инициализация массива NUM значением 0 (не посещена)
    for (int i = 0; i < N; i++) {
        NUM[i] = 0;
    }

    // Запуск DFS для каждой непосещенной вершины
    for (int i = 0; i < N; i++) {
        if (NUM[i] == 0) {  // Если вершина еще не была посещена
            DFS(matrix, N, NUM, i);
        }
    }

    // Освобождение памяти
    free(NUM);
}

int main() {

    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    int N;

    // Запросить у пользователя размер графа
    printf("Введите количество вершин в графе: ");
    scanf("%d", &N);

    // Выделить память для матрицы смежности
    int** adjacencyMatrix = (int**)malloc(N * sizeof(int*));
    for (int i = 0; i < N; i++) {
        adjacencyMatrix[i] = (int*)malloc(N * sizeof(int));
    }

    // Генерация матрицы смежности
    generateAdjacencyMatrix(adjacencyMatrix, N);

    // Вывод матрицы на экран
    printAdjacencyMatrix(adjacencyMatrix, N);

    // Запуск обхода в глубину для всех непосещенных вершин
    printf("\nРезультат обхода в глубину:\n");
    DFS_All(adjacencyMatrix, N);

    // Освобождение памяти
    for (int i = 0; i < N; i++) {
        free(adjacencyMatrix[i]);
    }
    free(adjacencyMatrix);

    return 0;
}