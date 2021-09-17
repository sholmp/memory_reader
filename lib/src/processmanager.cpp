#include "processmanager.h"
#include <fstream>
#include <iostream>
#include <regex>
#include <string>

#include <dirent.h>
#include <sys/uio.h>

using namespace std;

ProcessManager::ProcessManager()
{
}

int ProcessManager::getProcessId(std::string processName)
{
    string procDirPath = "/proc/";
    DIR* dir = opendir(procDirPath.c_str());

    dirent* directoryEntry;
    regex r(processName);
    smatch matches;
    while((directoryEntry = readdir(dir)) != NULL)
    {
        ifstream file(procDirPath + directoryEntry->d_name + "/cmdline");
        if(file)
        {
            string line;
            getline(file, line);


            if(regex_search(line, matches, r))
            {
                int pid = atoi(directoryEntry->d_name);
                cout << processName.c_str() << "has pid " << pid;
                return pid;
            }
        }

    }

    return -1;
}

int ProcessManager::readIntegerFromMemory(int pid, long address)
{
    int readMemory = -1;
    iovec local;
    local.iov_base = &readMemory;
    local.iov_len = sizeof(int);

    iovec remote;
    remote.iov_base = (int*)address;
    remote.iov_len = sizeof(int) * 2;

    int bytesRead = process_vm_readv(pid, &local, 1, &remote, 1, 0);
    if(bytesRead != sizeof(int))
    {
        perror("process_vm_readv");
        return -1;
    }

    return readMemory;
}

MapsFileLine ProcessManager::readMapsFileLine(ifstream &mapsFile) {
  static regex r(
      R"(([\da-f]+)-([\da-f]+) ([rwxp-]+) ([\da-f]+) ((\d+):(\d+)) (\d+)\s+([\/\w_]*))");
  smatch matches;
  string line;
  getline(mapsFile, line);
  MapsFileLine mapsLine;
  if (regex_match(line, matches, r)) {
    cout << "------------------" << endl;

    for (int j = 0; j < matches.size(); j++) {
      cout << matches[j] << endl;
    }
    if (matches.size() > 0) {
      // Parse data into Module struct
      try {
        mapsLine.addressStart = (void *)stol(matches[1].str(), nullptr, 16);
        mapsLine.addressEnd = (void *)stol(matches[2].str(), nullptr, 16);
        strncpy(mapsLine.perms, matches[3].str().c_str(), 5);
        mapsLine.offset = stol(matches[4].str(), nullptr, 16);
        mapsLine.device.major = stoi(matches[5].str());
        mapsLine.device.minor = stoi(matches[6].str());
        mapsLine.inode = stoi(matches[7].str());
        mapsLine.pathName = matches[8].str();
      } catch (std::invalid_argument e) {
        cout << e.what() << endl;
        exit(-1);
      }
    }
  }
  return mapsLine;
}

MapsFileLine ProcessManager::readEntireModuleFromMapsFile(int pid)
{
  ifstream mapsFile(string("/proc/") + to_string(pid) + "/maps");

  vector<MapsFileLine> lines;
  MapsFileLine firstLine = readMapsFileLine(mapsFile);
  lines.push_back(firstLine);

  for(;;)
  {
    MapsFileLine line = readMapsFileLine(mapsFile);
    if(line.pathName == firstLine.pathName)
      lines.push_back(line);
    else
     break;
  }

  // A module is simply the contiguous memory of each line in maps file
  // which has the same module name
  Module module = firstLine;
  module.addressEnd = lines.back().addressEnd;
  cout << "got " << lines.size() << " lines" << endl;

  return module;
}
