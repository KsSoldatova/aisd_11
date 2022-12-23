#include <GLFW/glfw3.h>
#include <iostream>
#include <math.h>
#pragma warning(disable : 4996)
using namespace std;

struct point {
	double x, y;
	//*point() {
	//	x = 0;
	//	y = 0;
	//}*/
	point(double _x = 0, double _y = 0) {
		x = _x;
		y = _y;
	}
	//point(const point& p) {
	//	x = p.x;
	//	y = p.y;
	//}
	point operator =(const point& p) {
		x = p.x;
		y = p.y;
		return *this;
	}
	friend ostream& operator<<(ostream& os, const point& rhs)
	{
		os << "point: (" << rhs.x << "," << rhs.y << ")" << endl;
		return os;
	}
};

class Lines {
	point* data = nullptr;
	int size;
public:
	Lines(int _size = 0) {
		if (_size == 0) return;
		size = _size;
		data = new point[size];
	}
	/*Lines(double _x,double _y) {
		size = 1;
		data = new point[size];
		data[0] = point(_x,_y);
	}*/
	/*Lines(const point& p) {
		size = 1;
		data = new point[size];
		data[0] = p;
	}*/
	/*~Lines() {
		delete[] data;
	}*/

	int get_size() const {
		return size;
	}

	point& operator[](int i) {
		if (i >= size and i < 0) {
			throw "Invalid index";
		}
		return data[i];
	}
	point operator[](int i) const {
		if (i >= size and i < 0) {
			throw "Invalid index";
		}
		return data[i];
	}
	point& operator <<(int i) {
		if (i >= size and i < 0) {
			throw "Invalid index";
		}
		return data[i];
	}
	friend ostream& operator<<(ostream& os, const Lines& rhs)
	{
		GLFWwindow* window;

		/* Initialize the library */
		if (!glfwInit())
		{
			throw exception("Error init");
		}

		/* Create a windowed mode window and its OpenGL context */
		window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
		if (!window)
		{
			glfwTerminate();
			throw exception("Error create window");
		}

		/* Make the window's context current */
		glfwMakeContextCurrent(window);

		/* Loop until the user closes the window */
		while (!glfwWindowShouldClose(window))
		{
			/* Render here */
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

			glBegin(GL_LINE_STRIP);
			for (size_t i = 0; i < rhs.size; i++)
			{
				glVertex2f(rhs.data[i].x, rhs.data[i].y);
			}
			glEnd();

			/* Swap front and back buffers */
			glfwSwapBuffers(window);

			/* Poll for and process events */
			glfwPollEvents();
		}

		glfwTerminate();
		os << endl;
		return os;
	}

	Lines& operator+=(const Lines& l) {
		Lines* temp = new Lines[l.size + size];
		temp = this;
		*this = *temp;

		for (int i = 0, j = size; i < l.size; i++, j++)
		{
			(*this)[j] = l[i];
		}

		size += l.size;
		return *this;
	}


	Lines& operator +(const point& p) {
		Lines* temp = new Lines[size+1];
		temp = this;
		(*this)[size] = p;
		size++;
		*this = *temp;
		return *this;
	}
	

	friend Lines operator+(const point& p, Lines& l) {
		Lines* tmp = new Lines[l.get_size()+1];
		tmp = &l;
		l = *tmp;
		for (int i = l.get_size() - 1; i != 0; i--) {
			l[i] = l[i - 1];
		}
		l[0] = p;
		return l;
	}

	bool operator==(const Lines& l) {
		if (l.size != size) {
			return false;
		}
		else {
			for (int j = 0; j < size; j++)
			{
				if ((*this)[j].x != l[j].x || (*this)[j].y != l[j].y) return false;
			}
			return true;
		}
	}
	bool operator!=(const Lines& l) {
		return !(*this == l);
	}
	void myletter() {
		point p(0, 0);
		(*this) = (*this) + p;
		point p1(-0.2, 0);
		(*this) = (*this)  + p1;
		point p2(-0.2, 0.5);
		(*this) = (*this)  + p2;
		point p3(0.01, 0.5);
		(*this) = (*this)  +  p3;
		cout << this;
	}

	double length() const {
		double len = 0;
		for (size_t i = 0; i < size - 1; i++)
		{
			len += pow(pow(data[i + 1].x - data[i].x, 2) + pow(data[i + 1].y - data[i].y, 2), 0.5);
		}
		return len;
	}
};
