#ifndef TDDnixbuild
#define TDDnixbuild

#include <vector>
#include <string>

/*
 * emulate nix-build to make usability better without having to integrate
 * nix-build-view into nix-build first
 * this helps to make performance tests as well...
 */
class NixBuild {

public:

    NixBuild();
    void tick();

private:

    std::vector<std::string> m;
    long millis_old = 0;
    std::vector<std::string> m_fetch;
    std::vector<std::string> m_build;

};

#endif // TDDnixbuild
