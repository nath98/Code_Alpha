#include <iostream>
#include <math.h>

#define X 6 //taille matrice
#define Y 6

using namespace std;

void Astar(struct node start, struct node end);
void create_grid (char (*matrix)[Y], struct node (*grid)[Y]);
void add_openlist_around_node(struct node (*grid)[Y], struct node *openlist[X*Y], struct c_lists *C, struct node N,  struct Closedlist *closedlist);
void print_grid( struct node (*grid)[Y] );
void grid_H_calcul ( struct node (*grid)[Y], struct node end);

struct node {

	unsigned short x, y, C, H, F; //position x, y, cout à l'origine, cout Heuristique, cout total
	char state; //'o' 'c' 'f' 'b' -> open close free blocked
};

struct c_lists{//compteur openlist et closedlist
	unsigned short open, closed;
};

struct Closedlist{
	struct node *parent[X*Y];
	struct node *child[X*Y];
};
struct smaller_F{
	unsigned short i, v; //index value
};



int main() {

	struct node debut = {
			0, 0, 0, 0, 0, 'f'
	};

	struct node fin = {
			5, 5, 0, 0, 0, 'f'
	};

	Astar(debut, fin);

	return 0;
}


void Astar(struct node start, struct node end) {

	char matrix[X][Y] = {  'f', 'f' ,'f', 'f', 'f', 'f' ,'f', 'f', 'b', 'f', 'f' ,'f', 'b', 'b', 'f' ,'f','f', 'f' ,'f', 'b', 'f', 'f' ,'f', 'f', 'b', 'f', 'f' ,'f', 'b', 'b', 'f' ,'f','b','f','f','f'  };
	struct node grid[X][Y];
	struct node *openlist[X*Y];
	struct Closedlist closedlist;//*parents *enfants
	struct c_lists C = { //compteur openlist et closedlist
			 0,0
	};
	unsigned short openlist_stop=0, i;
	struct smaller_F S_M;

	create_grid(matrix, grid);

	grid[start.x][start.y] = start;
	grid[end.x][end.y] = end;

	print_grid(grid);

	openlist[C.open] = &grid[start.x][start.y];
	openlist[C.open]->state='o';
	C.open ++;

	grid_H_calcul(grid, end);

	std::cout<<std::endl;
	print_grid(grid);

	add_openlist_around_node(grid, openlist, &C, start, &closedlist);

	std::cout<<std::endl;
	print_grid(grid);

	S_M.i=0;
	S_M.v=65535;

	//std::cout << C.open;
	while(!openlist_stop){
		//std::cout<<openlist_stop;
		std::cout<<std::endl;
		std::cout << std::endl;
		print_grid(grid);
		//std::cout << C.open;

		//openlist_stop=1;
		for(i=0; i<C.open; i++)
		{

			if(openlist[i]->state=='o'){
				if((openlist[i]->x==end.x)&&(openlist[i]->y==end.y)){
					openlist_stop=1;
					cout << "SEMAPHORE";

				}
				else{
					if(openlist[i]->F<=S_M.v){
						S_M.v = openlist[i]->F;
						S_M.i = i;
						//cout<<C.open ;

					}
				}
			}
		}
		add_openlist_around_node(grid, openlist, &C, *openlist[S_M.i], &closedlist);
		cout << "NON";


	}
	cout << "fin" ;





}

void create_grid (char (*matrix)[Y], struct node (*grid)[Y]) { //matrix[X][Y] grid[X][Y]

	unsigned short i, y;

	for (i=0; i<X; i++){

		for (y=0; y<Y; y++){

			grid[i][y].x=i;
			grid[i][y].y=y;
			grid[i][y].state = matrix[i][y];



		}
	}

}

void add_openlist_around_node(struct node (*grid)[Y], struct node *openlist[X*Y], struct c_lists *C, struct node N, struct Closedlist *closedlist){

	signed short i, y;

	//std::cout << openlist[c_lists[0]]->x;
	for (i=-1; i<=1; i++){
		for (y=-1; y<=1; y++)
		{
			if( //Dont exceed the grid
				(grid[N.x+i][N.y+y].x>=0) //Dont exceed in left
				&& (grid[N.x+i][N.y+y].y>=0) //Dont exceed in top
				&& (grid[N.x+i][N.y+y].x<X) //Dont exceed in right
				&& (grid[N.x+i][N.y+y].y<Y) ) //Dont exceed in bottom
			{
				if( // != Of the initial node
					(grid[N.x+i][N.y+y].x!=N.x)
					|| (grid[N.x+i][N.y+y].y!=N.y) )
					{
						if(grid[N.x+i][N.y+y].state=='f'){// if the node tested is free

							openlist[C->open]=&grid[N.x+i][N.y+y];
							openlist[C->open]->state='o';
							openlist[C->open]->C=N.C+1;
							openlist[C->open]->F=openlist[C->open]->C + openlist[C->open]->H;

							C->open = C->open+1;
						}

					}
			}

		}
	}
	closedlist->child[C->closed]=&grid[N.x][N.y];//Add N to the closed list
	closedlist->child[C->closed]->state='c';
	C->closed++;
}

void print_grid( struct node (*grid)[Y] ){
	unsigned short i,y;

	for (i=0; i<X; i++){
		for(y=0; y<Y; y++){
			std::cout<<grid[i][y].state<<" ";
			/*if(grid[i][y].state == 'o'){
				std::cout<<"("<<grid[i][y].F<<") ";
			}*/

		}
		std::cout<<std::endl;

	}
}

void grid_H_calcul ( struct node (*grid)[Y], struct node end){
	unsigned short i, y;
	for (i=0; i<X; i++){
		for(y=0; y<Y; y++){
			grid[i][y].H = hypot(grid[i][y].x-end.x,grid[i][y].y-end.y);
		}
	}
}
