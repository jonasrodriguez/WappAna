#include "ProcessFile.h"
#include <fstream>
#include <iomanip>
#include <iostream>

ProcessFile::ProcessFile(std::string file) : count_(0), progress_(-1) {
  std::ifstream infile;
  infile.open(file);

  // Count line numbers
  count_ = std::count(std::istreambuf_iterator<char>(infile),
                      std::istreambuf_iterator<char>(), '\n');

  // Reset file
  infile.clear();
  infile.seekg(0, std::ios::beg);

  int idx = 0;
  std::string line;
  while (std::getline(infile, line)) {
    idx++;
    ProcessLine(line, idx);
  }
  infile.close();
  GenerateResults();
}

void ProcessFile::ProcessLine(const std::string &line, const int &idx) {
  // Use regex to check if starts with a date:
  std::regex da("^([\\d]*)(?:\\/)(\\d*)(?:\\/)(\\d*).(\\d*)(?:\\:)(\\d*)");
  std::smatch datem;
  if (std::regex_search(line, datem, da) && datem.size() > 1) {
    wapp::Chat chat;
    if (!StoreDate(chat, datem)) {
      std::cout << "Error!" << std::endl;
      return;
    }
    ProcessName(chat, datem.suffix());
    chat.lineCount = 1;
    chats_.push_back(chat);
  } else {
    chats_.back().text.append(line);
    chats_.back().lineCount++;
  }

  // Update progress
  ShowProgress(idx);
}

void ProcessFile::ProcessName(wapp::Chat &chat, const std::string &suffix) {
  std::regex na("^(?:.\\-*)(?:.)(.\\w*)");
  std::smatch namem;
  if (std::regex_search(suffix, namem, na) && namem.size() > 1) {
    StoreName(namem.str(1));
    chat.user = namem.str(1);
    chat.text = namem.suffix();
  }
}

bool ProcessFile::StoreDate(wapp::Chat &chat, const std::smatch &match) {
  try {
    chat.timeDate.tm_mday = std::stoi(match.str(1));
    // Month stored like 0 a 11
    chat.timeDate.tm_mon = std::stoi(match.str(2)) - 1;
    chat.timeDate.tm_year = std::stoi(match.str(3));
    chat.timeDate.tm_hour = std::stoi(match.str(4));
    chat.timeDate.tm_min = std::stoi(match.str(5));
    return true;

  } catch (...) {
    return false;
  }
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

void ProcessFile::ShowProgress(const int &idx) {
  int per = (idx * 10) / count_;
  if (per == progress_) {
    return;
  }

  progress_ = per;
  std::cout << "[";
  for (int i = 0; i < 10; i++) {
    if (i == progress_) {
      std::cout << ">";
    } else if (i < progress_) {
      std::cout << "#";
    } else {
      std::cout << " ";
    }
  }
  std::cout << "]" << std::endl;
}

void ProcessFile::GenerateResults() {
  int multLines = 0;
  for (auto n : names_) {
    std::cout << n.first << " " << n.second << std::endl;
  }
  std::cout << "Total Lines: " << count_ << std::endl;
  std::cout << "Total Messages: " << chats_.size() << std::endl;
  std::cout << "multLines: " << multLines << std::endl;

  std::ofstream outfile;
  outfile.open("outfile.txt");
  for (auto c : chats_) {
    if (c.lineCount > 1) {
      multLines++;
    }

    outfile << c.user << " - " << std::put_time(&c.timeDate, "%d/%m/%y %H:%M")
            << std::endl;
    outfile << c.text << std::endl;
    outfile << "----------------------------------" << std::endl;
  }
  outfile.close();
}
