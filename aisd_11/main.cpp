using namespace std;

#include <iostream>
#include <cstdlib>
#include <math.h>



class broken_line
{
private:
	struct Points
	{
		int x = 0, y = 0;
	};
	Points* line = NULL;
	int size = 0, more_number = 0;

public:
	broken_line(int size = 0)
	{
		if (size == 0)
		{
			this->size = size;
			return;
		}
		more_number = size * 2;
		line = new Points[more_number];
		this->size = size;
	}
	Points* GetLine() const { return line; }
	int GetX() const { return line->x; }
	int GetY() const { return line->y; }
	int Get_size() const { return size; }
	int Get_more_points() const { return more_number; }

	friend std::ostream& operator << (std::ostream& os, const broken_line point)
	{
		for (int i = 0; i < point.Get_size(); i++)
		{
			os << '(' << point[i].x << ';' << point[i].y << ')' << endl;

		}
		return os;
	}


	Points operator [] (int index) const //для чтения
	{
		if (index >= 0 && index < size)
			return (line[index]);
		throw "!invalid index!";
	}
	Points& operator [] (int index) //для записи
	{
		if (index >= 0 && index < size)
			return (line[index]);
		throw "!invalid index!";
	}

	broken_line operator +(broken_line& other) //конкатенация двух линий 
	{
		if (this->size + other.Get_size() >= this->more_number)
		{
			this->more_number = (this->Get_more_points() + other.Get_size());
			broken_line* tmpline = new broken_line[this->Get_more_points()];
			tmpline = this;
			*this = *tmpline;
		}
		for (int i = 0, j = this->size; i < other.Get_size(); i++, j++)
		{
			(*this)[j] = other[i];
		}
		this->size += other.Get_size();
		return *this;
	}
	broken_line operator +(Points& point)//сложение ломаной и точки, добавление в конец 
	{
		this->size++;
		if (this->Get_size() == this->Get_more_points())
		{
			this->more_number *= 2;
			broken_line* tmpline = new broken_line[this->Get_more_points()];
			tmpline = this;
			*this = *tmpline;
		}
		(*this)[this->Get_size() - 1] = point;
		return *this;
	}
	friend broken_line operator +(Points& point, broken_line& tmp_line)//сложение ломаной и точки, добавление в начало
	{
		tmp_line.size++;
		if (tmp_line.Get_size() == tmp_line.Get_more_points())
		{
			tmp_line.more_number *= 2;
			broken_line* tline = new broken_line[tmp_line.Get_more_points()];
			tline = &tmp_line;
			tmp_line = *tline;
		}
		for (int i = tmp_line.Get_size() - 1; i != 0; i--)
		{
			tmp_line[i] = tmp_line[i - 1];
		}
		tmp_line[0] = point;
		return tmp_line;
	}
	broken_line operator =(const broken_line& tmp_line)
	{
		for (int i = 0; i < tmp_line.Get_size(); i++)
		{
			(*this)[i] = tmp_line[i];
		}
		return *this;
	}
	bool operator == (const broken_line& other_line)
	{
		if (this->Get_size() == other_line.Get_size())
		{
			for (int i = 0; i < this->Get_size(); i++)
			{
				if ((*this)[i].x != other_line[i].x || (*this)[i].y != other_line[i].y)
					return false;
			}
			return true;
		}
		return false;
	}
	bool operator != (const broken_line& other_line)
	{
		if (this->Get_size() == other_line.Get_size())
		{
			for (int i = 0; i < this->Get_size(); i++)
			{
				if ((*this)[i].x != other_line[i].x || (*this)[i].y != other_line[i].y)
					return true;
			}
			return false;
		}
		return true;
	}
	double Length()
	{
		for (int i = 0; i < this->Get_size(); i++)
			cout << "[" << i + 1 << "]" << " = " << "(" << (*this)[i].x << ";" << (*this)[i].y << ")" << endl;
		double len = 0;
		for (int i = 0; (i + 1) < this->Get_size(); i++)
			len += pow(pow(abs((*this)[i + 1].x - (*this)[i].x), 2) + pow(abs((*this)[i + 1].y - (*this)[i].y), 2), 0.5);
		return len;
	}
	void PrintLine() const
	{

		std::cout << this[0];
	}
};



broken_line CreatingLine(broken_line& start_line) {
	int x, y;
	for (int i = 0; i < start_line.Get_size(); i++)
	{
		std::cout << endl << "Enter the coordinates of the point:" << endl;
		std::cout << endl << "x = ";
		std::cin >> x;
		std::cout << endl << "y = ";
		std::cin >> y;
		start_line[i].x = x;
		start_line[i].y = y;
	}
	return start_line;
}


int IndexPoint(broken_line& start_line, bool flag)
{
	system("cls");
	flag = true;
	int index = 0;
	while (flag)
	{
		int choice = 0;
		choice = getchar();
		if (choice == 8) return choice;
		while (flag)
		{
			std::cout << endl << "Enter index:" << endl;
			std::cin >> index;
			try {
				if (index <= 0 || index > start_line.Get_size()) throw "!There is no such index point!";
				flag = false;
			}
			catch (const char* ex)
			{
				std::cout << ex << endl;
				std::cout << endl << "Try again" << endl;
			}
		}
		flag = true;
		while (flag)
		{
			try {
				std::cout << "Select:" << endl;
				std::cout << "1) Read coordinates";
				std::cout << "   2) Change coordinates" << endl;
				cin >> choice;
				if (choice != 1 && choice != 2) throw"!There is no such index point";
				flag = false;
			}
			catch (const char* ex)
			{
				std::cout << ex << endl;
				std::cout << endl << "Try again" << endl;
			}
		}
		if (choice == 1) cout << "Coordinates: " << "(" << start_line[index - 1].x << ";" << start_line[index - 1].y << ")" << endl << endl;
		if (choice == 2)
		{
			int x = 0, y = 0;
			std::cout << "Enter х: ";
			std::cin >> x;
			std::cout << "Enter y: ";
			std::cin >> y;
			start_line[index - 1].x = x;
			start_line[index - 1].y = y;
			std::cout << start_line << endl;
			std::cout << "Coordinates of the point with index " << index << " = (" << start_line[index - 1].x << "; " << start_line[index - 1].y << ")" << endl << endl;
		}
		break;
	}
	return -1;
}


int SumLine(broken_line& start_line, bool flag)
{
	int choice = 0;
	bool flag1 = true;
	flag = true;
	int n = 0;
	std::cout << "Point coordinates of the first broken line" << endl;
	start_line.PrintLine();
	while (flag1)
	{
		try {
			std::cout << "Press the second broken line " << endl;
			flag = true;
			while (flag)
			{
				try
				{
					std::cout << "Number of points: ";
					cin >> n;
					if (n < 2) throw "The numbers of points must be >= 2";
					flag = false;
				}
				catch (const char* ex)
				{
					std::cout << ex << endl;
					std::cout << endl << "Try again" << endl;
				}
			}
		}
		catch (const char* ex)
		{
			std::cout << ex << endl;
			std::cout << endl << "Try again" << endl;
		}
		broken_line tmp_line(n);
		broken_line new_line = CreatingLine(tmp_line);
		flag1 = false;
		std::cout << "Point coordinates of the second broken line" << endl;
		new_line.PrintLine();
		start_line = start_line + new_line;
		std::cout << endl << "Result: " << endl;
		start_line.PrintLine();
		flag1 = true;
	}
	return -1;
}


int SumPoint_Line(broken_line& start_line, bool flag)
{
	int choice = 0;
	flag = true;
	while (flag)
	{
		int x = 0, y = 0;
		std::cout << "Press coordinates of the point which want to add: " << endl;
		std::cout << "x = ";
		cin >> x;
		std::cout << "y = ";
		cin >> y;
		broken_line point(1);
		point[0].x = x;
		point[0].y = y;
		broken_line tmp_line = point[0] + start_line;
		tmp_line.PrintLine();
		start_line = tmp_line;
		break;
	}
	return -1;
}


int SumLine_Point(broken_line& start_line, bool flag)
{
	int choice = 0;
	flag = true;
	while (flag)
	{
		int x = 0, y = 0;
		std::cout << "Press coordinates of the point which want to add: " << endl;
		std::cout << "x = ";
		std::cin >> x;
		std::cout << "y = ";
		std::cin >> y;
		broken_line point(1);
		point[0].x = x;
		point[0].y = y;
		broken_line tmp_line = start_line + point[0];
		start_line = tmp_line;
		tmp_line.PrintLine();
		break;
	}
	return -1;
}


int LenLine(broken_line& start_line)
{
	std::cout << "Length of the line: " << start_line.Length() << endl;
	return -1;
}


int Compare(broken_line& start_line)
{
	int choice = 0;
	int x = 0, y = 0;
	bool flag1 = true, flag = true;
	int n = 0;
	std::cout << "Point coordinates of the first broken line" << endl;
	start_line.PrintLine();
	while (flag1)
	{
		choice = getchar();
		if (choice == 8) return choice;
		try {
			std::cout << "Press the second broken line " << endl;
			flag = true;

			while (flag)
			{
				try
				{
					std::cout << "Number of points: ";
					std::cin >> n;
					if (n < 2) throw "The numbers of points must be >= 2";
					flag = false;
					flag1 = false;
				}
				catch (const char* ex)
				{
					std::cout << ex << endl;
					std::cout << endl << "Try again" << endl;
				}
			}
		}
		catch (const char* ex)
		{
			std::cout << ex << endl;
			std::cout << endl << "Try again" << endl;
		}

		broken_line tmp_line(n);
		broken_line new_line = CreatingLine(tmp_line);
		flag1 = false;
		new_line.PrintLine();
		if (start_line == new_line) cout << "The broken lines are equal!" << endl;
		if (start_line != new_line) cout << "The broken lines are unequal!" << endl;
		break;
	}
	return -1;
}

void menu0()
{
	system("cls");
	std::cout << endl << "Choose where you want to start" << endl << endl;
	std::cout << "1. Create a broken line" << endl;
	std::cout << "2. Create a first letter of my surname" << endl;
	std::cout << "3. Complete the job" << endl;

}

void menu1()
{
	std::cout << endl << endl << "Next choice: " << endl;
	std::cout << "1. Broken lines concatenation" << endl;
	std::cout << "2. Add the point to the end of line (add a point at the finish of the line)" << endl;
	std::cout << "3. Add the line to the point (add a point at the start of the line)" << endl;
	std::cout << "4. The length of the line" << endl;
	std::cout << "5. Compare broken lines" << endl;
	std::cout << "6. Know/change point coordinates of the broken line" << endl;
	std::cout << "7. Back to main menu" << endl;
}


void CreateLetter(int x, int y, broken_line& line)
{
	line[0].x = x;
	line[0].y = y;
	line[1].x = x-2;
	line[1].y = y;
	line[2].x = x-2;
	line[2].y = y + 4;
	line[3].x = x;
	line[3].y = y+4;
	line.PrintLine();
}


broken_line& MyLetter(bool flag)
{
	broken_line line(4);
	int choice = 0;
	int x = 0, y = 0;
	system("cls");
	std::cout << "Press coordinaes of the first point" << endl;
	std::cout << "х = ";
	cin >> x;
	std::cout << "y = ";
	cin >> y;
	CreateLetter(x, y, line);
	return line;
}




bool JobWithLine(bool flag, bool flag1, int choice, broken_line& start_line)
{
	menu1();
	flag = true;
	while (flag)
	{
		try {
			std::cin >> choice;
			if (choice > 8 || choice < 1) throw "!There is no such option!";
			flag = false;
		}
		catch (const char* ex)
		{
			std::cout << ex << endl;
			std::cout << endl << "Try again" << endl;
		}
	}
	if (choice == 1)
		if (SumLine(start_line, flag) == 8) flag1 = true;
	if (choice == 2)
		if (SumLine_Point(start_line, flag) == 8) flag1 = true;
	if (choice == 3)
		if (SumPoint_Line(start_line, flag) == 8) flag1 = true;
	if (choice == 4)
		if (LenLine(start_line) == 8) flag1 = true;
	if (choice == 5)
		if (Compare(start_line) == 8) flag1 = true;
	if (choice == 6)
		if (IndexPoint(start_line, flag) == 8) flag1 = true;
	if (choice == 7)
	{
		flag = true;
		flag1 = false;
	}

	return flag1;
}



int main()
{
	int choice = 0;
	bool flag = true, flag1 = true;
	while (flag)
	{
		menu0();
		std::cout << "Choice: ";
		std::cin >> choice;
		switch (choice)
		{
		case 1:
		{

			flag = true;
			int n = 0;

			while (flag)
			{
				try
				{
					std::cout << "Number of points: ";
					std::cin >> n;
					if (n < 2) throw "The numbers of points muct be >= 2";
					flag = false;
				}
				catch (const char* ex)
				{
					std::cout << ex << endl;
					std::cout << endl << "Try again" << endl;
				}
			}
			flag = true;
			flag1 = true;
			broken_line tmp_line(n);
			broken_line start_line = CreatingLine(tmp_line);
			while (flag1)
				flag1 = JobWithLine(flag, flag1, choice, start_line);
			break;
		}
		case 2:
		{
			flag = true;
			flag1 = true;
			broken_line line = MyLetter(flag);
			while (flag1)
				flag1 = JobWithLine(flag, flag1, choice, line);
			break;
		}
		case 3:
		{
			return 0;
		}
	}
}


