#include <bits/stdc++.h>

#define pi (2*acos(0.0))

using namespace std;


class point
{

    double **array;

public:
    point()
    {
        int i;
        array = new double*[4];
        for(i=0; i<4; i++)
        {
            array[i] = new double[1];
        }
        array[3][0] = 1;
    }
    point(double x,double y,double z)
    {
        int i;
        array = new double*[4];
        for(i=0; i<4; i++)
        {
            array[i] = new double[1];
        }

        array[0][0] = x;
        array[1][0] = y;
        array[2][0] = z;
        array[3][0] = 1;
    }

    double** getArray()
    {
        return array;
    }

    double getx()
    {
        return array[0][0];
    }

    void setx(double x)
    {
        array[0][0] = x;
    }

    double gety()
    {
        return array[1][0];
    }

    void sety(double y)
    {
        array[1][0] = y;
    }

    double getz()
    {
        return array[2][0];
    }

    void setz(double z)
    {
        array[2][0] = z;
    }


    double getw()
    {
        return array[3][0];
    }


};

void print(point p)
{
    int i;
    cout<<fixed;
    for(i=0; i<3; i++)
    {
        cout<<p.getArray()[i][0]<<" ";
    }
    cout<<endl;
}

void print(ofstream& os,point p)
{

    os<<fixed;
    for(int i=0; i<3; i++)
    {
        os<<setprecision(7)<<p.getArray()[i][0]<<" ";
    }
    os<<endl;
}

void processweight(point p)
{
    int i;

    for(i=0; i<4; i++)
    {
        p.getArray()[i][0] = p.getArray()[i][0]/p.getw();
    }
}

void normalize(point p)
{
    int i;
    double sum = 0.0;
    for(i=0; i<3; i++)
    {
        sum += p.getArray()[i][0]*p.getArray()[i][0];
    }

    sum = sqrt(sum);
    p.getArray()[0][0] = p.getArray()[0][0]/sum;
    p.getArray()[1][0] = p.getArray()[1][0]/sum;
    p.getArray()[2][0] = p.getArray()[2][0]/sum;
}

double dotproduct(point a, point b)
{
    return a.getx()*b.getx() + a.gety()*b.gety() + a.getz()*b.getz();
}

point crossproduct(point a,point b)
{
    point p;
    p.setx(a.gety()*b.getz() - a.getz()*b.gety());
    p.sety(-(a.getx()*b.getz() - b.getx()*a.getz()));
    p.setz(a.getx()*b.gety() - b.getx()*a.gety());
    return p;
}


point R(point x,point a,double theta)
{
    point result;
    double dot = dotproduct(a,x);
    point cross = crossproduct(a,x);

    double costheta = cos(theta*pi/180.0);
    double sintheta = sin(theta*pi/180.0);

    result.setx(costheta*x.getx()+ (1-costheta)*dot*a.getx()+ sintheta*cross.getx());
    result.sety(costheta*x.gety()+ (1-costheta)*dot*a.gety()+ sintheta*cross.gety());
    result.setz(costheta*x.getz()+ (1-costheta)*dot*a.getz()+ sintheta*cross.getz());
    return result;
}


class matrix
{
    double **array;
    string type;
public:

    matrix()
    {
        int i;
        array = new double*[4];
        for(i=0; i<4; i++)
        {
            array[i] = new double[4];
        }
    }

    double** getArray()
    {
        return array;
    }

    void identity()
    {
        int i,j;
        type = "I";
        for(i=0; i<4; i++)
        {
            for(j=0; j<4; j++)
            {
                if(i==j)
                    array[i][j] = 1;
                else
                    array[i][j] = 0;
            }
        }
    }

    string getType()
    {
        return type;
    }

    void setType(string newtype)
    {
        type = newtype;
    }

};

void print(matrix mat)
{
    int i,j;

    for(i=0; i<4; i++)
    {
        for(j=0; j<4; j++)
        {
            cout<<setprecision(3)<<mat.getArray()[i][j]<<" ";
        }
        cout<<endl;
    }
    cout<<endl;
}

void scale(matrix mat, double x,double y,double z)
{
    mat.identity();
    mat.getArray()[0][0] = x;
    mat.getArray()[1][1] = y;
    mat.getArray()[2][2] = z;

}

void rotate(matrix mat,double angle, point a)
{
    mat.identity();
    mat.setType("R");
    normalize(a);

    point c1 = R(point(1,0,0),a,angle);
    point c2 = R(point(0,1,0),a,angle);
    point c3 = R(point(0,0,1),a,angle);

    mat.getArray()[0][0] = c1.getx();
    mat.getArray()[0][1] = c2.getx();
    mat.getArray()[0][2] = c3.getx();


    mat.getArray()[1][0] = c1.gety();
    mat.getArray()[1][1] = c2.gety();
    mat.getArray()[1][2] = c3.gety();

    mat.getArray()[2][0] = c1.getz();
    mat.getArray()[2][1] = c2.getz();
    mat.getArray()[2][2] = c3.getz();

}

void translate(matrix mat,double tx, double ty, double tz)
{
    mat.identity();
    mat.setType("T");

    mat.getArray()[0][3] = tx;
    mat.getArray()[1][3] = ty;
    mat.getArray()[2][3] = tz;
    mat.getArray()[3][3] = 1;
}

void viewRotate(matrix mat,point l, point r, point u)
{
    mat.identity();
    mat.getArray()[0][0] = r.getx();
    mat.getArray()[0][1] = r.gety();
    mat.getArray()[0][2] = r.getz();

    mat.getArray()[1][0] = u.getx();
    mat.getArray()[1][1] = u.gety();
    mat.getArray()[1][2] = u.getz();

    mat.getArray()[2][0] = -l.getx();
    mat.getArray()[2][1] = -l.gety();
    mat.getArray()[2][2] = -l.getz();
}


void projection(matrix mat,double near,double far,double t,double r)
{
    mat.identity();
    mat.getArray()[0][0] = near/r;
    mat.getArray()[1][1] = near/t;
    mat.getArray()[2][2] = -(far+near)/(far-near);
    mat.getArray()[2][3] = -(2*far*near)/(far-near);
    mat.getArray()[3][2] = -1;
    mat.getArray()[3][3] = 0;
}

matrix matmult(matrix x,matrix y)
{
    matrix mat;
    double **a,**b;
    a = x.getArray();
    b = y.getArray();

    int i,j;

    for (i = 0; i < 4; i++)
    {
        for (j = 0; j < 4; j++)
        {
            mat.getArray()[i][j] = 0;
            for (int k = 0; k < 4; k++)
            {
                mat.getArray()[i][j] += a[i][k] * b[k][j];
            }
        }
    }

    return mat;
}

point pointmult(matrix x,point y)
{
    double **a,**b;
    point p;
    a = x.getArray();
    b = y.getArray();

    int i,j,k;

    for (i = 0; i < 4; i++)
    {
        for ( j = 0; j < 1; j++)
        {
            p.getArray()[i][j] = 0;
            for ( k = 0; k < 4; k++)
            {
                p.getArray()[i][j] += a[i][k] * b[k][j];
            }
        }
    }
    return p;
}

int main()
{
    double eyeX = 0;
    double eyeY = 0;
    double eyeZ = 0;

    double lookX = 0;
    double lookY = 0;
    double lookZ = 0;

    double upX = 0;
    double upY = 0;
    double upZ = 0;

    double fovY = 0;
    double aspectRatio = 0;
    double near = 0;
    double far  = 0;

    stack<matrix> glstack;

    matrix transformMat;
    transformMat.identity();


    ifstream cin("scene.txt");
    ofstream stage1("stage1.txt");
    ofstream stage2("stage2.txt");
    ofstream stage3("stage3.txt");


    cin>>eyeX>>eyeY>>eyeZ;

    cin>>lookX>>lookY>>lookZ;

    cin>>upX>>upY>>upZ;

    cin>>fovY;
    cin>>aspectRatio;
    cin>>near;
    cin>>far;

    point l(lookX-eyeX,lookY-eyeY,lookZ-eyeZ);
    normalize(l);
    point up(upX,upY,upZ);
    point r = crossproduct(l,up);
    normalize(r);
    point u = crossproduct(r,l);


    matrix T;
    translate(T,-eyeX,-eyeY,-eyeZ);

    matrix R;
    viewRotate(R,l,r,u);

    matrix V = matmult(R,T);


    double fovX = fovY * aspectRatio;
    double project_t = near * tan(fovY*pi/360.0);
    double project_r = near * tan(fovX*pi/360.0);

    matrix P;
    projection(P,near,far,project_t,project_r);


    string command ="";
    while(true)
    {
        cin>>command;
        if(command=="triangle")
        {
            for(int i=0; i<3; i++)
            {
                double x,y,z;
                cin>>x>>y>>z;
                point p(x,y,z);
                point output1,output2,output3;
                output1 = pointmult(transformMat,p);
                if(output1.getw() !=1) processweight(output1);
                print(stage1,output1);

                output2 = pointmult(V,output1);
                if(output2.getw() !=1) processweight(output2);
                print(stage2,output2);

                output3 = pointmult(P,output2);
                if(output3.getw() !=1) processweight(output3);
                print(stage3,output3);
            }
            stage1<<endl;
            stage2<<endl;
            stage3<<endl;
        }
        else if(command=="scale")
        {
            double x,y,z;
            cin>>x>>y>>z;
            matrix mat;
            cout<<x<<y<<z<<endl;
            scale(mat,x,y,z);
            transformMat = matmult(transformMat,mat);
        }
        else if(command=="translate")
        {
            double x,y,z;
            cin>>x>>y>>z;
            matrix mat;
            translate(mat,x,y,z);
            transformMat = matmult(transformMat,mat);
        }
        else if(command=="rotate")
        {
            double angle,x,y,z;
            cin>>angle>>x>>y>>z;
            point p(x,y,z);
            matrix mat;
            rotate(mat,angle,p);
            transformMat = matmult(transformMat,mat);
        }
        else if(command=="push")
        {
            glstack.push(transformMat);
        }
        else if(command=="pop")
        {
            transformMat = glstack.top();
            glstack.pop();
        }
        else if(command=="end")
        {
            break;
        }
    }

}
