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
#ifdef DEBUG
			cout << "EConstructor:\t" << this << endl;
#endif // DEBUG
		}
		~Element()
		{
#ifdef DEBUG
			cout << "EDestructor:\t" << this << endl;
#endif // DEBUG
		}
		friend class List;
	}*Head, * Tail;  //объекты класса можно объявлять непосредственно после его описания.
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
#ifdef DEBUG
			cout << "ItConstructor:\t" << this << endl;
#endif // DEBUG
		}
		~Iterator()
		{
#ifdef DEBUG
			cout << "ItDestructor:\t" << this << endl;
#endif // DEBUG
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

		//             Comparison operators:
		bool operator==(const Iterator& other)const
		{
			return this->Temp == other.Temp;
		}
		bool operator!=(const Iterator& other)const
		{
			return this->Temp != other.Temp;
		}

		const int& operator*()const
		{
			return Temp->Data;
		}
		int& operator*()
		{
			return Temp->Data;
		}
	};
	class ReverseIterator
	{
		Element* Temp;
	public:
		ReverseIterator(Element* Temp = nullptr) :Temp(Temp)
		{
			cout << "RitConstructor:\t" << this << endl;
		}
		~ReverseIterator()
		{
			cout << "RitDestructor:\t" << this << endl;
		}

		//                 Incremento/Decremento:
		ReverseIterator& operator++()
		{
			Temp = Temp->pPrev;
			return *this;
		}
		ReverseIterator operator++(int)
		{
			ReverseIterator old = *this;
			Temp = Temp->pPrev;
			return old;
		}
		ReverseIterator& operator--()
		{
			Temp = Temp->pNext;
			return *this;
		}
		ReverseIterator operator--(int)
		{
			ReverseIterator old = *this;
			Temp = Temp->pNext;
			return old;
		}

		//              Comparison operattors:
		bool operator==(const ReverseIterator& other)const
		{
			return this->Temp == other.Temp;
		}
		bool operator!=(const ReverseIterator& other)const
		{
			return this->Temp != other.Temp;
		}

		//              Dereference operators (операторы разыименования):
		const int& operator*()const
		{
			return Temp->Data;
		}
		int& operator*()
		{
			return Temp->Data;
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
	Iterator begin()const
	{
		return Head;
	}
	Iterator end()const
	{
		return nullptr;
	}
	ReverseIterator rbegin()
	{
		return Tail;
	}
	ReverseIterator rend()
	{
		return nullptr;
	}
	List()
	{
		Head = Tail = nullptr;
		size = 0;
		cout << "LConstructor:\t" << this << endl;
	}
	List(const std::initializer_list<int>& il) :List()
	{
		for (int const* it = il.begin(); it != il.end(); ++it)
		{
			//push_front(*it);
			push_back(*it);
		}
	}
	List(const List& other) : List()
	{
		*this = other;
		cout << "CopyConstructor:\t" << this << endl;
	}
	~List()
	{
		while (Tail)pop_back();
		cout << "LDestructor:\t" << this << endl;
	}

	//                 Operators:
	List& operator=(const List& other)
	{
		if (this == &other)return *this;
		while (Head)pop_front();
		for (Element* Temp = other.Head; Temp; Temp = Temp->pNext)push_back(Temp->Data);
		cout << "CopyAssignment:\t" << this << endl;
		return *this;
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
			////1) Создаём новый элемент:
			//Element* New = new Element(Data);

			////2) Привязываем новый элемент к началу списка:
			//New->pNext = Head;

			////3) Привязываем головной элемент списка к новому элементу:
			//Head->pPrev = New;

			////4) Смещаем голову на новый элемент:
			//Head = New;

			Head = Head->pPrev = new Element(Data, Head);
		}
		size++;
	}
	void push_back(int Data)
	{
		if (Head == nullptr && Tail == nullptr)return push_front(Data);
		else
		{
			//Element* New = new Element(Data); // Создаём новый элемент
			//New->pPrev = Tail;                // Привязываем новый элемент к концу списка
			//Tail->pNext = New;                // Привязываем хвост к новому элементу
			//Tail = New;                       // Смещаем хвост на новый элемент
			Tail = Tail->pNext = new Element(Data, nullptr, Tail);
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
		/*Element* New = new Element(Data);
		New->pNext = Temp;
		New->pPrev = Temp->pPrev;
		Temp->pPrev->pNext = New;
		Temp->pPrev = New;*/

		Temp->pPrev = Temp->pPrev->pNext = new Element(Data, Temp, Temp->pPrev);

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

List operator+(const List& left, const List& right)
{
	List buffer = left;
	for (List::Iterator it = right.begin(); it != right.end(); ++it)
	{
		buffer.push_back(*it);
		*it *= 10;
	}
	return buffer;
}

//#define BASE_CHECK
//#define ITERATORS_CHECK
//#define OPERATOR_PLUS_CHECK

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

#ifdef ITERATORS_CHECK
	List list = { 3,5,8,13,21 };
	//list.print();
	for (int i : list)cout << i << tab; cout << endl;

	for (List::ReverseIterator it = list.rbegin(); it != list.rend(); ++it)
	{
		cout << *it << tab;
	}
	cout << endl;
#endif // ITERATORS_CHECK

#ifdef OPERATOR_PLUS_CHECK
	List list1 = { 3,5,8,13,21 };
	List list2 = { 34,55,89 };
	List list3 = list1 + list2;
	for (int i : list1)cout << i << tab; cout << endl;
	for (int i : list2)cout << i << tab; cout << endl;
	for (int i : list3)cout << i << tab; cout << endl;
#endif // OPERATOR_PLUS_CHECK


}