#include <string>
#include <iostream>
using namespace std;


class book{
public:
    //constructors
    book(){
        price = 0.0;
        available = false;
    }
    book  (
            string book_title, 
            string book_author,
            string book_publisher, 
            string book_stock_position, 
            float book_price, 
            bool book_availability
            )
    {
        title = book_title;
        author = book_author;
        publisher = book_publisher;
        stock_position = book_stock_position;
        price = book_price;
        available = book_availability;

    }
private:
    string title;
    string author;
    string publisher;
    string stock_position;
    float price;
    bool available;
};

int main (void) {
    return 0;
}