//varying vec3 vertex_color;
//
//void main() {
//  gl_FragColor = vec4(vertex_color,1.0);
//}


varying vec3 normal;
varying vec3 position;

void main() {
  vec3 diffuse = vec3(0.8, 0.5, 0.45);
  vec3 light_location = vec3(5.0, 5.0, 5.0);
  vec3 light_vector = normalize(light_location - position);

  float nxDir =max(0.0,dot(normal,light_vector));

  gl_FragColor = vec4(diffuse * nxDir, 1.0);
//  gl_FragColor = vec4(normal, 1.0);
}