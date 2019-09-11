//#pragma once
//#include <string>
//
//using namespace std;
//
//class AbstractCocktail
//{
//public:
//	static const int MAX_INGREDIENTS = 10;
//	static const int MAX_MEASUREMENTS = MAX_INGREDIENTS;
//	string name;
//	string ingredients[MAX_INGREDIENTS];	// Initialize 2D list of max 10 ingredients
//	int measurements[MAX_MEASUREMENTS];
//	string method;
//
//
//
//	virtual string getName() = 0;
//
//	virtual string getIngredients() = 0;
//	virtual void addIngredient(string) = 0;
//
//	virtual int getMeasurement() = 0;
//	virtual void addMeasurement(int) = 0;
//
//	virtual string getMethod() = 0;
//	virtual void setMethod(string) = 0;
//};