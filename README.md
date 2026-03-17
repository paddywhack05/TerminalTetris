# Terminal Tetris
```diff
- Do not use git bash on windows outside vs code
```
## Recomended Terminals
### Windows
MSYS2: if you use mingw u likely have it works perfect, \
Command prompt: Every one has it does the job, \
Powershell: I think its ugly but it works, \
Any vs code teminal: I hate that it hides the differences but it works,
### Linux
I tested it on the gnome Terminal which I think is xterm \
But most should work and im not a linux daily driver
## Controls
#### Arrow keys supported
A = ← \
D = → \
S = &nbsp;↓  \
E = ↷ \
Q = ↶  \
ESC = Exit \
&nbsp;↑ = ↷

## Build Instructions
```bash
make
or
gcc terminalTetris.c -o UR_NAME 
```

No linking needed all headers should come with os \
Some terminals work in vs code but not just the terminal git bash for windows seems to have problems flushing and input when not in vs code 



