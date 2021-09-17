#include "processmanager.h"

#include <cstring>
#include <fstream>
#include <iostream>
#include <regex>
#include <stdexcept>
#include <stdio.h>
#include <string>
#include <optional>

using namespace std;

#define debug(x, ...) cout << #x << ": " << x << "\n";
#define debugLabel(x, label) cout << label << ": " << x << "\n";
#define dl(x, label) debugLabel(x, label)

int main() {

  ProcessManager p;

  // string processName = "native_client";

  // int pid = p.getProcessId("native_client");

  // cout << "found pid of " << processName << ": " << pid << "\n";

  // long ammoAddress = 0x11338c8;

  // int ammo = p.readIntegerFromMemory(pid, ammoAddress);

  // cout << "found ammo to be: " << ammo << endl;

  // read maps file
  // ifstream mapsFile(string("/proc/") + to_string(pid) + "/maps");



  // Module firstModuleInMapsFile = p.readEntireModuleFromMapsFile(pid);

  // cout << firstModuleInMapsFile << endl;




  // long addr;


  // cin >> std::hex >> addr;

  // cout << addr;


  int val = p.readIntegerFromMemory(8084, 0x9f360);

  cout << val << endl;




  // Module module = p.readEntireModuleFromMapsFile(pid, );


}