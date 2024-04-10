#pragma once
#include "Set.h"
#include <fstream>

enum class cities { Київ, Львів, Харків, Дніпро, Одеса, 
	Тернопіль, Ужгород, Луцьк, Рівне, Івано_Франківськ,
	Житомир, Суми, Донецьк, Луганськ, Запоріжжя, 
	Сімферополь, Чернівці, Хмельницький, Вінниця, 
	Черкаси, Полтава, Чернігів, Кропивницький, 
	Миколаїв, Херсон, counter };

std::ostream& operator<<(std::ostream& out, cities city);
class CitiesTable
{
private:
	Set<cities> routes[(int)cities::counter];
public:
    void add_connection(cities city1, cities city2)
    {
        routes[(int)(city1)].add(city2);
        routes[(int)(city2)].add(city1);
    }
    void print_table() const
    {
        for (int i = 0; i < (int)(cities::counter); ++i)
        {
            std::ostringstream oss;
            oss << routes[i];
            if (oss.str() == "Empty set\n") continue;
            std::cout << static_cast<cities>(i) << ": ";
            size_t start = oss.str().find('{');
            size_t end = oss.str().find('}');
            std::cout << oss.str().substr(start, end - start + 1) << std::endl;
        }
        std::cout << std::endl;
    }
    static cities string_to_city(const std::string& line)
    {
        if (line == "Київ") return cities::Київ;
        else if (line == "Львів") return cities::Львів;
        else if (line == "Харків") return cities::Харків;
        else if (line == "Дніпро") return cities::Дніпро;
        else if (line == "Одеса") return cities::Одеса;
        else if (line == "Тернопіль") return cities::Тернопіль;
        else if (line == "Ужгород") return cities::Ужгород;
        else if (line == "Луцьк") return cities::Луцьк;
        else if (line == "Рівне") return cities::Рівне;
        else if (line == "Івано-Франківськ") return cities::Івано_Франківськ;
        else if (line == "Житомир") return cities::Житомир;
        else if (line == "Суми") return cities::Суми;
        else if (line == "Донецьк") return cities::Донецьк;
        else if (line == "Луганськ") return cities::Луганськ;
        else if (line == "Запоріжжя") return cities::Запоріжжя;
        else if (line == "Сімферополь") return cities::Сімферополь;
        else if (line == "Чернівці") return cities::Чернівці;
        else if (line == "Хмельницький") return cities::Хмельницький;
        else if (line == "Вінниця") return cities::Вінниця;
        else if (line == "Черкаси") return cities::Черкаси;
        else if (line == "Полтава") return cities::Полтава;
        else if (line == "Чернігів") return cities::Чернігів;
        else if (line == "Кропивницький") return cities::Кропивницький;
        else if (line == "Миколаїв") return cities::Миколаїв;
        else if (line == "Херсон") return cities::Херсон;
        else return cities::counter;
    }
    void readFromFile(const std::string& filename)
    {
        std::ifstream fin(filename);
        std::string line;
        while (!fin.eof())
        {
            std::getline(fin, line);
            std::istringstream iss(line);
            std::string starting;
            iss >> starting;
            cities starting_city = string_to_city(starting);

            std::string connection;
            while (iss >> connection)
            {
                cities connection_city = string_to_city(connection);
                add_connection(starting_city, connection_city);
            }
        }
        fin.close();
    }
    friend void find_route(const CitiesTable& table,cities start, cities end);
};

