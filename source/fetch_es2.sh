#!/usr/bin/env sh
set -eu
target="$(CDPATH= cd -- "$(dirname -- "$0")" && pwd)/upstream"
if [ -e "$target" ]; then
  echo "source/upstream already exists; refusing to merge." >&2
  exit 2
fi
git clone --recurse-submodules https://github.com/taedlar/es2_mudlib.git "$target"
