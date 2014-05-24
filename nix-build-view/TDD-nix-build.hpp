#ifndef TDDnixbuild
#define TDDnixbuild

#include <vector>
#include <string>

class NixBuild {
public:
  NixBuild();
  void tick();
private:
  std::vector<std::string> m;
};

#endif