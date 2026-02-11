#include <iostream> 
#include <limits> 
using namespace std; 

const int W = 10, H = 10; 

void waitForEnter() 
{ 
	cout << "Press Enter for next phase"<< endl; 
	cin.ignore(numeric_limits<streamsize>::max(), '\n'); 
} 

int checkNeighbors(bool g[H][W], int x, int y) 
{ 
	int n = 0; for (int dy = -1; dy <= 1; dy++) 
	{
		for (int dx = -1; dx <= 1; dx++) 
		{ 
			if (dx == 0 && dy == 0) continue; 
			
			int nx = x + dx, ny = y + dy; 
			
			if (nx >= 0 && nx < W && ny >= 0 && ny < H) n += g[ny][nx]; 
		} 
	} 
	
	return n; 
} 

void step(bool g[H][W]) 

{ 
	bool next[H][W] = {}; 
	for (int y = 0; y < H; y++) 
	{ 
		for (int x = 0; x < W; x++) 
		{
			int n = checkNeighbors(g, x, y); 
			bool alive = g[y][x]; next[y][x] = alive ? (n == 2 || n == 3) : (n == 3); 
		} 
	} 
	
	for (int y = 0; y < H; y++) for (int x = 0; x < W; x++) g[y][x] = next[y][x]; 

} 

void render(bool g[H][W]) 

{ 
	
	for (int y = 0; y < H; y++) 
	
	{ 
		
		for (int x = 0; x < W; x++) cout << (g[y][x] ? '8' : '.'); 
		cout << endl; 
	}
} 

bool isExtinct(bool g[H][W]) 

{ for (int y = 0; y < H; y++) 
	for (int x = 0; x < W; x++) 
		if (g[y][x] == true) return false; 
return true; 
} 

bool isStill(bool a[H][W], bool b[H][W]) 

{ 
	for (int y = 0; y < H; y++) 
		for (int x = 0; x < W; x++) 
			if (a[y][x] != b[y][x]) return false; 
	return true; 
} 

int main() 

{ 
	bool grid[H][W] = {}; grid[1][2] = 1; grid[2][3] = 1; grid[3][1] = 1; grid[3][2] = 1; grid[3][3] = 1; 
	for (int i = 0; i < 50; i++) 
	{ 
		cout << "\nPhase " << i << "\n"; render(grid); waitForEnter(); 
		
		bool prev[H][W]; 
		for (int y = 0; y < H; y++) 
			for (int x = 0; x < W; x++) prev[y][x] = grid[y][x]; 
		
		step(grid); 
		if (isExtinct(grid)) 
		{ 
			cout << "Extinction reached: all cells are dead." << endl; break; 
		} 
		
		if (isStill(prev, grid)) 
		
		{ 
			cout << "Still life reached: pattern no longer changes" << endl; break; 
		} 
	} 
}
