#include <iostream>
#include "grid.h"
#include <cassert>
#include <cctype>
#include <string>

using namespace std;

bool isPathWellFormed(string path){
	int k=0;
	if (path == "")
		return true;

	for (int pathSegment =0;;pathSegment++){
		if (k==path.size())
			break;
		if (isdigit(path[k]))
		{
			k++;
			if (k==path.size())
				return false;
			if (isdigit(path[k])){     //2 digit string segment
				k++;
				if (k==path.size())
					return false;
		if (path[k]=='n'||path[k]=='N'||path[k]=='s'||path[k]=='S'||path[k]=='e'||path[k]=='E'||path[k]=='w'||path[k]=='W')
			k++;
	
		else 
			return false;
			}
			else if (path[k]=='n'||path[k]=='N'||path[k]=='s'||path[k]=='S'||path[k]=='e'||path[k]=='E'||path[k]=='w'||path[k]=='W')
				k++;
	
			else
				return false;
		}
		else                      //needs to start with a digit
			return false;
	}
	return true;
}

int traverseSegment(int r, int c, char dir, int maxSteps){
	if (isWall(r,c))                           //prevents function from doing impossible things
		return -1;
	if ( r<1||c<1||r>getRows()||c>getCols()) 
		return -1;
	if (dir!= 'n'&&dir!='N'&&dir!= 's'&&dir!= 'S'&&dir!= 'e'&&dir!= 'E'&&dir!= 'w'&&dir!= 'W')
		return -1;
	if (maxSteps<0)
		return -1;
	if (maxSteps==0)
		return 0;
	for(int validSteps=0; validSteps!=maxSteps;validSteps++){
		if (dir=='n'||dir=='N')
			if(r>1) //prevents checking a nonexisting space
				if(!isWall(r-1,c)) //checks the next space for a wall
					r--;
				else 
					return validSteps;
			else if (r==1)
				return validSteps;
			else
				return 0;
		if (dir=='s'||dir=='S')
			if (r<getRows())
				if(!isWall(r+1,c))
					r++;
				else
					return validSteps;
			else if (r==getRows())
				return validSteps;
			else 
				return 0;
		if (dir=='e'||dir=='E')
			if (c<getCols())
				if(!isWall(r,c+1))
					c++;
				else 
					return validSteps;
			else if (c==getCols())
				return validSteps;
			else
				return 0;
		if (dir=='w'||dir=='W')
			if (c>1)
				if(!isWall(r,c-1))
					c--;
				else
					return validSteps;
			else if (c==1)
				return validSteps;
			else
				return 0;

	}
	return maxSteps;
}	
int traversePath(int sr, int sc, int er, int ec, string path, int& nsteps){
	char direction;
	int maxStepsOne;
	
	int maxStepsTwo;
	int maxStepsTotal;
	char zero = '0';
	
	if (sr<1 || sr>getRows()||sc<1||sc>getCols())
		return 3;
	if (er<1 || er>getRows()||ec<1||ec>getCols())
		return 3;
	if (isWall(sr,sc)||isWall(er,ec))
		return 3;
	if (!isPathWellFormed(path))
		return 3;
	int stepsTaken=0;
	nsteps=0;
	maxStepsOne = 0;
	maxStepsTwo = 0;
	
	for(int k = 0;k<path.size();){
	if (isdigit(path[k])){ 
		maxStepsOne = path[k]-zero; //converts char to int value
		
		k++;
		if (isdigit(path[k])){              //for numbers with 2 digits
			maxStepsTwo = path[k]-zero;
			k++;
			direction = path[k];
			maxStepsTotal= ((maxStepsOne) * 10)+(maxStepsTwo);   //so that we can have two digits
			stepsTaken += traverseSegment(sr, sc, direction, maxStepsTotal);
			if (maxStepsTotal==traverseSegment(sr, sc, direction, maxStepsTotal)){
			k++;
			}
			else{ 
				nsteps=stepsTaken;
				return 2;
			}
		}
		else if (isalpha(path[k])){         //for numbers with 1 digit
			direction = path[k]; 
			maxStepsTotal = maxStepsOne-0;		
			stepsTaken += traverseSegment(sr, sc, direction, maxStepsTotal);
			if (maxStepsTotal==traverseSegment(sr, sc, direction, maxStepsTotal)){
			k++;
			}
			else{
				nsteps=stepsTaken;
				return 2;
			}
		}
		if(direction=='n'||direction=='N') //prepares the next starting position
			sr-= maxStepsTotal;
		if(direction=='s'||direction=='S')
			sr+= maxStepsTotal;
		if(direction=='e'||direction=='E')
			sc+= maxStepsTotal;
		if(direction=='w'||direction=='W')
			sc-= maxStepsTotal;
		maxStepsTotal=0;
	}}
	if (sr==er&&sc==ec){      //if starting point is the same as ending point
		nsteps=stepsTaken;
		return 0;}
	else{
		nsteps=stepsTaken;
		return 1;}
}

int main(){
setSize(20,20);
    	  setSize(4,5);
    	  
    	    
    	    
	    assert(isPathWellFormed("2n1e"));
	    assert(!isPathWellFormed("1e."));
	    assert(traverseSegment(3, 1, 'N', 2) == 2);
	    int len;
	    len = -999;  // so we can detect whether traversePath sets len
	    assert(traversePath(2,1, 2,2, "", len) == 1 && len == 0);
	    len = -999;  // so we can detect whether traversePath sets len
	    assert(traversePath(3,1, 3,4, "1ex", len) == 3  &&  len == -999);
	 
	}