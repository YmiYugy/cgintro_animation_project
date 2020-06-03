# Underwater World Proposal

The scene is an underwater world containing fish.

### Minimal Feature set 

- fog 
- blueish screen tint
- fish swimming around
- simple lighting
- some set piece e.g. sunken ship, rock formation, etc.

### More advanced features (choose some)
- shadows distorted by the surface (approximation by a simple noise texture)
- caustics
- godrays
- flocking behaviour (boids)
    - implement via instancing and compute shader
- give fish an animation
- make it interactive to move the camera around
- use a particle system to create underwater bubbles with simple textures
- animated seaweed

### Most advanced features (more aspirational than realistic)
- ray tracing
    - use for:
        - fog
        - caustics
        - godrays
        - bubble refraction
        - shadows
        - global illumination
    - implement via compute shaders
- procedural generated coral reef
- utilizing dedicated ray tracing hardware for the compute tasks by using Vulkan instead of openGL

### Required Assets
- textured fish model
- set piece
- building pieces for a reef
- seaweed
- water bubble texture

### The Animation
This will just be a simple shot, locking at the fish swimming around.  
Together with the dynamic lighting and the objects this should be sufficiently interesting.

