#ifndef PLAYER
#define PLAYER



class Player
{
    int player_id;
    int level;

	public:

		/**
        * Player: c'tor of Player class.
        *
        * @param player_id -  the player unique id.
        * @param level - the player current level.
        **/
		Player(const int player_id, const int level);
        
        /**
        * Player: copy c'tor of Player class.
        *
        @param to_copy - the player to copy
        **/
        Player::Player(const Player& to_copy);

		/**
        * ~Player: d'tor of Player class.
        **/
		~Player() = default;

        /* 
        
         */
        int getPlayerID();

        /* 
        
         */
        int getPlayerLevel();

        /* 
        
         */
        void setPlayerLevel(int new_level);

        bool operator==(const Player&) const;
        bool operator>(const Player&) const;
        bool operator<(const Player&) const;
	};

#endif