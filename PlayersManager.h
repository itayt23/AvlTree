#ifndef PLAYERS_MANAGER
#define PLAYERS_MANAGER

#include "AvlTree.h"
//#include "library1.h"
#include "Player.h"
#include "Group.h"

/* Return Values
 * ----------------------------------- */
typedef enum {
    SUCCESS = 0,
    FAILURE = -1,
    ALLOCATION_ERROR = -2,
    INVALID_INPUT = -3
} StatusType;


class PlayersManager
{
    /**
    * need to chck if it is really Generic AVL
    * neet to check the AVL level what type it is?
    * neet to check in all calss which one is need to be protected
    **/
    AvlTree<Player>     avl_players;
    AvlTree<Group>      avl_non_empty_groups;
    AvlTree<Group>      avl_groups;
    AvlTree<int>        levels; //what type this AVL is?

	public:

        PlayersManager();
        ~PlayersManager();
        
        StatusType AddGroup(void *DS, int GroupID);

        StatusType AddPlayer(void *DS, int PlayerID, int GroupID, int Level);

        StatusType RemovePlayer(void *DS, int PlayerID);

        StatusType ReplaceGroup(void *DS, int GroupID, int ReplacementID);

        StatusType IncreaseLevel(void *DS, int PlayerID, int LevelIncrease);

        StatusType GetHighestLevel(void *DS, int GroupID, int *PlayerID);

        StatusType GetAllPlayersByLevel(void *DS, int GroupID, int **Players, int *numOfPlayers);

        StatusType GetGroupsHighestLevel (void *DS, int numOfGroups, int **Players);

};


#endif
