// uyabemepartA.c : Defines the entry point for the console application.
/*
Author: Kenneth Uyabeme
Date: October 9th 2017
Last Revision:
Limitations/Assumptions: 
1) Every customer has a first and last name.
2) Every customer has a cell and home phone number.
3) User can put in any string as the address. This program does not check to see if the address is valid. 
Notes: 
*/

//

#include "stdafx.h"
//Constants
//--------------------------------------------------
#define USER_INPUT_BUFFER_SIZE 50
#define ONE 1
//Global variables
//-----------------------------------
//Strings
char * enter_number_of_cus_message = "Please enter the number of customers you would like to save.\n";
char * enter_numof_char_in_name_message = "Please enter the number of characters in this name.\n";
char * enter_name_message = "Please enter the name.\n";

//Structs
//----------------------------------------------------
//struct for the cumstomer's name
struct full_name
{
	char * first_name;
	char *last_name;
};

//struct for the customer's phone number
struct phone_numbers
{
	char * home;
	char * cell;
};

struct customer
{
	struct name * customer_name;
	struct phone_number *customer_phone_number;
	char * address;
};

//Function prototypes 
//------------------------------------------------------------------------------
/*
This method:
1)Asks the user for the number of customers they would like enter
2) returns the number
*/
int request_for_num_of_cus();

/*This method:
1)Asks the user for the number of characters in customers name
2)Creates a pointer to a location in memory that can hold that many characters
3) Ask for the customer's name and stores the name in that location
*/
char * request_name();

/*This method
1) Given the a number of customers locates the amount of memory needed
2)Returns a pointer(to a customer struct array) to that memory locatoin
*/
struct customer * allocate_memory_for_cus(int num_of_customers);
/*This method 
1)creates a pointer to a full_name struct using malloc
2)using the "request_full_name" function sets the first name and last name memebers

*/
struct full_name * request_cus_full_name();

//Function definitions
//----------------------------------------------------------------------------------------------------
/*
This method:
1)Asks the user for the number of customers they would like enter
2) returns the number
*/


int request_for_num_of_cus() {
	char user_input_buffer[USER_INPUT_BUFFER_SIZE];// buffer for userinput
	
	int amount_of_cus;// the of customers gotten for the user

	//Getting user input for number of customers
	printf(enter_number_of_cus_message);
	fgets(user_input_buffer, sizeof(user_input_buffer), stdin);
	//*** ERORR HANDLING HERE!!!!**

	amount_of_cus = atoi(user_input_buffer);
	
	return amount_of_cus;
}
/*This method
1) Given the a number of customers locates the amount of memory needed
2)Returns a pointer(to a customer struct array) to that memory locatoin
*/
struct customer * allocate_memory_for_cus(int num_of_customers) {
	struct customer * customers;// pointer to hold customer structs
	customers = (struct customer *) malloc(num_of_customers * sizeof(struct customer));
	if (!customers)
	{
		printf("Memory allocation for customers pointer failed.\n");
		exit(1);
	}

	return customers;
}

/*This method:
1)Asks the user for the customers name (could be last or first)
2)Creates a pointer(to a string) to a location in memory that can hold as many characters as the length
of the name
3)Stores the name in that location.
4)returns the pointer 
*/
char * request_name(){
	char user_input_buffer[USER_INPUT_BUFFER_SIZE]; //buffer to store user_input
	char * name; //holds the name gotten from the user, could be the last or first name
	printf(enter_name_message); // Asking user for the name
	fgets(user_input_buffer, sizeof(user_input_buffer), stdin);
	//*** ERORR HANDLING HERE!!!!**

	name = (char *) malloc((strlen(user_input_buffer) + ONE) * sizeof(char)); //Getting the amount memory to hold the name
	if (!name)
	{
		printf("Memory allocation for name pointer failed.\n");
		exit(1);
	}
	strcpy(name,user_input_buffer);//Sets the pointer to point to the name
	return name;

}

/*This method
1)creates a pointer to a full_name struct using malloc
2)using the "request_name" function sets the first name and last name memebers

*/
struct full_name * request_cus_full_name() {
	struct full_name * cus_full_name; //customer's full name
	cus_full_name = (struct full_name *) malloc(sizeof(struct full_name));
	cus_full_name->first_name = request_name();//Setting first name
	cus_full_name->last_name = request_name();//Setting last name
	return cus_full_name;
}
//Program main
//-------------------------------------------------------
int main()
{
	struct customer * customers; //pointer to the array of customers
	int number_of_customers; 
	number_of_customers =  request_for_num_of_cus();//Asks for the number of customers and sets cusomters to be a 
	//pointer to location in memory that can hold that many customer structs.
	
	customers = allocate_memory_for_cus(number_of_customers);
	printf("Now please enter customer %d full name starting with the firstname then the lastname\n");
	customers[0].customer_name = request_cus_full_name();
	



    return 0;
}

