#include"List.h"
#include"List.cpp"

/// ----------------------------------------------------------- /// 

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