#!/usr/bin/env python3
# Kacper Walasek
import os

if __name__ == "__main__":
    for root, dirs, files in os.walk("./src", topdown=False):
        for name in files:
            if os.path.splitext(name)[1] == '.cpp':
                print(os.path.join(root, name)[2:])
