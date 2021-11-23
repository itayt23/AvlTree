#include "Group.h"


int const Group::getGroupID(){
    return this->group_id;
}

int Group::getNumberOfPlayers(){
    return this->num_players;
}

void Group::setNumberOfPlayers(int value){
    this->num_players=value;
}

Player* Group::getBestPlayer(){
    return this->best_group_player_ptr;
}    

void Group::setBestPlayer(Player* new_best_player){
    this->best_group_player_ptr=new_best_player;    // this an assignment and not a copy of the value
}

AvlTree<Player>* Group::getGroupPlayersTree(){
    return this->avl_group_players_ptr;
}

void Group::setGroupPlayersTree(AvlTree<Player>* new_tree){
    this->avl_group_players_ptr = new_tree;
}

AvlTree<int>* Group::getGroupLevelsTree(){
    return this->avl_group_levels_ptr;
}

void Group::setGroupsLevelsTree(AvlTree<int>* new_tree){
    this->avl_group_levels_ptr = new_tree;
}



// Group::Group(const Group& to_copy){
//     this->group_id = to_copy.getGroupID();
//     this->num_players = to_copy.getNumberOfPlayers();
//     this->avl_group_players_ptr(to_copy.getGroupPlayersTree());
//     this->avl_group_levels_ptr(to_copy.getGroupLevelsTree());
//     }

Group::Group(int id, int num_players) : group_id(id), num_players(num_players), 
    best_group_player_ptr(nullptr), avl_group_players_ptr(nullptr), avl_group_levels_ptr(nullptr) {};


bool Group::operator==(const Group& group) const
{
    if(this->group_id == group.group_id)
    {
        return true;
    }
    return false;
}

bool Group::operator<(const Group& group) const
{
    if(this->group_id < group.group_id)
    {
        return true;
    }
    return false;
}

bool Group::operator>(const Group& group) const
{
    if(this->group_id > group.group_id)
    {
        return true;
    }
    return false;
}