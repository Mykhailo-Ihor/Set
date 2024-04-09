#include "Сities.h"

std::ostream& operator<<(std::ostream& out, cities city)
{
    std::string cityNames[] = {
        "Київ", "Львів", "Харків", "Дніпро", "Одеса",
        "Тернопіль", "Ужгород", "Луцьк", "Рівне", "Івано-Франківськ",
        "Житомир", "Суми", "Донецьк", "Луганськ", "Запоріжжя",
        "Сімферополь", "Чернівці", "Хмельницький", "Вінниця",
        "Черкаси", "Полтава", "Чернігів", "Кропивницький",
        "Миколаїв", "Херсон", "counter"
    };

    out << cityNames[static_cast<int>(city)];
    return out;
}

void find_route(const CitiesTable& table,cities start, cities end)
{
    if (start == end)
    {
        std::cout << "Невалідний рейс " << start << " -> " << end << std::endl; return;
    }
    Set<cities> starting_city = table.routes[(int)start];
	if (starting_city.contain(end))
	{
		std::cout << "Рейс від міста " << start << " до міста " << end << std::endl;
        std::cout << start << " -> " << end << std::endl;
	}
    else
    {
        bool flag = false;
        Set<cities>::Iterator curr = starting_city.begin();
        while (curr != nullptr)
        {
            Set<cities> possible_route1 = table.routes[(int)*curr];
            if (possible_route1.contain(end))
            {
                std::cout << "Рейс від міста " << start << " до міста " << end << std::endl;
                std::cout << start << " -> " << *curr << " -> " << end << std::endl;
                flag = true;
                break;
            }
            else
            {
                Set<cities>::Iterator curr_possible_route = possible_route1.begin();
                while (curr_possible_route != nullptr)
                {
                    Set<cities> possible_route2 = table.routes[(int)*curr_possible_route];
                    if (possible_route2.contain(end))
                    {
                        std::cout << "Рейс від міста " << start << " до міста " << end << std::endl;
                        std::cout << start << " -> " << *curr << " -> " << *curr_possible_route << " -> " << end << std::endl;
                        flag = true;
                        break;
                    }
                    ++curr_possible_route;
                }
            }
            ++curr;
        }
        if (!flag)
        {
            std::cout << "Рейсу від міста " << start << " до міста " << end << " немає\n";
        }
    }
}
