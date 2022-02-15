#include "Stdafx.h"
#include "SecondScene.h"
void SecondScene::collision(void)
{
    for (int i = 0; i < _player->getMissile()->getBullet().size(); i++)
    {
        for (int j = 0; j < _em->getMinion().size(); j++)
        {
            RECT rc;
            if (IntersectRect(&rc, &_player->getMissile()->getBullet()[i].rc,
                &CollisionAreaResizing(_em->getMinion()[j]->getRect(), 40, 30)))
            {
                _missileEffect->show(rc);
                _player->removeMissile(i);
                _em->removeMinion(j);
                break;
            }
        }
    }
    for (int i = 0; i < _player->getBeam()->getBullet().size(); i++)
    {
        for (int j = 0; j < _em->getMinion().size(); j++)
        {
            RECT rc;
            if (IntersectRect(&rc, &_player->getBeam()->getBullet()[i].rc,
                &CollisionAreaResizing(_em->getMinion()[j]->getRect(), 40, 30)))
            {
                _beamEffect->show(rc);
                _em->removeMinion(j);
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
            _player->hitDamage(0.05f);
        }
    }
}
