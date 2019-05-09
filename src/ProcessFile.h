#include <map>
#include <string>

class ProcessFile {
public:
  ProcessFile(std::string);

private:
  void ProcessLine(const std::string &line);
  void StoreName(const std::string &name);

private:
  std::map<std::string, int> names_;
};
