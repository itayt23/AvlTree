#ifndef GROUP
#define GROUP

#include "AvlTree.h"
#include "Player.h"



class Group
{
  int group_id;
  int num_players;
  Player* best_group_player_ptr;    //should it be smart pointers?
  AvlTree<Player>* avl_group_players_ptr;   //should it be smart pointers?
  AvlTree<int>* avl_group_levels_ptr;    //should it be smart pointers?

    
	public:
		/**
        * Group: c'tor of Group class.
        *
        * @param group_id -  the Group unique id.
        * @param num_players - the player current level.
        **/
    Group(int id, int num_players);

        /* 
        * Group: copy c'tor of Group class
         */
    Group(const Group& to_copy);

		/**
        * ~Group: d'tor of Group class.
        **/
		~Group() = default; // am i need here to reset the destroy the pointers?!



       /* 
  
        */
    int const getGroupID();
      /* 
  
        */
    int getNumberOfPlayers();
      /* 
      
       */
    void setNumberOfPlayers(int value);
      /* 
  
        */
    Player* getBestPlayer();
      /* 
      
       */
    void setBestPlayer(Player* new_best_player);
      /* 
  
        */
    AvlTree<Player>* getGroupPlayersTree();
      /* 
          ASSIGNMENT
       */
    void setGroupPlayersTree(AvlTree<Player>* new_tree);
      /*
  
       */
    AvlTree<int>* getGroupLevelsTree();
  
      /* 
      
       */          
    void setGroupsLevelsTree(AvlTree<int>* new_tree);  
    
    bool operator==(const Group&) const;
    bool operator>(const Group&) const;
    bool operator<(const Group&) const;

    };

#endif