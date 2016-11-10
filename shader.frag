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
  vec3 diffuse = vec3(texture2D(myDiffuse, gl_TexCoord[0].st));
  vec3 light_location0 = vec3(25.0, 25.0, 25.0);
  vec3 light_location1 = vec3(-14, -28, -18);

  vec3 light_vector0 = normalize(light_location0 - position);
  vec3 light_vector1 = normalize(light_location1 - position);

  float nxDir0 =max(0.0,dot(normal,light_vector0));
  float nxDir1 =max(0.0,dot(normal,light_vector1));

  vec4 light_influence0 = vec4(diffuse * nxDir0, 1.0);
  vec4 light_influence1 = vec4(diffuse * nxDir1, 1.0);
  gl_FragColor = light_influence0 + light_influence1;
//  gl_FragColor = vec4(normal, 1.0);
}