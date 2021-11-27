#include <cmath>
#ifndef FORCEMODEL_H
#define FORCEMODEL_H


class ForceModel {
    private:

        int min_grams, max_grams;
        float min_v, max_v;
    
    public:

        ForceModel(int min_grams, int max_grams, float min_v, float max_v) {
            this->min_grams = min_grams;
            this->max_grams = max_grams;
            this->min_v = min_v;
            this->max_v = max_v;
        }

        float fit_equation(float v) {
            /*
                Fits an equation mapping voltage (volts) to weight (grams).
                The equation was generated using a 2nd order polynomial fitted to data.
            */
            if (v < min_v) {
                return max_grams;
            }
            else if (v > max_v) {
                return min_grams;
            }
            else {
                return 32.58f*pow(v, 2) - 244.66f*v + 502.67f;
            }
        }
};


#endif