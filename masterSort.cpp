#include "masterSort.h"  // check syntax

class Sort::Sort() {
	virtual bool operator() (const Book& book1, const Book& book2) {
		return(book1.date < book2.date);  // can be anything really
	}
}