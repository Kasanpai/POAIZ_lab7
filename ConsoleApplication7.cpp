#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>

// Структура для списка смежности
typedef struct Node {
    int vertex;
    struct Node* next;
} Node;

// Функция для сравнения двух элементов (используется в qsort)
int compare(const void* a, const void* b) {
    return (*(int*)a - *(int*)b);
}

void generateAdjacencyList(Node** adjList, int N) {
    srand(time(NULL));

    // Генерация списка смежности
    for (int i = 0; i < N; i++) {
        for (int j = i + 1; j < N; j++) {
            // С вероятностью 0.5 устанавливаем ребро между вершинами
            int edge = rand() % 2;
            if (edge == 1) {
                // Добавляем ребро (i, j) в список смежности вершины i
                Node* newNode = (Node*)malloc(sizeof(Node));
                newNode->vertex = j;
                newNode->next = adjList[i];
                adjList[i] = newNode;

                // Добавляем ребро (j, i) в список смежности вершины j (для неориентированного графа)
                newNode = (Node*)malloc(sizeof(Node));
                newNode->vertex = i;
                newNode->next = adjList[j];
                adjList[j] = newNode;
            }
        }
    }
}


void printAdjacencyList(Node** adjList, int N) {
    printf("Список смежности:\n");
    for (int i = 0; i < N; i++) {
        printf("%d: ", i + 1);
        Node* temp = adjList[i];
        while (temp != NULL) {
            printf("%d ", temp->vertex + 1);
            temp = temp->next;
        }
        printf("\n");
    }
}

// Итеративная функция обхода в глубину (DFS) с использованием стека
void DFS(Node** adjList, int N, int* NUM, int startVertex) {
    int* stack = (int*)malloc(N * sizeof(int));  // Стек для хранения вершин
    int top = -1;  // Индекс вершины в стеке
    stack[++top] = startVertex;  // Начальная вершина
    NUM[startVertex] = 1;  // Помечаем начальную вершину как посещенную

    while (top != -1) {  // Пока стек не пуст
        int v = stack[top--];  // Извлекаем вершину из стека
        printf("%d ", v + 1);  // Выводим вершину

        // Обрабатываем всех соседей вершины v
        Node* temp = adjList[v];
        while (temp != NULL) {
            if (NUM[temp->vertex] == 0) {  // Если сосед еще не посещен
                stack[++top] = temp->vertex;  // Добавляем соседа в стек
                NUM[temp->vertex] = 1;  // Помечаем соседа как посещенного
            }
            temp = temp->next;
        }
    }

    free(stack);  // Освобождение памяти для стека
}

void DFS_All(Node** adjList, int N) {
    // Массив для хранения состояния посещения вершин
    int* NUM = (int*)malloc(N * sizeof(int));

    // Инициализация массива NUM значением 0 (не посещена)
    for (int i = 0; i < N; i++) {
        NUM[i] = 0;
    }

    // Запуск DFS для каждой непосещенной вершины
    for (int i = 0; i < N; i++) {
        if (NUM[i] == 0) {  // Если вершина еще не была посещена
            DFS(adjList, N, NUM, i);
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

    // Выделить память для списка смежности
    Node** adjList = (Node**)malloc(N * sizeof(Node*));
    for (int i = 0; i < N; i++) {
        adjList[i] = NULL; // Инициализация всех списков как пустых
    }

    // Генерация списка смежности
    generateAdjacencyList(adjList, N);



    // Вывод списка смежности на экран
    printAdjacencyList(adjList, N);

    // Запуск обхода в глубину для всех непосещенных вершин
    printf("\nРезультат обхода в глубину:\n");
    DFS_All(adjList, N);

    // Освобождение памяти
    for (int i = 0; i < N; i++) {
        Node* temp = adjList[i];
        while (temp != NULL) {
            Node* next = temp->next;
            free(temp);
            temp = next;
        }
    }
    free(adjList);

    return 0;
}

