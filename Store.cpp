#include "Store.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <algorithm>

Store::Store(std::string storeName, std::string inventoryFileName):_storeName(storeName)
{
	getInventoryFromFile(inventoryFileName);
}

std::string Store::getSortedProductList(SortingCriteria sortingCriteria) const
{
	std::deque<Item> copy = _products;
	std::sort(copy.begin(), copy.end(), NameComparator);
	switch (sortingCriteria)
	{
	case CATEGORY:
		
		std::sort(copy.begin(), copy.end(),CategoryComparator);
		break;
	case NAME:
		//std::sort(copy.begin(), copy.end(), NameComparator);
		break;
	case PRICE:
		std::sort(copy.begin(), copy.end(), PriceComparator);
		break;
	case SERIAL:
		std::sort(copy.begin(), copy.end());
		break;
	default:
		INVALID_ARGUMENT;
		break;
	}
	return ToString(copy);
}

std::string Store::getProductListFilteredByCategory(ItemCategory category) const
{
	std::deque<Item> copy;
	switch (category)
	{
	case NONE:
		std::copy_if(_products.begin(), _products.end(), std::back_inserter(copy), [](Item item) { return item.getCategory() == NONE; });
		break;
	case FOOD:
		std::copy_if(_products.begin(), _products.end(), std::back_inserter(copy), [](Item item) { return item.getCategory() == FOOD; });
		break;
	case PHARM:
		std::copy_if(_products.begin(), _products.end(), std::back_inserter(copy), [](Item item) { return item.getCategory() == PHARM; });
		break;
	case CLEANING:
		std::copy_if(_products.begin(), _products.end(), std::back_inserter(copy), [](Item item) { return item.getCategory() == CLEANING; });
		break;
	case HOME:
		std::copy_if(_products.begin(), _products.end(), std::back_inserter(copy), [](Item item) { return item.getCategory() == HOME; });
		break;
	default:
		INVALID_ARGUMENT;
		break;
	}
	std::sort(copy.begin(), copy.end(), NameComparator);
	return ToString(copy);
}

Item Store::operator[](const int itemNumber) const
{
	return _products[itemNumber];
}

void Store::getInventoryFromFile(const std::string inventoryFileName)
{
	// This function reads a CSV file into the object inventory (std::deque<Item>)

	std::deque<std::deque<std::string>> content;	// the entire file as strings
	std::deque<std::string> row;					// a row in the file as string
	std::string line, word;							

	std::fstream file(inventoryFileName, std::ios::in);		// openning the csv file for read
	if (file.is_open())
	{
		while (std::getline(file, line))		// reading line by line
		{
			row.clear();

			std::stringstream str(line);		// adding the line to a std::stringstream

			while (std::getline(str, word, ','))	// reading each word seperated by ','
				row.push_back(word);
			content.push_back(row);
		}
	}
	else
	{
		std::cerr << "Could not open the file " << inventoryFileName << "\n" << std::endl;
		throw std::invalid_argument("Could not open the file " + inventoryFileName);
	}

	/* Indexes
		0 --- Item's Name
		1 --- Item's Serial
		2 --- Item's Unit Price
		3 --- Item's Category (int)
	*/

	for (int i = 1; i < content.size(); i++)
	{
		std::string itemName = content[i][0];
		std::string itemSerial = content[i][1];
		double itemPrice = strtod(content[i][2].c_str(), nullptr);
		ItemCategory itemCategory = ItemCategory(stoi(content[i][3]));
		this->_products.push_back(Item(itemName, itemSerial, itemPrice, itemCategory));
	}

	// To print the content remove the comments:
	// for (int i = 0; i < content.size(); i++)
	//{
	//	for (int j = 0; j < content[i].size(); j++)
	//	{
	//		std::cout << content[i][j] << " ";
	//	}
	//	std::cout << "\n";
	//}

}

std::string Store::ToString(std::deque<Item> products) const
{
	std::stringstream ret;
	for (auto item:products)
	{
		ret << item;
		ret << "\n";
	}
	return ret.str();
}

std::ostream& operator<<(std::ostream& os, const Store& store)
{
	os << store.ToString(store._products);
	return os;
}
