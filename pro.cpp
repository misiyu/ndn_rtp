#include <iostream>
#include "ndn_rtpp.h"

using namespace std;

int main()
{
	ndn_rtpp mypro("/localhost/nfd/producer") ;
	char buff[16090] ;
	for (int i = 0; i < 10000000; i++) {
		usleep(40000) ;	// 40ms
		if((i+1)%100 == 0) sleep(6) ;
		memset(buff,'a'+i%26,sizeof(buff)) ;
		mypro.sendobj(buff,sizeof(buff)) ;
	}

	return 0;
}
