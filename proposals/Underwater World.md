# Underwater World Proposal

The scene is an underwater world containing fish.

### Minimal Feature set 

- fog (Tristan)
- blueish screen tint
- fish swimming around (Tristan)
- simple lighting (Patrick/Tristan)
- some set piece e.g. sunken ship, rock formation, etc. (Patrick)

### More advanced features (choose some)
- shadows distorted by the surface (approximation by a simple noise texture) (Tristan)
- caustics (Patrick)
- godrays (Tristan)
- flocking behaviour (boids) (Tristan)
    - implement via instancing and compute shader
- give fish an animation (Patrick)
- make it interactive to move the camera around (Patrick *)
- use a particle system to create underwater bubbles with simple textures (Patrick)
- animated seaweed (Patrick)

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
- textured fish model (Tristan)
- set piece (Patrick)
- building pieces for a reef
- seaweed (Patrick)
- water bubble texture (Patrick)

### The Animation
This will just be a simple shot, locking at the fish swimming around.  
Together with the dynamic lighting and the objects this should be sufficiently interesting.


### Risks and Challenges
| Risks                                                       | Solutions                                                                                                                                              |   |   |   |
|-------------------------------------------------------------|--------------------------------------------------------------------------------------------------------------------------------------------------------|---|---|---|
| features are more difficult   to implement than aniticapted | the minimal features should be easy to implement   and the modularity of the more advanced features allows  to defer or skip the more challenging ones |   |   |   |
| collaboration                                               | frequent communication, source control and modular features should  ensure little friction when integrating features                                   |   |   |   |
|                                                             |                                                                                                                                                        |   |   |   |

