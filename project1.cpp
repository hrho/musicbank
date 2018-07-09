#include <iostream>
#include <fstream>
#include <iomanip>
#include <cstdlib>
#include <ctime>
using namespace std;

struct food{
string name,group;
float cal,per;
};

struct node{
food foodItem;
node *next;
};

class FoodList{
private:
node* first;
int size;
public:
FoodList(){
first = NULL;
}

void add(food f){
node *n = new node;
n->foodItem = f;
n->next = NULL;
if(first == NULL)
first = n;
else
{
node *last = first;
//find the last node
while(last->next != NULL)
last = last->next;
last->next = n;
}
size++;
}

void print() const{

cout <<left << setw(20) << "Name" << setw(15) <<"Food group" << setw(10) <<"Calories" << setw(15) << "Daily percentage" << endl;
for(node *curr = first; curr != NULL; curr= curr->next){
cout <<left << setw(20) << curr->foodItem.name
<< setw(15) << curr->foodItem.group
<< setw(10) << curr->foodItem.cal
<< setw(15) << curr->foodItem.per << endl;
}

cout << endl;

}

//searches and fills the param f with the found food and returns true if found, false if not found
bool findFood(string name, food &f) const
{
for(node *curr = first; curr != NULL; curr= curr->next){
if(curr->foodItem.name == name)
{
f = curr->foodItem;
return true;
}
}
return false;
}

int getSize(){
return size;
}

void deleteAbove(double calories){
node *curr = first;
node *prev = NULL;

while(curr != NULL)
{
if(curr->foodItem.cal > calories)
{
//delete the node
node* next = curr->next;
if(prev == NULL)
first = next;
else
prev->next = next;
delete curr;
curr = next;
size--;
}
else
{
prev = curr;
curr = curr->next;
}
}
}

food getRandomFood() const
{
int index = rand() % size;
node *curr = first;
for(int i = 0; i < index; i++)
return curr->foodItem;
}
};

void printMeal(food mealArr[3]);
void userMeal(const FoodList &flist, food mealArr[3]);
void randomMeal(const FoodList &flist, food mealArr[3]);
void deleteMeals( FoodList &flist);

int main()
{

// Open file
string filename = "/home/staff/dbock/csc125/projects/project1/foods.txt";
//string filename = "foods.txt";
fstream in(filename.c_str() , ios::in );

if(in.fail())
{
cout << "ERROR: could not open input file " << filename << endl;
return 1;
}
// Read lines

string name,group;
float cal,per;
cout << fixed << setprecision(2);
FoodList flist;
while( in >> name >> group >> cal >> per )
{
food f;
f.name = name;
f.group = group;
f.cal = cal;
f.per = per;
flist.add(f);
}

// Close file
in.close();

int choice = 0;
food mealArr[3];
srand(time(0));
while(choice != 5)
{
cout << "Welcome to Parkland Meal Selector" << endl;
cout << "Please select from the following" << endl;
cout << "1 - List food database" << endl;
cout << "2 - Create meal by manual selection" << endl;
cout << "3 - Create meal by random selection" << endl;
cout << "4 - Remove foods high in calorie" << endl;
cout << "5 - Exit" << endl;
cin >>choice;

switch(choice)
{
case 1: flist.print();
break;
case 2: userMeal(flist, mealArr);
printMeal(mealArr);
break;
case 3: randomMeal(flist, mealArr);
printMeal(mealArr);
break;
case 4:
deleteMeals(flist);
break;

case 5:
break;
default:
cout << "Invalid menu choice!" << endl;
}
}

}


void printMeal(food mealArr[3]){
double totalCal = 0;
double totalPer = 0;
cout << "===============================" << endl;
cout << "Your selected meal" << endl;

cout << "\tFoods: ";
for(int i = 0; i < 3; i++){
cout << mealArr[i].name << " ";
totalCal += mealArr[i].cal;
totalPer += mealArr[i].per;
}
totalPer *= 100;
cout << endl << "\tTotal Calorie count: " << totalCal << endl;
cout << "\tTotal Daily percentage: %" << totalPer << endl;
cout << "===============================" << endl;
cout << endl;

}

void userMeal(const FoodList &flist, food mealArr[3]){
int i =0;
food f;
string name;
while(i < 3){
cout << "Enter food name " << i << ": ";
cin >> name;
if(flist.findFood(name, f))
{
mealArr[i] = f;
i++;
}
else
cout << "No matching food: " << name << endl;
}
}

void randomMeal(const FoodList &flist, food mealArr[3])
{
food f;

for(int i = 0; i < 3; i++)
{
f = flist.getRandomFood();

//check if food already in meals
bool dup = false;
for(int j = 0; j < i; j++)
{
if(mealArr[j].name == f.name)
{
dup = true;
break;
}
}

if(!dup)
{
mealArr[i] = f;
}
}
}
void deleteMeals( FoodList &flist)
{
double calories;
cout << "Enter calorie limit: ";
cin >> calories;
flist.deleteAbove(calories);
}
