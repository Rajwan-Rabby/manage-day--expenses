#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Structure to represent a transaction
typedef struct {
    int transaction_id;
    char description[50];
    float amount;
    char category[20];
    char date[10];
} Transaction;

// Structure to represent a linked list node
typedef struct Node {
    Transaction transaction;
    struct Node* next;
} Node;

// Function to add
void addTransaction(Node** head, int transaction_id, char* description, float amount, char* category, char* date) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->transaction.transaction_id = transaction_id;
    strcpy(newNode->transaction.description, description);
    newNode->transaction.amount = amount;
    strcpy(newNode->transaction.category, category);
    strcpy(newNode->transaction.date, date);
    newNode->next = *head;
    *head = newNode;
}

void deleteTransaction(Node** head, int transaction_id) {
    Node* temp = *head;
    Node* prev = NULL;
    while (temp != NULL && temp->transaction.transaction_id != transaction_id) {
        prev = temp;
        temp = temp->next;
    }
    if (temp != NULL) {
        if (prev == NULL) {
            *head = temp->next;
        } else {
            prev->next = temp->next;
        }
        free(temp);
    }
}

// Function to update a transaction
void updateTransaction(Node* head, int transaction_id, char* description, float amount, char* category, char* date) {
    while (head != NULL) {
        if (head->transaction.transaction_id == transaction_id) {
            strcpy(head->transaction.description, description);
            head->transaction.amount = amount;
            strcpy(head->transaction.category, category);
            strcpy(head->transaction.date, date);
            break;
        }
        head = head->next;
    }
}

// Function to categorize expenses
void categorizeExpenses(Node* head) {
    printf("Categorized Expenses:\n");
    while (head != NULL) {
        printf("Category: %s, Amount: %.2f\n", head->transaction.category, head->transaction.amount);
        head = head->next;
    }
}

// Function to generate monthly spending report
void generateMonthlyReport(Node* head) {
    printf("Monthly Spending Report:\n");
    float total_amount = 0.0;
    while (head != NULL) {
        total_amount += head->transaction.amount;
        head = head->next;
    }
    printf("Total Amount Spent: %.2f\n", total_amount);
}

int main() {
    Node* head = NULL;
    int choice;
    int transaction_id;
    char description[50];
    float amount;
    char category[20];
    char date[10];

    while (1) {
        printf("1. Add Transaction\n");
        printf("2. Delete Transaction\n");
        printf("3. Update Transaction\n");
        printf("4. Categorize Expenses\n");
        printf("5. Generate Monthly Report\n");
        printf("6. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter transaction ID: ");
                scanf("%d", &transaction_id);
                printf("Enter description: ");
                scanf("%s", description);
                printf("Enter amount: ");
                scanf("%f", &amount);
                printf("Enter category: ");
                scanf("%s", category);
                printf("Enter date (DD/MM/YYYY): ");
                scanf("%s", date);
                addTransaction(&head, transaction_id, description, amount, category, date);
                break;
            case 2:
                printf("Enter transaction ID to delete: ");
                scanf("%d", &transaction_id);
                deleteTransaction(&head, transaction_id);
                break;
            case 3:
                printf("Enter transaction ID to update: ");
                scanf("%d", &transaction_id);
                printf("Enter new description: ");
                scanf("%s", description);
                printf("Enter new amount: ");
                scanf("%f", &amount);
                printf("Enter new category: ");
                scanf("%s", category);
                printf("Enter new date (DD/MM/YYYY): ");
                scanf("%s", date);
                updateTransaction(head, transaction_id, description, amount, category, date);
                break;
            case 4:
                categorizeExpenses(head);
                break;
            case 5:
                generateMonthlyReport(head);
                break;
            case 6:
                return 0;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    }

    return 0;
}