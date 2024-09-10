#include<iostream>
#include<array>
#include<vector>

using std::cin;
using std::cout;
using std::endl;

#define tab "\t"
#define delimetr "\n_____________________\n"

//#define	STL_ARRAY
#define	STL_VECTOR

void main()
{
	setlocale(LC_ALL, " ");
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

	vec.shrink_to_fit();//урезает вместительность до фактического размера вектора (size)
						//это можно сделать в цел€х экономии пам€ти, если мы уверены что в вектор
						//больше ничего не будет добавл€тьс€
	vector_info(vec);
	vec.resize(8);	//задает фактический размер ¬ектора.
					// ѕри уменьшении тер€ютс€ значени€ в конце ¬ектора 
	for (std::vector<int>::iterator it = vec.begin(); it != vec.end(); ++it)
	{
		cout << *it << tab;
	}
	cout << endl;
	vector_info(vec);
	vec.resize(14);
	for (int i : vec)cout << i << tab; cout << endl;
	vector_info(vec);
}
#endif // STL_VECTOR
	template<typename T>void vector_info(const std::vector<T>&vec) 
	{
	cout << "Size:    " << vec.size() << endl;
	cout << "Capacity:" << vec.capacity() << endl;
	cout << "MaxSize: " << vec.max_size() << endl;
	}
