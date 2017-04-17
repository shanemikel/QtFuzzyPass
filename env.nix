{ nixpkgs ? import <nixpkgs> { } }:       
with nixpkgs;

stdenv.mkDerivation {
  name = "qt5-env";
  buildInputs = [ qt5.full ];
}
