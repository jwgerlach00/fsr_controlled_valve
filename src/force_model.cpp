class ForceModel {
    private:
        int min_force, max_force;
        float min_v, max_v;
    
    public:

        ForceModel(int min_force, int max_force, float min_v, float max_v) {
            this->min_force = min_force;
            this->max_force = max_force;
            this->min_v = min_v;
            this->max_v = max_v;
        }

        float fit_equation(float v) {
            if (v < min_v) {
                return max_force;
            }
            else if (v > max_v) {
                return min_force;
            }
            else {
                return 32.58f*pow(v, 2) - 244.66f*v + 502.76f;
            }
        }
    
};