// Code for Project 1
/ Report poll results
	
#include <iostream>
using namespace std;       // see p. 36-37 in Savitch book
	
int main()
{
    int numberSurveyed;
    int forObama;
    int forRomney;
	
    cout << "How many registered voters were surveyed? ";
    cin >> numberSurveyed;
    cout << "How many of them say they will vote for Obama? ";
    cin >> forObama;
    cout << "How many of them say they will vote for Romney? ";
    cin << forRomney;
	
    double pctObama = 100.0 * forObama / numberSurveyed;
    double pctRomney = 100.0 * forRomney / numberSurveyed;

    cout.setf(ios::fixed);       // see pp. 31-32 in Savitch book
    cout.precision(1);
	
    cout << endl;
    cout << pctObama << "% say they will vote for Obama." << endl;
    cout << pctRomney << "% say they will vote for Romney." << endl;

    if (forObama > forRomney)
        cout << "Obama is predicted to win the election." << endl;
    else
        cout << "Romney is predicted to win the election." << endl;