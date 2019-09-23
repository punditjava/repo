#include <stdio.h>
#include <stdlib.h>

/* Наш узел */
typedef struct _Node {
    double value;
    struct _Node *next;
    struct _Node *prev; 
} Node;
/* Структура Списка */
typedef struct _linked_list {
    size_t size;
    Node *head;
    Node *tail;
} linked_list;
/* Создаём экземпляр структуры linked_list */
linked_list* createlinked_list() {
    linked_list *tmp = (linked_list*) malloc(sizeof(linked_list));
    tmp->size = 0;
    tmp->head = tmp->tail = NULL;
    return tmp;
}
/* Добавить элемент в конец списка */
int pushBack(linked_list *list, double value) {
    Node *tmp = (Node*) malloc(sizeof(Node));
    if (tmp == NULL) {
        puts("Fail in pushBack");
        return 0;
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
    return 1;
}
/* Выводим наш Списочек*/
void printlinked_list(linked_list *list, void (*fun)(double)) {
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
/* Удаляем элемент*/
int deleteElement(linked_list *list, Node *tmp)
{
    if(list == NULL || tmp == NULL)
	{   
        puts("Fail in deleteElement");  
        return 0;
    }
        
    if(tmp->prev != NULL)
    {       
        tmp->prev->next = tmp->next;
    }
    if(tmp->next != NULL)
    {
        tmp->next->prev= tmp->prev;
    }      
    if(!tmp->prev)
    {
        list->head = tmp->next;                
    }
    if(!tmp->next)
    {
        list->tail = tmp->prev;
    }
    free(tmp);

    return 1;
}

/* Сканируем на отрицательные числа*/
void scanElements(linked_list *list)
{
    Node *node = list->head;
    while(node)
    {
        Node *tmp = node;
        node = node->next;
        
        if(tmp->value < 0)
        {
            deleteElement(list,tmp);     
            list->size--;
        }
    }
}
/* Удаляем список*/
void DeleteList(linked_list **list)
{
    Node *tmp = (*list)->head;
    Node *next = NULL;
    while(tmp)
    {
        next = tmp->next;
        free(tmp);
        tmp = next;    
    }   
    free(*list);
    (*list) = NULL; 
}

void main() {

    linked_list *list = createlinked_list(); /*Теперь list наш новый списочек */

    double scanner = 0.0;

    while(scanf("%le", &scanner) == 1) /*Сканируем до ctrl&D */
    {
        pushBack(list, scanner); 
    }
    
    printlinked_list(list,printInt);
    scanElements(list);
    puts("Убрал отрицательные элементы: ");
    printlinked_list(list,printInt);

    DeleteList(&list);
}
