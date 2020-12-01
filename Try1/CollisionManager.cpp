#include "Bullet.h"
#include "CollisionManager.h"
#include "Enemy.h"
#include "EnemyBullet.h"
#include "EnemyManager.h"
#include "MusicManager.h"
#include "PlayerController.h"
#include "UIManager.h"
#include "SparkExplosion.h"

CollisionManager::CollisionManager()
= default;

// Although the functions are self explanatory, you may find details in the header
// Checks if Player and Enemy are colliding
void CollisionManager::checkForCollision(PlayerController& player, Enemy& enemy, SparkExplosion& sparkExplosion, MusicManager& musicManager, EnemyManager& enemyManager, UIManager& uiManager)
{
	if ( player.getGlobalBounds().intersects(enemy.getGlobalBounds()) )
	{
		if (enemy.getActive())
		{
			int health = player.getLife();
			uiManager.minusLife();
			uiManager.updateLifeNumber();
			player.setLife(health--);
			playExplosion(enemy, sparkExplosion);
			playHitSound(musicManager);
			killEnemy(enemy, musicManager);
			enemyManager.respawnWave(uiManager);
			updateWaveAndUI(enemyManager, uiManager);
		}
	}
}

//Checks if Enemy Bullet and Player are colliding
void CollisionManager::checkForCollision(EnemyBullet& enemyBullet, PlayerController& player, UIManager& uiManager, MusicManager& musicManager)
{
	if (enemyBullet.getGlobalBounds().intersects(player.getGlobalBounds()))
	{
		// Damage calculations
		// TODO: can only happen once every second
		int health = player.getLife();
		uiManager.minusLife();
		uiManager.updateLifeNumber();
		player.setLife(health--);
		playHitSound(musicManager);
		enemyBullet.hideBullet();
		enemyBullet.setIsActive(false);
	}
}

void CollisionManager::playExplosionSound(MusicManager& musicManager)
{
	musicManager.playRandomExplosion();
}

void CollisionManager::playHitSound(MusicManager& musicManager)
{
	musicManager.playRandomHitEffect();
}

void CollisionManager::killEnemy(Enemy& enemy, MusicManager& musicManager)
{
	enemy.setActive(false);
	enemy.setDead(true);
	playExplosionSound(musicManager);
}

void CollisionManager::updateWaveAndUI(EnemyManager& enemyManager, UIManager& uiManager)
{
	enemyManager.lastAlive();
	enemyManager.incrementWave();
	uiManager.addScoreUI();
}

void CollisionManager::playExplosion(Enemy& enemy, SparkExplosion& sparkExplosion)
{
	sparkExplosion.restartTimer();
	sparkExplosion.setPos(enemy.getPosition().x, enemy.getPosition().y);
	sparkExplosion.setIsActive();
}

void CollisionManager::checkForCollision(Bullet& bullet, Enemy& enemy, MusicManager& musicManager, EnemyManager& enemyManager, UIManager& uiManager, SparkExplosion& sparkExplosion)
{
	if (bullet.getGlobalBounds().intersects(enemy.getGlobalBounds()))
	{
		if( enemy.getActive() == true )
		{
			bullet.setIsActive(false);
			uiManager.updateScoreNumber();
			uiManager.updateWaveNumber();
			playExplosion(enemy, sparkExplosion);
			killEnemy(enemy, musicManager);
			updateWaveAndUI(enemyManager, uiManager);
			enemyManager.respawnWave(uiManager);
		}
	}
}

void CollisionManager::update(Bullet& bullet, MusicManager& musicManager, EnemyManager& enemyManager, UIManager& uiManager, SparkExplosion& sparkExplosion, EnemyBullet &enemyBullet, PlayerController &player) const
{
	for(  int i = 0; i < m_kArraySize; i++ )
	{
		checkForCollision(bullet, enemyManager.m_pEnemyArray[i], musicManager, enemyManager, uiManager, sparkExplosion);
		checkForCollision(player, enemyManager.m_pEnemyArray[i], sparkExplosion, musicManager, enemyManager, uiManager);
	}
	checkForCollision(enemyBullet, player, uiManager, musicManager);
}


bool CollisionManager::checkForCollision(Bullet& bullet, Base& base)
{
	return true;
}

bool CollisionManager::checkForCollision(EnemyBullet& bullet, Base& base)
{
	return true;
}

template <class T> T CollisionManager::checkColl(T*& obj1, T*& obj2)
{
	return (obj1.getGlobalBounds().intersects(obj2.getGlobalBounds()));
}
