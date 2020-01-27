/////wheel

#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include <windows.h>
#include <glut.h>
#define pi (2*acos(0.0))

double cameraHeight;
double cameraAngle;
int drawgrid;

double anglerot;
double anglerotor;

double peranglerot;
double peranglerotor;

double transunit;
double transunitx;
double transunity;
double radius;
double height;

struct point
{
    double x,y,z;
};


struct point points[100][100];

void drawGrid()
{
    int i;
    glColor3f(0.6, 0.6, 0.6);	//grey
    glBegin(GL_LINES);
    {
        for(i=-8; i<=8; i++)
        {
            //lines parallel to Y-axis
            glVertex3f(i*10, -90, 0);
            glVertex3f(i*10,  90, 0);

            //lines parallel to X-axis
            glVertex3f(-90, i*10, 0);
            glVertex3f( 90, i*10, 0);
        }
    }
    glEnd();
}

void drawCylinder(int slices,double h,double r)
{
    int i,j;
    for(i=0; i<2; i++)
    {
        for(j=0; j<=slices; j++)
        {
            points[i][j].y=r*cos(((double)j/(double)slices)*2*pi);
            points[i][j].z=r*sin(((double)j/(double)slices)*2*pi);
            points[i][j].x=h*i;
        }
    }
    //draw quads using generated points

    i= 0;

    for(j=0; j<slices; j++)
    {
        if(j>slices/2)
            glColor3f((double)j/(double)slices,(double)j/(double)slices,(double)j/(double)slices);
        else
            glColor3f((double)(slices-j)/(double)slices,(double)(slices-j)/(double)slices,(double)(slices-j)/(double)slices);
        glBegin(GL_QUADS);
        {
            glVertex3f(points[i][j].x,points[i][j].y,points[i][j].z);
            glVertex3f(points[i][j+1].x,points[i][j+1].y,points[i][j+1].z);
            glVertex3f(points[i+1][j+1].x,points[i+1][j+1].y,points[i+1][j+1].z);
            glVertex3f(points[i+1][j].x,points[i+1][j].y,points[i+1][j].z);
        }
        glEnd();
    }

    int divisor = floor(slices/4);

    glBegin(GL_QUADS);
    {
        //the spikes
        glVertex3f(points[0][divisor].x+(h/4),points[0][divisor].y,points[0][divisor].z);
        glVertex3f(points[1][divisor].x-((h)/4),points[1][divisor].y,points[1][divisor].z);
        glVertex3f(points[1][divisor*3].x-(h/4),points[1][divisor*3].y,points[1][divisor*3].z);
        glVertex3f(points[0][divisor*3].x+(h/4),points[0][divisor*3].y,points[0][divisor*3].z);

        glVertex3f(points[0][divisor*2].x+(h/4),points[0][divisor*2].y,points[0][divisor*2].z);
        glVertex3f(points[1][divisor*2].x-(h/4),points[1][divisor*2].y,points[1][divisor*2].z);
        glVertex3f(points[1][0].x-(h/4),points[1][0].y,points[1][0].z);
        glVertex3f(points[0][0].x+(h/4),points[0][0].y,points[0][0].z);
    }
    glEnd();

}


void keyboardListener(unsigned char key, int x,int y)
{
    switch(key)
    {

    case 'd':
        anglerot += peranglerot;
        printf("rotating right: %f\n",anglerot);
        break;

    case 'a':
        anglerot -= peranglerot;
        printf("rotating left: %f\n",anglerot);
        break;

    case 'w':
        anglerotor += peranglerotor;
        transunit = 2 * pi * radius * (double)(peranglerotor)/(double)(360);
        transunitx -= sin(anglerot*pi/(double)180) * transunit;
        transunity += cos(anglerot*pi/(double)180) * transunit;
        printf("forward direction: %f\n",anglerot);
        printf("w: self rotor angle :%f , transfer: %f, transferX: %f , transfer Y: %f \n ",anglerotor,transunit,transunitx,transunity );
        break;

    case 's':
        anglerotor -= peranglerotor;
        transunit = 2 * pi * radius * (double)(-peranglerotor)/(double)(360);
        transunitx -= sin(anglerot*pi/(double)180) * transunit;
        transunity += cos(anglerot*pi/(double)180) * transunit;
        printf("forward direction: %f\n",anglerot);
        printf("s: self rotor angle :%f , transfer: %f, transferX: %f , transfer Y: %f \n ",anglerotor,transunit,transunitx,transunity );
        break;

    default:
        break;
    }
}


void specialKeyListener(int key, int x,int y)
{
    switch(key)
    {
    case GLUT_KEY_DOWN:		//down arrow key
        cameraHeight -= 3.0;
        break;
    case GLUT_KEY_UP:		// up arrow key
        cameraHeight += 3.0;
        break;

    case GLUT_KEY_RIGHT:
        cameraAngle += 0.03;
        break;
    case GLUT_KEY_LEFT:
        cameraAngle -= 0.03;
        break;

    default:
        break;
    }
}


void display()
{

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glClearColor(0,0,0,0);	//color black
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    gluLookAt(100*cos(cameraAngle), 100*sin(cameraAngle), cameraHeight,		0,0,0,		0,0,1);

    glMatrixMode(GL_MODELVIEW);

    drawGrid();

    glPushMatrix();
    {
        glTranslatef(transunitx-(height/2),transunity,radius);
        glRotatef(anglerot,0,0,1);
        glRotatef(-anglerotor,1,0,0);
        drawCylinder(36,height,radius);
    }
    glPopMatrix();

    glutSwapBuffers();
}


void animate()
{
    glutPostRedisplay();
}

void init()
{
    cameraHeight=150.0;
    cameraAngle=1.0;

    anglerot = 0;
    anglerotor = 0;
    transunit = 0;
    radius = 30;
    height = 10;

    peranglerot = 1;
    peranglerotor = 1;


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
    glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGB);	//Depth, Double buffer, RGB color

    glutCreateWindow("My OpenGL Program");

    init();

    glEnable(GL_DEPTH_TEST);	//enable Depth Testing

    glutDisplayFunc(display);	//display callback function
    glutIdleFunc(animate);		//what you want to do in the idle time (when no drawing is occuring)

    glutKeyboardFunc(keyboardListener);
    glutSpecialFunc(specialKeyListener);

    glutMainLoop();		//The main loop of OpenGL

    return 0;
}
