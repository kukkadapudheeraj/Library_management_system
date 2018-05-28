#include<stdio.h>
#include<stdlib.h>
#include<string.h>
struct library
{
	int stu_id;
	char username[256];
	char password[256];
}totalUsers[500];
struct book
{
	int book_id;
	char title[256];
	char author[256];
	int noC;
	int issued_stu_id[500];
	int tot_issue;
}totalBooks[500];
static int bookCount = 0;
static int userCount = 0;
void copydetails()
{
	FILE *fp;
	fp=fopen("add_books1.dat","r");
	while(fscanf(fp,"%d %s %s %d",&((totalBooks[bookCount]).book_id),((totalBooks[bookCount]).title),((totalBooks[bookCount]).author),&(totalBooks[bookCount].noC))!=EOF)
	{
		bookCount++;
	}
	fclose(fp);
	FILE *pr;
	pr=fopen("user1.dat","r");
	while(fscanf(pr,"%d %s %s",&(totalUsers[userCount].stu_id),&(totalUsers[userCount].username),&(totalUsers[userCount].password))!=EOF)
	{
		userCount++;
	}
	fclose(pr);
}
void addBookDetails()
{
	FILE *fp;
	fp=fopen("add_books1.dat","a");
	printf("Enter book Id :\n ");
	scanf("%d",&((totalBooks[bookCount]).book_id));
	printf("Enter Title : \n");
	scanf("%s",((totalBooks[bookCount]).title));
	printf("Enter Author : \n");
	scanf("%s",((totalBooks[bookCount]).author));
	printf("Enter number of copies :\n ");
	scanf("%d",&(totalBooks[bookCount].noC));
	fprintf(fp,"%d %s %s %d\n",(totalBooks[bookCount]).book_id,(totalBooks[bookCount]).title,(totalBooks[bookCount]).author,(totalBooks[bookCount]).noC);
	totalBooks[bookCount].tot_issue = 0;
	fclose(fp);
	printf("Record added successfully\n");
	bookCount++;
	return;
}
void addMember()
{
	
	FILE *pr;
	pr=fopen("user1.dat","a+");
	printf("Enter student id :\n ");
	scanf("%d",&(totalUsers[userCount].stu_id));
	printf("Enter Username : \n");
	scanf("%s",&(totalUsers[userCount].username));
	printf("Enter password : \n");
	scanf("%s",&(totalUsers[userCount].password));
	fprintf(pr,"%d  %s  %s\n",totalUsers[userCount].stu_id,totalUsers[userCount].username,totalUsers[userCount].password);
	userCount++;
	fclose(pr);
	return;
}
void librarian()
{
	
	while(1)
	{
		printf("Enter 1 for adding book.\n");
		printf("Enter 2 for adding User.\n");
		printf("Enter 3 for going back.\n");
	int type;
	scanf("%d",&type);
	
		switch(type)
		{
			case 1:
				addBookDetails();
			break;
			
			case 2:
				addMember();
			break;
			
			case 3:
			return;
			
			default:
			printf("Wrong choice. Try again\n");
		}
	}
}

int user()
{
	printf("Enter credentials to verify \n");
	char user[256] = {0};
	char pass[256] = {0};
	printf("Enter Username : \n");
	scanf("%s",user);
	printf("Enter password : \n");
	scanf("%s",pass);
	/* check if username and password is correct or not */
	int i;
	for(i = 0;i<userCount;i++)
	{
		if((strcmp(totalUsers[i].password, pass) == 0) && (strcmp(totalUsers[i].username, user) == 0))
		return totalUsers[i].stu_id;
	}
	return -1;
}
void issue(int stuID)
{
	printf("Enter book id : ");
	int bookID;
	scanf("%d",&bookID);
	/* issue book to student */
	int i =0;
	for(i = 0;i<bookCount;i++)
	{
		if(totalBooks[i].book_id == bookID)
		{
			totalBooks[i].issued_stu_id[totalBooks[i].tot_issue] = stuID;
			totalBooks[i].tot_issue += 1;
			printf("Book issued to student\n");
			return;
			
		}
	}
	printf("invalid book id\n");
	return;
}
void returnn(int stuID)
{
	printf("Enter book id : ");
	int bookID;
	scanf("%d",&bookID);
	int i =0;
	for(i = 0;i<bookCount;i++)
	{
		if(totalBooks[i].book_id == bookID)
		{
			 int k=0;
			 for(k=0;k<totalBooks[i].tot_issue;k++)
			 {
			 	if(totalBooks[i].issued_stu_id[k]==stuID)
			 	{
			 	totalBooks[i].issued_stu_id[k]=-1;
			//totalBooks[i].issued_stu_id[totalBooks[i].tot_issue] = -1;
			printf("Book returned by student\n");
			return;
		}
	}
		}
	}
	printf("invalid book id\n");
	return;
}
void query(int stuID)
{
	printf("Select choice \n");
	int ch;
	printf("1. List of students to this book issued \n");
	printf("2. List of books issued to this student \n");
	scanf("%d",&ch);
	if(ch == 1)
	{
		printf("Enter book id : ");
		int book_id;
		scanf("%d",&book_id);
		int i = 0;
		for(i = 0; i < bookCount; i++)
		{
			if(totalBooks[i].book_id == book_id)
			{
				int j;
				for(j = 0; j< totalBooks[i].tot_issue; j++)
				{
					if(totalBooks[i].issued_stu_id[j] != -1)
					printf("student id = %d\n",totalBooks[i].issued_stu_id[j]);
				}
				return;
			}
		}
	}
	else if(ch == 2)
	{
		printf("Enter student id : ");
		int stu_id;
		scanf("%d",&stu_id);
		int i,j;
		for(i = 0; i < bookCount; i++)
		{
			//printf("1st\n");
				for(j = 0; j< totalBooks[i].tot_issue; j++)
				{
				//	printf("%d\n",totalBooks[i].issued_stu_id[j]);
					if(totalBooks[i].issued_stu_id[j] == stu_id)
					printf("book id = %d\n",totalBooks[i].book_id);
				}
			}
		return;
	}
	else
	{
		printf("Wrong choice\n");
	}
}
void userMenu(int stuID)
{
	printf("Enter 1 for issue. Enter 2 for Return. Enter 3 for Query.\n");
	int choice;
	scanf("%d",&choice);
	switch(choice)
	{
		case 1:
			issue(stuID);
			break;
			
		case 2:
			returnn(stuID);
			break;
			
		case 3:
			query(stuID);
			break;
			
		default:
			printf("invalid choice\n");
	}
}
int main()
{
	int res;
	copydetails();
	while(1)
	{
		int type;
		printf("Who are you?\n");
		printf("1.Librarian\n");
		printf("2.User\n");
		printf("3.exit\n");
		scanf("%d",&type);
		switch(type)
		{
			case 1:
				librarian();
				break;
			
			case 2:
				res = user();
				if(res== -1)
				{
					printf("Error : invalid username/password. try again.\n");
					break;
				}
				else
				printf("Login Succcessful\n");
				userMenu(res);
				break;
				
			case 3:
				exit(1);
				
			default:
				printf("Wrong Choice entered. Try again.\n");
				break;
		}
	}
}
