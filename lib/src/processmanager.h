#ifndef PROCESSMANAGER_H
#define PROCESSMANAGER_H

#include <fstream>

struct Device
{
    int major;
    int minor;
};

struct MapsFileLine
{
    void* addressStart;
    void* addressEnd;
    char perms[5]; // 'rw-p\0'
    long offset;
    Device device;
    int inode;
    std::string pathName;


    friend std::ostream& operator<<(std::ostream& os, MapsFileLine& rhs){
        os << "----------Information about a Module struct: ---------\n";
        os << "address start: " << std::hex << rhs.addressStart << "\n";
        os << "address end: " << std::hex << rhs.addressEnd << "\n";
        return os;
    }

};

// A module contains the same information as an individual line in maps file
// but a module will have the start address be the first line of maps file line
// and the end address will be the end address of the last entry which has the same name as the first line
typedef MapsFileLine Module; 

class ProcessManager
{
public:
    ProcessManager();

    int getProcessId(std::string processName);
    int readIntegerFromMemory(int pid, long address);

    MapsFileLine readMapsFileLine(std::ifstream &mapsFile);

    MapsFileLine readEntireModuleFromMapsFile(int pid);
};

#endif // PROCESSMANAGER_H
