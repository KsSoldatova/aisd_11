#include "Header.h"


int menu()
{
	cout << "What are you want to do? To press.." << endl;
	cout << "1 - summarize with new line" << endl;
	cout << "2 - Add new top to end" << endl;
	cout << "3 - Add new top to start" << endl;
	cout << "4 - Get length" << endl;
	cout << "5 - Get image of broken line" << endl;
	cout << "6 - First letter of my surname" << endl;
	cout << "7 - Go out" << endl;
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
	point p;
	p.x = x;
	p.y = y;
	return p;
}
int main()
{
	cout << "Enter the number of tops of broken line: " << endl;
	int size, size1;
	cin >> size;
	Lines a(size);
	
	point p, p1;
	for (int i = 0; i < size; i++) {

		p = get_points();
		a = a + p;
	}
	int m;
	do {
		m = menu();
		if (m == 1)
		{
			cout << "Enter the number of tops of new broken line: " << endl;
			cin >> size1;
			Lines c(size1);
			for (int i = 0; i < size1; i++) {

				p1 = get_points();
				c  = c + p1;
			}
			a += c;
			for (int i = 0; i < a.get_size(); i++)
			{
				cout << a[i];
			}
			cout << a;
			break;
		}
		if (m == 2)
		{
			cout << "Enter x and y for new point: " << endl;
			p1 = get_points();
			a  = a + p1;
			cout << a;
			break;
		}
		if (m == 3)
		{
			Lines c(2);
			cout << "Enter x and y for new point" << endl;
			p1 = get_points();
			c = p1 + a;
			cout << c;
			break;
		}
		if (m == 4)
		{
			cout << "length of broken line is " << a.length() << endl;
			break;
		}
		if (m == 5)
		{
			for (size_t i = 0; i < a.get_size(); i++)
			{
				cout << a[i];
			}
			cout << a;
			break;
		}
		if (m==6)
		{
			a.myletter();
			break;
		}
	} while (m != 7);




}
