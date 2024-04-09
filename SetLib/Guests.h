#pragma once
#include "Set.h"
#include <fstream>
using std::count;

enum class names { ������, ���, ��������, ³����, ������, ������, ���������, ����, �����, �����, 
	�����, �����, ����, ���, �����, ���������, ������, ������, ������, ������, �����,
	counter };

std::ostream& operator<<(std::ostream& out, names people)
{
	std::string name[] = { "������", "���", "��������", "³����", "������", "������", "���������", "����", "�����", "�����",
	"�����", "�����", "����", "���", "�����", "���������", "������", "������", "������", "������", "�����" };

	out << name[static_cast<int>(people)];
	return out;
}


class GuestTable {
private:
	Set<names> visitors[static_cast<int>(names::counter)];

public:
	GuestTable()
	{
		for (int i = 0; i < static_cast<int>(names::counter); ++i)
		{
			visitors[i] = Set<names>();
		}
	}

	GuestTable(const GuestTable& other)
	{
		for (int i = 0; i < static_cast<int>(names::counter); ++i)
		{
			visitors[i] = other.visitors[i];
		}
	}

	void add_visit(names host, names guest)
	{
		visitors[static_cast<int>(host)].add(guest);
	}

	void remove_visit(names host)
	{
		visitors[static_cast<int>(host)].remove_all();
	}

	void look_by_host(names host) const
	{
		std::cout << "Host: " << host << ". Visitors: " << visitors[static_cast<int>(host)] << std::endl;
	}

	void print_table() const
	{
		for (int i = 0; i < static_cast<int>(names::counter); ++i)
		{
			std::cout << static_cast<names>(i) << ": " << visitors[i] << std::endl;
		}
	}

	static names string_to_name(const std::string& line)
	{
		if (line == "������") return names::������;
		else if (line == "���") return names::���;
		else if (line == "��������") return names::��������;
		else if (line == "³����") return names::³����;
		else if (line == "������") return names::������;
		else if (line == "������") return names::������;
		else if (line == "���������") return names::���������;
		else if (line == "����") return names::����;
		else if (line == "�����") return names::�����;
		else if (line == "�����") return names::�����;
		else if (line == "�����") return names::�����;
		else if (line == "�����") return names::�����;
		else if (line == "����") return names::����;
		else if (line == "���") return names::���;
		else if (line == "�����") return names::�����;
		else if (line == "���������") return names::���������;
		else if (line == "������") return names::������;
		else if (line == "������") return names::������;
		else if (line == "������") return names::������;
		else if (line == "������") return names::������;
		else return names::�����;
	}

	void read_from_file(const std::string& fileName)
	{
		std::ifstream fin(fileName); 
		std::string line;
		while (!fin.eof()) 
		{
			std::getline(fin, line);
			std::istringstream iss(line);
			std::string host_name;
			iss >> host_name;

			names host = string_to_name(host_name);
			std::string guest_name;
			while (iss >> guest_name) 
			{
				names guest = string_to_name(guest_name);
				add_visit(host, guest);
			}
		}
		fin.close();
	}

	int quantity_of_visits(names person) const
	{
		int visits_counter = 0;
		for (int i = 0; i < static_cast<int>(names::counter); ++i)
		{
			if (visitors[i].contain(person))
			{
				++visits_counter;
			}
		}

		return visits_counter;
	}

	void visited_all() const
	{
		Set<names> ActiveVisitor;
		for (int i = 0; i < static_cast<int>(names::counter); ++i)
		{
			names curr_person = static_cast<names>(i);
			if (quantity_of_visits(curr_person) == static_cast<int>(names::counter) - 1)
			{
				ActiveVisitor.add(curr_person);
			}
		}

		if (ActiveVisitor.get_size() == 0)
		{
			std::cout << "�� ��������� �����, �� � ��� �������. " << std::endl;
		}
		else {
			std::cout << "������� ������, �� ������� ���: " << std::endl;
			ActiveVisitor.print_all();

		}
	}

	void visited_the_least() const
	{
		Set<names> MinVisits; 
		int min_visit = 0;
		for (int i = 1; i < static_cast<int>(names::counter); ++i)
		{
			if (quantity_of_visits(static_cast<names>(i)) < quantity_of_visits(static_cast<names>(min_visit)))
			{
				min_visit = i;
			}
		}

		MinVisits.add(static_cast<names>(min_visit));

		for (int j = min_visit + 1; j < static_cast<int>(names::counter); ++j)
		{
			if (quantity_of_visits(static_cast<names>(j)) == quantity_of_visits(static_cast<names>(min_visit)))
			{
				MinVisits.add(static_cast<names>(j));
			}
		}

		
		std::cout << "������� ������, �� ������� �������� �����: " << std::endl;
		MinVisits.print_all();
	}

	GuestTable reverse_table() const
	{
		GuestTable Reversed; 
		for (int i = 0; i < static_cast<int>(names::counter); ++i)
		{
			names curr_person = static_cast<names>(i);
			for (int j = 0; j < static_cast<int>(names::counter); ++j)
			{
				if (visitors[j].contain(curr_person))
				{
					Reversed.add_visit(curr_person, static_cast<names>(j));
				}
			}
		}

		return Reversed;
	}
	
	bool circle_of_three()
	{
		for (int i = 0; i < (int)names::counter; ++i)
		{
			if (visitors[i].get_size() == 2)
			{
				Set<names> Expected = visitors[i];
				Expected.add(static_cast<names>(i));
				Set<names>::Iterator Iter = Expected.begin();
				Set<names> member1 = visitors[(int)*Iter];
				Set<names> member2 = visitors[(int)*++Iter];
				Set<names> member3 = visitors[(int)*++Iter];
				Set<names> union1 = member1.set_union(member2);
				Set<names> union2 = union1.set_union(member3);
				if (union2 == Expected)
				{
					std::cout << "ҳ��� ���� ����� �����: " << union2;
					return true;
				}
			}
		}
		return false;
	}

};
