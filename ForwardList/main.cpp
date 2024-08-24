#include<iostream>
using namespace std;

using std::cin;
using std::cout;
using std::endl;

#define tab "\t"
#define delimiter "\n------------------------------\n"

template<typename T>class ForwardList;
template<typename T>class Iterator;
template<typename T>ForwardList<T> operator+(const ForwardList<T>& left, const ForwardList<T>& right);

template<typename T>class Element 
{
	T Data;          
	Element<T>* pNext;    
	static int count;
public:
	Element(T Data, Element<T>* pNext = nullptr) :Data(Data), pNext(pNext)
	{
		count++;
		//cout << "EConstructor:\t" << this << endl;
	}
	~Element()
	{
		count--;
		//cout << "EDestructor:\t" << this << endl;
	}
	friend class ForwardList<T>;
	friend class Iterator<T>;
	friend ForwardList<T> operator+(const ForwardList<T>& left, const ForwardList<T>& right);
};

template<typename T> int Element<T>::count = 0;

template<typename T>class Iterator
{
	Element<T>* Temp;
public:
	Iterator(Element<T>* Temp) : Temp(Temp)
	{
		//cout << "IConstructor:\t" << this << endl;
	}
	~Iterator()
	{
		//cout << "IDestructor:\t" << this << endl;
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
	bool operator ==(const Iterator& other)const
	{
		return this->Temp == other.Temp;
	}
	bool operator !=(const Iterator& other)const
	{
		return this->Temp != other.Temp;
	}
	T operator*()
	{
		return Temp->Data;
	}
	T& operator*()const
	{
		return Temp->Data;
	}
};
template<typename T>class ForwardList 
{
	Element<T>* Head; 
	unsigned int size; 
public:
	Iterator<T> begin()
	{
		return Head;
	}
	Iterator<T> end()
	{
		return nullptr;
	}
	int get_size()const
	{
		return size;
	}
	ForwardList()
	{
		Head = nullptr;
		size = 0;
		//cout << "LConstructor:\t" << this << endl;
	}
	explicit ForwardList(unsigned int size) : ForwardList() 
	{
		while (size--)push_front(0);
	}
	ForwardList(const ForwardList<T>& other) : ForwardList()
	{
		*this = other; 
		//cout << "CopyConstructor:\t" << this << endl;
	}
	ForwardList(ForwardList<T>&& other) : ForwardList()
	{
		*this = std::move(other); 
		//cout << "MoveConstructor:" << this << endl; 
	}
	ForwardList(const initializer_list<T>& il) : ForwardList() 
	{
		for (const T* it = il.begin(); it != il.end(); it++)
		{
			push_back(*it);
		}
	}
	~ForwardList()
	{
		while (Head)pop_front(); 
		//cout << "LDestructor:\t" << this << endl;
	}

	//                 Operators:
	ForwardList<T>& operator = (const ForwardList<T>& other)
	{
		if (this == &other)return *this;
		this->~ForwardList();
		for (Element<T>* Temp = other.Head; Temp; Temp = Temp->pNext)
			push_front(Temp->Data);
		//cout << "CopyAssignment:\t" << this << endl;
		return *this;
	}
	ForwardList<T>& operator = (ForwardList<T>&& other)
	{
		if (this == &other)return *this;
		this->~ForwardList();
		this->Head = other.Head;
		this->size = other.size;
		other.Head = nullptr;
		other.size = 0;
		//cout << "MoveAssignment:\t" << this << endl;
	}

	const int& operator[](int index)const
	{
		Element* Temp = Head;
		for (int i = 0; i < index; i++)Temp = Temp->pNext;
		return Temp->Data;
	}
	int& operator[](int index)
	{
		Element* Temp = Head;
		for (int i = 0; i < index; i++)Temp = Temp->pNext;
		return Temp->Data;
	}

	//            Adding elements (добавление элемента): 
	void push_front(T Data)
	{
		Head = new Element<T>(Data, Head);
		size++;
	}

	void push_back(T Data)
	{
		if (Head == nullptr)return push_front(Data); 
		Element<T>* Temp = Head; 
		while (Temp->pNext)
		{
			Temp = Temp->pNext;
		}
		Temp->pNext = new Element<T>(Data);
		size++;
	}
	//               Removing elements:
	void pop_front()
	{
		if (Head == nullptr)return; 
		Element<T>* Erased = Head;
		Head = Erased->pNext;
		delete Erased;
		size--;
		
	}

	void pop_back()
	{
		if (Head->pNext == nullptr)return pop_front();
		Element<T>* Temp = Head; 
		while (Temp->pNext->pNext)
		{
			Temp = Temp->pNext; 
		}
		delete Temp->pNext;
		Temp->pNext = nullptr;
		size--;
	}

	void insert(int index, T Data) //Вставляет элемент по индексу
	{
		if (index > size)
		{
			cout << "Error: out of range" << endl;
			return;
		}
		if (index == 0)return push_front(Data);
		//if (index > size)return;
		//Element* New = new Element(Data); //Выделяем память под новый элемент
		Element<T>* Temp = Head; //Создаём итератор который будет указывать на текущий элемент в списке
		for (int i = 0; i < index - 1; i++) //идём по списку до элемента перед добавляемым
		{
			if (Temp->pNext == nullptr)break;
			Temp = Temp->pNext;
		}
		//New->pNext = Temp->pNext; //записываем в добавляемый элемент адрес следующего элемента
		Temp->pNext = new Element<T>(Data, Temp->pNext); //в текущий записываем добавляемый
		size++;
	}
	void erase(int index)
	{
		if (index > size)
		{
			cout << "Error: out of range" << endl;
			return;
		}
		if (index == 0)return pop_front();
		Element<T>* Temp = Head;//Создаём итератор и начинаем идти по элементам с головы списка
		for (int i = 0; i < index - 1; i++)//Идём до нужного элемента
		{
			if (Temp->pNext == nullptr)break;
			Temp = Temp->pNext;
		}
		Element<T>* Erased = Temp->pNext; // Сохраняем удаляемый элемент
		Temp->pNext = Temp->pNext->pNext; // убираем элемент из списка
		delete Erased;// удаляем элемент из памяти
		size--;
	}

	//                  Methods:
	void print()const
	{
		//Element* Temp = Head;   //Temp - это итератор.
		//Итератор - это указатель, при помощи которого можно получить доступ к элементам структуры данных.  
		//while (Temp)
		//{
		//	cout << Temp << tab << Temp->Data << tab << Temp->pNext << endl;
		//	Temp = Temp->pNext; //Переход на следующий элемент.
		//}
		for (Element<T>* Temp = Head; Temp; Temp = Temp->pNext)
		{
			cout << Temp << tab << Temp->Data << tab << Temp->pNext << endl;
		}
		cout << "Количество элементов списка: " << size << endl;
		cout << "Общее количество элементов: " << Element<T>::count << endl;
	}
	void reverse()
	{
		ForwardList<T> buffer;
		while (Head)
		{
			buffer.push_front(Head->Data);
			pop_front();
		}
		this->Head = buffer.Head;
		buffer.Head = nullptr;
	}
};
template<typename T>
ForwardList<T> operator+(const ForwardList<T>& left, const ForwardList<T>& right)
{
	ForwardList<T> buffer = left;
	//for (int i = 0; i < left.get_size(); i++)buffer.push_back(left[i]);
	for (int i = 0; i < right.get_size(); i++)buffer.push_back(right[i]);
	return buffer;
}
void Print(int arr[])
//в функцию копируется указатель на массив arr, а не весь массив,
//поэтому будет выведено количество элементов один,
//а не количество элементов всего массива, так как 
//sizeof(arr) / sizeof(arr[0]) = 4/4 = 1, а не размер всего массива
//в байтах делённый на размер одного элемента в байтах;
{
	//cout << typeid(arr).name() << endl;
	//cout << sizeof(arr) << endl;
	for (int i = 0; i < sizeof(arr) / sizeof(arr[0]); i++)
	{
		cout << arr[i] << tab;
	}
	cout << endl;

	/*for (int i : arr)
	{
		cout << i << tab;
	}
	cout << endl;*/
}

//#define BASE_CHECK 
//#define COUNT_CHECK
//#define SIZE_CONSTRUCTOR_CHECK
//#define OPERATOR_PLUS_CHECK
//#define INITIALIZER_LIST_CONSTRUCTOR_CHECK
//#define RANGE_BASED_FOR_ARRAY
#define RANGED_BASED_FOR_LIST

void main()
{
	setlocale(LC_ALL, "");
#ifdef BASE_CHECK
	int n;
	cout << "Введите воличество элементов списка: "; cin >> n;
	ForwardList list;
	for (int i = 0; i < n; i++)
	{
		//list.push_front(rand() % 100);
		list.push_front(rand() % 100);
	}
	list.print();
	list.push_back(123);
	list.print();
	list.pop_front();
	list.print();
	int index;
	int value;
	cout << "Введите индекс добавляемого элемента: "; cin >> index;
	cout << "Введите значение добавляемого элемента: "; cin >> value;
	list.insert(index, value);
	list.print();
#endif // BASE_CHECK

#ifdef COUNT_CHECK
	ForwardList list1;
	list1.push_back(3);
	list1.push_back(5);
	list1.push_back(8);
	list1.push_back(13);
	list1.push_back(21);
	list1.print();

	ForwardList list2;
	list2.push_back(34);
	list2.push_back(55);
	list2.push_back(89);
	list2.print();
#endif // COUNT_CHECK

#ifdef SIZE_CONSTRUCTOR_CHECK
	ForwardList list(7);
	for (int i = 0; i < list.get_size(); i++)
	{
		list[i] = rand() % 100;
	}
	for (int i = 0; i < list.get_size(); i++)
	{
		cout << list[i] << tab;
	}
	cout << endl;
#endif // SIZE_CONSTRUCTOR_CHECK

#ifdef OPERATOR_PLUS_CHECK
	//ForwardList list1;
//list1.push_back(3);
//list1.push_back(5);
//list1.push_back(8);
//list1.push_back(13);
//list1.push_back(21);
//list1.print();

//ForwardList list2;
//list2.push_back(34);
//list2.push_back(55);
//list2.push_back(89);
//list2.print();

//cout << delimiter << endl;
////ForwardList list3 = list1 + list2;	//CopyConstructor
//cout << delimiter << endl;
//ForwardList list3;
//cout << delimiter << endl;
//list3 = list1 + list2;	//CopyAssignment
//cout << delimiter << endl;
//list3.print();  
#endif // OPERATOR_PLUS_CHECK

#ifdef INITIALIZER_LIST_CONSTRUCTOR_CHECK
	ForwardList list1 = { 3,5,8,13,21 };
	//Чтобы преобразовать из других типов в наш тип
	//нужен конструктор с одним параметром(Single-argument constructor)
	//и оператор присваивания (CopyAssignment) 
	//причём второй без первого не работает;
	list1.print();
#endif // INITIALIZER_LIST_CONSTRUCTOR_CHECK

#ifdef RANGE_BASED_FOR_ARRAY
	int arr[] = { 3,5,8,13,21 };
	//int* arr = new int[5] {3, 5, 8, 13, 21};
	for (int i = 0; i < sizeof(arr) / sizeof(int); i++)
	{
		cout << arr[i] << tab;
	}
	cout << endl;

	//Range-based for:
	for (int i : arr) //Цикл for на основе диапазона; 
		//Тип int переменной i будет использоваться для вычисления количества
		//элементов массива (sizeof(arr) / sizeof(int)) в цикле for;
	{
		cout << i << tab;
	}
https://legacy.cplusplus.com/doc/tutorial/control/#:~:text=equal%20to%2050.-,Range%2Dbased%20for%20loop,-The%20for%2Dloop
	//Range - это диапазон. Под данным термином в этом контексте понимают контейнер;
	//т.е. контейнером иногда называют 'range';
	//Следовательно, Range-base for - это цикл for для контейнеров. 
	cout << endl;
	cout << typeid(arr).name() << endl;
	Print(arr);
	//delete[] arr;  
#endif // RANGE_BASED_FOR_ARRAY

#ifdef RANGED_BASED_FOR_LIST
	ForwardList<int> list = { 3,5,8,13,21 };
	//list.print();
	for (int i : list)
	{
		//Error E2291 this range - based 'for' statement requires a suitable
		//"begin" function and none was found;
		//для этого оператора 'for', основанного на диапазоне,
		//требуется подходящая функция "begin", но она не найдена;
		//Error	C2672 'begin': no matching overloaded function found
		//не найдена соответствующая перегруженная функция
		//Error	C2672 'end': no matching overloaded function found	
		//Error	C3536 '<begin>$L0': cannot be used before it is initialized	
		//не может быть использован до его инициализации
		//Error	C3536 '<end>$L0': cannot be used before it is initialized	
		//Error	C2100 you cannot dereference an operand of type 'int'	
		//вы не можете разыменовать операнд типа 'int'
		cout << i << tab;
	}
	/*for (Iterator<int> it = list.begin(); it != list.end(); ++it)
	{
		cout << *it << tab;
	}*/
	cout << endl;
	ForwardList<double> list2 = { 1.1, 4.5, 2.3, 8.4, 5.5 };
	for (double i : list2)
	{
		cout << i << tab;
	}
	cout << endl;
	ForwardList<std::string> list3 = { "Здравствуйте", "Катю", "Можно" };
	for (std::string i : list3)cout << i << tab; cout << endl;
	list3.reverse();
	for (std::string i : list3)cout << i << tab; cout << endl;
	
#endif // RANGED_BASED_FOR_LIST

}