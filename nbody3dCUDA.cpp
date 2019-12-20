#include <iostream>
#include <stdio.h>
#include <cuda.h>
#include <cuda_device_runtime_api.h>
#include <chrono>

using namespace std::chrono;

using namespace std;

#define N 10								//No of particles
#define ITERATIONS 1000					//Total iterations of execution
#define TIME_STEP_LENGTH 0.000001			//Length of each time step
#define DISPLAY_IN_UNITS_OF 100	

struct particle 
{
	float posx, posy, posz;				//3d components of position
	float velx, vely, velz;				//3d components of velocity
	float accx, accy, accz;				//3d components of acceleration
	float forcex, forcey, forcez;		//3d components of force
	float mass;						
};

__global__ void updateForce(struct particle *body)
{
	int tID = blockIdx.x;
	int dif,sign,k;

	if(tID < N)
	{

		for (k = 0 ; k < N ; k++ ) //Getting force of body j wrt all other bodies k 
				{
					if(k != tID)
					{
						dif = body[tID].posx - body[k].posx;
						if(dif < 0)
							sign = -1;
						else
							sign = 1;
						body[tID].forcex += (sign)*((body[tID].mass*body[k].mass)/
											(powf(abs(dif),2)));

						dif = body[tID].posy - body[k].posy;
						sign = dif/abs(dif);
						body[tID].forcey += (sign)*((body[tID].mass*body[k].mass)/
											(powf(abs(dif),2)));

						dif = body[tID].posz - body[k].posz;
						sign = dif/abs(dif);
						body[tID].forcez += (sign)*((body[tID].mass*body[k].mass)/
											(powf(abs(dif),2)));

					}
				}
	}				
}


__global__ void updateParameters(struct particle *body)
{
	int tID = blockIdx.x;

	if(tID < N)
	{

		body[tID].accx = body[tID].forcex/body[tID].mass;  //updating acceleration
		body[tID].accy = body[tID].forcey/body[tID].mass;
		body[tID].accz = body[tID].forcez/body[tID].mass;

		body[tID].posx += body[tID].velx*TIME_STEP_LENGTH + (1/2)*body[tID].accx*powf(TIME_STEP_LENGTH,2); //updating position
		body[tID].posy += body[tID].vely*TIME_STEP_LENGTH + (1/2)*body[tID].accy*powf(TIME_STEP_LENGTH,2); 
		body[tID].posz += body[tID].velz*TIME_STEP_LENGTH + (1/2)*body[tID].accz*powf(TIME_STEP_LENGTH,2); 

		body[tID].velx += body[tID].accx*TIME_STEP_LENGTH; //updating velocity
		body[tID].vely += body[tID].accy*TIME_STEP_LENGTH;
		body[tID].velz += body[tID].accz*TIME_STEP_LENGTH;
	}
}



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




int main()
{
	struct particle body[N];
	struct particle *nbodies;
	int i,j;

	

	for(int i = 0 ; i < N ; i++)
	{
		body[i].posx = i+1;
		body[i].posy = i+1;
		body[i].posz = i+1;

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

	cudaMalloc((void **) &nbodies, N*sizeof(struct particle));

	auto start = high_resolution_clock::now(); 

	for(i = 0 ; i < ITERATIONS ; i++ )
	{	

		cudaMemcpy(nbodies, body, N*sizeof(struct particle), cudaMemcpyHostToDevice);

		updateForce<<<N,1>>>(nbodies);

		cudaDeviceSynchronize();

		updateParameters<<<N,1>>>(nbodies);	

		cudaMemcpy(body, nbodies, N*sizeof(struct particle), cudaMemcpyDeviceToHost);

		cudaDeviceSynchronize();



		for(j = 0 ; j < N ; j++ )
		{

			if(i % DISPLAY_IN_UNITS_OF == 0)	//printing current coordinates of the particle
				{

					if(j == 0)
						cout << "Iteration : " << i << endl;
						
					cout << j << " : ("<<body[j].posx<<","<<body[j].posy<<","<<body[j].posz<<")"<<endl; 

					if(j == N-1)
						cout<<endl;
				}
		}
	
	}

	auto stop = high_resolution_clock::now(); 

	auto duration = duration_cast<microseconds>(stop - start);

	cout << "Time Taken : " << duration.count() << endl;

}
