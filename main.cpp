#include"Customer.h"
#include "Store.h"
#include<map>
#include <string>
#include<iostream>

#define print(a) std::cout<<a<<'\n';
#define input(a) std::getline(std::cin, a);

int getOption() {
	int option = 0;
	std::cin >> option;
	getchar();//clearing buffer
	return option;
}
void option1buyIteamsFromStore(Store store, Customer& customer,std::string cartName) {
	int choice = 0;
	do {
		print("The items you can buy are: (0 to exit)\n" << store)
		choice = getOption();
		try
		{
			customer.addItem(store[choice], cartName);
		}
		catch (const std::exception& e)
		{
			print(e.what());
			return;
		}
	} while (choice != 0);
	
}
void option1selectShop(Customer& customer, std::string cartName) {
	std::string firstLine="Select the store to buy from :\n1. to buy in Shefa Isaschar(Super Market)\n2. to buy in MagshIKEA(Home products)\n3. to buy in MagshiPharm(Pharm and utils)\n4. Back to main menu";
	Store s1("Shefa Isaschar", "InventorySuperMarket.csv");
	Store s2("MagshIKEA", "InventoryIKEA.csv");
	Store s3("MagshiPharm", "InventoryPharm.csv");
	Store* send = nullptr;
	print(firstLine)
	int option = getOption();
	switch (option)
	{
	case 1:
		send = &s1;
		break;
	case 2:
		send = &s2;
		break;
	case 3:
		send = &s3;
		break;
	default:
		print("rerouting back to main menu")
		break;
	}
	option1buyIteamsFromStore(*send, customer, cartName);
}
void option1(Customer& customer) 
{
	std::string text="1. To create a new shopping cart\n2. Back to main menu";
	print(text);
	int option = getOption();
	switch (option)
	{
	case 1:
		print("enter the name of the shopping cart")
		std::getline(std::cin, text);//reduce reuse recycle thats how you get quick programs
		customer.createNewShoppingCart(text);
		option1selectShop(customer, text);
		break;
	default:
		print("rerouting back to main menu")
		break;
	}
}
void option2pickCart(Customer& customer) {
	print("Select Shopping Cart: (0 to exit)\n")
	int i = 1;
	std::map<int, std::string> cartsIndex;
	for (auto& element : customer.getCarts())
	{
		cartsIndex.insert({ i,element.first });
		print(i << ". " << element.first)
		i++;
	}
	int option = getOption();
	try
	{
		option1selectShop(customer, cartsIndex.at(option));
	}
	catch (const std::exception&)
	{
		print("rerouting back to main menu")
	}
}
void option2(Customer& customer) {
	std::string printText = "1. To create a new shopping cart\n2. Update existing shopping cart\n2. Back to main menu";
	print(printText);
	int option = getOption();
	switch (option)
	{
	case 1:
		print("enter the name of the shopping cart")
		input(printText)
		std::getline(std::cin, printText);
		customer.createNewShoppingCart(printText);
		option1selectShop(customer, printText);
	case 2:
		option2pickCart(customer);
		break;
	default:
		print("rerouting back to main menu")
		break;
	}
}
Customer GetCustomer(std::map<std::string, Customer>& customers,std::string name) {
	Customer ret(name);
	customers.insert({ name,ret });
	return ret;
}
int main()
{

	std::map<std::string, Customer> abcCustomers;

	

	std::string textForFirstPrint = "Welcome to MagshiMart!\n1. To sign as customer and buy items\n2. To update existing customer's items\n3. To print the customer who pays the most\n4. To exit";
	int option = 0;
	double max = -100000000000;
	std::string nameOfShame = "tamir";
	

	do
	{
		print(textForFirstPrint);
		option = getOption();
		switch (option)
		{
		case 1:
			print("enter your name")
			input(nameOfShame)
			GetCustomer(abcCustomers,nameOfShame);
			option1(abcCustomers.at(nameOfShame));
			break;
		case 2:
			print("enter your name")
			input(nameOfShame)
			option2(abcCustomers.at(nameOfShame));
			break;
		case 3:
			max = 0;
			for (auto& pair:abcCustomers)
			{
				auto sum = pair.second.totalSum();
				if (max<sum)
				{
					max = sum;
					nameOfShame = pair.first;
				}
			}
			print(nameOfShame<<" payed: "<<max)
		default:
			break;
		}
	} while (option!=4);
	return 0;
}