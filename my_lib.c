#include <stdio.h>//input output methods
#include <string.h>//contains string methods
#include <stdlib.h>//contains memory allocation methods
#include <windows.h>//contains the sleep function
#include <conio.h>//used for console applications such as cprintf and cscanf
#include <ctype.h>
//this program takes into account that there is only one copy of the books

//functions performed under the library system
void mainmenu();
void add_b();
void gbookdetails();
void storebooks();
void delete_b();
int search_b();
void issue_b();
void view_b();
void edit_b();
void closep();
void sbookdetails();
void gotoxy(int a,int b);
void issue_bview();
COORD coord;

//global variables

//book details
typedef struct{
    int id;
    char *cate;
    int pages;
    char title[20];
    char author[20];
}book;
book book1;
book *bp=&book1;

//issue details
typedef struct{
book book2;
char name[20];
}issue;
issue one;
issue *b2p=&one;
book *ip=&(one.book2);
FILE *p,*p1,*p2;
 //the main menu


//the main menu of the function
void mainmenu(){
    printf("****WELCOME TO THE LIBRARY SYSTEM****\n\n");
    gotoxy(2,2);
printf("  CATEGORIES\n");
printf(" 1.add book\n 2.delete book\n 3.search book\n 4.issue book\n 5.view all books\n 6.edit books\n 7.close application\n\n");
printf("SELECT A NUMBER: ");
printf("\n");
//selecting the function to perform
switch(getch()){
 case '1':
     system("cls");
     add_b();
     break;
case '2':
    system("cls");
    delete_b();
    break;
 case '3':
     system("cls");
  search_b();
  break;
 case '4':
     system("cls");
    printf("SELECT THE ACTION TO PERFORM\n1.read issued books\n2.issue a book\n");
    int a;
    scanf("%d",&a);
    if(a==1){system("cls");issue_bview();}
    else if(a==2){system("cls");issue_b();}
    break;
 case '5':
     system("cls");
     view_b();
     break;
 case '6':
     system("cls");
    edit_b();
     break;
 case '7':
     system("cls");
    closep();
}
}

//password function(checks if the password input works to somehow restore security)
void password(){
printf("ENTER THE PASSWORD\n");
char pass[10];
gets(pass);
if(strcmp(pass,"libsystem")==0){system("cls");mainmenu();}
else{system("cls");printf("YOU ENTERED THE WRONG PASSWORD! PLEASE TRY AGAIN\n");password();}
}

//adding books(contains setting books details and storing the books to the file)
void add_b(){
    printf("    ADDING FUNCTION    \n");
    printf("select a category\n 1.computer\n 2.electrical\n 3.mechanical\n 4.civil\n\n");
    printf("enter book category");
    int select2;
    scanf("%d",&select2);
    //selecting the category of the book
    switch(select2){
case 1:
    system("cls");
    book1.cate="computer";
    break;
 case 2:
    system("cls");
    book1.cate="electrical";
    break;
case 3:
    system("cls");
    book1.cate="mechanical";
    break;
case 4:
    system("cls");
    book1.cate="civil";
    }
    sbookdetails();
    storebooks();
    printf("PRESS ENTER TO ADD MORE BOOKS AND ESC TO GO BACK TO THE MAIN MENU ");
if(getch()==13){system("cls");add_b();}
else if(getch()==27){system("cls");mainmenu();}
else printf("something went wrong try again later!");
}

//setting the book details(attributes of the books)
void sbookdetails(){

int f;
int a;
printf("id: ");scanf("%d",&a);
p=fopen("book.text","rb");
//searching for the id in the file
while(fread(bp,sizeof(book1),1,p)==1){
    if(a==bp->id){
    f=1;
    break;
}
}
if(f!=1){
bp->id=a;
printf("category: %s\n",book1.cate);
printf("pages: ");scanf("%d",&book1.pages);
printf("title: ");scanf("%s",bp->title);
printf("author: ");scanf("%s",bp->author);

}
else{
printf("ID ALREADY EXISTS PLEASE TRY AGAIN(y/n)");
char d;
scanf("%s",&d);
if(d=='y'){
        system("cls");
        sbookdetails();}
        else{system("cls");mainmenu();}
}
fclose(p);
}

//writing the book details with the files(appending)
void storebooks(){
p=fopen("book.text","ab");
fseek(p,0,SEEK_END);//moving the pointer
fwrite(bp,sizeof(book1),1,p);
fclose(p);
}



//deleting books from the file
void delete_b(){
    printf("     DELECTING FUNCTION    \n");
    int a;
    char e;
     // getting the id for the book to be deleted
printf("enter ID of the book to be deleted ");
int d;
scanf("%d",&d);
p=fopen("book.text","rb");
while(fread(bp,sizeof(book1),1,p)==1){
    if(bp->id==d){
        printf("Id has been found\ndo you want continue deleting %s by %s (y/n) ",bp->title,bp->author);
        scanf("%s",&e);
        a=1;
        break;
}
}
if(e=='y'){
        p1=fopen("temp.text","wb");
        fseek(p,0,SEEK_SET);
    while(fread(bp,sizeof(book1),1,p)==1){
        if(bp->id!=d){//storing the other books in a temporary file
            fwrite(bp,sizeof(book1),1,p1);
        }
}
    fclose(p);
    fclose(p1);
    remove("book.text");
    rename("temp.text","book.text");
    system("cls");
    printf("DELETION IS COMPLETE\n");
    printf("PRESS ENTER TO DELETE ANOTHER BOOK OR\nESCAPE TO RETURN TO THE MAINMENU!");
if(getch()==13){system("cls");delete_b();}
else if(getch()==27){system("cls");mainmenu();}
else {printf("something went wrong try again later!");}
    }
    else{system("cls");mainmenu();}
if(a!=1){
        system("cls");
    printf("SORRY! THE ID YOU PROVIDED CANNOT BE FOUND PLEASE TRY AGAIN\n\nPRESS ENTER TO TRY AGAIN \n");
    if(getch()==13){system("cls");delete_b();}

if(getch()==13){
        system("cls");
        delete_b();
}
else if(getch()==27){
    system("cls");
    mainmenu();
}
}
}



//searching the file for a particular book using the book id
int search_b(){
    //user input
    int found;
    printf("enter the id of the book you want to search ");
int a;
scanf("%d",&a);
p=fopen("book.text","rb");
while(fread(bp,sizeof(book1),1,p)==1){//searching for the book using the id
      if(bp->id==a){
        printf("\nID FOUND!\n\ntitle: %s\nauthor: %s\npages: %d\nid: %d\ncategory: %s\n",bp->title,bp->author,bp->pages,bp->id,bp->cate);
        found=1;
        break;
      }
}
if(found!=1)printf("\nBOOK NOT FOUND!\n");
printf("PRESS ENTER TO SEARCH FOR ANOTHER BOOK OR ESCAPE TO RETURN TO THE MAINMENU ");
  if(getch()==13){system("cls");search_b();}
else if(getch()==27){system("cls");mainmenu();}
else printf("something went wrong try again later!");
fclose(p);
return found;
}


//issuing the book to a library user and storing the issuing details to a separate file
void issue_b(){

    //view all books available
    printf("    ISSUING BOOKS    \n");
    int a;
    int found;
    printf("enter the book id to be issued\n");
scanf("%d",&a);
p=fopen("book.text","rb");
//searching for the book id
while(fread(&book1,sizeof(book1),1,p)==1){
      if(a==bp->id){
        found=1;
        break;
      }
}
//issuing the book
if(found==1){
printf("issuing the book...\n");
fseek(p,(long long signed)-sizeof(book),SEEK_CUR);//changing the pointer position from the end of the book details to its beginning
fread(ip,sizeof(book1),1,p);
printf("enter the name of the borrower ");
char name2[20];
scanf("%s",&name2);
strcpy(one.name,name2);
printf("you are about to issue %s book of id %d to %s(y/n) ",ip->title,ip->id,b2p->name);
char in;
scanf("%s",&in);
if(in=='y'){
p2=fopen("issuing.text","ab");
fwrite(&one,sizeof(one),1,p2);
fclose(p2);
fclose(p);
printf("YOU HAVE ISSUED %s BOOK OF ID %d TO %s\n",ip->title,ip->id,b2p->name);

}
else if(getch()=='n'){system("cls");mainmenu();}
//confirming the books issued
}
else{
    system("cls");
    printf("ID NOT FOUND\n\n(y/n)");
}
printf("DO YOU WANT TO ISSUE ANOTHER BOOK? (y/n)");
char b;
scanf("%s",&b);
if(b=='y'){
    system("cls");
    issue_b();
}
else{system("cls");mainmenu();}
}


//viewing all the books stored in the file
void view_b(){
        system("cls");
        printf("ID CATEGORY    TITLE         author       pages\n\n");
    p=fopen("book.text","rb");
    int a =1;
    while(fread(bp,sizeof(book),1,p)==1){
        gotoxy(0,a);
        printf("%d",bp->id);
        gotoxy(3,a);
        printf("%s",bp->cate);
        gotoxy(15,a);
        printf("%s",bp->title);
        gotoxy(29,a);
        printf("%s",bp->author);
        gotoxy(42,a);
       printf("%d\n\n",bp->pages);
        a++;
}
printf("press ENTER to return to the main menu ");
if(getch()==13){
    system("cls");
    mainmenu();
}
}

//editing values of the books and updating the file
void edit_b(){
//getting user input on the id to be edited
printf("INPUT THE ID YOU WANT TO EDIT: ");
int a;
scanf("%d",&a);
//checking if the file exists in the file
p=fopen("book.text","rb+");
int found;
while(fread(bp,sizeof(book1),1,p)==1){
    if(a==bp->id){
    found=1;
    break;
    }
}
//getting the new details of the found id
if(found==1){
        system("cls");
    printf("ID FOUND! ENTER YOUR NEW DETAILS BELOW\n\n");
    printf("ID: %d\n",bp->id);
    printf("CATEGORY: %s\n",book1.cate);
    printf("TITLE: ");scanf("%s\n",&book1.title);
    printf("AUTHOR: ");scanf("%s",&book1.author);
    printf("PAGES: ");scanf("%d",&book1.pages);
    fseek(p,(long long int)-sizeof(book1),SEEK_CUR);
    fwrite(&book1,sizeof(book1),1,p);
    fclose(p);
    printf("YOUR BOOK HAS BEEN EDITED PRESS ENTER TO VIEW THE BOOK YOU HAVE EDITED");
    if(getch()==13){
        system("cls");
        view_b();
    }
}
else{
    system("cls");
    printf("ID NOT AVAILABLE!\n\nWAIT AS YOU ARE REDIRECTED TO THE MAIN MENU");
    char a;
    scanf("%c",&a);
    if(a=='\n'){
        Sleep(3000);
        system("cls");
        mainmenu();
    }
}
}


//exiting the program
void closep(){
printf("do you want to exit the application (y\n)");
char c;
scanf("%s",&c);
if(c=='y')system("cls");printf("  YOU HAVE EXITED THE APPLICATION  \n");printf("Do you want to return to the application(y/n)");
char d;
scanf("%s",&d);
if(d=='y'){
    system("cls");
mainmenu();
}
}
//viewing the books that have been issued in the library
void issue_bview(){
 system("cls");
        printf("ID CATEGORY    TITLE         AUTHOR       PAGES    NAME\n\n");
    p2=fopen("issuing.text","rb");
    int a =1;
    while(fread(b2p,sizeof(one),1,p2)==1){
        gotoxy(0,a);
        printf("%d",b2p->book2.id);
        gotoxy(3,a);
        printf("%s",b2p->book2.cate);
        gotoxy(15,a);
        printf("%s",ip->title);
        gotoxy(29,a);
        printf("%s",ip->author);
        gotoxy(42,a);
       printf("%d",ip->pages);
       gotoxy(50,a);
       printf("%s\n\n",b2p->name);
        a++;
}
printf("press ENTER to return to the main menu ");
if(getch()==13){
    system("cls");
    mainmenu();
}
}




//setting cursor position in the console
void gotoxy(int a,int b){
coord.X=a;coord.Y=b;
SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),coord);
}
int main(){
//the menu
password();
 }


















