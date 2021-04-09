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
    void setAvailability(){
        if(stockCount <=0){
            available = false;
        }else {
            available = true;
        }
    }


    //additional functions
    void addStock(int q){
        stockCount += q;
        cout << "Ordered "<<q << " " << title <<" books. "<<endl << "Total quantity: "<<stockCount <<endl;
    }

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

class customer{
    public:
        customer(){
            total_purchase = 0.0;
        }
        customer( string cName, string cEmail, string cContact, double cTP){
            name = cName;
            email = cEmail;
            contact = cContact;
            total_purchase = cTP;
        }
        //accessors
        string getName(){
            return name;
        }
        string getEmail(){
            return email;
        }
        string getContact(){
            return contact;
        }

        double getTotalPurchase(){
            return total_purchase;
        }

        //mutators
        void setName(string cName){name = cName;}
        void setEmail(string cEmail){email = cEmail;}
        void setContact(string cContact){contact = cContact;}
        void setTotalPurchase(double sum){total_purchase+=sum;}


        double buy (){
            char userInput = 'y';
            double total,i = 0;
            string invoice = "";
            while(userInput == 'y'){                
                cout <<endl << "Enter the book you want to buy: ";
                string title;
                if(!(i==0)){
                    cin.ignore();
                }
                i=1;
                getline(cin, title);
                cout << endl << "Enter quantity:  ";
                int quantity;
                cin >> quantity;
                

                ifstream myFile ("book.txt");
                bool isfound = false;
                string myText;
                book b = book();

                while (getline (myFile, myText)){
                    if (myText == title){
                        isfound = true;
            
                        b.setTitle(myText);
                            
                        getline(myFile, myText);
                        b.setAuthor(myText);
                            
                        getline(myFile, myText);
                        b.setPublisher(myText);
                            
                        getline(myFile, myText);
                        int count = stoi (myText);
                        b.setStockCount(count);

                        b.setAvailability();

                        getline(myFile, myText);
                        getline(myFile, myText);
                        float x = stof (myText);
                        b.setprice(x);

                        break;
                    }
                }

                myFile.close();
                
                
                if(isfound){
                    if ( b.getStockCount() - quantity >= 0){
                        b.setStockCount( b.getStockCount()- quantity);

                        ifstream readBookFile ("book.txt");
                        ofstream writeBookFile ("book1.txt", ios::app);
                        while(getline(readBookFile,myText)){
                            if(myText==b.getTitle()){
                                writeBookFile << myText << endl;
                                
                                getline(readBookFile,myText);
                                writeBookFile << myText << endl;

                                getline(readBookFile,myText);
                                writeBookFile << myText << endl;

                                writeBookFile << b.getStockCount() << endl;

                                getline(readBookFile,myText);
                                getline(readBookFile,myText);
                                writeBookFile << myText << endl;

                                getline(readBookFile,myText);
                                writeBookFile << myText << endl;

                            }else{
                                writeBookFile << myText << endl;
                            }
                        }
                        remove("book.txt");
                        rename("book1.txt", "book.txt");
                        readBookFile.close(); writeBookFile.close();

                        if(b.getStockCount()==0){
                            b.setAvailability();
                        }

                        total += (b.getPrice() * quantity);
                        invoice = invoice + "TITLE: "+b.getTitle() + "--------" + "RATE: $"+to_string(b.getPrice())+"--------"+ "Quantity: "+to_string(quantity)+" units--------"+"Cost: $" +to_string((b.getPrice() * quantity))+"\n";
                        
                    }else {
                            cout << "Sorry We only have "<< b.getStockCount() << " books." << endl;
                    } 
                        
                }else{
                        cout << endl << "Book not found"<< endl;
                }

                cout << endl << "Do you want to buy more books? (press y for yes, any key for no):  ";
                cin >> userInput;
            }
            invoice = invoice +"\n"+ "TOTAL----------------------------------------$"+to_string(total)+"\n";
            cout<<endl<<endl<<"*****************************INVOICE********************************"<<endl;
            cout << invoice <<endl;
            return total;
        }

    private:
        string name, email, contact;
        double total_purchase;
};


//----------------------------------------------------------------------------------------
string * credentials() {
    static string credentials [2];
    string id, password;

    std::cout<< "ID: ";  std::cin >> id;
    std::cout<< "Password: ";  std::cin >> password;

    credentials[0] = id; credentials[1] = password;
    return credentials;
}

void createEmployee(){
    
    string id,name, jobTitle, password;
    double salary;

    std::cout << endl << "Enter ID: ";
    std::cin >> id;
    std::cout << endl << "Enter Name: ";
    std::cin.ignore(); 
    getline(std::cin, name);    
    std::cout << endl << "Enter Job Title: ";
    getline(std::cin, jobTitle);    
    std::cout << endl << "Enter Salary: ";
    std::cin >> salary;
    std::cout << endl << "Enter Password: ";
    std::cin.ignore(); 
    getline(std::cin, password);

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
    cout << "***************************************" << endl;
    cout << "--------------Customer Session--------------" << endl;
    cout << "***************************************" << endl;
    bool ExistingCustomer;

    double total = -1;
    customer c = customer();
    cout << "Are an existing customer? (y/n):  ";
    char userInput;
    cin >> userInput;

    if(userInput == 'y'){
        ExistingCustomer = true;
    }else if (userInput == 'n'){
        ExistingCustomer = false;
    }else {
        cout << "***************ERROR*****************" << endl;
        cout << endl << "Illegal Command. Choose between y or n: ";
        cin >> userInput;
    }

    if (!ExistingCustomer){
        cout << endl << "Before you buy please enter your details for a better buying experience." <<endl;
       

        cout <<endl<< "NAME: ";
        string name;
        cin.ignore();
        getline(cin, name);
        
        cout << endl << "EMAIL: ";
        string email;
        getline(cin , email);

        cout << endl << "CONTACT: ";
        string contact;
        getline(cin , contact);

    
        c.setName(name);
        c.setEmail(email);
        c.setContact(contact);

        total = c.buy();
        cout<<"*********************************************************************"<<endl;
        ifstream rcusFile ("customer.txt");
        ofstream wcusFile ("customer1.txt", ios::app);
        string myText;
        while(getline(rcusFile,myText)){
            wcusFile << myText <<endl;
        }

        wcusFile << c.getName() << endl << c.getEmail() << endl << c.getContact() << endl << total <<endl; 
        remove("customer.txt");
        rename("customer1.txt", "customer.txt");
        rcusFile.close(); wcusFile.close();
        
 
    }else if (ExistingCustomer){
        ifstream rcustomerFile ("customer.txt");
        ofstream wcustomerFile ("customer1.txt", ios::app);
        bool isfound = false;
        string myText;
        string name;

        cout << "Enter name: ";
        cin.ignore();
        getline(cin, name);


        while(getline(rcustomerFile, myText)){
            if (myText == name){
                isfound = true;
                c.setName(myText);

                getline(rcustomerFile, myText);
                c.setEmail(myText);

                getline(rcustomerFile, myText);
                c.setContact(myText);

                getline(rcustomerFile, myText);
                double x = stoi(myText);
                c.setTotalPurchase(x);

                break;
            }
        }
        rcustomerFile.close(); wcustomerFile.close();


        if (isfound){
            cout << endl << "--------------Welcome " << c.getName() << " -------------" << endl;
            total = c.buy() * 0.95;
            cout << "Total after 5% off----------------------------------------$"+to_string(total)+"\n";
            cout<<"*********************************************************************"<<endl;
            ifstream rcusFile ("customer.txt");
            ofstream wcusFile ("customer1.txt", ios::app);
            string myText;
            while(getline(rcusFile,myText)){
                if(myText == c.getName()){
                    wcusFile << myText <<endl;
                    
                    getline(rcusFile,myText);
                    wcusFile << myText <<endl;

                    getline(rcusFile,myText);
                    wcusFile << myText <<endl;

                    getline(rcusFile,myText);
                    wcusFile << (total + c.getTotalPurchase())<<endl;
                }else{
                    wcusFile << myText <<endl;
                }
            }
 
            remove("customer.txt");
            rename("customer1.txt", "customer.txt");
            rcusFile.close(); wcusFile.close();

            
        }else {
            ExistingCustomer = false;
            cout << endl << "Sorry we don't have your name in our database.";
            cout << endl << "Before you buy please enter your details for a better buying experience." <<endl;
        

            c.setName(name);
            
            cout << endl << "EMAIL: ";
            string email;
            getline(cin , email);

            cout << endl << "CONTACT: ";
            string contact;
            getline(cin , contact);

        
            c.setName(name);
            c.setEmail(email);
            c.setContact(contact);

            total = c.buy();
            cout<<"*********************************************************************"<<endl;
            ifstream rcusFile ("customer.txt");
            ofstream wcusFile ("customer1.txt", ios::app);
            string myText;
            while(getline(rcusFile,myText)){
                wcusFile << myText <<endl;
            }

            wcusFile << c.getName() << endl << c.getEmail() << endl << c.getContact() << endl << total <<endl; 
            remove("customer.txt");
            rename("customer1.txt", "customer.txt");
            rcusFile.close(); wcusFile.close();
        }

    }


    


   


}

void staffUI(){
    char userInput;
    bool authenticated,logIn;
    string myText;
    string * loginDetails;
    cout << "***************************************" << endl;
    cout << "--------------Staff Login--------------" << endl;
    cout << "***************************************" << endl;
    loginDetails = credentials ();

    ifstream empFile ("employee.txt");
    while (getline (empFile, myText)){
        if (myText == loginDetails[0]){
            getline(empFile, myText);
            if (myText == loginDetails[1]){
                logIn = authenticated = true;
                break;
            }
        }
    }

    if (authenticated){
        while(logIn){ 
        cout << endl << endl  << "----------------Session----------------" << endl;
        cout<< "Press n-------->For creating new stock for a book." <<endl 
        << "press b-------->For Book search." << endl
        << "Press s-------->For stock status."<< endl
        << "Press a-------->For adding books to stock." << endl
        << "Press l--------> For Logging out."<<endl<<endl;

        cout << "User Input: ";
        cin >> userInput;

        if(userInput == 'l'){
            cout << "--------Terminating Session--------"<<endl;
            logIn = false;
        }else if (userInput=='b' || userInput=='s' || userInput=='a'){
            string title;
            bool isfound;
            book b = book();
            cout <<endl << "Enter book name: " ;
            cin.ignore();
            getline(cin , title);
            cout << endl;

            ifstream readBookFile ("book.txt");
            while (getline (readBookFile, myText)){
                if (myText == title){
                    isfound = true;
        
                    b.setTitle(myText);
                        
                    getline(readBookFile, myText);
                    b.setAuthor(myText);
                        
                    getline(readBookFile, myText);
                    b.setPublisher(myText);
                        
                    getline(readBookFile, myText);
                    int count = stoi (myText);
                    b.setStockCount(count);

                    b.setAvailability();

                    getline(readBookFile, myText);
                    getline(readBookFile, myText);
                    float x = stof (myText);
                    b.setprice(x);

                    break;
                }
            }
            
            readBookFile.close();

            if(isfound && userInput=='b'){

                cout << "---------------Search Results---------------"<<endl;    
                cout <<"TITLE: " <<b.getTitle() << endl 
                     <<"AUTHOR: "<< b.getAuthor()<< endl
                     <<"PUBLISHER: "<< b.getPublisher()<< endl
                     << "AVAILABILILTY: "<< boolalpha <<b.getAvailability() << endl
                     << "STOCK COUNT: "<< b.getStockCount()<< endl
                     << "PRICE: $"<<b.getPrice() << endl; 
                       
                }else if(isfound && userInput=='s'){
                    cout << "---------------Stock Query---------------"<<endl;
                    cout  << "STOCK COUNT: "<< b.getStockCount()<< endl;
                    if(!b.getAvailability()){
                        cout << "OUT OF STOCK!"<< endl;
                    }
                }else if (isfound && userInput=='a'){
                    int quantity;
                    cout << "Enter quantity: ";
                    cin >> quantity;

                    cout << "---------------Stock Order---------------"<<endl;
                    b.addStock(quantity);
                    b.setAvailability();

                    ofstream writeBookFile ("book1.txt", ios::app);
                    ifstream readBookFile ("book.txt");

                    while(getline(readBookFile,myText)){
                        if(myText==b.getTitle()){
                            writeBookFile << myText << endl;
                            
                            getline(readBookFile,myText);
                            writeBookFile << myText << endl;

                            getline(readBookFile,myText);
                            writeBookFile << myText << endl;

                            writeBookFile << b.getStockCount() << endl;

                            getline(readBookFile,myText);
                            getline(readBookFile,myText);
                            writeBookFile << myText << endl;

                            getline(readBookFile,myText);
                            writeBookFile << myText << endl;

                        }else{
                            writeBookFile << myText << endl;
                        }
                    }
                    remove("book.txt");
                    rename("book1.txt","book.txt");

                    readBookFile.close();
                    writeBookFile.close();

                }else{
                    cout << "---------------Error---------------"<<endl;
                    cout << "No Such book in your Inventory."<<endl;
                }

            }else if(userInput == 'n'){
                book b = book();
                string title, author, publisher;
                float price;
                int quantity;

                cin.ignore();
                cout << endl<<"Enter book title: ";
                getline(cin , title);
                b.setTitle(title);
                cout << endl << "Enter book author: ";
                getline(cin , author);
                b.setAuthor(author);
                cout << endl << "Enter book publisher: ";
                getline(cin , publisher);
                b.setPublisher(publisher);
                cout << endl << "Enter Stock quantity: ";
                cin >> quantity;
                b.setStockCount(quantity);
                cout << endl << "Enter book price: ";
                cin >> price;
                b.setprice(price);
                b.setAvailability();

                ofstream writeOnBookFile ("book.txt", ios::app);
                writeOnBookFile << b.getTitle() <<endl << b.getAuthor() <<endl
                <<b.getPublisher() <<endl << b.getStockCount() << endl << b.getAvailability() <<endl
                << b.getPrice() <<endl;
                writeOnBookFile.close();

                cout <<endl<<endl <<"---------------Results---------------"<<endl;
                cout<< "Book Added to Inventory."<<endl;
            }else{
                cout << "---------------Error---------------"<<endl;
                cout << "Invalid Command."<<endl;
            }
        }
        }else{
            cout << "---------------No Session---------------"<<endl;
            cout << "Access Denied"<< endl;
        }
        
    }

void AdminUI(){
    char userInput;
    bool authenticLogin;
    string * loginDetails;
    cout << "---------------------------------------" << endl;
    cout << "**************Admin Login**************" << endl;
    cout << "---------------------------------------" << endl;
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
               authenticLogin=true;
               a.setPassword(myText);
               break;
           }
       }
    }

    MyReadFile.close();


if (authenticLogin){
    while(authenticLogin){
    cout << endl << "-------------------Session-------------------"<<endl;
    cout<< "Press a--------->To add staff."<< endl;
    cout<< "Press m--------->To modify staff details."<< endl;
    cout<< "Press d--------->To delete staff."<< endl;
    cout << "Press c--------->For delete customer."<<endl;
    cout<< "Press g--------->For generating sales report."<< endl;
    cout<< "Press l--------->For logging out."<< endl;
    cout << "Your input: ";
    cin >> userInput;
    cout <<endl;


    string id, updateValue, name, password, jobTitle;
    double salary;
    employee e = employee ();
    bool found, illegal,foundCustomer, isPass, isName, isJobTitle, isSalary = false;
    ifstream readFile ("employee.txt");
    ofstream writeFile ("employee1.txt", ios :: app);
    ofstream WriteFile ("employee.txt", ios :: app);
    ifstream rcusFile ("customer.txt");
    ofstream wcusFile ("customer1.txt", ios::app);
    string  n;

    switch(userInput){
        case 'c':
            cout << "Enter name of customer: ";
            cin.ignore();
            getline(cin, n);
            cout << endl;
            while(getline(rcusFile,myText)){
                if(myText == n){
                    getline(rcusFile,myText);
                    getline(rcusFile,myText);
                    getline(rcusFile,myText);
                    foundCustomer = true;
                }else{
                    wcusFile << myText <<endl;
                }
            }

            remove("employee1.txt");
            remove("customer.txt");
            rename("customer1.txt", "customer.txt");
            rcusFile.close(); wcusFile.close();

            if(foundCustomer){
                cout  << "-------------------Results-------------------"<<endl;
                cout << "Customer successfully deleted" <<endl;
            }else{
                cout  << "-------------------Results-------------------"<<endl;
                cout << "Customer does not exist in your database."<<endl;
            }
            break;
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
            
            WriteFile  << e.getId() << endl << e.getPassword() << endl << e.getName ()
            << endl << e.getJobTitle() << endl << e.getSalary() << endl;

            cout  << "-------------------Results-------------------"<<endl;
            cout << "Added employee!"<<endl;

            remove("employee1.txt");
            remove("customer1.txt");
            WriteFile.close();
            writeFile.close();
            readFile.close();

            break;
        case 'm':
            found = false;
            cout << "Enter employee id: "; cin >> id ; cout <<endl;
            cout << "What do you want to update? (press p for password, n for name, j for job title, s for salary): ";
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
            }else{
                isSalary = isPass = isJobTitle = isName = false;
            }


            cout << "Enter Update value: ";
            cin.ignore();
            getline(cin, updateValue);
            cout << endl;
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

                        
                    }else{
                        writeFile << myText <<endl; //p
                        
                        getline(readFile, myText);
                        writeFile << myText <<endl; //n
                        
                        getline(readFile, myText);
                        writeFile << myText <<endl; //j

                        getline(readFile, myText);
                        writeFile << myText <<endl; // s

                        cout << "Illegal command" << endl; 
                        illegal =true;                       
                    }
                found = true;
                    
                }else{
                    writeFile << myText<< endl;
                }
            }

            remove("customer1.txt");
            remove("employee.txt");
            rename ("employee1.txt","employee.txt");
            readFile.close();
            writeFile.close();
            WriteFile.close();
            if (!found ) {
                cout << "Employee with id " << id << " doesn't exist" << endl; 
            }else if (found && !(illegal)){
                cout  << "-------------------Results-------------------"<<endl;
                cout << "Updated successfully" << endl;
            }
            break;
        case 'd':
            cout << "Enter employee id: "; cin >> id ; cout <<endl;
            cout << "deleting employee with id " << id << "...." << endl;
            found = false;
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

            remove("customer1.txt");
            remove("employee.txt");
            rename ("employee1.txt","employee.txt");
            readFile.close();
            writeFile.close();
            WriteFile.close();
            if (!found) {
                cout << "Employee with id " << id << " doesn't exist" << endl; 
            }else{
                cout  << "-------------------Results-------------------"<<endl;
                cout << "Deleted successfully" << endl;
            }             
            break;
        case 'g':
            //need to this
            remove("employee1.txt");
            remove("customer1.txt");
            break;
        case 'l':
            authenticLogin = false;
            cout  << "--------------Terminating Session-------------------"<<endl;
            remove("employee1.txt");
            remove("customer1.txt");
            break;
        default:
            cout  << "-------------------Error-------------------"<<endl;
            cout<< "Illegal command"<<endl;
    }
    }
}else{
            cout  << "-------------------Error-------------------"<<endl;
            cout<< "Access denied"<< endl;
}


}

int main (void) {
    bool terminate;
    char userInput;

    while(!terminate){
        cout <<endl<<endl<< "----------------------Home page-----------------------"<<endl;
        cout << "Press s----------->For staff login." << endl << "Press a----------->For admin login." << endl << "Press c----------->To buy." << endl << "press t----------->To terminate."<<endl<< "User Input: "; 
        cin >> userInput;

        if(userInput =='s'){
            staffUI();
        }else if (userInput == 'a'){
            AdminUI();
        }else if (userInput == 't'){
            terminate = true;
            cout<<endl << "----------Program terminating----------"<<endl;
        }else if (userInput == 'c'){
            customerUI();
        }else{
            cout<<endl << "Illegal command. Try again."<<endl;
        }


    }


    
    return 0;
}