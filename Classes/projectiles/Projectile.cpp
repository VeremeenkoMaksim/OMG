#include "Projectile.h" 

Projectile::Projectile(Enemy * target, float speed, float damage) {
	this->target = target;
	this->speed = speed;
	this->damage = damage;
}

bool Projectile::init() {
	this->scheduleUpdate();
	return true;
}

void Projectile::update(float dt) {
	if (MoveToTarget(target, dt)) {
		cocos2d::Director::getInstance()->getRunningScene()->removeChild(this, false);
		target->ReceiveDamage(damage);
	}
}

bool Projectile::MoveToTarget(Enemy * target, float dt) {
	auto distance = this->getPosition().distance(target->getPosition());
	if (distance > 10) {
		auto direction = FindDirection(target->getPosition(), this->getPosition());
		this->setPosition(this->getPosition().x + speed * dt * direction.x, this->getPosition().y + speed * dt * direction.y);
	}
	else return true;
	return false;
}

cocos2d::Vec2 Projectile::FindDirection(cocos2d::Vec2 currentPos, cocos2d::Vec2 targetPos) {
	cocos2d::Vec2 dir;
	cocos2d::Vec2 distanceToTarget = currentPos - targetPos;
	if (distanceToTarget.x < 0)
		dir.x = -1;
	else if (distanceToTarget.x > 0)
		dir.x = 1;
	if (distanceToTarget.y < 0)
		dir.y = -1;
	else if (distanceToTarget.y > 0)
		dir.y = 1;
	return dir;
}