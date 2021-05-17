let
  pkgs = import <nixpkgs> { };
in
pkgs.mkShell {
  buildInputs = with pkgs; [ glib.dev glib pkg-config bear readline80.dev ];
}
