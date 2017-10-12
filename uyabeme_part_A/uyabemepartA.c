// uyabemepartA.c : Defines the entry point for the console application.
/*
Author: Kenneth Uyabeme
Date: October 9th 2017
Last Revision:
Limitations/Assumptions: 
1) Every customer has a first and last name.
2) Every customer has a cell and home phone number.
3) User can put in any string as the address. This program does not check to see if the address is valid. 
4) User inputs a correct set of characters for a phone number. This program does not check to see if the phone number is valid.
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
char * enter_number_message = "Please enter the number.\n";
char * enter_address_message = "Please enter the address.\n";
char * enter_first_name_message = "Please enter their first name.\n";
char * enter_last_name_message = "Now enter their last name.\n";
char * enter_home_phone_message = "Now enter their homephone number.\n";
char * enter_cell_phone_message = "Now enter their cellphone number.\n";
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
	struct full_name * customer_name;
	struct phone_numbers *customer_phone_numbers;
	char * customer_address;
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

/*This function
1) requests a number from the user(could be home or cell)
2) returns a pointer to the number which is stored as a char array
*/
char * request_number();
/*This function
1) creates a pointer to a phone_number struct using malloc
2) using the request_number function gets the home and cell numbers 
3)returns the pointer to the phone number struct
*/
struct phone_numbers * request_phone_numbers();
/*This function:
1) Asks the user for an address 
2) Creates a pointer for the address using malloc
3) set the pointer to the address and returns the pointer
*/
char * request_address();

/*
This method
1) Given a pointer to an array of customer structs and the number of customers sorts the array in order of numbers*/
void name_sort(struct customer * customers, int number_of_customers);

/*This function
1) prints out all customer info 
*/
static void display_all_customers_info(struct customers* customer_from_user, int num_of_customers);

/*This method
1) Given a pointer to an array of customer structs makes all customers which have the same name are sorted
by their home phone number
*/
void number_sort(struct customer * customers, int number_of_customers);
/*
This method:
1)Asks the user for the number of customers they would like enter
2) returns the number
*/
/*This function gotten from
https://stackoverflow.com/questions/12646734/how-to-sort-an-array-of-string-alphabetically-case-sensitive-nonstandard-colla
1)Compares strings but does so with case insentivity so ABC and abc are seen as the same
2) Alright from the first feature, it is just the same "strcmp".
*/
int strcasecmp(const char *a, const char *b);
//Function definitions
//----------------------------------------------------------------------------------------------------


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
	printf(enter_first_name_message);//Ask for first name
	cus_full_name->first_name = request_name();//Setting first name
	printf(enter_last_name_message);//Ask for first name
	cus_full_name->last_name = request_name();//Setting last name
	return cus_full_name;
}
/*This method
1) requests a number from the user(could be home or cell)
2)request for a location in memory to store that number and stores the number
2) returns the pointer to that location in memory.
*/
char * request_number() {
	char user_input_buffer[USER_INPUT_BUFFER_SIZE]; // input from user
	char * number; // number to be returned
	//printf(enter_number_message);//Asking user for a number
	fgets(user_input_buffer, sizeof(user_input_buffer), stdin);
	number = (char *)malloc(strlen(user_input_buffer) * sizeof(char) + ONE); // requesting memory to store number
	if (!number)
	{
		printf("Memory allocation for number pointer failed.\n");
		exit(1);
	}
	strcpy(number, user_input_buffer);//Sets the pointer to point to the name
	return number;

}
/*This function
1) creates a pointer to a phone_number struct using malloc
2) using the request_number function gets the home and cell numbers
3)returns the pointer to the phone number struct
*/
struct phone_numbers * request_phone_numbers(){
	struct phone_numbers * cus_phone_numbers;
	cus_phone_numbers = (struct phone_numbers *) malloc(sizeof(struct phone_numbers)); 
	if (!cus_phone_numbers)
	{
		printf("Memory allocation for phone_numbers pointer failed");
		exit(1);
	}
	printf(enter_home_phone_message); //Ask for homephone number
	cus_phone_numbers->home = request_number();
	printf(enter_cell_phone_message); //Ask for cellphone number
	cus_phone_numbers->cell = request_number();
	return cus_phone_numbers;
}

/*This function:
1) Asks the user for an address
2) Creates a pointer for the address using malloc
3) set the pointer to the address and returns the pointer
*/
char * request_address() {
	char user_input_buffer[USER_INPUT_BUFFER_SIZE];//User input buffer
	char * cus_address; //pointer to the wherer the address will be stored

	printf(enter_address_message);//Asking user for a address
	fgets(user_input_buffer, sizeof(user_input_buffer), stdin);
	cus_address = (char *)malloc(strlen(user_input_buffer) * sizeof(char) + ONE); // requesting memory to store number
	if (!cus_address) {
		printf("Memory allocatoin for cus_address failed.\n");
		exit(1);
	}

	strcpy(cus_address, user_input_buffer);
	return cus_address;
}
/*This method
1) Given a pointer to an array of customer structs sorts the array in order of home phone numbers
*/
void name_sort(struct customer * customers, int number_of_customers) {
	int i, j; // counters
	struct customer temp;
	
	for (i = 0; i <= number_of_customers-1; i++) {
		for (j = i+1; j <= number_of_customers-1; j++){
			if (strcasecmp(customers[i].customer_name->last_name, customers[j].customer_name->last_name)> 0)
			{
				temp = customers[i];
				customers[i] = customers[j];
				customers[j] = temp;
			}
		}
	}
}

/*This function
1) prints out all customer info
*/
static void display_all_customers_info(struct customer* customers_from_user, int num_of_customers) {
	int i; // counter
	for (i = 0; i < num_of_customers; i++)
	{
		printf("Customer %d\n Name:%s      %sHomePhone: %sCellPhone: %sAddress: %s\n",i+1,customers_from_user[i].customer_name->first_name, 
			customers_from_user[i].customer_name->last_name,
			customers_from_user[i].customer_phone_numbers->home,
			customers_from_user[i].customer_phone_numbers->cell,
			customers_from_user[i].customer_address);
	}
}
/*This function gotten from 
https://stackoverflow.com/questions/12646734/how-to-sort-an-array-of-string-alphabetically-case-sensitive-nonstandard-colla
1)Compares strings but does so with case insentivity so ABC and abc are seen as the same
2) Alright from the first feature, it is just the same "strcmp".
*/
int strcasecmp(const char *a, const char *b) {
	while (*a && *b) {
		if (tolower(*a) != tolower(*b)) {
			break;
		}
		++a;
		++b;
	}
	return tolower(*a) - tolower(*b);
}

/*This method
1) Given a pointer to an array of customer structs makes all customers which have the same name are sorted
by their home phone number
*/
void number_sort(struct customer * customers, int number_of_customers) {
	int i, j; // counters
	struct customer temp;

	for (i = 0; i <= number_of_customers - 1; i++) {
		for (j = i + 1; j <= number_of_customers - 1; j++) {
			if (strcasecmp(customers[i].customer_name->last_name, customers[j].customer_name->last_name)== 0)
			{
				if (strcasecmp(customers[i].customer_phone_numbers->home, customers[j].customer_phone_numbers->home) > 0){
					temp = customers[i];
					customers[i] = customers[j];
					customers[j] = temp;
				}
			}
		}
	}
}
//Program main
//-------------------------------------------------------
int main()
{
	struct customer * customers; //pointer to the array of customers
	int number_of_customers; 
	int i; //counter
	number_of_customers =  request_for_num_of_cus();//Asks for the number of customers and sets cusomters to be a 
	//pointer to location in memory that can hold that many customer structs.
	
	customers = allocate_memory_for_cus(number_of_customers);
	for (i = 0; i < number_of_customers; i++) {
		customers[i].customer_name = request_cus_full_name();
		customers[i].customer_phone_numbers = request_phone_numbers();
		customers[i].customer_address = request_address();

	}
	 
	display_all_customers_info(customers, number_of_customers);
	name_sort(customers,number_of_customers);
	printf("After name sorting\n");
	display_all_customers_info(customers, number_of_customers);
	number_sort(customers, number_of_customers);
	printf("After number sorting\n");
	display_all_customers_info(customers, number_of_customers);
	
	//Releasing the block memory of being used
	for ( i = 0; i < number_of_customers; i++)
	{
		free(customers[i].customer_name->first_name);
		free(customers[i].customer_name->last_name);
		free(customers[i].customer_name);
		free(customers[i].customer_phone_numbers->cell);
		free(customers[i].customer_phone_numbers->home);
		free(customers[i].customer_phone_numbers);
		free(customers[i].customer_address);
		free(customers[i]);
	}
	free(customers);
	while (1);
    return 0;
}

