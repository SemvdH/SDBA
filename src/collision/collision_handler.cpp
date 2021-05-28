#include "collision_handler.h"

namespace collision
{
	void CheckCollisions(std::vector<entities::CollisionEntity*>& entities)
	{
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
		 	entities::CollisionEntity* entity = entities[i];
		 	
		 	for (int j = i + 1; i < entities.size() - 1; j++)
		 	{
		 		entities::CollisionEntity* entity2 = entities[j];
		 		
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
