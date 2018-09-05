#ifndef __SHIP_H_INCLUDED__
#define __SHIP_H_INCLUDED__

#include "structs.h"
#include <vector>

class ship
{
    public:
        //constructors
        explicit ship(int tp, std::vector<point> pnts); 
        explicit ship(int tp);

        //getters
        std::vector<point> getPoints();
        std::vector<triangle> getTriangles();
        std::vector<point> getAtkPnts();
        
        //setters
        point getLocation();
        int getHealth();
        void setRotation(double rot);
        void setLocation(double x, double y);

        //actions
        void fire();                    // fire weapon
        void iterateAction();           // move / fire weapon
        //void activatePowerUp(PowerUp pwr);        // change weapon type
        void activatePowerUp(int pwr);
        void setAction(int act);
        int damageHealth(int dmg);
        void resetShip();

        //render functions
        void renderShip();              // draw the ship
        void tessilateShip();           // Tesslate the ship
        
    
    private:
        //main variables
        int type;
        point location;
        std::vector<point> shppnts;
        std::vector<triangle> shptris;
        std::vector<point> atkpnts;
        int actionSet;
        int health;
        int cycle;
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