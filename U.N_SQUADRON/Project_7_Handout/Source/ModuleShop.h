#ifndef _MODULESHOP_H_
#define _MODULESHOP_H_

#include "Module.h"
#include "Animation.h"
#include"Path.h"

struct SDL_Texture;

struct WeaponsPrice {
	bool selected = false;
	int ammo;
	int priceWeapon;
};

class ModuleShop : public Module
{
public:
	//Constructor
	ModuleShop(bool startEnabled);

	//Destructor
	~ModuleShop();

	// Called when the module is activated
	// Loads the necessary textures for the map background
	bool Start() override;

	// Called at the middle of the application loop
	// Updates the scene's background animations
	update_status Update() override;
	bool CleanUp();

	// Sound effects indices
	uint chooseFx = 0;
	// Called at the end of the application loop.
	// Performs the render call of all the parts of the scene's background
	update_status PostUpdate() override;
	void select();
	void activeSelected(int _weapon);


public:
	enum SHOP_SLOT: int{
		CLUSTER,
		PHOENIX,
		FALCON,
		BULLPUP,
		S_SHELL,
		T_LASER,
		BOMB,
		NAPALM,
		GUNPOD,
		CEILING,
		MEGACRUSH,
		EXIT,

	};

	SDL_Texture* bgTexture = nullptr;
	SDL_Texture* selectorTexture = nullptr;
	int tiendaX = 0, tiendaY = 0;
	int weaponsition = 0;
	uint OptionSelection = 0;
	uint SelectWeapon = 0;
	uint InsuficientMoney = 0;

	bool keyDownPad = false;
	int hudfont1 = 0;

	int selectedWeapon;

	bool begin = false;

	//info

	int money = 3000;
	int score = 0;
	int level = 2;
	int pow = 0;
	int total = 0;
	int lives = 2;

	bool infiniteMoney = false;

	WeaponsPrice weapons[11];

	char moneyText[10] = { "\0" };

	//solved
	SDL_Texture* WeaponsSold = nullptr;

	


};
#endif // !_MODULESHOP_H_