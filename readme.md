# TODO
- (BIG) Checking at render time which faces, if any, are occluded and don't render.
- Change from weird python wrapper to C Based window, allows easier implementation of render func.
- Work on render function


## IDEA FOR RENDER ORDER
For Every Model have the x_bar y_bar and z_bar be known, then get the distance from the camera, if it is in the viewport, than loop through every face on the model and every face of models equal to or closer in distance, moving inwards out then finally whatever the background fill in the rest with background.

Or paint background and floor first and just assume little inefficiency since background and floor are most likely just images.
Can get more complex if floor has depth and is actually a rendered object, if so just treat it similar to a model.

Since assuming the camera is the origin always, it gets easier to check if vector intersects plane, just check all four points of plane, since it is possible that the center of a plane is occluded but the rest of the plane is not.

Finally once satisfied render outwards in, so that if there is any overlap with semi occluded planes, you don't run into the issue of random texture overlap or that something is missing.

### For Intersection
- Need to know all plane normals, in order to get intersection
- Find IP using the ideas from https://courses.cs.washington.edu/courses/csep557/10au/lectures/triangle_intersection.pdf
- Then check if within smaller plane portion
- If it is disable that specific plane, and move on. 
- Only check against planes that will be rendered.
- If working inwards out, can assume that all of the planes that are enabled have the potential to be rendered.
- Versus outwards in, you can run into something where a plane further out gets rendered even tho something closer is covering it.
- MAKE SURE TO CHECK 4 CORNERS, IF EVEN 1 IS UNOCCLUDED THEN RENDER IT