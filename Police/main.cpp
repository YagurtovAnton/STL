#define _CRT_SECURE_NO_WARNINGS
#pragma warning (disable: 4326)
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
	tm time;
public:
	//const std::string& get_license_plate()const
	//{
	//	return license_plate;
	//}

	int get_violation_id()const
	{
		return id;
	}
	const  std::string& get_violation()const
	{
		return VIOLATIONS.at(id);
	}
	const std::string get_time()const
	{
		/*std::string result = asctime(&time);
		result.pop_back();
		return result;*/
		const int SIZE = 256;
		char formatted[SIZE]{};
		strftime(formatted, SIZE, "%R %e.%m.%Y", &time);
		return formatted;
	}
	const std::string get_place()const
	{
		return place;
	}
	const time_t get_timestamp()const
	{
		tm copy = time;
		return mktime(&copy);
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
		char* time_buffer = new char[time.size() + 1] {};
		strcpy(time_buffer, time.c_str());
		//this->time = time;
		int time_elements[5]{};
		int i = 0;
		char delimiters[] = ":./ ";
		for (char* pch = strtok(time_buffer, delimiters); pch; pch = strtok(NULL, delimiters))
			time_elements[i++] = std::atoi(pch);
		delete[] time_buffer;
		this->time.tm_hour = time_elements[0];
		this->time.tm_min = time_elements[1];
		this->time.tm_mday = time_elements[2];
		this->time.tm_mon = time_elements[3];
		this->time.tm_year = time_elements[4]-1900;
	}

	//			Constructors
	Crime
	( 
		int violation_id,
		const std::string& place,
		const std::string& time
	)
	{
		//set_license_plate(license_plate);
		this->time = {};
		set_violation_id(violation_id);
		set_place(place);
		set_time(time);
#ifdef DEBUG
		cout << "Constructor:\t" << this << endl;
#endif // DEBUG
	}

	~Crime()
	{
#ifdef DEBUG
		cout << "Destructor:\t" << this << endl;
#endif // DEBUG
	}
};
	std::ostream& operator<<(std::ostream& os, const Crime& obj)
	{
		return os << obj.get_time()<<" : " << obj.get_place() << " - "<< obj.get_violation();
	}
	std::ofstream& operator<<(std::ofstream& os, const Crime& obj)
	{
		os << obj.get_violation_id() << " " << obj.get_timestamp() << " " << obj.get_place();
		return os;
	}

	void print(const std::map<std::string, std::list<Crime>>& base);
	void save(const std::map<std::string, std::list<Crime>>& base, const std::string& filename);

void main()
{
	setlocale(LC_ALL, "");
	Crime crime(1, "��.������", "11:00 1.11.2011");
	cout << crime << endl;


	std::map<std::string, std::list<Crime>>base =
	{
		{"a777dd",{Crime(1,  "��.������",		"11:00 12.11.2011"), Crime(2,"��.C������",		"12:12 20.11.2011")}},
		{"a000bb",{Crime(6,  "��.����������",	"13:00 13.11.2011"), Crime(8,"��.����������",	"13:12 22.11.2011")}},
		{"a666aa",{Crime(10, "��.��������",		"21:00 19.11.2011"), Crime(9,"��.��������",		"23:32 23.11.2011")}}
	}; 
	print(base);
	save(base, "base.txt");
}

void print(const std::map<std::string, std::list<Crime>>& base)
{
	cout << delimiter << endl;
	for (std::map<std::string, std::list<Crime>>::const_iterator map_it = base.begin();
		map_it != base.end();
		++map_it)
	{
		cout << map_it->first << ":\n";
		for (std::list<Crime>::const_iterator it = map_it->second.begin(); it != map_it->second.end(); ++it)
		{
			cout << "\t" << *it << endl;
		}
		cout << delimiter << endl;
	}
}

void save(const std::map<std::string, std::list<Crime>>& base, const std::string& filename)
{
	std::ofstream fout(filename);
	//fout << delimiter << endl;
	for (std::map<std::string, std::list<Crime>>::const_iterator map_it = base.begin();
		map_it != base.end();
		++map_it)
	{
		fout << map_it->first << ":\t";
		for (std::list<Crime>::const_iterator it = map_it->second.begin(); it != map_it->second.end(); ++it)
		{
			fout << *it << ",";
		}
		fout.seekp(-1, std::ios::cur);
		fout << ";\n";
	}
	fout.close();
	std::string command = "notepad " + filename;
	system(command.c_str());
}