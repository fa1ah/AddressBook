#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include "contact.h"
#include "file.h"
#include "populate.h"

char name[50],phone[20],mail[50];
int flag;
int arr[50];

void valid_name(AddressBook *addressBook) // validate name
{
    for(;;)
    {
        flag=0;
        printf("Enter name:");
        scanf(" %49[^\n]",name);
        for(int i=0;name[i]!='\0';i++)
        {
            if(isalpha(name[i])||isspace(name[i]))
            {
                flag=1;
            }
            else
                flag=0;
                break;
        }
        if(flag)
            break;
        printf("only alphabets\n");
    }
}
void valid_phone(AddressBook *addressBook)// validate phone
{
    for(;;)
    {
        flag=0;
        printf("Enter number:");
        scanf("%s",phone);
        if(strlen(phone)==10)
        {
            for(int j=0;phone[j]!='\0';j++)
            {
                if(isdigit(phone[j]))
                    flag=1;
                else{
                    flag=0;
                    break;
                }
            }
        }
        if(flag==0){
            printf("should have 10 digits\n");
            continue;
        }
        for(int i=0;i<addressBook->contactCount;i++)
        {
            if(strcmp(phone,addressBook->contacts[i].phone)==0){
                flag=0;
                break;
            }
        }
        if(flag)
            break;
        printf("already present\n");
    }
    
}
void valid_mail(AddressBook *addressbook) // validate mail
{
    for(;;)
    {
        flag=1;
        printf("Enter email:");
        scanf("%s",mail);
        int len = strlen(mail);
        for(int i=0;i<len;i++)
        {
            char *check=strstr(mail,"@");
            if(check==NULL)
            {
                flag=0;
                break;
            }
            char *check1=strstr(mail,".com");
            if(check1==NULL)
            {
                flag=0;
                break;
            }
        }
        if(flag)
        {
            printf("contact added\n");
            break;
        }
        printf("incorrect mail id\n");
    }
}

void listContacts(AddressBook *addressBook, int sortCriteria) 
{
    Contact temp;
    switch(sortCriteria)
    {
        case 1: // sorting based on name
            for(int i=0;i<(addressBook->contactCount);i++)
            {
                for(int j=0;j<addressBook->contactCount-1;j++)
                {
                    if(strcmp(addressBook->contacts[j].name,addressBook->contacts[j+1].name)>0)
                    {
                        temp=addressBook->contacts[j];
                        addressBook->contacts[j]=addressBook->contacts[j+1];
                        addressBook->contacts[j+1]=temp;
                    }
                }
            }
            break; 
        case 2:  // sorting based on phone
        for(int i=0;i<(addressBook->contactCount);i++)
        {
            for(int j=0;j<addressBook->contactCount-1;j++)
            {
                if(strcmp(addressBook->contacts[j].phone,addressBook->contacts[j+1].phone)>0)
                {
                    temp=addressBook->contacts[j];
                    addressBook->contacts[j]=addressBook->contacts[j+1];
                    addressBook->contacts[j+1]=temp;
                }
            }
        }
            break;
        case 3:  // sorting based on mail
        for(int i=0;i<(addressBook->contactCount);i++)
        {
            for(int j=0;j<addressBook->contactCount-1;j++)
            {
                if(strcmp(addressBook->contacts[j].email,addressBook->contacts[j+1].email)>0)
                {
                    temp=addressBook->contacts[j];
                    addressBook->contacts[j]=addressBook->contacts[j+1];
                    addressBook->contacts[j+1]=temp;
                }
            }
        }
            break;
        default:
        {
            printf("Enter the above options\n");
            return;
        }
    }
        printf("-------------------------------------------\n");   
    for(int i=0;i<(addressBook->contactCount);i++)
    {    
        printf("%s\t\t",addressBook->contacts[i].name);
        printf("%s\t\t",addressBook->contacts[i].phone);
        printf("%s\n",addressBook->contacts[i].email);
    }
}
void initialize(AddressBook *addressBook) {
    addressBook->contactCount = 0;
    // populateAddressBook(addressBook);    
    // Load contacts from file during initialization (After files)
    loadContactsFromFile(addressBook);
}
void saveAndExit(AddressBook *addressBook) {
    saveContactsToFile(addressBook); // Save contacts to file
    exit(EXIT_SUCCESS); // Exit the program
}
void createContact(AddressBook *addressBook)
{
    valid_name(addressBook);
    valid_phone(addressBook);
    valid_mail(addressBook);
    int limit=addressBook->contactCount;
    strcpy(addressBook->contacts[limit].name,name);
    strcpy(addressBook->contacts[limit].phone,phone);
    strcpy(addressBook->contacts[limit].email,mail);
    addressBook->contactCount++;
}
int* searchContact(AddressBook *addressBook) 
{
    printf("Select search criteria:\n");
    printf("1. Search by name\n");
    printf("2. Search by phone\n");
    printf("3. Search by email\n");
    int searchChoice;
    char c;
    for(;;)
    {
        printf("Enter your choice: ");
        searchChoice=5;
        scanf("%d",&searchChoice); // if(scanf("%d%s", &searchChoice,&c)== 2 || c == '\n')//ask sir
        if(searchChoice>0 && searchChoice<4)
            break;
        printf("choose from the above options\n: ");
    }
    int index=1,cursor=0;
    switch(searchChoice)
    {
        case 1: // search by name
            flag=1;
            printf("Enter name:");
            scanf(" %49[^\n]",name);
            for(int i=0;i<(addressBook->contactCount);i++)
            {
                char *res=strcasestr(addressBook->contacts[i].name,name);
                if(res!=NULL)
                {
                    printf("%d. ",index);
                    printf("%s\t\t",addressBook->contacts[i].name);
                    printf("%s\t\t",addressBook->contacts[i].phone);
                    printf("%s\n",addressBook->contacts[i].email);
                    printf("**********************\n");
                    arr[cursor]=i;// store the index from list
                    index++; // present index
                    cursor++;
                    flag=0;
                }
            }
            if(flag)
                    printf("No contact found\n");
            break;
        
        case 2: // search by phone
            flag=1;
            printf("Enter phone number: ");
            scanf("%s",phone);
            for(int i=0;i<(addressBook->contactCount);i++)
            {
                int res=strcmp(phone,addressBook->contacts[i].phone);
                if(res==0)
                {
                    printf("%d. ",index);
                    printf("%s\t\t",addressBook->contacts[i].name);
                    printf("%s\t\t",addressBook->contacts[i].phone);
                    printf("%s\n",addressBook->contacts[i].email);
                    printf("**********************\n");
                    arr[cursor]=i;
                    flag=0;
                    index++;
                    cursor++;
                    break;
                }
            }
            if(flag)
                    printf("No contact found\n");
            break;
        case 3: // search by mail
            flag=1;
            int index=1;
            printf("Enter email id: ");
            scanf("%s",mail);
            for(int i=0;i<(addressBook->contactCount);i++)
            {
                char* res=strcasestr(addressBook->contacts[i].email,mail);
                if(res!=NULL)
                {
                    printf("%d. ",index);
                    printf("%s\t\t",addressBook->contacts[i].name);
                    printf("%s\t\t",addressBook->contacts[i].phone);
                    printf("%s\n",addressBook->contacts[i].email);
                    printf("**********************\n");
                    arr[cursor]=i;
                    flag=0;
                    index++;
                    cursor++;
                    break;
                }
            }
            if(flag)
                    printf("No mail id found\n");
            break;
    }
    if(flag)
        return 0;
    else    
        return arr;
}
void editContact(AddressBook *addressBook)
{
    int cursor;
	printf("Select edit criteria:\n");
    printf("1. edit by name\n");
    printf("2. edit by phone\n");
    printf("3. edit by email\n");
    int editChoice;
    for(;;)
    {
        printf("Enter your choice: ");
        scanf("%d", &editChoice);
        if(editChoice>0&&editChoice<4)
            break;
        printf("choose from the above options\n: ");
    }
    switch(editChoice)
    {
        case 1:
            flag=1;
            printf("Enter name:");
            scanf(" %49[^\n]",name);
            for(int i=0;i<(addressBook->contactCount);i++)
            {
                int res=strcasecmp(name,addressBook->contacts[i].name);
                if(res==0)
                {
                    printf("%s\t\t",addressBook->contacts[i].name);
                    printf("%s\t\t",addressBook->contacts[i].phone);
                    printf("%s\n",addressBook->contacts[i].email);
                    printf("Select edit criteria:\n");
                    printf("1. edit name\n");
                    printf("2. edit phone\n");
                    printf("3. edit email\n");
                    int edChoice;
                    for(;;)
                    {
                        printf("Enter your choice: ");
                        scanf("%d", &edChoice);
                        if(edChoice>0&&edChoice<4)
                            break;
                        printf("choose from the above options\n: ");
                    }
                    switch(edChoice)
                    {
                        case 1:
                            valid_name(addressBook);
                            strcpy(addressBook->contacts[i].name,name);
                            flag=0;
                            break;
                        case 2:
                            valid_phone(addressBook);
                            strcpy(addressBook->contacts[i].phone,phone);
                            flag=0;
                            break;
                        case 3:
                            valid_mail(addressBook);
                            strcpy(addressBook->contacts[i].email,mail);
                            flag=0;
                            break;
                    }              
                }
            }
            if(flag)
                printf("No name found\n");
            else
                printf("contact updated\n");
            break;
        case 2:
            flag=1;
            printf("Enter phone number:");
            scanf(" %19[^\n]",phone);
            for(int i=0;i<(addressBook->contactCount);i++)
            {
                int res=strcmp(name,addressBook->contacts[i].phone);
                if(res==0)
                {
                    printf("Select edit criteria:\n");
                    printf("1. edit name\n");
                    printf("2. edit phone\n");
                    printf("3. edit email\n");
                    int edChoice;
                    for(;;)
                    {
                        printf("Enter your choice: ");
                        scanf("%d", &edChoice);
                        if(edChoice>0&&edChoice<4)
                            break;
                        printf("choose from the above options\n: ");
                    }
                    switch(edChoice)
                    {
                        case 1:
                            valid_name(addressBook);
                            strcpy(addressBook->contacts[i].name,name);
                            flag=0;
                            break;
                        case 2:
                            valid_phone(addressBook);
                            strcpy(addressBook->contacts[i].phone,phone);
                            flag=0;
                            break;
                        case 3:
                            valid_mail(addressBook);
                            strcpy(addressBook->contacts[i].email,mail);
                            flag=0;
                            break;
                    }              
                }
            }
            if(flag)
                printf("No number found\n");
            else
                printf("contact updated\n");
            break;

        case 3:
            flag=1;
            printf("Enter mail id:");
            scanf(" %49[^\n]",name);
            for(int i=0;i<(addressBook->contactCount);i++)
            {
                int res=strcasecmp(addressBook->contacts[i].email,mail);
                if(res==0)
                {
                    printf("Select edit criteria:\n");
                    printf("1. edit name\n");
                    printf("2. edit phone\n");
                    printf("3. edit email\n");
                    int edChoice;
                    for(;;)
                    {
                        printf("Enter your choice: ");
                        scanf("%d", &edChoice);
                        if(edChoice>0&&edChoice<4)
                            break;
                        printf("choose from the above options\n: ");
                    }
                    switch(edChoice)
                    {
                        case 1:
                            valid_name(addressBook);
                            strcpy(addressBook->contacts[i].name,name);
                            flag=0;
                            break;
                        case 2:
                            valid_phone(addressBook);
                            strcpy(addressBook->contacts[i].phone,phone);
                            flag=0;
                            break;
                        case 3:
                            valid_mail(addressBook);
                            strcpy(addressBook->contacts[i].email,mail);
                            flag=0;
                            break;
                    }              
                }
            }
            if(flag)
                printf("No mail id found\n");
            else
                printf("contact updated\n");
            break;
    }

}
void deleteContact(AddressBook *addressBook)
{
    int n;
    int* arr=searchContact(addressBook);
    if(arr==0)
    {
        printf("no contacts found");
        return;
    }
    printf("Enter the contact to be deleted:");
    scanf("%d",&n);
    int num;
    for(;;)
    {
        printf("confirm deletion\n 1.Yes\n 2.No\n input:");
        scanf("%d",&num);
        if(num==1)
            break;
        if(num==2)
            return;
        printf("choose from the option\n");
    }
    int del_index=arr[n-1];
    for(int i=del_index;i<addressBook->contactCount-1;i++)
    {
        addressBook->contacts[del_index]=addressBook->contacts[del_index+1];
    }   
    addressBook->contactCount--;
    printf("contact deleted\n");


   
}