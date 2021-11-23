#include "Player.h"

Player::Player(const int player_id, const int level){
    this->player_id = player_id;
    this->level = level;
}

Player::Player(const Player& to_copy){
    this->player_id = to_copy.player_id;
    this->level = to_copy.level;
}

int Player::getPlayerID(){
    return this->player_id;
}

int Player::getPlayerLevel(){
    return this->level;
}

void Player::setPlayerLevel(int new_level){
    this->level = new_level;
}
bool Player::operator==(const Player& player) const
{
    if(this->player_id == player.player_id)
    {
        return true;
    }
    return false;
}

bool Player::operator<(const Player& player) const
{
    if(this->player_id < player.player_id)
    {
        return true;
    }
    return false;
}

bool Player::operator>(const Player& player) const
{
    if(this->player_id > player.player_id)
    {
        return true;
    }
    return false;
}





