FROM nixos/nix

RUN nix-channel --update

RUN git clone https://github.com/ElementsProject/lightning.git /lightning
COPY flake.nix /lightning/flake.nix

WORKDIR /lightning
RUN git add flake.nix

RUN nix develop --extra-experimental-features nix-command --extra-experimental-features flakes --configure
RUN nix develop --extra-experimental-features nix-command --extra-experimental-features flakes --build
