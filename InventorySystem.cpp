#include <string>
#include <fstream>
#include <iostream>
#include <stdio.h>
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
    string title, author, publisher;
    int stockCount;
    float price;
    bool available;
};

class admin{
    private:
        string id, name, password;
    public:
        admin(){}
        admin (string aId, string aName, string aPassword){
            id = aId;
            name = aName;
            password = aPassword;

            ofstream MyFile("admin.txt", ios::app);
            MyFile << id <<endl << name <<endl << password <<endl;
            MyFile.close();
        }
        string getId(){
            return id;
        }
        string getName(){
            return name;
        }
        string getPassword(){
            return password;
        }

        void setId(string aId){id = aId;}
        void setName(string aName){name = aName;}
        void setPassword(string aPassword){password = aPassword;}


};

class employee{
    public:
        //Constructors
        employee(){
            salary = 0.0;
        }
        employee(string eId, string employeeName, string employeeJobTitle, double employeeSalary, string ePassword ){
            id = eId;
            name = employeeName;
            jobTitle = employeeJobTitle;
            salary = employeeSalary;
            password = ePassword;
        }

        //Accessors
        string getId(){
            return id;
        }

        string getName(){
            return name;
        }

        string getJobTitle(){
            return jobTitle;
        }

        double getSalary(){
            return salary;
        }

        string getPassword(){
            return password;
        }

        //Mutators
        void setId(string employeeId){id = employeeId;}
        void setName(string employeeName){name = employeeName;}
        void setJobTitle(string employeeJobTitle){jobTitle = employeeJobTitle;}
        void setSalary(double employeeSalary){salary = employeeSalary;}
        void setPassword(string employeePassword){password = employeePassword;}



    private:
        string id, name, jobTitle, password;
        double salary;
};

class stock{
    public:
        //Constructor
        stock(){

        }
    private:
};



//----------------------------------------------------------------------------------------
string * credentials() {
    static string credentials [2];
    string id, password;

    cout<< "ID: ";  cin >> id;
    cout<< "Password: ";  cin >> password;

    credentials[0] = id; credentials[1] = password;
    return credentials;
}

void createEmployee(){
    
    string id,name, jobTitle, password;
    double salary;

    cout << endl << "Enter ID: ";
    cin >> id;
    cout << endl << "Enter Name: ";
    cin.ignore(); 
    getline(cin, name);    
    cout << endl << "Enter Job Title: ";
    getline(cin, jobTitle);    
    cout << endl << "Enter Salary: ";
    cin >> salary;
    cout << endl << "Enter Password: ";
    cin.ignore(); 
    getline(cin, password);

    employee e = employee(id, name, jobTitle, salary, password);
    
    ofstream employeeFile("employee.txt", ios::app);
    employeeFile << e.getId() << endl 
    << e.getPassword() << endl 
    << e.getName() << endl 
    << e.getJobTitle() << endl
    << e.getSalary() <<endl;
    employeeFile.close();

}

void customerUI(){
    cout << "Customer Login" << endl;
    string * loginDetails = credentials();

}
void staffUI(){
    char userInput;
    string * loginDetails;
    cout << "Staff Login" << endl << "Do you have an Account? (y/n) : ";
    cin >> userInput;

    switch (userInput){
        case 'y':
            loginDetails = credentials();
            break;
        case 'Y':
            loginDetails = credentials();
            break;
        case 'n':
            createEmployee(); 
            break;   
        case 'N':
            createEmployee();
            break;
        default:
            cout << endl << "Incorrect choice" << endl;
    }
}


void AdminUI(){
    char userInput;
    bool authenticLogin;
    string * loginDetails;
    cout << "**************Admin Login**************" << endl;
    loginDetails = credentials();

    string myText;
    ifstream MyReadFile("admin.txt");

    while (getline (MyReadFile, myText)) {
       if (myText==loginDetails[0]){
           admin a = admin();
           a.setId( myText);
           getline (MyReadFile, myText);
           a.setName(myText);
           getline (MyReadFile, myText);
           if (myText==loginDetails[1]){
               authenticLogin = true;
               a.setPassword(myText);
               break;
           }
       }
    }

    MyReadFile.close();


    switch (authenticLogin){
        case false:
            cout<< "Access denied"<< endl;
            break;
        case true:
            cout << endl << "****************************"<<endl;
            cout<< "For adding staff press a."<< endl;
            cout<< "For modify staff press m."<< endl;
            cout<< "For delete staff press d."<< endl;
            cout<< "For generating sales report press g."<< endl;
            cout << "Your input: ";
            cin >> userInput;
            cout <<endl;
    }
    
    string id, updateValue, name, password, jobTitle;
    double salary;
    employee e = employee ();
    bool found, isPass, isName, isJobTitle, isSalary;
    ifstream readFile ("employee.txt");
    ofstream writeFile ("employee1.txt", ios :: app);
    ofstream WriteFile ("employee.txt", ios :: app);
    switch(userInput){
        case 'a':
            cout << "Enter id: " ;
            cin >> id ;
            cout << endl << "Enter password: ";
            cin.ignore();           
            getline (cin , password);
            cout << endl << "Enter name: ";
            getline (cin , name);
            cout << endl << "Enter job title: ";
            getline (cin , jobTitle);
            cout << endl << "Enter salary: ";
            cin >> salary;

            e.setId(id); e.setPassword(password); e.setName(name); e.setJobTitle(jobTitle); e.setSalary(salary);
            
            WriteFile << endl << e.getId() << endl << e.getPassword() << endl << e.getName ()
            << endl << e.getJobTitle() << endl << e.getSalary() << endl;

            cout << "Added employee!"<<endl;

            remove("employee1.txt");
            WriteFile.close();
            writeFile.close();
            readFile.close();

            break;
        case 'm':
            cout << "Enter employee id: "; cin >> id ; cout <<endl;
            cout << "What do you want to update? (press p for password, n for name, j for job title, s for salary)";
            cin >> userInput;
            cout << endl;
            if (userInput == 'p'){
                isPass = true;
                isSalary = isJobTitle = isName = false;
            }else if (userInput == 'n'){
                isName = true;
                isSalary = isJobTitle = isPass = false;
            }else if (userInput == 'j'){
                isJobTitle = true;
                isSalary = isPass = isName = false;
            } else if (userInput == 's'){
                isSalary = true;
                isPass = isJobTitle = isName = false;
            }


            cout << "Enter Update value: "; cin >> updateValue; cout << endl;
            cout << "Updating employee with id " << id << "...." << endl;

            while (getline (readFile, myText)) {
                if (myText == id){
                    writeFile << myText <<endl;
                    getline (readFile, myText);
                    if(isPass){
                        writeFile << updateValue << endl;
                        getline (readFile, myText);
                        writeFile << myText <<endl;
                        getline (readFile, myText);
                        writeFile << myText <<endl;
                        getline (readFile, myText);
                        writeFile << myText <<endl;
                    }else if (isName){
                        writeFile << myText <<endl;
                        getline(readFile, myText);
                        writeFile << updateValue <<endl;
                        getline(readFile, myText);
                        writeFile << myText <<endl;
                        getline(readFile, myText);
                        writeFile << myText <<endl;

                    }else if (isJobTitle){
                        writeFile << myText <<endl;
                        getline(readFile, myText);
                        writeFile << myText <<endl;
                        getline(readFile, myText);
                        writeFile << updateValue <<endl;
                        getline(readFile, myText);
                        writeFile << myText <<endl;
                    }else if (isSalary){
                        writeFile << myText <<endl;
                        getline(readFile, myText);
                        writeFile << myText <<endl;
                        getline(readFile, myText);
                        writeFile << myText <<endl;
                        getline(readFile, myText);
                        writeFile << updateValue <<endl;
                    }

                    found = true;
                }else{
                    writeFile << myText<< endl;
                }
            }

            remove("employee.txt");
            rename ("employee1.txt","employee.txt");
            readFile.close();
            writeFile.close();
            WriteFile.close();
            if (!found) {
                cout << "Employee with id " << id << " doesn't exist" << endl; 
            }else{
                cout << "Updated successfully" << endl;
            }
            break;
        case 'd':
            cout << "Enter employee id: "; cin >> id ; cout <<endl;
            cout << "deleting employee with id " << id << "...." << endl;

            while (getline (readFile, myText)) {
                if (myText == id){
                    for(int i = 0; i < 4 ; i++){
                        getline(readFile, myText);
                    }
                    found = true;
                }else{
                    writeFile << myText<< endl;
                }
            }

            remove("employee.txt");
            rename ("employee1.txt","employee.txt");
            readFile.close();
            writeFile.close();
            WriteFile.close();
            if (!found) {
                cout << "Employee with id " << id << " doesn't exist" << endl; 
            }else{
                cout << "Deleted successfully" << endl;
            }             
            break;
        case 'g':
            
            break;
        default:
            cout<< "Illegal command";
    }

}

int main (void) {
    AdminUI();
    return 0;
}