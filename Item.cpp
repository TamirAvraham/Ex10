#include "Item.h"


#define INVALID_ARGUMENT throw std::invalid_argument("invalid argumnet")

Item::Item(string name, string serialNumber, double unitPrice, ItemCategory category):_name(name),_category(category),_count(1)
{
	if (serialNumber.length()!=5||unitPrice<0.0)
	{
		INVALID_ARGUMENT;
	}
	_serialNumber = serialNumber;
	_unitPrice = unitPrice;
}

bool Item::operator>(const Item& other) const
{
	return other._serialNumber < this->_serialNumber;
}
double Item::totalPrice() const
{
	return _unitPrice*_count;
}
bool Item::operator<(const Item& other) const
{
	return other._serialNumber > this->_serialNumber;
}
bool Item::operator==(const Item& other) const
{
	return other._serialNumber == this->_serialNumber;
}

std::string Item::getName() const
{
	return _name;
}

std::string Item::getSerial() const
{
	return _serialNumber;
}

int Item::getCount() const
{
	return _count;
}

double Item::getPrice() const
{
	return _unitPrice;
}

ItemCategory Item::getCategory() const
{
	return _category;
}

void Item::setCount(int count)
{
	if (count<1)
	{
		INVALID_ARGUMENT;
	}
	_count = count;
}

std::ostream& operator<<(std::ostream& os, const Item& item)
{
	auto str = "[Serial: " + item.getSerial() +
		", Name: " + item.getName() +
		", Category: " + getItemCategoryString(item.getCategory()) +
		", Price: " + std::to_string(item.getPrice()) +
		", Amount: " + std::to_string(item.getCount()) + "]";
	os << str;
	return os;
}
