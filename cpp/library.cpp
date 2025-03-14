#include<iostream>
#include<vector>
#include<fstream>
#include<sstream>
#include<unordered_map>
#include<algorithm>>

using namespace std;

struct Book{
    int id;
    string title;
    string author;
    bool isBorrowed;
};

vector<Book> library;
int bookID = 1;

void addBook();
void displayBooks();



void addBook(){
    Book newBook;
    newBook.id = bookID++;
    cout<<"Enter Book Titile";
    cin.ignore();
    getline(cin,newBook.title);
    cout<<"Enter Author Name";
    getline(cin,newBook.author);
    newBook.isBorrowed = false;
    library.push_back(newBook);

}

void displayBooks(){
    for(const auto &book: library){
        cout<<book.id <<" "<<book.title;
    }
}

void searchBook(){
    string keyword;
    getline(cin,keyword);
    for(const auto& book: library){
        if(book.title.find(keyword) != string::npos){
            cout<<"Book Found";
            cout<<"ID:"<<book.id;
        }
    }
}

void deleteBook(){
    int id;
    cin>> id;
    for(auto it = library.begin();it != library.end();++it){
        if(it->id == id){
            library.erase(it);
            cout<<"Book deleted";
            return;
        }
    }
    cout<<"Boot not found";
}

void updateBook(){
    int id;
    cout<<"Enter Book id";
    cin>>id;
    for(auto &book: library){
        if(book.id == id){
            cin.ignore();
            getline(cin,book.title);
            getline(cin,book.author);
            return;
        }
    }
    cout<<"Book not found";
}

void borrowBook(){
    int id;
    cout<<"Enter book id";
    cin>>id;
    for(auto &book: library){
        if(book.id == id){
            book.isBorrowed = true;
            cout<<" Book borrowed";
        }
    }
    cout<<"Book not available";
}

void returnBook(){
    int id;
    cout<<"Enter book id";
    cin>>id;
    for(auto &book: library){
        if(book.id == id && book.isBorrowed){
            book.isBorrowed = false;
            cout<<"Book returned to library";
            return;
        }
    }
    cout<<"Invalid book";
}

void saveDatatoFile(){
    ofstream file("library.txt");
    for(const auto &book: library){
        file <<book.id<<","<<book.title<<","<<book.author<<","<<book.isBorrowed;
    }
    file.close();

}

void loadDataFromFile(){
    ifstream file("library.txt");
    if(!file) return;
    library.clear();
    string line;
    while(getline(file,line)){
        stringstream ss(line);
        Book book;
        string temp;
        getline(ss,temp,','); book.id = stoi(temp);
        getline(ss,book.title,',');
        getline(ss,book.author,',');
        getline(ss,temp,','); book.isBorrowed = stoi(temp);
        library.push_back(book);
        bookID = max(bookID,book.id+1);
    }
    file.close();
}
unordered_map<string,string> users = {{"admin","admin123"},{"user","user123"}};
bool userlogin(bool &isAdmin){
    string username, password;
    cout<<"Enter username";
    cin>>username;
    cout<<"Enter password";
    cin>>password;

    if(users.find(username) != users.end() && users[username] == password){
        isAdmin = (username == "admin");
        cout<<"login successfull";
        return true;
    }else{
        cout<<"Invalid credentials";
        return false;
    }
}

void sortBooks(){
    sort(library.begin(),library.end(),[](Book a, Book b){
        return a.title < b.title;
    });
    displayBooks();
}

void generateReport(){
    int borrowedCount = 0, availableCount = 0;
    for(const auto &book : library){
        if(book.isBorrowed) borrowedCount++;
        else availableCount++;
    }
    cout<<"Available Books Count:"<<availableCount;
    cout<<"Borrowed Books Count:"<<borrowedCount;
}

void exportToCSV(){
    ofstream file("library_report.csv");
    file << "ID,Title,Author";
    for(const auto &book: library){
        file <<book.id<<","<<book.title<<","<<book.author;
    }
    file.close();
    cout<<"Data exported to csv file.";
}