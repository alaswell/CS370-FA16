//----------------------------------------------------
//CS370 Partial Code for PA1
//Authors: Leon, Rejina
//Students: Provide your own header here.
//----------------------------------------------------

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>


#define DEBUG 0

// Defining the records structure for Library Systems Book list
typedef struct _Book
{
  int ISBN;
  char Title[20];
  char Author[20];
  char Description[40];
  int CopiesAtCSU;
  
  
  struct _Book *next;
} Book;



//------------------------------------------------------
// Display the menu and return the user choices
char Menu(void)
{
char ch;
do{
    printf("\n Main Menu");
    printf("\n ------------------");
    printf("\n1- Add Book");
    printf("\n2- Delete Book");
    printf("\n3- List All Books");
    printf("\n4- Save data to file & exit");
    printf("\n -------------------------------");
    printf("\n Enter your choice(1-4):");

    char line[80];
    fgets(line, 80, stdin);
    ch = *line;


} while(ch>'4' || ch<'1');
return ch;
}




//------------------------------------------------------
//Function to Add Book info to the linked list
//@parameters :
// listHead : Pointer to the head of the list. [Q1: We need a pointer to pointer in this function, Why?]
// ISBN,Author,Title, Description CopiesAtCsu : Book's ISBN,Author, Title, CopiesAtCsu and Description respectively
// sortIndx : The field number used for sorting the list, 1 is ISBN, 2 is Title, and 3 is Author.

int AddBook(Book **listHead,int ISBN,char *Title,char *Author, int CopiesAtCsu, char *description,  int sortIndx)
{
// [Q2: This function has too many value parameters ISBN,Title,Author,... etc. Is there a better way to pass 
//  those values? if Yes, write a prototype for it]
Book *current=*listHead,*prev,*newNode;
int locFound=0;

// Your code to check if Book ISBN already exists

//.......Your code Goes here................





// Code to create new node and populate it with data.
   
//.......Your code Goes here.................






// Code  to add to an empty list

//.......Your code Goes here.................







// code to find the appropriate position of the new record in the list based on
// the sorting field.
// Hint:  You should keep track of pointers to the previous and next 
// nodes you will use to insert a new record
 	
current=*listHead;
prev=current;



//.......Your code Goes here.................









	
// Now to add the new record : 
// there are 2 cases:
// 1- if the record is to be inserted at the beginning of the list
// 		Hint: you need to change the list header pointer	

// 2-If not at the beginning, then it would be inserted after some record
//	   based on the order. 




//.......Your code Goes here.................


return 1;


}
	




//------------------------------------------------------
// Function to read books' info from a file and add them to the
//  Books linked list sorted based on the sortIndx
// Use the function AddBook
//@ Params:
// fileName : the file to read from. The file contains info separated by 
//		commas and/or spaces  and each line belongs to a book.
// list: Pointer to the head of the list. [Q3: We need a pointer to pointer in this function, Why?]
// @Return:
//  1 on success and 0 on failure. 
int
readfile (char *fileName, Book **list, int sortIndx)
{



  FILE *fd;
  char Title[20],Author[20],Description[40];
  int ISBN;
  int CopiesAtCsu;

  if (DEBUG)
    printf ("Entering readfile\n");

  fd = fopen (fileName, "r");
  if (!fd){
	printf("\n Error reading input file");
    	return 0;
	}
	
// loop through the file and read the data
// line by line,  call the AddBook function to add the book to the list	
	
//.......Your code Goes here.................



    
 //close the file   
  fclose (fd);
 return 1;
}







//------------------------------------------------------
//function to write data from the list to a text file
// fileName : the file to Write to. Each record of the data is written as separated by commas and/or spaces
//               and each record is written in a separate line. 

// list: The head of the list pointer. Q4: We didn't use a pointer to pointer in this function, Why?
void writefile (char *fileName, Book *list)
{



  FILE *fd;
  Book *p=list;
  if (DEBUG)
    printf ("Entering writefile\n");
  fd = fopen (fileName, "w");
 
// loop through THE LINKED list and write the records to the file
// line by line
  
//.......Your code Goes here.................


  fclose (fd);
  return;

}






// Function to delete a book data from the list using his ISBN
//@ Params:
//
// BookList: Pointer to the head of the 
// [Q5: We need a pointer to pointer in this function, Why?]
// id : The ISBN of the book whose data is to be deleted.
// @Return:
//  1 on success and 0 on failure. 
//------------------------------------------------------

int deleteBook(int ISBN,Book **BookList)
{

	Book *current=*BookList,*prev;
	
	// [what about deleting from an empty list? Handle appropriately.]
	
	//.......Your code Goes here.................
		
		
		
		
		
		
	// what if the record to be deleted is at the head of the list
	
	//.......Your code Goes here.................
		
	
	
	
	
	
	
	
	// Not the in the front, OK we need to find it and keep track of
	// the pointers to the previous and next records
	// then delete it if found.

	while(current!=NULL)
	{
		if(current->ISBN==ISBN)
		{
		 prev->next=current->next;
		 free(current);
		return 1;
		 
		}
	prev=current;
	current=current->next;
	}
	
	
// Not found! OK this means delete wasn't successful. Return 0.
printf("\n Book ISBN not found !");
return 0;

}






//------------------------------------------------------
//function to display Books' info
//@params:
// Pointer to the header of the list
void displayBookList(Book *listHead)
{
Book *p=listHead;
printf("\n%-9s %-20s %-20s %-10s %-40s","Book_ISBN","Title","Author"," Copies@CSU","    Description");
printf("\n------------------------------------------------------------------------------------------------------------------");
while(p!=NULL)
   {  printf("\n%-9d %-20s %-20s %-10d %-40s",p->ISBN,p->Title,p->Author,p->CopiesAtCsu,p->Description);
	p=p->next;

	}

//Adjust it to make sure it display well on CS lab machine

}


//------------------------------------------------------
// Utility function:
// alternative to scanf.
// store white spaces except \n to char*
// scanf neglects characters after it the space
void getText(char *message, char *variable, int size)
{
    printf("\n %s: ", message);
    fgets(variable, sizeof(char) * size, stdin);
    sscanf(variable, "%[^\n]", variable);
}

//------------------------------------------------------
//Main function:
// parses the command line parameters, defines the header of the list,
// initializes the list with data from the file provided with the command line
// then displays the menu, and calls other functions based
// on user choices.


int main(int argc, char **argv)
{
char ch;
char fileName[30];
int sort=0;
int c;
int sortIndx=1;
Book *BookList=NULL;  // the list header is declared and initialized with NULL
int ISBN;
char Title[20],Author[20],Description[40];
int CopiesAtCsu;


// start parsing the command line parameters

  opterr = 0;
  if(argc<2) {
  fprintf (stderr, "Usage: options -f inputfile.txt [-s fileName] [-a] \n");
	return 0;
  }
  while ((c = getopt (argc, argv, "f:s:a")) != -1)
    switch (c)
      {
      case 'f':   // the user provided the file and its name should be in the optarg
             // Complete the code to get the file name 
	          // ..............complete this code.....................
	          
	          
	          
	          

	break;
      case 's':  // the user provided the sorting field, we need to check the optarg
      			// and set the sortIndx accordingly 
	
	
	if (strcmp(optarg,"ISBN")==0) sortIndx=1;
	else if (strcmp(optarg,"Title")==0)  sortIndx=2;
	   else if  //  ................ complete this if  statement........
	   
		      else printf("\n unknown index field, default assumed");
			
			
	break;
      case 'a':   // the sorting direction (ascending or descending)
                  //is not used in this code, you need to figure out how and where to use it ?
	sort = 1;
	break;
     
      case '?':   //there was an error
	 if (optopt == 'f' || optopt == 's' )
          fprintf (stderr, "Option -%c requires an argument.\n", optopt);

      	fprintf (stderr, "Usage: options -f inputfile.txt [-s Title] [-a] \n");
	return 0;
     
      }





 // now initialize the list with data from the file provided by the user
 
 // .......... your code goes here..........................
 



 
 
 
do{

ch=Menu();

  switch (ch)
	  {
	  case '1': printf("\n Enter Book info. to add ");
		    getText("Title", Title, 20);
    getText("Author", Author, 20);
    getText("Description", Description, 40);
    printf("\n ISBN:");
    scanf("%d",&ISBN);
    printf("\n copies at CSU:");
    scanf("%d",&CopiesAtCsu);
    getchar();

			 // call the function AddBook with these inputs
			 //......complete the function call.................
			 
			  AddBook(............................);
			  
		    break;
	  case '2': printf("\n Enter Book ISBN to delete :");
			scanf("%d",&ISBN);
			  // call the function delete record with this input id 
			 //......complete the function call.................
			deleteRecord(....................);
			
		    break;
	  case '3': 
			displayBookList(BookList);
		    break;
	  case '4': 
			writefile (fileName, BookList);
		    break;
	 
	}

}while(ch!='4');

}

