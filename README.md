# Bomberman-Cpp
The classic bomberman implemented with C++

Window.h:
•	UpdatePlayerInput() = check the pressed key input (SDL_GetKeyboardState) and the "inputnull" (private variable in windows). If a key is press inputnull’ll set true and                       u can’t no longer press that key. The player is moved by 32 pixels and a variable “arrayposition” is increased for chech the under cell
