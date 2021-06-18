#include "collision_handler.h"
#include <iostream>

namespace collision
{
	void CheckCollisions(std::vector<std::shared_ptr<entities::CollisionEntity>>& entities)
	{
		if (entities.size() < 2) { return; }
			if (entities.size() == 2)
			{
				if (entities[0]->IsColliding(*entities[1]))
				{
					collision::Collision c = { *entities[0], *entities[1] };
					entities[0]->OnCollide(c);
					entities[1]->OnCollide(c);
				}
			}
		
			for (int i = 0; i < entities.size() - 2; i++)
			{
				std::shared_ptr<entities::CollisionEntity> entity = entities[i];

				for (int j = i + 1; j < entities.size() - 1; j++)
				{
					
					std::shared_ptr<entities::CollisionEntity> entity2 = entities[j];

					if (entity == entity2)
					{
						continue;
					}

					if (entity->IsColliding(*entity2))
					{
						collision::Collision c = { *entity, *entity2 };
						entity->OnCollide(c);
						entity2->OnCollide(c);
						break;
					}
				}
			}
			
	}
}
