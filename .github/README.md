# 3D Cube

A lightweight, high-performance 3D graphics application exploring procedural 3D camera matrices and mathematical abstractions in C++. Built around the powerful [Raylib](https://www.raylib.com/) library, the rendering pipeline dynamically draws a centralized grid and wireframed cube entity.

# Preview 

![Preview](preview.png)


## Running Locally

Because this project natively hooks into **Nix Flakes**, dependency matching and building is completely automated.

1. Clone the repository and navigate inside:
   ```bash
   git clone https://github.com/sijanthapa171/cube.git
   cd CubeSolver
   ```

2. Boot into the guaranteed development shell with the required compiler tools:
   ```bash
   nix develop
   ```

3. Compile the application and systematically spin up the custom graphical window:
   ```bash
   make run
   ```

### Additional Build Commands
- `make`: Compiles standard object assets safely routing to the `/build` folder.
- `make clean`: Wipes the generated binary target and `/build` directory cache.

