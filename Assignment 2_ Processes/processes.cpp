#include "tinbes.h"

#define TABLE_SIZE 25
#define RUNNING 'r'
#define PAUSED 'p'

string processName[TABLE_SIZE];
int id[TABLE_SIZE];
char state[TABLE_SIZE];
long addr[TABLE_SIZE];
int noOfProcesses = 0;
int idCounter = 0;

int newProcess(string name, long address) {
  for(int i = 0; i < processName.size(); i++){ //loop through array
    // Check if process name and/or address isn't in use yet.
    if(name == processName[i] || address == addr[i]){
      cout << "Address or name already in use"
      return -1;
    }
  }
  // Create process
  id[i] = idCounter;
  processName[i] = name;
  addr[i] = address;
  noOfProcesses++;
  return idCounter++;
}

void removeProcess(int i) {
  if(id[i] != NULL){ //if process exists
    id[i] = NULL;
    state[i] = NULL;
    addr[i] = NULL;
    cout << "Process " << i << "Sucesfully removed";
  }
  else{ //Print error message
    cout << "Process" << i << "doesn't exist";
    return;
  }
  for (int j = i; j < noOfProcesses; j++) { //Move back all after i by one spot
    id[j] = id[j+1];
    state[j] = state[j+1];
    addr[j] = state[j+1];
  }
    idCounter--;
    noOfProcesses--;
}

void executeProcesses() {
  long newAddr;
  for (int i = 0; i < noOfProcesses; i++) {
    if (state[i] == RUNNING) {

      // TO DO

      if (newAddr == 0) {
        cout << "Process \"" << processName[i] << "\" has terminated." << endl;
        removeProcess(i--);
      } else {
        addr[i] = newAddr;
      }
    }
  }
}

void listProcesses() {
  for (int i = 0; i < noOfProcesses; i++) {
    cout << id[i] << ' ' << processName[i] << ' ' << state[i] << endl;
  }
}

int findProcess(int i) {
  for (int j = 0; j < noOfProcesses; j++) {

    // TO DO

  }
  return -1;
}

void suspendProcess(int i) {
  int j = findProcess(i);
  if (j == -1) {
    cout << "Process does not exist." << endl;
    return;
  }
  if (state[j] == PAUSED) {
    cout << "Process already paused." << endl;
  }
  else {

    // TO DO

  }
}

void resumeProcess(int i) {
  int j = findProcess(i);
  if (j == -1) {
    cout << "Process does not exist." << endl;
    return;
  }
  if (state[j] == RUNNING) {
    cout << "Process already running." << endl;
  }
  else {

    // TO DO

  }
}

void killProcess(int i) {
  int j = findProcess(i);
  if (j == -1) {
    cout << "Process does not exist." << endl;
  } else {

    // TO DO

  }
}

int main() {
  unblockCin();
  string command;
  while (true) {
    if (charactersAvailable()) {
      command = readLine();
      if (command == "RUN") {
        string name = readLine();
        long address = stoi(readLine());
        cout << newProcess(name, address) << endl;
      }
      if (command == "LIST") {
        listProcesses();
      }
      if (command == "SUSPEND") {
        int i = stoi(readLine());
        suspendProcess(i);
      }
      if (command == "RESUME") {
        int i = stoi(readLine());
        resumeProcess(i)
      }
      if (command == "KILL") {
        int i = stoi(readLine());
        killProcess(i)
      }
    }
    else {
      executeProcesses();
    }
  }
}
