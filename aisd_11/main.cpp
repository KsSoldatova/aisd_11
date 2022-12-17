#include "Header (1).h"



int menu()
{
	cout << "What are you want to do? To press.." << endl;
	cout << "1 - summarize with new line" << endl;
	cout << "2 - Add new top to end" << endl;
	cout << "3 - Add new top to start" << endl;
	cout << "4 - Get length" << endl;
	cout << "5 - Get image of broken line" << endl;
	cout << "6 - First letter of my surname" << endl;
	cout << "7 - Find the top by index" << endl;
	cout << "8 - Go out" << endl;
	int m;
	cin >> m;
	return m;
}
point get_points() {
	double x = 0, y = 0;
	cout << "Enter x: " << endl;
	cin >> x;
	cout << "Enter y:" << endl;
	cin >> y;
	return point(x, y);
}
int main()
{
	
	cout << "Enter the number of tops of broken line: " << endl;
	int size;
	cin >> size;
	Lines a(0,0);
	Lines c(0, 0);
	point p,p1;
	for (int i = 0; i < size; i++) {

		p = get_points();
		a += p;
	}
	int m;
	do {
		m = menu();
		switch (m) {
		case 1:
			cout<<"Enter the number of tops of new broken line: " << endl;
			int size1;
			cin >> size1;
			for (int i = 0; i < size1; i++) {

				p1 = get_points();
				a += p1;
			}
			for (size_t i = 0; i < a.get_size(); i++)
			{
				cout << a[i];
			}
			break;
		case 2:
			cout << "Enter x and y for new point: " << endl;
			p1 = get_points();
			a += p1;
			for (size_t i = 0; i < a.get_size(); i++)
			{
				cout << a[i];
			}
			break;
		case 3:
			cout << "Enter x and y for new point" << endl;
			p1 = get_points();
			c += p1;
			c += a;
			for (size_t i = 0; i < c.get_size(); i++)
			{
				cout << c[i];
			}
			a = c;
			break;
		case 4:
			cout << "length of broken line is " << a.length() << endl;
			break;
		case 5:
			for (size_t i = 0; i < a.get_size(); i++)
			{
				cout << a[i];
			}
			cout << a;
			break;
		case 6:
			Lines b(0, 0);
			b += point(-0.2, 0);
			b += point(-0.2, 0.5);
			b += point(0.01, 0.5);
			for (size_t i = 0; i < b.get_size(); i++)
			{
				cout << b[i];
			}
			cout << b;
			break;
		//case 7:
		//	cout << "Enter index of the top" << endl;
		//	int index;
		//	cin >> index;
		//	if (index <= size) {
		//		for (size_t i = 0; i < a.get_size(); i++)
		//		{
		//			if (a[i].x == a[index].x && a[i].y == a[index].y)
		//			{
		//				cout << a[i];
		//			}
		//		}
		//	}
		}
	} while (m != 8);
	

	
	
}