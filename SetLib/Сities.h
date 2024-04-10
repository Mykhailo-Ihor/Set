#pragma once
#include "Set.h"
#include <fstream>

enum class cities { ���, ����, �����, �����, �����, 
	��������, �������, �����, г���, �����_���������,
	�������, ����, �������, ��������, ��������, 
	ѳ���������, �������, ������������, ³�����, 
	�������, �������, ������, �������������, 
	�������, ������, counter };

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
        if (line == "���") return cities::���;
        else if (line == "����") return cities::����;
        else if (line == "�����") return cities::�����;
        else if (line == "�����") return cities::�����;
        else if (line == "�����") return cities::�����;
        else if (line == "��������") return cities::��������;
        else if (line == "�������") return cities::�������;
        else if (line == "�����") return cities::�����;
        else if (line == "г���") return cities::г���;
        else if (line == "�����-���������") return cities::�����_���������;
        else if (line == "�������") return cities::�������;
        else if (line == "����") return cities::����;
        else if (line == "�������") return cities::�������;
        else if (line == "��������") return cities::��������;
        else if (line == "��������") return cities::��������;
        else if (line == "ѳ���������") return cities::ѳ���������;
        else if (line == "�������") return cities::�������;
        else if (line == "������������") return cities::������������;
        else if (line == "³�����") return cities::³�����;
        else if (line == "�������") return cities::�������;
        else if (line == "�������") return cities::�������;
        else if (line == "������") return cities::������;
        else if (line == "�������������") return cities::�������������;
        else if (line == "�������") return cities::�������;
        else if (line == "������") return cities::������;
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

