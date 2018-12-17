
#include "enterprise.h"


	enterprise::enterprise()
	{
		location = {0, 0, 0, 1, 0};
		layer lyr;
		//Generate the Enterprise
		lyr.pnts.push_back(point{ 5,  0, 0, 1});
		lyr.pnts.push_back(point{ 2,  1, 0, 1});
		lyr.pnts.push_back(point{ 2,  3, 0, 1});
		lyr.pnts.push_back(point{-5,  3, 0, 1});
		lyr.pnts.push_back(point{-5,  1, 0, 1});
		lyr.pnts.push_back(point{ 0,  1, 0, 1});
		lyr.pnts.push_back(point{ 0, -1, 0, 1});
		lyr.pnts.push_back(point{-5, -1, 0, 1});
		lyr.pnts.push_back(point{-5, -3, 0, 1});
		lyr.pnts.push_back(point{ 2, -3, 0, 1});
		lyr.pnts.push_back(point{ 2, -1, 0, 1});

		//Generate Trangles
		tessellate(&lyr);

		//set attack points (i.e. where it shoots from)
		atkpnts.push_back(point{ 5,  0, 0, 1});

		health = 100;
		cycle = 0;
		EndGameAnimation = 5;

	}
}