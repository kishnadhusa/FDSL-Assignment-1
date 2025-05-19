#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Record {
    int id;
    char name[50];
    struct Record* next;
};

struct Record* createRecord(int id, const char* name) {
    struct Record* newRecord = (struct Record*)malloc(sizeof(struct Record));
    newRecord->id = id;
    strcpy(newRecord->name, name);
    newRecord->next = NULL;
    return newRecord;
}

void insertRecord(struct Record** head, int id, const char* name) {
    struct Record* newRecord = createRecord(id, name);
    if (*head == NULL) {
        *head = newRecord;
    } else {
        struct Record* temp = *head;
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = newRecord;
    }
}

void deleteRecord(struct Record** head, int id) {
    struct Record* temp = *head;
    struct Record* prev = NULL;

    if (temp != NULL && temp->id == id) {
        *head = temp->next;
        free(temp);
        return;
    }

    while (temp != NULL && temp->id != id) {
        prev = temp;
        temp = temp->next;
    }

    if (temp == NULL) {
        printf("Record with ID %d not found.\n", id);
        return;
    }

    prev->next = temp->next;
    free(temp);
}

void modifyRecord(struct Record* head, int id, const char* newName) {
    struct Record* temp = head;
    while (temp != NULL) {
        if (temp->id == id) {
            strcpy(temp->name, newName);
            return;
        }
        temp = temp->next;
    }
    printf("Record with ID %d not found.\n", id);
}

void displayDatabase(struct Record* head) {
    struct Record* temp = head;
    printf("Database Records:\n");
    while (temp != NULL) {
        printf("ID: %d, Name: %s\n", temp->id, temp->name);
        temp = temp->next;
    }
}

int main() {
    struct Record* database = NULL;

    insertRecord(&database, 1, "Alice");
    insertRecord(&database, 2, "Bob");
    insertRecord(&database, 3, "Charlie");

    displayDatabase(database);

    modifyRecord(database, 2, "Robert");
    printf("\nAfter modification:\n");
    displayDatabase(database);

    deleteRecord(&database, 1);
    printf("\nAfter deletion:\n");
    displayDatabase(database);

    while (database != NULL) {
        deleteRecord(&database, database->id);
    }

    return 0;
}
