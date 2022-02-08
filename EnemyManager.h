#pragma once
#include "GameNode.h"
#include "Enemy.h"

class EnemyManager:public GameNode
{
	//typedef c거임..
	//typedef vector<Enemy***> vEnemy;이 제일 좋음
	//더블포인터는 참조의 참조
	//트리플포인터 friend 키워드 객체지향 파괴하는 키워드 - 정보은닉 무시
	//상속으로 엮기긴 싫은데 친구키워드로 엮으면 프라이빗을 뒤적일수있음 일방적 친구임
	//겟셋은 함수에 의한 호출
	//겟셋은 후입선출(LIFO) - 속도가 더 느림
	//go to급이라고 생각하는 사람도 있음 딱 적재적소에 쓰는게 좋음! - 스파게티 되기 딱좋음

	//참조-> 주솟값을 줄테니 스마트포인터로 사용하셈
private:
	typedef vector<Enemy*> vEnemy;
	typedef vector<Enemy*>::iterator viEnemy;

private:
	vEnemy _vMiniom;
	viEnemy _viMiniom;

public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	void setMinion(void);
	void setMinion2(void);
	void setMinion3(void);

	EnemyManager() {}
	~EnemyManager() {}
};

