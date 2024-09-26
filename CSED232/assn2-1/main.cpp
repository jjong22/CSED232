#include <iostream>
#include <string>
#include <fstream>

using namespace std;

struct Pokemon
{   
    int number;
    string name;
    string type[2];
    int height;
    int weight;
    string pre_evo;
    string post_evo;
};

int search_pockemon(Pokemon[], int, string);
int search_pre_evo_pockemon(Pokemon[], int, string);
int search_post_evo_pockemon(Pokemon[], int, string);
void add_pockemon(Pokemon[], int &);
void edit_pockemon(Pokemon[], int &);
void delete_pokemon(Pokemon[], int &, string);
void print_specific_pokemon(Pokemon[], int);
void print_all_pokemon(Pokemon[], int);
void print_with_type(Pokemon[], int, string);
void print_menu();

int main()
{
    Pokemon database[200];
    Pokemon temp_database[200];
    int num_of_pokemons = 0;

    while(1)
    {
        // print_specific_pokemon(database, -1);

        add_pockemon(database, num_of_pokemons);

        edit_pockemon(database, num_of_pokemons);
        delete_pokemon(database, num_of_pokemons, "-"); // TODO : 이름을 함수 내부에서 입력 받도록 수정
        
        print_with_type(database, num_of_pokemons, "type");
        print_all_pokemon(database, num_of_pokemons);

        exit(0);
    }

    return 0;
}

void add_pockemon(Pokemon database[], int &num_of_pokemons)
{
    string temp_evo;
    string temp_name;

    // database[num_of_pokemons].number = num_of_pokemons + 1; 굳이?

    cout << "Enter the name of the Pockemon to add: ";
    cin >> temp_name;

    if (search_pockemon(database, num_of_pokemons, temp_name) != -1) // 이미 존재하는 이름의 포켓몬인 경우
    {
        cout << "The entered name already exists in this database." << endl;
        return;
    }
    database[num_of_pokemons].name = temp_name;

    cout << "Enter the type(s): ";
    cin >> database[num_of_pokemons].type[0];
    // TODO : 순회해서 공백있으면 두번째 타입으로 저장하는 코드 추가하기

    // TODO : 예외 발생시 재입력 받는 코드 구현하기
    cout << "Enter the height (cm): ";
    cin >> database[num_of_pokemons].height;

    cout << "Enter the weight (kg): ";
    cin >> database[num_of_pokemons].weight;

    cout << "Enter the name of the pre-evolution Pockemon (Type \"-\" if none): ";
    cin >> temp_evo;
    if (search_pockemon(database, num_of_pokemons, temp_evo) != -1 or temp_evo == "-") // 이 이름의 포켓몬이 존재하는 경우
    {
        cout << "The Pokemon has been added." << endl;
        database[num_of_pokemons].pre_evo = temp_evo;

        int pre_evo_index = search_pockemon(database, num_of_pokemons, temp_evo); // 이전 전화체의 위치를 찾아 post_evo를 현재 이름으로 변경
        database[pre_evo_index].post_evo = temp_name;
    }
    else
    {
        cout << "The entered name doesn’t exist in this database." << endl;
        database[num_of_pokemons].pre_evo = "-";
    }

    num_of_pokemons++;
}

void edit_pockemon(Pokemon database[], int &num_of_pokemons)
{
    if (num_of_pokemons == 0)
    {
        cout << "There is no Pokemon in the database." << endl;
        return;
    }

    string pokemon_name;
    cout << "Enter the name of the Pokemon to edit: ";
    cin >> pokemon_name;

    int result = search_pockemon(database, num_of_pokemons, pokemon_name);
    if (result == -1)
    {
        cout << "The entered name doesn’t exist in this database." << endl;
        return;
    }

    print_specific_pokemon(database, result);
    Pokemon temp_pokemon = database[result];

    int selection;
    cout << "1. Type    2. Height    3. Weight    4. Pre-Evolution" << endl;
    cout << "Enter the attribute to edit: ";
    cin >> selection;

    if (selection == 1) // Type TODO : 2개로 나누기, 예외처리 등
    {
        cout << "Enter the type(s): ";
        cin >> temp_pokemon.type[0];
    }
    else if (selection == 2) // Height
    {
        cout << "Enter the height (cm): ";
        cin >> temp_pokemon.height;
    }
    else if (selection == 3) // Weight
    {
        cout << "Enter the weight (kg): ";
        cin >> temp_pokemon.weight;
    }
    else if (selection == 4) // Pre-Evolution
    {
        string new_prv_evo;

        cout << "Enter the name of the pre-evolution Pockemon (Type \"-\" if none): ";
        cin >> new_prv_evo;

        if (search_pre_evo_pockemon(database, num_of_pokemons, new_prv_evo) != -1) // 이 이름의 포켓몬이 존재하는 경우
        {
            cout << "The Pokemon cant be added." << endl;
            return;
        }

        temp_pokemon.pre_evo = new_prv_evo;
        
        int edited_had_post_evo = search_pre_evo_pockemon(database, num_of_pokemons, temp_pokemon.name); // 이전에 이 포켓몬을 post_evo로 가지고 있던 포켓몬
        int edited_new_post_evo = search_post_evo_pockemon(database, num_of_pokemons, temp_pokemon.name); // 업데이트로 인해 새로운 post_evo가 생긴 경우

        if (edited_had_post_evo != -1) // 이전에 이 포켓몬을 post_evo로 가지고 있던 포켓몬이 존재하는 경우
        {
            database[edited_had_post_evo].post_evo = "-";
        }
        if (edited_new_post_evo != -1) // 업데이트로 인해 새로운 post_evo가 생긴 경우
        {
            database[edited_new_post_evo].post_evo = temp_pokemon.name;
        }
    }

    database[result] = temp_pokemon;
}

int search_pockemon(Pokemon database[], int num_of_pokemons, string name)
{
    for (int i = 0; i < num_of_pokemons; i++)
    {
        if (database[i].name == name)
        {
            return i; // database에서의 index를 반환
        }
    }
    return -1; // 찾지 못한 경우, -1을 반환
}

int search_pre_evo_pockemon(Pokemon database[], int num_of_pokemons, string name)
{
    for (int i = 0; i < num_of_pokemons; i++)
    {
        if (database[i].pre_evo == name)
        {
            return i; // database에서의 index를 반환
        }
    }
    return -1; // 찾지 못한 경우, -1을 반환
}

int search_post_evo_pockemon(Pokemon database[], int num_of_pokemons, string name)
{
    for (int i = 0; i < num_of_pokemons; i++)
    {
        if (database[i].post_evo == name)
        {
            return i; // database에서의 index를 반환
        }
    }
    return -1; // 찾지 못한 경우, -1을 반환
}

void delete_pokemon(Pokemon database[], int &num_of_pokemons, string name)
{
    if (num_of_pokemons == 0)
    {
        cout << "There is no Pokemon in the database." << endl;
        return;
    }

    int result = search_pockemon(database, num_of_pokemons, name);

    if (result == -1)
    {
        cout << "The entered name doesn’t exist in this database." << endl;
        return;
    }

    int have_pre_evo = search_pre_evo_pockemon(database, num_of_pokemons, name); // name을 pre_evo로 가지고 있는 포켓몬
    int have_post_evo = search_post_evo_pockemon(database, num_of_pokemons, name); // name을 post_evo로 가지고 있는 포켓몬

    if (have_pre_evo != -1)
    {
        database[have_pre_evo].pre_evo = "-";
    } 
    if (have_post_evo != -1)
    {
        database[have_post_evo].post_evo = "-";
    }

    for (int i = result; i < num_of_pokemons - 1; i++) // 한칸씩 땡기기
    {
        database[i] = database[i + 1];
    }
}

void print_specific_pokemon(Pokemon database[], int index)
{
    cout << "-------------------------------------------------------------------------" << endl;
    cout << "Number Name Type Height Weight Pre-Evolution Post-Evolution" << endl;
    cout << database[index].number+1;
    cout << database[index].name;
    cout << database[index].type[0];
    cout << ", ";
    cout << database[index].type[1];
    cout << database[index].height; 
    cout << database[index].weight;
    cout << database[index].pre_evo;
    cout << database[index].post_evo << endl;
    cout << "-------------------------------------------------------------------------" << endl;
}

void print_all_pokemon(Pokemon database[], int num_of_pokemons)
{
    cout << "-------------------------------------------------------------------------" << endl;
    cout << "Number Name Type Height Weight Pre-Evolution Post-Evolution" << endl;
    for (int i = 0; i < num_of_pokemons; i++)
    {
        cout << database[i].number+1;
        cout << database[i].name;
        cout << database[i].type[0];
        cout << ", ";
        cout << database[i].type[1];
        cout << database[i].height; 
        cout << database[i].weight;
        cout << database[i].pre_evo;
        cout << database[i].post_evo << endl;
    }
    cout << "-------------------------------------------------------------------------" << endl;
}

void print_with_type(Pokemon database[], int num_of_pokemons, string type)
{
    cout << "-------------------------------------------------------------------------" << endl;
    cout << "Number Name Type Height Weight Pre-Evolution Post-Evolution" << endl;
    for (int i = 0; i < num_of_pokemons; i++)
    {
        if (database[i].type[0] == type or database[i].type[1] == type)
        // TODO : 검색한 타입이 앞에 와야한다면 순서 바꿔서 출력?
        {
            cout << database[i].number+1;
            cout << database[i].name;
            cout << database[i].type[0];
            cout << ", ";
            cout << database[i].type[1];
            cout << database[i].height; 
            cout << database[i].weight;
            cout << database[i].pre_evo;
            cout << database[i].post_evo << endl;
        }
    }
    cout << "-------------------------------------------------------------------------" << endl;
}

void print_menu()
{   cout << "================MENU===============" << endl;
    cout << "1. Display Pokemon" << endl;
    cout << "2. Add Pokemon" << endl;
    cout << "3. Edit Pokemon" << endl;
    cout << "4. Delete a Pokemon" << endl;
    cout << "5. Display Database" << endl;
    cout << "6. Exit" << endl;
    cout << "===================================" << endl;
}