#include<stdio.h>
#include<stdlib.h>
#include<string.h>
FILE* fp;
// Defining a structure for the inventory
struct Product{
    int prod_Id;
    char prod_name[100];
    int quantity;
}p;

void addproduct();
void displayproduct();
void updateproduct();
void deleteproduct();
void buyproduct();
void searchproduct();
void searchbyid();
void sort();

int main(){
        int choice;
        
        while(1){
            printf("<========= Inventory Management System =========>\n\n");
            printf("                  1. Add Product                 \n");
            printf("                  2. Display Product             \n");
            printf("                  3. Update Product              \n");
            printf("                  4. Delete Product              \n");
            printf("                  5. Search Product              \n");
            printf("                  6. Buy Product                 \n");
            printf("                  7. Sort by Product I'd         \n");
            printf("                  8. Exit                        \n");
            printf("\n<===============================================>\n\n");
            printf("Enter your choice : ");
            scanf("%d",&choice);
            printf("\n");
            switch(choice){
                case 8:
                printf("<=========== Program exit Successful ===========>\n\n");
                    exit(0);
                case 7:
                    sort();
                    break;
                case 1:
                    addproduct();
                    break;
                case 2:
                    displayproduct();
                    break;
                case 3:
                    updateproduct();
                    break;
                case 4:
                    deleteproduct();
                    break;
                case 6:
                    buyproduct();
                    break;
                case 5:
                    searchproduct();
                    break;
                default:
                    printf("<================ Invalid Choice ===============>\n");
            }
            printf("\n\n");
            
        }
        return 0;


}

void sort(){
    printf("<================= Sorted List =================>\n\n");
    printf("%-10s %-10s %-30s \n","Product I'd      ","Product Name     ","Product Quantity     ");
    int c=0,i,j;
    struct Product p1[50], t;
    fp=fopen("product.txt","rb");

    while(fread(&p,sizeof(p),1,fp)==1){
        p1[c++]=p;
    }
    for(i=0;i<c-1;i++){
        for(j=i+1;j<c;j++){
            if(p1[i].prod_Id > p1[j].prod_Id){
                t=p1[i];
                p1[i]=p1[j];
                p1[j]=t;
            }
        }
    }
    for(int i=0;i<c;i++){
        printf("%-20d %-20s %-40d \n",p1[i].prod_Id,p1[i].prod_name,p1[i].quantity);
    }

    fclose(fp);
}

void del(int id){
    int f=0;
    FILE* ft;
    fp=fopen("product.txt","rb");
    ft=fopen("temp.txt","wb");
    while(fread(&p, sizeof(p),1,fp)==1){
        if(id==p.prod_Id){
            f=1;
        }
        else fwrite(&p,sizeof(p),1,ft);
    }

    fclose(fp);
    fclose(ft);

    remove("product.txt");
    rename("temp.txt","product.txt");
}

void addproduct(){
    fp=fopen("product.txt","ab");

    printf("Enter the Product I'd : ");
    scanf("%d",&p.prod_Id);

    printf("Enter the Product Name : ");
    fflush(stdin);
    gets(p.prod_name);

    printf("Enter the Product Quantity : ");
    fflush(stdin);
    scanf("%d",&p.quantity);

    printf("\n\nProduct added Successfully!!");
    fwrite(&p,sizeof(p),1,fp);

    fclose(fp);
}

void displayproduct(){
    printf("<================ Product List ================>\n\n");
    printf("%-10s %-10s %-30s \n","Product I'd      ","Product Name     ","Product Quantity     ");
    printf("-------------------------------------------------------------------------------\n");
    fp=fopen("product.txt","rb");

    while(fread(&p,sizeof(p),1,fp)==1){
        printf("%-20d %-20s %-40d \n",p.prod_Id,p.prod_name,p.quantity);
    }

    fclose(fp);
}

void updateproduct(){
    int id,f;
    printf("<================ Update Product ===============>\n\n");
    printf("Enter the Product I'd to update : ");
    scanf("%d",&id);

    fp=fopen("product.txt","rb+");

    while(fread(&p,sizeof(p),1,fp)==1){
        if(id==p.prod_Id){
            f=1;
            printf("Enter the new Product Name : ");
            fflush(stdin);
            gets(p.prod_name);

            printf("Enter the new Product Quantity : ");
            fflush(stdin);
            scanf("%d",&p.quantity);

            fseek(fp,-sizeof(p),1);
            fwrite(&p,sizeof(p),1,fp);
            fclose(fp);
            break;
        }
    }

    if(f==1) printf("\nProduct Updated Successfully!\n");
    else printf("\nProduct not found!\n");
}

void deleteproduct(){
    int id,f;
    printf("<============== Delete Product ==============>\n\n");
    printf("Enter the product I'd to delete : ");
    scanf("%d",&id);

    FILE* ft;

    ft=fopen("product.txt","rb");
    while(fread(&p,sizeof(p),1,fp)==1){
        if(id==p.prod_Id){
            f=1;
            fclose(fp);
            break;
        }
    }

    if(f==1){
        printf("\nProduct deleted Successfully");
        del(id);
    }
    else printf("\nProduct not found");

}

void buyproduct(){
    int id,f=0;
    printf("<================ Buy Product ==================>\n\n");
    printf("Enter the product id to buy : ");
    scanf("%d",&id);

    fp=fopen("product.txt","rb+");

    while(fread(&p,sizeof(p),1,fp)==1){
        if(id==p.prod_Id){
            f=1;
            p.quantity=p.quantity-1;
            fseek(fp,-sizeof(p),1);
            fwrite(&p,sizeof(p),1,fp);
            fclose(fp);
            if(p.quantity==0){
                del(p.prod_Id);
            }
            break;
        }
    }

    if(f==1){
        printf("\nProduct bought successfully");
    }
    else printf("\n\nProduct not found");
}

void searchbyid(){
    int id,f=0;
    printf("Enter the Product I'd you want to search : ");
    scanf("%d",&id);
    fp=fopen("product.txt","rb");
    printf("%-10s %-10s %-30s \n","Product I'd      ","Product Name     ","Product Quantity     ");
    while(fread(&p,sizeof(p),1,fp)==1){
        if(id==p.prod_Id){
            f=1;
            printf("%-20d %-20s %-40d \n",p.prod_Id,p.prod_name,p.quantity);
            break;
        }
        
    }
    fclose(fp);
    if(f==0) printf("\nRecord not found!\n");
    else printf("\nRecord found successfull\n");

}

void searchbyname(){
    char name[100];
    int f=0;
    printf("Enter the Product Name you want to search : \n");
    fflush(stdin);
    gets(name);
    fp=fopen("product.txt","rb");
    printf("\n%-10s %-10s %-30s \n","Product I'd      ","Product Name     ","Product Quantity     ");
    while(fread(&p,sizeof(p),1,fp)==1){
        if(strcmp(name,p.prod_name)==0){
            f=1;
            printf("%-20d %-20s %-40d \n",p.prod_Id,p.prod_name,p.quantity);
            break;
        }
        
    }
    fclose(fp);
    if(f==0) printf("\nRecord not found!\n");
    else printf("\nRecord found successfull\n");
}

void searchproduct(){
    int ch;
    while(1){
        printf("\n<================== Search ==================>\n");
        printf("1.Search by Product Name\n");
        printf("2.Search by Product I'd\n");
        printf("3.Return to main menu\n");
        printf("\nEnter your choice : ");
        scanf("%d",&ch);
        switch(ch){
            default:
               printf("Invalid Choice");
               break;
            case 3:
                main();
                break;
            case 2:
                searchbyid();
                break;
            case 1:
                searchbyname();
                break; 
        }
    }
}

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char username[50];
    char password[50];
} User;

void create_account(User *user) {
    printf("Enter a username: ");
    scanf("%s", user->username);

    printf("Enter a password: ");
    scanf("%s", user->password);
}

int validate_user(User *user) {
    // Check if the username and password match
    if (strcmp(user->username, "admin") == 0 && strcmp(user->password, "password") == 0) {
        return 1; // Success
    }

    return 0; // Failure
}

int main() {
    int option;
    User user;

    do {
        printf("\n1. Login\n");
        printf("2. Create account\n");
        printf("3. Exit\n");
        printf("Enter an option: ");
        scanf("%d", &option);

        switch (option) {
            case 1:
                printf("Enter username: ");
                scanf("%s", user.username);

                printf("Enter password: ");
                scanf("%s", user.password);

                if (validate_user(&user)) {
                    printf("Login successful!\n");
                } else {
                    printf("Invalid username or password.\n");
                }
                break;

            case 2:
                create_account(&user);
                printf("Account created successfully!\n");
                break;

            case 3:
                printf("Exiting...\n");
                break;

            default:
                printf("Invalid option. Please try again.\n");
        }
    } while (option != 3);

    return 0;
}