#include <stdio.h>
#include <errno.h>
#include "file.h"

void saveContactsToFile(AddressBook *addressBook) {
    FILE *fp = fopen("addressBook.csv","w+");
    if(fp==NULL){
        perror("cant open file\n"); // error validation
        return;
    }
    for(int i=0;i<addressBook->contactCount;i++) //saving contacts
    {
        fprintf(fp,"%s,%s,%s\n",addressBook->contacts[i].name,addressBook->contacts[i].phone,addressBook->contacts[i].email);
    }
    fclose(fp);

}

void loadContactsFromFile(AddressBook *addressBook) {
    FILE *fp = fopen("addressBook.csv","r+");
    if(fp==NULL)
    {
        perror("cant access file\n"); // error validation
        return;
    }
    for(int i=0; ;i++)  // loading contacts
    {
        if(fscanf(fp,"%[^,],%[^,],%[^\n]\n",addressBook->contacts[i].name,addressBook->contacts[i].phone,addressBook->contacts[i].email)!=3)
        {
            break;
        }
        addressBook->contactCount++;

    }
    fclose(fp);
    return;
}
