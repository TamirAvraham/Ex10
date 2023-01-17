#include "Customer.h"

Customer::Customer(std::string name):_name(name)
{
}

Customer::Customer():_name()
{
}

double Customer::shoppingCartSum(std::string shoppingCartName)
{
	double sum = 0.0;
	auto cart = _shoppingCarts[shoppingCartName];
	for (auto item : *cart) {
		sum += item.totalPrice();
	}
	return sum;
}

double Customer::totalSum()
{
	double sum = 0.0;
	for (auto cart : _shoppingCarts) {
		sum += this->shoppingCartSum(cart.first);
	}
	return sum;
}

void Customer::createNewShoppingCart(std::string shoppingCartName)
{
	std::set<Item>* set=new std::set<Item>();
	std::pair<std::string, std::set<Item>*> inserted(shoppingCartName, set);
	_shoppingCarts.insert(inserted);
}

void Customer::addItem(Item item, std::string shoppingCartName)
{
	auto cart = _shoppingCarts[shoppingCartName];
	for (Item& itemInCart : *cart) {
		if (item==itemInCart)
		{
			itemInCart.setCount(item.getCount()+1);
			return;
		}
	}
	cart->insert(item);
}

void Customer::removeItem(Item item, std::string shoppingCartName)
{
	auto cart = _shoppingCarts[shoppingCartName];
	for (Item& itemInCart : *cart) {
		if (item == itemInCart)
		{
			if (item.getCount()==0)
			{
				cart->swap()
			}
			return;
		}
	}
	cart->insert(item);
}
