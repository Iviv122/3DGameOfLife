#include <GLFW/glfw3.h>
#include <stdio.h>
#include <stdlib.h>

#define HEIGHT 50
#define WIDTH 50
#define LENGTH 50

int getLife(int*** matrix, int x,int y, int z){

	int counter=0;

	for(int i=-1;i<=1;i++){
	for(int j=-1;j<=1;j++){
	for(int k=-1;k<=1;k++){
	
	if( i== 0 & j == 0 && k == 0){continue;}
	
	int nx = i+x;
	int ny = j+y;
	int nz = k+z;	

	if(WIDTH-1 < nx || HEIGHT-1 < ny || LENGTH-1 < nz ){ continue;}
	if(0 > nx || 0 > ny || 0 > nz){continue;}
	if(matrix[nx][ny][nz] == 1) {counter++;}	

	}}}

	return counter;
}

void updateLife(int*** matrix, int*** tempmatrix,int x,int y,int z){

	int count = getLife(matrix,x,y,z);

        if(count <2 || count > 3){
        tempmatrix[x][y][z] = 0;
	}else if(count == 3){
        tempmatrix[x][y][z] = 1;
	}else if(count ==2 && matrix[x][y][z] == 1) {
	tempmatrix[x][y][z] =1;        
	}

}

int main(void)
{
	int*** matrix;
	int*** tempmatrix;
	
	float scale = (float) 1/WIDTH;

	matrix = (int***)calloc(WIDTH,sizeof(int**));
	tempmatrix = (int***)calloc(WIDTH,sizeof(int**));
 
	for(int i=0;i<WIDTH;i++){
	matrix[i] = (int**)calloc(HEIGHT,sizeof(int*));
	tempmatrix[i] = (int**)calloc(HEIGHT,sizeof(int*));
		
		for(int j=0;j<HEIGHT;j++){
		matrix[i][j] = (int*)calloc(LENGTH,sizeof(int));
		tempmatrix[i][j] = (int*)calloc(LENGTH,sizeof(int));
		}
	}

	matrix[25][25][23] = 1;
	matrix[25][25][24] = 1;
	matrix[25][25][25] = 1;

	GLFWwindow* window;

	if (!glfwInit())
		return -1;

	window = glfwCreateWindow(1000, 1000, "Hello World", NULL, NULL);
	if (!window)
	{
			glfwTerminate();
			return -1;
		}
		glfwMakeContextCurrent(window);
		while (!glfwWindowShouldClose(window))
		{
		glClear(GL_COLOR_BUFFER_BIT);
		
		glPushMatrix();	
		glRotatef(35,1,1,1);
		glScalef(scale,scale,scale);
		glPointSize(2);
		glBegin(GL_POINTS);
			
			for(int x=0;x<WIDTH;x++){
			for(int y=0;y<HEIGHT;y++){
			for(int z=0;z<LENGTH;z++){
				updateLife(matrix,tempmatrix,x,y,z);
				if(matrix[x][y][z] == 1) {glVertex3f(x-(WIDTH/2),y-(HEIGHT/2),z-(LENGTH/2));}
			}}}
		glEnd();
		glPopMatrix();
		
		int*** temp = matrix;
		matrix = tempmatrix;
		tempmatrix = temp;



        glfwSwapBuffers(window);

        glfwPollEvents();
    }
	free(tempmatrix);
	free(matrix);
	glfwTerminate();
	return 0;
}

