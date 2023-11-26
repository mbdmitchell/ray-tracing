# Ray Tracing

This repository comprises my ongoing ray tracing project. To understand the theory, I have been learning from `raytracing.github.io`. Although note that, due to dissatisfaction with the quality of the author's code examples, my code very rarely follows their code.

I will update the README as I go, showing the different stages.

## Stages
(In reverse-chronological order)

### 2. Flesh out initial Code

![Output Image from this stage](./assets/stage_2.png)

#### Changes

- Add a `Camera` and `Viewport` class
- Flesh out rendering logic, rendering an image (see above) based on the y-direction of the rays

### 1. Initial Stage

![Output Image from this stage](./assets/stage_1.png)

#### Changes
- Make Python script to view PPM images and integrated it into my C++ code
- Start creating some of the core classes and functions: Vec3, Ray, `render()`, etc.
- Render first image (with some temporary function bodies) to test that the whole process from file creation, writing to the file, to loading/viewing it with the Python script ran correctly