#include "../include/team.h"

using namespace std;

/* @Berat Dalsuna
Student Name: Berat Dalsuna
Student ID: 150200002
Date: 12/10/21
*/

Team::Team(){};
string Team::getName() { return name; };
int Team::getCurrentSize() { return current_size; };
int Team::getId() { return id; };
int Team::getCapacity() { return capacity; };
Player *Team::getPlayer(int number)
{
    for (int i = 0; i < current_size; i++)
    {
        if (player_list[i].getNumber() == number)
            return &player_list[i];
    }
    return nullptr;
};
Player *Team::getPlayerList()
{
    return player_list;
};
void Team::setName(string new_name) { name = new_name; };
void Team::setId(int newId) { id = newId; };
void Team::listPlayers()
{
    cout << "Number"
         << " Name"
         << " Age"
         << " #Goals"
         << " #Assists"
         << " #Matches" << endl;
    ;
    for (int i = 0; i < current_size; i++)
    {
        cout << player_list[i].getNumber() << " - ";
        cout << player_list[i].getName() << " - ";
        cout << player_list[i].getAge() << " - ";
        cout << player_list[i].getGoalNumber() << " - ";
        cout << player_list[i].getAssistNumber() << " - ";
        cout << player_list[i].getMatchNumber() << endl;
    }
};
void Team::addPlayer(int number, string name, int age, int goals, int assists, int matches)
{
	// *********************Fill this method 
    if(this->current_size==0){
        this->capacity = 3;
    }
    else if (this->capacity==this->current_size){
        this->capacity *= 2;
    }

    Player* new_player_list = new Player[current_size+1]; //a new player list is created with a length of current_size + 1 
    Player* player_list = this->getPlayerList(); //gets old player list
    
    for(int i=0;i<this->current_size;i++){ // old array = new array except lastly added player
        new_player_list[i] = player_list[i];
        if(player_list[i].getNumber()==number){
            cout << "The Jersey number " << number << " is owned by another player in the team! Try another number or enter -1 to cancel adding player:" << endl;
            return;
        }
    }

    new_player_list[this->current_size] = Player(number,name,age,goals,assists,matches); //add last player
    this->current_size++;
    delete[] this->player_list;
    this->player_list = new_player_list; // old array = new array completely
    
    return;
};

bool Team::checkNumber(int number)
{
     for (int i = 0; i < current_size; i++)
    {
        if (player_list[i].getNumber() == number)
            return true;
    }
    return false;
}