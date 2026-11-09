#!/usr/bin/env bash
# Development-only helper: build source archives for thirdparty downloads from git tags, for networks where
# GitHub archive downloads are blocked but `git clone` works. Usage:
#   utils/fetch-git-archives.sh OUTDIR URL...      # URLs as found in thirdparty/*/CMakeLists.txt
#   export KO_LOCAL_ARCHIVES=OUTDIR                # then run the normal build
# NOTE: archives are made from the git tag (not the release tarball), and are not checksum-verified by the build.
set -euo pipefail
out="$1"; shift
mkdir -p "$out"
for url in "$@"; do
    file="${url##*/}"
    [ -f "$out/$file" ] && continue
    if [[ "$url" =~ ^https://github.com/([^/]+)/([^/]+)/(archive/refs/tags|archive|releases/download)/([^/]+)(/.*)?$ ]]; then
        owner="${BASH_REMATCH[1]}"; repo="${BASH_REMATCH[2]}"; kind="${BASH_REMATCH[3]}"; ref="${BASH_REMATCH[4]}"
        if [ "$kind" = "releases/download" ]; then ref="${ref}"; fi
    else
        echo "skip (unsupported url): $url" >&2; continue
    fi
    ref="${ref%.tar.gz}"
    tmp="$(mktemp -d)"
    echo "== $owner/$repo @ $ref"
    if git clone -q --depth 1 --branch "$ref" "https://github.com/$owner/$repo" "$tmp/src" 2>/dev/null \
       || git clone -q --depth 1 --branch "v$ref" "https://github.com/$owner/$repo" "$tmp/src" 2>/dev/null; then
        :
    else
        git clone -q "https://github.com/$owner/$repo" "$tmp/src"
        git -C "$tmp/src" checkout -q "$ref"
    fi
    git -C "$tmp/src" submodule update --init --depth 1 -q 2>/dev/null || true
    # Include submodules, in a GitHub-like top directory.
    top="${repo}-${ref}"
    mv "$tmp/src" "$tmp/$top"; rm -rf "$tmp/$top/.git"
    tar -C "$tmp" -czf "$out/$file" "$top"
    rm -rf "$tmp"
done
