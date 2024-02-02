#include <iostream>
#include <Windows.h>
#include <fstream>

#define NL endl

using namespace std;

int menuIndex = 0;
char path[] = "foodData.txt";
int customer_total_cost = 0;

//--------------------------> Class declaration <-------------------------------------
struct cloneMenuData
{
  int foodcode;
  string foodname;
  int price;
};
class FoodMenu
{
protected:
  int foodcode;
  string foodname;
  int price;

public:
  void setMenuData(cloneMenuData temp)
  {
    this->foodcode = temp.foodcode;
    this->foodname = temp.foodname;
    this->price = temp.price;
  }

  cloneMenuData getMenuData(cloneMenuData temp)
  {
    temp.foodcode = this->foodcode;
    temp.foodname = this->foodname;
    temp.price = this->price;
    return temp;
  }

  void showItem()
  {
    cout << NL << "\t|```````````````````````````" << NL;
    cout << "\t| Item code : " << foodcode << NL;
    cout << "\t| Item : " << foodname << NL;
    cout << "\t| Price : " << price << NL;
    cout << "\t'```````````````````````````" << NL;
  }
};

class FoodMenu mainMenuArray[1000]; 

// Food Menu file
void readMenuDataFromFile()
{
  ifstream file(path);
  if (file.fail())
  {
    menuIndex = 0;
    return;
  }
  
  else
  {
    cloneMenuData tempObject;
    while (file >> tempObject.foodcode)
    {
      file.ignore();
      getline(file, tempObject.foodname);
      file >> tempObject.price;
      mainMenuArray[menuIndex].setMenuData(tempObject);
      menuIndex++;
    }
  }
  file.close();
  return;
}

void saveMenuInFile()
{
  ofstream file(path);
  cloneMenuData tempObject;
  for (int j = 0; j < menuIndex; j++)
  {
    tempObject = mainMenuArray[j].getMenuData(tempObject);
    file << tempObject.foodcode << NL;
    file << tempObject.foodname << NL;
    file << tempObject.price << NL;
  }
  file.close();
  return;
}
// to show the full menu list saved in menu array
void showMenuItems()
{
  system("cls");
  cout << "\n=============== Menu Items List ===============\n\n";

  if (menuIndex == 0)
  {
    cout << "\tSorry there is no food on menu\n";
    return;
  }
  else
  {
    for (int j = 0; j < menuIndex; j++)
    {
      mainMenuArray[j].showItem();
    }
  }
  return;
}

// ordering food from the menu stock, accessible by the customer
void selectFoodForOrder()
{
  cout << NL << "\tEnter Food Code : ";
  int foodcode, amount;
  cin >> foodcode;
  int index = (foodcode - 1);
  if (index < menuIndex)
  {
    cloneMenuData tempObject;
    tempObject = mainMenuArray[index].getMenuData(tempObject);
    system("cls");
    cout << "\n\tSelected Item: \n";
    mainMenuArray[index].showItem();
    cout << NL << "\tEnter Food Amount : ";
    cin >> amount;

    cout << NL << "\tSelected Food Code : " << tempObject.foodcode;
    cout << NL << "\tSelected Food name : " << tempObject.foodname;
    cout << NL << "\tSelected Food price : " << tempObject.price;
    cout << NL << "\tFood Amount : " << amount;
    cout << NL << "\tCost : " << (tempObject.price * amount);
    char confirm;
    cout << NL << "\tConfirm order? [y/n] : ";
    cin >> confirm;
    if (confirm == 'n' || confirm != 'y')
    {
      cout << "\n\tYou've canceled the order...\n\n";
      return;
    }
    int sum = tempObject.price * amount;
    customer_total_cost += sum;
    cout << NL << "\tYou have ordered " << sum << " Taka food in this session";
    cout << NL << "\tYour total bill is : " << customer_total_cost << " Taka" << NL << NL;
    mainMenuArray[index].setMenuData(tempObject);
    cout << NL << "\tpress 1 to order again, any other number to return to cutomer menu: ";
    int option;
    cin >> option;
    if (option == 1)
      selectFoodForOrder();
    else
      return;
  }
  else
    cout << "\tInvalid Food code" << NL;
}

//-------------------------------------> End of Food Menu interface<-------------------------------------------

//----------------------> User Profile & Customer interface functions <--------------------------
void clearScreen()
{
  cout << "\n\tpress enter to continue...";
  getchar();
  getchar();
  system("cls");
}

// Customer section and options
int CustomerAccess()
{
  int select2, option;
  while (1)
  {

    system("cls");
    cout << "\n=============== Welcome to Customer section ===============\n\n";
    cout << "\tpress following numbers\n";
    cout << "\t1) View Menu item and order\n";
    cout << "\t2) Exit the app\n";
    cout << "\n\tYour total bill untill now: " << customer_total_cost << " Taka." << NL;
    cout << "\n\tGive your option: ";
    cin >> select2;
    if (select2 == 1)
    {
      showMenuItems();
      cout << "\tEnter 1 to order and  2 to return to Customer menu\n";
      cout << "\tEnter your option: ";
      cin >> option;
      if (option == 2)
        continue;
      else
      {
        selectFoodForOrder();
        clearScreen();
      }
    }
    else
      break;
  }
}
//-----------------------> End of User Profile section<-----------------------

// ----------------------------> Starting of the App <---------------------------
int main()
{
  system("color 0B");
  // reading data from database
  readMenuDataFromFile();
  // startup of first page of program from here.
  CustomerAccess();
  // saving all the array data to file before closing
  saveMenuInFile();
  return 0;
}

// ----------------------------> End of the App <----------------------------