#include "splashkit.h"
#include <string>
#include <vector>

using std::string;
using std::vector;

struct knight_data
{
    string name;
    int age;
    string mob;
    vector<string> items;
};

struct kingdom_data
{
    string name;
    vector<knight_data> knights;
};

string read_string(string prompt)
{
    string result;
    write(prompt);
    result = read_line();
    return result;
}

int read_integer(string prompt)
{
    string line;
    line = read_string(prompt);
    return convert_to_integer(line);
}

knight_data read_knight()
{
    knight_data result;
    result.name = read_string("Enter name: ");
    result.age = read_integer("Enter age: ");
    result.mob = read_string("Enter Month of Birth: ");
    return result;
}

void write_knight(const knight_data &knight)
{
    write_line("Hello " + knight.name + ", month of birth: " + knight.mob + ", aged: " + std::to_string(knight.age));
}

enum knight_update_option
{
    UPDATE_NAME,
    UPDATE_AGE,
    UPDATE_MOB,
    FINISH_UPDATE
};

knight_update_option read_knight_update_option()
{
    int result;
    write_line("1 Update name");
    write_line("2 Update age");
    write_line("3 Update month of birth");
    write_line("4 Finish update");
    result = read_integer("Select option: ");
    return static_cast<knight_update_option>(result - 1);
}

void update_knight(knight_data &knight)
{
    knight_update_option option;
    do
    {
        write_line();
        write_line("== Update Knight ==");
        write_knight(knight);
        write_line();
        option = read_knight_update_option();
        switch (option)
        {
            case UPDATE_NAME:
                knight.name = read_string("Enter new name: ");
                break;
            case UPDATE_AGE:
                knight.age = read_integer("Enter new age: ");
                break;
            case UPDATE_MOB:
                knight.mob = read_string("Enter new month of birth: ");
                break;
            case FINISH_UPDATE:
                break;
            default:
                write_line("Please enter a valid option");
        }
    } while (option != FINISH_UPDATE);
}

void add_knight(kingdom_data &kingdom)
{
    knight_data new_knight;
    new_knight = read_knight();
    kingdom.knights.push_back(new_knight);
}

void write_kingdom(const kingdom_data &kingdom)
{
    write_line("===============");
    write_line(kingdom.name);
    write_line("=== Knights ===");
    for (int i = 0; i < kingdom.knights.size(); i++)
    {
        write_knight(kingdom.knights[i]);
    }
    write_line("==============");
}

void delete_knight(kingdom_data &kingdom, int index)
{
    if (index >= 0 && index < kingdom.knights.size())
    {
        int last_idx;
        last_idx = kingdom.knights.size() - 1;
        kingdom.knights[index] = kingdom.knights[last_idx];
        kingdom.knights.pop_back();
    }
}

int select_knight(const kingdom_data &kingdom)
{
    write_kingdom(kingdom);
    int i = -1;
    while (i < 1 || i > kingdom.knights.size())
    {
        i = read_integer("Please Select a Knight: ");
        if (i < 1 || i > kingdom.knights.size())
        {
            write_line("Invalid Option. Please Try Again!");
        }
    }
    return i - 1;
}

void delete_knight_from_kingdom(kingdom_data &kingdom)
{
    int i = select_knight(kingdom);
    delete_knight(kingdom, i);
}

kingdom_data read_kingdom()
{
    kingdom_data result;
    result.name = read_string("Enter Kingdom Name: ");
    return result;
}

void query_knight(const kingdom_data &kingdom)
{
    int idx_of_knights = select_knight(kingdom);
    write_knight(kingdom.knights[idx_of_knights]);
}

enum system_actions
{
    ADD_KNIGHT,
    DELETE_KNIGHT,
    QUERY_KNIGHT,
    UPDATE_KNIGHT,
    DISPLAY_DETAILS,
    FINISH_SYSTEM_ACTIONS
};

system_actions read_system_actions()
{
    int result;

    write_line("1: Add Knight");
    write_line("2: Delete Knight");
    write_line("3: Query Knight");
    write_line("4: Update Knight");
    write_line("5: Display Knight");
    write_line("6: Finish Knight");
    result = read_integer("Select Option:");

    return static_cast<system_actions>(result - 1);
}

void system_actions_menu(kingdom_data &kingdom)
{
    int x;
    system_actions option;

    do
    {
        write_line();
        write_line("== System Actions ==");
        write_kingdom(kingdom);
        write_line();
        option = read_system_actions();

        switch (option)
        {
            case ADD_KNIGHT:
                add_knight(kingdom);
                break;
            case DELETE_KNIGHT:
                delete_knight_from_kingdom(kingdom);
                break;
            case QUERY_KNIGHT:
                query_knight(kingdom);
                break;
            case UPDATE_KNIGHT:
                x = select_knight(kingdom);
                update_knight(kingdom.knights[x]);
                break;
            case DISPLAY_DETAILS:
                write_kingdom(kingdom);
                break;
            case FINISH_SYSTEM_ACTIONS:
                break;
            default:
                write_line("Please Select a Valid Option!");
        }

    } while (option != FINISH_SYSTEM_ACTIONS);
}

int main()
{
    kingdom_data my_kingdom;
    my_kingdom = read_kingdom();
    system_actions_menu(my_kingdom);
    return 0;
}
