#ifndef COMPAREFUNC_H
#define COMPAREFUNC_H  // check syntax

using namespace std;

class Sort_name(){
	bool operator() (const Book& book1, const Book& book2);
}

class Sort_author(){
	bool operator() (const Book& book1, const Book& book2);
}

class Sort_date(){
	bool operator() (const Book& book1, const Book& book2);
}

class Sort_type(){
	bool operator() (const Book& book1, const Book& book2);
}

class Sort_isbn10(){
	bool operator() (const Book& book1, const Book& book2);
}

class Sort_isbn13(){
	bool operator() (const Book& book1, const Book& book2);
}

class Sort_pages(){
	bool operator() (const Book& book1, const Book& book2);
}

class Sort_searchmatch(){
	bool operator() (const Book& book1, const Book& book2);
}

#endif