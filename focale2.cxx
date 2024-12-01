#include <iostream>
#include <vector>
#include <fstream>
#include <cmath>

using namespace std;

int main(){
    ifstream ifile1("lente.txt");
    ifstream ifile2("schermo.txt");
    ofstream ofile1("X.txt");
    ofstream ofile2("Y.txt");
    ofstream ofile3("s_X.txt");
    ofstream ofile4("s_Y.txt");
    ofstream ofile5("p.txt");
    ofstream ofile6("q.txt");
    // 1/p+1/q=1/f ---- X+Y=A_0
    vector<double> p_l, p_s; 
    vector<double> q, p; //p=p_l -p_0 +dr/2 -vv'/6  ,   q=p_s-p_l-dr/2-vv'/6
    vector<double> Y, X; // x=1/p , y=1/q 

    double f;
    double s_p = sqrt(2*0.05*0.05 + 0.01*0.01/4 + 0.01*0.01/36);
    double s_q = s_p;
    cout << "s_p= " << s_p << endl;

    vector<double> s_X, s_Y, s_A;
    
    double valore1, valore2;

    while(ifile1 >> valore1){
        p.push_back(valore1-20.0 + 0.26/2 -1.01/6);
        ofile5 << valore1-20.0 + 0.26/2 -1.01/6 << ", ";
        p_l.push_back(valore1);
    }

    
    while(ifile2 >> valore2){
        p_s.push_back(valore2);
    }


    if(p_s.size() != p_l.size()){
        cout << "vettori p_s e p_l di dimensioni diverse "<< endl;
    }

    for(int i=0; i<p_s.size(); ++i){
        q.push_back(p_s.at(i) - p_l.at(i)-0.26/2 -1.01/6);
        ofile6 << p_s.at(i) - p_l.at(i)-0.26/2 -1.01/6 << ", ";
        Y.push_back(1/q.at(i));
        X.push_back(1/p.at(i));
        s_X.push_back(s_p*pow(X.at(i), 2));  
        s_Y.push_back(s_q*pow(Y.at(i), 2));
        ofile1 << X.at(i) << endl;
        ofile2 << Y.at(i) << endl; 
        ofile3 << s_X.at(i) << endl;
        ofile4 << s_Y.at(i) << endl;
    }

    double covxy=0, sumx=0, sumy=0, sumxy=0;
    double varx=0, vary=0;
    for(int i=0; i<X.size(); ++i){
        sumx += X.at(i);
        sumy += Y.at(i);
        sumxy += Y.at(i)*X.at(i);
        varx += pow(X.at(i), 2);
        vary += pow(Y.at(i), 2);
    }
    double x_m = sumx/X.size();
    double y_m = sumy/X.size();
    double divxy = 0;
    for (int i = 0; i < X.size(); ++i) {
        divxy += pow(X.at(i) - x_m, 2) * pow(Y.at(i) - y_m, 2);
    }

    covxy=(sumxy - (sumx*sumy/X.size()))/(X.size()-1);
    varx = (varx - pow(sumx, 2)/X.size())/(X.size()-1);
    vary = (vary - pow(sumy, 2)/X.size())/(X.size()-1);
    double covxy2 = (sumxy - sumx*sumy)/divxy;

    cout << "covxy= " << covxy << endl;
    cout << "covxy2= " << covxy2 << endl;
    cout << "corr= " << covxy/(sqrt(varx)*sqrt(vary)) << endl;
    // covxy = -covxy;
    double sum=0;

    if(Y.size() != X.size()){
        cout << "vettori x, y di dimensioni diverse "<< endl;
    }
    
    for(int i=0; i<X.size(); ++i){
        sum += ((X.at(i)+Y.at(i))/(pow(s_Y.at(i), 2) + pow(s_X.at(i), 2) + 2*covxy));

    }
    double div = 0;// divisore della formula per A_0
    for(int i=0; i<X.size(); ++i){
        div += 1/(pow(s_Y.at(i), 2) + pow(s_X.at(i), 2) + 2*covxy);
    }
    double A_0 = sum/div;
    cout << "A_0= " << A_0 << endl;
    
    f = 1/A_0;
    double s_A_0= sqrt(sqrt(pow(1/div, 2))); //incertezza sulla media pesata
    double s_f = s_A_0/(A_0 * A_0);
    cout << "f +s_f = " << f << " +- " << s_f << endl;

    double sump= 0.0; 
    double sumq = 0.0; 
    double sumpq = 0.0; 
    int N = p.size();

    // secondo metodo
    for (int i = 0; i < N; ++i) {
        sump += p.at(i);
        sumq += q.at(i);
        sumpq += p.at(i)*q.at(i);
    }
    double p_m = sump/N;
    double q_m = sumq/N;
    double covpq = (sumpq - (sump*sumq/N))/(N-1);
    cout << covpq << endl;
    covpq =0;
    double s_f_2 = pow(pow(q_m / (q_m+p_m), 4) * pow(s_p, 2) + pow(p_m / (q_m+p_m), 4) * pow(s_q, 2) + 2 * pow(q_m*p_m, 2) * covpq / pow(q_m + p_m, 4), 0.5);
    cout << "f +s_f_2 = " << f << " +- " << s_f_2 << endl;

    //aberrazione sferica e cromatica
    f = 5.192692;
    s_f = 0.03;
    // valori ottenuti con la media pesata, usiamo questi valori per calcolare c e V, dato che rappresentano la miglior stima di f, no?

    double l_medio= 0.63195; //incertezza gaussiana
    double s_lmedio = 0.020;
    double c=l_medio*f/(1.4*1.4); //coefficiente aberrazione sferica
    double s_c=c*sqrt(pow((s_lmedio/l_medio), 2) + pow((s_f/f), 2) + 4*pow((0.05/1.4), 2));

    vector<double> A={0.154, 0.111, 0.113, 0.09, 0.096, 0.102, 0.083, 0.105, 0.099, 0.113};
    double sum_A=0; 
    double sum2=0;
    for(int i=0; i<A.size(); ++i){
        sum_A += A.at(i);
    }
    
    double A_medio= sum_A/A.size(); //coefficiente aberrazione cromatica
    double V=f/A_medio; //numero di abbe

    for(int i=0; i<A.size(); ++i){
        sum2 += pow((A_medio - A.at(i)), 2);
    }

     
    double s_A_medio= sqrt(sum2/(A.size()*(A.size()-1)));
    double s_V = V*sqrt(pow((s_f/f), 2) + pow((s_A_medio/A_medio), 2));
    cout << "c = " << c << " +- " << s_c << endl;
    cout << "numero di Abbe V= " << V << " +- " << s_V << endl;

    //Bessel
    double L = 52-20-1.01/3; 
    double s_L = sqrt(2*0.05*0.05 + 0.01/9);//L=P_s-P_0-VV'/3 , s_L = sqrt(2)*s_p = s_q
    double s_medio = 18.59;
    double s_s_medio = 0.0314; 
    double s_f_b = sqrt(pow((s_medio/(2*L)), 2)*pow(s_s_medio, 2) + pow((1/4+pow((s_medio/(2*L)), 2)), 2)*s_L*s_L);
    double f_bessel = (L*L - s_medio*s_medio)/(4*L);
    cout << "f_bessel = " << f_bessel << " +- " << s_f_b << endl;

    return 0;

 
}