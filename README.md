# :sunny: **Ray Tracing**
<img width="1595" height="892" alt="image" src="https://github.com/user-attachments/assets/f77a8c5a-747b-456c-90f6-9a545cbe7788" />



## **Overview**

This is a simple ray tracer project built with C++. I completed this project based on the course by [HongLab](https://www.honglab.ai/courses/graphicspt1).

### Built with
![Visual Studio](https://img.shields.io/badge/Visual%20Studio-5C2D91.svg?style=for-the-badge&logo=visual-studio&logoColor=white)  ![C++](https://img.shields.io/badge/c++-%2300599C.svg?style=for-the-badge&logo=c%2B%2B&logoColor=white)


### Core Concepts Learned in the Course
* Drawing Sphere
* Adding Shadows
* Barycentric coordinates
* Texturing
* Super Sampling
* Light Reflection & Refraction

### Additional Implementations

Beyond the course material, I further implemented:

* Cube Mapping
* Fresnel Reflection/Refraction
* Antialiasing
* Depth of Field



## **Features**

### Depth of Field (DoF)

**Description:** Depth of Field simulates the camera lens effect where only a specific range of distances is in sharp focus, while objects outside this range appear blurred. This adds realism and artistic depth to the scene.
<img width="1590" height="887" alt="DoF" src="https://github.com/user-attachments/assets/0665dc80-4ab0-4696-955f-efd40461bb02" />


### Antialiasing

**Description:** Antialiasing is a technique used to smooth out jagged edges (aliasing) that appear in rendered images due to pixelation.

| No Antialiasing | With Antialiasing |
|---|---|
| <img src="https://github.com/user-attachments/assets/e786476c-9035-4106-a67e-1833d7809679" alt="No Antialiasing Example 1" width="1000"> | <img src="https://github.com/user-attachments/assets/92aaf1f6-0bfc-46cf-aff0-18b9646fa97c" alt="Antialiasing Example 1" width="1000"> |
| <img src="https://github.com/user-attachments/assets/544bc6eb-684c-411f-9bc9-ae324501adc9" alt="No Antialiasing Example 2" width="450"> | <img src="https://github.com/user-attachments/assets/2f6465c3-8f6f-4681-8ab6-f483b717b883" alt="Antialiasing Example 2" width="450"> |


### Fresnel

**Description:** The Fresnel effect describes how the reflectivity of a surface changes with the angle of incidence. Surfaces become more reflective which is crucial for realistic material appearance (for this project I used it for water).

| No Fresnel | With Fresnel |
|---|---|
| <img src="https://github.com/user-attachments/assets/3fc37180-9b52-498a-8d39-280503101ac3" alt="No Fresnel Example" width="450"> | <img src="https://github.com/user-attachments/assets/b0cf9b38-2506-4444-96b7-09007b7d45b8" alt="With Fresnel Example" width="450"> |



## **Limitations**

* **Fixed Camera Position:** The camera position is static and cannot be controlled.
    * _For future work:_ Implement camera controls.
* **Underexposed Indirect Lighting:** Areas not directly illuminated by light sources appear too dark, lacking realistic ambient or indirect illumination.
* **Unrealistic Shadows:** Shadows are currently hard-edged and lack physically accurate properties.
* **Basic Texture Mapping:** The current texture mapping method could be improved for more realistic appearance.
* **Performance:** Rendering a scene with all features enabled takes approximately 5 minutes on my laptop.
    * _For future work:_ Use GPU acceleration for significant speedup.
* **Code Organization:** The core ray tracing logic is primarily contained within `Raytracer.cpp` for simplicity in this initial project.
    *_For future work:_ Separate header files and classes for enhanced modularity.



## **Installation**
Download the project and run the sln file. If it doesn't run in Release mode please run in Debug mode.


## **Acknowledgements**
* [HongLab](https://www.honglab.ai/courses/graphicspt1)
* [Cube Map](https://www.humus.name/index.php?page=Cubemap&item=Tenerife2)
* [Fresnel](https://www.scratchapixel.com/lessons/3d-basic-rendering/introduction-to-shading/reflection-refraction-fresnel.html)
* [Antialiasing](https://raytracing.github.io/books/RayTracingInOneWeekend.html)
* Depth of Field
  - [nvidia DoF 1](https://developer.nvidia.com/gpugems/gpugems/part-iv-image-processing/chapter-23-depth-field-survey-techniques)
  - [nvidia DoF 2](https://developer.nvidia.com/gpugems/gpugems3/part-iv-image-effects/chapter-28-practical-post-process-depth-field)
  - [Ray Tracing in One Weekend](https://raytracing.github.io/books/RayTracingInOneWeekend.html)
