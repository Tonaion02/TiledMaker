#include "Systems/RenderSystem.h"

//Including some context
#include "Game.h"
#include "World.h"
//Including some context

//Including Enviroment
#include "Enviroment/WindowHandler.h"
#include "Enviroment/TextureHandler.h"
#include "Enviroment/TileSet.h"
//Including Enviroment

//Including Utils
#include "Misc/Grid.h"
//Including Utils





//-----------------------------------------------------------------------------------------------------------------------------------------
//Class RenderSystem
//-----------------------------------------------------------------------------------------------------------------------------------------
void RenderSystem::draw()
{
	Game* gameInstance = Game::get();
	World* world = gameInstance->getWorld();

	ComponentPool<DrawComponent>* drawCmp = &gameInstance->getWorld()->mPoolDrawComponent;
	ComponentPool<TransformComponent>* transformCmp = &gameInstance->getWorld()->mPoolTransformComponent;

	SDL_Rect destRect;
	destRect.w = static_cast<int>(world->currentLevel.tileSet->tileDim.x * world->cameraData.baseScale);
	destRect.h = static_cast<int>(world->currentLevel.tileSet->tileDim.y * world->cameraData.baseScale);
	
	Vector2i dim = world->currentLevel.dim;
	SDL_Renderer* renderer = WindowHandler::get().getRenderer();



	RenderSystem::drawFirstLayerTileMap();

	//Draw all drawCmp
	for (unsigned int i = 0; i < drawCmp->mNext; i++)
	{
		Entity e = drawCmp->mDirectArray[i];

		destRect.x = static_cast<int>(transformCmp->mPackedArray[transformCmp->mReverseArray[e]].pos.x * destRect.w);
		destRect.y = static_cast<int>(transformCmp->mPackedArray[transformCmp->mReverseArray[e]].pos.y * destRect.h);

		destRect.x += static_cast<int>(world->cameraData.adj.x);
		destRect.y += static_cast<int>(world->cameraData.adj.y);

		SDL_RenderCopy(
			renderer,
			world->textureActor,
			&world->tilesetActor->srcRects[drawCmp->mPackedArray[i].id],
			&destRect
		);
	}
	//Draw all drawCmp

	RenderSystem::drawOtherLayerTileMap();
}



void RenderSystem::drawFirstLayerTileMap()
{
	Game* gameInstance = Game::get();
	World* world = gameInstance->getWorld();

	float baseScale = world->cameraData.baseScale;

	SDL_Rect destRect;
	destRect.w = static_cast<int>(world->currentLevel.tileSet->tileDim.x * baseScale);
	destRect.h = static_cast<int>(world->currentLevel.tileSet->tileDim.y * baseScale);

	Vector2i dim = world->currentLevel.dim;
	Vector2i tileDim = world->currentLevel.tileSet->tileDim;
	SDL_Renderer* renderer = WindowHandler::get().getRenderer();



	//Render first layer of tilemap
	for (int y = world->cameraData.startToRender.y; y < world->cameraData.endToRender.y; y++)
	{
		destRect.y = static_cast<int>(y * destRect.h);
		destRect.y += static_cast<int>(world->cameraData.adj.y);

		for (int x = world->cameraData.startToRender.x; x < world->cameraData.endToRender.x; x++)
		{
			destRect.x = static_cast<int>(x * destRect.w);
			destRect.x += static_cast<int>(world->cameraData.adj.x);

			int id = world->currentLevel.graphicTileLayer.gTiles[y * dim.x + x];

			SDL_RenderCopy(
				renderer,
				world->currentLevel.tileSet->texture,
				&world->currentLevel.tileSet->srcRects[id],
				&destRect
			);
		}

		int w = 0;
	}
	//Render first layer of tilemap
}



void RenderSystem::drawOtherLayerTileMap()
{
	Game* gameInstance = Game::get();
	World* world = gameInstance->getWorld();

	SDL_Rect destRect;
	destRect.w = static_cast<int>(world->currentLevel.tileSet->tileDim.x * world->cameraData.baseScale);
	destRect.h = static_cast<int>(world->currentLevel.tileSet->tileDim.y * world->cameraData.baseScale);

	int maxZ = world->currentLevel.maxZ;
	Vector2i dim = world->currentLevel.dim;
	SDL_Renderer* renderer = WindowHandler::get().getRenderer();



	//Render other layer of tilemap
	for (int z = 1; z < maxZ * 2; z++)
	{
		for (int y = world->cameraData.startToRender.y; y < world->cameraData.endToRender.y; y++)
		{
			destRect.y = static_cast<int>(y * destRect.h);
			destRect.y += static_cast<int>(world->cameraData.adj.y);

			for (int x = world->cameraData.startToRender.x; x < world->cameraData.endToRender.x; x++)
			{
				destRect.x = static_cast<int>(x * destRect.w);
				destRect.x += static_cast<int>(world->cameraData.adj.x);

				int id = world->currentLevel.graphicTileLayer.gTiles[z * dim.x * dim.y + y * dim.x + x];

				if (id <= -1)
					continue;

				SDL_RenderCopy(
					renderer,
					world->currentLevel.tileSet->texture,
					&world->currentLevel.tileSet->srcRects[id],
					&destRect
				);
			}
		}
	}
	//Render other layer of tilemap
}
//-----------------------------------------------------------------------------------------------------------------------------------------
//Class RenderSystem
//-----------------------------------------------------------------------------------------------------------------------------------------