#include<stdio.h>
#include<conio.h>
#include<string.h>
#include<stdlib.h>
#include<windows.h>
//#include<graphic.h>
struct library{
int pages;
char bk_name[50],bk_author[50];
float price;
}bk_list;
//int login();
int add();//function declaration
int edit();
int search();
int delete();
int display();
int main(){
system("cls");
system("color 5F");
char user[30]="shovan",pass[10]="admin@123",exit_choice,ch,c='\n';
int choice,i=0,try=0;
char epass[10],euser[30];
do{ //Login page 
login:
printf("\n\t\t\t***********************\n");
printf("\t\t\t\xB2\xB2\xB2\xB2\xB2\xB2\xB2 WELCOME \xB2\xB2\xB2\xB2\xB2\xB2\xB2\n");
printf("\t\t\t***********************");
printf("\nEnter the username:\n");
gets(euser);
printf("Enter the password:\n");
while(i<10){
epass[i]=getch();
c=epass[i];
if(c=='\r'){
break;
}
else{
printf("*");
i++;
}
}
epass[i]='\0';
i=0;
if(strcmp(user,euser)==0 &&strcmp(pass,epass)==0){ //Comparison of admin and user 
// system("pause");
goto menu;
// break;
}
else{
printf("\nPlease re enter your username and password:\n");
system("pause");
try++;
}
}while(try<3);
menu:
label:
do{ //Interface of admin login page 
system("cls");
system("color 5F");
printf("\t\t\t*************************************\n");
printf("\t\t\xB2\xB2\xB2\xB2\xB2\xB2\xB2 WELCOME TO LIBRARY MANAGEMENT SYSTEM \xB2\xB2\xB2\xB2\xB2\xB2\xB2");
printf("\n\t\t\t*************************************");
printf("\n\n\t\t\t-------MENU-------\n");
printf("1.Add Book\n2.Display Book\n3.Edit Book\n4.Search Book\n5.Delete Book\n6.Exit\n"); //Library option for admin 
printf("Enter the choice:\n");
scanf("%d",&choice);
switch(choice){
case 1: add();
break;
case 2: display();
break;
case 3: edit();
break;
case 4: search();
break;
case 5: delete();
break;
case 6: printf("Do you want to exit?(y/n)\n");
scanf("%s",&exit_choice);
if(exit_choice=='Y'||exit_choice=='y'){
break;
}
if(exit_choice=='n'|| exit_choice=='N'){
goto label;
}
break;
default: printf("Enter valid choice!\n"); //confirmation before exit 
}
} while(choice!=6);
return 0;
}
int add(){
FILE*fpA;
fpA=fopen("library.bin","ab"); //Library directory 
if(fpA==NULL){
printf("ERROR!FILE NOT AVAILABLE\n");
}
system("cls");
system("color 4F");
printf("\t\t\t\t********************\n");
printf("\t\t\t\t\tADD NEW BOOK\t\t\t\t\t\n");
printf("\t\t\t\t********************\n");
printf("Book Name:\n");
scanf("%s",bk_list.bk_name);
//fgets(bk_list.bk_name,sizeof(bk_list.bk_name),stdin);
printf("Book Author:\n");
scanf("%s",bk_list.bk_author);
//gets(bk_list.bk_author);
printf("Book Pages:\n");
scanf("%d",&bk_list.pages);
printf("Book Price:\n");
scanf("%s",&bk_list.price);
fwrite(&bk_list, sizeof(bk_list),1,fpA);
fclose(fpA);
printf("Book Added Successfully!!\n");
printf("\n");
}
int display(){
FILE *fpD;
fpD=fopen("library.bin","rb");
if(fpD==NULL){
printf("ERROR!FILE NOT AVAILABLE\n");
}
system("cls");
system("color 71");
getch();
printf("\t\t\t\t********************\n");
printf("\t\t\t\tBOOK INFORMATION\n");
printf("\t\t\t\t********************\n");
printf("\nBOOK TITLE\t\tBOOK AUTHOR\t\tBOOK PAGES\t\tBOOK PRICE\t\t");
while(fread(&bk_list,sizeof(bk_list),1,fpD)==1){
printf("\n%s",bk_list.bk_name);
printf("\t\t%s",bk_list.bk_author);
printf("\t\t%d",bk_list.pages);
printf("\t\t\t%.2f",bk_list.price);
printf("\n");
}
getch();
fclose(fpD);
}
int edit(){ //edit of book 
char name[30];
FILE *fpD;
FILE *fpW;
fpD = fopen("library.bin","rb");
fpW = fopen("temp.bin","wb");
system("cls");
system("color F1");
getch();
printf("\n\t\t\t**********EDIT BOOK**********\n\n Enter the name of the book to edit: \n");
scanf("%s",name);
while(fread(&bk_list, sizeof(bk_list),1,fpD) == 1){
if(strcmp(name,bk_list.bk_name) != 0){
fwrite(&bk_list, sizeof(bk_list),1,fpW);
}
}
printf("New Name: \n");
scanf("%s",bk_list.bk_name);
printf("New Author: \n");
scanf("%s",bk_list.bk_author);
printf("New Page: \n");
scanf("%d",&bk_list.pages);
printf("New Price: \n");
scanf("%lf",&bk_list.price);
fwrite(&bk_list, sizeof(bk_list),1,fpW);
fclose(fpD);
fclose(fpW);
remove("library.bin");
rename("temp.bin","library.bin");
printf("EDIT SUCCESSFUL\n");
getch();
}
int search(){ //search of book
int found=0,name_length,i;
char bk_query[30],name[30];
system("cls");
system("color 02");
printf("Enter the book name to be searched:\n");
scanf("%s",bk_query);
FILE *fpS;
fpS=fopen("library.bin","rb");
getch();
name_length=strlen(bk_query);
while(fread(&bk_list,sizeof(bk_list),1,fpS)==1){
for(i=0;i<name_length;i++){
name[i]=bk_list.bk_name[i];
name[name_length]='\0';
}
if(strcmp(name,bk_query)==0){ //if name of book is not found it can be searched by either pg no, author or price
printf("Book Name:%s\nBook Author:%s\nBook Pages:%d\nBook Price:%.2f\n",bk_list.bk_name,bk_list.bk_author,bk_list.pages,bk_list.price);
found++;
}
}
if(found==0){
printf("No matches found!!\n");
}
printf("\n");
fclose(fpS);
getch();
}
int delete(){ //deletation of book from directory 
char book_name[50], flag = 0;
int i,j;
FILE *fpD, *fpW;
system("cls");
getch();
//heading();
fpD = fopen("library.bin","rb");
if(fpD == NULL){
printf("Unable to get the record\n");
}
fpW = fopen("temp.bin","wb");
printf("Enter the book to be deleted:\n");
scanf("%s",&book_name);
while(fread(&bk_list, sizeof(bk_list),1,fpD) == 1){
if(strcmp(book_name,bk_list.bk_name) != 0){
fwrite(&bk_list, sizeof(bk_list),1,fpW);
}
else{
printf("Book Deleted\n");
flag=1;
}
}
if(flag==0){
printf("No such book exist\n");
}
fclose(fpD);
fclose(fpW);
remove("library.bin");
rename("temp.bin","library.bin");
getch();
}