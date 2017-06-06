#!/bin/bash

git pull
git submodule update --init
git submodule foreach git stash
git submodule foreach git pull origin master

# I don't like this test since we use cpp14. ruin it.
rm -rf external/benchmark/test/cxx03_test.cc
cp cmake/fakedTests/cxx03_test.cc external/benchmark/test/cxx03_test.cc