#include <bits/stdc++.h>

#define pi (2*acos(0.0))

using namespace std;


class pt
{

    double **myarray;

public:
    pt()
    {
        int i;
        myarray = new double*[4];
        for(i=0; i<4; i++)
        {
            myarray[i] = new double[1];
        }
        myarray[3][0] = 1;
    }
    pt(double x,double y,double z)
    {
        int i;
        myarray = new double*[4];
        for(i=0; i<4; i++)
        {
            myarray[i] = new double[1];
        }

        myarray[0][0] = x;
        myarray[1][0] = y;
        myarray[2][0] = z;
        myarray[3][0] = 1;
    }

    double** getArray()
    {
        return myarray;
    }

    double getX()
    {
        return myarray[0][0];
    }

    void setX(double x)
    {
        myarray[0][0] = x;
    }

    double getY()
    {
        return myarray[1][0];
    }

    void setY(double y)
    {
        myarray[1][0] = y;
    }

    double getZ()
    {
        return myarray[2][0];
    }

    void setZ(double z)
    {
        myarray[2][0] = z;
    }


    double getW()
    {
        return myarray[3][0];
    }


};

void PrintFunction(pt p)
{
    int i;
    cout<<fixed;
    for(i=0; i<3; i++)
    {
        cout<<p.getArray()[i][0]<<" ";
    }
    cout<<endl;
}

void PrintFunction(ofstream& os,pt p)
{

    os<<fixed;
    for(int i=0; i<3; i++)
    {
        os<<setprecision(7)<<p.getArray()[i][0]<<" ";
    }
    os<<endl;
}

void divisonbyweight(pt p)
{
    int i;

    for(i=0; i<4; i++)
    {
        p.getArray()[i][0] = p.getArray()[i][0]/p.getW();
    }
}

void normalize(pt p)
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

double dotproduct(pt a, pt b)
{
    return a.getX()*b.getX() + a.getY()*b.getY() + a.getZ()*b.getZ();
}

pt crossproduct(pt a,pt b)
{
    pt p;
    p.setX(a.getY()*b.getZ() - a.getZ()*b.getY());
    p.setY(-(a.getX()*b.getZ() - b.getX()*a.getZ()));
    p.setZ(a.getX()*b.getY() - b.getX()*a.getY());
    return p;
}


pt RotPoint(pt x,pt a,double theta)
{
    double dot = dotproduct(a,x);
    pt cross = crossproduct(a,x);

    double cosine_val = cos(theta*pi/180.0);
    double sin_val = sin(theta*pi/180.0);

    pt result;
    result.setX(cosine_val*x.getX()+ (1-cosine_val)*dot*a.getX()+ sin_val*cross.getX());
    result.setY(cosine_val*x.getY()+ (1-cosine_val)*dot*a.getY()+ sin_val*cross.getY());
    result.setZ(cosine_val*x.getZ()+ (1-cosine_val)*dot*a.getZ()+ sin_val*cross.getZ());
    return result;
}


class mtx
{
    double **myarray;

public:

    mtx()
    {
        int i;
        myarray = new double*[4];
        for(i=0; i<4; i++)
        {
            myarray[i] = new double[4];
        }
    }

    double** getArray()
    {
        return myarray;
    }

    void ConverttoIdentity()
    {
        int i,j;

        for(i=0; i<4; i++)
        {
            for(j=0; j<4; j++)
            {
                if(i==j)
                    myarray[i][j] = 1;
                else
                    myarray[i][j] = 0;
            }
        }
    }



};

void PrintFunction(mtx mat)
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

void Scaling(mtx mat, double x,double y,double z)
{
    mat.ConverttoIdentity();
    mat.getArray()[0][0] = x;
    mat.getArray()[1][1] = y;
    mat.getArray()[2][2] = z;

}

void Rotating(mtx mat,double angle, pt a)
{
    mat.ConverttoIdentity();

    normalize(a);

    pt c1 = RotPoint(pt(1,0,0),a,angle);
    pt c2 = RotPoint(pt(0,1,0),a,angle);
    pt c3 = RotPoint(pt(0,0,1),a,angle);

    mat.getArray()[0][0] = c1.getX();
    mat.getArray()[0][1] = c2.getX();
    mat.getArray()[0][2] = c3.getX();


    mat.getArray()[1][0] = c1.getY();
    mat.getArray()[1][1] = c2.getY();
    mat.getArray()[1][2] = c3.getY();

    mat.getArray()[2][0] = c1.getZ();
    mat.getArray()[2][1] = c2.getZ();
    mat.getArray()[2][2] = c3.getZ();

}

void Translating(mtx mat,double tx, double ty, double tz)
{
    mat.ConverttoIdentity();

    mat.getArray()[0][3] = tx;
    mat.getArray()[1][3] = ty;
    mat.getArray()[2][3] = tz;
    mat.getArray()[3][3] = 1;
}

void ViewRotation(mtx mat,pt l, pt r, pt u)
{
    mat.ConverttoIdentity();
    mat.getArray()[0][0] = r.getX();
    mat.getArray()[1][0] = u.getX();
    mat.getArray()[2][0] = -l.getX();

    mat.getArray()[0][1] = r.getY();
    mat.getArray()[1][1] = u.getY();
    mat.getArray()[2][1] = -l.getY();

    mat.getArray()[0][2] = r.getZ();
    mat.getArray()[1][2] = u.getZ();
    mat.getArray()[2][2] = -l.getZ();
}


void ViewProjection(mtx mat,double t,double r,double near,double far)
{
    mat.ConverttoIdentity();
    mat.getArray()[0][0] = near/r;
    mat.getArray()[1][1] = near/t;
    mat.getArray()[3][3] = 0;

    mat.getArray()[2][2] = -(far+near)/(far-near);
    mat.getArray()[2][3] = -(2*far*near)/(far-near);
    mat.getArray()[3][2] = -1;
}

pt PointMultiplication(mtx x,pt y)
{
    double **a,**b;
    pt p;
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

mtx MAtrixMultiplication(mtx x,mtx y)
{
    mtx mat;
    double **first,**second;
    first = x.getArray();
    second = y.getArray();

    int i,j;

    for (i = 0; i < 4; i++)
    {
        for (j = 0; j < 4; j++)
        {
            mat.getArray()[i][j] = 0;
            for (int k = 0; k < 4; k++)
            {
                mat.getArray()[i][j] += first[i][k] * second[k][j];
            }
        }
    }

    return mat;
}


int main()
{
    stack<mtx> GLStack;

    mtx TransformationMatrix;
    TransformationMatrix.ConverttoIdentity();


    ifstream cin("scene.txt");
    ofstream stage1_output("stage1.txt");
    ofstream stage2_output("stage2.txt");
    ofstream stage3_output("stage3.txt");


    double eye_x = 0;
    double eye_y = 0;
    double eye_z = 0;

    double look_x = 0;
    double look_y = 0;
    double look_z = 0;

    double up_x = 0;
    double up_y = 0;
    double up_z = 0;

    double f_Y = 0;
    double a_Ratio = 0;
    double near = 0;
    double far  = 0;

    cin>>eye_x>>eye_y>>eye_z;

    cin>>look_x>>look_y>>look_z;

    cin>>up_x>>up_y>>up_z;

    cin>>f_Y>>a_Ratio>>near>>far;

    pt l(look_x-eye_x,look_y-eye_y,look_z-eye_z);
    normalize(l);
    pt up(up_x,up_y,up_z);
    pt r = crossproduct(l,up);
    normalize(r);
    pt u = crossproduct(r,l);


    mtx T;
    Translating(T,-eye_x,-eye_y,-eye_z);

    mtx RotPoint;
    ViewRotation(RotPoint,l,r,u);

    mtx V = MAtrixMultiplication(RotPoint,T);


    double fovX = f_Y * a_Ratio;
    double project_t = near * tan(f_Y*pi/360.0);
    double project_r = near * tan(fovX*pi/360.0);

    mtx P;
    ViewProjection(P,project_t,project_r,near,far);


    string cmnd ="";
    while(true)
    {
        cin>>cmnd;
        if(cmnd=="triangle")
        {
            for(int i=0; i<3; i++)
            {
                double x,y,z;
                cin>>x>>y>>z;

                pt p(x,y,z);
                pt p1,p2,p3;

                p1 = PointMultiplication(TransformationMatrix,p);
                if(p1.getW() !=1) divisonbyweight(p1);
                PrintFunction(stage1_output,p1);

                p2 = PointMultiplication(V,p1);
                if(p2.getW() !=1) divisonbyweight(p2);
                PrintFunction(stage2_output,p2);

                p3 = PointMultiplication(P,p2);
                if(p3.getW() !=1) divisonbyweight(p3);
                PrintFunction(stage3_output,p3);
            }
            stage1_output<<endl;
            stage2_output<<endl;
            stage3_output<<endl;
        }
        else if(cmnd=="scale")
        {
            double x,y,z;
            cin>>x>>y>>z;
            mtx mat;

            Scaling(mat,x,y,z);
            TransformationMatrix = MAtrixMultiplication(TransformationMatrix,mat);
        }
        else if(cmnd=="translate")
        {
            double x,y,z;
            cin>>x>>y>>z;
            mtx mat;
            Translating(mat,x,y,z);
            TransformationMatrix = MAtrixMultiplication(TransformationMatrix,mat);
        }
        else if(cmnd=="rotate")
        {
            double angle,x,y,z;
            cin>>angle>>x>>y>>z;
            pt p(x,y,z);
            mtx mat;
            Rotating(mat,angle,p);
            TransformationMatrix = MAtrixMultiplication(TransformationMatrix,mat);
        }
        else if(cmnd=="push")
        {
            GLStack.push(TransformationMatrix);
        }
        else if(cmnd=="pop")
        {
            TransformationMatrix = GLStack.top();
            GLStack.pop();
        }
        else if(cmnd=="end")
        {
            break;
        }
    }

}
