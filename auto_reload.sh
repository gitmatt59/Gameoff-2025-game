#!/usr/bin/env bash
printf '%s\n' src/main.cpp | entr -r sh -c 'cmake --build build && exec ./build/endoparasitic_clone'

