#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int id;
    char name[50];
    char position[20];
    int age;
} Player;

typedef struct Node {
    Player data;
    struct Node* next;
    struct Node* prev;
} Node;

typedef struct {
    Node* head;
    Node* tail;
    int size;
} FootballList;

FootballList* createList() {
    FootballList* list = (FootballList*)malloc(sizeof(FootballList));
    list->head = NULL;
    list->tail = NULL;
    list->size = 0;
    return list;
}

Node* createNode(int id, const char* name, const char* position, int age) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data.id = id;
    strcpy(newNode->data.name, name);
    strcpy(newNode->data.position, position);
    newNode->data.age = age;
    newNode->next = NULL;
    newNode->prev = NULL;
    return newNode;
}

void addPlayer(FootballList* list, int id, const char* name, const char* position, int age) {
    Node* newNode = createNode(id, name, position, age);
    
    if (list->head == NULL) {
        list->head = newNode;
        list->tail = newNode;
    } else {
        list->tail->next = newNode;
        newNode->prev = list->tail;
        list->tail = newNode;
    }
    list->size++;
    printf("Added player: %s (ID: %d)\n", name, id);
}

int deletePlayer(FootballList* list, int id) {
    if (list->head == NULL) {
        printf("List is empty. Cannot delete player with ID %d.\n", id);
        return 0;
    }
    
    Node* current = list->head;
    
    while (current != NULL && current->data.id != id) {
        current = current->next;
    }
    
    if (current == NULL) {
        printf("Player with ID %d not found.\n", id);
        return 0;
    }
    
    printf("Deleting player: %s (ID: %d)\n", current->data.name, current->data.id);
    
    if (list->head == list->tail) {
        list->head = NULL;
        list->tail = NULL;
    } else if (current == list->head) {
        list->head = current->next;
        list->head->prev = NULL;
    } else if (current == list->tail) {
        list->tail = current->prev;
        list->tail->next = NULL;
    } else {
        current->prev->next = current->next;
        current->next->prev = current->prev;
    }
    
    free(current);
    list->size--;
    return 1;
}

int deletePlayerByName(FootballList* list, const char* name) {
    if (list->head == NULL) {
        printf("List is empty. Cannot delete player %s.\n", name);
        return 0;
    }
    
    Node* current = list->head;
    
    while (current != NULL && strcmp(current->data.name, name) != 0) {
        current = current->next;
    }
    
    if (current == NULL) {
        printf("Player %s not found.\n", name);
        return 0;
    }
    
    printf("Deleting player: %s (ID: %d)\n", current->data.name, current->data.id);
    
    if (list->head == list->tail) {
        list->head = NULL;
        list->tail = NULL;
    } else if (current == list->head) {
        list->head = current->next;
        list->head->prev = NULL;
    } else if (current == list->tail) {
        list->tail = current->prev;
        list->tail->next = NULL;
    } else {
        current->prev->next = current->next;
        current->next->prev = current->prev;
    }
    
    free(current);
    list->size--;
    return 1;
}

void displayPlayers(FootballList* list) {
    if (list->head == NULL) {
        printf("No players in the list.\n");
        return;
    }
    
    printf("\n=== Football Team ===\n");
    Node* current = list->head;
    int count = 1;
    
    while (current != NULL) {
        printf("%d. ID: %d | Name: %s | Position: %s | Age: %d\n", 
               count++, current->data.id, current->data.name, 
               current->data.position, current->data.age);
        current = current->next;
    }
    printf("Total players: %d\n\n", list->size);
}

void displayPlayersReverse(FootballList* list) {
    if (list->tail == NULL) {
        printf("No players in the list.\n");
        return;
    }
    
    printf("\n=== Football Team Roster (Reverse) ===\n");
    Node* current = list->tail;
    int count = list->size;
    
    while (current != NULL) {
        printf("%d. ID: %d | Name: %s | Position: %s | Age: %d\n", 
               count--, current->data.id, current->data.name, 
               current->data.position, current->data.age);
        current = current->prev;
    }
    printf("Total players: %d\n\n", list->size);
}

void freeList(FootballList* list) {
    Node* current = list->head;
    Node* next;
    
    while (current != NULL) {
        next = current->next;
        free(current);
        current = next;
    }
    
    free(list);
}

int main() {
    FootballList* team = createList();
    
    printf("=== Football Team Management System ===\n\n");
    
    addPlayer(team, 10, "Lionel Messi", "RW/CAM/CF", 36);
    addPlayer(team, 7, "Cristiano Ronaldo", "ST/LW", 39);
    addPlayer(team, 14, "Desire Doue", "LW", 20);
    addPlayer(team, 4, "Lamine Yamal", "RW/CAM", 17);
    addPlayer(team, 7, "Florinel Coman", "LW", 26);
    addPlayer(team, 7, "Ciuntu Daniel", "ST", 22);
    
    displayPlayers(team);
    
    printf("Attempting to delete player with ID 7:\n");
    deletePlayer(team, 7);
    displayPlayers(team);
    
    printf("Attempting to delete player 'Ciuntu Daniel':\n");
    deletePlayerByName(team, "Ciuntu Daniel");
    displayPlayers(team);
    
    printf("Attempting to delete player with ID 99:\n");
    deletePlayer(team, 99);
    
    displayPlayersReverse(team);
    
    printf("Deleting remaining players:\n");
    deletePlayer(team, 10);
    deletePlayer(team, 4);
    deletePlayer(team, 14);
    deletePlayer(team, 7);
    
    displayPlayers(team);
    
    printf("Attempting to delete from empty list:\n");
    deletePlayer(team, 1);
    
    freeList(team);
    
    return 0;
}
