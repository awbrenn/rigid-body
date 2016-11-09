//varying vec3 vertex_color;
//
//void main() {
//  gl_FragColor = vec4(vertex_color,1.0);
//}


varying vec3 normal;
varying vec3 position;

// This is set by the .c code.
uniform sampler2D myDiffuse;

void main() {
  vec3 diffuse = vec3(texture2D(myDiffuse, gl_TexCoord[0].st/gl_TexCoord[0].q));
  vec3 light_location = vec3(5.0, 5.0, 5.0);
  vec3 light_vector = normalize(light_location - position);

  float nxDir =max(0.0,dot(normal,light_vector));

  gl_FragColor = vec4(diffuse * nxDir, 1.0);
//  gl_FragColor = vec4(normal, 1.0);
}