//
// Created by awbrenn on 10/16/16.
//

//
// Created by Austin Brennan on 9/12/16
// See readme.md for more details
//
#define GL_GLEXT_PROTOTYPES 1

#include "Camera.h"
#include "Object.h"
#include "RigidObject.h"
#include "Solver.h"

#ifdef __APPLE__
  #pragma clang diagnostic ignored "-Wdeprecated-declarations"
  #include <GLUT/glut.h>
  #include <OpenGL/gl.h>
#else
  #include <GL/glut.h>
  #include <GL/gl.h>
#endif

int WIDTH = 1280;
int HEIGHT = 720;

Camera *camera;
RigidObject *rigid_object;
Solver *solver;
unsigned int INTEGRATOR;
Vector3d user_acceleration;
double user_accel_magnitude;
bool simulation_paused = false;

// TODO remove this
bool first_run = true;

bool showReferenceGrid = false;
bool showNormals = false;
bool showDebugMode = false;

// draws a simple grid
void drawReferenceGrid() {
  glUseProgram(0);
  glColor3f(0.0f, 0.0f, 0.0f);

  glLineWidth(1.0f);

  for (double i=-12; i<12; i++) {
    for (double j=-12; j<12; j++) {
      glBegin(GL_LINES);
      glVertex3f(i, (GLfloat) solver->ground_level, j);
      glVertex3f(i, (GLfloat) solver->ground_level, j+1);
      glEnd();
      glBegin(GL_LINES);
      glVertex3f(i, (GLfloat) solver->ground_level, j);
      glVertex3f(i+1, (GLfloat) solver->ground_level, j);
      glEnd();

      if (j == 11){
        glBegin(GL_LINES);
        glVertex3f(i, (GLfloat) solver->ground_level, j+1);
        glVertex3f(i+1, (GLfloat) solver->ground_level, j+1);
        glEnd();
      }
      if (i == 11){
        glBegin(GL_LINES);
        glVertex3f(i+1, (GLfloat) solver->ground_level, j);
        glVertex3f(i+1, (GLfloat) solver->ground_level, j+1);
        glEnd();
      }
    }
  }

  glLineWidth(2.0f);
  glBegin(GL_LINES);
  glVertex3f(-12, (GLfloat) solver->ground_level, 0);
  glVertex3f(12, (GLfloat) solver->ground_level, 0);
  glEnd();
  glBegin(GL_LINES);
  glVertex3f(0, (GLfloat) solver->ground_level, -12);
  glVertex3f(0, (GLfloat) solver->ground_level, 12);
  glEnd();
  glLineWidth(1.0f);
}

void initCameraDebug() {
  // set up camera
  // parameters are eye point, aim point, up vector
  camera = new Camera(Vector3d(0, 5, 5), Vector3d(0, 0, 0),
                      Vector3d(0, 1, 0));

  // grey background for window
  glClearColor(0.62, 0.62, 0.62, 0.0f);
//  glClearColor(0.0, 0.0, 0.0, 0.0f);
  glShadeModel(GL_SMOOTH);
  glDepthRange(0.0f, 1.0f);

  glEnable(GL_NORMALIZE);
  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

void initCameraRender() {
  // set up camera
  // parameters are eye point, aim point, up vector
  camera = new Camera(Vector3d(0, 5, 5), Vector3d(0, 0, 0),
                      Vector3d(0, 1, 0));

  // black background for window
  glClearColor(0.0, 0.0, 0.0, 0.0f);
  glShadeModel(GL_SMOOTH);
  glDepthRange(0.0f, 1.0f);

  glEnable(GL_NORMALIZE);
  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

void drawDebug() {
  Vector3d gravity(0.0, -9.8, 0.0);
  Vector3d spring_force(0.0, 0.0, 0.0);
  double spring_constant = 200.0;
  Vector3d line_anchor(0.0, 0.0, 0.0);
  double line_length = 2.0;
  Vector3d rigid_body_pin_position = rigid_object->getPinPosition();
  Vector3d r = (rigid_body_pin_position - rigid_object->state.x).normalize(); // unit vector from rigid body position to pinned point on rigid body
  Vector3d l = (line_anchor - rigid_body_pin_position).normalize(); // unit vector in the direction of the anchor from the pin

  if (rigid_body_pin_position.norm() > line_length) {
    spring_force = spring_constant * ((rigid_body_pin_position.norm() - line_length) * l);
  }

  glColor3f(0.1, 0.2, 0.7);
  glBegin(GL_LINES);
  glVertex3f(rigid_object->state.x.x, rigid_object->state.x.y, rigid_object->state.x.z);
  glVertex3f(rigid_object->state.x.x + r.x, rigid_object->state.x.y + r.y, rigid_object->state.x.z + r.z);
  glEnd();

  glColor3f(0.7, .7, 0.1);
  glBegin(GL_LINES);
  glVertex3f(rigid_body_pin_position.x, rigid_body_pin_position.y, rigid_body_pin_position.z);
  glVertex3f(rigid_body_pin_position.x + l.x, rigid_body_pin_position.y + l.y, rigid_body_pin_position.z + l.z);
  glEnd();

  glColor3f(1.0, .2, 0.2);
  glBegin(GL_LINES);
  glVertex3f(rigid_body_pin_position.x, rigid_body_pin_position.y, rigid_body_pin_position.z);
  glVertex3f(rigid_body_pin_position.x + spring_force.x, rigid_body_pin_position.y + spring_force.y, rigid_body_pin_position.z + spring_force.z);
  glEnd();

//  glColor3f(1.0, .2, 0.2);
//  glBegin(GL_LINES);
//  glVertex3f(rigid_body_pin_position.x, rigid_body_pin_position.y, rigid_body_pin_position.z);
//  glVertex3f(rigid_body_pin_position.x + spring_force.x, rigid_body_pin_position.y + spring_force.y, rigid_body_pin_position.z + spring_force.z);
//  glEnd();

  glColor3f(1.0, 0.0, 0.0);
  glPointSize(3.0);
  glBegin(GL_POINTS);
  glVertex3f(rigid_body_pin_position.x, rigid_body_pin_position.y, rigid_body_pin_position.z);
  glEnd();

  glColor3f(0.0, 1.0, 3.0);
  glPointSize(3.0);
  glBegin(GL_POINTS);
  glVertex3f(0.0, 0.0, 0.0);
  glEnd();

  glColor3f(0.0, 0.0, 0.0);
}

void drawMeshDebug() {
  glPolygonMode(GL_FRONT, GL_LINE);
  glPolygonMode(GL_BACK, GL_LINE);
  glBegin(GL_TRIANGLES);
  for (int i = 0; i < rigid_object->displaced_mesh.faces.size(); ++i) {
    Face face = rigid_object->displaced_mesh.faces[i];
    for (int j = 0; j < 3; ++j) {
      glNormal3f((GLfloat) face.v[j]->normal->x, (GLfloat) face.v[j]->normal->y, (GLfloat) face.v[j]->normal->z);
      glVertex3f((GLfloat) face.v[j]->position->x, (GLfloat) face.v[j]->position->y, (GLfloat) face.v[j]->position->z);
    }
  }
  glEnd();
  glPolygonMode(GL_FRONT, GL_FILL);
  glPolygonMode(GL_BACK, GL_FILL);

  if (showNormals) {
    glColor3f(0.0, 1.0, 0.0);
    glBegin(GL_LINES);
    for (int i = 0; i < rigid_object->displaced_mesh.faces.size(); ++i) {
      Face face = rigid_object->displaced_mesh.faces[i];
      for (int j = 0; j < 3; ++j) {
        glVertex3f((GLfloat) face.v[j]->position->x, (GLfloat) face.v[j]->position->y,
                   (GLfloat) face.v[j]->position->z);
        glVertex3f((GLfloat) (face.v[j]->position->x + face.v[j]->normal->x),
                   (GLfloat) (face.v[j]->position->y + face.v[j]->normal->y),
                   (GLfloat) (face.v[j]->position->z + face.v[j]->normal->z));
      }
    }
    glEnd();
    glColor3f(0.0, 0.0, 0.0);
  }
}

void drawBungeeLine() {
  Vector3d bungee_line = rigid_object->getPinPosition() - solver->line_anchor_point;

  glBegin(GL_LINES);
  glVertex3f((GLfloat) solver->line_anchor_point.x, (GLfloat) solver->line_anchor_point.y,
             (GLfloat) solver->line_anchor_point.z);
  glVertex3f((GLfloat) (solver->line_anchor_point.x + bungee_line.x),
             (GLfloat) (solver->line_anchor_point.y + bungee_line.y),
             (GLfloat) (solver->line_anchor_point.z + bungee_line.z));
  glEnd();
}

void drawMesh() {
  glUseProgram(rigid_object->shader->program);
  glActiveTexture(GL_TEXTURE0);
  glBindTexture(GL_TEXTURE_2D, 0);
  glBegin(GL_TRIANGLES);
  for (int i = 0; i < rigid_object->displaced_mesh.faces.size(); ++i) {
    Face face = rigid_object->displaced_mesh.faces[i];
    for (int j = 0; j < 3; ++j) {
      glTexCoord2f((GLfloat) face.v[j]->uv->x, (GLfloat) face.v[j]->uv->y);
      glNormal3f((GLfloat) face.v[j]->normal->x, (GLfloat) face.v[j]->normal->y, (GLfloat) face.v[j]->normal->z);
      glVertex3f((GLfloat) face.v[j]->position->x, (GLfloat) face.v[j]->position->y, (GLfloat) face.v[j]->position->z);
    }
  }
  glEnd();
  glUseProgram(0);
}

void perspDisplay() {
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  // draw the camera created in perspective
  camera->PerspectiveDisplay(WIDTH, HEIGHT);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();

  if (showReferenceGrid)
    drawReferenceGrid();

  if (showDebugMode) {
    drawReferenceGrid();
    drawMeshDebug();

    if (!first_run) {
      drawDebug();
    }
  }
  else {
    drawMesh();
    if (!first_run) {
      drawBungeeLine();
    }
  }

  first_run = false;

  glFlush();
  glutSwapBuffers();
}

void stepSimulation() {
  if (not simulation_paused) {
    solver->update(INTEGRATOR, user_acceleration);
    user_acceleration = Vector3d(0.0, 0.0, 0.0);
    glutPostRedisplay();
  }
}

void mouseEventHandler(int button, int state, int x, int y) {
  // let the camera handle some specific mouse events (similar to maya)
  camera->HandleMouseEvent(button, state, x, y);
  glutPostRedisplay();
}

void motionEventHandler(int x, int y) {
  // let the camera handle some mouse motions if the camera is to be moved
  camera->HandleMouseMotion(x, y);
  glutPostRedisplay();
}

void keyboardEventHandler(unsigned char key, int x, int y) {
  switch (key) {
    case 'w': case 'W':
      user_acceleration = Vector3d(0.0, 0.0, -1.0 * user_accel_magnitude);
      break;

    case 'a':
      user_acceleration = Vector3d(-1.0 * user_accel_magnitude, 0.0, 0.0);
      break;

    case 's':
      user_acceleration = Vector3d(0.0, 0.0, user_accel_magnitude);
      break;

    case 'd':
      user_acceleration = Vector3d(user_accel_magnitude, 0.0, 0.0);
      break;

    case 'p': case 'P':
      simulation_paused = !simulation_paused;
      ;
      break;

    case 'r': case 'R':
      showDebugMode = !showDebugMode;
      ;
      break;

    case 'n': case 'N':
      showNormals = !showNormals;
      ;
      break;

    case 'g': case 'G':
      showReferenceGrid = !showReferenceGrid;
      break;

    case 'f': case 'F':
      camera->SetCenterOfFocus(Vector3d(0, 0, 0));
      break;

    case 'q': case 'Q':	// q or esc - quit
    case 27:		// esc
      exit(0);
  }

  glutPostRedisplay();
}

bool readParameters(char *paramfile_name) {
  bool succeeded = true;
  std::ifstream paramfile_stream(paramfile_name);
  std::string line;

  if (paramfile_stream.is_open()) {
    // read through the file
    while (getline(paramfile_stream, line)) {

      if (line.compare("RIGID OBJECT:") == 0) {
        double mass;
        unsigned int pin_vertex_index;
        std::string obj_filename;
        std::string frag_shader_filename;
        std::string vert_shader_filename;
        std::string diffuse_texture_filename;
        // skip a line
        getline(paramfile_stream, line);

        // stream the line with object information
        getline(paramfile_stream, line);
        std::stringstream object_stream(line);

        object_stream >> obj_filename;

        // skip a few lines
        getline(paramfile_stream, line);
        getline(paramfile_stream, line);
        getline(paramfile_stream, line);

        object_stream.str(line);
        object_stream.clear();

        object_stream >> frag_shader_filename >> vert_shader_filename >> diffuse_texture_filename;

        // skip a line
        getline(paramfile_stream, line);
        getline(paramfile_stream, line);
        getline(paramfile_stream, line);

        object_stream.str(line);
        object_stream.clear();

        object_stream >> mass >> pin_vertex_index;

//        std::cout << "mass: " << mass << " k: " << spring_constant << " d: " << damping_constant << std::endl;

        // TODO add rigid_index_number to parameters
        rigid_object = new RigidObject(obj_filename, frag_shader_filename, vert_shader_filename, diffuse_texture_filename, mass,
                                       pin_vertex_index);
      }

      else if (line.compare("SOLVER:") == 0) {
        double time_step,
               ground_plane,
               spring_constant,
               line_length;
        unsigned int substeps;
        Vector3d line_anchor_point;

        // skip a line
        getline(paramfile_stream, line);

        getline(paramfile_stream, line);
        std::stringstream solver_stream(line);
        solver_stream >> time_step >> substeps;

        // skip a line
        getline(paramfile_stream, line);
        getline(paramfile_stream, line);
        getline(paramfile_stream, line);

        solver_stream.str(line);
        solver_stream.clear();
        std::string integration_type;

        solver_stream >> integration_type;
        if (integration_type.compare("EULER") == 0) {
          INTEGRATOR = EULER;
        }
        else if (integration_type.compare("RK4") == 0) {
          INTEGRATOR = RK4;
        }
        else {
          INTEGRATOR = RK4;
        }

        // skip a line
        getline(paramfile_stream, line);
        getline(paramfile_stream, line);
        getline(paramfile_stream, line);

        solver_stream.str(line);
        solver_stream.clear();

        solver_stream >> ground_plane >> spring_constant >> line_length >> line_anchor_point.x >>
                                                                           line_anchor_point.y >>
                                                                           line_anchor_point.z;

        // skip a line
        getline(paramfile_stream, line);
        getline(paramfile_stream, line);
        getline(paramfile_stream, line);

        solver_stream.str(line);
        solver_stream.clear();

        solver_stream >> user_accel_magnitude;

        solver = new Solver(rigid_object, time_step, substeps, ground_plane, spring_constant,
                            line_length, line_anchor_point);
      }
    }
  }
  else {
    succeeded = false;
  }

  return succeeded;
}

int main(int argc, char *argv[]) {
  if (argc != 2) {
    std::cerr << "Proper Usage: $> SquishyMesh parameters" << std::endl;
    exit(EXIT_FAILURE);
  }

  // set up opengl window
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_RGBA | GLUT_DEPTH | GLUT_DOUBLE);
  glutInitWindowSize(WIDTH, HEIGHT);
  glutInitWindowPosition(50, 50);
  int persp_win = glutCreateWindow("Simulating A Rigid Body");
  glEnable(GL_DEPTH_TEST);
  glEnable(GL_MULTISAMPLE_ARB);

  // read the parameters
  readParameters(argv[1]);

  // initialize the camera and such
  initCameraDebug();

  // set up opengl callback functions
  glutDisplayFunc(perspDisplay);
  glutIdleFunc(stepSimulation);
  glutMouseFunc(mouseEventHandler);
  glutMotionFunc(motionEventHandler);
  glutKeyboardFunc(keyboardEventHandler);

  glutMainLoop();
  return(0);
}

