#include <GL/glut.h>
#include <math.h>

// Camera position and orientation
float camX = 2.3f, camY = 1.7f, camZ = 2.7f;
float yaw = -90.0f, pitch = 0.0f;
float lastX = 400, lastY = 300;
bool firstMouse = true;
bool hidden = false;
float lidAngle = 0.0f; // Current rotation angle
bool isOpening = true; // Direction of movement (opening/closing)

// Camera direction
float dirX = 0.0f, dirY = 0.0f, dirZ = -1.0f;

// Window variables
int windowWidth = 800;
int windowHeight = 600;
int savedWindowWidth = 800;
int savedWindowHeight = 600;
int savedWindowPosX = 100;
int savedWindowPosY = 100;
void setupLighting ();
bool isFullscreen = false;


void Cartecius()
{
	glColor3f(1.0, 0.0, 0.0);
	glBegin(GL_LINES);
	
	glVertex3f(-100.0, 1.5, 0.0);
	glVertex3f(100.0, 1.5, 0.0);
	
	glVertex3f(0.0, -100.0, 0.0);
	glVertex3f(0.0, 100.0, 0.0);
	
	glVertex3f(0.0, 1.5, -100.0);
	glVertex3f(0.0, 1.5, 100.0);
	glEnd();
}

void hiddenCarte()
{
	if (hidden)
	{
		Cartecius();
	}
}

void drawChest() {
	glPushMatrix();
	glTranslatef(0.0f, 0.0f, -0.9f);
	
    // Peti
    glColor3ub(206, 168, 15);
    glPushMatrix();
    glTranslatef(-2.45f, 0.30f, 0.0f);
    glScalef(1.0f, 0.4f, 2.0f);
    glutSolidCube(1.0f);
    glPopMatrix();
    
    //wireb peti
    glColor3f(0.0f, 0.0f, 0.0f);
	glLineWidth(10.0f); // Menetapkan ketebalan garis menjadi 3 piksel
	glPushMatrix();
	glTranslatef(-2.45f, 0.30f, 0.0f);
	glScalef(1.0f, 0.4f, 2.0f);
	glutWireCube(1.0f);
	glPopMatrix();
	glLineWidth(1.0f); // Mengembalikan ketebalan garis ke default
	
	//button
	glColor3ub(255, 255, 255);
    glPushMatrix();
    glTranslatef(-1.95f, 0.50f, 0.0f);
    glScalef(0.1f, 0.1f, 0.1f);
    glutSolidCube(1.0f);
    glPopMatrix();
    
    //========== tingkat 2 =========
    //peti
    glColor3ub(206, 168, 15);
    glPushMatrix();
    glTranslatef(-2.45f, 1.0f, 0.0f);
    glScalef(1.0f, 0.4f, 2.0f);
    glutSolidCube(1.0f);
    glPopMatrix();
    
    //tutup
    glColor3f(0.0f, 0.0f, 0.0f);
	glLineWidth(10.0f); // Menetapkan ketebalan garis menjadi 3 piksel
	glPushMatrix();
	glTranslatef(-2.45f, 1.0f, 0.0f);
	glScalef(1.0f, 0.4f, 2.0f);
	glutWireCube(1.0f);
	glPopMatrix();
	glLineWidth(1.0f); // Mengembalikan ketebalan garis ke default
	
	//button
	glColor3ub(255, 255, 255);
    glPushMatrix();
    glTranslatef(-1.95f, 1.20f, 0.0f);
    glScalef(0.1f, 0.1f, 0.1f);
    glutSolidCube(1.0f);
    glPopMatrix();

    // Tutup
    glColor3ub(206, 168, 15);
    glPushMatrix();
    glTranslatef(-2.45f, 0.6f, 0.0f);
    glScalef(1.0f, 0.2f, 2.0f);
    glutSolidCube(1.0f);
    glPopMatrix();
    
    glColor3f(0.0f, 0.0f, 0.0f);
    glLineWidth(10.0f);
    glPushMatrix();
    glTranslatef(-2.45f, 0.6f, 0.0f);
    glScalef(1.0f, 0.2f, 2.0f);
    glutWireCube(1.0f);
    glPopMatrix();
    glLineWidth(1.0f);
    
    //tingkat 2
    glColor3ub(206, 168, 15);
    glPushMatrix();
    glTranslatef(-2.45f, 1.3f, 0.0f);
    glScalef(1.0f, 0.2f, 2.0f);
    glutSolidCube(1.0f);
    glPopMatrix();
    
    glColor3f(0.0f, 0.0f, 0.0f);
    glLineWidth(10.0f);
    glPushMatrix();
    glTranslatef(-2.45f, 1.3f, 0.0f);
    glScalef(1.0f, 0.2f, 2.0f);
    glutWireCube(1.0f);
    glPopMatrix();
    glLineWidth(1.0f);
    
    //========= rotate sebelah kanan =========
    
    // peti kanan
    glColor3ub(206, 168, 15);
    glPushMatrix();
    glRotated(90, 0, 45, 0);
    glTranslatef(1.55f, 0.30f, 0.0f);
    glScalef(1.0f, 0.4f, 2.0f);
    glutSolidCube(1.0f);
    glPopMatrix();
    
    glColor3f(0.0f, 0.0f, 0.0f);
	glLineWidth(10.0f); // Menetapkan ketebalan garis menjadi 3 piksel
	glPushMatrix();
	glRotated(90, 0, 45, 0);
    glTranslatef(1.55f, 0.30f, 0.0f);
	glScalef(1.0f, 0.4f, 2.0f);
	glutWireCube(1.0f);
	glPopMatrix();
	glLineWidth(1.0f); // Mengembalikan ketebalan garis ke default
	
	glColor3ub(255, 255, 255);
    glPushMatrix(); 
	glRotated(90, 0, 45, 0);
    glTranslatef(1.05f, 0.50f, 0.0f);
    glScalef(0.1f, 0.1f, 0.1f);
    glutSolidCube(1.0f);
    glPopMatrix();
    
    //Tutup
    glColor3ub(206, 168, 15);
    glPushMatrix();
    glRotated(90, 0, 45, 0);
    glTranslatef(1.55f, 0.6f, 0.0f);
    glScalef(1.0f, 0.2f, 2.0f);
    glutSolidCube(1.0f);
    glPopMatrix();
    
    glColor3f(0.0f, 0.0f, 0.0f);
    glLineWidth(10.0f);
    glPushMatrix();
    glRotated(90, 0, 45, 0);
    glTranslatef(1.55f, 0.6f, 0.0f);
    glScalef(1.0f, 0.2f, 2.0f);
    glutWireCube(1.0f);
    glPopMatrix();
    glLineWidth(1.0f);
    
    glPopMatrix();
}

void toggleFullscreen() {
    isFullscreen = !isFullscreen;
    if (isFullscreen) {
        // Save current window position and size
        savedWindowPosX = glutGet(GLUT_WINDOW_X);
        savedWindowPosY = glutGet(GLUT_WINDOW_Y);
        savedWindowWidth = glutGet(GLUT_WINDOW_WIDTH);
        savedWindowHeight = glutGet(GLUT_WINDOW_HEIGHT);
        
        // Switch to fullscreen
        glutFullScreen();
    } else {
        // Restore window position and size
        glutReshapeWindow(savedWindowWidth, savedWindowHeight);
        glutPositionWindow(savedWindowPosX, savedWindowPosY);
    }
}

void init() {
    glEnable(GL_DEPTH_TEST);
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    // Hide cursor and set it to center
    glutSetCursor(GLUT_CURSOR_NONE);
    
    glutFullScreen();
    isFullscreen = true;
    
    glEnable(GL_DEPTH_TEST);
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glutSetCursor(GLUT_CURSOR_NONE);

    // Tambahkan setup pencahayaan
    setupLighting();
}

void drawRoom() {
	//========= Floor =========
    // Gambar permukaan (Quad)
	glColor3f(0.94f, 0.86f, 0.55f);  // Warna pasir gurun yang lebih muda
	glBegin(GL_QUADS);
    glVertex3f(-3.0f, 0.0f, -3.0f);
    glVertex3f(-3.0f, 0.0f, 3.0f);
    glVertex3f(3.0f, 0.0f, 3.0f);
    glVertex3f(3.0f, 0.0f, -3.0f);
	glEnd();

	// Gambar garis-garis horizontal
	glColor3f(0.3f, 0.2f, 0.1f);  // Warna garis lebih gelap untuk kontras
	for (float x = -3.0f; x <= 3.0f; x += 0.5f) {
    	glBegin(GL_LINES);
        	glVertex3f(x, 0.0f, -3.0f);
        	glVertex3f(x, 0.0f, 3.0f);
    	glEnd();
	}

	// Gambar garis-garis vertikal
	for (float z = -3.0f; z <= 3.0f; z += 0.5f) {
    	glBegin(GL_LINES);
        	glVertex3f(-3.0f, 0.0f, z);
        	glVertex3f(3.0f, 0.0f, z);
    	glEnd();
	}

    //========= Ceiling =========
    // Gambar permukaan (Quad)
	glColor3f(0.8f, 0.6f, 0.3f);  // Warna kayu Minecraft yang lebih muda
	glBegin(GL_QUADS);
    glVertex3f(-3.0f, 3.0f, -3.0f);
    glVertex3f(-3.0f, 3.0f, 3.0f);
    glVertex3f(3.0f, 3.0f, 3.0f);
    glVertex3f(3.0f, 3.0f, -3.0f);
	glEnd();

	// Gambar garis-garis horizontal
	glColor3f(0.3f, 0.2f, 0.1f);  // Warna garis lebih gelap untuk kontras
	for (float x = -3.0f; x <= 3.0f; x += 0.5f) {
    	glBegin(GL_LINES);
        	glVertex3f(x, 3.0f, -3.0f);
        	glVertex3f(x, 3.0f, 3.0f);
    	glEnd();
	}

	// Gambar garis-garis vertikal
	for (float z = -3.0f; z <= 3.0f; z += 0.5f) {
    	glBegin(GL_LINES);
        	glVertex3f(-3.0f, 3.0f, z);
        	glVertex3f(3.0f, 3.0f, z);
    	glEnd();
	}

    // Walls
    glColor3f(0.8f, 0.6f, 0.3f);
    
    //========= Back wall =========
    // Gambar permukaan (Quad)
	glColor3f(0.8f, 0.6f, 0.3f);  // Warna kayu Minecraft yang lebih muda
	glBegin(GL_QUADS);
    glVertex3f(-3.0f, 0.0f, -3.0f);
    glVertex3f(-3.0f, 3.0f, -3.0f);
    glVertex3f(3.0f, 3.0f, -3.0f);
    glVertex3f(3.0f, 0.0f, -3.0f);
	glEnd();

	// Gambar garis-garis horizontal
	glColor3f(0.3f, 0.2f, 0.1f);  // Warna garis lebih gelap untuk kontras
	for (float x = -3.0f; x <= 3.0f; x += 0.5f) {
    	glBegin(GL_LINES);
        	glVertex3f(x, 0.0f, -3.0f);
        	glVertex3f(x, 3.0f, -3.0f);
    	glEnd();
	}

	// Gambar garis-garis vertikal
	for (float y = 0.0f; y <= 3.0f; y += 0.5f) {
    	glBegin(GL_LINES);
        	glVertex3f(-3.0f, y, -3.0f);
        	glVertex3f(3.0f, y, -3.0f);
    	glEnd();
	}

    // Front wall
    glColor3f(0.8f, 0.6f, 0.3f);  // Warna kayu Minecraft yang lebih muda
	glBegin(GL_QUADS);
    glVertex3f(-3.0f, 0.0f, 3.0f);
    glVertex3f(-3.0f, 3.0f, 3.0f);
    glVertex3f(3.0f, 3.0f, 3.0f);
    glVertex3f(3.0f, 0.0f, 3.0f);
	glEnd();

	// Gambar garis-garis horizontal
	glColor3f(0.3f, 0.2f, 0.1f);  // Warna garis lebih gelap untuk kontras
	for (float y = 0.0f; y <= 3.0f; y += 0.5f) {
    	glBegin(GL_LINES);
        	glVertex3f(-3.0f, y, 3.0f);
        	glVertex3f(3.0f, y, 3.0f);
    	glEnd();
	}

	// Gambar garis-garis vertikal
	for (float x = -3.0f; x <= 3.0f; x += 0.5f) {
    	glBegin(GL_LINES);
        	glVertex3f(x, 0.0f, 3.0f);
        	glVertex3f(x, 3.0f, 3.0f);
    	glEnd();
	}

    // Left wall
    // Gambar permukaan (Quad)
	glColor3f(0.8f, 0.6f, 0.3f);  // Warna kayu Minecraft yang lebih muda
	glBegin(GL_QUADS);
    glVertex3f(-3.0f, 0.0f, -3.0f);
    glVertex3f(-3.0f, 3.0f, -3.0f);
    glVertex3f(-3.0f, 3.0f, 3.0f);
    glVertex3f(-3.0f, 0.0f, 3.0f);
	glEnd();

	// Gambar garis-garis horizontal
	glColor3f(0.3f, 0.2f, 0.1f);  // Warna garis lebih gelap untuk kontras
	for (float y = 0.0f; y <= 3.0f; y += 0.5f) {
    	glBegin(GL_LINES);
        	glVertex3f(-3.0f, y, -3.0f);
        	glVertex3f(-3.0f, y, 3.0f);
    	glEnd();
	}

	// Gambar garis-garis vertikal
	for (float z = -3.0f; z <= 3.0f; z += 0.5f) {
    	glBegin(GL_LINES);
        	glVertex3f(-3.0f, 0.0f, z);
        	glVertex3f(-3.0f, 3.0f, z);
   		glEnd();
	}

    // Right wall
    // Gambar permukaan (Quad)
	glColor3f(0.8f, 0.6f, 0.3f);  // Warna kayu Minecraft yang lebih muda
	glBegin(GL_QUADS);
    glVertex3f(3.0f, 0.0f, -3.0f);
    glVertex3f(3.0f, 3.0f, -3.0f);
    glVertex3f(3.0f, 3.0f, 3.0f);
    glVertex3f(3.0f, 0.0f, 3.0f);
	glEnd();

	// Gambar garis-garis horizontal
	glColor3f(0.3f, 0.2f, 0.1f);  // Warna garis lebih gelap untuk kontras
	for (float y = 0.0f; y <= 3.0f; y += 0.5f) {
    	glBegin(GL_LINES);
        	glVertex3f(3.0f, y, -3.0f);
        	glVertex3f(3.0f, y, 3.0f);
    	glEnd();
	}

	// Gambar garis-garis vertikal
	for (float z = -3.0f; z <= 3.0f; z += 0.5f) {
    	glBegin(GL_LINES);
        	glVertex3f(3.0f, 0.0f, z);
        	glVertex3f(3.0f, 3.0f, z);
    	glEnd();
	}

}

void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    // Set camera position and orientation
    gluLookAt(camX, camY, camZ,
              camX + dirX, camY + dirY, camZ + dirZ,
              0.0f, 1.0f, 0.0f);

    drawRoom();
    drawChest();
    hiddenCarte();
    
    glPushMatrix();
    glTranslatef(-0.45f, 0.0f, -6.2f);
    glPopMatrix();
	
    glutSwapBuffers();
}

void reshape(int w, int h) {
    windowWidth = w;
    windowHeight = h;
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0f, (float)w / h, 0.1f, 100.0f);
    glMatrixMode(GL_MODELVIEW);
}

void keyboard(unsigned char key, int x, int y) {
    float speed = 0.1f;
    
    switch (key) {
        case 'w':
            camX += dirX * speed;
            camZ += dirZ * speed;
            break;
        case 's':
            camX -= dirX * speed;
            camZ -= dirZ * speed;
            break;
        case 'a':
            camX += dirZ * speed;
            camZ -= dirX * speed;
            break;
        case 'd':
            camX -= dirZ * speed;
            camZ += dirX * speed;
            break;
        case 'c':	
			hidden = !hidden;
			break;
        case 'f': // Tombol F untuk toggle fullscreen
            toggleFullscreen();
            break;
        case 27:  // ESC key
            if (isFullscreen) {
                toggleFullscreen(); // Keluar dari fullscreen dulu
            } else {
                exit(0); // Keluar program jika sudah dalam mode window
            }
            break;
    }
    glutPostRedisplay();
}



void mouseMove(int x, int y) {
    float xoffset = x - windowWidth/2;
    float yoffset = windowHeight/2 - y;

    float sensitivity = 0.1f;
    xoffset *= sensitivity;
    yoffset *= sensitivity;

    yaw += xoffset;
    pitch += yoffset;

    if (pitch > 89.0f)
        pitch = 89.0f;
    if (pitch < -89.0f)
        pitch = -89.0f;

    dirX = cos(yaw * M_PI / 180.0f) * cos(pitch * M_PI / 180.0f);
    dirY = sin(pitch * M_PI / 180.0f);
    dirZ = sin(yaw * M_PI / 180.0f) * cos(pitch * M_PI / 180.0f);
    
    // Reset mouse position to center of window
    glutWarpPointer(windowWidth/2, windowHeight/2);
    
    glutPostRedisplay();
}

void setupLighting() {
    // Aktifkan pencahayaan
    glEnable(GL_LIGHTING);

    // Aktifkan sumber cahaya pertama
    glEnable(GL_LIGHT0);

    // Set warna cahaya
    GLfloat lightAmbient[] = {0.2f, 0.2f, 0.2f, 1.0f};
    GLfloat lightDiffuse[] = {0.8f, 0.8f, 0.8f, 1.0f};
    GLfloat lightSpecular[] = {1.0f, 1.0f, 1.0f, 1.0f};

    glLightfv(GL_LIGHT0, GL_AMBIENT, lightAmbient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, lightDiffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, lightSpecular);

    // Set posisi cahaya
    GLfloat lightPosition[] = {2.0f, 4.0f, 2.0f, 1.0f}; // Posisi cahaya (x, y, z, w)
    glLightfv(GL_LIGHT0, GL_POSITION, lightPosition);

    // Set parameter attenuation (melemahnya cahaya seiring jarak)
    glLightf(GL_LIGHT0, GL_CONSTANT_ATTENUATION, 1.0f);
    glLightf(GL_LIGHT0, GL_LINEAR_ATTENUATION, 0.05f);
    glLightf(GL_LIGHT0, GL_QUADRATIC_ATTENUATION, 0.01f);

    // Aktifkan warna material otomatis
    glEnable(GL_COLOR_MATERIAL);
    glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    
    // Get screen resolution
    windowWidth = glutGet(GLUT_SCREEN_WIDTH);
    windowHeight = glutGet(GLUT_SCREEN_HEIGHT);
    
    glutInitWindowSize(windowWidth, windowHeight);
    glutInitWindowPosition(0, 0);
    glutCreateWindow("Pixelated Room");

    init();

    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);
    glutPassiveMotionFunc(mouseMove);

    glutMainLoop();
    return 0;
}

