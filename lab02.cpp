 #include <iostream>
 #include <string>
 #include <vector>
 #include <stdio.h>

#define A 0 //macro definitions of the genes to simplify later code
#define T 1 //works off binary values of assigned ints
#define C 2
#define G 3

using namespace std;

void decompress(int size, int gene) {
  unsigned char gee = gene;
  int adj = 0;
  int readj = 6;
  unsigned char out;
  if (size >= 4) { //there are 4 compressed letters
    for (int i = 4; i > 0; i--) {
      out = gee << adj; //left shifts unsigned char over 0,2,4,6 for chars 1,2,3,4 respectively
      out >>= readj; //right shifts every char over 6 to 
      adj += 2; //adds 2 to the first left shift every iteration to allow me tto take the values of
                //every other binary position  
      if (out == 0){
	cout << 'A';
      } else if (out == 1) {
	cout << 'T';
      } else if (out == 2) {
	cout << 'C';
      }
      else cout << 'G'; //assigns letter value to appropriate binary number
    }
  }
  else if (size < 4) { //there are less than 4 compressed letters
    for (int i = 0; i < size; i++) {
      out = gee <<adj;
      out >>= readj;
      adj += 2;
      if (out == 0){
	cout << 'A';
      } else if (out == 1) {
	cout << 'T';
      } else if (out == 2) {
	cout << 'C';
      }
      else cout << 'G';
    }
  }
}

void compress(char gene[]) {
  string str = gene;
  int x = str.length();
  int j;
  if ((x%4) != 0) {
    j = ((x/4)+2);
  } else (j=(x/4)+1); //j defines the number of unsigned chars needed

  vector<unsigned char> store; //generic vector to store unsigned chars in
  store.assign(j,0);

  for (int i = 0, k = 1; k < j; i++) {
    if ((i%4)==0 && (i != 0)) { //makes the method repeat every 4 characters
      k++;
    } if (str[i] == 'C') { //if-loop checking case of gene string char by char
      store[k] |= C;
    } else if (str[i] == 'T') {
      store[k] |= T;
    } else if (str[i] == 'G') {
      store[k] |= G;
    } else {
      store[k] |= A; //generic case A to work for letter A and as a buffer for 0
    } if ((i+1)%4 != 0) { //stops the function from left-shifting the fourth char and multiples of 4 in the gene string
      store[k] <<= 2;
    }
  }
  cout << x << " ";
  for (int p=1; p<j; p++) { //prints the compressed numbers
    printf("%d ",store[p]);
  }
  cout << endl;
}

int main(int argc, char* argv[]) {
  for (int i = 0; i < argc; ++i); //basic command line arg
  string str = argv[1];
  
  if (str == "-c") { //calls the method to compress
    compress(argv[2]); 
  }
  
  else if (str == "-d") { //calls the method to decompress
    int j = 3;
    int size = atoi(argv[2]); //converts first argument after -d to an integer representing the string size
    cout << size << " ";
    while (argv[j] != NULL) { //checks to see if there is a command line argument
      int gene = atoi(argv[j]); //converts command line arguments after initial size to integer
      decompress(size,gene);
      j++;
      size -= 4; //subtracts 4 from size for every processed integer allowing the last integer
                 //to have an accurate size in the decompress function
    }
    cout << endl;
  }
}
