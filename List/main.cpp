#include<iostream>
#include <new.h>
using namespace std;

using std::cin;
using std::cout;
using std::endl;

#define tab "\t"

class List
{
	class Element
	{
		int Data;      //значение элемента
		Element* pNext;//указательна следующий элемент
		Element* pPrev;//указатель на предыдущий элемент

	public:
		Element(int Data, Element* pNext = nullptr, Element* pPrev = nullptr)
			:Data(Data), pNext(pNext), pPrev(pPrev)
		{
			cout << "EConstructor:\t" << this << endl;
		}
		~Element()
		{
			cout << "EDestructor:\t" << this << endl;
		}
		friend class List;
	}*Head, *Tail;  //объекты класса можно объявлять непосредственно после его описания.
	//Element* Head;
	//Element* Tail;
	size_t size; //typedef unsigned __int64 size_t;
	//size_t - это typedef на 'unsigned int'.
	//Директива 'typedef' создаёт псевдоним для существующего типа данных.
	//typedef имеет следующий синтаксис: typedef существующий_тип_данных псевдоним
	/*size_t — это специальный беззнаковый целочисленный тип, определённый в стандартных библиотеках языков С и С++.
		Он является типом результата, возвращаемого оператором sizeof и alignof.Максимально допустимым значением типа size_t является константа SIZE_MAX.
		Размер size_t выбирается таким образом, чтобы в него можно было записать максимальный размер теоретически возможного массива или объекта.
		Этот тип используется : для хранения размеров объектов; для индексации массивов; для адресной арифметики.*/
    //https://cplusplus.com/reference/cstddef/size_t/
public:
	class Iterator
	{
		Element* Temp;
	public:
		Iterator(Element* Temp = nullptr) :Temp(Temp)
		{
			cout << "ItConstructor:\t" << this << endl;
		}
		~Iterator()
		{
			cout << "ItDestructor:\t" << this << endl;
		}

		Iterator& operator++()
		{
			Temp = Temp->pNext;
			return *this;
		}
		Iterator operator++(int)
		{
			Iterator old = *this;
			Temp = Temp->pNext;
			return old;
		}
		Iterator& operator--()
		{
			Temp = Temp->pPrev;
			return *this;
		}
		Iterator operator--(int)
		{
			Iterator old = *this;
			Temp = Temp->pPrev;
			return old;
		}
	};
	Iterator begin()
	{
		return Head;
	}
	Iterator end()
	{
		return nullptr;
	}
	List()
	{
		Head = Tail = nullptr;
		size = 0;
		cout << "LConstructor:\t" << this << endl;
	}
	~List()
	{
		while (Head)pop_front();
		cout << "LDestructor:\t" << this << endl;
	}
	List(const std::initializer_list<int>& il) :List()
	{
		for (int const* it = il.begin(); it != il.end(); ++it)
		{
			push_back(*it);
		}
	}
	//                 Adding elements:
	void push_front(int Data)
	{
		if (Head == nullptr && Tail == nullptr)
		{
			Head = Tail = new Element(Data);
		}
		else
		{
			//1) Создаём новый элемент:
			Element* New = new Element(Data);

			//2) Привязываем новый элемент к началу списка:
			New->pNext = Head;

			//3) Привязываем головной элемент списка к новому элементу:
			Head->pPrev = New;

			//4) Смещаем голову на новый элемент:
			Head = New;
		}
		size++;
	}
	void push_back(int Data)
	{
		if (Head == nullptr && Tail == nullptr)return push_front(Data);
		else
		{
			Element* New = new Element(Data); // Создаём новый элемент
			New->pPrev = Tail;                // Привязываем новый элемент к концу списка
			Tail->pNext = New;                // Привязываем хвост к новому элементу
			Tail = New;                       // Смещаем хвост на новый элемент
		}
		size++;
	}
	void pop_front()
	{
		if (Head == nullptr && Tail == nullptr)return; // Если указывают на ноль, то ничего не делаем;
		if (Head == Tail) // Если Head и Tail указывают на один и тот же элемент;
		{
			delete Head;            //удаляем голову
			Head = Tail = nullptr;  //обнуляем Head и Tail
			size--;
			return;
		}
		Head = Head->pNext;     // Убираем нулевой элемент из списка
		delete Head->pPrev;     // Удаляем нулевой элемент из памяти
		Head->pPrev = nullptr;  // Делаем указатель Head->pPrev нулевым чтобы он не указывал на удалённый элемент
		size--;
	}
	void pop_back()
	{
		if (Head == Tail)return pop_front(); //Если один элемент в списке то удаляем с начала 
		Tail = Tail->pPrev;     // Привязываем хвост к предыдущему элементу
		delete Tail->pNext;     // Удаляем последний элемент 
		Tail->pNext = nullptr;  // Новый последний элемент указываем на ноль, так как он указывает на удалённый элемент
		size--;
	}
	void insert(int Data, int index)
	{
		if (index > size)return;
		if (index == 0)return push_front(Data);
		if (index == size)return push_back(Data);
		Element* Temp;
		if (index < size / 2)
		{
			Temp = Head;
			for (int i = 0; i < index; i++)
			{
				Temp = Temp->pNext;
			}
		}
		else
		{
			Temp = Tail;
			for (int i = 0; i < size - index - 1; i++)
			{
				Temp = Temp->pPrev;
			}
		}
		Element* New = new Element(Data);
		New->pNext = Temp;
		New->pPrev = Temp->pPrev;
		Temp->pPrev->pNext = New;
		Temp->pPrev = New;
		size++;
	}

	//                      Methods:
	void print()const
	{
		for (Element* Temp = Head; Temp; Temp = Temp->pNext)
		{
			cout << Temp->pPrev << tab << Temp << tab << Temp->Data << tab << Temp->pNext << endl;
		}
		cout << "Количество элементов в списке: " << size << endl;
	}
	void reverse_print()
	{
		for (Element* Temp = Tail; Temp; Temp = Temp->pPrev)
		{
			cout << Temp->pPrev << tab << Temp << tab << Temp->Data << tab << Temp->pNext << endl;
		}
		cout << "Количество элементов в списке: " << size << endl;
	}
};

//#define BASE_CHECK

void main()
{
	setlocale(LC_ALL, "");
#ifdef BASE_CHECK
	int n;
	cout << "Введите размер списка: "; cin >> n;
	List list;
	for (int i = 0; i < n; i++)
	{
		list.push_back(rand() % 100);
		//list.push_front(rand() % 100);
	}
	list.print();
	list.reverse_print();
	list.push_back(256);
	list.print();
	list.pop_front();
	list.print();
	list.pop_back();
	list.print();
	list.insert(128, 123);
	list.print();
#endif // BASE_CHECK

	List list = { 3,5,8,13,21 };
	//list.print();
	for (int i : list)cout << i << tab; cout << endl;

}