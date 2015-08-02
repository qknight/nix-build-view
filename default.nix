with import <nixpkgs> {};

stdenv.mkDerivation rec {
  name = "nix-build-view";

  src = fetchgit {
    url     = "https://github.com/qknight/${name}";
    rev     = "311110e59e185eb1015dcfd34b30f31a862503bc";
    sha256  = "10wqq9jh1vc83grnmi1ds130i5w8665zm1fg84bncbik03farnch";
  };

  buildInputs = [ ncurses cmake ];

  configurePhase ="";
  buildPhase = ''
    mkdir -p ${name}/build
    cd ${name}/build
    cmake .. && make
  '';

  installPhase = "mkdir -p $out/bin && mv nix-build-view $out/bin/.";

  meta = {
    description = "A monitor for nix-build";
    homepage = "http://blog.lastlog.de/posts/nix-build-view_using_ncurses/";
  };
}
