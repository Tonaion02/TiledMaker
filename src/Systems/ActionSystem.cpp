#include "ActionSystem.h"

#include "ECS/ECS.h"

//Including other system
#include "Systems/MoveSystem.h"
//Including other system

//Including world
#include "Game.h"
#include "World.h"
//Including world





//-----------------------------------------------------------------------------------------------------------------------------------------
//Class ActionSystem
//-----------------------------------------------------------------------------------------------------------------------------------------
void ActionSystem::init()
{
	World* world = Game::get()->getWorld();

	ComponentPool<ActionComponent>* poolActionCmp = &world->mPoolActionComponent;

	for (unsigned int i = 0; i < poolActionCmp->mNext; i++)
	{
		poolActionCmp->mPackedArray[i].currentAction = NoneActions;
	}
}



void ActionSystem::endAction()
{
	World* world = Game::get()->getWorld();

	ComponentPool<ActionComponent>* poolActionCmp = &world->mPoolActionComponent;

	for (unsigned int i = 0; i < poolActionCmp->mNext; i++)
	{
		int currentAction = poolActionCmp->mPackedArray[i].currentAction;

		if (currentAction != NoneActions)
		{		
			if (isEnd(poolActionCmp->mPackedArray[i].actionDelays[currentAction]))
			{
				//Correct termination of action
				switch (currentAction)
				{

				case Walk:
				case Rotate:
					MoveSystem::endMove(poolActionCmp->mDirectArray[i]);
					break;

				default:
					break;
				}
				//Correct termination of action


				//Reset action 
				//poolActionCmp->mPackedArray[i].currentAction = NoneActions;
				getCmpIndex(&world->mPoolActionComponent, i)->currentAction = NoneActions;
				//Reset action
			}
		}
	}
}



void ActionSystem::updateAction()
{
	World* world = Game::get()->getWorld();
	float deltaTime = Game::get()->getDeltaTime();

	ComponentPool<ActionComponent>* poolActionCmp = &world->mPoolActionComponent;

	for (unsigned int i = 0; i < poolActionCmp->mNext; i++)
	{
		//if (poolActionCmp->mPackedArray[i].currentAction != NoneActions)
		if (getCmpIndex(&world->mPoolActionComponent, i)->currentAction != NoneActions)
		{
			//Update delay of Action
			//poolActionCmp->mPackedArray[i].actionDelays[poolActionCmp->mPackedArray[i].currentAction].timePassed += deltaTime;
			getCmpIndex(&world->mPoolActionComponent, i)->actionDelays[getCmpIndex(&world->mPoolActionComponent, i)->currentAction].timePassed += deltaTime;
			//Update delay of Action
		}
	}
}



void ActionSystem::startAction(Entity e, Actions action)
{
	World* world = Game::get()->getWorld();

	ComponentPool<ActionComponent>* poolActionCmp = &world->mPoolActionComponent;

	//if (poolActionCmp->mPackedArray[poolActionCmp->mReverseArray[e]].currentAction == NoneActions)
	if (getCmpEntity(&world->mPoolActionComponent, e)->currentAction == NoneActions)
	{
		//poolActionCmp->mPackedArray[poolActionCmp->mReverseArray[e]].currentAction = action;
		getCmpEntity(&world->mPoolActionComponent, e)->currentAction = action;
		//start(&poolActionCmp->mPackedArray[poolActionCmp->mReverseArray[e]].actionDelays[poolActionCmp->mPackedArray[poolActionCmp->mReverseArray[e]].currentAction]);
		start(&getCmpEntity(&world->mPoolActionComponent, e)->actionDelays[getCmpEntity(&world->mPoolActionComponent, e)->currentAction]);
	}
}



bool ActionSystem::isDoingNothing(Entity e)
{
	World* world = Game::get()->getWorld();

	//ComponentPool<ActionComponent>* poolActionCmp = &world->mPoolActionComponent;

	//return poolActionCmp->mPackedArray[poolActionCmp->mReverseArray[e]].currentAction == Actions::NoneActions;
	return getCmpEntity(&world->mPoolActionComponent, e)->currentAction == Actions::NoneActions;
}
//-----------------------------------------------------------------------------------------------------------------------------------------
//Class ActionSystem
//-----------------------------------------------------------------------------------------------------------------------------------------