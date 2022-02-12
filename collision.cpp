#include "Stdafx.h"
#include "Collision.h"

HRESULT Collision::init(Rocket* rocket, EnemyManager* em, EffectManager* efxm)
{
	_rocket = rocket;
	_em = em;
	_efxm = efxm;
	return S_OK;
}


void Collision::update(void)
{
	for (int i = 0; i < _rocket->getMissile()->getBullet().size(); i++)
	{
		for (int j = 0; j < _em->getMinion().size(); j++)
		{
			
			if (IntersectRect(&rc, &_rocket->getMissile()->getBullet()[i].rc,
				&CollisionAreaResizing(_em->getMinion()[j]->getRect(), 40, 30)))
			{
				_rocket->removeMissile(i);
				_em->removeMinion(j);
				_efxm->slashEffect(PointMake(rc.left,rc.top));
				break;
			}
		}
	}
	for (int i = 0; i < _rocket->getBeam()->getBullet().size(); i++)
	{
		for (int j = 0; j < _em->getMinion().size(); j++)
		{
			
			if (IntersectRect(&rc, &_rocket->getBeam()->getBullet()[i].rc,
				&CollisionAreaResizing(_em->getMinion()[j]->getRect(), 40, 30)))
			{
				_em->removeMinion(j);
				_efxm->dustEffect(PointMake(rc.left, rc.top));
				break;
			}
		}
	}
	for (int i = 0; i < _rocket->getShotgun()->getBullet().size(); i++)
	{
		for (int j = 0; j < _em->getMinion().size(); j++)
		{
			
			if (IntersectRect(&rc, &_rocket->getShotgun()->getBullet()[i].rc,
				&CollisionAreaResizing(_em->getMinion()[j]->getRect(), 40, 30)))
			{
				_rocket->removeMissile(i);
				_em->removeMinion(j);
				
				break;
			}
		}
	}
	for (int i = 0; i < _rocket->getMiniRocket()->getBullet().size(); i++)
	{
		for (int j = 0; j < _em->getMinion().size(); j++)
		{
		
			if (IntersectRect(&rc, &_rocket->getMiniRocket()->getBullet()[i].rc,
				&CollisionAreaResizing(_em->getMinion()[j]->getRect(), 40, 30)))
			{
				_rocket->removeMissile(i);
				_em->removeMinion(j);
			
				break;
			}
		}
	}
}
