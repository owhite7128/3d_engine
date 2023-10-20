# TODO
- Finish rendering triangles intelligently (not just for looping through max size rect)
- Import and display materials (start with just flat colors imported per triangle, then move onto actual image textures).

# Intention
The intention of this project is to create a fully working software renderer to load .OBJ files and do everything a simple renderer should (rotation, translation, scaling, etc). This is not a fully featured game engine, so features required for that such as level loading or physics or game logic will need to be implemented by the end user.

# Features
- Full Z-Culling based on distance from the camera for maximum efficiency.
- Simple to use toolchain supporting init and per render functions to perform any computation every frame render.
- Rotation, scaling, and translation of all imported models. 
- Model importing based upon modern .OBJ file standard.
- Rotation and translation of camera to change the viewed perspective.

## To Use
On inclusion of the library and all required dependancies, a state struct will be initialized and a SDL window of size 1280x720 will be attached.

In order to use the renderer, first attach init and render functions as such
```
render_init (void (*init)(), void (*render)());
```

Once the necessary functions have been attached tell the renderer which mode to use. Currently only 3D mode is supported.
```
render (RENDER_MODE_3D);
```

Inside the init function, import any models that will need to be utilized right away and give them an initial state, rotation is thought of as a quaternion.
```
VEC3D init_pos = {x, y, z, 1};
ANG3D init_rot = {alpha, beta, gamma, angle};
add_model (app->mod_list, "objsrc", init_pos, init_rot, scale);
```

Then anything that is written inside the attached render function gets executed every frame. Models can be manipulated, added, or removed by using the mod_list linked list.