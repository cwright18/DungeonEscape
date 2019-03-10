#ifndef _KYLES_H_
#define _KYLES_H_

#include <X11/Xlib.h>
#include <X11/keysym.h>
#include <GL/glx.h>
#include <cstdlib>
#include <cmath>
#include <ctime>
#include <cstring>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include "ppm.h"
//types
typedef float Flt;
typedef Flt Matrix[4][4];

//macros
#define rnd() (((Flt)rand())/(Flt)RAND_MAX)

//constants
const Flt timeslice = 1.0f;
const Flt gravity = -0.2f;
#define PI 3.141592653589793
#define ALPHA 1
#define RUN 6.0
#define WALK 3.5 //default 2...I think
#define JUMP 6.0 //default 4.0
#define WINDOW_WIDTH 1200
#define WINDOW_HEIGHT 900
#define GRAVITY 0.25 //default 0.1
#define OFFSET 15
#define C_HEIGHT 2
#define C_WIDTH 10
#define W_HEIGHT 3
#define W_WIDTH 10
#define MAXBUTTONS 3
#define MAXPARTICLES 400

//structs
struct Vec {
	Flt x, y, z;
};

struct Shape {
	Flt width, height;
	Flt radius;
	Vec center;
};

struct Particle {
	Shape s;
	Vec velocity;
};

struct Hurtbox {
	Flt width, height;
	Flt radius;
	Vec center;
};

struct Button {
	Flt width, height;
	Vec center;
	GLfloat alpha;
};

struct Hitbox {
	Flt width, height;
	Vec center;
};

enum State {
	STATE_NONE,
	STATE_STARTMENU,
	STATE_LOADING,
	STATE_GAMEPLAY,
	STATE_PAUSE,
	STATE_CONTROLS,
	STATE_GAMEOVER,
	STATE_WON
};

class Texture {
public:
	Ppmimage *background;
	Ppmimage *box;
	Ppmimage *spike;
	Ppmimage *start;
	Ppmimage *loading;
	Ppmimage *died;
	Ppmimage *credits;
	Ppmimage *platform;
	Ppmimage *flames;
	GLuint spikeTexture;
	GLuint startTexture;
	GLuint loadTexture;
	GLuint platTexture;
	GLuint backTexture;
	GLuint diedTexture;
	GLuint creditsTexture;
	GLuint boxTexture;
	GLuint flamesTexture;
	Flt xc[2];
	Flt yc[2];
	Flt xd[2];
	Flt yd[2];
	Flt xl[2];
	Flt yl[2];
	Flt xb[2];
	Flt yb[2];
	Flt xB[2];
	Flt yB[2];
	Flt xs[2];
	Flt ys[2];
	Flt xS[2];
	Flt yS[2];
	Flt xp[2];
	Flt yp[2];
	Flt xf[2];
	Flt yf[2];
};

class Weapon {
public:
	Shape s;
	Hitbox hit;
	Vec velocity;
	Vec initThrow;
	bool weaponSnd;
	bool thrown;
};

class Character {
public:
	Shape s;
	Weapon l[2];
	Hurtbox hurt;
	Vec dir;
	Vec pos;
	Vec velocity;
	int jumpCurrent;
	int jumpMax;
	bool soundChk;
	bool hurtJump;
	Flt angle;
	Flt color[3];
	bool upgrade;
	bool upgrade2;
	bool isLeft;
};

class Game {
public:
	Shape box[7];
	Shape plat[20];
	Shape spike[20];
	Character character;
	State state;
	Texture tex;
	Button button;
	Particle particle[MAXPARTICLES];
	int n;
	int num;
	int xres, yres;
	int done;
	char keys[65536];
	bool swtch;
	bool hasDied;
	Game() {
		n = 0;
		num = 0;
		state = STATE_STARTMENU;
		xres = WINDOW_WIDTH;
		yres = WINDOW_HEIGHT;
		done = 0;
		memset(keys, 0, 65536);
		button.alpha = 1.0;
		button.height = 50;
		button.width = 100;
		hasDied = false;
	}
};

#endif //_KYLES_H_
