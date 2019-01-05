#include "harrisdetector.h"
#include <algorithm>
#include <Eigen/Dense>
#include <cmath>

using namespace Eigen;


bool RESPONSECOMP(Vertex i, Vertex j){
    return i.getResponse() > j.getResponse();
}

HarrisDetector::HarrisDetector()
{
    ringNeighbourhood  = 1;
    typeNei = RING;
    k = 0.04;
    fractionDiagonal = 0.01;
    typeSelection = FRACTION;


}

HarrisDetector::HarrisDetector(Mesh& mesh)
{
    this->obj = mesh;
    ringNeighbourhood = 1;
    typeNei = RING;
    k = 0.04;
    fractionDiagonal = 0.01;
    typeSelection = FRACTION;
    paramSelection = 0.01;
}

HarrisDetector::HarrisDetector(Mesh& mesh, Property &prop)
{
    this->obj = mesh;

    map<string, string>::iterator it;

    string val = prop.getProperty("neibourhood");
    if(!val.empty()){
        if(val == "RING")
        {
            typeNei = RING;
        }
        else if(val == "ADAPTIVE")
        {
            typeNei = ADAPTIVE;
        }
    }
    else
        val = RING;

    val = prop.getProperty("nbRings");
    if(!val.empty()){
        if (atoi(val.c_str()) > 0)
            ringNeighbourhood = atoi(val.c_str());
        else
            ringNeighbourhood = 1;
    }
    else
        ringNeighbourhood = 1;
    val = prop.getProperty("fractionDiagonal");

    if(!val.empty()){
        if (atof(val.c_str()) > 0)
            fractionDiagonal = atof(val.c_str());
        else
            fractionDiagonal = 0.01;
    }
    else
        fractionDiagonal = 0.01;

    val = prop.getProperty("k");
    if(!val.empty()){
        if (atof(val.c_str()) > 0)
            k = atof(val.c_str());
        else
            k = 0.04;
    }
    else
        k = 0.04;
    val = prop.getProperty("typeSelection");
    if(!val.empty()){
        if(val == "FRACTION")
            typeSelection = FRACTION;
        else if (val == "CLUSTERING")
            typeSelection = CLUSTERING;
        else
            typeSelection = FRACTION;
    }
    else
        typeSelection = FRACTION;
    val = prop.getProperty("paramSelection");

    if(!val.empty()){
        if (atof(val.c_str()) > 0)
            paramSelection = atoi(val.c_str());
        else
            paramSelection = 0.01;
    }
    else
        paramSelection = 0.01;
}

HarrisDetector::~HarrisDetector()
{

}

vector<Vertex> HarrisDetector::getInterestPoints()
{
   vector<Vertex> interestPoints;

    double max =0.0;
    double diag = obj.getDiag();

    vector<Vertex> Vertices = obj.getVertices();
    vector <vector <uint>> faces = obj.getFaces();

    vector<Vertex>::iterator it;
    for (it = Vertices.begin(); it != Vertices.end(); it++)
    {
        //cout << "iteration " << cont << endl;
        set<uint> neighbours;
        if (typeNei == RING)
            neighbours = (*it).getNeighborhood(ringNeighbourhood,Vertices);
        else if(typeNei == ADAPTIVE)
            neighbours = (*it).getRadius(Vertices,diag*fractionDiagonal);
        // calculating the centroid
        //cout << "calculating the centroid" << endl;
        double xc = 0, yc = 0 , zc = 0;

        set<uint>::iterator it2;
        vector<Vertex> neighb_set;
        //cout << "retrieving the set of neighbours" << endl;
        for (it2 = neighbours.begin(); it2 != neighbours.end();it2++)
        {
            neighb_set.push_back(Vertices[(*it2)]);

            xc += Vertices[(*it2)].getx();
            yc += Vertices[(*it2)].gety();
            zc += Vertices[(*it2)].getz();
        }

        xc /= neighbours.size();
        yc /= neighbours.size();
        zc /= neighbours.size();
        // shifting all values according to the centroid
        //cout << "shift" << endl;
        vector<Vertex>::iterator it3;
        for (it3 = neighb_set.begin(); it3 != neighb_set.end(); it3++)
        {
            (*it3).setx((*it3).x() - xc);
            (*it3).sety((*it3).y() - yc);
            (*it3).setz((*it3).z() - zc);
        }
        // covariance matrix computation
        Matrix3d A;
        //cout << "covariance matrix" << endl;
        for (it3 = neighb_set.begin(); it3 != neighb_set.end(); it3++)
        {
            double x = (*it3).x(), y = (*it3).y(), z = (*it3).z();

            A(0,0) += x*x;
            A(0,1) += x*y; A(1,1) += y*y;
            A(0,2) += x*z; A(1,2) += y*z; A(2,2) += z*z;
        }
        A(1,0) = A(0,1);
        A(2,0) = A(0,2);
        A(2,1) = A(1,2);

        for(int i = 0; i < 2; i++)
            for (int j =0; j < 2; j++)
                A(i,j) /= neighb_set.size();

        // computing eigen vectors
        //cout << "calculating eigen vectors" << endl;
        SelfAdjointEigenSolver<Matrix3d> eigensolver(A);
        if (eigensolver.info() == Success)
        {
            Vector3d eigenvalues = eigensolver.eigenvalues();
            Matrix3d eigenvector = eigensolver.eigenvectors();

            vector<double> eval;
            vector<Vector3d> evec;
            for (int i = 0; i < 3; i++)
            {
                eval.push_back(eigenvalues(i));
                Vector3d currEvec(eigenvector(0,i), eigenvector(1,i),eigenvector(2,i));
                evec.push_back(currEvec);
            }
            // sorting the eigenvalues and vectors in descending order
            reverse(eval.begin(), eval.end());
            reverse(evec.begin(), evec.end());

            double x,y,z;
            x = neighb_set[0].x() - xc;
            y = neighb_set[1].y() - yc;
            z = neighb_set[2].z() - zc;

            // changing the coordinate system, and the values of each point according to the new system
            vector<double> X, Y,Z;
            X.push_back(evec[0](0)); X.push_back(evec[1](0)); X.push_back(evec[2](0));
            Y.push_back(evec[0](1)); Y.push_back(evec[1](1)); Y.push_back(evec[2](1));
            Z.push_back(evec[0](2)); Z.push_back(evec[1](2)); Z.push_back(evec[2](2));

            if (Z[0]*x + Z[1]*y + Z[2]*z < 0)
            {
                Z[0] = -Z[0];
                Z[1] = -Z[1];
                Z[2] = -Z[2];

                swap(X[0], Y[0]);
                swap(X[1], Y[1]);
                swap(X[2], Y[2]);
            }

            for (it3 = neighb_set.begin(); it3 != neighb_set.end(); it3++)
            {
                double a = (*it3).x(),
                       b = (*it3).y(),
                       c = (*it3).z();
                (*it3).setx(X[0]*a +X[1]*b +X[2]*c);
                (*it3).sety(Y[0]*a +Y[1]*b +Y[2]*c);
                (*it3).setz(Z[0]*a +Z[1]*b +Z[2]*c);
            }

            double x1 = neighb_set[0].x(), y1 = neighb_set[0].y();

            for (it3 = neighb_set.begin(); it3 != neighb_set.end(); it3++)
            {
                double a = (*it3).x(),
                       b = (*it3).y();
                (*it3).setx(a - x1);
                (*it3).sety(b - y1);
            }

            MatrixXd QM(6,6);
            VectorXd QV(6);

            for (it3 = neighb_set.begin(); it3 != neighb_set.end(); it3++)
            {
                double a = (*it3).x(),
                       b = (*it3).y(),
                       c = (*it3).z();

                QM(0,0) += pow(a,4);
                QM(0,1) += pow(a,3)*b;
                QM(0,2) += a*a*b*b;
                QM(0,3) += pow(a,3);
                QM(0,4) += a*a*b;
                QM(0,5) += a*a;

                QM(1,1) += a*a*b*b;
                QM(1,2) += a*b*b*b;
                QM(1,3) += a*a*b;
                QM(1,4) += a*b*b;
                QM(1,5) += a*b;

                QM(2,2) += b*b*b*b;
                QM(2,3) += a*b*b;
                QM(2,4) += b*b*b;
                QM(2,5) += b*b;

                QM(3,3) += b*b*b;
                QM(3,4) += a*b;
                QM(3,5) += a;

                QM(4,4) += b*b;
                QM(4,5) += b;

                QV(0) += c*a*a; QV(1) += c*a*b; QV(2) += c*b*b;
                QV(3) += c*a; QV(4) += c*b; QV(5) += c;
            }
            QM(1,0) = QM(0,1);
            QM(2,0) = QM(0,2);
            QM(3,0) = QM(0,3);
            QM(4,0) = QM(0,4);
            QM(5,0) = QM(0,5);

            QM(2,1) = QM(1,2);
            QM(3,1) = QM(1,3);
            QM(4,1) = QM(1,4);
            QM(5,1) = QM(1,5);

            QM(3,2) = QM(2,3);
            QM(4,2) = QM(2,4);
            QM(5,2) = QM(2,5);

            QM(4,3) = QM(3,4);
            QM(5,3) = QM(3,5);

            QM(5,4) = QM(4,5);

            QM(5,5) = double(neighb_set.size());

            // solving the system

            VectorXd RES = QM.fullPivLu().solve(QV);


            double FX2 = RES(3)*RES(3) + 2*pow(RES(0),4) + 2*RES(1)*RES(1) ;
            double FY2 = RES(3)*RES(3) + 2*pow(RES(2),4) + 2*RES(1)*RES(1) ;
            double FXFY= RES(3)*RES(4) + 2*RES(0)*RES(0)*RES(1) + 2*RES(1)*RES(2)*RES(2);

            double resp = FX2 * FY2 - FXFY * FXFY - this->k*(FX2 + FY2) * (FX2+FY2) ;
            (*it).setResponse(resp);
            //cout << resp << endl;
            if (resp > max)
                max = resp;
        }
    }
    vector<Vertex> candidates;
    for (it = Vertices.begin(); it != Vertices.end(); it++)
    {
        (*it).processMax(Vertices);
        if(it->getInterest())
        {
            candidates.push_back(*it);
        }
    }
    sort(candidates.begin(), candidates.end(), RESPONSECOMP);
    if (typeSelection == FRACTION)
    {
        double f = (1 / paramSelection);
        long fl = long(f);
        long plzwork = Vertices.size();
        long numPoints = plzwork/fl;
        if(candidates.size() > numPoints)
            for (it = candidates.begin(); it != candidates.begin() + numPoints; it++)
                interestPoints.push_back(*it);
        else
        interestPoints = candidates;
    }
    else if(typeSelection == CLUSTERING)
    {
        cout << "Clustering selection" << endl;
        for (it = candidates.begin(); it != candidates.end(); it++)
        {
            bool found = false;
            unsigned int i = 0;
            while (i < interestPoints.size() && found == false)
            {
                double X = interestPoints[i].x() - it->x();
                double Y = interestPoints[i].y() - it->y();
                double Z = interestPoints[i].z() - it->z();
                i++;
                if(sqrt(X*X + Y*Y + Z*Z) < (diag*paramSelection))
                    found = true;
            }
            if (found == false)
                interestPoints.push_back(*it);
        }
    }
    return interestPoints;
}
