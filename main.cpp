#include<windows.h>
#include<bits/stdc++.h>
#include<stdarg.h>
#include<GL/glut.h>
static float rx[100]= {0}, ry[100]= {0};

//control waves
static double w1 =0,w2=0,w3=0;
static bool transmit=false;
void *currentfont= GLUT_BITMAP_TIMES_ROMAN_24;

void drawstring(float x,float y,float z,char *string)
{
    char *c;
    glRasterPos3f(x,y,z);
    for(c=string; *c!='\0'; c++)
    {
        glColor3f(0,0,0);
        glutBitmapCharacter(currentfont,*c);
    }
}

//DRAW THE SATELITE IN THE SKY
void satellite()
{
    glRotatef(60,1,0,0);
//body
    glPushMatrix();
    glColor3f(0.2,0.2,0.2);
    glScaled(1,0.6,1);
    glTranslatef(3.0,0,0.0);
    glutSolidCube(0.5);
    glPopMatrix();
//Solar Panels
    glPushMatrix();
    glColor3f(1,1,1);
    glTranslatef(3,0,0.0);
    glScaled(3.7,0.0,1);
    glutSolidCube(0.5); //CUBE SHAPED PANELS
    glPopMatrix();
//SPHERE = BALL SHAPE(UPPER ROUND SHAPED OBJECT)
    glPushMatrix();
    glColor3f(0.6,0.1,0.2);
    glTranslatef(3.0,0,-0.4);
    glScaled(0.5,0.5,0.5);
    glutSolidSphere(0.4,100,100);//SPHERE = BALL SHAPE
    glPopMatrix();
//TORUS = DOUGHNUT SHAPE(LOWER DOUGHNUT SHAPED OBJECT)
    glPushMatrix();
    glColor3f(0.6,0.1,0.2);
    glTranslatef(3.0,0,0.4);
    glScaled(0.4,0.4,0.3);
    glutSolidTorus(0.3,0.2,20,20);  //TORUS = DOUGHNUT SHAPE
    glPopMatrix();
}

/*OpenGL keeps a stack of matrices to quickly apply and remove transformations.
glPushMatrix copies the top matrix and pushes it onto the stack,
while glPopMatrix pops the top matrix off the stack. All transformation functions (glScaled, etc.)
function on the top matrix, and the top matrix is what all rendering commands use to transform their data.
By pushing and popping matrices, you can control what transformations apply to which objects,
as well as apply transformations to groups of objects, and easily reverse the transformations
so that they don't affect other objects.*/

void building(float x1,float y1,float z1){
//BUILDING BODY
    glPushMatrix();
    glColor3f(0.880, 0.200, 0.205);
    glTranslatef(x1,y1,z1);
    glScaled(0.5,1.5,0.5);
    glutSolidCube(2);
    glPopMatrix();
//DISH ON THE BUILDING
    glPushMatrix();
    glColor3f(1,1,1);
    glTranslatef(x1,y1+1.8,z1);
    glRotatef(50,1,0,0);
    glScaled(0.5,1.5,0.5);
    glutSolidCone(0.5,1,20,20);
    glPopMatrix();
//WINDOWS OF THE BUILDINGS
    glPushMatrix();
    glColor3f(0, 0, 0);
    glTranslatef(x1-0.2,y1+0.7,z1);
    glScaled(0.5,0.5,0.5);
    for(float j=-3; j<1.5; j+=.8)
    {
        for(float i=0; i<1; i+=0.8)
        {
            glPushMatrix();
            glTranslatef(i,j,1);
            glutSolidCube(0.4);
            glPopMatrix();
        }
    }
    glPopMatrix();
}

void waves()
{
    glPushMatrix();
        glTranslatef(0,1,0);
        glScaled(0.05,0.5,0.1);
        glutSolidCube(1.0);
    glPopMatrix();
    glPushMatrix();
        glRotatef(-8,0,0,1);
        glTranslatef(0.01,1,0);     //TEMON KICHU NA, DESIGN OF THE 3 STRIPES OF THE SIGNAL
        glScaled(0.05,0.5,0.1);     //BOTH UPLINK AND DOWNLINK
        glutSolidCube(0.5);
    glPopMatrix();
    glPushMatrix();
        glRotatef(8,0,0,1);
        glTranslatef(-0.01,1,0);
        glScaled(0.05,0.6,0.1);
        glutSolidCube(0.5);
    glPopMatrix();
}

void sat1()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    glTranslatef(0.0f,0.0f,-13.0f);

    glPushMatrix();
    glColor3f(0.039, 0.698, 0.098);
    glTranslatef(0,-12,0);
    glutSolidSphere(10.0,50,50);
    glPopMatrix();
//Building Center
    glPushMatrix();
    glColor3f(0.1, 0.6, 0.8);
    glRotatef(-3,0,0,1);
    building(1.2,-1.2,3.2);
    glPopMatrix();
//Building left
    glPushMatrix();
    glColor3f(0.121, 0.698, 0.196);
    glRotatef(5,0,0,1);
    building(-3.8,-1.2,0);
    glPopMatrix();
//Building right
    glPushMatrix();
    glColor3f(0.894, 0.035, 0.027);
    glRotatef(-5,0,0,1);
    building(3.8,-1.2,0);
    glPopMatrix();
//GROUND SIGNAL STATION
    glPushMatrix();
    glColor3f(1,1,1);
    glTranslatef(-1,-2,4);
    glRotatef(270,1,0,0);
    glScaled(1.0,1,2.0);
    glutWireCone(0.5,1,4,10);
    glPopMatrix();
//GROUND SIGNAL STATION ER DISH
    glPushMatrix();
    glColor3f(1,1,0.5);
    glTranslatef(-1.08,0.2,3);
    glRotatef(60,1,0,0);
    glScaled(0.7,1.3,0.7);
    glutSolidCone(0.4,0.5,20,20);
    glPopMatrix();
//SATELLITE IN THE SKY
    glPushMatrix();
    glTranslatef(-3,3.0,0);
    satellite();
    glPopMatrix();
//UPLINK SIGNAL DESIGN
    glPushMatrix();
    glColor3f(1,1,1);
    if(transmit)
    {
        glRotatef(-25,0,0,1);
        glTranslatef(-1.25,-1.6+w1,0);
    }
    else glTranslatef(1,20,3.3);
    waves();
    glPopMatrix();
//DOWNLINK SIGNAL TO RIGHT BUILDING
    glPushMatrix();
    if(transmit)
    {
        glRotatef(50,0,0,1);
        glTranslatef(2.8,3.2-w2,0);
    }
    else glTranslatef(1,20,3.3);
    waves();
    glPopMatrix();
//DOWNLINK SIGNAL TO LEFT BUILDING
    glPushMatrix();
    if(transmit)
    {
        glRotatef(-50,0,0,1);
        glTranslatef(-2.8,3.2-w2,0);
    }
    else glTranslatef(1,20,3.3);
    waves();
    glPopMatrix();
//DOWNLINK SIGNAL TO CENTER BUILDING
    glPushMatrix();
    if(transmit)
    {
        glRotatef(23,0,0,1);
        glTranslatef(1,3.0-w3,3.3);
    }
    else glTranslatef(1,20,3.3);
    waves();
    glPopMatrix();
//TITLES UNDER DIFFERENT INFRASTRUCTURES
    glPushMatrix();
    glTranslatef(0.0,0.0,-2.0);
    glColor3f(1,1,1);
    drawstring(1.5,3.7,-1.0,"SATELLITE");
    glColor3f(1,1,1);
    drawstring(-4.4,.5,-1.0,"RECEIVER");
    glColor3f(1,1,1);
    drawstring(0,-2,7,"RECEIVER");
    glColor3f(1,1,1);
    drawstring(-1.5,-1,-1.0,"TRANSMITTER");
    glColor3f(1,1,1);
    drawstring(3.2,1,3,"RECEIVER");
    glPopMatrix();

    glFlush();
    glutSwapBuffers();
}

void S()
{
    if(transmit)
    {
        if(w1<=4.2)     //CONTROLS SPEED OF WAVE TOWARDS THE SATELITE
            w1+=0.02;

        if(w1>=2.5 && w2<=6.9)      //w1, w2, w3 ALL ARE USED TO CONTROL SPEED OF WAVE PROPAGATION
            w2+=0.03;

        if(w1>=2.5 && w3<=5)    //CONTROLS SPEED OF WAVE TOWARDS THE MIDDLE BUILDING
            w3+=0.02;
    }
    sat1();
}

void doInit()
{
    glClearColor(0.0,0.0,0.0,0);//set Background color as black
    glViewport(0,0,680,480);
    //Select the projection matrix and reset it then setup our view perspective
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(30.0f,(GLfloat)640/(GLfloat)480,0.1f,200.0f); //set up a perspective projection matrix
    /* Select the modelview matrix, which we alter with rotatef() */
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glClearDepth(2.0f);
    glEnable(GL_DEPTH_TEST);
    glEnable( GL_COLOR_MATERIAL );
    glDepthFunc(GL_LEQUAL);
}

void display()  //DONE
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    glTranslatef(0.0f,0.0f,-12.0f);

    GLfloat mat_ambient[]= {0.0f,1.0f,2.0f,1.0f};
    GLfloat mat_diffuse[]= {0.0f,1.5f,.5f,1.0f};
    GLfloat mat_specular[]= {5.0f,1.0f,1.0f,1.0f};
    GLfloat mat_shininess[]= {50};
    glMaterialfv(GL_FRONT,GL_AMBIENT,mat_ambient);
    glMaterialfv(GL_FRONT,GL_DIFFUSE,mat_diffuse);
    glMaterialfv(GL_FRONT,GL_SPECULAR,mat_specular);
    glMaterialfv(GL_FRONT,GL_SHININESS,mat_shininess);

    GLfloat lightIntensity[]= {1.7f,1.7f,1.7f,1.0f};
    GLfloat light_position3[]= {0.0f,8.0f,10.0f,0.0f};
    glLightfv(GL_LIGHT0,GL_POSITION,light_position3);
    glLightfv(GL_LIGHT0,GL_DIFFUSE,lightIntensity);

    GLfloat lightIntensity1[]= {1.7f,1.7f,1.7f,1.0f};
    GLfloat light_position31[]= {-2.0f,8.0f,10.0f,0.0f};
    glLightfv(GL_LIGHT1,GL_POSITION,light_position31);
    glLightfv(GL_LIGHT1,GL_DIFFUSE,lightIntensity1);

    glEnable(GL_COLOR_MATERIAL);
    glFlush();
    glutSwapBuffers();
}

void mykey(unsigned char key,int x,int y)
{
    if(key)
    {
        transmit=!transmit;
        glutIdleFunc(S);
    }
}
int main(int argc, char *argv[])
{
    glutInit(&argc, argv);//initialize the GLUT library
    glutInitDisplayMode(GLUT_DOUBLE|GLUT_RGB);
    glutInitWindowSize(1000,600);
    glutInitWindowPosition(0,0);
    glutCreateWindow("Demonstrating Satellite Communication");
    glutDisplayFunc(display);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_LIGHT1);
    glShadeModel(GL_SMOOTH); //CHECK THE DISH
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_NORMALIZE);
    glutKeyboardFunc(mykey);
    doInit();
    glutMainLoop();
    return 0;
}
