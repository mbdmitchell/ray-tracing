# Ray Tracing

This repository comprises my ongoing ray tracing project. To understand the theory, I have been learning from `raytracing.github.io`. Although note that, due to dissatisfaction with the quality of the author's code examples, my code very rarely uses any of their code.

I will update the README as I go, showing the different stages.

## Stages
(In reverse-chronological order)

### 1. Initial Stage

![Output Image from this stage](./assets/stage_1.png)

#### Changes
- Make Python script to view PPM images and integrated it into my C++ code
- Start creating some of the core classes and functions: Vec3, Ray, `render()`, etc.
- Rendered first image (with some temporary function bodies) to test that the whole process from file creation, writing to the file, to loading/viewing it with the Python script ran correctly