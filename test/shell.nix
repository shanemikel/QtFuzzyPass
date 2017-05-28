{ nixpkgs ? import <nixpkgs> { }
, environment ? ./env.nix
}:
with builtins;

let
  extraBuildInputs = with nixpkgs.pkgs; [
    nettools
  ];
  overrideDerivation = d:
    nixpkgs.lib.overrideDerivation d (p: {
      shellHook = appendShellHook p ''
        export PS1=' '
        . ~/.nixpkgs/shellrc
      '';
      buildInputs = p.buildInputs ++ extraBuildInputs;
    });
  appendShellHook = p: s:
    if hasAttr "shellHook" p then p.shellHook + "\n" + s else s;
  getEnv = file:
    import file { inherit nixpkgs; };
in

overrideDerivation (getEnv environment)
