#ifndef COLLISIONMANAGER_H
#define COLLISIONMANAGER_H


// Forward class declaration for the functions
class Base;
class Bullet;
class Enemy;
class EnemyBullet;
class EnemyManager;
class MusicManager;
class PlayerController;
class SparkExplosion;
class UIManager;


class CollisionManager
{
private:
	// Overloaded function checking individual collision type
	// And returning true if the they are intersecting
	// Checks for player and enemy
	static void checkForCollision(PlayerController &player, Enemy &enemy, SparkExplosion& sparkExplosion, MusicManager& musicManager, EnemyManager& enemyManager, UIManager& uiManager);

	// Checks for player bullet and enemy
	static void checkForCollision(Bullet &bullet, Enemy &enemy, MusicManager &musicManager, EnemyManager &enemyManager, UIManager &uiManager, SparkExplosion &sparkExplosion);

	// Check for enemy bullet and player
	static void checkForCollision(EnemyBullet &enemyBullet, PlayerController &player, UIManager& uiManager, MusicManager& musicManager);

	// Check for player bullet and bases
	static bool checkForCollision(Bullet &bullet, Base &base);

	// Check for enemy bullet and base
	static bool checkForCollision(EnemyBullet &bullet, Base &base);

	// Function to "kill" the enemy collided with
	static void killEnemy(Enemy& enemy, MusicManager& musicManager);

	// Updates the UI and Wave logic
	static void updateWaveAndUI(EnemyManager& enemyManager, UIManager& uiManager);

	// Plays explosion at enemy location
	static void playExplosion(Enemy& enemy, SparkExplosion& sparkExplosion);

	// Plays a sound on death/hit
	static void playExplosionSound(MusicManager& musicManager);
	static void playHitSound(MusicManager& musicManager);


	// Template try
	template <class T>	static T checkColl(T*& obj1, T*& obj2);


public:
	CollisionManager();

	// Checks objects for collision
	void update(Bullet &bullet, MusicManager &musicManager, EnemyManager &enemyManager, UIManager &uiManager, SparkExplosion &sparkExplosion, EnemyBullet &enemyBullet, PlayerController &player) const;

};


#endif
