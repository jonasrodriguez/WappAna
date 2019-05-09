#include "ProcessFile.h"
#include <fstream>
#include <iostream>
#include <regex>

ProcessFile::ProcessFile(std::string file) {
  int lineCount = 0;
  std::ifstream infile;
  infile.open(file);
  std::string line;
  while (std::getline(infile, line)) {
    ProcessLine(line);
    lineCount++;
  }
  infile.close();

  for (auto n : names_) {
    std::cout << n.first << " " << n.second << std::endl;
  }
  std::cout << "c: " << lineCount << std::endl;
}

void ProcessFile::ProcessLine(const std::string &line) {
  std::string dateTime;
  std::string name;
  std::string text;

  size_t datePos = line.find_first_of("-");
  dateTime = line.substr(0, datePos);

  size_t namePos = line.find_first_of(":", datePos);
  if (datePos >= namePos) {
    std::cout << line << std::endl;
    return;
  }
  name = line.substr(datePos, namePos);
  //  std::cout << dateTime << "-" << name << std::endl;

  //  // Use regex to split date&time - user - message
  //  std::regex re("^(.*\\-)([^:]*)(.*)");
  //  std::smatch match;
  //  if (std::regex_search(line, match, re) && match.size() > 1) {
  //    dateTime = match.str(0);
  //    name = match.str(1);
  //    text = match.str(2);
  //  }

  //  StoreName(name);
}

void ProcessFile::StoreName(const std::string &name) {
  std::map<std::string, int>::iterator it;
  it = names_.find(name);
  if (it != names_.end()) {
    it->second++;
  } else {
    names_.insert(std::pair<std::string, int>(name, 1));
  }
}
