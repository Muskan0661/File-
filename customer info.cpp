#include <stdio.h>
struct info {
    int name;
    int accno;
    int balance;
};
int main() {
    int i, num;
    printf("Number of customers initially: ");
    scanf("%d", &num);
    struct info bank[num];
    for (i = 0; i < num; i++) {
        printf("Customer %d name (ID): ", i + 1);
        scanf("%d", &bank[i].name);
        printf("Account number: ");
        scanf("%d", &bank[i].accno);
        printf("Balance: ");
        scanf("%d", &bank[i].balance);
    }
    char moreinfo;
    printf("Want info of more customers? y/n: ");
    scanf(" %c", &moreinfo);
    if (moreinfo == 'y') {
        int additional_num;
        printf("Number of additional customers: ");
        scanf("%d", &additional_num);
        struct info new_bank[additional_num];
        for (i = 0; i < additional_num; i++) {
            printf("Customer %d name (ID): ", i + 1 + num);
            scanf("%d", &new_bank[i].name);
            printf("Account number: ");
            scanf("%d", &new_bank[i].accno);
            printf("Balance: ");
            scanf("%d", &new_bank[i].balance);
        }
        printf("\nFinal customer data:\n");
        for (i = 0; i < num; i++) {
            printf("\nCustomer %d\n", i + 1);
            printf("Name (ID): %d\n", bank[i].name);
            printf("Account number: %d\n", bank[i].accno);
            printf("Balance: %d\n", bank[i].balance);
        }
        for (i = 0; i < additional_num; i++) {
            printf("\nCustomer %d\n", i + 1 + num);
            printf("Name (ID): %d\n", new_bank[i].name);
            printf("Account number: %d\n", new_bank[i].accno);
            printf("Balance: %d\n", new_bank[i].balance);
        }
    } 
	else {
        printf("No more customers will be added.\n");
        printf("\nFinal customer data:\n");
        for (i = 0; i < num; i++) {
            printf("\nCustomer %d\n", i + 1);
            printf("Name (ID): %d\n", bank[i].name);
            printf("Account number: %d\n", bank[i].accno);
            printf("Balance: %d\n", bank[i].balance);
        }
    }
    return 0;
}
