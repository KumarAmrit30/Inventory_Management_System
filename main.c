#include<stdio.h>
#include<stdlib.h>
#include<string.h>
// Defining a structure for the inventory
struct Product{
    int prod_Id;
    char prod_name[100];
    int quantity;
}p;
void addproduct(){
    FILE* fp=fopen("product.txt","ab");
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
    
}
void updateproduct(){}
void deleteproduct(){}
void buyproduct(){}
int main(){
        int choice;
        while(1){
            printf("<==========Inventory Management System==========>\n");
            printf("                  1. Add Product                 \n");
            printf("                  2. Display Product             \n");
            printf("                  3. Update Product              \n");
            printf("                  4. Delete Product              \n");
            printf("                  5. Buy Product                 \n");
            printf("                  6. Exit                        \n");
            printf("<===============================================>\n\n\n");
            printf("Enter your choice : ");
            scanf("%d",&choice);
            printf("\n");
            switch(choice){
                case 6:
                    exit(0);
                case 1:
                    addproduct();
                    break;
                case 2:
                    displayproduct();
                    break;
                // case 3:
                //     updateproduct();
                //     break;
                // case 4:
                //     deleteproduct();
                //     break;
                // case 5:
                //     buyproduct();
                //     break;
                default:
                    printf("Invalid choice....\n\n");
            }
            printf("Press any key to continue....\n\n\n");
            
        }
        return 0;


}