#include <stdlib.h>
#include <string>
#include <iostream>
#include <wiringPi.h>
#include <fstream>

#define OUTPUT_PIN 0
#define INPUT_PIN 2

using namespace std;

char decodeMorse(string s) {
  const string morse("EISHVUF*ARL*WPJTNDBXKCYMGZQO");
  int p = -1;
  for (int i = 0; i < s.length(); i++) {
    if (s[i] == '-') p += 1 << (4 - i);
    else p++;
  }
  return morse[p];
}

void wait(int n) {
  delay(100 * n);
}

void dot() {
  digitalWrite(OUTPUT_PIN, HIGH);
  wait(1);
  digitalWrite(OUTPUT_PIN, LOW);
  wait(1);

}

void dash() {
  digitalWrite(OUTPUT_PIN, HIGH);
  wait(3);
  digitalWrite(OUTPUT_PIN, LOW);
  wait(1);

}
//Open a text file which contains the morse codes
string sendMorse(char character) {
  string characterInMorse;
  string line;
  freopen("morse.txt", "r", stdin);

  while(getline(cin, line)){   //Searches for line which contains the given character
       if(line.at(0) == character){
         cout << line;
         break;
       }
  }

  for(int index = 1; index < line.length(); index = index + 1){ //Checks every symbol on the selected line for dashes and dots.
    if(line.at(index) == '.'){
      dot();
      characterInMorse += '.';
    }
    else if(line.at(index == '-')){
      dash();
      characterInMorse += '-';
    }
  }
  wait(2); // wait 1 + 2 = 3 dots in total
  characterInMorse += " "; //space between characters for translation to ASCII
  return characterInMorse;
}

int main() {

  wiringPiSetup() ;
  pullUpDnControl(INPUT_PIN, PUD_UP);
  pinMode (OUTPUT_PIN, OUTPUT);
  wiringPiISR(INPUT_PIN, INT_EDGE_BOTH, &switchChanged);

  cout << "ASCII to morse code" << endl;
  cout << "Please enter a sentence" << endl;
  string input;
  string output;
  getline(cin, input);

  for(int i = 0; i < input.length(); i = i + 1){
    if(input.at(i) == ' '){
      output += " ";
      wait(7);
    }
    else output.append(sendMorse(input.at(i)));
  }
  cout << "Output " + output;
}
