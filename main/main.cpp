
#include <iostream>
#include "Composant1.h"
#include "Composant2.h"
#include <string.h>
#include <dlfcn.h>

using namespace std;

int main(int argc, char ** argv)
{
	int data1=3;
	int data2=5;

	int valeur1;
	int valeur2;
	string fct1, fct2, library1, library2;
	
	//valeur1=composant1(data1,data2);
	//valeur2=composant2(data1,data2);

	void *composant1_handle = dlopen("libComposant1.so", RTLD_LAZY);
	void *composant2_handle = dlopen("libComposant2.so", RTLD_LAZY);
	

	int (*ptr1)(int,int);
	int (*ptr2)(int,int);
	

	cout << "Function1 : " << endl;
	cin >> fct1 ;

	cout << "Function2 : " << endl;
	cin >> fct2 ;

	if (fct1=="composant1"){
		library1 = "libComposant1.so";
		library2 = "libComposant2.so";
	}
	else{
		library1 = "libComposant2.so";
		library2 = "libComposant1.so";
	}

	composant1_handle = dlopen(library1.c_str(), RTLD_LAZY);
	composant2_handle = dlopen(library2.c_str(), RTLD_LAZY);

	ptr1 = (int (*)(int, int))dlsym(composant1_handle, fct1.c_str());
	ptr2 = (int (*)(int, int))dlsym(composant2_handle, fct2.c_str());

	if (composant1_handle==NULL || composant2_handle==NULL || ptr1==NULL || ptr2==NULL){
		printf("ERROR NULL");
		exit(1);
	}

	valeur1=(*ptr1)(data1, data2);
	valeur2=(*ptr2)(data1, data2);


	cout << getComposant1Version() << endl;
	cout << "valeur 1 :" << ptr1(data1, data2) << " valeur 2 :" << ptr2(data1, data2) << endl;
}
