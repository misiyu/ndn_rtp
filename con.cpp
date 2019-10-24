#include <iostream>
#include "ndn_rtpc.h"

using namespace std;

int main()
{
	ndn_rtpc mycon("/localhost/nfd/producer") ;
	char buff[200000] ;
	int len ;
	while(1){
		len = mycon.readobj(buff) ;
		cout << "len = " << len << "  buff[0] = " << buff[0] << endl ;
	}

	return 0;
}
