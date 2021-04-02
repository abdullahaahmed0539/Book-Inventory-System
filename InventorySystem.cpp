#include <string>
#include <iostream>
using namespace std;


class book{
public:
    //constructors
    book(){
        stockCount = 0;
        price = 0.0;
        available = false;
    }
    book  (
            string bookTitle, 
            string bookAuthor,
            string bookPublisher, 
            int bookStockCount, 
            float bookPrice, 
            bool bookAvailability
            )
    {
        title = bookTitle;
        author = bookAuthor;
        publisher = bookPublisher;
        stockCount = bookStockCount;
        price = bookPrice;
        available = bookAvailability;

    }

    //Accessors
    string getTitle (){
        return title;
    }

    string getAuthor (){
        return author;
    }

    string getPublisher (){
        return publisher;
    }

    int getStockCount (){
        return stockCount;
    }

    float getPrice(){
        return price;
    }

    bool getAvailability (){
        return available;
    }

    //Mutators
    void setTitle(string bookTitle){title = bookTitle;}
    void setAuthor(string bookAuthor){author = bookAuthor;}
    void setPublisher(string bookPublisher){publisher = bookPublisher;}
    void setStockCount(int bookCount){stockCount = bookCount;}
    void setprice(float bookPrice){price = bookPrice;}
    void setAvailability(bool status){available = status;}


private:
    string title;
    string author;
    string publisher;
    int stockCount;
    float price;
    bool available;
};

class employee{
    public:
        //Constructors
        employee(){
            salary = 0.0;
        }
        employee(string employeeName, string employeeJobTitle, double employeeSalary ){
            name = employeeName;
            jobTitle = employeeJobTitle;
            salary = employeeSalary;
        }

        //Accessors
        string getName(){
            return name;
        }

        string getJobTitle(){
            return jobTitle;
        }

        double getSalary(){
            return salary;
        }

        //Mutators
        void setName(string employeeName){name = employeeName;}
        void setJobTitle(string employeeJobTitle){jobTitle = employeeJobTitle;}
        void setSalary(double employeeSalary){salary = employeeSalary;}

    private:
        string name;
        string jobTitle;
        double salary;
};






int main (void) {

    return 0;
}