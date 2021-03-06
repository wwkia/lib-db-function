#include "cmpt_error.h"
#include "comparefunc.h"
#include "masterSort.h"

using namespace std;

// Pre-condition:
//   Takes in: Book 1 and Book 2
// Post-condition:
//   inherits from mastersort 
//   compares each bool returning either true or false to the comparision
//   of a name of a book
class Sort_name : Sort(){ 
public:
	bool operator() (const Book& book1, const Book& book2) {
		string name1 = book1.name.toLowerCase();
		string name2 = book2.name.toLowerCase();
		if (name1.compare(name2) == 0)
			return false;
		else if (name1.compare(name2) < 0)
			return true;
		return false;
	}
};

// Pre-condition:
//   Takes in: Book 1 and Book 2
// Post-condition:
//   inherits from mastersort 
//   compares each bool returning either true or false to the comparision
//   of a author of a book
class Sort_author : Sort(){
public:
	bool operator() (const Book& book1, const Book& book2) {
		string author1 = book1.author.toLowerCase();
		string author2 = book2.author.toLowerCase();
		if (author1.compare(author2) == 0)
			return false;
		else if (author1.compare(author2) < 0)
			return true;
		return false;
	}
};

// Pre-condition:
//   Takes in: Book 1 and Book 2
// Post-condition:
//   inherits from mastersort 
//   compares each bool returning either true or false to the comparision
//   of a date of a book
class Sort_date : Sort(){
public:
	bool operator() (const Book& book1, const Book& book2) {
		return (book1.date < book2.date);
	}
};

// Pre-condition:
//   Takes in: Book 1 and Book 2
// Post-condition:
//   inherits from mastersort 
//   compares each bool returning either true or false to the comparision
//   of a type of a book
class Sort_type : Sort(){
public:
	bool operator() (const Book& book1, const Book& book2) {
		string type1 = book1.type.toLowerCase();
		string type2 = book2.type.toLowerCase();
		if (type1.compare(type2) == 0)
			return false;
		else if (type1.compare(type2) < 0)
			return true;
		return false;
	}
};

// Pre-condition:
//   Takes in: Book 1 and Book 2
// Post-condition:
//   inherits from mastersort 
//   compares each bool returning either true or false to the comparision
//   of a isbn of a book
class Sort_isbn10 : Sort(){
public:
	bool operator() (const Book& book1, const Book& book2) {
		string tmp1 = book1.isbn[0].to_string();
		string tmp2 = book2.isbn[0].to_string();
		string isbn10_1 = tmp1.toLowerCase();
		string isbn10_2 = tmp2.toLowerCase();
		if (isbn1.compare(isbn2) == 0)
			return false;
		else if (isbn1.compare(isbn2) < 0)
			return true;
		return false;
	}
};

// Pre-condition:
//   Takes in: Book 1 and Book 2
// Post-condition:
//   inherits from mastersort 
//   compares each bool returning either true or false to the comparision
//   of a isbn of a book
class Sort_isbn13 : Sort(){
public:
	bool operator() (const Book& book1, const Book& book2) {
		string tmp3 = book1.isbn[1].to_string();
		string tmp4 = book2.isbn[1].to_string();
		string isbn13_1 = tmp1.toLowerCase();
		string isbn13_2 = tmp2.toLowerCase();
		if (isbn13_1.compare(isbn13_2) == 0)
			return false;
		else if (isbn13_1.compare(isbn13_2) < 0)
			return true;
		return false;
	}
};

// Pre-condition:
//   Takes in: Book 1 and Book 2
// Post-condition:
//   inherits from mastersort 
//   compares each bool returning either true or false to the comparision
//   of the number of pages in a book
class Sort_pages : Sort(){
public:
	bool operator() (const Book& book1, const Book& book2) {
		return (book1.pages < book2.pages);
	}
};

// Pre-condition:
//   Takes in: Book 1 and Book 2
// Post-condition:
//   inherits from mastersort 
//   compares each bool returning either true or false to the comparision
//   of relevancy of a search of a book
class Sort_searchmatch : Sort(){
public:
	bool operator() (const Book& book1, const Book& book2) {
		return (book1.searchmatch < book2.searchmatch);
	}
};
