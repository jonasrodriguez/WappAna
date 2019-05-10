#include "Types.h"
#include <map>
#include <regex>
#include <vector>

class ProcessFile {
public:
  ProcessFile(std::string);

private:
  void ProcessLine(const std::string &line, const int &idx);
  void ProcessName(wapp::Chat &chat, const std::string &);
  void StoreName(const std::string &name);
  bool StoreDate(wapp::Chat &chat, const std::smatch &);
  void GenerateResults();
  void ShowProgress(const int &);

private:
  long count_;
  int progress_;
  std::map<std::string, int> names_;
  std::vector<wapp::Chat> chats_;
};
