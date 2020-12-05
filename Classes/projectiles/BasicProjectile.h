#pragma once
#include "Projectile.h" 
class BasicProjectile : public Projectile
{
private:
	
public:
	BasicProjectile(Enemy * target, float speed, float damage);
	virtual bool init();
};