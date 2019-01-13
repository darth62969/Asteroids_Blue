#ifndef __SHIP_H__
#define __SHIP_H__

#include "headers.h"
#include "object.h"
#include "bullet.h"


class ship : public object 
{
    public:
        //constructors
		ship();
        ship(int tp, std::vector<point> pnts); 
        ship(int tp);

        //getters
		virtual std::vector<point> getBounds();
        virtual std::vector<point> getPoints();
        virtual std::vector<triangle> getTriangles();
        virtual std::vector<point> getAtkPnts();
        
        //setters
	
		int getHealth();         
		void setHealth(int dmg);
		int getAction();
		void setAction(int act);
		



        //actions

        virtual void fire(mode * md);                    // fire weapon
		virtual void resetShip();

        void iterateAction();           // move / fire weapon

		int addHealth(int dmg);
		int damageHealth(int dmg);


//        void activatePowerUp(PowerUp pwr);        // change weapon type
//        void activatePowerUp(int pwr);




        //render functions
		virtual void render();
        
		/*depreciated*/
		void renderShip();              // draw the ship
        void tessilateShip();           // Tesslate the ship
        
    
    protected:
    	//main variables
        std::vector<point> atkpnts;
        int actionSet;
        int health;
        int cycle;
		bullet blt;
        //PowerUp power

        //specific variables for things
        double EndGameAnimation;
        double WinGameAnimation=0;
        point shipRender;

        double seconds;


};

class PowerUp
{
    
    public:
        explicit PowerUp(int type);
        explicit PowerUp(int frate, int ftype, int fcount, double farch, int dmg, int time);
        void setLocation(point loc);
        void increment();
        void drawPowerUp();
    private:
        friend class ship;

        int type;
        int firerate;
        int firetype;
        int firecount;
        double firearc;
        int damage;
        int time;
        point location;

    
};

#endif