// L14_Ex1_Inheritance.cpp
#include <iostream>
#include <cstring>

using namespace std;

// --------- BaseSig class and methods ------------------------------
class BaseSig{
	private:
		// neither derived classes nor other users
		// can access private members
	
	protected:	// accessible by derived classes, not by other users.
		int length;
		int *raw_data;
		
	public:
		BaseSig();		// default constructor.
		BaseSig(int L);	// parametric constructor
		~BaseSig();		// destructor
		int getLength() { return length; };
		int getRawValue(int pos);
		static int numObjects;	// static, only one member for the entire hierarchy
		virtual void printInfo();
};

int BaseSig::numObjects = 0;	// initialize static data member

// Base class constructor
BaseSig::BaseSig(){
	length = 0;
	raw_data = NULL;
	numObjects++;
	cout << "BaseSig default constructor" << endl;
}

// Base class parametric constructor
// Note that the data array is not being initialized (we could read from a file)
BaseSig::BaseSig(int L){
	length = L;
	raw_data = new int[L];
	if(raw_data == NULL)
		cerr << "Error in memory allocation";
	numObjects++;
	cout << "BaseSig parametric constructor" << endl;
}

// Base class destructor
BaseSig::~BaseSig(){
	delete[] raw_data;
	cout << "Goodbye, BaseSig." << endl;
}

int BaseSig::getRawValue(int pos) {
	if(pos < 0)			// invalid index
		return(raw_data[0]);
	else if(pos >= length)	// invalid index
		return(raw_data[length-1]);	
	else
		return(raw_data[pos]);
}

void BaseSig::printInfo() {
	cout << "\nLength: " << length << endl;
}
// ------------------------------------------------------------------

// --------- ExtendSig class and methods ----------------------------
class ExtendSig : public BaseSig{ // ExtendSig is derived from class BaseSig
//BaseSig is a public base class
	private: 
		double average;		// add new data members
		double *data;
		
	public:
		ExtendSig(int L);	//derived classes need a new constructor
		~ExtendSig();
		
		// define new member functions
		double getValue(int pos);
		int setValue(int pos, double val);
		double getAverage();
		
		// redefine member function. Virtual keyword not needed
		void printInfo();	// new standard: explicit "override" keyword can be used
};

// Derived class constructor. Note how the Base constructor is called.
ExtendSig::ExtendSig(int L) : BaseSig(L) {
	data = new double[L];
	if(data == NULL)
		cerr << "Error in memory allocation";
	else{
		for(int i = 0; i < L; i++)
			data[i] = (double)raw_data[i];
		average = getAverage();
	}
	cout << "ExtendSig parametric constructor" << endl;
}

// Derived class destructor
ExtendSig::~ExtendSig() {
	//delete raw_data;
	delete data;
	cout << "Goodbye, ExtendSig." << endl;
}

double ExtendSig::getValue(int pos) {
	if(pos < 0)			// invalid index
		return(data[0]);
	else if(pos >= length)	// invalid index
		return(data[length-1]);	
	else
		return(data[pos]);
}

int ExtendSig::setValue(int pos, double val) {
	if((pos < 0) || (pos >= length))
		return(-1);	// invalid index
	else {
		data[pos] = val;
		average = getAverage();
		return(0);	// success
	}
}

double ExtendSig::getAverage() {
	if(length == 0)
		return(0.0);
	else {
		double temp = 0.0;
		for(int i = 0; i < length; i++)
			temp += data[i];
		return(temp/(double)length);
	}
}

// Redefined printInfo function for derived class
void ExtendSig::printInfo() {
	cout << "\nLength: " << length << endl
		 << "Average: " << average << endl;
}
// ------------------------------------------------------------------

#define N 4
#define CASE 1
// Main function. A few examples
int main(){

// ----------- Not Recommended --------------------------------------
#if CASE == 0
	BaseSig Barray[N];		// array of BaseSig objects
	
	cout << "\nBefore filling the array" << endl;
	for(int i = 0; i < N; i++) {
		if(i%2 == 0)
			Barray[i] = BaseSig(i+1);
		else
			Barray[i] = ExtendSig(i+1);
	}
	
	cout << "\nBefore printing info" << endl;
	
	for(int i = 0; i < N; i++) {
		Barray[i].printInfo();
	}
#endif
// ------------------------------------------------------------------

#if CASE != 0
	BaseSig *Barray[N];		// array of pointers to BaseSig
	
	cout << "\nBefore filling the array" << endl;
	for(int i = 0; i < N; i++) {
		if(i%2 == 0)	// even numbers will be BaseSig objects
			Barray[i] = new BaseSig(i+1);
		else			// odd numbers will be ExtenSig objects
			Barray[i] = new ExtendSig(i+1);
	}
	
	cout << "\nBefore printing info" << endl;
	
	for(int i = 0; i < N; i++) {
		Barray[i]->printInfo();
	}
	
	for(int i = 0; i < N; i++) {
		delete Barray[i];
	}
#endif

	return 0;
}