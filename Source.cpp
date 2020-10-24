#include <iostream>
#include <cmath>
# define M_PI 3.14159265358979323846

//Абстрактный класс Figure
class Figure
{
protected:
	float area = 0, perimeter = 0;
	virtual float CalculatePerimeter() = 0;
	virtual float CalculateArea() = 0;
	virtual bool ExistCheck() = 0;
	enum ExistValues //Значения существования. Просто для удобства
	{
		EXISTS,
		NOT_EXISTS
	};
public:
	float getArea();
	float getPerimeter();
	void ShowInfo();
};

//Производный класс Triangle
class Triangle : public Figure
{
	float side_1, side_2, side_3;
	float CalculatePerimeter();
	float CalculateArea();
	bool ExistCheck();

public:
	Triangle(float side_1, float side_2, float side_3)
	{
		this->side_1 = side_1;
		this->side_2 = side_2;
		this->side_3 = side_3;

		if (ExistCheck() == EXISTS) // Проверка на существование треугольника
		{
			perimeter = CalculatePerimeter();
			area = CalculateArea();
		}
		else std::cout << "Triangle doesn't exist!\a\n";
	}
};

//Производный класс Parallelogram
class Parallelogram : public Figure
{
	float side_1_3, side_2_4, angle;
	float CalculatePerimeter();
	float CalculateArea();
	bool ExistCheck();
public:
	Parallelogram(float side_1_3, float side_2_4, float angle)
	{
		this->side_1_3 = side_1_3;
		this->side_2_4 = side_2_4;
		this->angle = angle;
		if (ExistCheck() == EXISTS) //Проверка на существование параллелограмма
		{
			perimeter = CalculatePerimeter();
			area = CalculateArea();
		}
		else std::cout << "Parallelogram doesn't exist!\a\n";
	}
};

//Определение не виртуальных методов абстрактного класса Figure
void Figure::ShowInfo()
{
	if (ExistCheck() == EXISTS)
	{
		std::cout << "---------------------------------\n";
		std::cout << "Object of " << typeid(*this).name() << "\n\n";
		std::cout << "Perimeter = " << perimeter << "\n";
		std::cout << "Area = " << area << "\n";
		std::cout << "---------------------------------\n";
	}
}

//Аксессоры 
float Figure::getArea()
{
	return area;
}
float Figure::getPerimeter()
{
	return perimeter;
}

//Определение методов производного класса Triangle
float Triangle::CalculatePerimeter()
{
	return side_1 + side_2 + side_3;
}
float Triangle::CalculateArea()
{
	float p = perimeter / 2; //p - полупериметр треугольника
	return sqrt(p * (p - side_1) * (p - side_2) * (p - side_3));
}
bool Triangle::ExistCheck()
{
	if ((side_1 + side_2 >= side_3) && (side_2 + side_3 >= side_1) && (side_1 + side_3 >= side_2))
		return EXISTS;
	else
		return NOT_EXISTS;
}

//Определение методов производного класса Parallelogram
float Parallelogram::CalculatePerimeter()
{
	return side_1_3*2 + side_2_4*2;
}
float Parallelogram::CalculateArea()
{
	float h = side_1_3 * sin((angle * M_PI)/180);
	return side_2_4 * h;
}
bool Parallelogram::ExistCheck()
{
	if (angle > 0 && angle <= 90)
		return EXISTS;
	else
		return NOT_EXISTS;
}

int main(void)
{
	//Количество объектов классов Triangle и Parallelogram.
	const unsigned short trianglesQuantity = 2;
	const unsigned short parallelogramQuantity = 3;

	//Объявление функций нахождения объектов с максимальными необходимыми величинами.
	Triangle MaxArea(Triangle*);
	Parallelogram MaxPerimeter(Parallelogram*);

	//Объявление и инициализация объектов
	Triangle* triangles = new Triangle[trianglesQuantity]{ {2,2,2},{2,3,2} };
	Parallelogram* parallelograms = new Parallelogram[parallelogramQuantity]{ {2,2,30},{2,5,40},{3,4,71} };

	//Просто вывод информации про объекты
	for (int i(0);i<trianglesQuantity;i++)
	{
		triangles[i].ShowInfo();
	}
	for (int i(0); i < parallelogramQuantity; i++)
	{
		parallelograms[i].ShowInfo();
	}

	//Объекты хранящие в себе объекты с самыми большими периметром и площадью.
	Triangle biggestArea = MaxArea(triangles);
	Parallelogram biggestPerimeter = MaxPerimeter(parallelograms);

	//Вывод 
	std::cout << "\n\nMax area triangle:\n";
	biggestArea.ShowInfo();
	std::cout << "\n\nMax perimeter parallelogram:\n";
	biggestPerimeter.ShowInfo();

	delete[] triangles, parallelograms;
	system("pause");
}

Triangle MaxArea(Triangle* arr_Triangles)
{
	Triangle maxArea { 0,0,0 };
	for (int i(0);i< _msize(arr_Triangles) / sizeof(Triangle);i++) //Нахождение объекта с наибольшей площадью. Если несколько с одинаковой, то сохраняется последний.
	{
		if (arr_Triangles[i].getArea() > maxArea.getArea())
		{
			maxArea = arr_Triangles[i];
		}
	}
	return maxArea;
}

Parallelogram MaxPerimeter(Parallelogram* arr_Parallelograms) //Нахождение объекта с наибольшим периметром. Если несколько с одинаковым, то сохраняется последний.
{
	Parallelogram maxPerimeter{ 0,0,1 };
	for (int i(0); i < _msize(arr_Parallelograms) / sizeof(Parallelogram); i++)
	{
		if (arr_Parallelograms[i].getArea() > maxPerimeter.getArea())
		{
			maxPerimeter = arr_Parallelograms[i];
		}
	}
	return maxPerimeter;
}