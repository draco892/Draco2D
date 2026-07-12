#!/usr/bin/env bash
# gecko_surprise.sh - ASCII Art Esatta + Colore Fluido (Senza Righe Vuote)
# Compatibile: macOS Apple Silicon (Bash 3.2) | Zero glitch | Spazi preservati al 100%

trap 'clear; exit 0' INT TERM QUIT
clear

ROWS=(
"III       L      OOO  V   V EEEEE       Y   Y  OOO  U   U       M   M Y   Y        CCC  U   U TTTTT EEEEE        GGG  EEEEE  CCC  K   K  OOO            33333 "
" I        L     O   O V   V E            Y Y  O   O U   U       MM MM  Y Y        C   C U   U   T   E           G     E     C   C K  K  O   O         <    3  "
" I        L     O   O V   V EEEE          Y   O   O U   U       M M M   Y         C     U   U   T   EEEE        G GG  EEEE  C     KKK   O   O        <    33  "
" I        L     O   O  V V  E             Y   O   O U   U       M   M   Y         C   C U   U   T   E           G   G E     C   C K  K  O   O         < 3   3 "
"III       LLLLL  OOO    V   EEEEE         Y    OOO   UUU        M   M   Y          CCC   UUU    T   EEEEE        GGG  EEEEE  CCC  K   K  OOO             333  "
)

while true; do
  # Genera colore RGB 24-bit casuale
  R=$((RANDOM % 256))
  G=$((RANDOM % 256))
  B=$((RANDOM % 256))

  for row in "${ROWS[@]}"; do
    # Stampa riga con colore e avanzamento a capo (NESSUN \n iniziale)
    printf "\033[38;2;%d;%d;%dm%s\033[0m\n" "$R" "$G" "$B" "$row"
  done

  sleep 1
done

