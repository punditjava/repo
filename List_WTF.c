#include <stdio.h>
#include <stdlib.h>

/* Наш узел */
typedef struct _Node {
    double value;
    struct _Node *next;
    struct _Node *prev; 
} Node;
/* Структура Списка */
typedef struct _DblLinkedList {
    size_t size;
    Node *head;
    Node *tail;
} DblLinkedList;
/* Создаём экземпляр структуры DblLinkedList */
DblLinkedList* createDblLinkedList() {
    DblLinkedList *tmp = (DblLinkedList*) malloc(sizeof(DblLinkedList));
    tmp->size = 0;
    tmp->head = tmp->tail = NULL;
    return tmp;
}
/* Добавить элемент в конец списка */
void pushBack(DblLinkedList *list, double value) {
    Node *tmp = (Node*) malloc(sizeof(Node));
    if (tmp == NULL) {
        exit(3);
    }
    tmp->value = value;
    tmp->prev = list->tail;
    tmp->next = NULL;

    if (list->tail) {
        list->tail->next = tmp;
    }
    list->tail = tmp;

    if (list->head == NULL) {
        list->head = tmp;
    }
    list->size++;
}
/* Выводим наш Списочек*/
void printDblLinkedList(DblLinkedList *list, void (*fun)(double)) {
    Node *tmp = list->head;
    while (tmp) {
        fun(tmp->value);
        tmp = tmp->next;
    }
    printf("\n");
}
/* Вспомогательная функция для вывода*/
void printInt(double value) {
    printf("%f ", ((double) value));
}
/* Удаляем отрицательный элемент*/
void deleteElement(Node *lst)
{
    if(lst->prev != NULL)
    {
        lst->prev->next = lst->next;
    }
    if(lst->next != NULL)
    {
        lst->next->prev= lst->prev;
    }
}
/* Сканируем на отрицательные числа*/
void scanElements(DblLinkedList *list)
{
    Node *tmp = list->head;
    while(tmp)
    {
        if(tmp->value < 0)
            {
                deleteElement(tmp);
                list->size--;
            }
        tmp = tmp->next;
    }
}

void main() {

    DblLinkedList *list = createDblLinkedList(); /*Теперь list наш новый списочек */

    double scanner = 0.0;

    while(scanf("%le", &scanner) == 1) /*Сканируем до ctrl&D */
    {
        pushBack(list, scanner); 
    }
    
    printDblLinkedList(list,printInt);
    scanElements(list);
    puts("Убрал отрицательные элементы: ");
    printDblLinkedList(list,printInt);
}