#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_USER 10

typedef struct
{
    int id;
    char* name;
    double balance;
    int pin;
    bool active;
} User;

int userIndexCounter = -1;
int userIDCounter = 0;

User users[MAX_USER] = {};

void createUser(char* name, const int pin, const double initialBalance = 0)
{
    const int newUserID = ++userIndexCounter;

    users[newUserID] = {};

    users[newUserID].id = ++userIDCounter;
    users[newUserID].name = name;
    users[newUserID].pin = pin;
    users[newUserID].balance = initialBalance;
    users[newUserID].active = true;
}

void clearScreen()
{
    system("cls");
}

int chooseMenu(char menus[10][20])
{
    while (1)
    {
        printf("Menus:\n");

        int validMenu = 0;

        for (int i = 0; i < 10; i++)
        {
            if (strlen(menus[i]) == 0) break;

            validMenu += 1;

            printf("%d. %s\n", i + 1, menus[i]);
        }

        int choosedMenu;

        printf("Menu:");
        scanf("%d", &choosedMenu);

        if (choosedMenu > validMenu || choosedMenu < 1)
        {
            clearScreen();

            printf("Invalid menu\n");
        }
        else
        {
            return choosedMenu;
        }
    }
}

int main(void)
{
    createUser("Foo", 123123, 10000);
    createUser("Bar", 321321, 20000);

    while (1)
    {
        char menus[10][20] = {"Register", "Login"};
        const int menuChoice = chooseMenu(menus);

        clearScreen();

        switch (menuChoice)
        {
        case 1:
            printf("Register\n");
            char* name;
            int pin;

            printf("Name:");
            scanf("%s", &name);
            printf("Pin:");
            scanf("%d", &pin);

            break;
        case 2:
            printf("Login\n");
        }
    }
}
