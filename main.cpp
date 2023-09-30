

#include <iostream>

#include <SDL.h>

#include <stdlib.h>

#include <math.h>
#include <cmath>

using namespace std;

int main(int argc, char *argv[])
{

    // Start of display class
    class Display
    {
    public:
        const int frameLimit = 800;
        int tickMarklen;
        int tickMarkDis = 0;
        int lineLen = 1;
        SDL_Window *window = nullptr;
        SDL_Renderer *renderer = nullptr;

        Display()
        {

            SDL_Init(SDL_INIT_VIDEO);
            SDL_CreateWindowAndRenderer(frameLimit, frameLimit, 0, &window, &renderer);

            SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
            SDL_RenderClear(renderer);

            SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        }

        void RenderXY()
        {
            SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
            SDL_RenderClear(renderer);

            SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

            // This makes the x,y graph
            while (lineLen < frameLimit)
            {
                tickMarklen = 5;

                SDL_RenderDrawPoint(renderer, lineLen, frameLimit / 2);
                SDL_RenderDrawPoint(renderer, frameLimit / 2, lineLen);

                if (tickMarkDis == 10)
                {

                    while (tickMarklen > 0)
                    {
                        SDL_RenderDrawPoint(renderer, frameLimit / 2 + tickMarklen - 3, lineLen);
                        SDL_RenderDrawPoint(renderer, lineLen, frameLimit / 2 + tickMarklen - 3);
                        tickMarklen--;
                    }
                    tickMarkDis = 0;
                }

                tickMarkDis++;
                lineLen++;
            } // end of the x, y graph
        }

        void RenderGraph(int xValuespos[], int yValuespos[], int xValuesneg[], int yValuesneg[])
        {
            // this makes the function
            for (int i = 0; i < 400; i++)
            {
                int k = 1;
                for (int j = 0; j < 5; j++)
                {

                    SDL_RenderDrawPoint(renderer, xValuespos[i] - j + 2, yValuespos[i] - j + 2);
                    SDL_RenderDrawPoint(renderer, xValuesneg[i] - j + 2, yValuesneg[i] - j + 2);
                    SDL_RenderDrawPoint(renderer, xValuespos[i] - k, yValuespos[i] + k + 2);
                    SDL_RenderDrawPoint(renderer, xValuesneg[i] - k, yValuesneg[i] + k + 2);
                    k++;
                }
            }
        }
        void Show()
        {
            SDL_RenderPresent(renderer);

            bool windowRunning = true;
            while (windowRunning)
            {

                SDL_Event event;

                while (SDL_PollEvent(&event))
                {
                    if (event.type == SDL_QUIT)
                    {
                        windowRunning = false;
                    }
                }
            }
        }
        void showless()
        {
            SDL_RenderPresent(renderer);
        }

    }; // end of display class

    // start of function class
    class Function
    {
    public:
        
        const int domainLimit = 400;
        const int rangeLimit = 400;
        const int center = 400;
        int rangepos[400] = {};
        int rangeneg[400] = {};
        int xValuespos[400] = {};
        int xValuesneg[400] = {};
        int yValuespos[400] = {};
        int yValuesneg[400] = {};

        Function()
        {
            for (int i = 0; i < domainLimit; i++)
            {
                rangepos[i] = i;
                rangeneg[i] = 0 - i;
                xValuespos[i] = i + center;
                xValuesneg[i] = center - i;
            }
        }

        virtual void equation()
        {
            return;
        }

        virtual void getInput()
        {
            return;
        }

    }; // end of function class

    // start of linear class
    class Linear : public Function
    {
        // y = mx + b
    public:
        double m = 1;
        double b = 0;
        double f = 0;

        void getInput()
        {
            system("clear");
            cout << "Linear Equation: y = mx + b" << endl;
            cout << "Input a value for m as (a) decimal: ";
            cin >> m;
            cout << "Input a value for (b): ";
            cin >> b;
            cout << "your equation is y = " << m << "x + " << b << endl;
            b = b * 10;
        }

        void equation()
        {

            for (int i = 0; i < 400; i++)
            {
                yValuespos[i] = -(m * (rangepos[i]) + b) + 400;
                yValuesneg[i] = -(m * (rangeneg[i]) + b) + 400;
            }
        }

    }; // end of linear class

    // start of quadratic class
    // y = a(x - h)^2 + k
    class Quadratic : public Function
    {
    public:
        double a = 1;
        double h = 0;
        double k = 0;

        void getInput()
        {
            system("clear");
            cout << "Quadratic Equation: y = a(x - h)^2 + k" << endl;
            cout << "Input a value for (a) as a decimal. Example .04: ";
            cin >> a;
            cout << "Input a value for (h). Example 10: ";
            cin >> h;
            cout << "Input a value for (k). Example -20: ";
            cin >> k;
            cout << "your equation is y = " << a << "(x - " << h << ")^2 + " << k << endl;
            a = a / 10;
            h = h * 10;
            k = k * 10;
        }
        void equation()
        {

            for (int i = 0; i < 400; i++)
            {
                
                yValuespos[i] = -(a * (rangepos[i] - h) * (rangepos[i] - h)) - k + 400;
                yValuesneg[i] = -(a * (rangeneg[i] - h) * (rangeneg[i] - h)) - k + 400;
            }
        }
    }; // end of quadratic class

    // start of exponential class
    class Sin : public Function
    {
    public:
        long double a;
        float b;
        float d;
        float c;

        void getInput()
        {
            system("clear");
            cout << "Sin Equation: y = a * Sin(b(x - d)) + c" << endl;
            cout << "Input a value for (a). Example 10: ";
            cin >> a;
            cout << "Input a value for (b) as a decimal. Example .2: ";
            cin >> b;
            cout << "Input a value for (d). Example 0: ";
            cin >> d;
            cout << "Input a value for (c). Example 0: ";
            cin >> c;
            cout << "your equation is y = " << a << "Sin(" << b << "(x - " << d << ")) + " << c << endl;
            b = b / 10;
            d = d * 10;
            c = c * 10;
            a = a * 10;
        }

        // y = a*sin(b(x-d)) + c
        void equation()
        {

            for (int i = 0; i < 400; i++)
            {
                yValuespos[i] = round(-(a * sin(b * (rangepos[i] + d))) - c + 400);
                yValuesneg[i] = round(-(a * sin(b * (rangeneg[i] + d))) - c + 400);
            }
        }

    }; // end of Sin class

    // start of square root class
    class SquareRoot : Function
    {
    public:
    }; // end of square root class

    // start of logarithmic class
    class Tan : public Function
    {
    public:
        long double a;
        float b;
        float d;
        float c;
        void getInput()
        {
            system("clear");
            cout << "Tangent Equation: y = a * Tan(b * x + c)) + d" << endl;
            cout << "Input a value for (a). Example 10: ";
            cin >> a;
            cout << "Input a value for (b) as a decimal. Example .2: ";
            cin >> b;
            cout << "Input a value for (d). Example 0: ";
            cin >> d;
            cout << "Input a value for (c). Example 0: ";
            cin >> c;
            cout << "your equation is y = " << a << "Sin(" << b << "(x - " << d << ")) + " << c << endl;
            b = b / 10;
            d = d * 10;
            c = c * 10;
            a = a * 10;
        }

        void equation()
        {
            for (int i = 0; i < 400; i++)
            {
                yValuespos[i] = round(-(a * tan(b * rangepos[i] + c)) - d + 400);
                yValuesneg[i] = round(-(a * tan(b * rangeneg[i] + c)) - d + 400);
            }
        }
    }; // end of logarithmic class

    // start of absolute value class
    class AbsoluteValue : public Function
    {
    public:
        double a;
        float b;
        float h;
        float k;
        // y = a|x-h| + k
        void getInput()
        {
            system("clear");
            cout << "Absolute Value Equation: y = a * |x - h| + k" << endl;
            cout << "Input a value for (a). example 1.5: ";
            cin >> a;
            cout << "Input a value for (h). example -10: ";
            cin >> h;
            cout << "Input a value for (k). example -10: ";
            cin >> k;
            cout << "your equation is y = " << a << " * |x - " << h << "| + " << k;
            h = h * 10;
            k = k * 10;
        }

        void equation()
        {

            for (int i = 0; i < 400; i++)
            {
                yValuespos[i] = -(a * abs(rangepos[i] - h)) - k + 400;
                yValuesneg[i] = -(a * abs(rangeneg[i] - h)) - k + 400;
            }
        }
    }; // end of absolute value class

    int choice = 0;
    system("clear");
    cout << "Welcome to the Visual Graphing Calculator." << endl;
    cout << "Please pick a function to graph" << endl;
    cout << "1 Linear\n2 Quadratic\n3 Absolute Value\n4 Sin\n5 Tangent" << endl;
    cout << "Enter the number of your function here: ";
    cin >> choice;

    class Run{
        public:
            void run(Function Chosen, Display display1){
            Chosen.equation();
            display1.RenderXY();
            display1.RenderGraph(Chosen.xValuespos, Chosen.yValuespos, Chosen.xValuesneg, Chosen.yValuesneg);
            display1.RenderGraph(Chosen.xValuespos, Chosen.yValuespos, Chosen.xValuesneg, Chosen.yValuesneg);
            display1.Show();
            }
    };

    Display display1;
    Linear line;
    Quadratic quad;
    AbsoluteValue abs;
    Sin sin;
    Tan tan;
    
    if (choice == 1){
        
        line.getInput();
        line.equation();
        display1.RenderXY();
        display1.RenderGraph(line.xValuespos, line.yValuespos, line.xValuesneg, line.yValuesneg);
        display1.RenderGraph(line.xValuespos, line.yValuespos, line.xValuesneg, line.yValuesneg);
        display1.Show();
    }
    else if (choice == 2){
        quad.getInput();
        quad.equation();
        display1.RenderXY();
        display1.RenderGraph(quad.xValuespos, quad.yValuespos, quad.xValuesneg, quad.yValuesneg);
        display1.RenderGraph(quad.xValuespos, quad.yValuespos, quad.xValuesneg, quad.yValuesneg);
        display1.Show();
        
    }
    else if (choice == 3){
        abs.getInput();
        abs.equation();
        display1.RenderXY();
        display1.RenderGraph(abs.xValuespos, abs.yValuespos, abs.xValuesneg, abs.yValuesneg);
        display1.RenderGraph(abs.xValuespos, abs.yValuespos, abs.xValuesneg, abs.yValuesneg);
        display1.Show();
        
    }
    else if (choice == 4){
        sin.getInput();
        sin.equation();
        display1.RenderXY();
        display1.RenderGraph(sin.xValuespos, sin.yValuespos, sin.xValuesneg, sin.yValuesneg);
        display1.RenderGraph(sin.xValuespos, sin.yValuespos, sin.xValuesneg, sin.yValuesneg);
        display1.Show();
        
    }
    else if (choice == 5){
        tan.getInput();
        tan.equation();
        display1.RenderXY();
        display1.RenderGraph(tan.xValuespos, tan.yValuespos, tan.xValuesneg, tan.yValuesneg);
        display1.RenderGraph(tan.xValuespos, tan.yValuespos, tan.xValuesneg, tan.yValuesneg);
        display1.Show();
        
    }

    
    
    

    return 0;
}
