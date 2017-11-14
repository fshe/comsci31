#include <iostream>
#include <string>
using namespace std;

int main()
{ 

	cout << "Units sold: ";           // Declaration of variables and information collection
	int unitsSold;
	cin >> unitsSold;
	if (unitsSold <0)
	{
		cout << "---\n" << "The number of units sold must be nonnegative.";
		return 1;
	}
	cin.ignore(10000, '\n');

	cout << "Title: ";
	string title;
	getline(cin, title);
	if (title == "")
	{
		cout << "---\n" << "You must enter a title.";
		return 1;
	}

	cout << "Sales price: ";
	double salesPrice;
	cin >> salesPrice;
	
	cout << "Expense: ";
	double expense;
	cin >> expense;
	cin.ignore(10000, '\n');
	if (expense <0)
	{
		cout << "---\n" << "The expense must be nonnegative.";
		return 1;
	}
	else 
		if (salesPrice < expense)
		{
			cout << "---\n" << "The sales price must not be less than the expense.";
			return 1;
		}
	
	cout << "Premium item? (y/n): ";
	string response;
	getline(cin, response);
	if (response != "y" && response != "n")
	{
		cout << "---\n" << "You must enter y or n.";
		return 1;
	}
	double netSellingPrice;
	netSellingPrice = salesPrice - expense;		// Price - expense = net selling price

	double royalty;                             // Royalty = total earned in royalties
	if(unitsSold <= 300)                        // Calculations for different cases of royalty
		royalty = netSellingPrice * 0.08 * unitsSold;
	else
		if (response == "y" && unitsSold <= 1000) 
			royalty = ((300 * .08) + (unitsSold - 300) * .14) * netSellingPrice;
		else
			if (response == "n" && unitsSold <=1000)
				royalty = ((300 * .08) + (unitsSold - 300) * .11) * netSellingPrice;
			else
				if (response == "y" && unitsSold > 1000)
					royalty = ((300 * .08) + (700 * .14) + (unitsSold - 1000) * .14) * netSellingPrice;
				else
					if (response == "n" && unitsSold > 1000)
						royalty = ((300 * .08) + (700 * .11) + (unitsSold - 1000) * .14) * netSellingPrice;
					else
						return 1;
	cout.setf(ios::fixed);
	cout.precision(2);
	cout << "---\n" << title << " earned $" << royalty << " in royalties." << endl;
}