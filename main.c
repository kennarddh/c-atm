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

int createUser(char* name, int pin, double initialBalance)
{
    int index = ++userIndexCounter;
    int userID = ++userIDCounter;

    // users[newUserID] = {};

    users[index].id = userID;
    users[index].name = name;
    users[index].pin = pin;
    users[index].balance = initialBalance;
    users[index].active = true;

    return userID;
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
            return choosedMenu - 1;
        }
    }
}

bool tryAskForPin(User* user)
{
    int failPinTimes = 0;

    while (1)
    {
        int pin;

        printf("Pin:");
        scanf("%d", &pin);

        if (user->pin != pin)
        {
            printf("Wrong pin.\n");

            failPinTimes += 1;

            if (failPinTimes >= 3)
            {
                printf("Pin wrong 3 times. User deactivated.\n");

                user->active = false;

                return false;
            }
        }
        else
        {
            return true;
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
        int menuChoice = chooseMenu(menus);

        clearScreen();

        switch (menuChoice)
        {
        case 0:
            {
                printf("Register\n");
                char* name;
                int pin, initialBalance;

                printf("Name:");
                scanf("%s", &name);
                printf("Pin:");
                scanf("%d", &pin);
                printf("Initial balance:");
                scanf("%d", &initialBalance);

                int userID = createUser(&name, pin, initialBalance);

                printf("User %s created.\nUser id: %d\n", &name, userID);

                break;
            }
        case 1:
            {
                printf("Login\n");

                int userID, pin;

                printf("ID:");
                scanf("%d", &userID);
                printf("Pin:");
                scanf("%d", &pin);

                int foundUserIndex = -1;

                for (int i = 0; i < userIndexCounter + 1; ++i)
                {
                    User user = users[i];

                    if (userID == user.id)
                    {
                        foundUserIndex = i;
                    }
                }

                if (foundUserIndex == -1)
                {
                    printf("User with id %d not found\n", userID);

                    break;
                }

                User* user = &users[foundUserIndex];

                if (user->pin != pin)
                {
                    printf("Wrong pin\n");

                    break;
                }

                clearScreen();

                printf("Logged in as %s.\n", user->name);

                while (1)
                {
                    char loggedInMenus[10][20] = {"Check Balance", "Logout", "Change Pin", "Transfer"};
                    int loggedInMenuChoice = chooseMenu(loggedInMenus);

                    switch (loggedInMenuChoice)
                    {
                    case 0:
                        printf("Your balance is %f\n", user->balance);

                        break;
                    case 1:
                        printf("Logged out.\n");

                        goto logout;
                    case 2:
                        {
                            printf("Change pin.\n");

                            bool isPinCorrect = tryAskForPin(user);

                            if (!isPinCorrect)
                                goto logout;

                            int newPin;

                            printf("New Pin:");
                            scanf("%d", &newPin);

                            if (user->pin == newPin)
                            {
                                printf("New pin cannot be same as current pin.\n");

                                break;
                            }

                            user->pin = newPin;

                            printf("Pin changed.\n");

                            goto logout;
                        }
                    case 3:
                        {
                            // Wrong here. Always go here.
                            printf("Transfer.\n");

                            bool isPinCorrect = tryAskForPin(user);

                            if (!isPinCorrect)
                                goto logout;


                            int transferAmount;

                            printf("Transfer Amount:");
                            scanf("%d", &transferAmount);

                            if (transferAmount > user->balance)
                            {
                                printf("Not enough balance\n");

                                break;
                            }

                            int targetUserID;

                            printf("Target User ID:");
                            scanf("%d", &targetUserID);

                            int foundUserIndex2 = -1;

                            for (int i = 0; i < userIndexCounter + 1; ++i)
                            {
                                User* userIter = &users[i];

                                if (targetUserID == userIter->id)
                                {
                                    foundUserIndex2 = i;
                                }
                            }

                            if (foundUserIndex2 == -1)
                            {
                                printf("Target user with id %d not found\n", targetUserID);

                                break;
                            }

                            User* targetUser = &users[foundUserIndex];

                            user->balance -= transferAmount;
                            targetUser->balance += transferAmount;

                            printf("Succesfully transfered %d to user with the id %d.\n", transferAmount, targetUserID);

                            break;
                        }
                    }
                }
            }

        logout:
            void;
        }
    }
}
