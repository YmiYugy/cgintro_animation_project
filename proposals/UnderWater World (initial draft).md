# Underwater World Proposal

The scene is an underwater world containing fish.

### Minimal Feature set 

- fog 
- blueish screen tint
- fish swimming around
- simple lighting

### More advanced features (choose some)
- shadows distorted by the surface (approximation by a simple noise texture)
- caustics
- godrays
- flocking behaviour (boids)
    - implement via instancing and compute shader
- give fish an animation
- make it interactive to move the camera around
- use a particle system to create underwater bubbles with simple textures

### Most advanced features (more aspirational than realistic)
- ray tracing
    - use for:
        - fog
        - caustics
        - godrays
        - bubble refraction
    - implement via compute shaders
- procedural generated coral reef
- animated seaweed
- utilizing dedicated ray tracing hardware for the compute tasks by using Vulkan instead of openGL