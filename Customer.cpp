#include "Customer.h"

Customer::Customer(std::string name):_name(name)
{
}

Customer::Customer():_name()
{
}

Customer::~Customer()
{
}

double Customer::shoppingCartSum(std::string shoppingCartName) const
{
	double sum = 0.0;
	auto cart = _shoppingCarts.at(shoppingCartName);
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
	_shoppingCarts.insert({ shoppingCartName, set });
}

void Customer::addItem(Item item, std::string shoppingCartName)
{
	auto cart = _shoppingCarts.at(shoppingCartName);
	for (Item itemInCart : *cart) {
		if (item==itemInCart)
		{
			item = itemInCart;
			Item newItem = item;
			newItem.setCount(newItem.getCount() + 1);
			updateItemInSet(cart, item, newItem);
			return;
		}
	}
	cart->insert(item);
}

void Customer::removeItem(Item item, std::string shoppingCartName)
{
	auto cart = _shoppingCarts.at(shoppingCartName);
	for (Item itemInCart : *cart) {
		if (item == itemInCart)
		{
			item = itemInCart;
			if (item.getCount()<=1)
			{
				cart->erase(item);
				return;
			}
			Item newItem = item;
			newItem.setCount(newItem.getCount() - 1);
			updateItemInSet(cart, item, newItem);
			return;
		}
	}
	cart->insert(item);
}

std::string Customer::getName() const
{
	return _name;
}

std::set<Item>* Customer::getShoppingCart(std::string shoppingCartName)
{
	return _shoppingCarts.at(shoppingCartName);
}

void Customer::updateItemInSet(std::set<Item>* set, Item toUpdate, Item newItem)
{
	auto iterator = set->find(toUpdate);
	if (iterator!=set->end())
	{
		std::set<Item>::iterator iteratorToNewItem = iterator;
		iteratorToNewItem++;
		set->erase(iterator);
		set->insert(iteratorToNewItem, newItem);
	}

}
std::map<std::string, std::set<Item>*> Customer::getCarts() const {
	return _shoppingCarts;
}
