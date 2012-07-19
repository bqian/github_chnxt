#include <iostream>
#include <fstream>
#include <string>

#include "configFile.h"

using namespace std;

ConfigFile::ConfigFile()
{
  _numEntries = 0;
}

ConfigFile::~ConfigFile()
{
}

int ConfigFile::read(const char* path)
{
  string line;
  ifstream file (path);
  _path = strdup(path);
  if(file.is_open())
  {
    while(file.good()) {
      getline(file, line);
      if(line.size() != 17) {
        continue;
      }
      /* Copy the line into the list of entries */
      _addresses[_numEntries] = strdup(line.c_str());
      _numEntries++;
    }
    file.close();
  } else {
    return -1;
  }
  return 0; 
}

int ConfigFile::numEntries()
{
  return _numEntries;
}

int ConfigFile::addEntry(const char* entry)
{
  /* Move all the entries up one */
  for(int i = (_numEntries-1); i >= 0; i--) {
    _addresses[i+1] = _addresses[i];
  }
  _addresses[0] = strdup(entry);
  _numEntries++;
  return 0;
}

int ConfigFile::moveEntryDown(int index)
{
  if(index < 0) {
    return -1;
  }
  if(index >= (_numEntries-1)) {
    return -1;
  }
  /* Swap with entry belo */
  char *tmp;
  tmp = _addresses[index+1];
  _addresses[index+1] = _addresses[index];
  _addresses[index] = tmp;
  return 0;
}

int ConfigFile::moveEntryUp(int index)
{
  if(index <= 0) {
    return -1;
  }
  if(index >= _numEntries) {
    return -1;
  }
  /* Just swap the data of this entry with the one above it */
  char* tmp;
  tmp = _addresses[index-1];
  _addresses[index-1] = _addresses[index];
  _addresses[index] = tmp;
  return 0;  
}

const char* ConfigFile::getEntry(int index)
{
  if(index >= _numEntries) {
    return NULL;
  }
  return _addresses[index];
}

int ConfigFile::remove(int index)
{
  if(index >= _numEntries) {
    return -1;
  }
  if(index < 0) {
    return -1;
  }
  free(_addresses[index]);
  for(int i = index+1; i < _numEntries; i++) {
    _addresses[i-1] = _addresses[i];
  }
  _numEntries--;
}

int ConfigFile::write()
{
  ofstream file;
  file.open(_path);
  for(int i = 0; i < _numEntries; i++) {
    file << _addresses[i] << endl;
  }
  file.close();
  return 0;
}
