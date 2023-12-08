#include <gl/glut.h>
#include <math.h>

GLdouble smokePos = 0.0;//smoke postion delta
GLdouble smokeRadius1 = 0.01;
GLdouble smokeRadius2 = 0.015;
GLdouble smokeRadius3 = 0.02;
GLdouble carPos = 0.0;//car postion delta
GLdouble thetaX = 0.5;
GLdouble thetaY = 0;
GLdouble thetaSun = 0;
GLdouble distance = 1;
bool forward = true;//if car is moving forward
bool rotate = true;//if the camera is spinning
GLdouble cloudX = 0.0; // 控制云朵X轴位置的全局变量
GLdouble theta = 0;
GLfloat P = 0.1; //Pixel cube size

//press F1 to pause and play
void specialKeys(int key, int x, int y) {
	if (key == GLUT_KEY_F1) {
		rotate = true;//
	}
	if (key == GLUT_KEY_F2) {
		rotate = false;//
	}
	if (key == GLUT_KEY_UP) {
		rotate = false;
		thetaY -= 0.01;//
	}
	if (key == GLUT_KEY_DOWN) {
		rotate = false;
		thetaY += 0.01;
	}
	if (key == GLUT_KEY_LEFT) {
		rotate = false;
		thetaX += 0.01;
	}
	if (key == GLUT_KEY_RIGHT) {
		rotate = false;
		thetaX -= 0.01;
	}

	glutPostRedisplay();
}


void idle() {
	//idle function
	smokePos += 0.00005;
	smokeRadius1 += 0.00002;
	smokeRadius2 += 0.00002;
	smokeRadius3 += 0.00002;
	thetaSun += 0.00005;
	if (rotate) {
		thetaX += 0.0001;
	}
	if ((carPos > -1.5) && forward) {
		carPos -= 0.0005;
	}
	else if (carPos < 0.0) {
		carPos += 0.0005;
		forward = false;
	}
	else {
		forward = true;
	}
	// 更新云朵的位置
	theta += 0.0005;
	cloudX = sin(theta) * 0.5;
	glutPostRedisplay();
}

void visual3D() {
	//Visualise a 3D axis
	glColor3f(1.0, 0.0, 0.0);
	glBegin(GL_LINES);
	glVertex3f(0, 0, 0);
	glVertex3f(2, 0, 0);
	glVertex3f(0, 0, 0);
	glVertex3f(0, 2, 0);
	glVertex3f(0, 0, 0);
	glVertex3f(0, 0, 2);
	glEnd();
}

// 字母 'M' 的像素模式
bool M[5][5] = {
	{1, 1, 1, 1, 1},
	{0, 1, 0, 0, 0},
	{0, 0, 1, 0, 0},
	{0, 1, 0, 0, 0},
	{1, 1, 1, 1, 1}
};

// 字母 'I' 的像素模式
bool I[5][5] = {
	{1, 0, 0, 0, 1},
	{1, 0, 0, 0, 1},
	{1, 1, 1, 1, 1},
	{1, 0, 0, 0, 1},
	{1, 0, 0, 0, 1}
};

// 字符 'N' 的像素模式
bool N[5][5] = {
	{1, 1, 1, 1, 1},
	{0, 1, 0, 0, 0},
	{0, 0, 1, 0, 0},
	{0, 0, 0, 1, 0},
	{1, 1, 1, 1, 1}
};

// 字符 'G' 的像素模式
bool G[5][5] = {
	{0, 1, 1, 1, 0},
	{1, 0, 0, 0, 1},
	{1, 0, 1, 0, 1},
	{1, 0, 1, 0, 1},
	{0, 0, 1, 1, 0}
};

// 字母 'H' 的像素模式
bool H[5][5] = {
	{1, 1, 1, 1, 1},
	{0, 0, 1, 0, 0},
	{0, 0, 1, 0, 0},
	{0, 0, 1, 0, 0},
	{1, 1, 1, 1, 1}
};

// 字母 'A' 的像素模式
bool A[5][5] = {
	{0, 1, 1, 1, 1},
	{1, 0, 1, 0, 0},
	{1, 0, 1, 0, 0},
	{1, 0, 1, 0, 0},
	{0, 1, 1, 1, 1}
};

// 字母 'O' 的像素模式
bool O[5][5] = {
	{0, 1, 1, 1, 0},
	{1, 0, 0, 0, 1},
	{1, 0, 0, 0, 1},
	{1, 0, 0, 0, 1},
	{0, 1, 1, 1, 0}
};

// 绘制一个像素化的字符
void drawPixelatedChar(char c, GLfloat x, GLfloat y, GLfloat z, GLfloat size) {
	bool(*pattern)[5];

	switch (c) {
	case 'M': pattern = M; break;
	case 'I': pattern = I; break;
	case 'N': pattern = N; break;
	case 'G': pattern = G; break;
	case 'H': pattern = H; break;
	case 'A': pattern = A; break;
	case 'O': pattern = O; break;
	default: return; // 如果字符未定义，不绘制
	}

	for (int i = 0; i < 5; ++i) {
		for (int j = 0; j < 5; ++j) {
			if (pattern[i][j]) {
				glPushMatrix();
				glTranslated(x + i * size, 0, z + j * size);
				glutSolidCube(size);
				glPopMatrix();
			}
		}
	}
}

// 绘制一个像素化的字符串
void drawPixelatedString(const char* text, GLfloat x, GLfloat y, GLfloat z, GLfloat size) {
	const char* c = text;
	while (*c != '\0') {
		drawPixelatedChar(*c, x, y, z, size);
		x += 6 * size; // 为下一个字符向右移动
		c++;
	}
}

void oneCube(GLfloat x, GLfloat y, GLfloat z, GLfloat L) {
	glPushMatrix();
	glTranslated(x, y, z);
	glutSolidCube(L);
	glPopMatrix();
}

void drawCloud(GLfloat dx, GLfloat dy, GLfloat dz) {
	GLfloat cloud[][2] = { {-0.1, 0.3}, {0.0, 0.3}, {0.1, 0.3}, {-0.3, 0.2}, {-0.2, 0.2}, {-0.1, 0.2}, {0.0, 0.2}, {0.1, 0.2}, {0.2, 0.2}, {-0.4, 0.1}, {-0.3, 0.1}, {-0.2, 0.1}, {-0.1, 0.1}, {0.0, 0.1}, {0.1, 0.1}, {0.2, 0.1}, {-0.4, 0.0}, {-0.3, 0.0}, {-0.2, 0.0}, {-0.1, 0.0}, {0.0, 0.0}, {0.1, 0.0}, {0.2, 0.0}, {0.3, 0.0}, {-0.2, -0.1}, {-0.1, -0.1}, {0.0, -0.1}, {0.1, -0.1} };
	GLfloat cloudLayer2[][2] = { {-0.1, 0.2}, {0.0, 0.2},{-0.3, 0.1}, {-0.2, 0.1}, {-0.1, 0.1}, {0.0, 0.1}, {0.1, 0.1}, {-0.3, 0.0}, {-0.2, 0.0}, {-0.1, 0.0}, {0.0, 0.0}, {0.1, 0.0} };
	GLfloat cloudLayer3[][2] = { {-0.1, 0.1}, {0.0, 0.1}, {-0.1, 0.0}, {0.0, 0.0} };
	GLfloat no_mat[] = { 0.0, 0.0, 0.0, 1.0 };
	GLfloat mat_ambient[] = { 0.7, 0.7, 0.7, 1.0 };
	GLfloat mat_ambient_color[] = { 0.8, 0.8, 0.2, 1.0 };
	GLfloat mat_diffuse[] = { 0.1, 0.5, 0.8, 1.0 };
	GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat no_shininess[] = { 0.0 };
	GLfloat low_shininess[] = { 5.0 };
	GLfloat high_shininess[] = { 100.0 };
	GLfloat mat_emission[] = { 0.3, 0.2, 0.2, 0.0 };

	glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient_color);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, no_mat);
	glMaterialfv(GL_FRONT, GL_SHININESS, no_shininess);
	glMaterialfv(GL_FRONT, GL_EMISSION, mat_emission);

	

	//Draw cloud
	for (int i = 0; i < sizeof(cloud) / sizeof(cloud[0]); i++) {
		glColor3f(0.0, 1.0, 1.0);
		oneCube(cloud[i][0] + dx + cloudX, cloud[i][1] + dy, dz, P);
		if (i < sizeof(cloudLayer2) / sizeof(cloudLayer2[0]))
			oneCube(cloudLayer2[i][0] + dx + cloudX, cloudLayer2[i][1] + dy, dz - P, P);
		oneCube(cloudLayer2[i][0] + dx + cloudX, cloudLayer2[i][1] + dy, dz - P, P);
		if (i < sizeof(cloudLayer3) / sizeof(cloudLayer3[0]))
			oneCube(cloudLayer3[i][0] + dx + cloudX, cloudLayer3[i][1] + dy, dz - 2 * P, P);
	}
	//Draw eyes
	glColor3f(0.0, 0.0, 0.0);
	oneCube(-0.2 + dx + cloudX, 0.12 + dy, dz + P * 0.5, P * 0.3);
	oneCube(0.1 + dx + cloudX, 0.12 + dy, dz + P * 0.5, P * 0.3);

	//Draw mouth
	for (int i = 0; i < 7; i++) {
		float theta = 2.0f * 3.1415926f * float(i + 9) / float(15);
		float x = 0.06 * cosf(theta);
		float y = 0.06 * sinf(theta);
		oneCube(x + dx + cloudX, y + dy, dz + P * 0.5, P * 0.2);
	}
}

void drawWall() {
	//wall of the house
	glPushMatrix();
	glColor3f(0.8, 0.8, 0.8);
	glutSolidCube(1);
	glPopMatrix();
}

void drawRoof() {
	//roof
	glPushMatrix();
	glTranslated(0, 0.5, 0);
	glRotated(90, -90, 0, 0);
	glColor3f(1, 0.2, 0);
	glutSolidCone(0.8, 1.2, 50, 50);
	glPopMatrix();
}

void drawDoor() {
	glPushMatrix();
	glTranslated(0, 0, 0.51);
	glColor3f(0.5, 0.5, 0.1);
	//door
	glBegin(GL_POLYGON);
	glVertex2f(0.1, 0.2);
	glVertex2f(0.4, 0.2);
	glVertex2f(0.4, -0.5);
	glVertex2f(0.1, -0.5);
	glEnd();

}



void drawChimney() {
	//chimney
	glPushMatrix();
	glTranslated(0.4, 1.05, 0.0);
	glColor3f(0.9, 0.4, 0);
	glutSolidCube(0.2);
	glPopMatrix();
	glPushMatrix();
	glTranslated(0.4, 1.25, 0.0);
	glutSolidCube(0.2);
	glPopMatrix();
}

void drawFloor() {
	//floor
	glPushMatrix();
	glColor3f(0, 0.8, 0);
	glRotated(90, 90, 0, 0);
	glTranslated(0.0, 0.0, 0.5);
	glBegin(GL_POLYGON);
	glVertex2f(3.0, 3.0);
	glVertex2f(-3.0, 3.0);
	glVertex2f(-3.0, -3.0);
	glVertex2f(3.0, -3.0);
	glEnd();
	glPopMatrix();
}

void drawTree(GLdouble x, GLdouble y) {
	glPushMatrix();
	glTranslated(x, 0.35, y);
	glRotated(90, -90, 0, 0);
	glColor3f(0, 0.8, 0);
	glutSolidCone(0.2, 0.2, 50, 50);
	glPopMatrix();

	glPushMatrix();
	glTranslated(x, 0, y);
	glRotated(90, -90, 0, 0);
	glColor3f(0, 0.8, 0);
	glutSolidCone(0.5, 0.4, 50, 50);
	glPopMatrix();

	for (int i = 0; i <= 10; i++) {
		glPushMatrix();
		glTranslated(x, -0.5 + 0.05 * i, y);
		glRotated(90, -90, 0, 0);
		glColor3f(1, 0.2, 0);
		glutSolidCube(0.1);
		glPopMatrix();
	}
}

void drawFence() {
	//fence
	glBegin(GL_POLYGON);
	glColor3f(1.0, 0.5, 0);
	glVertex3f(1.0, -0.2, 1);
	glVertex3f(1.0, -0.3, 1);
	glVertex3f(0, -0.3, 1);
	glVertex3f(0, -0.2, 1);
	glEnd();

	glBegin(GL_POLYGON);
	glVertex3f(-1, -0.2, 1);
	glVertex3f(-1, -0.3, 1);
	glVertex3f(-0.5, -0.3, 1);
	glVertex3f(-0.5, -0.2, 1);
	glEnd();

	for (int i = 0; i <= 10; i++) {
		glBegin(GL_POLYGON);
		glVertex3f(1.0 - 2 * i * 0.05, 0, 1);
		glVertex3f(1.0 - 2 * i * 0.05, -0.5, 1);
		glVertex3f(1.0 - 2 * i * 0.05 + 0.05, -0.5, 1);
		glVertex3f(1.0 - 2 * i * 0.05 + 0.05, 0, 1);
		glEnd();
	}

	for (int i = 15; i <= 20; i++) {
		glBegin(GL_POLYGON);
		glVertex3f(1.0 - 2 * i * 0.05, 0, 1);
		glVertex3f(1.0 - 2 * i * 0.05, -0.5, 1);
		glVertex3f(1.0 - 2 * i * 0.05 + 0.05, -0.5, 1);
		glVertex3f(1.0 - 2 * i * 0.05 + 0.05, 0, 1);
		glEnd();
	}

	glBegin(GL_POLYGON);
	glVertex3f(1.0, -0.2, -1);
	glVertex3f(1.0, -0.3, -1);
	glVertex3f(-1.0, -0.3, -1);
	glVertex3f(-1.0, -0.2, -1);
	glEnd();

	for (int i = 0; i <= 20; i++) {
		glBegin(GL_POLYGON);
		glVertex3f(1.0 - 2 * i * 0.05, 0, -1);
		glVertex3f(1.0 - 2 * i * 0.05, -0.5, -1);
		glVertex3f(1.0 - 2 * i * 0.05 + 0.05, -0.5, -1);
		glVertex3f(1.0 - 2 * i * 0.05 + 0.05, 0, -1);
		glEnd();
	}

	glBegin(GL_POLYGON);
	glVertex3f(1.0, -0.2, 1);
	glVertex3f(1.0, -0.3, 1);
	glVertex3f(1.0, -0.3, -1);
	glVertex3f(1.0, -0.2, -1);
	glEnd();

	for (int i = 0; i <= 20; i++) {
		glBegin(GL_POLYGON);
		glVertex3f(1.0, 0, 1 - 2 * i * 0.05);
		glVertex3f(1.0, -0.5, 1 - 2 * i * 0.05);
		glVertex3f(1.0, -0.5, 1 - 2 * i * 0.05 + 0.05);
		glVertex3f(1.0, 0, 1 - 2 * i * 0.05 + 0.05);
		glEnd();
	}

	glBegin(GL_POLYGON);
	glVertex3f(-1.0, -0.2, 1);
	glVertex3f(-1.0, -0.3, 1);
	glVertex3f(-1.0, -0.3, -1);
	glVertex3f(-1.0, -0.2, -1);
	glEnd();

	for (int i = 0; i <= 20; i++) {
		glBegin(GL_POLYGON);
		glVertex3f(-1.0, 0, 1 - 2 * i * 0.05);
		glVertex3f(-1.0, -0.5, 1 - 2 * i * 0.05);
		glVertex3f(-1.0, -0.5, 1 - 2 * i * 0.05 + 0.05);
		glVertex3f(-1.0, 0, 1 - 2 * i * 0.05 + 0.05);
		glEnd();
	}
}

void drawWindow(GLdouble point1x, GLdouble point2x, GLdouble point1y, GLdouble point2y, GLdouble z) {
	//window
	glBegin(GL_POLYGON);
	glColor3f(0, 0.8, 1.0);
	glVertex3f(point1x, point1y, z);
	glVertex3f(point1x, point2y, z);
	glVertex3f(point2x, point2y, z);
	glVertex3f(point2x, point1y, z);
	glEnd();
	glPopMatrix();
}

void drawCarBody(GLdouble x, GLdouble y, GLdouble z) {
	glPushMatrix();
	glTranslated((x + carPos), y, z);
	glutSolidCube(0.3);
	glPopMatrix();
}

void drawCarWheel(GLdouble x, GLdouble y, GLdouble z) {
	glPushMatrix();
	glTranslated((x + carPos), y, z);
	glRotated(0.0, 1.0, 0.0, 0.0);
	glutSolidTorus(0.03, 0.07, 10, 10);
	glPopMatrix();
}

void drawCarWindow(GLdouble x, GLdouble y, GLdouble z) {
	glPushMatrix();
	glTranslated((x + carPos), y, 0);
	drawWindow(-0.1, 0.1, -0.1, 0.1, z);
	glPopMatrix();
}

void drawCar() {

	//car body
	glColor3f(1.0, 1.0, 0.0);
	drawCarBody(1.0, 0.1, 1.4);
	drawCarBody(0.7, 0.1, 1.4);
	drawCarBody(1.2, -0.2, 1.4);
	drawCarBody(0.9, -0.2, 1.4);
	drawCarBody(0.6, -0.2, 1.4);

	//car windows
	drawCarWindow(1.0, 0.1, 1.56);
	drawCarWindow(0.7, 0.1, 1.56);
	drawCarWindow(1.0, 0.1, 1.24);
	drawCarWindow(0.7, 0.1, 1.24);

	//Four Wheels
	glColor3f(0.0, 0.0, 0.0);
	drawCarWheel(1.15, -0.4, 1.3);
	drawCarWheel(1.15, -0.4, 1.5);
	drawCarWheel(0.65, -0.4, 1.3);
	drawCarWheel(0.65, -0.4, 1.5);
}

void drawSmoke(GLdouble x_pos, GLdouble y_pos, GLdouble smokeRadius,
	GLdouble x_ext, GLdouble y_ext) {
	glPushMatrix();
	glColor3f(0.6, 0.6, 0.6);
	glTranslated((x_pos + smokePos), (y_pos + smokePos / 5), 0.0);
	glRotated(100, 1.0, -0.3, 0.0);
	glutSolidTorus((smokeRadius + x_ext), (smokeRadius + y_ext), 30, 30);

	glPopMatrix();
}

void smokeReposition() {
	smokePos = 0.0;
	smokeRadius1 = 0.01;
	smokeRadius2 = 0.015;
	smokeRadius3 = 0.02;
}
void drawSun(GLdouble r, GLdouble radius) {
	glPushMatrix();
	glColor3f(1.0, 0.8, 0);
	glTranslated(-r * cos(thetaSun), r * sin(thetaSun), -3.0);
	glutSolidSphere(radius, 50, 50);
	glPopMatrix();
}

void sunReposition() {
	thetaSun = 0;
}

void display() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	//gluLookAt(1, 0.4, 2.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
	gluLookAt(3 * cos(thetaX), distance, 3 * sin(thetaX), 0, thetaY, 0, 0.0, 1.0, 0.0);

	//visual3D();//axis
	glColor3f(1.0, 1.0, 1.0); // 设置白色
	drawPixelatedString("MINGHAO", -2.0, 2.0, 3.0, P); // 在适当的位置绘制
	drawWall();
	drawRoof();
	drawDoor();
	drawWindow(-0.4, -0.2, 0.2, -0.1, 0);
	drawChimney();
	drawFloor();
	drawFence();
	drawCar();
	drawTree(2.0, 0);
	drawTree(-2.0, -0.5);
	drawTree(-2.0, 0);
	drawTree(-2.0, 0.5);
	drawTree(-2.0, 1.0);
	drawCloud(1, 0.9, -0.6);
	if (smokeRadius1 < 0.1) {
		drawSmoke(0.45, 1.55, smokeRadius1, 0.0, 0.005);
		drawSmoke(0.55, 1.70, smokeRadius2, 0.01, 0.015);
		drawSmoke(0.65, 1.85, smokeRadius3, 0.02, 0.030);
	}
	else {
		smokeReposition();
	}
	if (thetaSun < 3.14) {
		drawSun(5, 0.2);
	}
	else {
		sunReposition();
	}
	glFlush();
}

void init() {
	//places lighting in the view
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	GLfloat light_position[] = { 1.0, 1.0, 0.0, 0.0 };
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);
	glEnable(GL_COLOR_MATERIAL);

	glClearColor(0.0, 1.0, 1.0, 1.0);
	glColor3f(0.0, 0.0, 0.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-2.0, 2.0, -2.0, 2.0, -2.0, 100.0);
}

int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitWindowSize(1000, 1000);
	glutCreateWindow("CW of Minghao Li");
	glutDisplayFunc(display);
	glutIdleFunc(idle);
	glutSpecialFunc(specialKeys);
	init();
	glEnable(GL_DEPTH_TEST);
	glutMainLoop();
}
