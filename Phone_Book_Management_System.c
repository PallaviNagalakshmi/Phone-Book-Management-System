#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stddef.h>

struct phone
{
    char name[25];
    long long int contact;
    struct phone *next;
    char category[20];
} *start = NULL, *newnode = NULL;

// Function to check for correct phone number
int validNumber(long long int originalNumber)
{
    long long int number = originalNumber;
    int digitCount = 0;

    while (number != 0)
    {
        number /= 10;
        digitCount++;
    }

    if (digitCount == 10 && (originalNumber >= 6000000000 && originalNumber <= 9999999999))
        return 0; // valid number
    else
        return 1; // invalid number
}

// Function to check for a duplicate contact based on name or phone number
int isDuplicateContact(const char *name, const long long int contact)
{
    struct phone *temp = start;

    while (temp != NULL)
    {
        // Check for duplicate based on name
        if (name != NULL && strcasecmp(temp->name, name) == 0)
        {
            // Duplicate contact found based on name
            return 1;
        }
        // Check for duplicate based on phone number
        if (temp->contact == contact)
        {
            // Duplicate contact found based on phone number
            return 1;
        }

        temp = temp->next;
    }

    // No duplicate found
    return 0;
}

// Function to insert new contact
void add(struct phone *newContact)
{
    if (isDuplicateContact(newContact->name, newContact->contact))
    {
        printf("\nDuplicate contacts are not allowed.\n", newContact->name);
        return;
    }
    struct phone *temp = start;
    struct phone *prev = NULL; // Add a pointer to the previous node

    if (start == NULL)
    {
        start = newContact;
    }
    else
    {
        while (temp != NULL && strcmp(temp->name, newContact->name) < 0)
        {
            prev = temp;
            temp = temp->next;
        }
        if (prev == NULL)
        {
            // Insert at the beginning of the list
            newContact->next = start;
            start = newContact;
        }
        else
        {
            // Insert in the middle or at the end of the list
            prev->next = newContact;
            newContact->next = temp;
        }
    }
}

// Function to perform case-insensitive substring search
const char *caseInsensitiveStrStr(const char *existing, const char *search)
{
    size_t searchLen = strlen(search);

    while (*existing)
    {
        if (strncasecmp(existing, search, searchLen) == 0)
        {
            return existing;
        }
        existing++;
    }

    return NULL;
}

// Function to search for a contact
void search(char name[])
{
    if (start == NULL)
    {
        printf("No contacts present in phone book\n");
    }
    else
    {
        struct phone *temp = start;
        int found = 0;

        printf("Contacts matching '%s':\n", name);

        while (temp != NULL)
        {
            if (caseInsensitiveStrStr(temp->name, name) != NULL)
            {
                found = 1;
                // Print the original case of the name
                printf("\nName: %s\nPhone number: %lld\n", temp->name, temp->contact);
            }
            temp = temp->next;
        }

        if (!found)
        {
            printf("No contact found with the given name or substring\n\n");
        }
    }
}

// Function to delete a contact
void deleteContact(char name[])
{
    if (start == NULL)
    {
        printf(" No contacts in phone book to delete ");
    }
    else
    {
        struct phone *temp = start;
        struct phone *temp1 = temp;

        while (temp != NULL && strcmp(temp->name, name) != 0)
        {
            temp1 = temp;
            temp = temp->next;
        }

        if (temp == NULL)
        {
            printf("No such contact found\n");
        }
        else
        {
            if (temp1 == temp)
            {
                // The contact to delete is the first node
                start = temp->next;
            }
            else
            {
                temp1->next = temp->next;
            }
            printf("Deleted contact of %s\n", temp->name);
            free(temp);
        }
    }
}

// Function to modify a contact
void modify(char name[])
{
    if (start == NULL)
    {
        printf("No contacts present in phone book\n");
    }
    else
    {
        struct phone *temp = start;
        while (temp != NULL && strcmp(temp->name, name) != 0)
            temp = temp->next;
        if (temp == NULL)
            printf("No such contact found\n");
        else
        {
            printf("Enter new name:\t");
            scanf("%s", temp->name);

            printf("Enter new number:\t");
            scanf("%lld", &temp->contact);

            while (validNumber(temp->contact))
            {
                printf("Invalid phone number. Please enter again\nPhone number:");
                scanf("%lld", &temp->contact);
            }
        }
    }
}

// Function to remove all contacts
void remove_all()
{
    system("cls");

    if (start == NULL)
    {
        printf("No contacts in phone book to delete\n");
    }
    else
    {
        while (start != NULL)
        {
            struct phone *temp = start;
            start = start->next;
            free(temp);
        }
        printf("All data in the phonebook deleted successfully\n");
    }
}

// Function to display all contacts
void display()
{
    if (start == NULL)
        printf("\nNo contacts in phone book to display\n");
    else
    {
        printf("\nContacts in phone book:\n");
        struct phone *temp = start;
        int i = 1;
        while (temp != NULL)
        {
            printf("\n%d. %s", i, temp->name);
            temp = temp->next;
            i++;
        }
        printf("\n");
    }
}

void displayGrouped()
{
    if (start == NULL)
        printf("\nNo contacts in the phone book to display\n");
    else
    {
        char currentCategory[20] = "";
        printf("\nContacts grouped by category:\n");
        struct phone *temp = start;
        while (temp != NULL)
        {
            if (strcmp(temp->category, currentCategory) != 0)
            {
                printf("\n%s:\n", temp->category);
                strcpy(currentCategory, temp->category);
            }
            printf("\nName: %s\nPhone number: %lld\n", temp->name, temp->contact);
            temp = temp->next;
        }
    }
}
// Function to display emergency contact numbers
void displayEmergencyContacts()
{
    printf("\nEmergency Contact Numbers:\n");
    printf("1. NATIONAL EMERGENCY NUMBER: 112\n");
    printf("2. POLICE: 100 or 112\n");
    printf("3. FIRE: 101\n");
    printf("4. AMBULANCE: 102\n");
    printf("5. Disaster Management Services: 108\n");
    printf("6. Women Helpline: 1091\n");
    printf("7. Women Helpline (Domestic Abuse): 181\n");
    printf("8. Air Ambulance: 9540161344\n");
    printf("9. Aids Helpline: 1097\n");
    printf("10. Anti Poison (New Delhi): 1066 or 011-1066\n");
    printf("11. Disaster Management (N.D.M.A): 1078, 01126701728\n");
    printf("12. EARTHQUAKE/FLOOD/DISASTER (N.D.R.F Headquaters) NDRF HELPLINE NO: 011-24363260 9711077372\n");
    printf("13. Deputy Commissioner Of Police – Missing Child And Women: 1094\n");
    printf("14. Railway Enquiry: 139\n");
    printf("15. Senior Citizen Helpline: 14567\n");
    printf("16. Medical Helpline: 108\n");
    printf("17. Railway Accident Emergency Service: 1072\n");
    printf("18. Road Accident Emergency Service: 1073\n");
    printf("19. Road Accident Emergency Service On National Highway For Private Operators: 1033\n");
    printf("20. ORBO Centre, AIIMS (For Donation Of Organ) Delhi: 1060\n");
    printf("21. Kisan Call Centre: 18001801551\n");
    printf("22. Relief Commissioner For Natural Calamities: 1070\n");
    printf("23. Children In Difficult Situation: 1098\n");
    printf("24. National Poisons Information Centre - AIIMS NEW DELHI (24*7): 1800116117, 011-26593677, 26589391\n");
    printf("25. Poison Information Centre (CMC, Vellore): 18004251213\n");
    printf("26. Tourist Helpline: 1363 or 1800111363\n");
    printf("27. LPG Leak Helpline: 1906\n");
    printf("28. KIRAN MENTAL HEALTH Helpline: 18005990019\n");
    printf("29. CYBER CRIME HELPLINE: 155620\n");
    printf("30. COVID 19 HELPLINE: 011-23978046 OR 1075\n");
}

// Main function
int main()
{
    int ch;
    char name[20];
    printf("*******************************************\n");
    printf("\tPHONE BOOK MANAGEMENT SYSTEM\t\n");
    printf("*******************************************\n");

    while (1)
    {
        printf("\n1. Add new contact\t2. Search for a contact\t\t3. Modify a contact\n\n");
        printf("4. Delete a contact\t5. Show all contacts\t\t6. Delete all contacts\n\n");
        printf("7. Display Emergency Contact Numbers\t8. Display contacts by groups\t9. Close phone book\n\n");
        printf("Choose an operation to perform:\t");
        scanf("%d", &ch);
        system("cls");

        switch (ch)
        {
        case 1:
            newnode = (struct phone *)malloc(sizeof(struct phone));
            printf("\t*Details of new contact*\n\nEnter name:\t");
            scanf("%s", newnode->name);
            printf("Enter phone number:");
            scanf("%lld", &newnode->contact);
            // Check for valid number
            while (validNumber(newnode->contact))
            {
                printf("Invalid phone number. Please enter again\nPhone number:");
                scanf("%lld", &newnode->contact);
            }
            printf("Enter group (e.g., Family, Friends, Work):\t");
            scanf("%s", newnode->category);

            newnode->next = NULL;
            add(newnode);
            printf("\nNew contact added!!!\n");
            break;

        case 2:
            printf("Enter name to search:\t");
            scanf("%s", name);
            search(name);
            break;

        case 3:
            printf("Enter name of contact you want to modify:\t");
            scanf("%s", name);
            modify(name);
            break;

        case 4:
            printf("Enter name of contact to delete:\t");
            scanf("%s", name);
            deleteContact(name);
            break;

        case 5:
            display();
            break;

        case 6:
            remove_all();
            break;

        case 7:
            displayEmergencyContacts();
            break;

        case 8:
            displayGrouped();
            break;
        case 9:
            exit(0);

        default:
            printf("Choose correct option:\t");
        }
    }
}