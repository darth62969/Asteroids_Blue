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
        
        //setters
        point getLocation();
        void setRotation(double rot);
        void setLocation(double x, double y);

        //actions
        void fire();                    // fire weapon
        void iterateAction();           // move / fire weapon
        void PowerUp(int power);        // change weapon type
        void setAction(int act);
        void damageHealth(int dmg);
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

        //specific variables for things
        double EndGameAnimation=7;
        double WinGameAnimation=0;
        point shipRender;




};

#endif