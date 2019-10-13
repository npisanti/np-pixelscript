
#ifdef GL_ES
precision highp float;
#endif

uniform float u_time;
uniform vec2 u_resolution;

uniform sampler2D u_tex0;

void main (void) {
    vec2 st = gl_FragCoord.xy/u_resolution;
    
    vec4 source = texture2D( u_tex0, st );
    
    vec3 color = 1.0 - source.rgb;
    
    gl_FragColor = vec4( color, 1.0 ); 
}
