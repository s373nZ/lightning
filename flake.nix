{
  inputs = {
    nixpkgs.url = "github:NixOS/nixpkgs";
  };

  outputs = { self, nixpkgs, flake-utils }: {
    devShell.x86_64-linux =
      with import nixpkgs { system = "x86_64-linux"; };
      mkShell {
        #name = "clightning";
        #src = self;
        packages = [
          autoreconfHook
          gawk
          gettext
          libz
          postgresql.lib
          protobuf
          python39Packages.mako
          sqlite
        ];
        # TODO: This doesn't seem to be working. Installing Python packages is a pain: https://discourse.nixos.org/t/why-is-it-so-hard-to-use-a-python-package/19200/9
        shellHook = ''
          poetry install --no-root
        '';
      };
  
  };
}
