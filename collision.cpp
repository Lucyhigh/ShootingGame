#include "Stdafx.h"
#include "MainGame.h"

void MainGame::collision(void)
{
	for (int i = 0; i < _rocket->getMissile()->getBullet().size(); i++)
	{
		for (int j = 0; j < _em->getMinion().size(); j++)
		{
			RECT rc;
			if (IntersectRect(&rc, &_rocket->getMissile()->getBullet()[i].rc,
				&CollisionAreaResizing(_em->getMinion()[j]->getRect(), 40, 30)))
			{
				_rocket->removeMissile(i);
				_em->removeMinion(j);
				break;
			}
		}
	}
	for (int i = 0; i < _rocket->getBeam()->getBullet().size(); i++)
	{
		for (int j = 0; j < _em->getMinion().size(); j++)
		{
			RECT rc;
			if (IntersectRect(&rc, &_rocket->getBeam()->getBullet()[i].rc,
				&CollisionAreaResizing(_em->getMinion()[j]->getRect(), 40, 30)))
			{
				_em->removeMinion(j);
				break;
			}
		}
	}
	for (int i = 0; i < _rocket->getShotgun()->getBullet().size(); i++)
	{
		for (int j = 0; j < _em->getMinion().size(); j++)
		{
			RECT rc;
			if (IntersectRect(&rc, &_rocket->getShotgun()->getBullet()[i].rc,
				&CollisionAreaResizing(_em->getMinion()[j]->getRect(), 40, 30)))
			{
				_em->removeMinion(j);
				break;
			}
		}
	}
	for (int i = 0; i < _rocket->getMiniRocket()->getBullet().size(); i++)
	{
		for (int j = 0; j < _em->getMinion().size(); j++)
		{
			RECT rc;
			if (IntersectRect(&rc, &_rocket->getMiniRocket()->getBullet()[i].rc,
				&CollisionAreaResizing(_em->getMinion()[j]->getRect(), 40, 30)))
			{
				_em->removeMinion(j);
				break;
			}
		}
	}
}