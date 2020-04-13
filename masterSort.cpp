#include "masterSort.h"  // check syntax

// Is a sorting class which is used by all of the functions in comparefunc and
// is made virtual so any of the classes of different types in comparefunc can
// use the function and overwrite it to complete the desired sort

class Sort::Sort() {
	virtual bool operator() (const Book& book1, const Book& book2) {
		return(book1.date < book2.date);  // can be anything really
	}
}