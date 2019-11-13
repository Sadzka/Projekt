#include <iostream>

using namespace std;

class Polynomial
{
    int n;
    double * args;
public:
    Polynomial() : n(0), args(nullptr)
    {

    }
    Polynomial(int nn) : n(nn)
    {
        args = new double[n];
        for(int i=0; i<n; i++)
            args[i] = 0;
    }
    Polynomial(int nn, double * argss) : n(nn)
    {
        args = new double[nn];
        for(int i=0; i<n; i++)
        {
            args[i] = argss[i];
        }
    }
    Polynomial(Polynomial & poly) : n(poly.n)
    {
        args = new double[n];
        for(int i=0; i<n; i++)
            args[i] = poly.args[i];
    }
    ~Polynomial()
    {
        delete [] args;
    }

    Polynomial & operator=(const Polynomial & poly)
    {
        if(this == &poly)
        {
            return *this;
        }
        else
        {
            delete [] args;

            this->n = poly.n;
            this->args = new double[poly.n];
            for(int i=0; i<poly.n; i++)
                args[i] = poly.args[i];

            //Polynomial(poly.n, poly.args);
            return *this;
        }
    }

    Polynomial operator+(Polynomial & poly)
    {
        if( this->n > poly.n)
        {
            Polynomial ret(*this);

            for(int i = 1; i <= poly.n; i++)
            {
                ret.args[n - i] += poly.args[ poly.n - i];

            }

            return ret;
        }
        else
        {
            Polynomial ret(poly);
            for(int i = 0; i < poly.n; i++)
                ret.args[i] = poly.args[i];

            for(int i = 1; i <= ret.n; i++)
                ret.args[poly.n - i] += ret.args[n - i];

            return ret;
        }
    }

    Polynomial operator-(Polynomial & poly)
    {
        if( this->n > poly.n)
        {
            Polynomial ret(*this);

            for(int i = 1; i <= poly.n; i++)
            {
                ret.args[n - i] -= poly.args[ poly.n - i];

            }

            return ret;
        }
        else
        {
            Polynomial ret(poly);
            for(int i = 0; i < poly.n; i++)
                ret.args[i] = poly.args[i];

            for(int i = 1; i <= ret.n; i++)
                ret.args[poly.n - i] -= ret.args[n - i];

            return ret;
        }
    }

    Polynomial operator*(const Polynomial & poly)
    {
        Polynomial ret(*this);

        int wn = ret.n + poly.n - 1;
        double * wargs = new double[wn];
        for (int i = 0; i < wn; i++)
            wargs[i] = 0;

        for(int i = 0; i < ret.n; i++)
        {
            for (int j = 0; j < poly.n; j++)
            {
                wargs[ i + j ] += (ret.args[i] * poly.args[j]);
            }
        }

        delete [] ret.args;
        ret.args = wargs;
        ret.n = wn;

        return ret;
    }

    Polynomial operator/(Polynomial & poly)
    {
        int ile = this->n - poly.n + 1;
        Polynomial wynik(ile);
        Polynomial reszta(*this);

        for (int i = 0; i < ile; i++)
        {
            wynik.args[i] = reszta.args[i]/poly.args[0];

            for(int j=0; j< poly.n; j++)
            {
                reszta.args[i+j] -= wynik.args[i] * poly.args[j];
            }
        }
        return wynik;
    }

    Polynomial operator%(Polynomial & poly)
    {
        int ile = this->n - poly.n + 1;
        Polynomial wynik(ile);
        Polynomial reszta(*this);

        for (int i = 0; i < ile; i++)
        {
            wynik.args[i] = reszta.args[i]/poly.args[0];

            for(int j=0; j< poly.n; j++)
            {
                reszta.args[i+j] -= wynik.args[i] * poly.args[j];
            }
        }
        return reszta;
    }

    friend ostream & operator<< (ostream &out, const Polynomial &poly)
    {
        poly.show();
    }

    void show()const
    {
        cout << "stopien: " << n-1 << " args: ";
        for(int i=0; i<n-2; i++)
        {
            if(args[i] >= 0)
                cout << "+" << args[i] << "x^" << n-1-i << + " ";
            else
                cout << args[i] << "x^" << n-1-i << + " ";
        }

        if(n >= 2)
        {
            if(args[n-2] >= 0)
                cout << "+" << args[n-2] << "x " ;
            else
                cout <<args[n-2] << "x " ;
        }

        if(n >= 1)
        {
            if(args[n-1] >= 0)
                cout << "+" << args[n-1] << endl;
            else
                cout <<args[n-1]  << endl;
        }
    }

    int getSize()const
    {
        return n;
    }
    double * getArgs()const
    {
        return args;
    }
};

int main()
{
    double args1[3] = {10, 15, 30};
    Polynomial poly1(3, args1 );

    double args2[2] = {1, 5};

    Polynomial poly2(2, args2 );

    poly1.show();
    poly2.show();

    cout << poly1 / poly2;
    return 0;
}
