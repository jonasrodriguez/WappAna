#include <fstream>
#include <iostream>
#include <regex>
#include <sstream>
#include <string>

using namespace std;

void ProcessLine(const std::string &line) {

  std::string dateTime;
  std::string name;
  std::string text;

  // Use regex to split date&time - user - message
  std::regex re("(.*)\\-(.*)\\:(.*)");
  std::smatch match;
  if (std::regex_search(line, match, re) && match.size() > 1) {
    dateTime = match.str(1);
    name = match.str(2);
    text = match.str(3);
  }

  std::cout << name << std::endl;
}

int main() {
  ifstream infile;
  infile.open("chat.txt");

  std::string line;
  while (std::getline(infile, line)) {
    std::istringstream iss(line);
  }

  infile.close();
  return 0;
}
