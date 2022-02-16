#include "Stdafx.h"
#include "SecondScene.h"
void SecondScene::collision(void)
{
	bool isCollided = false;
	for (int j = 0; j < _em->getMinion().size(); j++)
	{
		if (isCollided)
			break;

		for (int i = 0; i < _player->getMissile()->getBullet().size(); i++)
		{
			tagBullet playerBullet = _player->getMissile()->getBullet()[i];
			if (!playerBullet.fire)
			{
				continue;
			}
			if (j >= _em->getMinion().size())
			{
				continue;
			}
			Enemy* enemy = _em->getMinion()[j];
			if (enemy == nullptr)
			{
				continue;
			}
			RECT rc;
			if (IntersectRect(&rc, &playerBullet.rc,
				&CollisionAreaResizing(enemy->getRect(), 40, 30)))
			{
				_missileEffect->show(rc);
				_player->removeMissile(i);
				_em->removeMinion(j);
				_score += 50;
				isCollided = true;
				break;
			}
		}

		for (int i = 0; i < _player->getShotgun()->getBullet().size(); i++)
		{
			tagBullet playerBullet = _player->getShotgun()->getBullet()[i];
			if (!playerBullet.fire)
			{
				continue;
			}
			if (j >= _em->getMinion().size())
			{
				continue;
			}
			Enemy* enemy = _em->getMinion()[j];
			if (enemy == nullptr)
			{
				continue;
			}

			RECT rc;
			if (IntersectRect(&rc, &playerBullet.rc,
				&CollisionAreaResizing(enemy->getRect(), 40, 30)))
			{
				_missileEffect->show(rc);
				_player->removeMissile(i);
				_em->removeMinion(j);
				_score += 30;
				isCollided = true;
				break;
			}
		}

		for (int i = 0; i < _player->getMiniRocket()->getBullet().size(); i++)
		{
			tagBullet playerBullet = _player->getMiniRocket()->getBullet()[i];
			if (!playerBullet.fire)
			{
				continue;
			}
			if (j >= _em->getMinion().size())
			{
				continue;
			}
			Enemy* enemy = _em->getMinion()[j];
			if (enemy == nullptr)
				continue;

			RECT rc;
			if (IntersectRect(&rc, &playerBullet.rc,
				&CollisionAreaResizing(enemy->getRect(), 40, 30)))
			{
				_miniRocketEffect->show(rc);
				_player->removeMissile(i);
				_em->removeMinion(j);
				_score += 20;
				isCollided = true;
				break;
			}
		}

		for (int i = 0; i < _player->getBeam()->getBullet().size(); i++)
		{
			tagBullet playerBullet = _player->getBeam()->getBullet()[i];
			if (j >= _em->getMinion().size())
			{
				continue;
			}
			RECT rc;
			if (IntersectRect(&rc, &playerBullet.rc,
				&CollisionAreaResizing(_em->getMinion()[j]->getRect(), 40, 30)))
			{
				_beamEffect->show(rc);
				_em->removeMinion(j);
				_score += 10;
				isCollided = true;
				break;
			}
		}
	}

	for (int i = 0; i < _em->getBullet()->getBullet().size(); i++)
	{
		RECT rc;
		if (IntersectRect(&rc, &_em->getBullet()->getBullet()[i].rc, &_player->getRect()))
		{
			_em->getBullet()->removeBullet(i);
			_player->hitDamage(0.5f);
		}
	}
}

