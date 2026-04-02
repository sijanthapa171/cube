{
  description = "A simple C++ Raylib development shell";

  inputs = {
    nixpkgs.url = "github:NixOS/nixpkgs/nixos-unstable";
  };

  outputs = { self, nixpkgs }:
    let
      supportedSystems = [ "x86_64-linux" "aarch64-linux" "x86_64-darwin" "aarch64-darwin" ];
      forAllSystems = nixpkgs.lib.genAttrs supportedSystems;
      pkgs = forAllSystems (system: nixpkgs.legacyPackages.${system});
    in
    {
      devShells = forAllSystems (system: {
        default = pkgs.${system}.mkShell {
          nativeBuildInputs = with pkgs.${system}; [ 
            pkg-config 
            gnumake 
          ];
          buildInputs = with pkgs.${system}; [
            gcc
            raylib
          ];
        };
      });
    };
}
