﻿#include<iostream>
#include<string>
#include <new.h>
using namespace std;

using std::cin;
using std::cout;
using std::endl;

#define tab "\t"
#define delimeter "\n-------------------------------\n"

template<typename T>class List
{
	class Element
	{
		T Data;      //значение элемента
		Element* pNext;//указательна следующий элемент
		Element* pPrev;//указатель на предыдущий элемент
	public:
		Element(T Data, Element* pNext = nullptr, Element* pPrev = nullptr)
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
	class ConstBaseIterator
	{
	protected:
		Element* Temp;
	public:
		ConstBaseIterator(Element* Temp = nullptr) :Temp(Temp){}
		~ConstBaseIterator() {}
		//             Comparison operators:
		bool operator==(const ConstBaseIterator& other)const
		{
			return this->Temp == other.Temp;
		}
		bool operator!=(const ConstBaseIterator& other)const
		{
			return this->Temp != other.Temp;
		}
		//              Dereference operators (операторы разыименования):
		const T& operator*()const
		{
			return Temp->Data;
		}
	};
public:
	class ConstIterator : public ConstBaseIterator
	{
	public:
		ConstIterator(Element* Temp = nullptr) :ConstBaseIterator(Temp){}
		~ConstIterator(){}
		ConstIterator& operator++()
		{
			ConstBaseIterator::Temp =ConstBaseIterator::Temp->pNext;
			return *this;
		}
		ConstIterator operator++(int)
		{
			ConstIterator old = *this;
			ConstBaseIterator:: Temp = ConstBaseIterator::Temp->pNext;
			return old;
		}
		ConstIterator& operator--()
		{
			ConstBaseIterator::Temp = ConstBaseIterator::Temp->pPrev;
			return *this;
		}
		ConstIterator operator--(int)
		{
			ConstIterator old = *this;
			ConstBaseIterator::Temp = ConstBaseIterator::Temp->pPrev;
			return old;
		}
	};
	class ConstReverseIterator : public ConstBaseIterator
	{
	public:
		ConstReverseIterator(Element* Temp = nullptr) :ConstBaseIterator(Temp){}
		~ConstReverseIterator(){}
		//                 Incremento/Decremento:
		ConstReverseIterator& operator++()
		{
			ConstBaseIterator::Temp = ConstBaseIterator::Temp->pPrev;
			return *this;
		}
		ConstReverseIterator operator++(int)
		{
			ConstReverseIterator old = *this;
			ConstBaseIterator::Temp = ConstBaseIterator::Temp->pPrev;
			return old;
		}
		ConstReverseIterator& operator--()
		{
			ConstBaseIterator::Temp = ConstBaseIterator::Temp->pNext;
			return *this;
		}
		ConstReverseIterator operator--(int)
		{
			ConstReverseIterator old = *this;
			ConstBaseIterator::Temp = ConstBaseIterator::Temp->pNext;
			return old;
		}
	};
	// Если возникает необходимость изменить значение в списке, 
	// то кроме константных итераторов нужны ещё и обычные итераторы.
	// Обычные итераторы будут дополнять 
	// константные итераторы обычным не константным разъименованием.

	class Iterator : public ConstIterator
	{
	public:
		Iterator(Element* Temp = nullptr) :ConstIterator(Temp){}
		~Iterator(){}
		T& operator*()
		{
			return ConstBaseIterator::Temp->Data;
		}
	};
	class ReverseIterator :public ConstReverseIterator
	{
	public:
		ReverseIterator(Element* Temp = nullptr): ConstReverseIterator(Temp){}
		~ReverseIterator(){}
		T& operator*()
		{
			return ConstBaseIterator::Temp->Data;
		}
	};

	Iterator begin();
	Iterator end();
	ConstIterator begin()const;
	ConstIterator end()const;
	ReverseIterator rbegin();
	ReverseIterator rend();
	ConstReverseIterator rbegin()const;
	ConstReverseIterator rend()const;
	List();
	List(const std::initializer_list<T>& il);
	List(const List<T>& other);
	~List();
	//                 Operators:
	List<T>& operator=(const List<T>& other);
	//                 Adding elements:
	void push_front(T Data);
	void push_back(T Data);
	void pop_front();
	void pop_back();
	void insert(T Data, int index);
	//                      Methods:
	void print()const;
	void reverse_print();
};
//                             List methods:
template<typename T>typename List<T>::Iterator List<T>::begin()
{
	return Head;
}
template<typename T>typename List<T>::Iterator List<T>::end()
{
	return nullptr;
}
template<typename T>typename List<T>::ConstIterator List<T>::begin()const
{
	return Head;
}
template<typename T>typename List<T>::ConstIterator List<T>::end()const
{
	return nullptr;
}
template<typename T>typename List<T>::ReverseIterator List<T>::rbegin()
{
	return Tail;
}
template<typename T>typename List<T>::ReverseIterator List<T>::rend()
{
	return nullptr;
}
template<typename T>typename List<T>::ConstReverseIterator List<T>::rbegin()const
{
	return Tail;
}
template<typename T>typename List<T>::ConstReverseIterator List<T>::rend()const
{
	return nullptr;
}
template<typename T>List<T>::List()
{
	Head = Tail = nullptr;
	size = 0;
	cout << "LConstructor:\t" << this << endl;
}
template<typename T>List<T>::List(const std::initializer_list<T>& il) :List()
{
	for (T const* it = il.begin(); it != il.end(); ++it)
	{
		//push_front(*it);
		push_back(*it);
	}
}
template<typename T>List<T>::List(const List<T>& other) : List()
{
	*this = other;
	cout << "CopyConstructor:\t" << this << endl;
}
template<typename T>List<T>::~List()
{
	while (Tail)pop_back();
	cout << "LDestructor:\t" << this << endl;
}

//                Operators:
//type         name (   parameters   )
template<typename T>List<T>& List<T>::operator=(const List<T>& other)
{
	if (this == &other)return *this;
	while (Head)pop_front();
	for (Element* Temp = other.Head; Temp; Temp = Temp->pNext)push_back(Temp->Data);
	cout << "CopyAssignment:\t" << this << endl;
	return *this;
}

//                 Adding elements:
template<typename T>void List<T>::push_front(T Data)
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
template<typename T>void List<T>::push_back(T Data)
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
template<typename T>void List<T>::pop_front()
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
template<typename T>void List<T>::pop_back()
{
	if (Head == Tail)return pop_front(); //Если один элемент в списке то удаляем с начала 
	Tail = Tail->pPrev;     // Привязываем хвост к предыдущему элементу
	delete Tail->pNext;     // Удаляем последний элемент 
	Tail->pNext = nullptr;  // Новый последний элемент указываем на ноль, так как он указывает на удалённый элемент
	size--;
}
template<typename T>void List<T>::insert(T Data, int index)
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
template<typename T>void List<T>::print()const
{
	for (Element* Temp = Head; Temp; Temp = Temp->pNext)
	{
		cout << Temp->pPrev << tab << Temp << tab << Temp->Data << tab << Temp->pNext << endl;
	}
	cout << "Количество элементов в списке: " << size << endl;
}
template<typename T>void List<T>::reverse_print()
{
	for (Element* Temp = Tail; Temp; Temp = Temp->pPrev)
	{
		cout << Temp->pPrev << tab << Temp << tab << Temp->Data << tab << Temp->pNext << endl;
	}
	cout << "Количество элементов в списке: " << size << endl;
}

template<typename T>
List<T> operator+(const List<T>& left, const List<T>& right)
{
	List<T> buffer = left;
	for (List::ConstIterator it = right.begin(); it != right.end(); ++it)
	{
		buffer.push_back(*it);
		//*it *= 10; 
		//Для того чтобы невозможно было изменить операнды оператора +
		//создаём базовый класс с константными методами 
		//которые не дают изменять объекты для которых вызываются
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

	for (List::Iterator it = list3.begin(); it != list3.end(); ++it)
	{
		*it *= 100;
	}
	for (int i : list3) cout << i << tab; cout << endl;
#endif // OPERATOR_PLUS_CHECK

	List<int> i_list = { 3,5,8,13,21 };
	for (int i : i_list)cout << i << tab; cout << endl;
	for (List<int>::Iterator it = i_list.begin(); it != i_list.end(); ++it)
		cout << *it << tab; 
	cout << endl;
	for (List<int>::ReverseIterator it = i_list.rbegin(); it != i_list.end(); ++it)
		cout << *it << tab;
	cout << endl;
	cout << delimeter << endl;

	List<double> d_list = { 2.7, 3.14, 5.5, 8.3 };
	for (double i : d_list)cout << i << tab; cout << endl;
	for (List<double>::Iterator it = d_list.begin(); it != d_list.end(); ++it)
		cout << *it << tab; cout << endl;
	for (List<double>::ReverseIterator it = d_list.rbegin(); it != d_list.rend(); ++it)
		cout << *it << tab; cout << endl;
	cout << delimeter << endl;

	List<std::string> s_list = { "Хорошо", "живёт", "на", "свете", "Винни", "Пух" };
	for (std::string i : s_list)cout << i << tab; cout << endl;
	for (List<std::string>::Iterator it = s_list.begin(); it != s_list.end(); ++it)
		cout << *it << tab; cout << endl;
	for (List<std::string>::ReverseIterator it = s_list.rbegin(); it != s_list.rend(); ++it)
		cout<< *it << tab; cout << endl;
	cout << delimeter << endl;


}