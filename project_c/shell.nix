let
  pkgs = import <nixpkgs> { };
  glib = pkgs.glib.overrideAttrs (old: {
    version = "2.68.0";

    src = pkgs.fetchurl {
      url = "mirror://gnome/sources/glib/2.68/glib-2.68.0.tar.xz";
      sha256 = "1sh3h6b734cxhdd1qlzvhxq6rc7k73dsisap5y3s419s9xc4ywv7";
    };

    patches = [];

    postInstall = ''
      moveToOutput "share/glib-2.0" "$dev"
    '';
  });
in
pkgs.mkShell {
  buildInputs = with pkgs; [ glib.dev glib pkg-config bear readline80.dev ];
}
