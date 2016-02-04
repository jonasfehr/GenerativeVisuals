// Author @patriciogv - 2015
// http://patriciogonzalezvivo.com
// edited for own use Jonas Fehr

#ifdef GL_ES
precision mediump float;
#endif

uniform vec2 u_resolution;
uniform float u_amount;
uniform float u_time;

uniform float u_xGrid;
uniform float u_yGrid;

uniform bool bwSwitch;
uniform bool bgTransparent;

float random (in float x) {
    return fract(sin(x)*1e4);
}

float random (in vec2 st) { 
    return fract(sin(dot(st.xy, vec2(12.9898,78.233)))* 43758.5453123);
}

float pattern(vec2 st, vec2 v, float t) {
    vec2 p = floor(st+v);
    return step(t, random(100.+p*.000001)+random(p.x)*0.5 );
}

void main() {
    vec2 st = gl_FragCoord.xy/u_resolution.xy;
    st.x *= u_resolution.x/u_resolution.y;

    vec2 grid = vec2(u_xGrid,u_yGrid);
    //vec2 grid = vec2(100.,200.);
    st *= grid;
    
    vec2 ipos = floor(st);  // integer
    vec2 fpos = fract(st);  // fraction
    
    vec2 vel = vec2(u_time*2.*max(grid.x,grid.y)); // time
    vel *= vec2(-1.,0.0) * random(1.0+ipos.y); // direction

    // Assign a random value base on the integer coord
    vec2 offset = vec2(0.1,0.);

    // vec3 color = vec3(0.);
    // color.r = pattern(st+offset,vel,0.2+1.0-u_amount);
    // color.g = pattern(st,vel,0.2+1.0-u_amount);
    // color.b = pattern(st-offset,vel,0.2+1.0-u_amount);

    float n = pattern(st,vel,0.2+1.0-u_amount);

    // Margins
    // color *= step(0.2,fpos.y);
   
    vec3 color = vec3(1.);

   float a = 1.0;
   if (bwSwitch) n = 1.0-n;
    if (bgTransparent) a = n;

   color = n * color;
    

    gl_FragColor = vec4(color, a);
}