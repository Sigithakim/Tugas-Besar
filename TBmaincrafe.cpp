#include <GL/glut.h>
#include <math.h>

// Camera position and orientation
float camX = 2.3f, camY = 1.7f, camZ = 2.7f;
float yaw = -90.0f, pitch = -50.0f;
float lastX = 400, lastY = 300;
bool firstMouse = true;
bool hidden = false;
float lidAngle = 0.0f; // Current rotation angle
bool isOpening = true; // Direction of movement (opening/closing)
float door_angle = 0.0f; // Sudut rotasi pintu
bool is_opening = false;
bool is_closing = false;
// Variabel global untuk sudut tutup peti
float tutupAngle = 0.0f; // Awalnya tertutup (0 derajat)

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

void drawMinecraftDoor() {
    // Bagian bawah pintu (panel kayu bawah)
    glPushMatrix();
    glColor3f(0.6f, 0.4f, 0.2f); // Warna coklat kayu
    glTranslatef(-3.0f, 2.0f, 2.0f); // Posisi panel bawah
    glRotatef(90.0, 0.0, 1.0, 0.0);
    glScalef(1.5f, 1.0f, 0.1f); // Skalakan panel bawah
    glutSolidCube(1.0f);        // Kubus solid untuk panel bawah
    glPopMatrix();

    // Bagian atas pintu (panel kayu atas)
    glPushMatrix();
    glColor3f(0.6f, 0.4f, 0.2f); // Warna coklat kayu
    glTranslatef(-3.0f, 0.8f, 2.0f); // Posisi panel atas
    glRotatef(90.0, 0.0, 1.0, 0.0);
    glScalef(1.5f, 1.5f, 0.1f); // Skalakan panel atas
    glutSolidCube(1.0f);        // Kubus solid untuk panel atas
    glPopMatrix();

    // Jendela pintu (kaca kecil)
    glPushMatrix();
    glColor3f(0.7f, 0.9f, 1.0f); // Warna biru terang untuk kaca
    glTranslatef(-2.9f, 0.5f, 2.0f); // Posisi kaca pada panel atas
    glRotatef(90.0, 0.0, 1.0, 0.0);
    glScalef(1.0f, 0.4f, 0.01f); // Skalakan kaca
    glutSolidCube(1.0f);         // Kubus solid untuk kaca
    glPopMatrix();

    // Pegangan pintu (logam kecil)
    glPushMatrix();
    glColor3f(0.8f, 0.8f, 0.8f); // Warna abu-abu terang untuk logam
    glTranslatef(-2.95f, 1.5f, 1.5f); // Posisi pegangan pada panel bawah
    glScalef(0.05f, 0.5f, 0.04f); // Skalakan pegangan
    glutSolidCube(1.0f);         // Kubus solid untuk pegangan
    glPopMatrix();
}

void drawMinecraftTorch() {
	//Obor Kanan
    // Batang obor (kayu)
    glPushMatrix();
    glColor3f(0.5f, 0.25f, 0.0f); // Warna coklat untuk kayu
    glTranslatef(5.8f, 2.0f, 2.0f); // Posisi batang obor
    glScalef(0.15f, 2.0f, 0.15f);    // Skalakan batang obor
    glutSolidCube(0.5f);           // Kubus solid untuk batang
    glPopMatrix();

    // Tempat obor
    glPushMatrix();
    glColor3f(0.0f, 0.0f, 0.0f);   // Warna oranye
    glTranslatef(5.9f, 2.0f, 2.0f); // Posisi nyala api bagian bawah
    glScalef(1.0f, 0.3f, 0.3f);    // Skalakan api
    glutSolidCube(0.5f);           // Kubus solid untuk api bagian bawah
    glPopMatrix();

    // Nyala api (merah)
    glPushMatrix();
    glColor3f(1.0f, 0.0f, 0.0f);   // Warna merah
    glTranslatef(5.8f, 2.5f, 2.0f); // Posisi nyala api bagian tengah
    glScalef(0.25f, 0.25f, 0.25f);    // Skalakan api
    glutSolidCube(0.5f);           // Kubus solid untuk api bagian tengah
    glPopMatrix();

    // Nyala api (kuning)
    glPushMatrix();
    glColor3f(1.0f, 1.0f, 0.0f);   // Warna kuning
    glTranslatef(5.8f, 2.6f, 2.0f); // Posisi nyala api bagian atas
    glScalef(0.1f, 0.1f, 0.1f);    // Skalakan api
    glutSolidCube(0.5f);           // Kubus solid untuk api bagian atas
    glPopMatrix();
    
    //Obor Kiri
    // Batang obor (kayu)
    glPushMatrix();
    glColor3f(0.5f, 0.25f, 0.0f); // Warna coklat untuk kayu
    glTranslatef(5.8f, 2.0f, -2.0f); // Posisi batang obor
    glScalef(0.15f, 2.0f, 0.15f);    // Skalakan batang obor
    glutSolidCube(0.5f);           // Kubus solid untuk batang
    glPopMatrix();

    // Tempat obor
    glPushMatrix();
    glColor3f(0.0f, 0.0f, 0.0f);   // Warna oranye
    glTranslatef(5.9f, 2.0f, -2.0f); // Posisi nyala api bagian bawah
    glScalef(1.0f, 0.3f, 0.3f);    // Skalakan api
    glutSolidCube(0.5f);           // Kubus solid untuk api bagian bawah
    glPopMatrix();

    // Nyala api (merah)
    glPushMatrix();
    glColor3f(1.0f, 0.0f, 0.0f);   // Warna merah
    glTranslatef(5.8f, 2.5f, -2.0f); // Posisi nyala api bagian tengah
    glScalef(0.25f, 0.25f, 0.25f);    // Skalakan api
    glutSolidCube(0.5f);           // Kubus solid untuk api bagian tengah
    glPopMatrix();

    // Nyala api (kuning)
    glPushMatrix();
    glColor3f(1.0f, 1.0f, 0.0f);   // Warna kuning
    glTranslatef(5.8f, 2.6f, -2.0f); // Posisi nyala api bagian atas
    glScalef(0.1f, 0.1f, 0.1f);    // Skalakan api
    glutSolidCube(0.5f);           // Kubus solid untuk api bagian atas
    glPopMatrix();
}

void drawArmor() {
    GLfloat armorColor[] = { 0.5f, 0.5f, 0.5f }; // Warna abu-abu untuk baju zirah
    glColor3fv(armorColor);

    // Bagian badan (dada)
    glPushMatrix();
    glTranslatef(5.9f, 1.5f, 0.0f); // Posisi pelindung dada
    glRotatef(270.0f, 0.0f, 1.0f, 0.0f);
    glScalef(1.5f, 2.0f, 0.5f);    // Skalakan kubus untuk dada
    glutSolidCube(0.5f);           // Kubus solid untuk pelindung dada
    glPopMatrix();

    // Bahu kanan
    glPushMatrix();
    glTranslatef(5.9f, 2.0f, 0.5f); // Posisi bahu kanan
    glRotatef(270.0f, 0.0f, 1.0f, 0.0f);
    glScalef(1.0f, 0.5f, 0.5f);    // Skalakan kubus untuk bahu kanan
    glutSolidCube(0.5f);           // Kubus solid untuk bahu kanan
    glPopMatrix();

    // Bahu kiri
    glPushMatrix();
    glTranslatef(5.9f, 2.0f, -0.5f); // Posisi bahu kiri
    glRotatef(270.0f, 0.0f, 1.0f, 0.0f);
    glScalef(1.0f, 0.5f, 0.5f);     // Skalakan kubus untuk bahu kiri
    glutSolidCube(0.5f);            // Kubus solid untuk bahu kiri
    glPopMatrix();

    // Helm (kepala)
    glPushMatrix();
    glTranslatef(5.9f, 2.5f, 0.0f); // Posisi helm
    glRotatef(270.0f, 0.0f, 1.0f, 0.0f);
    glScalef(1.1f, 0.7f, 0.5f);    // Skalakan kubus untuk helm
    glutSolidCube(0.5f);           // Kubus solid untuk helm
    glPopMatrix();

    // Detail helm 
    glPushMatrix();
    glColor3f(0.3f, 0.3f, 0.3f);   // Warna visor lebih gelap
    glTranslatef(5.78f, 2.5f, 0.0f); // Posisi visor
    glRotatef(270.0f, 0.0f, 1.0f, 0.0f);
    glScalef(0.7f, 0.3f, 0.1f);    // Skalakan visor
    glutSolidCube(0.5f);           // Kubus solid untuk visor
    glPopMatrix();
    
    // Pelindung pinggang
    glPushMatrix();
    glColor3fv(armorColor); // Kembali ke warna armor
    glTranslatef(5.9f, 0.8f, 0.0f); // Posisi pinggang
    glRotatef(270.0f, 0.0f, 1.0f, 0.0f);
    glScalef(1.7f, 0.5f, 0.6f);    // Skalakan sabuk pelindung
    glutSolidCube(0.5f);           // Kubus solid untuk sabuk
    glPopMatrix();

}

void drawMinecraftSpear() {
	//Tombak 1
    // Warna bagian pegangan tombak (kayu)
    GLfloat woodColor[] = { 1.6f, 0.3f, 0.0f };

    // Warna bagian ujung tombak (logam)
    GLfloat metalColor[] = { 0.8f, 0.8f, 0.8f };

    // Gambar pegangan tombak (silinder panjang)
    glColor3fv(woodColor);
    glPushMatrix();
    glTranslatef(5.9f, 2.3f, 1.2f); // Atur posisi pegangan
    glRotatef(90.0f, 1.0f, 0.0f, 0.0f); // Rotasi untuk membuat silinder tegak
    GLUquadric* quad = gluNewQuadric();
    gluCylinder(quad, 0.03f, 0.03f, 2.0f, 20, 20); // Silinder panjang
    glPopMatrix();

    // Gambar ujung tombak (kerucut)
    glColor3fv(metalColor);
    glPushMatrix();
    glTranslatef(5.9f, 2.3f, 1.2f); // Atur posisi ujung tombak
    glRotatef(270.0f, 1.0f, 0.0f, 0.0f); // Rotasi untuk kerucut menghadap ke atas
    glutSolidCone(0.10f, 0.5f, 20, 20); // Kerucut sebagai ujung tombak
    glPopMatrix();

}

void drawShield() {
    // Warna dasar tameng (kayu)
    glColor3f(0.6f, 0.4f, 0.2f);
    glPushMatrix();
    
    // Bentuk utama tameng
    glTranslatef(-1.3f, 1.5f, -5.9f);
    glRotated(180, 0, 0, 0);
    glScalef(0.5f, 1.0f, 0.2f);
    glutSolidCube(1.0f);
    glPopMatrix();

    // Warna garis pinggir tameng (besi)
    glColor3f(0.7f, 0.7f, 0.7f);
    glRotated(90, 0, 1, 0);
    glLineWidth(5.0f);
    glPushMatrix();
    
    // Bingkai tameng
    glTranslatef(5.9f, 1.5f, -1.3f);
    glRotated(270, 0, 1, 0);
    glScalef(0.5f, 1.0f, 0.2f);
    glutWireCube(1.0f);
    glPopMatrix();
    glLineWidth(1.0f);

    // Tambahan simbol tengah (misalnya salib)
    glColor3f(1.0f, 0.0f, 0.0f); // Warna merah
    glPushMatrix();
    
    // Batang vertikal salib
    glTranslatef(5.8f, 1.5f, -1.3f);
    glRotated(90, 0, 45, 0);
    glScalef(0.1f, 0.6f, 0.05f);
    glutSolidCube(1.0f);
    glPopMatrix();
    glPushMatrix();
    
    // Batang horizontal salib
    glTranslatef(5.8f, 1.5f, -1.3f);
    glRotated(90, 0, 45, 0);
    glScalef(0.4f, 0.1f, 0.05f);
    glutSolidCube(1.0f);
    glPopMatrix();
}

void drawPeti() {
	// Fungsi untuk menggambar peti tengah
    // Badan peti
    glColor3ub(206, 168, 15); // Warna emas untuk peti
    glPushMatrix();
    glRotated(90, 0, 45, 0);
    glTranslatef(5.0f, 0.30f, 0.0f); // Posisi solid cube
    glScalef(1.0f, 0.4f, 2.0f);
    glutSolidCube(1.0f);
    glPopMatrix();

    // Garis pembungkus solid cube
    glColor3f(0.0f, 0.0f, 0.0f); // Warna hitam untuk garis
    glLineWidth(10.0f); // Ketebalan garis
    glPushMatrix();
    glRotated(90, 0, 45, 0);
    glTranslatef(5.0f, 0.31f, 0.0f); // Posisi sedikit diangkat agar tidak menyatu dengan solid cube
    glScalef(1.0f, 0.4f, 2.0f);
    glutWireCube(1.0f);
    glPopMatrix();
    glLineWidth(1.0f); // Mengembalikan ketebalan garis ke default

    // Kotak putih di atas peti
    glColor3ub(255, 255, 255); // Warna putih
    glPushMatrix();
    glRotated(90, 0, 45, 0);
    glTranslatef(4.50f, 0.50f, 0.0f); // Posisi kotak putih
    glScalef(0.1f, 0.1f, 0.1f);
    glutSolidCube(1.0f);
    glPopMatrix();

    // Tutup peti
    glColor3ub(206, 168, 15); // Warna emas untuk tutup
    glPushMatrix();
    glRotated(90, 0, 45, 0);
    glTranslatef(5.0f, 0.6f, -1.0f); // Posisi awal tutup peti (pivot di belakang)
    glRotatef(tutupAngle, 0.0f, 0.0f, -1.0f); // Rotasi membuka/menutup ke atas (sumbu Z)
    glTranslatef(0.0f, 0.0f, 1.0f); // Geser kembali tutup peti ke tempatnya
    glScalef(1.0f, 0.2f, 2.0f);
    glutSolidCube(1.0f);
    glPopMatrix();

    // Garis pembungkus tutup peti
    glColor3f(0.0f, 0.0f, 0.0f); // Warna hitam untuk garis tutup
    glLineWidth(10.0f);
    glPushMatrix();
    glRotated(90, 0, 45, 0);
    glTranslatef(5.0f, 0.61f, -1.0f); // Posisi awal tutup peti (pivot di belakang)
    glRotatef(tutupAngle, 0.0f, 0.0f, -1.0f); // Rotasi membuka/menutup ke atas (sumbu Z)
    glTranslatef(0.0f, 0.0f, 1.0f); // Geser kembali tutup peti ke tempatnya
    glScalef(1.0f, 0.2f, 2.0f);
    glutWireCube(1.0f);
    glPopMatrix();
    glLineWidth(1.0f); // Mengembalikan ketebalan garis ke default
}

void Cartecius()
{
	glBegin(GL_LINES);
	
	glVertex3f(-100.0, 1.5, 0.0);
	glColor3f(1.0, 0.0, 0.0);
	glVertex3f(100.0, 1.5, 0.0);
	
	glVertex3f(0.0, -100.0, 0.0);
	glColor3f(0.0, 1.0, 0.0);
	glVertex3f(0.0, 100.0, 0.0);
	
	glVertex3f(0.0, 1.5, -100.0);
	glColor3f(0.0, 0.0, 1.0);
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

void drawPetikiri() {
	glPushMatrix();
	glTranslatef(0.0f, 0.0f, 0.0f);
	
	//Peti tingkat di sebelah kiri 
    // Peti
    glColor3ub(206, 168, 15);
    glPushMatrix();
    glTranslatef(-2.45f, 0.30f, -3.0f);
    glScalef(1.0f, 0.4f, 2.0f);
    glutSolidCube(1.0f);
    glPopMatrix();
    
    //wire peti
    glColor3f(0.0f, 0.0f, 0.0f);
	glLineWidth(10.0f); // Menetapkan ketebalan garis menjadi 3 piksel
	glPushMatrix();
	glTranslatef(-2.45f, 0.30f, -3.0f);
	glScalef(1.0f, 0.4f, 2.0f);
	glutWireCube(1.0f);
	glPopMatrix();
	glLineWidth(1.0f); // Mengembalikan ketebalan garis ke default
	
	//button
	glColor3ub(255, 255, 255);
    glPushMatrix();
    glTranslatef(-1.95f, 0.50f, -3.0f);
    glScalef(0.1f, 0.1f, 0.1f);
    glutSolidCube(1.0f);
    glPopMatrix();
    
    //========== tingkat 2 =========
    //peti
    glColor3ub(206, 168, 15);
    glPushMatrix();
    glTranslatef(-2.45f, 1.0f, -3.0f);
    glScalef(1.0f, 0.4f, 2.0f);
    glutSolidCube(1.0f);
    glPopMatrix();
    
    //tutup
    glColor3f(0.0f, 0.0f, 0.0f);
	glLineWidth(10.0f); // Menetapkan ketebalan garis menjadi 3 piksel
	glPushMatrix();
	glTranslatef(-2.45f, 1.0f, -3.0f);
	glScalef(1.0f, 0.4f, 2.0f);
	glutWireCube(1.0f);
	glPopMatrix();
	glLineWidth(1.0f); // Mengembalikan ketebalan garis ke default
	
	//button
	glColor3ub(255, 255, 255);
    glPushMatrix();
    glTranslatef(-1.95f, 1.20f, -3.0f);
    glScalef(0.1f, 0.1f, 0.1f);
    glutSolidCube(1.0f);
    glPopMatrix();

    // Tutup
    glColor3ub(206, 168, 15);
    glPushMatrix();
    glTranslatef(-2.45f, 0.6f, -3.0f);
    glScalef(1.0f, 0.2f, 2.0f);
    glutSolidCube(1.0f);
    glPopMatrix();
    
    glColor3f(0.0f, 0.0f, 0.0f);
    glLineWidth(10.0f);
    glPushMatrix();
    glTranslatef(-2.45f, 0.6f, -3.0f);
    glScalef(1.0f, 0.2f, 2.0f);
    glutWireCube(1.0f);
    glPopMatrix();
    glLineWidth(1.0f);
    
    //tingkat 2
    glColor3ub(206, 168, 15);
    glPushMatrix();
    glTranslatef(-2.45f, 1.3f, -3.0f);
    glScalef(1.0f, 0.2f, 2.0f);
    glutSolidCube(1.0f);
    glPopMatrix();
    
    glColor3f(0.0f, 0.0f, 0.0f);
    glLineWidth(10.0f);
    glPushMatrix();
    glTranslatef(-2.45f, 1.3f, -3.0f);
    glScalef(1.0f, 0.2f, 2.0f);
    glutWireCube(1.0f);
    glPopMatrix();
    glLineWidth(1.0f);

    glPopMatrix();
}

void drawPetikanan() {
	glPushMatrix();
	glTranslatef(4.9f, 0.0f, 0.0f);
	
	//Peti tingkat di sebelah kanan
    // Peti
    glColor3ub(206, 168, 15);
    glPushMatrix();
    glTranslatef(-2.45f, 0.30f, -3.0f);
    glScalef(1.0f, 0.4f, 2.0f);
    glutSolidCube(1.0f);
    glPopMatrix();
    
    //wire peti
    glColor3f(0.0f, 0.0f, 0.0f);
	glLineWidth(10.0f); // Menetapkan ketebalan garis menjadi 3 piksel
	glPushMatrix();
	glTranslatef(-2.45f, 0.30f, -3.0f);
	glScalef(1.0f, 0.4f, 2.0f);
	glutWireCube(1.0f);
	glPopMatrix();
	glLineWidth(1.0f); // Mengembalikan ketebalan garis ke default
	
	//button
	glColor3ub(255, 255, 255);
    glPushMatrix();
    glTranslatef(-2.95f, 0.50f, -3.0f);
    glScalef(0.1f, 0.1f, 0.1f);
    glutSolidCube(1.0f);
    glPopMatrix();
    
    //========== tingkat 2 =========
    //peti
    glColor3ub(206, 168, 15);
    glPushMatrix();
    glTranslatef(-2.45f, 1.0f, -3.0f);
    glScalef(1.0f, 0.4f, 2.0f);
    glutSolidCube(1.0f);
    glPopMatrix();
    
    //tutup
    glColor3f(0.0f, 0.0f, 0.0f);
	glLineWidth(10.0f); // Menetapkan ketebalan garis menjadi 3 piksel
	glPushMatrix();
	glTranslatef(-2.45f, 1.0f, -3.0f);
	glScalef(1.0f, 0.4f, 2.0f);
	glutWireCube(1.0f);
	glPopMatrix();
	glLineWidth(1.0f); // Mengembalikan ketebalan garis ke default
	
	//button
	glColor3ub(255, 255, 255);
    glPushMatrix();
    glTranslatef(-2.95f, 1.20f, -3.0f);
    glScalef(0.1f, 0.1f, 0.1f);
    glutSolidCube(1.0f);
    glPopMatrix();

    // Tutup
    glColor3ub(206, 168, 15);
    glPushMatrix();
    glTranslatef(-2.45f, 0.6f, -3.0f);
    glScalef(1.0f, 0.2f, 2.0f);
    glutSolidCube(1.0f);
    glPopMatrix();
    
    glColor3f(0.0f, 0.0f, 0.0f);
    glLineWidth(10.0f);
    glPushMatrix();
    glTranslatef(-2.45f, 0.6f, -3.0f);
    glScalef(1.0f, 0.2f, 2.0f);
    glutWireCube(1.0f);
    glPopMatrix();
    glLineWidth(1.0f);
    
    //tingkat 2
    glColor3ub(206, 168, 15);
    glPushMatrix();
    glTranslatef(-2.45f, 1.3f, -3.0f);
    glScalef(1.0f, 0.2f, 2.0f);
    glutSolidCube(1.0f);
    glPopMatrix();
    
    glColor3f(0.0f, 0.0f, 0.0f);
    glLineWidth(10.0f);
    glPushMatrix();
    glTranslatef(-2.45f, 1.3f, -3.0f);
    glScalef(1.0f, 0.2f, 2.0f);
    glutWireCube(1.0f);
    glPopMatrix();
    glLineWidth(1.0f);

    glPopMatrix();
}

void drawRak1() {
    glPushMatrix();
    glTranslatef(1.75f, 0.0f, 2.4f);
    
    // Permukaan bawah
    glColor3f(0.2f, 0.2f, 0.2f);
    glPushMatrix();
    glTranslatef(-4.25f, 0.0f, -2.0f);
    glScalef(1.0f, 0.1f, 3.0f);
    glutSolidCube(1.0f);
    glPopMatrix();
    
    // Permukaan tengah
    glColor3f(0.2f, 0.2f, 0.2f);
    glPushMatrix();
    glTranslatef(-4.25f, 1.5f, -2.0f);
    glScalef(1.0f, 0.1f, 3.0f);
    glutSolidCube(1.0f);
    glPopMatrix();
    
    // Permukaan atas
    glColor3f(0.2f, 0.2f, 0.2f);
    glPushMatrix();
    glTranslatef(-4.25f, 3.0f, -2.0f);
    glScalef(1.0f, 0.1f, 3.0f);
    glutSolidCube(1.0f);
    glPopMatrix();

    // Kaki-kaki meja
    glPushMatrix();
    glTranslatef(-4.5f, 0.4f, -0.6f);
    glScalef(0.1f, 5.0f, 0.1f);
    glutSolidCube(1.0f);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-4.0f, 0.4f, -0.6f);
    glScalef(0.1f, 5.0f, 0.1f);
    glutSolidCube(1.0f);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-4.5f, 0.375f, -3.4f);
    glScalef(0.1f, 5.0f, 0.1f);
    glutSolidCube(1.0f);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-4.0f, 0.375f, -3.4f);
    glScalef(0.1f, 5.0f, 0.1f);
    glutSolidCube(1.0f);
    glPopMatrix();
    
    glPopMatrix();
}

void drawRak2() {
    glPushMatrix();
    glTranslatef(1.5f, 0.0f, -1.8f);
    glRotatef(90.0, 0.0, 1.0, 0.0);
    
    // Permukaan bawah
    glColor3f(0.2f, 0.2f, 0.2f);
    glPushMatrix();
    glTranslatef(-4.25f, 0.0f, -2.0f);
    glScalef(1.0f, 0.1f, 3.0f);
    glutSolidCube(1.0f);
    glPopMatrix();
    
    // Permukaan tengah
    glColor3f(0.2f, 0.2f, 0.2f);
    glPushMatrix();
    glTranslatef(-4.25f, 1.5f, -2.0f);
    glScalef(1.0f, 0.1f, 3.0f);
    glutSolidCube(1.0f);
    glPopMatrix();
    
    // Permukaan atas
    glColor3f(0.2f, 0.2f, 0.2f);
    glPushMatrix();
    glTranslatef(-4.25f, 3.0f, -2.0f);
    glScalef(1.0f, 0.1f, 3.0f);
    glutSolidCube(1.0f);
    glPopMatrix();

    // Kaki-kaki meja
    glPushMatrix();
    glTranslatef(-4.5f, 0.4f, -0.6f);
    glScalef(0.1f, 5.0f, 0.1f);
    glutSolidCube(1.0f);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-4.0f, 0.4f, -0.6f);
    glScalef(0.1f, 5.0f, 0.1f);
    glutSolidCube(1.0f);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-4.5f, 0.375f, -3.4f);
    glScalef(0.1f, 5.0f, 0.1f);
    glutSolidCube(1.0f);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-4.0f, 0.375f, -3.4f);
    glScalef(0.1f, 5.0f, 0.1f);
    glutSolidCube(1.0f);
    glPopMatrix();
    
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
    glVertex3f(-3.0f, 0.0f, -6.0f);
    glVertex3f(-3.0f, 0.0f, 3.0f);
    glVertex3f(3.0f, 0.0f, 3.0f);
    glVertex3f(3.0f, 0.0f, -6.0f);
	glEnd();

	// Gambar garis-garis horizontal
	glColor3f(0.3f, 0.2f, 0.1f);  // Warna garis lebih gelap untuk kontras
	for (float x = -3.0f; x <= 3.0f; x += 0.5f) {
    	glBegin(GL_LINES);
        	glVertex3f(x, 0.0f, -6.0f);
        	glVertex3f(x, 0.0f, 3.0f);
    	glEnd();
	}

	// Gambar garis-garis vertikal
	for (float z = -6.0f; z <= 3.0f; z += 0.5f) {
    	glBegin(GL_LINES);
        	glVertex3f(-3.0f, 0.0f, z);
        	glVertex3f(3.0f, 0.0f, z);
    	glEnd();
	}

    //========= Ceiling =========
    // Gambar permukaan (Quad)
	glColor3f(0.8f, 0.6f, 0.3f);  // Warna kayu Minecraft yang lebih muda
	glBegin(GL_QUADS);
    glVertex3f(-3.0f, 3.0f, -6.0f);
    glVertex3f(-3.0f, 3.0f, 3.0f);
    glVertex3f(3.0f, 3.0f, 3.0f);
    glVertex3f(3.0f, 3.0f, -6.0f);
	glEnd();

	// Gambar garis-garis horizontal
	glColor3f(0.3f, 0.2f, 0.1f);  // Warna garis lebih gelap untuk kontras
	for (float x = -3.0f; x <= 3.0f; x += 0.5f) {
    	glBegin(GL_LINES);
        	glVertex3f(x, 3.0f, -6.0f);
        	glVertex3f(x, 3.0f, 3.0f);
    	glEnd();
	}

	// Gambar garis-garis vertikal
	for (float z = -6.0f; z <= 3.0f; z += 0.5f) {
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
    glVertex3f(-3.0f, 0.0f, -6.0f);
    glVertex3f(-3.0f, 3.0f, -6.0f);
    glVertex3f(3.0f, 3.0f, -6.0f);
    glVertex3f(3.0f, 0.0f, -6.0f);
	glEnd();

	// Gambar garis-garis horizontal
	glColor3f(0.3f, 0.2f, 0.1f);  // Warna garis lebih gelap untuk kontras
	for (float x = -3.0f; x <= 3.0f; x += 0.5f) {
    	glBegin(GL_LINES);
        	glVertex3f(x, 0.0f, -6.0f);
        	glVertex3f(x, 3.0f, -6.0f);
    	glEnd();
	}

	// Gambar garis-garis vertikal
	for (float y = 0.0f; y <= 3.0f; y += 0.5f) {
    	glBegin(GL_LINES);
        	glVertex3f(-3.0f, y, -6.0f);
        	glVertex3f(3.0f, y, -6.0f);
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
    glVertex3f(-3.0f, 0.0f, -6.0f);
    glVertex3f(-3.0f, 3.0f, -6.0f);
    glVertex3f(-3.0f, 3.0f, 3.0f);
    glVertex3f(-3.0f, 0.0f, 3.0f);
	glEnd();

	// Gambar garis-garis horizontal
	glColor3f(0.3f, 0.2f, 0.1f);  // Warna garis lebih gelap untuk kontras
	for (float y = 0.0f; y <= 3.0f; y += 0.5f) {
    	glBegin(GL_LINES);
        	glVertex3f(-3.0f, y, -6.0f);
        	glVertex3f(-3.0f, y, 3.0f);
    	glEnd();
	}

	// Gambar garis-garis vertikal
	for (float z = -6.0f; z <= 3.0f; z += 0.5f) {
    	glBegin(GL_LINES);
        	glVertex3f(-3.0f, 0.0f, z);
        	glVertex3f(-3.0f, 3.0f, z);
   		glEnd();
	}

    // Right wall
    // Gambar permukaan (Quad)
	glColor3f(0.8f, 0.6f, 0.3f);  // Warna kayu Minecraft yang lebih muda
	glBegin(GL_QUADS);
    glVertex3f(3.0f, 0.0f, -6.0f);
    glVertex3f(3.0f, 3.0f, -6.0f);
    glVertex3f(3.0f, 3.0f, 3.0f);
    glVertex3f(3.0f, 0.0f, 3.0f);
	glEnd();

	// Gambar garis-garis horizontal
	glColor3f(0.3f, 0.2f, 0.1f);  // Warna garis lebih gelap untuk kontras
	for (float y = 0.0f; y <= 3.0f; y += 0.5f) {
    	glBegin(GL_LINES);
        	glVertex3f(3.0f, y, -6.0f);
        	glVertex3f(3.0f, y, 3.0f);
    	glEnd();
	}

	// Gambar garis-garis vertikal
	for (float z = -6.0f; z <= 3.0f; z += 0.5f) {
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
    drawPetikiri();
    drawPetikanan();
    hiddenCarte();
    drawPeti();
    drawRak1();
    drawRak2();
    drawShield();
    drawMinecraftSpear();
    drawMinecraftTorch();
    drawArmor();
    drawMinecraftDoor();
    
    
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
		case 'h':
			if (tutupAngle < 45.0f) { // Batas rotasi maksimal 
                tutupAngle += 5.0f;
            }
            break;
        case 'j':
        	if (tutupAngle > 0.0f) { // Batas rotasi minimal
                tutupAngle -= 5.0f;
            }
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
