#include <iostream>
#include <cmath>
#include "rbt.h"
#include "rbt_node.h"

using std::cout;
using std::endl;

int main() {
	RBT<int> rbt;
//	cout << "**********0********" << endl;
//	cout << rbt << endl;
//	cout << "**********1********" << endl;
//	rbt.insert(70,300);
//	cout << rbt << endl;
//	cout << "**********2********" << endl;
//	for(int i=0;i<10;++i) 
//		rbt.insert(random()%100, random()%100);
//	cout << rbt << endl;
//	cout << "********search*****" << endl;
//	cout << rbt.search(90).data << endl;
//	cout << "********max********" << endl;
//	cout << rbt.max().data << endl;
//	cout << "********min********" << endl;
//	cout << rbt.min().data << endl;
	cout << "******display********" << endl;
	rbt.display();
	cout << "******insert0********" << endl;
	rbt.insert(70,300);
	rbt.display();
	cout << "******insert1********" << endl;
	for(int i=0;i<20;++i) { 
		rbt.insert(random()%100, random()%100);
		rbt.display();
		cout << "******insert" << i << "********" << endl;
	}
	rbt.display();
	cout << "******display********" << endl;
	rbt.display();
	cout << "******remove********" << endl;
	rbt.remove(77);
	rbt.remove(70);
	rbt.remove(90);
	rbt.remove(80);
	rbt.remove(93);
	cout << rbt << endl;
	cout << "******display********" << endl;
	rbt.display();
	return 0;
}
