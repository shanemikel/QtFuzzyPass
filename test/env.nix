{ nixpkgs ? import <nixpkgs> {}, compiler ? "clang" }:       
with nixpkgs;

let
  dCompiler = builtins.getAttr compiler nixpkgs;
  stdenv = nixpkgs.overrideCC nixpkgs.stdenv dCompiler;
in stdenv.mkDerivation {
  name = "cc-env";
  buildInputs = [ ];
}
