//mine

#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include <string>
#include <windows.h>
#include <glut.h>
#include <iostream>
#include <sstream>

#define pi (2*acos(0.0))

int drawaxes;
double angle;
double globheight;
double globradius;
double cylindersegment;


struct point
{
    double x,y,z;

    std::string toString() {
        std::ostringstream strout;
        strout<< "x: " << x << ", y: " << y << ", z: " << z << std::endl;
        return strout.str();
    }
};

struct point position,look,up,right;


void drawAxes()
{
    if(drawaxes==1)
    {
        glColor3f(1.0, 1.0, 1.0);
        glBegin(GL_LINES);
        {
            glVertex3f( 100,0,0);
            glVertex3f(-100,0,0);

            glVertex3f(0,-100,0);
            glVertex3f(0, 100,0);

            glVertex3f(0,0, 100);
            glVertex3f(0,0,-100);
        }
        glEnd();
    }
}


void drawSquare(double a)
{
    glBegin(GL_QUADS);
    {
        glVertex3f( a, a,0);
        glVertex3f( a,-a,0);
        glVertex3f(-a,-a,0);
        glVertex3f(-a, a,0);
    }
    glEnd();
}


void drawCylinder(double globradius,double height,int segments)
{
    int i;
    struct point points[100];
    for(i=0; i<=segments/4; i++)
    {
        points[i].x=globradius*cos(((double)i/(double)segments)*2*pi);
        points[i].y=globradius*sin(((double)i/(double)segments)*2*pi);
    }

    for(i=0; i<segments/4; i++)
    {
        glBegin(GL_QUADS);
        {
            glVertex3f(points[i].x,points[i].y,height);
            glVertex3f(points[i+1].x,points[i+1].y,height);
            glVertex3f(points[i+1].x,points[i+1].y,0);
            glVertex3f(points[i].x,points[i].y,0);
        }
        glEnd();
    }
}


void drawSphere(double globradius,int slices,int stacks)
{
    struct point points[100][100];
    int i,j;
    double h,r;
    for(i=0; i<=stacks; i++)
    {
        h=globradius*sin(((double)i/(double)stacks)*(pi/2));
        r=globradius*cos(((double)i/(double)stacks)*(pi/2));
        for(j=0; j<=slices/4; j++)
        {
            points[i][j].x=r*cos(((double)j/(double)slices)*2*pi);
            points[i][j].y=r*sin(((double)j/(double)slices)*2*pi);
            points[i][j].z=h;
        }
    }
    //draw quads using generated points
    for(i=0; i<stacks; i++)
    {
        for(j=0; j<slices/4; j++)
        {
            glBegin(GL_QUADS);
            {
                glVertex3f(points[i][j].x,points[i][j].y,points[i][j].z);
                glVertex3f(points[i][j+1].x,points[i][j+1].y,points[i][j+1].z);
                glVertex3f(points[i+1][j+1].x,points[i+1][j+1].y,points[i+1][j+1].z);
                glVertex3f(points[i+1][j].x,points[i+1][j].y,points[i+1][j].z);
            }
            glEnd();
        }
    }
}


struct point crossProduct(struct point p,struct point q)
{
    struct point r;

    r.x = p.y*q.z - p.z*q.y;
    r.y = -(p.x*q.z - q.x*p.z);
    r.z = p.x*q.y - q.x*p.y;

    return r;
}

void rotateccw(struct point *first, struct point *second,struct point axis, double angle)
{
    struct point result = crossProduct(*first,axis);

    first->x = first->x*cos(angle) + result.x*sin(angle);
    first->y = first->y*cos(angle) + result.y*sin(angle);
    first->z = first->z*cos(angle) + result.z*sin(angle);

    result = crossProduct(*second,axis);

    second->x = second->x*cos(angle) + result.x*sin(angle);
    second->y = second->y*cos(angle) + result.y*sin(angle);
    second->z = second->z*cos(angle) + result.z*sin(angle);
}

void keyboardListener(unsigned char key, int x,int y)
{
    switch(key)
    {
    case '1':
        rotateccw(&look, &right, up, -angle);
        printf("Look left :");
        std::cout<<look.toString();
        break;
    case '2':
        rotateccw(&look, &right, up, angle);
        printf("Look right :");
        std::cout<<look.toString();
        break;
    case '3':
        rotateccw(&look, &up, right, -angle);
        printf("Look up :");
        std::cout<<up.toString();
        break;
    case '4':
        rotateccw(&look, &up, right, angle);
        printf("Look down :");
        std::cout<<up.toString();
        break;
    case '5':
        rotateccw(&right, &up, look, -angle);
        printf("Tilt clockwise :");
        std::cout<<right.toString();
        break;
    case '6':
        rotateccw(&right, &up, look, angle);
        printf("Tilt anticlockwise :");
        std::cout<<right.toString();
        break;
    default:
        break;
    }
}

void specialKeyListener(int key, int x,int y)
{
    switch(key)
    {

    case GLUT_KEY_DOWN:

        position.x -= look.x;
        position.y -= look.y;
        position.z -= look.z;

        std::cout<<"new position after move backward: "<<position.toString();
        break;

    case GLUT_KEY_UP:

        position.x += look.x;
        position.y += look.y;
        position.z += look.z;

        std::cout<<"new position after move forward: "<<position.toString();
        break;

    case GLUT_KEY_RIGHT:

        position.x += right.x;
        position.y += right.y;
        position.z += right.z;

        std::cout<<"new position after move right: "<<position.toString();

        break;

    case GLUT_KEY_LEFT:

        position.x -= right.x;
        position.y -= right.y;
        position.z -= right.z;

        std::cout<<"new position after move left: "<<position.toString();
        break;

    case GLUT_KEY_PAGE_UP:

        position.x += up.x;
        position.y += up.y;
        position.z += up.z;

        std::cout<<"new position after move up: "<<position.toString();

        break;

    case GLUT_KEY_PAGE_DOWN:

        position.x -= up.x;
        position.y -= up.y;
        position.z -= up.z;

        std::cout<<"new position after move down: "<<position.toString();

        break;

    case GLUT_KEY_HOME:

        if(globheight > 0)
        {
            globheight -= 2;
            globradius += 1;
        }

        printf("cube to sphere: radius: %f  height: %f\n",globradius,globheight);
        break;

    case GLUT_KEY_END:

        if(globradius > 0)
        {
            globheight += 2;
            globradius -= 1;
        }

        printf("sphere to cube: radius: %f  height: %f\n",globradius,globheight);
        break;

    default:
        break;
    }
}

void mouseListener(int button, int state, int x, int y)
{
    switch(button)
    {
    case GLUT_LEFT_BUTTON:
        if(state == GLUT_DOWN)
            drawaxes=1-drawaxes;
        break;

    default:
        break;
    }
}

void drawSphereGroup()
{
    glColor3f(1,0,0);

    //1st region up
    glPushMatrix();
    glTranslatef(globheight,globheight,globheight);
    drawSphere(globradius,cylindersegment,cylindersegment);
    glPopMatrix();

    //2nd region up
    glPushMatrix();
    glTranslatef(-globheight,globheight,globheight);
    glRotatef(90,0,0,1);
    drawSphere(globradius,cylindersegment,cylindersegment);
    glPopMatrix();

    //3rd region up
    glPushMatrix();
    glTranslatef(-globheight,-globheight,globheight);
    glRotatef(180,0,0,1);
    drawSphere(globradius,cylindersegment,cylindersegment);
    glPopMatrix();

    //4th region up
    glPushMatrix();
    glTranslatef(globheight,-globheight,globheight);
    glRotatef(270,0,0,1);
    drawSphere(globradius,cylindersegment,cylindersegment);
    glPopMatrix();

    //1st region down
    glPushMatrix();
    glTranslatef(globheight,globheight,-globheight);
    glRotatef(90,0,1,0);
    drawSphere(globradius,cylindersegment,cylindersegment);
    glPopMatrix();

    //2nd region down
    glPushMatrix();
    glTranslatef(-globheight,globheight,-globheight);
    glRotatef(90,0,0,1);
    glRotatef(90,0,1,0);
    drawSphere(globradius,cylindersegment,cylindersegment);
    glPopMatrix();

    //3rd region down
    glPushMatrix();
    glTranslatef(-globheight,-globheight,-globheight);
    glRotatef(180,0,0,1);
    glRotatef(90,0,1,0);
    drawSphere(globradius,cylindersegment,cylindersegment);
    glPopMatrix();

    //4th region down
    glPushMatrix();
    glTranslatef(globheight,-globheight,-globheight);
    glRotatef(270,0,0,1);
    glRotatef(90,0,1,0);
    drawSphere(globradius,cylindersegment,cylindersegment);
    glPopMatrix();
}

void drawCylinderGroup()
{
    glColor3f(0,1,0);

    //upper 1st region
    glPushMatrix();
    glTranslatef(-globheight,globheight,globheight);
    glRotatef(90,1,0,0);
    glRotatef(90,0,1,0);
    drawCylinder(globradius, 2*globheight, cylindersegment);
    glPopMatrix();

    //upper 2nd region
    glPushMatrix();
    glTranslatef(-globheight,globheight,globheight);
    glRotatef(270,0,1,0);
    glRotatef(90,1,0,0);
    drawCylinder(globradius, 2*globheight, cylindersegment);
    glPopMatrix();

    //upper 3rd region
    glPushMatrix();
    glTranslatef(-globheight,-globheight,globheight);
    glRotatef(180,1,0,0);
    glRotatef(90,0,1,0);
    drawCylinder(globradius, 2*globheight, cylindersegment);
    glPopMatrix();

    //upper 4th region
    glPushMatrix();
    glTranslatef(globheight,globheight,globheight);
    glRotatef(90,1,0,0);
    drawCylinder(globradius, 2*globheight, cylindersegment);
    glPopMatrix();


    //vertical 1st region
    glPushMatrix();
    glTranslatef(globheight,globheight,-globheight);
    drawCylinder(globradius, 2*globheight, cylindersegment);
    glPopMatrix();

    //vertical 2nd region
    glPushMatrix();
    glTranslatef(-globheight,globheight,-globheight);
    glRotatef(90,0,0,1);
    drawCylinder(globradius, 2*globheight, cylindersegment);
    glPopMatrix();

    //vertical 3rd region
    glPushMatrix();
    glTranslatef(-globheight,-globheight,-globheight);
    glRotatef(180,0,0,1);
    drawCylinder(globradius, 2*globheight, cylindersegment);
    glPopMatrix();

    //vertical 4th region
    glPushMatrix();
    glTranslatef(globheight,-globheight,-globheight);
    glRotatef(270,0,0,1);
    drawCylinder(globradius, 2*globheight, cylindersegment);
    glPopMatrix();

    //lower 1st region
    glPushMatrix();
    glTranslatef(-globheight,globheight,-globheight);
    glRotatef(90,0,1,0);
    drawCylinder(globradius, 2*globheight, cylindersegment);
    glPopMatrix();

    //lower 2nd region
    glPushMatrix();
    glTranslatef(-globheight,globheight,-globheight);
    glRotatef(180,0,1,0);
    glRotatef(90,1,0,0);
    drawCylinder(globradius, 2*globheight, cylindersegment);
    glPopMatrix();

    //lower 3rd region
    glPushMatrix();
    glTranslatef(-globheight,-globheight,-globheight);
    glRotatef(270,1,0,0);
    glRotatef(90,0,1,0);
    drawCylinder(globradius, 2*globheight, cylindersegment);
    glPopMatrix();

    //lower 4th region
    glPushMatrix();
    glTranslatef(globheight,globheight,-globheight);
    glRotatef(90,0,1,0);
    glRotatef(90,1,0,0);
    drawCylinder(globradius, 2*globheight, cylindersegment);
    glPopMatrix();
}

void drawSquareGroup()
{
    glColor3f(1,1,1);

    //upper side
    glPushMatrix();
    glTranslatef(0,0,globheight+globradius);
    drawSquare(globheight);
    glPopMatrix();

    //lower side
    glPushMatrix();
    glTranslatef(0,0,-globheight-globradius);
    drawSquare(globheight);
    glPopMatrix();

    //1st side
    glPushMatrix();
    glTranslatef(0,globheight+globradius,0);
    glRotatef(90,1,0,0);
    drawSquare(globheight);
    glPopMatrix();

    //2nd side
    glPushMatrix();
    glTranslatef(-globheight-globradius,0,0);
    glRotatef(90,0,1,0);
    drawSquare(globheight);
    glPopMatrix();

    //3rd side
    glPushMatrix();
    glTranslatef(0,-globheight-globradius,0);
    glRotatef(90,1,0,0);
    drawSquare(globheight);
    glPopMatrix();

    //4th side
    glPushMatrix();
    glTranslatef(globheight+globradius,0,0);
    glRotatef(90,0,1,0);
    drawSquare(globheight);
    glPopMatrix();
}

void display()
{

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glClearColor(0,0,0,0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(position.x, position.y, position.z, position.x + look.x, position.y + look.y,
              position.z + look.z, up.x, up.y, up.z);


    glMatrixMode(GL_MODELVIEW);

    drawAxes();

    drawSphereGroup();

    drawCylinderGroup();

    drawSquareGroup();

    glutSwapBuffers();
}


void animate()
{
    glutPostRedisplay();
}

void init()
{

    double sqrtroot = (double)1/(double)sqrt(2);
    drawaxes=1;
    angle = (double)3/(double)180 * pi;
    globradius = 10;
    globheight = 20;
    cylindersegment = 36;

    up = {0,0,1};
    right = {-sqrtroot, sqrtroot, 0};
    look = {-sqrtroot, -sqrtroot, 0};
    position = {100,100,0};

    glClearColor(0,0,0,0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(80,	1,	1,	1000.0);
}

int main(int argc, char **argv)
{
    glutInit(&argc,argv);
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(0, 0);
    glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGB);
    glutCreateWindow("My OpenGL Program");

    init();

    glEnable(GL_DEPTH_TEST);

    glutDisplayFunc(display);
    glutIdleFunc(animate);
    glutKeyboardFunc(keyboardListener);
    glutSpecialFunc(specialKeyListener);
    glutMouseFunc(mouseListener);

    glutMainLoop();
    return 0;
}
