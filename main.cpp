#include <cstdio>
#include <iomanip>
#include <iostream>
#include <string>
#include <math.h>
using namespace std;


// 2d array of drone coordinates 
const int drone_locations[8][2] = 
	{{2,2}, // drone #1
	 {2,5}, // drone #2
	 {2,8}, // drone #3
	 {5,2}, // drone #4
	 {5,8}, // drone #5
	 {8,2}, // drone #6
	 {8,5}, // drone #7
	 {8,8} // drone #8
	};

/* 
	Input: a row and column
	Output: integer of the drone's in that position if found
			if not, return -1
*/
int is_drone(int row, int col){
	int i;
	// Iterate over the array of drone positions
	for (i = 0; i<8; i++){
		// Return drone number if matches with 1 based index
		if (drone_locations[i][0] == row && drone_locations[i][1] == col) return i + 1;
	}
	// Else
	return -1;
}

/* 
	Input: destination row and column, drone row and column
	Output: float of the total distance traveled by the drone
*/
float calc_distance_travelled(int dl_row, int dl_col, int d_row, int d_col){

	// Math
	float dist_a = d_row - 5;
	dist_a = dist_a*dist_a;
	float temp = d_col - 5;
	temp = temp*temp;
	dist_a = sqrt(dist_a + temp);

	// Math
	float dist_b = 5 - dl_row;
	dist_b = dist_b*dist_b;
	temp = 5 - dl_col;
	temp = temp*temp;
	dist_b = sqrt(dist_b + temp);

	// Math
	float dist_c = dl_row - d_row;
	dist_c = dist_c*dist_c;
	temp = dl_col - d_col;
	temp = temp*temp;
	dist_c = sqrt(dist_c + temp);

	// Math
	return dist_a + dist_b + dist_c;
}

int main(){

	// Symbols for blockville
	char apartment = '*';
	char warehouse = 'W';
	
	string blockville[11][11];

	// Loop over entire blockville and populate with characters
	for(int row=0;row<11;row++){
		for(int col=0;col<11;col++){
			// Calls is_drone each time which is not efficient and should probably be moved
			int on_drone = is_drone(row, col);
			// If warehouse
			if (row==5 && col==5){
				blockville[row][col] = 'W';
			}
			// If is_drone found found a drone on that spot
			else if (on_drone != -1){
				// Reason for the 1-based index in is_drone
				blockville[row][col] = to_string(on_drone);
			}
			else {
				blockville[row][col] = '*';
			}
			
		}
	}
	// Compiler does splitting and parsing of input
	int input_row, input_col;
	cin >> input_row >> input_col;
	
	// Self explanatory
	if (input_row == 5 && input_col == 5){
		cout<<"Sorry, drones can't deliver TO the warehouse" << endl;
	}

	// If the inputted rows are within the bounds
	else if ((0<= input_row && input_row < 11) && (0<= input_col && input_col < 11)){
		int on_drone = is_drone(input_row, input_col);
		// If a drone is on the space
		if (on_drone != -1){
			// 1-based indexing again
			cout<<"Drone " << on_drone<< " will make the delivery" << endl;
		}
		else{
			// Starting at unreachable number so that next lowest distance will be less
			// Weird
			float lowest_dist = 100;
			int closest;
			// Calculate distance for each of the drones and get the lowest distance
			for (int drone_num = 0; drone_num<8; drone_num++){
				float dist = calc_distance_travelled(input_row, input_col, drone_locations[drone_num][0], drone_locations[drone_num][1]);
				if (dist < lowest_dist){
					lowest_dist = dist;
					closest = drone_num + 1;
				}
			}
			// Set the inputted coords to P
			blockville[input_row][input_col] = 'P';
			// Print the array
			for(int row=0;row<11;row++){
				// Make new line and append each character before printing and starting again
				string line;
				for(int col=0;col<11;col++){
					line += blockville[row][col];
					line += " ";
				}
				cout << line << "\n";
			}
			cout<<"Drone " << closest << " will make the delivery" << endl;
			cout << fixed << setprecision(2);
			cout<< "This drone traveled a distance of " << lowest_dist << " blocks" << endl;

		}
		// Will be called in both cases
		cout<<"Thank you for using our delivery services" << endl;

	} else{
		// If the inputted row/col are OOB
		cout<<"Sorry, illegal delivery location" << endl;
	}



	
	return 0;
}
