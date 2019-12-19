#include <iostream>
#include <math.h>
#include <stdlib.h>

using namespace std;

#define N 5								//No of particles
#define ITERATIONS 1000					//Total iterations of execution
#define TIME_STEP_LENGTH 0.0001			//Length of each time step
#define DISPLAY_IN_UNITS_OF 100	

struct particle 
{
	float posx, posy, posz;				//3d components of position
	float velx, vely, velz;				//3d components of velocity
	float accx, accy, accz;				//3d components of acceleration
	float forcex, forcey, forcez;		//3d components of force
	float mass;						
};


float getforce(float x1,float x2,float m1,float m2)   //calculates the force experienced by object at
													  //position x1 due to the object at position x2
{
	float dis = abs(x1-x2);
	if(dis < 0.2)
		dis = 0.2;
	float f = (m1*m2)/pow(dis,2);
	
	if(x1 < x2)         // x1 experiences a force in the +ve direction ( x1 ---> x2 where ---> is force)
		return f;
	else
		return -f;		// x2 experiences a force in the -ve direction ( x2 <--- x1 where <--- is force)

}

float getacc(float force,float m)	//calculates acceleration of an object
{									//acceleration = force/mass									
	float acc = force/m;
	return acc;
}

float getvel(float initvel,float acc,float time)  //calculates the new velocity of the object after
{												 // time = time has elapsed 
	float vel = initvel + acc*time;
}


float getpos(float pos,float vel,float acc,float time)   //calculates the new position of an object with 
{														//after time = time
	float newpos = pos + vel*time + (1/2)*(acc)*(pow(time,2));
	return newpos;
}


int main()
{
	struct particle body[N];
	int i, j, k;
	//initialization of all parameters
	for(int i = 0 ; i < N ; i++)
	{
		body[i].posx = i;
		body[i].posy = i;
		body[i].posz = i;

		body[i].velx = 0;
		body[i].vely = 0;
		body[i].vely = 0;

		body[i].accx = 0;
		body[i].accy = 0;
		body[i].accz = 0;

		body[i].forcex = 0;
		body[i].forcey = 0;
		body[i].forcez = 0;

		body[i].mass = 10;
	}

	
	for(int i = 0 ; i < ITERATIONS ; i++)  //no of time steps
	{

		for(int j = 0 ; j < N ; j++ ) 
		{

			for (k = 0 ; k < N ; k++ ) //Getting force of body j wrt all other bodies k 
			{
				if(k != j)
				{
					body[j].forcex += getforce(body[j].posx, body[k].posx, body[j].mass, body[k].mass);
					body[j].forcey += getforce(body[j].posy, body[k].posy, body[j].mass, body[k].mass);
					body[j].forcez += getforce(body[j].posz, body[k].posz, body[j].mass, body[k].mass);
				}
			}
		}

		

		for(int j = 0 ; j < N ; j++ )		//updating all the parameters
		{

			body[j].accx = getacc(body[j].forcex, body[j].mass);  //updating acceleration
			body[j].accy = getacc(body[j].forcey, body[j].mass);
			body[j].accz = getacc(body[j].forcez, body[j].mass);
			
			if(i % DISPLAY_IN_UNITS_OF == 0)	//printing current coordinates of the particle
			{

				if(j == 0)
					cout << i << endl;
				
				cout << j << " : ("<<body[j].posx<<","<<body[j].posy<<","<<body[j].posz<<")"<<endl; 

				if(j == N-1)
					cout<<endl;
			}
			

			body[j].posx = getpos(body[j].posx, body[j].velx, body[j].accx, TIME_STEP_LENGTH); //updating position
			body[j].posy = getpos(body[j].posy, body[j].vely, body[j].accy, TIME_STEP_LENGTH); 
			body[j].posz = getpos(body[j].posz, body[j].velz, body[j].accz, TIME_STEP_LENGTH); 

			body[j].velx = getvel(body[j].velx, body[j].accx, TIME_STEP_LENGTH); //updating velocity
			body[j].vely = getvel(body[j].vely, body[j].accy, TIME_STEP_LENGTH);
			body[j].velz = getvel(body[j].velz, body[j].accz, TIME_STEP_LENGTH);
		}
		

	}

}