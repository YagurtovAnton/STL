#include<iostream>
#include<fstream>
#include<string>
#include<conio.h>
#include<map>
#include<list>
#include<ctime>

using std::cin;
using std::cout;
using std::endl;

#define tab "\t"
#define delimiter "\n______________________________________________________________________\n"


const std::map<int, std::string> VIOLATIONS =
{
	{ 1, "������ ������������" },
	{ 2, "�������� � ������������ �����" },
	{ 3, "����������� ��������" },
	{ 4, "���������� ��������"},
	{ 5, "���������� ������������� �������������" },
	{ 6, "���������� ����� ���������� �����������"},
	{ 7, "���������� ���������"},
	{ 8, "������ �� �������"},
	{ 9, "����� �� ��������� ������"},
	{10, "����� �� �����������"},
	{11, "���� � ��������� ���������"},
	{12, "����������� �������"},
	{13, "�������� ��������� � ����������� ����������"},
	{14, "��������� ������������� �����"},
	{15, "���������� ������������ �������� �� ���"},
	{16, "��������� ������� ��� ������"},
};

class Crime
{
	//std::string license_plate;
	int id;
	std::string place;
	std::string time;
public:
	//const std::string& get_license_plate()const
	//{
	//	return license_plate;
	//}
	int get_violation_id()const
	{
		return id;
	}

	const std::string& get_violation()const
	{
		return VIOLATIONS.at(id);
	}
	const std::string& get_time()const
	{
		return time;
	}
	const std::string& get_place()const
	{
		return place;
	}
	//void set_license_plate(const std::string& license_plate)
	//{
	//	this->license_plate = license_plate;
	//}
	void set_violation_id(int id)
	{
		this->id = id;
	}
	void set_place(const std::string& place)
	{
		this->place = place;
	}
	void set_time(const std::string& time)
	{
		this->time = time;
	}

	//			Constructors
	Crime( int violation_id,
		const std::string& place, const std::string& time)
	{
		//set_license_plate(license_plate);
		set_violation_id(violation_id);
		set_place(place);
		set_time(time);
	}
#ifdef DEBUG
		cout << "Constructor:\t" << this << endl;
#endif // DEBUG

	~Crime()
	{
#ifdef DEBUG
		cout << "Destructor:\t" << this << endl;
#endif // DEBUG
	}
};
	std::ostream& operator<<(std::ostream& os, const Crime& obj)
	{
		return os << obj.get_time()<<":\t " << obj.get_place() << " - "<< obj.get_violation();
	}

	
void main()
{
	setlocale(LC_ALL, "");
	Crime crime(1, "��. ������", "11:00 1.11.2011");
	cout << crime << endl;


	std::map<std::string, std::list<Crime>>base =
	{
		{"a777dd",{Crime(1, "��. ������", "11:00 12.11.2011"),Crime(2,"��. �������", "12.12 20/12/2012")}},
		{"a000bb",{Crime(6, "��. ����������", "13:00 13.11.2011"),Crime(8,"��. ����������", "13.12 22.12.2012")}},
		{"a666aa",{Crime(10, "��. ��������", "21:00 19.11.2011"),Crime(9,"��. ��������", "23.32 23.12.2012")}}
	};
	for
		(
			std::map<std::string, std::list<Crime>>::iterator map_it = base.begin();
			map_it != base.end();
			++map_it
			)
	{
		cout << map_it->first << ":\n";
		for(std::list<Crime>::iterator it=map_it->second.begin(); it!=map_it->second.end();++it)
		{
			cout << "\t" << *it << endl;
		}
		cout << delimiter << endl;
	}
}
