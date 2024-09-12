#include<iostream>
#include<array>
#include<vector>
#include<list>

using std::cin;
using std::cout;
using std::endl;

#define tab "\t"
#define delimetr "\n_____________________\n"

template<typename T>void vector_info(const std::vector<T>& vec);

//#define	STL_ARRAY
//#define	STL_VECTOR
#define	STL_LIST

void main()
{
	setlocale(LC_ALL, "");
	//cout << "hello STL " << endl;
#ifdef STL_ARRAY
	const int N = 5;
	std::array<int, N>arr{ 3, 5, 8, 13, 21 };
	for (int i = 0; i < arr.size(); i++)
	{
		cout << arr[i] << tab;
	}
	cout << endl;
#endif // STL_ARRAY
#ifdef STL_VECTOR
	std::vector<int> vec = { 0, 1, 1, 2, 3, 5, 8, 13, 21, 34 };
	for (int i = 0; i < vec.size(); i++)
	{
		cout << vec[i] << tab;
	}
	cout << endl;
	vector_info(vec);
	vec.reserve(24);

	vector_info(vec);

	vec.shrink_to_fit();//������� ��������������� �� ������������ ������� ������� (size)
	//��� ����� ������� � ����� �������� ������, ���� �� ������� ��� � ������
	//������ ������ �� ����� �����������
	vector_info(vec);
	vec.resize(8);	//������ ����������� ������ �������.
	// ��� ���������� �������� �������� � ����� ������� 
	for (std::vector<int>::iterator it = vec.begin(); it != vec.end(); ++it)
	{
		cout << *it << tab;
	}
	cout << endl;
	vector_info(vec);
	//vec.resize(14);
	for (int i : vec)cout << i << tab; cout << endl;
	vector_info(vec);
	vec.insert(vec.begin() + 4, { 1000, 2000, 4000 });
	for (int i : vec)cout << i << tab; cout << endl;

	int index;
	int count;
	int value;
	cout << "������� ������ ������������ ��������: "; cin >> index;
	cout << "������� ���������� ����������� ��������: "; cin >> count;
	cout << "������� ��������  ������������ ��������: "; cin >> value;
	//vec.insert(vec.begin() + index, value);
	vec.insert(vec.begin() + index, count, value);
	for (int i : vec)cout << i << tab; cout << endl;
	vector_info(vec);
	cout << "������� ������ ������������ ��������: "; cin >> index;
	cout << "������� ���������� ������������ ��������: "; cin >> count;
	vec.erase(vec.begin() + index, vec.begin() + index + count);
	for (int i : vec)cout << i << tab; cout << endl;
#endif // STL_VECTOR

#ifdef STL_LIST
	std::list<int>list = { 3,5,8,13,21 };
	//for (int i = 0; i < list.size(); i++);
	//{
	//	cout << list[i] << tab;
	//}
	for (std::list<int>::iterator it = list.begin(); it != list.end(); ++it)
		cout << *it << tab;
	cout << endl;
	cout << list.front() << endl;
	cout << list.back() << endl;
	list.push_front(2);
	list.push_back(34);
	list.emplace_front(1);
	for (int i : list)cout << i << tab; cout << endl;

	int index;
	int value;
	do
	{
		cout << "������� ������ ������������ ��������: "; cin >> index;
		if (index >= list.size())cout << "Error: Out of range" << endl;
	} while (index >= list.size());
	cout << "������� �������� ������������ ��������: "; cin >> value;
	std::list<int>::iterator position = list.begin();
	//for (int i = 0; i < index; i++)position++;
	std::advance(position, index);
	list.insert(position, value);
	for (int i : list)cout << i << tab; cout << endl;

#endif // STL_LIST
}


template<typename T>void vector_info(const std::vector<T>& vec)
{
	cout << "Size:    " << vec.size() << endl;
	cout << "Capacity:" << vec.capacity() << endl;
	cout << "MaxSize: " << vec.max_size() << endl;
}
