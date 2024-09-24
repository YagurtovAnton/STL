#define _CRT_SECURE_NO_WARNINGS
#pragma warning (disable: 4326)
#include<iostream>
#include<fstream>
#include<string>
#include<sstream>
#include<conio.h>
#include<map>
#include<list>
#include<ctime>
#include<Windows.h>

using std::cin;
using std::cout;
using std::endl;

#define tab "\t"
#define delimiter "\n______________________________________________________________________\n"


#define Enter 13
#define Escape 27
#define UP_ARROW 72
#define DOWN_ARROW 80
//const char* menu_items[] =
//{
//"1. загрузить базу из файла",
//"2. сохранить базу в файл",
//"3. вывести базу на экран",
//"4.вывести информацию по номеру",
//};

const std::map<int, std::string>MENU_ITEMS =
{
	{1, "Загрузить базу из файла"},
	{2, "Сохранить базу в файл"},
	{3, "Вывести базу на экран"},
	{5, "Вывести информацию по номеру"},
	{4, "Добавить нарушение"},
};

const std::map<int, std::string> VIOLATIONS =
{
	{ 1, "Ремень безопасности" },
	{ 2, "Парковка в неположенном месте" },
	{ 3, "Пересечение сплошной" },
	{ 4, "Превышение скорости"},
	{ 5, "Отсутствие водительского удостоверения" },
	{ 6, "Отсутствие права управления автомобилем"},
	{ 7, "Отсутствие страховки"},
	{ 8, "Проезд на красный"},
	{ 9, "Выезд на встречную полосу"},
	{10, "Дрифт на перекрестке"},
	{11, "Езда в нетрезвом состоянии"},
	{12, "Оскорбление офицера"},
	{13, "Внесение изменений в конструкцию автомобиля"},
	{14, "Перевозка негабаритного груза"},
	{15, "Превышение максимальной нагрузки на ось"},
	{16, "Перевозка ребенка без кресла"},
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
	void set_timestamp(time_t timestamp)
	{
		time = *localtime(&timestamp);
	}
	//			Constructors
	explicit Crime
	(
		int violation_id=0,
		const std::string& place = "place",
		const std::string& time= "00:00 01.01.2000"
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
std::istream& operator>>(std::ifstream& is, Crime& obj)
{
	int id;
	time_t timestamp;
	std::string place;
	is >> id >> timestamp;
	std::getline(is, place, ',');
	is.ignore();
	obj.set_violation_id(id);
	obj.set_timestamp(timestamp);
	obj.set_place(place);
	return is;
}
int menu();
	void print(const std::map<std::string, std::list<Crime>>& base);
	void save(const std::map<std::string, std::list<Crime>>& base, const std::string& filename);
	std::map<std::string, std::list<Crime>>load(const std::string& filename);
#define SAVE_CHEK


void main()
{
	setlocale(LC_ALL, "");
#ifdef DEBUG
	Crime crime(1, "ул.Ленина", "11:00 1.11.2011");
	cout << crime << endl;


	std::map<std::string, std::list<Crime>>base =
	{
		{"a777dd",{Crime(1,  "ул.Ленина",		"11:00 12.11.2011"), Crime(2,"пл.Cвободы",		"12:12 20.11.2011")}},
		{"a000bb",{Crime(6,  "ул.Космнавтов",	"13:00 13.11.2011"), Crime(8,"ул.Космнавтов",	"13:12 22.11.2011")}},
		{"a666aa",{Crime(10, "ул.Преуской",		"21:00 19.11.2011"), Crime(9,"ул.Преуской",		"23:32 23.11.2011")}}
	};
	print(base);
	save(base, "base.txt");
#endif // DEBUG
	std::map<std::string, std::list<Crime>> base = load("base.txt");
	do
	{
		switch (menu())
		{
		case 0: return;
		case 1: base = load("base.txt");	break;
		case 2: save(base, "base.txt");		break;
		case 3: print(base);				break;
		case 4: cout << "Скоро будет" << endl; break;
		case 5: cout << "Скоро будет" << endl; break;
		}
	} while (true);
}
int menu()
{
	int selected_item = 1;
	char key;
	do
	{
		system("CLS");
		HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
		for (int i = 1; i <= MENU_ITEMS.size(); i++)
		{
			cout << (i == selected_item ? "[" : " ");
			cout << i << ". ";
			cout.width(32);
			cout << std::left;
			if (i == selected_item)SetConsoleTextAttribute(hConsole, 0x70);
			cout << MENU_ITEMS.at(i);
			SetConsoleTextAttribute(hConsole, 0x07);
			cout << (i == selected_item ? "  ]" : " ");
			cout << endl;
		}
		key = _getch();
		//cout << (int)key << endl;
		switch (key)
		{
		case UP_ARROW:	 /*if (selected_item > 1)*/selected_item--; break;
		case DOWN_ARROW: /*if (selected_item < MENU_ITEMS.size())*/selected_item++; break;
		case Enter:		 return selected_item;
		case Escape:	 return 0;
		}
		if (selected_item == MENU_ITEMS.size() + 1)selected_item = 1;
		if (selected_item == 0)selected_item = MENU_ITEMS.size();
	} while (key != Escape);
	return 0;
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
	cout << "количество номеров:" << endl;
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
		fout << endl;
	}
	fout.close();
	std::string command = "notepad " + filename;
	system(command.c_str());
}

std::map<std::string, std::list<Crime>>load(const std::string& filename)
{
	std::map<std::string, std::list<Crime>>base;
	std::ifstream fin(filename);
	if (fin.is_open())
	{
		while (!fin.eof())
		{
			
			std::string licence_plate;
			std::getline(fin, licence_plate,':');
			licence_plate.erase(0, licence_plate.find_first_not_of('\n'));
			fin.ignore();
			std::string buffer;
			std::getline(fin, buffer);
			char* sz_buffer = new char[buffer.size() + 1] {};
			strcpy(sz_buffer, buffer.c_str());
			Crime crime;// (0, "place", "00:00 01.01.2000");
			char delimiters[] = ",";
			for (char* pch = strtok(sz_buffer, delimiters); pch; pch = strtok(NULL, delimiters))
			{
				std::cout << pch << "\t";
			//	std::string s_crime(pch);
				std::stringstream ss_crime(pch, std::ios_base::in | std::ios_base::out);
				//ss_crime >> crime;
				//base[license_plate].push_back(crime);
			}
			/*std::string licence_plate;
			std::getline(fin, licence_plate);
			char delimitrs[] = '*/
		/*	std::string license_plate;
			std::getline(fin, license_plate, ':');
			fin.ignore();
			crime crame(0,"place", "time");
			fin>>crame;
			base[license_plate].push_back(crame);*/
		}
		fin.close();
	}
	else
	{
		std::cerr << "Error: file not found" << endl;
	}
	return base;
}