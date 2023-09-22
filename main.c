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
    printf("<===============Product List===============>\n\n");
    printf("%-10s %-10s %-30s \n","Product I'd      ","Product Name     ","Product Quantity     ");
    printf("----------------------------------------------\n");
    fp=fopen("product.txt","rb");
    while(fread(&p,sizeof(p),1,fp)==1){
        printf("%-20d %-20s %-40d \n",p.prod_Id,p.prod_name,p.quantity);
    }
    fclose(fp);
}
void updateproduct(){
    int id,f;
    printf("<=================Update Product================>\n\n");
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
    printf("<===============Delete Product===============>\n\n");
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
    printf("<=================Buy Product===================>\n\n");
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
int main(){
        int choice;
        while(1){
            printf("<==========Inventory Management System==========>\n\n");
            printf("                  1. Add Product                 \n");
            printf("                  2. Display Product             \n");
            printf("                  3. Update Product              \n");
            printf("                  4. Delete Product              \n");
            // printf("                  5. Search Product              \n");
            printf("                  6. Buy Product                 \n");
            printf("                  7. Exit                        \n");
            printf("\n<===============================================>\n\n");
            printf("Enter your choice : ");
            scanf("%d",&choice);
            printf("\n");
            switch(choice){
                case 7:
                printf("<=========== Program exit Successful ===========>\n\n");
                    exit(0);
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
                default:
                    printf("<=================Invalid Choice================>\n");
            }
            printf("\n\n");
            
        }
        return 0;


}