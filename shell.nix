/*
    Nix shell file to import everything needed to build this project.
    This file is used as a default when running nix-shell.
*/

{ pkgs ? import <nixpkgs> {} }:
with pkgs;

stdenv.mkDerivation {
    name = "build-env";
    buildInputs = [
        catch2
        clang-tools
        clang
        cmake
        gcc
        ninja
    ];
}
