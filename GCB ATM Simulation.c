// ATM Banking System
// Created by User on 3/6/2024.

#include <stdio.h>
#include <stdlib.h>

// Define the maximum size of a name
#define N 30

// Structure to represent an ATM account
typedef struct ATM {
    char name[N];
    int pin;
    float amount;
} ATM;

// Define a linked list node
struct node {
    struct node *prev;
    ATM atm;
    struct node *next;
};

// Global variables
int choice, ans;
float x;
struct node *head = NULL, *new_node, *temp,*ptr;

// Function to search for an ATM account based on PIN
struct node *search(int pin, struct node *y) {
    temp = y;
    while (temp != NULL && temp->atm.pin != pin) {
        temp = temp->next;
    }
    return temp;
}


// Function to create a new ATM account
struct node *create_account(struct node *y) {
    do {
        new_node = (struct node *)malloc(sizeof(struct node));

        printf("Enter your Full name: ");
        scanf("%s", new_node->atm.name);

        printf("Enter a four-digit pin number: ");
        scanf("%d", &new_node->atm.pin);

        printf("Enter initial deposit amount: ");
        scanf("%f", &new_node->atm.amount);

        new_node->prev = NULL;
        new_node->next = NULL;

        if (y == NULL) {
            y = temp = new_node;
        } else {
            temp->next = new_node;
            new_node->prev = temp;
            temp = new_node;
        }

        printf("Create another bank account (1 for yes, 0 for no): ");
        scanf("%d", &choice);

    } while (choice != 0);

    return y;
}

// Function to delete an ATM account based on PIN
struct node *delete_account(struct node *y) {
    int pin;
    printf("Enter Account to be deleted: ");
    scanf("%d", &pin);

    temp = search(pin, y);

    if (temp != NULL) {
        if (temp->prev != NULL) {
            temp->prev->next = temp->next;
        } else {
            y = temp->next;
        }

        if (temp->next != NULL) {
            temp->next->prev = temp->prev;
        }

        free(temp);
        printf("Account has been deleted\n");
    } else {
        printf("Account not found\n");
    }

    return y;
}

// Function to deposit money into an ATM account
struct node *deposit(struct node *y) {
    int pin;
    float amount;
    printf("Enter your pin number: ");
    scanf("%d", &pin);

    ptr = search(pin, y);

    if (ptr != NULL) {
        printf("Enter amount to be deposited: ");
        scanf("%f", &amount);
        ptr->atm.amount += amount;
        printf("Amount has been credited\n");
    } else {
        printf("Account not found\n");
    }

    return y;
}

// Function to withdraw money from an ATM account
struct node *withdrawal(struct node *y) {
    int pin;
    float amount;
    printf("Enter your pin number: ");
    scanf("%d", &pin);

    ptr = search(pin, y);

    if (ptr != NULL) {
        printf("Enter amount to be withdrawn: ");
        scanf("%f", &amount);

        if (ptr->atm.amount >= amount) {
            ptr->atm.amount -= amount;
            printf("Amount has been debited\n");
        } else {
            printf("Insufficient funds\n");
        }
    } else {
        printf("Account not found\n");
    }

    return y;
}

// Function to check the balance of an ATM account
float check_balance(struct node *y) {
    int pin;
    printf("Enter your pin number: ");
    scanf("%d", &pin);

    ptr = search(pin, y);

    if (ptr != NULL) {
        return ptr->atm.amount;
    } else {
        printf("Account not found\n");
        return 0.0;
    }
}

// Function to free allocated memory for the linked list
void free_memory(struct node *y) {
    while (y != NULL) {
        temp = y;
        y = y->next;
        free(temp);
    }
}

// Main function to interact with the user and perform banking operations
int main() {
    do {
        printf("Welcome To GCB Bank PLC Limited\n");

        printf("\n\n----ATM Services----\n"
               "1. Create bank account\n"
               "2. Deposit Cash\n"
               "3. Withdraw Money\n"
               "4. Check Balance\n"
               "5. Delete Account\n"
               "6. Exit\n\n");

        printf("Which of the Services do You require: ");
        scanf("%d", &ans);

        switch (ans) {
            case 1:
                head = create_account(head);
                break;
            case 2:
                head = deposit(head);
                break;
            case 3:
                head = withdrawal(head);
                break;
            case 4:
                x = check_balance(head);
                printf("Your balance is: %.2f\n", x);
                break;
            case 5:
                head = delete_account(head);
                break;
            case 6:
                printf("Exiting the program\n");
                break;
            default:
                printf("Invalid response\nTry again\n");
                break;
        }

    } while (ans != 6);

    // Free allocated memory before exiting the program
    free_memory(head);

    return 0;
}
